# cocos2d-x-card-game

## 1. 项目简介

本项目是一个基于 Cocos2d-x 3.17 引擎开发的卡牌游戏 Demo，适用于游戏开发实习岗位的技术评估。项目实现了基本的卡牌游戏逻辑、界面交互与动画效果，支持在 Windows 平台上通过 Visual Studio 2022 进行编译和调试。源码结构清晰，便于学习和功能扩展。

---

## 2. 项目环境

- **引擎版本**：Cocos2d-x 3.17  
- **开发工具**：Visual Studio 2022  
- **脚本依赖**：Python 2.7  
- **支持平台**：Windows（VS2022工程，其他平台需自行适配）

---

## 3. 拉取与依赖处理

### 拉取项目到本地

请在命令行中执行：

```sh
git clone https://github.com/KirisameMarisa0602/cocos2d-x-card-game.git
```

### 重要依赖操作（external 文件夹处理）

**拉取项目后，请务必进行以下操作：**

1. 将项目根目录下的 `external` 文件夹**剪切**（或移动）到 `cocos2d` 文件夹下，**替换原有的 `cocos2d/external` 文件夹**。

   - 操作流程举例：
     - 剪切：`cocos2d-x-card-game/external`
     - 粘贴并替换至：`cocos2d-x-card-game/cocos2d/external`

2. 此步骤可确保项目依赖的第三方库完整且路径正确，否则可能导致编译时缺少依赖报错。

---

## 4. 项目打开与编译运行

1. **打开工程**  
   使用 Visual Studio 2022，打开项目根目录下 `proj.win32` 文件夹中的 `CardGame.sln` 解决方案文件。

2. **设置启动项目**  
   在解决方案资源管理器中，右击 `CardGame` 项目，选择“设为启动项目”。

3. **运行项目**  
   选择“本地 Windows 调试器”，点击运行即可编译并启动卡牌游戏 Demo。

---

## 5. 常见问题

- 如遇第三方依赖缺失、链接错误等问题，优先检查 external 文件夹是否已正确替换到 `cocos2d/external` 目录。
- 确保已在环境变量配置好 Python 2.7（通常用于 Cocos2d-x 工具链）。

---

## 6. 联系方式

Wechat：loyaltender
QQ：3938314729
电话：15554178691
