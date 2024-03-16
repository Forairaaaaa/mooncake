# Mooncake

适用于单片机的多 App 生命周期调度器，简化启动器设计，提高复用

A light weight multiple apps' life cycle dispatcher, simplify app launcher designing and app code reusing

------

### 目的：

- 将应用抽象成多个有序的[生命周期](https://github.com/Forairaaaaa/mooncake/blob/main/src/app/app.h#L81) （`AppBase`）
- 将应用的静态资源、创建销毁抽象成[工厂](https://github.com/Forairaaaaa/mooncake/blob/main/src/app/app.h#L20) （`AppPacker`）
- 提供内外 API 控制应用生命周期
- 提供[调度器](https://github.com/Forairaaaaa/mooncake/blob/main/src/app/app_manager.cpp#L161)，根据应用状态，调度生命周期钩子函数 （`Mooncake`）

### TODO：
- 删掉没用的东西
- 也许会抛弃工厂模式

Monica 项目请切换 [monica](https://github.com/Forairaaaaa/mooncake/tree/monica) 分支

![](https://github.com/Forairaaaaa/mooncake/blob/main/pics/note_shit.jpg?raw=true)
