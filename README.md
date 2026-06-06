1. 下载全部源码文件
首先，获取项目所需的全部核心源代码文件。

game.h：头文件，定义了所有数据结构、枚举类型、函数声明及全局常量。
main.c：主程序入口，负责系统初始化和LVGL图形库的启动。
game_bg.c：背景加载模块，实现从SD卡读取背景图片的功能。
game_btns_load.c 和 game_btns_cb.c：按钮创建与事件回调处理。
game_cell_cb.c：方块滑动交换的核心逻辑。
game_clear.c：消除检测与执行算法。
game_fall.c：方块下落与重填系统的实现。
game_level.c：关卡数据与死局检测。
game_score.c：分数管理、计时器与游戏结束逻辑。
game_sqr_check.c 和 game_sqr_src.c：游戏棋盘初始化与方块皮肤加载。
game_tool.c：道具（炸弹、行列清除）功能实现。
drivers.h 及相关驱动文件：底层硬件抽象层（HAL）接口。
请确保以上所有.c和.h文件均已下载并置于您的项目工作目录中。

2. 将生成的.bin文件部署至SD卡
bg_default.bin：默认主题背景图片。
bg_theme.bin：夏日主题背景图片。
default_red.bin, default_yellow.bin, default_green.bin, default_blue.bin, default_purple.bin：默认主题下的五种方块皮肤。
theme_red.bin, theme_yellow.bin, theme_green.bin, theme_blue.bin, theme_purple.bin：夏日主题下的五种方块皮肤。
score_1.bin 至 score_5.bin：用于存储五个关卡的最高分记录。
