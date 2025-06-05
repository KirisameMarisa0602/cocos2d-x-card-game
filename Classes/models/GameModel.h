// GameModel.h
// �޸ģ��ؿ�������LevelConfigLoaderͳһ����

#pragma once
#include "CardModel.h"
#include <vector>

// ǰ������
class LevelConfig;

class GameModel : public cocos2d::Ref
{
public:
    static GameModel* getInstance();

    // �½ӿڣ�ͨ��LevelConfig����
    void loadLevelConfig(LevelConfig* config);

    // �ɽӿڣ�ͨ��json·�����أ��ڲ��Զ�����LevelConfigLoader��
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