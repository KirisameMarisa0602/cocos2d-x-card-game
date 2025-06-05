// UndoModel.cpp
// ֻ�������ݣ���ʵ���κγ����߼�

#include "UndoModel.h"

// ���һ��������������ʷջ
void UndoModel::pushOp(const CardMoveOp& op)
{
    _history.push(op);
}

// �������һ������������¼
CardMoveOp UndoModel::popOp()
{
    if (_history.empty())
        return CardMoveOp(); // ������Ч����
    CardMoveOp op = _history.top();
    _history.pop();
    return op;
}

// �ж��Ƿ��пɳ�������
bool UndoModel::canUndo() const
{
    return !_history.empty();
}

// ������г���������ʷ
void UndoModel::clear()
{
    while (!_history.empty()) _history.pop();
}

// ��ȡֻ����ʷջ
const std::stack<CardMoveOp>& UndoModel::getHistory() const
{
    return _history;
}