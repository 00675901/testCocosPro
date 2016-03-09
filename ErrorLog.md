03-09 00:28:05.958 13095-13126/com.coin.cocos A/libc: Fatal signal 11 (SIGSEGV), code 1, fault addr 0x0 in tid 13126 (GLThread 3214)
********** Crash dump: 13882**********
Build fingerprint: 'samsung/h3gduosctc/hlte:5.0/LRX21V/N9009KEU2GOI1:user/release-keys'
pid: 13882, tid: 13901, name: GLThread 3234  >>> com.coin.cocos <<<
signal 11 (SIGSEGV), code 1 (SEGV_MAPERR), fault addr 0x0
Stack frame #00 pc 001179be  /data/app/com.coin.cocos-1/lib/arm/libcocos2dcpp.so (HelloWorld::init()+365): Routine HelloWorld::init() at /Users/ggyyer/Android_workspace/testCocosPro/proj.android-studio/app/jni/../../../Classes/HelloWorldScene.cpp:61 (discriminator 2)
Stack frame #01 pc 00117b11  /data/app/com.coin.cocos-1/lib/arm/libcocos2dcpp.so (HelloWorld::create()+52): Routine HelloWorld::create() at /Users/ggyyer/Android_workspace/testCocosPro/proj.android-studio/app/jni/../../../Classes/HelloWorldScene.h:17
Stack frame #02 pc 00117b4d  /data/app/com.coin.cocos-1/lib/arm/libcocos2dcpp.so (HelloWorld::createScene()+8): Routine HelloWorld::createScene() at /Users/ggyyer/Android_workspace/testCocosPro/proj.android-studio/app/jni/../../../Classes/HelloWorldScene.cpp:11
Stack frame #03 pc 001175fd  /data/app/com.coin.cocos-1/lib/arm/libcocos2dcpp.so (AppDelegate::applicationDidFinishLaunching()+212): Routine AppDelegate::applicationDidFinishLaunching() at /Users/ggyyer/Android_workspace/testCocosPro/proj.android-studio/app/jni/../../../Classes/AppDelegate.cpp:78 (discriminator 3)
Stack frame #04 pc 00117e43  /data/app/com.coin.cocos-1/lib/arm/libcocos2dcpp.so (cocos2d::Application::run()+6): Routine cocos2d::Application::run() at /Users/ggyyer/Android_workspace/testCocosPro/proj.android-studio/app/jni/../../../cocos2d/cocos/platform/android/CCApplication-android.cpp:68
Stack frame #05 pc 00118e0d  /data/app/com.coin.cocos-1/lib/arm/libcocos2dcpp.so (Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit+92): Routine Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit at /Users/ggyyer/Android_workspace/testCocosPro/proj.android-studio/app/jni/../../../cocos2d/cocos/platform/android/javaactivity-android.cpp:72
Stack frame #06 pc 0001be79  /data/dalvik-cache/arm/data@app@com.coin.cocos-1@base.apk@classes.dex

错误原因：需要加载的资源文件不存在android assets在项目中没有引入，导致需要加载的资源文件不存在
解决：把assets拷到项目目录下（proj.android-studio/app）,并在gradle中引入（assets.srcDir "assets"）
********** Crash dump: 13882 END**********