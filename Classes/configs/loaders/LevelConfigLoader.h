// configs/loaders/LevelConfigLoader.h
// 关卡配置文件加载逻辑，将JSON文件解析为LevelConfig数据结构

#pragma once
#include "configs/models/LevelConfig.h"
#include <string>

class LevelConfigLoader {
public:
    // 从JSON文件加载关卡配置，返回LevelConfig对象
    // 失败时返回nullptr
    static LevelConfig* loadFromFile(const std::string& jsonPath);
};