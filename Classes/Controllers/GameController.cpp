// GameController.cpp
// 游戏控制器实现，负责用户操作逻辑、界面刷新、数据同步

#include "GameController.h"
#include "ui/CocosGUI.h"

bool GameController::init()
{
    if (!Scene::init()) return false;

    // 获取并初始化主数据模型
    _model = GameModel::getInstance();
    _model->loadLevel("level/level1.json");

    // 创建 UndoModel 和 UndoManager（非单例，成员变量）
    _undoModel = new UndoModel();
    _undoModel->retain(); // 遵循 cocos2d-x 引用计数
    _undoManager = new UndoManager(_undoModel);

    // 创建视图
    _view = GameView::create();
    addChild(_view);

    // 渲染初始数据
    _view->renderPlayfield(_model->getPlayfield());
    _view->renderStack(_model->getStack());

    // 注册监听
    registerCardListeners();

    // 显示回退按钮并注册回调
    _view->showUndoButton(CC_CALLBACK_0(GameController::onUndoClicked, this));
    return true;
}

// 注册所有可交互牌的监听器
void GameController::registerCardListeners()
{
    // 获取事件分发器
    auto dispatcher = _view->getEventDispatcher();

    // 先移除所有已存在的监听器，防止重复添加
    for (auto card : _model->getPlayfield()) {
        CardView* view = _view->getCardView(card);
        if (view)
            dispatcher->removeEventListenersForTarget(view, true);
    }
    for (auto card : _model->getStack()) {
        CardView* view = _view->getCardView(card);
        if (view)
            dispatcher->removeEventListenersForTarget(view, true);
    }

    // 1. 手牌区——所有非顶牌可点（顶牌不能点）
    auto& stack = _model->getStack();
    if (stack.size() > 1) {
        for (size_t i = 0; i < stack.size() - 1; ++i) {
            CardModel* card = stack[i];
            CardView* view = _view->getCardView(card);
            if (view) {
                auto listener = cocos2d::EventListenerTouchOneByOne::create();
                listener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event*) {
                    if (view->getBoundingBox().containsPoint(touch->getLocation())) {
                        this->onStackCardClicked(card);
                        return true;
                    }
                    return false;
                    };
                dispatcher->addEventListenerWithSceneGraphPriority(listener, view);
            }
        }
    }

    // 2. 桌面区——所有牌可点
    for (auto card : _model->getPlayfield()) {
        CardView* view = _view->getCardView(card);
        if (view) {
            auto listener = cocos2d::EventListenerTouchOneByOne::create();
            listener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event*) {
                if (view->getBoundingBox().containsPoint(touch->getLocation())) {
                    this->onPlayfieldCardClicked(card);
                    return true;
                }
                return false;
                };
            dispatcher->addEventListenerWithSceneGraphPriority(listener, view);
        }
    }
}

// 处理手牌区（堆区）牌的点击：将备用牌移动到顶部并记录操作
void GameController::onStackCardClicked(CardModel* card)
{
    auto& stack = _model->getStack();
    if (stack.size() < 2) return;
    CardModel* topCard = stack.back();
    if (card == topCard) return;

    int fromIndex = std::find(stack.begin(), stack.end(), card) - stack.begin();
    cocos2d::Vec2 fromPos = _view->getCardView(card)->getPosition();
    cocos2d::Vec2 toPos = _view->getCardView(topCard)->getPosition();

    // 记录原顶部牌信息（即被替换到备用区的牌）
    CardModel* replacedCard = topCard;
    int replacedIndex = fromIndex;
    cocos2d::Vec2 replacedFrom = _view->getCardView(replacedCard)->getPosition();

    // 填充操作信息
    CardMoveOp op;
    op.card = card;
    op.from = fromPos;
    op.to = toPos;
    op.fromArea = 0;
    op.toArea = 0;
    op.fromIndex = fromIndex;
    op.replacedCard = replacedCard;
    op.replacedIndex = replacedIndex;
    op.replacedFrom = replacedFrom;
    _undoManager->recordMove(op);

    // 将备用牌移到顶部
    stack.erase(stack.begin() + fromIndex);
    stack.push_back(card);

    _view->moveCardWithAnimation(card, toPos, [this]() {
        _view->renderStack(_model->getStack());
        registerCardListeners();
        });
}

// 处理桌面区牌的点击：移动到手牌顶部并记录操作
void GameController::onPlayfieldCardClicked(CardModel* card)
{
    auto& stack = _model->getStack();
    if (stack.empty()) return;
    CardModel* topCard = stack.back();

    if (abs(topCard->getFace() - card->getFace()) == 1) {
        cocos2d::Vec2 fromPos = _view->getCardView(card)->getPosition();
        cocos2d::Vec2 toPos = _view->getCardView(topCard)->getPosition();

        CardMoveOp op;
        op.card = card;
        op.from = fromPos;
        op.to = toPos;
        op.fromArea = 1;
        op.toArea = 0;
        op.fromIndex = -1;
        op.replacedCard = nullptr;
        op.replacedIndex = -1;
        op.replacedFrom = cocos2d::Vec2::ZERO;
        _undoManager->recordMove(op);

        auto& playfield = _model->getPlayfield();
        playfield.erase(std::find(playfield.begin(), playfield.end(), card));
        stack.push_back(card);

        _view->moveCardWithAnimation(card, toPos, [this]() {
            _view->renderPlayfield(_model->getPlayfield());
            _view->renderStack(_model->getStack());
            registerCardListeners();
            });
    }
}

// 处理回退按钮点击：实现手牌区交换和桌面区回退逻辑
void GameController::onUndoClicked()
{
    if (!_undoManager->canUndo()) return;
    CardMoveOp op = _undoManager->undo();
    if (!op.card) return;

    auto& stack = _model->getStack();
    auto& playfield = _model->getPlayfield();

    // 先从当前位置移除被移动的牌
    if (op.toArea == 0) {
        auto it = std::find(stack.begin(), stack.end(), op.card);
        if (it != stack.end()) stack.erase(it);

        // 如果是手牌区交换操作，需要把顶部牌也交换回去
        if (op.fromArea == 0 && op.toArea == 0 && op.replacedCard) {
            // 移除当前顶部的被替换牌
            auto it2 = std::find(stack.begin(), stack.end(), op.replacedCard);
            if (it2 != stack.end()) stack.erase(it2);

            // 恢复两张牌的坐标
            op.card->setCardPos(op.from);
            op.replacedCard->setCardPos(op.replacedFrom);

            // 插回原备用牌和顶部牌
            stack.insert(stack.begin() + op.fromIndex, op.card);
            stack.push_back(op.replacedCard);

            // 动画：移动被移动的牌回原位置，刷新
            _view->moveCardWithAnimation(op.card, op.from, [this]() {
                _view->renderStack(_model->getStack());
                registerCardListeners();
                });
            return;
        }
    }
    else if (op.toArea == 1) {
        auto it = std::find(playfield.begin(), playfield.end(), op.card);
        if (it != playfield.end()) playfield.erase(it);
    }

    // 其它情况（如桌面区→手牌区等）
    op.card->setCardPos(op.from);
    if (op.fromArea == 0) {
        stack.push_back(op.card);
    }
    else if (op.fromArea == 1) {
        playfield.push_back(op.card);
    }
    _view->moveCardWithAnimation(op.card, op.from, [this]() {
        _view->renderPlayfield(_model->getPlayfield());
        _view->renderStack(_model->getStack());
        registerCardListeners();
        });
}