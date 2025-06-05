// CardView.h
// �ƵĿ��ӻ���ͼ�࣬�������Ƶ�ͼ�񡢻�ɫ�������ͱ��ֲ�

#pragma once
#include "cocos2d.h"
#include "models/CardModel.h"

class CardView : public cocos2d::Sprite
{
public:
    // ��������������һ��������ģ�Ͱ󶨵�����ͼ
    static CardView* create(CardModel* model);

    // ���°�����ģ��
    void setModel(CardModel* model);

    // ��ȡ��ǰ�󶨵�����ģ��
    CardModel* getModel() const { return _model; }

    // ˢ����ʾ�����������ɫ�仯ʱ���ã�
    void refresh();

protected:
    CardModel* _model; // �󶨵�����ģ��ָ��
    bool init(CardModel* model); // ʵ�ʳ�ʼ������
};