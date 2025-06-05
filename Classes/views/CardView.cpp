// CardView.cpp
// 牌的可视化视图类实现

#include "CardView.h"

// 工厂方法：创建新视图并初始化
CardView* CardView::create(CardModel* model)
{
    CardView* ret = new CardView();
    if (ret && ret->init(model)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

// 初始化：加载牌面底图、绑定数据模型
bool CardView::init(CardModel* model)
{
    if (!Sprite::initWithFile("card_general.png"))
        return false;
    _model = model;
    if (_model)
        setPosition(_model->getCardPos());
    refresh();
    return true;
}

// 重新绑定数据模型
void CardView::setModel(CardModel* model)
{
    _model = model;
    refresh();
}

// 刷新视图，显示点数、花色等
void CardView::refresh()
{
    this->removeAllChildren();

    // 只有正面朝上时才显示内容
    if (!_model || !_model->isFaceUp()) return;

    int suit = _model->getSuit();
    int face = _model->getFace();
    if (suit < 0 || suit > 3) {
        CCLOG("Invalid suit: %d", suit);
        return;
    }
    if (face < 0 || face > 12) {
        CCLOG("Invalid face: %d", face);
        return;
    }

    // 红色：方块、红桃，黑色：梅花、黑桃
    std::string color = (suit == CST_DIAMONDS || suit == CST_HEARTS) ? "red" : "black";
    std::string sFace;
    // 牌号文字
    if (face == 0) sFace = "A";
    else if (face == 10) sFace = "J";
    else if (face == 11) sFace = "Q";
    else if (face == 12) sFace = "K";
    else sFace = std::to_string(face + 1);

    // 牌面小数字、花色、大数字资源路径
    std::string smallNumPath = "number/small_" + color + "_" + sFace + ".png";
    std::string bigNumPath = "number/big_" + color + "_" + sFace + ".png";
    std::string suitName[] = { "club", "diamond", "heart", "spade" };
    std::string suitPath = "suits/" + std::string(suitName[suit]) + ".png";

    // 日志输出调试信息
    CCLOG("CardView::refresh face=%d suit=%d %s %s %s", face, suit, smallNumPath.c_str(), bigNumPath.c_str(), suitPath.c_str());

    // 左上角小数字
    auto smallNum = cocos2d::Sprite::create(smallNumPath);
    if (smallNum)
    {
        smallNum->setAnchorPoint(cocos2d::Vec2(0, 1));
        smallNum->setPosition(cocos2d::Vec2(10, getContentSize().height - 10));
        addChild(smallNum);
    }
    // 右上角花色
    auto suitIcon = cocos2d::Sprite::create(suitPath);
    if (suitIcon)
    {
        suitIcon->setAnchorPoint(cocos2d::Vec2(1, 1));
        suitIcon->setPosition(cocos2d::Vec2(getContentSize().width - 10, getContentSize().height - 10));
        addChild(suitIcon);
    }
    // 底部中央大数字
    auto bigNum = cocos2d::Sprite::create(bigNumPath);
    if (bigNum)
    {
        bigNum->setAnchorPoint(cocos2d::Vec2(0.5, 0));
        bigNum->setPosition(cocos2d::Vec2(getContentSize().width / 2, 10));
        addChild(bigNum);
    }
}