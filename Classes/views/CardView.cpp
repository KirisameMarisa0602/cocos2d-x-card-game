// CardView.cpp
// �ƵĿ��ӻ���ͼ��ʵ��

#include "CardView.h"

// ������������������ͼ����ʼ��
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

// ��ʼ�������������ͼ��������ģ��
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

// ���°�����ģ��
void CardView::setModel(CardModel* model)
{
    _model = model;
    refresh();
}

// ˢ����ͼ����ʾ��������ɫ��
void CardView::refresh()
{
    this->removeAllChildren();

    // ֻ�����泯��ʱ����ʾ����
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

    // ��ɫ�����顢���ң���ɫ��÷��������
    std::string color = (suit == CST_DIAMONDS || suit == CST_HEARTS) ? "red" : "black";
    std::string sFace;
    // �ƺ�����
    if (face == 0) sFace = "A";
    else if (face == 10) sFace = "J";
    else if (face == 11) sFace = "Q";
    else if (face == 12) sFace = "K";
    else sFace = std::to_string(face + 1);

    // ����С���֡���ɫ����������Դ·��
    std::string smallNumPath = "number/small_" + color + "_" + sFace + ".png";
    std::string bigNumPath = "number/big_" + color + "_" + sFace + ".png";
    std::string suitName[] = { "club", "diamond", "heart", "spade" };
    std::string suitPath = "suits/" + std::string(suitName[suit]) + ".png";

    // ��־���������Ϣ
    CCLOG("CardView::refresh face=%d suit=%d %s %s %s", face, suit, smallNumPath.c_str(), bigNumPath.c_str(), suitPath.c_str());

    // ���Ͻ�С����
    auto smallNum = cocos2d::Sprite::create(smallNumPath);
    if (smallNum)
    {
        smallNum->setAnchorPoint(cocos2d::Vec2(0, 1));
        smallNum->setPosition(cocos2d::Vec2(10, getContentSize().height - 10));
        addChild(smallNum);
    }
    // ���Ͻǻ�ɫ
    auto suitIcon = cocos2d::Sprite::create(suitPath);
    if (suitIcon)
    {
        suitIcon->setAnchorPoint(cocos2d::Vec2(1, 1));
        suitIcon->setPosition(cocos2d::Vec2(getContentSize().width - 10, getContentSize().height - 10));
        addChild(suitIcon);
    }
    // �ײ����������
    auto bigNum = cocos2d::Sprite::create(bigNumPath);
    if (bigNum)
    {
        bigNum->setAnchorPoint(cocos2d::Vec2(0.5, 0));
        bigNum->setPosition(cocos2d::Vec2(getContentSize().width / 2, 10));
        addChild(bigNum);
    }
}