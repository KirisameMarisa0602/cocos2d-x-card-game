// CardModel.h
// ������ģ�ͣ������¼�����Ƶĵ�������ɫ�������桢λ�õ���Ϣ

#pragma once
#include "cocos2d.h"

// ��ɫ����ö��
enum CardSuitType {
    CST_NONE = -1,      // δ֪/�޻�ɫ
    CST_CLUBS,          // ÷��
    CST_DIAMONDS,       // ����
    CST_HEARTS,         // ����
    CST_SPADES,         // ����
    CST_NUM_CARD_SUIT_TYPES // ��ɫö������
};

// �ƺ�����ö��
enum CardFaceType {
    CFT_NONE = -1,      // δ֪/�޵���
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
    CFT_NUM_CARD_FACE_TYPES // �ƺ�ö������
};

// �����Ƶ�����ģ�ͣ�����洢��������ɫ��λ�á���������Ϣ
class CardModel : public cocos2d::Ref // �̳�Ref��֧�����ü�������
{
public:
    // ��̬��������������һ����
    static CardModel* create(int face, int suit, const cocos2d::Vec2& pos, bool isFaceUp = true);

    // ��ȡ�ƺ�
    int getFace() const { return _face; }

    // ��ȡ��ɫ
    int getSuit() const { return _suit; }

    // ����/��ȡ���Ƿ����泯��
    void setFaceUp(bool up) { _isFaceUp = up; }
    bool isFaceUp() const { return _isFaceUp; }

    // ����/��ȡ�Ƶ�λ��
    void setCardPos(const cocos2d::Vec2& pos) { _cardPos = pos; }
    cocos2d::Vec2 getCardPos() const { return _cardPos; }

protected:
    int _face;              // �ƺ�
    int _suit;              // ��ɫ
    bool _isFaceUp;         // �Ƿ����泯��
    cocos2d::Vec2 _cardPos; // ���ڽ����ϵ�����

    // ʵ�ʳ�ʼ������
    bool init(int face, int suit, const cocos2d::Vec2& pos, bool isFaceUp);
};