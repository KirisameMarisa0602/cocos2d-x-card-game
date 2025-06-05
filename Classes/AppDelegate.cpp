#include "AppDelegate.h"
#include "controllers/GameController.h"

USING_NS_CC;

/**
 * @brief ���캯����ͨ���������⴦��
 */
AppDelegate::AppDelegate() {}

/**
 * @brief ������������Դ�ͷŵȣ����������ֶ��ͷţ�
 */
AppDelegate::~AppDelegate() {}

/**
 * @brief Ӧ�ó�ʼ����ڣ�������Ⱦ���ڡ��ֱ��ʡ���ԴĿ¼������������
 */
bool AppDelegate::applicationDidFinishLaunching()
{
    // 1. ��ȡ���ݣ�Director����OpenGL��ͼ
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

    // 2. �����δ����OpenGL��ͼ���򴴽��´��ڣ�ָ�����⡢��С������ϵ����
    if (!glview)
    {
        glview = GLViewImpl::createWithRect("CardGame", cocos2d::Rect(0, 0, 1080, 2080), 0.5f);
        director->setOpenGLView(glview);
    }

    // 3. ������Ʒֱ���Ϊ1080*2080���������Ӧ����֤��ͬ��Ļ��ʾһ��
    glview->setDesignResolutionSize(1080, 2080, ResolutionPolicy::FIXED_WIDTH);

    // 4. ����֡��Ϊ60FPS
    director->setAnimationInterval(1.0f / 60);

    // 5. �����Դ����·����resĿ¼����������Դ����
    FileUtils::getInstance()->addSearchPath("res");

    // 6. ������������������GameControllerΪ��Ϸ����������
    auto scene = GameController::create();
    director->runWithScene(scene);

    return true;
}

/**
 * @brief Ӧ�ý����̨ʱ�ص������е�����App�������ȣ�����ͣ����
 */
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
}

/**
 * @brief Ӧ�����½���ǰ̨ʱ�ص����ָ�����
 */
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
}