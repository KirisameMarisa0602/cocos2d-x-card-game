// GameController.h
// ��Ϸ��������������������ģ�͡���ͼ���û�����

#pragma once
#include "models/GameModel.h"
#include "views/GameView.h"
#include "models/UndoModel.h"
#include "managers/UndoManager.h"

class GameController : public cocos2d::Scene
{
public:
    // ��ʼ������
    virtual bool init();

    // ��׼ Cocos2d-x ��������
    CREATE_FUNC(GameController);

private:
    GameView* _view = nullptr;         // ��Ϸ������ͼ
    GameModel* _model = nullptr;       // ��Ϸ����ģ��
    UndoModel* _undoModel = nullptr;   // ��������ģ��
    UndoManager* _undoManager = nullptr; // ����������

    // ע�����пɽ����Ƶļ�����
    void registerCardListeners();

    // �������������������Ƶĵ��
    void onStackCardClicked(CardModel* card);

    // �����������Ƶĵ��
    void onPlayfieldCardClicked(CardModel* card);

    // ������˰�ť���
    void onUndoClicked();
};