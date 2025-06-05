// GameController.h
// 游戏控制器，负责连接数据模型、视图与用户交互

#pragma once
#include "models/GameModel.h"
#include "views/GameView.h"
#include "models/UndoModel.h"
#include "managers/UndoManager.h"

class GameController : public cocos2d::Scene
{
public:
    // 初始化方法
    virtual bool init();

    // 标准 Cocos2d-x 创建方法
    CREATE_FUNC(GameController);

private:
    GameView* _view = nullptr;         // 游戏界面视图
    GameModel* _model = nullptr;       // 游戏数据模型
    UndoModel* _undoModel = nullptr;   // 撤销数据模型
    UndoManager* _undoManager = nullptr; // 撤销管理器

    // 注册所有可交互牌的监听器
    void registerCardListeners();

    // 处理手牌区（堆区）牌的点击
    void onStackCardClicked(CardModel* card);

    // 处理桌面区牌的点击
    void onPlayfieldCardClicked(CardModel* card);

    // 处理回退按钮点击
    void onUndoClicked();
};