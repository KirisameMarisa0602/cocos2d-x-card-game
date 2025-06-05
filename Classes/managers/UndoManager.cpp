// UndoManager.cpp
// ֻʵ�ֳ������߼������������� UndoModel �洢

#include "UndoManager.h"

UndoManager::UndoManager(UndoModel* undoModel)
    : _undoModel(undoModel)
{
}

// ��¼һ�β���
void UndoManager::recordMove(const CardMoveOp& op)
{
    _undoModel->pushOp(op);
}

// �������һ�β���
CardMoveOp UndoManager::undo()
{
    return _undoModel->popOp();
}

// �Ƿ���Գ���
bool UndoManager::canUndo() const
{
    return _undoModel->canUndo();
}

// ������г�����¼
void UndoManager::clear()
{
    _undoModel->clear();
}

// ��ȡֻ��������ʷ
const std::stack<CardMoveOp>& UndoManager::getHistory() const
{
    return _undoModel->getHistory();
}