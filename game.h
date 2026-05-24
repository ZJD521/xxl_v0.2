#include "drivers.h"
#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
#include "stdlib.h"

//方块的行数，列数，边长
#define GRID_COLS 8   
#define GRID_ROWS 7
#define CELL_LENG 70 

//方块图片大小
#define CELL_SIZE 70*70*3

//场地的左上角坐标
#define FIELD_X 232
#define FIELD_Y 100

#define BG_W 256  //背景原始大小
#define BG_H 150
#define BG_SIZE (BG_W * BG_H * 3)//背景图片大小

#define BTN_W 64  //按钮原始大小
#define BTN_H 36
#define BTN_SIZE (BTN_W*BTN_H*3) //按钮图片大小

#define duration 300   //默认动画时长




typedef enum{          //主题种类
  DEFAULT,
	ICE
}bg_theme;

typedef enum{          
  RED,   //颜色标记
	YELLOW,
	GREEN,
	BLUE,
	PURPLE,
	DEL   //删除标记
}cell_type;

typedef struct {       //背景图片，背景主题
	lv_obj_t*img;
  bg_theme theme;
}bac;

typedef struct {	//方块图片，标签，坐标
	lv_obj_t*img;
  cell_type type;
	uint8_t x;
  uint8_t y;
}sqr;

typedef struct {  //用于打包交换的两个方块
  sqr* cell_a;
	sqr* cell_b;
}ani;

typedef enum {   //当前状态
	NORMAL,
  SWAPPING,
	FALLING
}state;

// 全局新增
#ifndef GAME_H
#define GAME_H

// 道具枚举
typedef enum {
    ITEM_NONE,
    ITEM_BOMB,
    ITEM_ROW_CLEAR,
    ITEM_COL_CLEAR
} ItemType;

extern ItemType cur_use_item;

#endif


//相关函数


//初始化
void game_init(void);
void game_level_data_init(void);

//死局

bool deadlock_det();

void game_deadlock();

//加载;


void game_bg_load(lv_obj_t * scr);  //加载默认背景

void game_sqr_field_init(lv_obj_t* scr);   //加载游戏场，创建方块对象

void game_sqr_src_load(void);        //导入方块皮肤

void game_btn_start_load(void);    //加载开始按钮

void game_btn_choose_load(void);   //加载选项按钮

void game_btn_mode_load(void);   //选择模式

void game_btn_time_load(void);  //选择时间限制

void game_btn_step_load(void);  //选择步数限制

void game_btn_theme_load(void); //选择主题

void game_btn_theme_default_load(void);     //加载动物主题按钮

void game_btn_theme_ice_load(void);         //加载蔬果主题按钮 

void game_btn_exit_load(lv_obj_t*scr);        //加载返回按钮

void game_btn_level_load(void);//关卡选择按钮

void game_btn_item_bomb_load(void);

void game_btn_item_row_load(void);

void game_btn_item_col_load(void); //道具按钮加载

cell_type safe_type(uint8_t x, uint8_t y,cell_type t);  //返回不与周围相同的方块类型

void game_score_label_create(lv_obj_t *scr);  //创建分数标签

void game_init_data(void);  //数据初始化

void game_end_show(void);  //游戏结束

void game_cleanup_all(void);  //清理本局资源




//交换

void cell_swap_exec(sqr * cell_1 , sqr * cell_2);   //交换图片位置的执行函数

void game_init_coord_map(void);    //初始化索引

void swap_cell_coordinates(uint8_t i1, uint8_t j1, uint8_t i2, uint8_t j2);  //交换索引

void update_coord_map_for_single_cell(sqr* cell, uint8_t old_x, uint8_t old_y);  //更新单个方块坐标索引


// 消除

void mark_match(int x, int y, cell_type t);        //标记周围可消除的方块

uint8_t game_check_clear(void);  //消除检测

void game_do_clear(lv_timer_t* timer);    //消除执行

void clear_coord_map_at(uint8_t x, uint8_t y);    //清除单个索引




//下落

void game_init_fall_system(void);     //初始化下落系统

void game_fall_stop_all(void);      //停止下落链（局间清理用）

void game_fall_all(void);   //下落函数

