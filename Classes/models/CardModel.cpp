// CardModel.cpp
// 牌数据模型实现

#include "CardModel.h"

// 静态工厂方法，创建并初始化一张牌
CardModel* CardModel::create(int face, int suit, const cocos2d::Vec2& pos, bool isFaceUp)
{
    CardModel* ret = new CardModel();
    // 初始化成功则返回对象，否则安全删除
    if (ret && ret->init(face, suit, pos, isFaceUp)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret); // 安全删除，防止内存泄漏
    return nullptr;
}

// 实际初始化函数
bool CardModel::init(int face, int suit, const cocos2d::Vec2& pos, bool isFaceUp)
{
    // 非法点数或花色直接失败
    if (face < 0 || face > 13)   // 非法点数
        return false;
    if (suit < 0 || suit > 3)    // 非法花色
        return false;

    // 正常赋值
    _face = face;
    _suit = suit;
    _isFaceUp = isFaceUp;
    _cardPos = pos;
    return true;
}