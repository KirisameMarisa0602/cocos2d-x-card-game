// GameView.cpp
// ��Ϸ��������ͼʵ�֣������Զ����š��Զ��Ų��Ⱥ����߼�

#include "GameView.h"
#include "ui/CocosGUI.h"

bool GameView::init()
{
    if (!Layer::init()) return false;
    setContentSize(cocos2d::Size(1080, 2080));

    // ���汳��
    auto deskBg = cocos2d::LayerColor::create(cocos2d::Color4B(180, 120, 60, 255), 1080, 1500);
    deskBg->setPosition(0, 580);
    this->addChild(deskBg, -2);

    // ����������
    auto handBg = cocos2d::LayerColor::create(cocos2d::Color4B(120, 30, 140, 255), 1080, 580);
    handBg->setPosition(0, 0);
    this->addChild(handBg, -2);

    return true;
}

void GameView::renderPlayfield(const std::vector<CardModel*>& cards)
{
    // 1. �����Ѿ������ڵ���ͼ
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

    // 2. ��������ģ�ͣ���һ��Ⱦ
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
        // ֱ����ģ���������
        view->setPosition(model->getCardPos());
        view->setScale(1.0f); // ��֤������
        view->setLocalZOrder(10);
    }
}

// �Զ��������������������Ƶĺ��Ų���
void GameView::renderStack(const std::vector<CardModel*>& cards)
{
    const float cardWidth = 120.0f;
    const float minSpacing = 6.0f;
    const float maxSpacing = 40.0f;
    const float topCardGap = 60.0f;     // ������ζ��Ƽ��
    const float baseY = 200.0f;         // ������������

    const float undoBtnWidth = 64.0f;
    const float undoBtnMargin = 30.0f;
    const float rightMargin = undoBtnWidth + undoBtnMargin + 30.0f;

    size_t n = cards.size();
    if (n == 0) return;

    float leftMargin = 90.0f;
    float totalWidth = 1080.0f - leftMargin - rightMargin;

    // 1. �����������
    float spacing = maxSpacing;
    if (n > 1) {
        float requiredWidth = cardWidth * n + maxSpacing * (n - 2) + topCardGap;
        // 2. �������ܿ�����������
        if (requiredWidth > totalWidth) {
            spacing = (totalWidth - cardWidth * n - topCardGap) / (n - 2);
            if (spacing < minSpacing) spacing = minSpacing;
        }
    }

    // 3. �������������ԷŲ��£�����������
    float usedWidth = cardWidth * n + spacing * (n - 2) + (n > 1 ? topCardGap : 0);
    float scale = 1.0f;
    if (usedWidth > totalWidth) {
        scale = totalWidth / usedWidth;
        usedWidth = totalWidth;
    }

    // 4. ������㣬ʵ���������
    float startX = leftMargin + (totalWidth - usedWidth) / 2 + cardWidth * scale / 2;

    // 5. �����������ƣ����κ����Ų����Զ������������
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
            // ��������ǰһ�����и�����
            x += (n - 1) * (cardWidth * scale + spacing * scale) + topCardGap * scale;
        }
        view->setPosition(cocos2d::Vec2(x, baseY));
        view->setScale(scale); // �Զ�����
        view->setLocalZOrder(100 + i);
    }
}

// ��ʾ�����ˡ����ְ�ť����ע�����ص�
void GameView::showUndoButton(const std::function<void()>& callback)
{
    using namespace cocos2d;
    using namespace ui;
    // �����ޱ��������ְ�ť����ʾ�����ˡ�
    auto btn = Button::create();
    btn->setTitleText("RollBack");
    btn->setTitleFontSize(36);
    btn->setTitleColor(Color3B::WHITE);
    btn->setContentSize(Size(100, 60)); // ��ť�ߴ�ɵ�
    btn->setPosition(Vec2(1080 - 70, 360)); // ���½�
    btn->setScale9Enabled(true);
    btn->setOpacity(200); // ��͸��
    btn->addClickEventListener([=](Ref*) { callback(); });
    this->addChild(btn, 1000);
}

// ������ĳ�����ƶ���Ŀ��λ�ã�����������ɻص�
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

// ��ȡĳ��������ģ�Ͷ�Ӧ����ͼ
CardView* GameView::getCardView(CardModel* model) const
{
    auto it = _cardViews.find(model);
    if (it != _cardViews.end())
        return it->second;
    return nullptr;
}

// �Ƴ����п�����ͼ
void GameView::clearCardViews()
{
    for (auto& pair : _cardViews)
    {
        if (pair.second)
            pair.second->removeFromParent();
    }
    _cardViews.clear();
}