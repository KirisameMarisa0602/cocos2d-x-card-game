// UndoManager.cpp
// 只实现撤销的逻辑操作，数据由 UndoModel 存储

#include "UndoManager.h"

UndoManager::UndoManager(UndoModel* undoModel)
    : _undoModel(undoModel)
{
}

// 记录一次操作
void UndoManager::recordMove(const CardMoveOp& op)
{
    _undoModel->pushOp(op);
}

// 撤销最近一次操作
CardMoveOp UndoManager::undo()
{
    return _undoModel->popOp();
}

// 是否可以撤销
bool UndoManager::canUndo() const
{
    return _undoModel->canUndo();
}

// 清空所有撤销记录
void UndoManager::clear()
{
    _undoModel->clear();
}

// 获取只读撤销历史
const std::stack<CardMoveOp>& UndoManager::getHistory() const
{
    return _undoModel->getHistory();
}