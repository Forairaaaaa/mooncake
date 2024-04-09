# Mooncake

适用于单片机的多 App 生命周期调度框架，使用工厂模式以结构化 App 设计、简化 App 启动器设计、提高复用

A light weight multiple apps' life cycle dispatcher framework, structure app design, simplify app launcher designing and code reusing

------

### 目的：

- 将应用抽象成多个有序的[生命周期](https://github.com/Forairaaaaa/mooncake/blob/main/src/app/app.h#L146) （`AppBase`）
- 将应用的静态资源、创建销毁抽象成[工厂](https://github.com/Forairaaaaa/mooncake/blob/main/src/app/app.h#L15) （`AppPacker`）
- 提供内外 [API](https://github.com/Forairaaaaa/mooncake/blob/main/src/app/app.h#L119) 控制应用生命周期
- 提供[调度器](https://github.com/Forairaaaaa/mooncake/blob/main/src/app/app_manager.h#L19)，根据应用状态，调度生命周期钩子函数 （`Mooncake`）

### 示例

```cpp
#include <mooncake.h>

using namespace MOONCAKE;

/* -------------------------------------------------------------------------- */
/*                          Create your app like this                         */
/* -------------------------------------------------------------------------- */
// 重载 App 生命周期回调函数
class MyApp : public APP_BASE
{
    // Like setup()
    void onResume() override { spdlog::info("hi"); }

    // Like loop()
    void onRunning() override { spdlog::info("6"); }
};

// 重载 App 工厂
class MyAppPacker : public APP_PACKER_BASE
{
    void* newApp() override { return new MyApp; }
    void deleteApp(void* app) override { delete (MyApp*)app; }
};

int main()
{
    // 创建并初始化 Mooncake
    // Create mooncake and init
    Mooncake mooncake;
    mooncake.init();

    // 安装 App (工厂)
    // Install your app by app packer
    // so that mooncake konws how to create and destroy your app
    mooncake.installApp(new MyAppPacker);
	
    // 安装 App 后, 可以在已安装列表里获取 App (工厂)
    // After app installed, we can get the packer pointer back from the installed list
    auto my_app_packer = mooncake.getInstalledAppList()[0];
	
    // 创建 App 实例, 并开始 App
    // Tell mooncake to create an instance of your app, and start it
    mooncake.createAndStartApp(my_app_packer);
	
    // 把框架丢进循环里, 所有 App 的回调都会在 update 方法里被调用
    // Keep framework running
    for (int i = 0; i < 114514; i++)
        mooncake.update();
	
    // Mooncake 被销毁时会主动去释放所有的 App 实例和工厂
    // Mooncake will help you destroy every app and packers' instance
    return 0;
}
```

### Monica 项目请切换 [monica](https://github.com/Forairaaaaa/mooncake/tree/monica) 分支

![](https://github.com/Forairaaaaa/mooncake/blob/main/pics/note_shit.jpg?raw=true)
