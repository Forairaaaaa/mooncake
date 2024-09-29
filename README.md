# Mooncake

适用于单片机的多 App 管理调度框架

- 结构化 App 生命周期设计
- 多 App 管理
- 可扩展的行为管理

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

App 的生命周期可参考[图表](https://github.com/Forairaaaaa/mooncake?tab=readme-ov-file#appability)

## API

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

App 的所有生命周期回调都会集中在 Mooncake 的  `update()` 方法中触发：

```cpp
/**
 * @brief 更新 Mooncake，刷新 App 及 Extension 状态，触发生命周期回调
 *
 */
void update();
```

一般可以丢进 `while` 里

### 线程安全

所有 API 都为线程 **不安全**，Mooncake 只提供管理器和一个集中的 `update()` 调度接口

如果需要线程安全，确保 Mooncake 在临界区：

```cpp
// 一边
while (1) {
    mutex.lock();
    mc.update();
    mutex.unlock();
}

// 另一边
mutex.lock();
mc.openApp(114514);
mutex.unlock();
```

## Ability 模型

这概念抄[鸿蒙](https://docs.openharmony.cn/pages/v4.1/zh-cn/application-dev/application-models/abilitykit-overview.md)的，有点像超级青春版

**Ability** 为一个应用的行为抽象，每个 Ability 都会有最基础的 **创建、运行、销毁** 三个状态

基于这三个状态，可以派生出不同生命周期的 Ability 类型

```mermaid
classDiagram
    AbilityBase <|-- BasicAbility
    AbilityBase <|-- UIAbility
    AbilityBase <|-- WorkerAbility
    AbilityBase <|-- AppAbility
    class AbilityBase{
        baseCreate()
        baseUpdate()
        baseDestroy()
    }
    class BasicAbility{
        onCreate()
        onRunning()
        onDestroy()
    }
    class UIAbility{
        onCreate()
        onShow()
        onForeground()
        onBackground()
        onHide()
        onDestroy()
    }
    class WorkerAbility{
        onCreate()
        onResume()
        onRunning()
       	onPause()
        onDestroy()
    }
    class AppAbility{
        onCreate()
        onOpen()
        onRunning()
        onSleeping()
        onClose()
        onDestroy()
    }
```

### BasicAbility

 `BasicAbility` 类型生命周期：

```mermaid
graph TD;
    onCreate-->onRunning;
    onRunning-- destroy -->onDestroy;
    
```

提供了最简单的三段式生命周期，可以把 `onCreate` 比作 **Arduino** 的 `setup`，`onRunning` 比作 `loop` 

### UIAbility

 `UIAbility` 类型生命周期：

```mermaid
graph TD;
    onCreate-->onForeground;
    onForeground-- hide -->onHide;
    onHide-->onBackground;
    onBackground-- show -->onShow;
    onShow-->onForeground;
    onForeground-- destroy -->onDestroy;
    onBackground-- destroy -->onDestroy;
    
```

扩展出前后台概念，由 `hide` 和 `show` 接口切换状态，适合需要前后台概念的 UI 行为

### WorkerAbility

 `WorkerAbility` 类型生命周期：

```mermaid
graph TD;
    onCreate-->onRunning;
    onRunning-- pause -->暂停;
    暂停-- resume -->onRunning;
    onRunning-- destroy -->onDestroy;
    暂停-- destroy -->onDestroy;
    
```

扩展出运行和暂停行为，由 `pause` 和 `resume` 接口切换状态，适合后台运行的行为，比如数据监听和事件转发

### AppAbility

 `AppAbility` 类型生命周期：

```mermaid
graph TD;
    onCreate-->onSleeping;
    onOpen-->onRunning;
    onRunning-- close -->onClose;
    onClose-->onSleeping;
    onSleeping-- open -->onOpen;
    onRunning-- destroy -->onDestroy;
    onSleeping-- destroy -->onDestroy;
    
```

扩展出打开和关闭行为，由 `open` 和 `close` 接口切换状态

提供 App 信息和接口：

```cpp
struct AppInfo_t {
    std::string name;
    void* icon = nullptr;
    void* userData = nullptr;
};

const AppInfo_t& getAppInfo();
AppInfo_t& setAppInfo();
```

适合有 App 信息需求的多应用行为

## Mooncake

**Mooncake** 内部提供两个 **Ability** 管理器：

```cpp
std::unique_ptr<AbilityManager> _app_ability_manager;
std::unique_ptr<AbilityManager> _extension_ability_manager;
```

- **App Ability 管理器** 只用于管理  `AppAbility` 类型，一个 `AppAbility`  对于 Mooncake 框架来说就是一个 **App** ，Mooncake 提供了针对性的接口封装

- **Extension Ability 管理器** 可以用于管理任意 Ability 类型，比如需要一些 `WorkerAbility` 来监听数据、`UIAbility` 渲染图像、自己派生的 `CustomAbility` 等都可以丢到这里统一由 Mooncake 管理

比如：

```cpp
// 创建 Mooncake
Mooncake mc;

// 安装 App
printf(">> install app\n");
mc.installApp(std::make_unique<MyApp>());
// 输出：
// >> install app
// [app] on construct

// 安装扩展
printf(">> install extensions\n");
mc.ExtensionManager()->createAbility(std::make_unique<MyWorker>());
mc.ExtensionManager()->createAbility(std::make_unique<MyUI>());
// 输出：
// >> install extensions
// [worker] on construct
// [ui] on construct

// 更新 Mooncake
printf(">> update mooncake\n");
for (int i = 0; i < 3; i++) {
    mc.update();
}
// 输出：
// >> update mooncake
// [worker] on running
// [ui] on foreground
// [app] on running
// [worker] on running
// [ui] on foreground
// [app] on running
// [worker] on running
// [ui] on foreground
```

### AbilityManager

**Ability 管理器** 负责 Ability 实例的创建、储存和销毁，以及原始生命周期的调度触发

每个 Ability 实例会分配一个 **Ability ID**，方便查找索引：

```cpp
/**
 * @brief 创建 Ability，返回 Ability ID
 *
 * @param ability
 * @return int
 */
int createAbility(std::unique_ptr<AbilityBase> ability);

/**
 * @brief 销毁指定 ID 的 Ability
 *
 * @param abilityID
 * @return true
 * @return false
 */
bool destroyAbility(int abilityID);
```

**Ability ID** 并不是绝对唯一的，当一个 Ability 被销毁时，对应的 ID 会被 **回收**，等待分配到新的 Ability

AbilityManager 还提供针对性的 Ability 操作接口，简化 Ability 状态切换，避免直接的实例操作：

```cpp
/* -------------------------------------------------------------------------- */
/*                            Ability API Wrapping                            */
/* -------------------------------------------------------------------------- */
// 对外暴露针对性的 Ability 操作接口

bool showUIAbility(int abilityID);
bool hideUIAbility(int abilityID);
UIAbility::State_t getUIAbilityCurrentState(int abilityID);

bool pauseWorkerAbility(int abilityID);
bool resumeWorkerAbility(int abilityID);
WorkerAbility::State_t getWorkerAbilityCurrentState(int abilityID);

bool openAppAbility(int abilityID);
bool closeAppAbility(int abilityID);
AppAbility::AppInfo_t getAppAbilityAppInfo(int abilityID);
AppAbility::State_t getAppAbilityCurrentState(int abilityID);
```

