// UndoModel.h
// 只负责撤销操作的历史数据存储，不实现撤销逻辑

#pragma once
#include "CardModel.h"
#include <stack>

// 记录一次牌移动的操作信息（支持手牌区交换，记录被替换的顶部牌信息）
struct CardMoveOp
{
    CardModel* card;             // 被移动的牌指针
    cocos2d::Vec2 from;          // 起始位置
    cocos2d::Vec2 to;            // 目标位置
    int fromArea;                // 起始区域（0: 手牌, 1: 桌面）
    int toArea;                  // 目标区域
    int fromIndex;               // 被移动牌原始在手牌区的下标
    CardModel* replacedCard;     // 被替换到备用区的原顶部牌（仅手牌区交换时有效）
    int replacedIndex;           // 原顶部牌在备用区的下标
    cocos2d::Vec2 replacedFrom;  // 原顶部牌的起始位置
    // 构造函数：默认全部无效
    CardMoveOp()
        : card(nullptr), fromArea(-1), toArea(-1), fromIndex(-1),
        replacedCard(nullptr), replacedIndex(-1), replacedFrom(cocos2d::Vec2::ZERO) {
    }
};

// UndoModel 只做历史操作数据的存取，不包含撤销功能
class UndoModel : public cocos2d::Ref
{
public:
    // 添加一条操作记录到历史栈
    void pushOp(const CardMoveOp& op);

    // 弹出最近一条操作记录（执行撤销时调用）
    CardMoveOp popOp();

    // 判断是否还有可撤销操作
    bool canUndo() const;

    // 清空历史记录
    void clear();

    // 获取只读的历史栈（如需UI只读显示）
    const std::stack<CardMoveOp>& getHistory() const;

private:
    std::stack<CardMoveOp> _history; // 撤销操作历史栈
};