// GameView.h
// 游戏界面视图层，负责牌区、手牌区的布局、自动适应、动画等

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

    // 渲染桌面区的所有牌，自动布局
    void renderPlayfield(const std::vector<CardModel*>& cards);

    // 渲染手牌区的所有牌，自动布局
    void renderStack(const std::vector<CardModel*>& cards);

    // 显示“回退”按钮，并注册点击回调
    void showUndoButton(const std::function<void()>& callback);

    // 以动画移动某张牌到指定位置，动画结束可执行回调
    void moveCardWithAnimation(CardModel* model, const cocos2d::Vec2& to, std::function<void()> onComplete = nullptr);

    // 获取某数据模型对应的视图
    CardView* getCardView(CardModel* model) const;

    // 移除并清空所有卡牌视图
    void clearCardViews();
private:
    // 数据模型指针到视图的映射表
    std::unordered_map<CardModel*, CardView*> _cardViews;
};