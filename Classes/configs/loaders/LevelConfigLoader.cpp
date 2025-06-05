// configs/loaders/LevelConfigLoader.cpp
// �ؿ������ļ�����ʵ��

#include "LevelConfigLoader.h"
#include "json/document.h"
#include "cocos2d.h"

LevelConfig* LevelConfigLoader::loadFromFile(const std::string& jsonPath) {
    using namespace cocos2d;
    // ��ȡ�ļ�����
    std::string fileData = FileUtils::getInstance()->getStringFromFile(jsonPath);
    if (fileData.empty()) return nullptr;

    rapidjson::Document doc;
    doc.Parse(fileData.c_str());
    if (doc.HasParseError()) return nullptr;

    LevelConfig* config = new LevelConfig();

    // ����Playfield
    if (doc.HasMember("Playfield") && doc["Playfield"].IsArray()) {
        for (auto& cardDef : doc["Playfield"].GetArray()) {
            CardConfig card;
            card.face = cardDef["CardFace"].GetInt();
            card.suit = cardDef["CardSuit"].GetInt();
            card.pos.x = cardDef["Position"]["x"].GetFloat();
            card.pos.y = cardDef["Position"]["y"].GetFloat();
            config->playfieldCards.push_back(card);
        }
    }
    // ����Stack
    if (doc.HasMember("Stack") && doc["Stack"].IsArray()) {
        for (auto& cardDef : doc["Stack"].GetArray()) {
            CardConfig card;
            card.face = cardDef["CardFace"].GetInt();
            card.suit = cardDef["CardSuit"].GetInt();
            card.pos.x = cardDef["Position"]["x"].GetFloat();
            card.pos.y = cardDef["Position"]["y"].GetFloat();
            config->stackCards.push_back(card);
        }
    }
    return config;
}