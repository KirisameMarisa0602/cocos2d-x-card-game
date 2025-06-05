// UndoManager.h
// �������㣬��������ص��߼����������� UndoModel ���ݣ��ǵ�����

#pragma once
#include "models/UndoModel.h"

// UndoManager ��Ϊ controller �ĳ�Ա�������������߼�
class UndoManager
{
public:
    // ���캯��������ע�� UndoModel ָ��
    UndoManager(UndoModel* undoModel);

    // ��¼һ���Ƶ��ƶ�����
    void recordMove(const CardMoveOp& op);

    // ִ�г������������ز������ݣ�ʵ�ʻ����� controller ִ�У�
    CardMoveOp undo();

    // �ж��Ƿ���Գ���
    bool canUndo() const;

    // ��ճ�����ʷ
    void clear();

    // ��ȡֻ��������ʷ������UI��ʾ��
    const std::stack<CardMoveOp>& getHistory() const;

private:
    UndoModel* _undoModel; // ��������ģ�ͣ���ʵ����������Ĳ���
};