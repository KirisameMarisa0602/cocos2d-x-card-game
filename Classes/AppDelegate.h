#pragma once

#include "cocos2d.h"

/**
 * @brief 应用程序入口类，负责Cocos2d-x引擎初始化、窗口设置及主场景加载
 *        继承自 cocos2d::Application，生命周期由引擎管理
 */
class AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
     * @brief 应用程序初始化回调，设置OpenGL视图、设计分辨率、运行主场景
     * @return true 表示初始化成功，false 表示失败
     */
    virtual bool applicationDidFinishLaunching();

    /**
     * @brief 当应用进入后台（如切到其他App或锁屏）时被调用
     */
    virtual void applicationDidEnterBackground();

    /**
     * @brief 当应用重新进入前台（如切回App）时被调用
     */
    virtual void applicationWillEnterForeground();
};