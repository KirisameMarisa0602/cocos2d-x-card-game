// configs/models/LevelConfig.h
// 关卡配置数据结构，仅做数据描述

#pragma once
#include "cocos2d.h"
#include <vector>

// 单张牌的配置
struct CardConfig {
    int face;               // 牌面
    int suit;               // 花色
    cocos2d::Vec2 pos;      // 位置
};

// 关卡配置：包含桌面区和手牌区两部分牌的初始信息
class LevelConfig {
public:
    std::vector<CardConfig> playfieldCards; // 桌面区牌
    std::vector<CardConfig> stackCards;     // 手牌区牌
};