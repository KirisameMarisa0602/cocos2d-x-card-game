// GameModel.cpp
// �޸ģ�֧��ͨ��LevelConfig����

#include "GameModel.h"
#include "configs/models/LevelConfig.h"
#include "configs/loaders/LevelConfigLoader.h"
#include "cocos2d.h"
#include <algorithm>

GameModel* GameModel::getInstance()
{
    static GameModel instance;
    return &instance;
}

void GameModel::clear()
{
    for (auto c : _playfield) c->release();
    for (auto c : _stack) c->release();
    _playfield.clear();
    _stack.clear();
}

// �½ӿڣ�ͨ��LevelConfigֱ�Ӽ���
void GameModel::loadLevelConfig(LevelConfig* config)
{
    clear();
    if (!config) return;

    // ������
    for (const auto& cardCfg : config->playfieldCards) {
        CardModel* card = CardModel::create(cardCfg.face, cardCfg.suit, cardCfg.pos, true);
        card->retain();
        _playfield.push_back(card);
    }
    // ������
    for (const auto& cardCfg : config->stackCards) {
        CardModel* card = CardModel::create(cardCfg.face, cardCfg.suit, cardCfg.pos, true);
        card->retain();
        _stack.push_back(card);
    }
}

// �ɽӿڣ�ͨ��LevelConfigLoader��Ӽ���
void GameModel::loadLevel(const std::string& jsonPath)
{
    LevelConfig* config = LevelConfigLoader::loadFromFile(jsonPath);
    loadLevelConfig(config);
    if (config) delete config; // ע���ͷ�
}

std::vector<CardModel*>& GameModel::getPlayfield() { return _playfield; }
std::vector<CardModel*>& GameModel::getStack() { return _stack; }

void GameModel::moveCardToPlayfield(CardModel* card, const cocos2d::Vec2& toPos)
{
    auto it = std::find(_stack.begin(), _stack.end(), card);
    if (it != _stack.end())
        _stack.erase(it);
    card->setCardPos(toPos);
    _playfield.push_back(card);
}

void GameModel::moveCardToStack(CardModel* card, const cocos2d::Vec2& toPos)
{
    auto it = std::find(_playfield.begin(), _playfield.end(), card);
    if (it != _playfield.end())
        _playfield.erase(it);
    card->setCardPos(toPos);
    _stack.push_back(card);
}