// GameModel.h
// 修改：关卡加载由LevelConfigLoader统一管理

#pragma once
#include "CardModel.h"
#include <vector>

// 前向声明
class LevelConfig;

class GameModel : public cocos2d::Ref
{
public:
    static GameModel* getInstance();

    // 新接口：通过LevelConfig加载
    void loadLevelConfig(LevelConfig* config);

    // 旧接口：通过json路径加载（内部自动调用LevelConfigLoader）
    void loadLevel(const std::string& jsonPath);

    std::vector<CardModel*>& getPlayfield();
    std::vector<CardModel*>& getStack();

    void moveCardToPlayfield(CardModel* card, const cocos2d::Vec2& toPos);
    void moveCardToStack(CardModel* card, const cocos2d::Vec2& toPos);

    void clear();

private:
    std::vector<CardModel*> _playfield;
    std::vector<CardModel*> _stack;
};