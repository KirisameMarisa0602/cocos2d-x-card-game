// CardView.h
// 牌的可视化视图类，负责单张牌的图像、花色、点数和表现层

#pragma once
#include "cocos2d.h"
#include "models/CardModel.h"

class CardView : public cocos2d::Sprite
{
public:
    // 工厂方法：创建一个与数据模型绑定的牌视图
    static CardView* create(CardModel* model);

    // 重新绑定数据模型
    void setModel(CardModel* model);

    // 获取当前绑定的数据模型
    CardModel* getModel() const { return _model; }

    // 刷新显示（如点数、花色变化时调用）
    void refresh();

protected:
    CardModel* _model; // 绑定的数据模型指针
    bool init(CardModel* model); // 实际初始化方法
};