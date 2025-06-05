# cocos2d-x-card-game

## 1. 项目简介

本项目是一个基于 Cocos2d-x 3.17 引擎开发的卡牌游戏 Demo，适用于游戏开发实习岗位的技术评估。项目实现了基本的卡牌游戏逻辑、界面交互与动画效果，支持在 Windows 平台上通过 Visual Studio 2022 进行编译和调试。

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

## 4. 关卡配置说明

项目关卡配置文件位于项目根目录下的 `Resources\res\level` 文件夹内，采用 JSON 格式。你可以通过修改这些 JSON 文件，自定义桌面部分卡牌、手牌的花色、点数、位置等内容。

### 配置文件格式示例

```json
{
    "Playfield": [
        {
            "CardFace": 12,
            "CardSuit": 0,
            "Position": {"x": 250, "y": 1500}
        },
        {
            "CardFace": 2,
            "CardSuit": 0,
            "Position": {"x": 300, "y": 1300}
        },
        {
            "CardFace": 2,
            "CardSuit": 1,
            "Position": {"x": 350, "y": 1100}
        },
        {
            "CardFace": 2,
            "CardSuit": 0,
            "Position": {"x": 850, "y": 1500}
        },
        {
            "CardFace": 2,
            "CardSuit": 0,
            "Position": {"x": 800, "y": 1300}
        },
        { 
            "CardFace": 1,
            "CardSuit": 3,
            "Position": {"x": 750, "y": 1100}
        }
    ],
    "Stack": [
        {
            "CardFace": 2,
            "CardSuit": 0,
            "Position": {"x": 0, "y": 0}
        },
        {
            "CardFace": 0,
            "CardSuit": 2,
            "Position": {"x": 0, "y": 0}
        },
        {
            "CardFace": 3,
            "CardSuit": 0,
            "Position": {"x": 0, "y": 0}
        }
    ]
}
```
只需根据上述格式设置桌面部分卡牌与手牌的花色、点数与位置即可。

---

## 5. 项目打开与编译运行

1. **打开工程**  
   使用 Visual Studio 2022，打开项目根目录下 `proj.win32` 文件夹中的 `CardGame.sln` 解决方案文件。

2. **设置启动项目**  
   在解决方案资源管理器中，右击 `CardGame` 项目，选择“设为启动项目”。

3. **运行项目**  
   选择“本地 Windows 调试器”，点击运行即可编译并启动卡牌游戏 Demo。

---

## 6. 程序开发文档

程序开发文档位于项目根目录下的 `docs` 文件夹中，供开发与二次开发参考。

---

## 7. 常见问题

- 如遇第三方依赖缺失、链接错误等问题，优先检查 external 文件夹是否已正确替换到 `cocos2d/external` 目录。
- 确保已在环境变量配置好 Python 2.7（通常用于 Cocos2d-x 工具链）。

---

## 8. 联系方式
wechat : loyaltender
QQ : 3938314729
tel : 15554178691
