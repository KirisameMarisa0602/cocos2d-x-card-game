// GameView.cpp
// 游戏界面主视图实现，包括自动缩放、自动排布等核心逻辑

#include "GameView.h"
#include "ui/CocosGUI.h"

bool GameView::init()
{
    if (!Layer::init()) return false;
    setContentSize(cocos2d::Size(1080, 2080));

    // 桌面背景
    auto deskBg = cocos2d::LayerColor::create(cocos2d::Color4B(180, 120, 60, 255), 1080, 1500);
    deskBg->setPosition(0, 580);
    this->addChild(deskBg, -2);

    // 手牌区背景
    auto handBg = cocos2d::LayerColor::create(cocos2d::Color4B(120, 30, 140, 255), 1080, 580);
    handBg->setPosition(0, 0);
    this->addChild(handBg, -2);

    return true;
}

void GameView::renderPlayfield(const std::vector<CardModel*>& cards)
{
    // 1. 清理已经不存在的视图
    for (auto it = _cardViews.begin(); it != _cardViews.end(); )
    {
        if (std::find(cards.begin(), cards.end(), it->first) == cards.end())
        {
            if (it->second)
                it->second->removeFromParent();
            it = _cardViews.erase(it);
        }
        else
        {
            ++it;
        }
    }

    // 2. 遍历所有模型，逐一渲染
    for (auto* model : cards)
    {
        CardView* view = nullptr;
        if (_cardViews.count(model) == 0) {
            view = CardView::create(model);
            _cardViews[model] = view;
            this->addChild(view);
        }
        else {
            view = _cardViews[model];
            view->refresh();
        }
        // 直接用模型里的坐标
        view->setPosition(model->getCardPos());
        view->setScale(1.0f); // 保证无缩放
        view->setLocalZOrder(10);
    }
}

// 自动适配手牌区（堆区）牌的横排布局
void GameView::renderStack(const std::vector<CardModel*>& cards)
{
    const float cardWidth = 120.0f;
    const float minSpacing = 6.0f;
    const float maxSpacing = 40.0f;
    const float topCardGap = 60.0f;     // 顶牌与次顶牌间隔
    const float baseY = 200.0f;         // 手牌区纵坐标

    const float undoBtnWidth = 64.0f;
    const float undoBtnMargin = 30.0f;
    const float rightMargin = undoBtnWidth + undoBtnMargin + 30.0f;

    size_t n = cards.size();
    if (n == 0) return;

    float leftMargin = 90.0f;
    float totalWidth = 1080.0f - leftMargin - rightMargin;

    // 1. 优先用最大间距
    float spacing = maxSpacing;
    if (n > 1) {
        float requiredWidth = cardWidth * n + maxSpacing * (n - 2) + topCardGap;
        // 2. 若超出总宽度则收缩间距
        if (requiredWidth > totalWidth) {
            spacing = (totalWidth - cardWidth * n - topCardGap) / (n - 2);
            if (spacing < minSpacing) spacing = minSpacing;
        }
    }

    // 3. 若极限收缩后仍放不下，则整体缩放
    float usedWidth = cardWidth * n + spacing * (n - 2) + (n > 1 ? topCardGap : 0);
    float scale = 1.0f;
    if (usedWidth > totalWidth) {
        scale = totalWidth / usedWidth;
        usedWidth = totalWidth;
    }

    // 4. 计算起点，实现整体居中
    float startX = leftMargin + (totalWidth - usedWidth) / 2 + cardWidth * scale / 2;

    // 5. 遍历所有手牌，依次横排排布，自动适配间距和缩放
    for (size_t i = 0; i < n; ++i)
    {
        CardModel* model = cards[i];
        CardView* view = nullptr;
        if (_cardViews.count(model) == 0) {
            view = CardView::create(model);
            _cardViews[model] = view;
            this->addChild(view);
        }
        else {
            view = _cardViews[model];
            view->refresh();
        }

        float x = startX;
        if (n == 1) {
            x = startX;
        }
        else if (i < n - 1) {
            x += i * (cardWidth * scale + spacing * scale);
        }
        else {
            // 顶部牌与前一张牌有更大间隔
            x += (n - 1) * (cardWidth * scale + spacing * scale) + topCardGap * scale;
        }
        view->setPosition(cocos2d::Vec2(x, baseY));
        view->setScale(scale); // 自动缩放
        view->setLocalZOrder(100 + i);
    }
}

// 显示“回退”文字按钮，并注册点击回调
void GameView::showUndoButton(const std::function<void()>& callback)
{
    using namespace cocos2d;
    using namespace ui;
    // 创建无背景的文字按钮，显示“回退”
    auto btn = Button::create();
    btn->setTitleText("RollBack");
    btn->setTitleFontSize(36);
    btn->setTitleColor(Color3B::WHITE);
    btn->setContentSize(Size(100, 60)); // 按钮尺寸可调
    btn->setPosition(Vec2(1080 - 70, 360)); // 右下角
    btn->setScale9Enabled(true);
    btn->setOpacity(200); // 略透明
    btn->addClickEventListener([=](Ref*) { callback(); });
    this->addChild(btn, 1000);
}

// 动画将某张牌移动到目标位置，动画结束后可回调
void GameView::moveCardWithAnimation(CardModel* model, const cocos2d::Vec2& to, std::function<void()> onComplete)
{
    CardView* view = getCardView(model);
    if (!view) return;
    auto move = cocos2d::MoveTo::create(0.3f, to);
    if (onComplete) {
        auto seq = cocos2d::Sequence::create(move, cocos2d::CallFunc::create(onComplete), nullptr);
        view->runAction(seq);
    }
    else {
        view->runAction(move);
    }
}

// 获取某张牌数据模型对应的视图
CardView* GameView::getCardView(CardModel* model) const
{
    auto it = _cardViews.find(model);
    if (it != _cardViews.end())
        return it->second;
    return nullptr;
}

// 移除所有卡牌视图
void GameView::clearCardViews()
{
    for (auto& pair : _cardViews)
    {
        if (pair.second)
            pair.second->removeFromParent();
    }
    _cardViews.clear();
}