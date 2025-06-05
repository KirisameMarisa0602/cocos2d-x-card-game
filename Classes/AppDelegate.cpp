#include "AppDelegate.h"
#include "controllers/GameController.h"

USING_NS_CC;

/**
 * @brief 构造函数，通常不做特殊处理
 */
AppDelegate::AppDelegate() {}

/**
 * @brief 析构函数，资源释放等（本例无需手动释放）
 */
AppDelegate::~AppDelegate() {}

/**
 * @brief 应用初始化入口，设置渲染窗口、分辨率、资源目录并加载主场景
 */
bool AppDelegate::applicationDidFinishLaunching()
{
    // 1. 获取导演（Director）和OpenGL视图
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

    // 2. 如果还未创建OpenGL视图，则创建新窗口（指定标题、大小和缩放系数）
    if (!glview)
    {
        glview = GLViewImpl::createWithRect("CardGame", cocos2d::Rect(0, 0, 1080, 2080), 0.5f);
        director->setOpenGLView(glview);
    }

    // 3. 设置设计分辨率为1080*2080，宽度自适应，保证不同屏幕显示一致
    glview->setDesignResolutionSize(1080, 2080, ResolutionPolicy::FIXED_WIDTH);

    // 4. 设置帧率为60FPS
    director->setAnimationInterval(1.0f / 60);

    // 5. 添加资源查找路径（res目录），便于资源加载
    FileUtils::getInstance()->addSearchPath("res");

    // 6. 创建并运行主场景（GameController为游戏主控制器）
    auto scene = GameController::create();
    director->runWithScene(scene);

    return true;
}

/**
 * @brief 应用进入后台时回调（如切到其他App、锁屏等），暂停动画
 */
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
}

/**
 * @brief 应用重新进入前台时回调，恢复动画
 */
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
}