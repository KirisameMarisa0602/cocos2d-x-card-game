// UndoModel.h
// ֻ��������������ʷ���ݴ洢����ʵ�ֳ����߼�

#pragma once
#include "CardModel.h"
#include <stack>

// ��¼һ�����ƶ��Ĳ�����Ϣ��֧����������������¼���滻�Ķ�������Ϣ��
struct CardMoveOp
{
    CardModel* card;             // ���ƶ�����ָ��
    cocos2d::Vec2 from;          // ��ʼλ��
    cocos2d::Vec2 to;            // Ŀ��λ��
    int fromArea;                // ��ʼ����0: ����, 1: ���棩
    int toArea;                  // Ŀ������
    int fromIndex;               // ���ƶ���ԭʼ�����������±�
    CardModel* replacedCard;     // ���滻����������ԭ�����ƣ�������������ʱ��Ч��
    int replacedIndex;           // ԭ�������ڱ��������±�
    cocos2d::Vec2 replacedFrom;  // ԭ�����Ƶ���ʼλ��
    // ���캯����Ĭ��ȫ����Ч
    CardMoveOp()
        : card(nullptr), fromArea(-1), toArea(-1), fromIndex(-1),
        replacedCard(nullptr), replacedIndex(-1), replacedFrom(cocos2d::Vec2::ZERO) {
    }
};

// UndoModel ֻ����ʷ�������ݵĴ�ȡ����������������
class UndoModel : public cocos2d::Ref
{
public:
    // ���һ��������¼����ʷջ
    void pushOp(const CardMoveOp& op);

    // �������һ��������¼��ִ�г���ʱ���ã�
    CardMoveOp popOp();

    // �ж��Ƿ��пɳ�������
    bool canUndo() const;

    // �����ʷ��¼
    void clear();

    // ��ȡֻ������ʷջ������UIֻ����ʾ��
    const std::stack<CardMoveOp>& getHistory() const;

private:
    std::stack<CardMoveOp> _history; // ����������ʷջ
};