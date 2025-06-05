// CardModel.h
// 牌数据模型，负责记录单张牌的点数、花色、正反面、位置等信息

#pragma once
#include "cocos2d.h"

// 花色类型枚举
enum CardSuitType {
    CST_NONE = -1,      // 未知/无花色
    CST_CLUBS,          // 梅花
    CST_DIAMONDS,       // 方块
    CST_HEARTS,         // 红桃
    CST_SPADES,         // 黑桃
    CST_NUM_CARD_SUIT_TYPES // 花色枚举数量
};

// 牌号类型枚举
enum CardFaceType {
    CFT_NONE = -1,      // 未知/无点数
    CFT_ACE,            // A
    CFT_TWO,            // 2
    CFT_THREE,          // 3
    CFT_FOUR,           // 4
    CFT_FIVE,           // 5
    CFT_SIX,            // 6
    CFT_SEVEN,          // 7
    CFT_EIGHT,          // 8
    CFT_NINE,           // 9
    CFT_TEN,            // 10
    CFT_JACK,           // J
    CFT_QUEEN,          // Q
    CFT_KING,           // K
    CFT_NUM_CARD_FACE_TYPES // 牌号枚举数量
};

// 单张牌的数据模型，负责存储点数、花色、位置、正反面信息
class CardModel : public cocos2d::Ref // 继承Ref，支持引用计数管理
{
public:
    // 静态工厂方法，创建一张牌
    static CardModel* create(int face, int suit, const cocos2d::Vec2& pos, bool isFaceUp = true);

    // 获取牌号
    int getFace() const { return _face; }

    // 获取花色
    int getSuit() const { return _suit; }

    // 设置/获取牌是否正面朝上
    void setFaceUp(bool up) { _isFaceUp = up; }
    bool isFaceUp() const { return _isFaceUp; }

    // 设置/获取牌的位置
    void setCardPos(const cocos2d::Vec2& pos) { _cardPos = pos; }
    cocos2d::Vec2 getCardPos() const { return _cardPos; }

protected:
    int _face;              // 牌号
    int _suit;              // 花色
    bool _isFaceUp;         // 是否正面朝上
    cocos2d::Vec2 _cardPos; // 牌在界面上的坐标

    // 实际初始化函数
    bool init(int face, int suit, const cocos2d::Vec2& pos, bool isFaceUp);
};