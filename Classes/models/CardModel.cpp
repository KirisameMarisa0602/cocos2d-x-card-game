// CardModel.cpp
// ������ģ��ʵ��

#include "CardModel.h"

// ��̬������������������ʼ��һ����
CardModel* CardModel::create(int face, int suit, const cocos2d::Vec2& pos, bool isFaceUp)
{
    CardModel* ret = new CardModel();
    // ��ʼ���ɹ��򷵻ض��󣬷���ȫɾ��
    if (ret && ret->init(face, suit, pos, isFaceUp)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret); // ��ȫɾ������ֹ�ڴ�й©
    return nullptr;
}

// ʵ�ʳ�ʼ������
bool CardModel::init(int face, int suit, const cocos2d::Vec2& pos, bool isFaceUp)
{
    // �Ƿ�������ɫֱ��ʧ��
    if (face < 0 || face > 13)   // �Ƿ�����
        return false;
    if (suit < 0 || suit > 3)    // �Ƿ���ɫ
        return false;

    // ������ֵ
    _face = face;
    _suit = suit;
    _isFaceUp = isFaceUp;
    _cardPos = pos;
    return true;
}