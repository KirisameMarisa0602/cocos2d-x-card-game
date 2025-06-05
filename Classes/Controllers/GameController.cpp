// GameController.cpp
// ��Ϸ������ʵ�֣������û������߼�������ˢ�¡�����ͬ��

#include "GameController.h"
#include "ui/CocosGUI.h"

bool GameController::init()
{
    if (!Scene::init()) return false;

    // ��ȡ����ʼ��������ģ��
    _model = GameModel::getInstance();
    _model->loadLevel("level/level1.json");

    // ���� UndoModel �� UndoManager���ǵ�������Ա������
    _undoModel = new UndoModel();
    _undoModel->retain(); // ��ѭ cocos2d-x ���ü���
    _undoManager = new UndoManager(_undoModel);

    // ������ͼ
    _view = GameView::create();
    addChild(_view);

    // ��Ⱦ��ʼ����
    _view->renderPlayfield(_model->getPlayfield());
    _view->renderStack(_model->getStack());

    // ע�����
    registerCardListeners();

    // ��ʾ���˰�ť��ע��ص�
    _view->showUndoButton(CC_CALLBACK_0(GameController::onUndoClicked, this));
    return true;
}

// ע�����пɽ����Ƶļ�����
void GameController::registerCardListeners()
{
    // ��ȡ�¼��ַ���
    auto dispatcher = _view->getEventDispatcher();

    // ���Ƴ������Ѵ��ڵļ���������ֹ�ظ����
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

    // 1. �������������зǶ��ƿɵ㣨���Ʋ��ܵ㣩
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

    // 2. ���������������ƿɵ�
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

// �������������������Ƶĵ�������������ƶ�����������¼����
void GameController::onStackCardClicked(CardModel* card)
{
    auto& stack = _model->getStack();
    if (stack.size() < 2) return;
    CardModel* topCard = stack.back();
    if (card == topCard) return;

    int fromIndex = std::find(stack.begin(), stack.end(), card) - stack.begin();
    cocos2d::Vec2 fromPos = _view->getCardView(card)->getPosition();
    cocos2d::Vec2 toPos = _view->getCardView(topCard)->getPosition();

    // ��¼ԭ��������Ϣ�������滻�����������ƣ�
    CardModel* replacedCard = topCard;
    int replacedIndex = fromIndex;
    cocos2d::Vec2 replacedFrom = _view->getCardView(replacedCard)->getPosition();

    // ��������Ϣ
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

    // ���������Ƶ�����
    stack.erase(stack.begin() + fromIndex);
    stack.push_back(card);

    _view->moveCardWithAnimation(card, toPos, [this]() {
        _view->renderStack(_model->getStack());
        registerCardListeners();
        });
}

// �����������Ƶĵ�����ƶ������ƶ�������¼����
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

// ������˰�ť�����ʵ�������������������������߼�
void GameController::onUndoClicked()
{
    if (!_undoManager->canUndo()) return;
    CardMoveOp op = _undoManager->undo();
    if (!op.card) return;

    auto& stack = _model->getStack();
    auto& playfield = _model->getPlayfield();

    // �ȴӵ�ǰλ���Ƴ����ƶ�����
    if (op.toArea == 0) {
        auto it = std::find(stack.begin(), stack.end(), op.card);
        if (it != stack.end()) stack.erase(it);

        // �����������������������Ҫ�Ѷ�����Ҳ������ȥ
        if (op.fromArea == 0 && op.toArea == 0 && op.replacedCard) {
            // �Ƴ���ǰ�����ı��滻��
            auto it2 = std::find(stack.begin(), stack.end(), op.replacedCard);
            if (it2 != stack.end()) stack.erase(it2);

            // �ָ������Ƶ�����
            op.card->setCardPos(op.from);
            op.replacedCard->setCardPos(op.replacedFrom);

            // ���ԭ�����ƺͶ�����
            stack.insert(stack.begin() + op.fromIndex, op.card);
            stack.push_back(op.replacedCard);

            // �������ƶ����ƶ����ƻ�ԭλ�ã�ˢ��
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

    // ��������������������������ȣ�
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