void game_fall_one(sqr* cell, uint8_t target_y);  //下落单个方块

void fall_complete_check(lv_timer_t* timer);  //全部下落完成检测

//重填

void game_refill(lv_timer_t* timer);  //重填所有空方块

void game_create_new_cell(uint8_t x, uint8_t y);  //生成单个重填方块

//道具
void bomb_effect(uint8_t x,uint8_t y);//炸弹生效

void row_clear_effect(uint8_t row);//行消
	
void col_clear_effect(uint8_t col);//列消


//回调函数

void btn_start_cb(lv_event_t*e); //“开始游戏”按钮

void btn_choose_cb(lv_event_t*e);  //“选项”按钮

void btn_mode_cb(lv_event_t*e); //“模式”按钮

void btn_time_cb(lv_event_t*e); //“时间模式”按钮

void btn_step_cb(lv_event_t*e); //“步数模式”按钮

void btn_theme_cb(lv_event_t*e); //“主题”按钮

void btn_def_cb(lv_event_t*e);   //“动物主题”按钮

void btn_ice_cb(lv_event_t*e);   //“蔬果主题”按钮

void btn_exit_cb(lv_event_t*e); //返回按钮

void btn_level_cb(lv_event_t*e);//选择关卡按钮

void screen_cb(lv_event_t*e);    //游戏屏幕加载回调

void cell_cb(lv_event_t*e);      //单个方块回调

void swap_ready_cb(lv_anim_t *a);     //交换动画完成的回调

void fall_anim_ready_cb(lv_anim_t* a);   //下落动画完成回调

void game_timer_cb(lv_timer_t* timer);  //定时器回调

void tool_check_cb(lv_timer_t* timer);//道具可用状态

//全局变量

extern lv_obj_t * scr_menu; //菜单界面

extern lv_obj_t * scr_game; //游戏界面

extern lv_img_dsc_t start_struct;    //开始按钮                    
extern lv_obj_t * btn_start ;
extern uint8_t *start_buffer;

extern lv_img_dsc_t choose_struct;    //选择按钮                      
extern lv_obj_t * btn_choose ;
extern uint8_t *choose_buffer;

extern lv_img_dsc_t def_struct;    //动物主题按钮                    
extern lv_obj_t * btn_def ;
extern uint8_t *def_buffer;

extern lv_img_dsc_t ice_struct;    //蔬果主题按钮                 
extern lv_obj_t * btn_ice ;
extern uint8_t *ice_buffer;

extern bac bg;                    //背景结构体
extern lv_img_dsc_t bg_struct;            
extern uint8_t *bg_buffer;   

extern uint8_t *cell_buffer[5];   //方块图片数组

extern lv_img_dsc_t cell_struct[5];    //方块图片数据结构体      

extern sqr* coord_map[GRID_COLS][GRID_ROWS];//坐标-方块查找索引

extern state status;         //游戏状态

extern sqr cell[GRID_COLS][GRID_ROWS];  //方块图片数组
 
extern lv_obj_t *frame[GRID_COLS][GRID_ROWS];  //框架数组



extern uint16_t game_score; // 当前得分
extern uint16_t high_score;    // 开机内最高得分
extern uint16_t game_time;     // 剩余时间
extern uint8_t  game_over;     // 游戏是否结束标志
extern uint16_t game_step; //剩余步数
extern uint16_t game_goal;  //目标分数
extern uint16_t game_level;

extern lv_obj_t *label_score;  //得分标签
extern lv_obj_t *label_time;   //时间标签
extern lv_obj_t *label_high;  //最高分标签
extern lv_obj_t *label_step;  //步数标签
extern lv_obj_t *label_goal;   //目标分数标签

extern lv_obj_t *game_end_bg;
extern lv_obj_t *game_end_title;
extern lv_obj_t *game_end_score;
extern lv_obj_t *btn_back_main; //弹窗

extern lv_obj_t* btn_item_bomb;
extern lv_obj_t *btn_item_row;
extern lv_obj_t *btn_item_col; //道具按钮

extern uint8_t item_bomb_used ;
extern uint8_t item_row_used  ;
extern uint8_t item_col_used  ;//道具状态
