// GameView.h
// ��Ϸ������ͼ�㣬�����������������Ĳ��֡��Զ���Ӧ��������

#pragma once
#include "models/CardModel.h"
#include "views/CardView.h"
#include <functional>
#include <unordered_map>
#include "cocos2d.h"

class GameView : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(GameView);

    // ��Ⱦ�������������ƣ��Զ�����
    void renderPlayfield(const std::vector<CardModel*>& cards);

    // ��Ⱦ�������������ƣ��Զ�����
    void renderStack(const std::vector<CardModel*>& cards);

    // ��ʾ�����ˡ���ť����ע�����ص�
    void showUndoButton(const std::function<void()>& callback);

    // �Զ����ƶ�ĳ���Ƶ�ָ��λ�ã�����������ִ�лص�
    void moveCardWithAnimation(CardModel* model, const cocos2d::Vec2& to, std::function<void()> onComplete = nullptr);

    // ��ȡĳ����ģ�Ͷ�Ӧ����ͼ
    CardView* getCardView(CardModel* model) const;

    // �Ƴ���������п�����ͼ
    void clearCardViews();
private:
    // ����ģ��ָ�뵽��ͼ��ӳ���
    std::unordered_map<CardModel*, CardView*> _cardViews;
};