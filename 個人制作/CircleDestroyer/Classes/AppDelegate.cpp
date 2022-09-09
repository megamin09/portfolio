/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "AppDelegate.h"
#include "../proj.win32/src/flame_main/function_main.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(1920, 1080);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1280, 720);
static cocos2d::Size largeResolutionSize = cocos2d::Size(1920, 1080);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
// �ʂ̃R���e�L�X�g���K�v�ȏꍇ�́AglContextAttrs�̒l��ύX���܂�
// ���ׂẴv���b�g�t�H�[���ɉe�����܂�

void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    // OpenGL�R���e�L�X�g������ݒ�F�ԁA�΁A�A�A���t�@�A�[���A�X�e���V���A�}���`�T���v����
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// �p�b�P�[�W�}�l�[�W���[���g�p���Ă���Ƀp�b�P�[�W���C���X�g�[������ꍇ�́A
// don't modify or remove this function
// ���̊֐���ύX�܂��͍폜���Ȃ��ł�������
static int register_all_packages()
{
    //�p�b�P�[�W�}�l�[�W���̃t���O
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    // �f�B���N�^�[������������
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("SampleGame", cocos2d::Rect(0, 0, mediumResolutionSize.width, mediumResolutionSize.height));
#else
        glview = GLViewImpl::create("SampleGame");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    // �f�B�X�v���CFPS���I���ɂ���
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    // FPS��ݒ肵�܂��B������Ăяo���Ȃ��ꍇ�̃f�t�H���g�l��1.0 / 60�ł��B
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    //�f�U�C���̉𑜓x��ݒ肷��
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::SHOW_ALL);
    auto frameSize = glview->getFrameSize();
    
    director->setContentScaleFactor(MIN(largeResolutionSize.height / designResolutionSize.height, largeResolutionSize.width / designResolutionSize.width));

    //���̉��̃R�����g������Android�̏ꍇ�͕K�v�Ȃ�
    //IOS�͂悭�킩���Ă��Ȃ�

    // if the frame's height is larger than the height of medium size.
    // �t���[���̍��������^�̍������傫���ꍇ�B
    //if (frameSize.height > mediumResolutionSize.height)
    //{
    //    director->setContentScaleFactor(MIN(largeResolutionSize.height / designResolutionSize.height, largeResolutionSize.width / designResolutionSize.width));
    //}
    //// if the frame's height is larger than the height of small size.
    //// �t���[���̍������������T�C�Y�̍������傫���ꍇ�B
    //else if (frameSize.height > smallResolutionSize.height)
    //{
    //    director->setContentScaleFactor(MIN(mediumResolutionSize.height / designResolutionSize.height, mediumResolutionSize.width / designResolutionSize.width));
    //}
    //// if the frame's height is smaller than the height of medium size.
    ////�t���[���̍��������^�̍��������������ꍇ�B
    //else
    //{
    //    director->setContentScaleFactor(MIN(smallResolutionSize.height / designResolutionSize.height, smallResolutionSize.width / designResolutionSize.width));
    //}

    register_all_packages();

    // create a scene. it's an autorelease object
    // �V�[�����쐬���܂��B��������I�u�W�F�N�g�ł�
    auto scene = function_main::createScene();
    /*auto scene2 = DebugSystem::createScene();*/

    // run
    director->runWithScene(scene);
    //// run
    //director->runWithScene(scene2);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
// ���̊֐��́A�A�v�����A�N�e�B�u�łȂ��Ƃ��ɌĂяo����܂��B�d�b���󂯂�ƌĂяo����邱�Ƃɒ��ӂ��Ă��������B
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
// ���̊֐��́A�A�v�����ĂуA�N�e�B�u�ɂȂ����Ƃ��ɌĂяo����܂�
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
