// UndoModel.cpp
// 只负责数据，不实现任何撤销逻辑

#include "UndoModel.h"

// 添加一条撤销操作到历史栈
void UndoModel::pushOp(const CardMoveOp& op)
{
    _history.push(op);
}

// 弹出最近一条撤销操作记录
CardMoveOp UndoModel::popOp()
{
    if (_history.empty())
        return CardMoveOp(); // 返回无效操作
    CardMoveOp op = _history.top();
    _history.pop();
    return op;
}

// 判断是否还有可撤销操作
bool UndoModel::canUndo() const
{
    return !_history.empty();
}

// 清空所有撤销操作历史
void UndoModel::clear()
{
    while (!_history.empty()) _history.pop();
}

// 获取只读历史栈
const std::stack<CardMoveOp>& UndoModel::getHistory() const
{
    return _history;
}