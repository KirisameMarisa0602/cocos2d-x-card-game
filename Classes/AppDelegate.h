#pragma once

#include "cocos2d.h"

/**
 * @brief Ӧ�ó�������࣬����Cocos2d-x�����ʼ�����������ü�����������
 *        �̳��� cocos2d::Application�������������������
 */
class AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
     * @brief Ӧ�ó����ʼ���ص�������OpenGL��ͼ����Ʒֱ��ʡ�����������
     * @return true ��ʾ��ʼ���ɹ���false ��ʾʧ��
     */
    virtual bool applicationDidFinishLaunching();

    /**
     * @brief ��Ӧ�ý����̨�����е�����App��������ʱ������
     */
    virtual void applicationDidEnterBackground();

    /**
     * @brief ��Ӧ�����½���ǰ̨�����л�App��ʱ������
     */
    virtual void applicationWillEnterForeground();
};