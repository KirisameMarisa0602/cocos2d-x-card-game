// configs/models/LevelConfig.h
// �ؿ��������ݽṹ��������������

#pragma once
#include "cocos2d.h"
#include <vector>

// �����Ƶ�����
struct CardConfig {
    int face;               // ����
    int suit;               // ��ɫ
    cocos2d::Vec2 pos;      // λ��
};

// �ؿ����ã��������������������������Ƶĳ�ʼ��Ϣ
class LevelConfig {
public:
    std::vector<CardConfig> playfieldCards; // ��������
    std::vector<CardConfig> stackCards;     // ��������
};