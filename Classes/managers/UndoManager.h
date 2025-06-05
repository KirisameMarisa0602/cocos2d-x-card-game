// UndoManager.h
// 管理器层，负责撤销相关的逻辑操作，持有 UndoModel 数据（非单例）

#pragma once
#include "models/UndoModel.h"

// UndoManager 作为 controller 的成员变量，负责撤销逻辑
class UndoManager
{
public:
    // 构造函数，依赖注入 UndoModel 指针
    UndoManager(UndoModel* undoModel);

    // 记录一次牌的移动操作
    void recordMove(const CardMoveOp& op);

    // 执行撤销操作（返回操作数据，实际回退由 controller 执行）
    CardMoveOp undo();

    // 判断是否可以撤销
    bool canUndo() const;

    // 清空撤销历史
    void clear();

    // 获取只读撤销历史（如需UI显示）
    const std::stack<CardMoveOp>& getHistory() const;

private:
    UndoModel* _undoModel; // 持有数据模型，不实现数据自身的操作
};