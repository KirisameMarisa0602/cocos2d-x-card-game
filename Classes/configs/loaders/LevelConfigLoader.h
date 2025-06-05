// configs/loaders/LevelConfigLoader.h
// �ؿ������ļ������߼�����JSON�ļ�����ΪLevelConfig���ݽṹ

#pragma once
#include "configs/models/LevelConfig.h"
#include <string>

class LevelConfigLoader {
public:
    // ��JSON�ļ����عؿ����ã�����LevelConfig����
    // ʧ��ʱ����nullptr
    static LevelConfig* loadFromFile(const std::string& jsonPath);
};