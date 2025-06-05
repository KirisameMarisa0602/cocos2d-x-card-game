// configs/loaders/LevelConfigLoader.cpp
// 关卡配置文件加载实现

#include "LevelConfigLoader.h"
#include "json/document.h"
#include "cocos2d.h"

LevelConfig* LevelConfigLoader::loadFromFile(const std::string& jsonPath) {
    using namespace cocos2d;
    // 读取文件内容
    std::string fileData = FileUtils::getInstance()->getStringFromFile(jsonPath);
    if (fileData.empty()) return nullptr;

    rapidjson::Document doc;
    doc.Parse(fileData.c_str());
    if (doc.HasParseError()) return nullptr;

    LevelConfig* config = new LevelConfig();

    // 解析Playfield
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
    // 解析Stack
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