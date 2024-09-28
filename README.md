# Mooncake

使用生命周期来结构化 App 设计，提供 App 安装、打开、关闭等统一管理接口

------

简单使用：

```cpp
// 派生一个 App
class MyApp : public AppAbility {
public:
    MyApp()
    {
        // 配置 App 信息
        setAppInfo().name = "凤爪";

        printf("[%s] on construct\n", getAppInfo().name.c_str());
    }

    // 重载生命周期回调函数
    void onOpen() override
    {
        printf("[%s] on open\n", getAppInfo().name.c_str());
    }
    void onRunning() override
    {
        printf("[%s] on running\n", getAppInfo().name.c_str());
    }

    // ...
    // void onCreate() override {}
    // void onSleeping() override {}
    // void onClose() override {}
    // void onDestroy() override {}
};

Mooncake mc;

// 安装 App
printf(">> install app\n");
auto my_app_id = mc.installApp(std::make_unique<MyApp>());
// 输出：
// >> install app
// [凤爪] on construct

// 打开 App
mc.openApp(my_app_id);

// 更新 Mooncake
printf(">> update mooncake\n");
for (int i = 0; i < 3; i++) {
    mc.update();
}
// 输出：
// >> update mooncake
// [凤爪] on open
// [凤爪] on running
// [凤爪] on running
```

App 的所有生命周期回调都会集中在 `update()` 方法中触发：

```cpp
/**
 * @brief 更新 Mooncake，刷新 App 及 Extension 状态，触发生命周期回调
 *
 */
void update();
```

App 管理接口：

```cpp
/**
 * @brief 安装 App，返回 App ID
 *
 * @param appAbility
 * @return int
 */
int installApp(std::unique_ptr<AppAbility> appAbility);

/**
 * @brief 卸载指定 ID 的 App
 *
 * @param appID
 * @return true
 * @return false
 */
bool uninstallApp(int appID);

/**
 * @brief 卸载所有 App
 *
 */
void uninstallAllApps();

/**
 * @brief 打开指定 ID 的 App
 *
 * @param appID
 * @return true
 * @return false
 */
bool openApp(int appID);

/**
 * @brief 关闭指定 ID 的 App
 *
 * @param appID
 * @return true
 * @return false
 */
bool closeApp(int appID);

/**
 * @brief 检查 App 是否存在
 *
 * @param appID
 * @return true
 * @return false
 */
bool isAppExist(int appID);

/**
 * @brief 获取当前 App 数量
 *
 * @return std::size_t
 */
std::size_t getAppNum();

/**
 * @brief 获取指定 ID 的 App 信息
 *
 * @param appID
 * @return AppAbility::AppInfo_t
 */
AppAbility::AppInfo_t getAppInfo(int appID);

/**
 * @brief 获取所有 App 的 App 信息
 *
 * @return std::vector<AppAbility::AppInfo_t>
 */
std::vector<AppAbility::AppInfo_t> getAllAppInfo();

/**
 * @brief 获取指定 ID 的 App 当前生命周期状态
 *
 * @param appID
 * @return AppAbility::State_t
 */
AppAbility::State_t getAppCurrentState(int appID);
```

## Ability 模型

