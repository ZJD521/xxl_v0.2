#include "drivers.h"
#include "lvgl.h"
#include "game.h"

extern lv_obj_t * scr_menu; 
extern lv_obj_t * scr_game;

extern lv_obj_t * btn_level[5];

extern void btn_start_cb(lv_event_t*e);
extern void btn_choose_cb(lv_event_t*e);
extern void btn_def_cb(lv_event_t*e);
extern void btn_ice_cb(lv_event_t*e);
extern void btn_item_bomb_cb(lv_event_t *e);
extern void btn_item_row_cb(lv_event_t *e);
extern void btn_item_col_cb(lv_event_t *e);

   //开始按钮定义                      
lv_obj_t * btn_start ;

  //选择按钮定义                      
lv_obj_t * btn_choose ;

  //动物主题按钮定义                      
lv_obj_t * btn_def ;

  //蔬果主题按钮定义                      
lv_obj_t * btn_ice ;

//返回按钮定义
lv_obj_t* btn_exit;
//模式按钮定义
lv_obj_t* btn_mode;
//时间按钮定义
lv_obj_t* btn_time;
//步数按钮定义
lv_obj_t* btn_step;
//主题按钮定义
lv_obj_t* btn_theme;
//仨道具按钮定义
lv_obj_t* btn_item_bomb;
lv_obj_t *btn_item_row;
lv_obj_t *btn_item_col;
lv_obj_t *btn_clear_score;
lv_obj_t *btn_help;

void game_btn_start_load(){        //加载开始按钮
	
    btn_start = lv_btn_create(scr_menu);  //在菜单界面创建按钮
	  lv_obj_set_size(btn_start,256,100);  //按钮大小
	  lv_obj_align(btn_start,LV_ALIGN_CENTER,-200,0); //右移200
	  lv_obj_add_event_cb(btn_start,btn_start_cb,LV_EVENT_CLICKED,NULL);  //绑定回调（clicked）会执行
	  lv_obj_t *lb_start=lv_label_create(btn_start);  //加个标签
	  lv_label_set_text(lb_start,"START");  //id
    lv_obj_set_style_bg_color(btn_start, lv_color_hex(0xFFC107), LV_PART_MAIN);//按钮颜色
    lv_obj_set_style_radius(btn_start, 10, LV_PART_MAIN);  //设置按钮圆角（半径10）
    lv_obj_set_style_bg_color(btn_start, lv_color_hex(0xCC8400), LV_PART_MAIN | LV_STATE_PRESSED);  //设置按钮被按下时的颜色
	  lv_obj_set_style_text_color(btn_start, lv_color_hex(0xFFFFFF), LV_PART_MAIN);//字体颜色
	  lv_obj_center(lb_start); //文字在按钮中居中
    lv_obj_set_style_text_font(lb_start , &lv_font_montserrat_40, 0);  //字体大小40
	lv_obj_set_style_shadow_width(btn_start,10,0);
	lv_obj_set_style_shadow_spread(btn_start,3,0);
	lv_obj_set_style_shadow_color(btn_start,lv_color_hex(0x000000),0);
	lv_obj_set_style_bg_grad_dir(btn_start, LV_GRAD_DIR_VER, 0); // 第三个参数 0 表示应用到主要部分 (main part)
	lv_obj_set_style_bg_grad_color(btn_start, lv_color_hex(0xFF5220), 0); // 金色
	lv_obj_set_style_bg_main_stop(btn_start, 0, 0);   // 主色从 0 开始
	lv_obj_set_style_bg_grad_stop(btn_start, 255, 0); // 渐变色在 255 结束




}

void game_btn_choose_load(){        //加载设置按钮
	  btn_choose = lv_btn_create(scr_menu);
	  lv_obj_set_size(btn_choose,256,100);
	  lv_obj_align(btn_choose,LV_ALIGN_CENTER,200,0); //左移200
	  lv_obj_add_event_cb(btn_choose,btn_choose_cb,LV_EVENT_CLICKED,NULL);
	  lv_obj_t *lb_choose=lv_label_create(btn_choose);
	  lv_label_set_text(lb_choose,"OPTION");
    lv_obj_set_style_bg_color(btn_choose, lv_color_hex(0xFFC107), LV_PART_MAIN);
    lv_obj_set_style_radius(btn_choose, 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_choose, lv_color_hex(0xCC8400), LV_PART_MAIN | LV_STATE_PRESSED);
	  lv_obj_set_style_text_color(btn_choose, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	  lv_obj_center(lb_choose);
    lv_obj_set_style_text_font(lb_choose , &lv_font_montserrat_40, 0);
	lv_obj_set_style_shadow_width(btn_choose,10,0);
	lv_obj_set_style_shadow_spread(btn_choose,3,0);
	lv_obj_set_style_shadow_color(btn_choose,lv_color_hex(0x000000),0);
	lv_obj_set_style_bg_grad_dir(btn_choose, LV_GRAD_DIR_VER, 0); // 第三个参数 0 表示应用到主要部分 (main part)
	lv_obj_set_style_bg_grad_color(btn_choose, lv_color_hex(0xFF5220), 0); // 金色
	lv_obj_set_style_bg_main_stop(btn_choose, 0, 0);   // 主色从 0 开始
	lv_obj_set_style_bg_grad_stop(btn_choose, 255, 0); // 渐变色在 255 结束

}
void game_btn_theme_default_load(){        //加载默认主题按钮
    btn_def = lv_btn_create(scr_menu);
	  lv_obj_set_size(btn_def,256,100);
	  lv_obj_align(btn_def,LV_ALIGN_CENTER,0,0); 
	  lv_obj_add_event_cb(btn_def,btn_def_cb,LV_EVENT_CLICKED,NULL);
	  lv_obj_t *lb_def=lv_label_create(btn_def);
	  lv_label_set_text(lb_def,"DEFAULT\n  THEME");
    lv_obj_set_style_bg_color(btn_def, lv_color_hex(0x3742FA), LV_PART_MAIN);
    lv_obj_set_style_radius(btn_def, 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_def, lv_color_hex(0x1927D0), LV_PART_MAIN | LV_STATE_PRESSED);
	  lv_obj_set_style_text_color(btn_def, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	  lv_obj_center(lb_def);
    lv_obj_set_style_text_font(lb_def , &lv_font_montserrat_40, 0);
 		lv_obj_add_flag(btn_def,LV_OBJ_FLAG_HIDDEN);  //开始的时候隐藏
		 lv_obj_set_style_shadow_width(btn_def,10,0);
		 lv_obj_set_style_shadow_spread(btn_def,3,0);
		 lv_obj_set_style_shadow_color(btn_def,lv_color_hex(0x000000),0);
		 lv_obj_set_style_bg_grad_dir(btn_def, LV_GRAD_DIR_VER, 0); // 第三个参数 0 表示应用到主要部分 (main part)
		 lv_obj_set_style_bg_grad_color(btn_def, lv_color_hex(0x20B2FF), 0); //蓝色
		 lv_obj_set_style_bg_main_stop(btn_def, 0, 0);   // 主色从 0 开始
		 lv_obj_set_style_bg_grad_stop(btn_def, 255, 0); // 渐变色在 255 结束
}
void game_btn_theme_ice_load(){        //加载夏日主题按钮
    btn_ice = lv_btn_create(scr_menu);
	  lv_obj_set_size(btn_ice,256,100);
  	lv_obj_align(btn_ice,LV_ALIGN_CENTER,0,-150); //上移150
	  lv_obj_add_event_cb(btn_ice,btn_ice_cb,LV_EVENT_CLICKED,NULL);
	  lv_obj_t *lb_ice=lv_label_create(btn_ice);
	  lv_label_set_text(lb_ice,"SUMMER\n  THEME");
    lv_obj_set_style_bg_color(btn_ice, lv_color_hex(0x20B6B6), LV_PART_MAIN);
    lv_obj_set_style_radius(btn_ice, 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_ice, lv_color_hex(0x0A9E9E), LV_PART_MAIN | LV_STATE_PRESSED);
	  lv_obj_set_style_text_color(btn_ice, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	  lv_obj_center(lb_ice);
    lv_obj_set_style_text_font(lb_ice , &lv_font_montserrat_40, 0);
		lv_obj_add_flag(btn_ice,LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_style_shadow_width(btn_ice,10,0);
		lv_obj_set_style_shadow_spread(btn_ice,3,0);
		lv_obj_set_style_shadow_color(btn_ice,lv_color_hex(0x000000),0);
		lv_obj_set_style_bg_grad_dir(btn_ice, LV_GRAD_DIR_VER, 0); // 第三个参数 0 表示应用到主要部分 (main part)
		lv_obj_set_style_bg_grad_color(btn_ice, lv_color_hex(0x20E6E6), 0);//青色 
		lv_obj_set_style_bg_main_stop(btn_ice, 0, 0);   // 主色从 0 开始
		lv_obj_set_style_bg_grad_stop(btn_ice, 255, 0); // 渐变色在 255 结束
}
void game_btn_exit_load(lv_obj_t*scr){        //加载返回按钮
    btn_exit = lv_btn_create(scr);
	if(scr==scr_menu){
		lv_obj_set_size(btn_exit,256,100);
  	lv_obj_align(btn_exit,LV_ALIGN_CENTER,0,150); //下移150
	}
	else if(scr==scr_game){
		lv_obj_set_size(btn_exit,128,50);
		lv_obj_align(btn_exit, LV_ALIGN_BOTTOM_RIGHT, -10, -40); 
	}
	  lv_obj_add_event_cb(btn_exit,btn_exit_cb,LV_EVENT_CLICKED,NULL);
	  lv_obj_t *lb_exit=lv_label_create(btn_exit);
	  lv_label_set_text(lb_exit,"EXIT");
    lv_obj_set_style_bg_color(btn_exit, lv_color_hex(0xFFC107), LV_PART_MAIN);
    lv_obj_set_style_radius(btn_exit, 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_exit, lv_color_hex(0xCC8400), LV_PART_MAIN | LV_STATE_PRESSED);
	  lv_obj_set_style_text_color(btn_exit, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	  lv_obj_center(lb_exit);
	if(scr==scr_menu)
    lv_obj_set_style_text_font(lb_exit , &lv_font_montserrat_40, 0);
	else
	  lv_obj_set_style_text_font(lb_exit , &lv_font_montserrat_30, 0);
	
		lv_obj_add_flag(btn_exit,LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_style_shadow_width(btn_exit,10,0);
		lv_obj_set_style_shadow_spread(btn_exit,3,0);
		lv_obj_set_style_shadow_color(btn_exit,lv_color_hex(0x000000),0);
		lv_obj_set_style_bg_grad_dir(btn_exit, LV_GRAD_DIR_VER, 0); // 第三个参数 0 表示应用到主要部分 (main part)
		lv_obj_set_style_bg_grad_color(btn_exit, lv_color_hex(0xFF5220), 0); //金色
		lv_obj_set_style_bg_main_stop(btn_exit, 0, 0);   // 主色从 0 开始
		lv_obj_set_style_bg_grad_stop(btn_exit, 255, 0); // 渐变色在 255 结束

}
void game_btn_mode_load(){        //加载模式按钮
    btn_mode = lv_btn_create(scr_menu);
	  lv_obj_set_size(btn_mode,256,100);
  	lv_obj_align(btn_mode,LV_ALIGN_CENTER,0,-150); //上移150
	lv_obj_add_event_cb(btn_mode,btn_mode_cb,LV_EVENT_CLICKED,NULL);
	  lv_obj_t *lb_mode=lv_label_create(btn_mode);
	  lv_label_set_text(lb_mode,"MODE");
    lv_obj_set_style_bg_color(btn_mode, lv_color_hex(0x9B59B6), LV_PART_MAIN);
    lv_obj_set_style_radius(btn_mode, 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_mode, lv_color_hex(0x7E3EA8), LV_PART_MAIN | LV_STATE_PRESSED);
	  lv_obj_set_style_text_color(btn_mode, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	  lv_obj_center(lb_mode);
    lv_obj_set_style_text_font(lb_mode , &lv_font_montserrat_40, 0);
		lv_obj_add_flag(btn_mode,LV_OBJ_FLAG_HIDDEN);

		lv_obj_set_style_shadow_width(btn_mode,10,0);
		lv_obj_set_style_shadow_spread(btn_mode,3,0);
		lv_obj_set_style_shadow_color(btn_mode,lv_color_hex(0x000000),0);
		lv_obj_set_style_bg_grad_dir(btn_mode, LV_GRAD_DIR_VER, 0); // 第三个参数 0 表示应用到主要部分 (main part)
		lv_obj_set_style_bg_grad_color(btn_mode, lv_color_hex(0xB185DB), 0); //紫色
		lv_obj_set_style_bg_main_stop(btn_mode, 0, 0);   // 主色从 0 开始
		lv_obj_set_style_bg_grad_stop(btn_mode, 255, 0); // 渐变色在 255 结束

}

void game_btn_time_load(){       //时间模式 
    btn_time = lv_btn_create(scr_menu);
	  lv_obj_set_size(btn_time,256,100);
  	lv_obj_align(btn_time,LV_ALIGN_CENTER,0,-150); //上移150
	lv_obj_add_event_cb(btn_time,btn_time_cb,LV_EVENT_CLICKED,NULL);
	  lv_obj_t *lb_time=lv_label_create(btn_time);
	  lv_label_set_text(lb_time,"TIME");
    lv_obj_set_style_bg_color(btn_time, lv_color_hex(0xFF9800), LV_PART_MAIN);
    lv_obj_set_style_radius(btn_time, 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_time, lv_color_hex(0xE68A00), LV_PART_MAIN | LV_STATE_PRESSED);
	  lv_obj_set_style_text_color(btn_time, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	  lv_obj_center(lb_time);
	  lv_obj_set_style_text_font(lb_time , &lv_font_montserrat_40, 0);
		  lv_obj_add_flag(btn_time,LV_OBJ_FLAG_HIDDEN);
		  
		lv_obj_set_style_shadow_width(btn_time,10,0);
		lv_obj_set_style_shadow_spread(btn_time,3,0);
		lv_obj_set_style_shadow_color(btn_time,lv_color_hex(0x000000),0);
		lv_obj_set_style_bg_grad_dir(btn_time, LV_GRAD_DIR_VER, 0); // 第三个参数 0 表示应用到主要部分 (main part)
		lv_obj_set_style_bg_grad_color(btn_time, lv_color_hex(0xFFB74D), 0); //橙色
		lv_obj_set_style_bg_main_stop(btn_time, 0, 0);   // 主色从 0 开始
		lv_obj_set_style_bg_grad_stop(btn_time, 255, 0); // 渐变色在 255 结束
}
void game_btn_step_load(){        //步数模式
    btn_step = lv_btn_create(scr_menu);
	  lv_obj_set_size(btn_step,256,100);
  	lv_obj_align(btn_step,LV_ALIGN_CENTER,0,0); 
	lv_obj_add_event_cb(btn_step,btn_step_cb,LV_EVENT_CLICKED,NULL);
	  lv_obj_t *lb_step=lv_label_create(btn_step);
	  lv_label_set_text(lb_step,"STEP");
    lv_obj_set_style_bg_color(btn_step, lv_color_hex(0x4CAF50), LV_PART_MAIN);
    lv_obj_set_style_radius(btn_step, 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_step, lv_color_hex(0x3D8B40), LV_PART_MAIN | LV_STATE_PRESSED);
	  lv_obj_set_style_text_color(btn_step, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	  lv_obj_center(lb_step);
	  lv_obj_set_style_text_font(lb_step , &lv_font_montserrat_40, 0);
		  lv_obj_add_flag(btn_step,LV_OBJ_FLAG_HIDDEN);
		  lv_obj_set_style_shadow_width(btn_step,10,0);
		  lv_obj_set_style_shadow_spread(btn_step,3,0);
		  lv_obj_set_style_shadow_color(btn_step,lv_color_hex(0x000000),0);
		  lv_obj_set_style_bg_grad_dir(btn_step, LV_GRAD_DIR_VER, 0); // 第三个参数 0 表示应用到主要部分 (main part)
		lv_obj_set_style_bg_grad_color(btn_step, lv_color_hex(0x81C784), 0); //绿色
		lv_obj_set_style_bg_main_stop(btn_step, 0, 0);   // 主色从 0 开始
		lv_obj_set_style_bg_grad_stop(btn_step, 255, 0); // 渐变色在 255 结束
  }

void game_btn_theme_load(){      //选择主题  
    btn_theme = lv_btn_create(scr_menu);
	  lv_obj_set_size(btn_theme,256,100);
  	lv_obj_align(btn_theme,LV_ALIGN_CENTER,0,0); 
	lv_obj_add_event_cb(btn_theme,btn_theme_cb,LV_EVENT_CLICKED,NULL);
	  lv_obj_t *lb_theme=lv_label_create(btn_theme);
	  lv_label_set_text(lb_theme,"THEME");
    lv_obj_set_style_bg_color(btn_theme, lv_color_hex(0xE91E63), LV_PART_MAIN);
    lv_obj_set_style_radius(btn_theme, 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_theme, lv_color_hex(0xD81A5A), LV_PART_MAIN | LV_STATE_PRESSED);
	  lv_obj_set_style_text_color(btn_theme, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	  lv_obj_center(lb_theme);
	  lv_obj_set_style_text_font(lb_theme , &lv_font_montserrat_40, 0);
		  lv_obj_add_flag(btn_theme,LV_OBJ_FLAG_HIDDEN);
		  lv_obj_set_style_shadow_width(btn_theme,10,0);
		  lv_obj_set_style_shadow_spread(btn_theme,3,0);
		  lv_obj_set_style_shadow_color(btn_theme,lv_color_hex(0x000000),0);
		  lv_obj_set_style_bg_grad_dir(btn_theme, LV_GRAD_DIR_VER, 0); // 第三个参数 0 表示应用到主要部分 (main part)
		  lv_obj_set_style_bg_grad_color(btn_theme, lv_color_hex(0xF06292), 0);//粉色 
		  lv_obj_set_style_bg_main_stop(btn_theme, 0, 0);   // 主色从 0 开始
		  lv_obj_set_style_bg_grad_stop(btn_theme, 255, 0); // 渐变色在 255 结束
}
void game_btn_level_load(){     //选择关卡
	for (int i=0;i<5;i++){
		btn_level[i] = lv_btn_create(scr_menu);
	  lv_obj_set_size(btn_level[i],70,70);
  	lv_obj_align(btn_level[i],LV_ALIGN_CENTER,-280+2*i*70,0); 
	lv_obj_add_event_cb(btn_level[i],btn_level_cb,LV_EVENT_CLICKED,(void*)(i+1));
	  lv_obj_t *lb_level=lv_label_create(btn_level[i]);
	  lv_label_set_text_fmt(lb_level,"%d",i+1);
    lv_obj_set_style_bg_color(btn_level[i], lv_color_hex(0xFFC107), LV_PART_MAIN);
    lv_obj_set_style_radius(btn_level[i], 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_level[i], lv_color_hex(0xCC8400), LV_PART_MAIN | LV_STATE_PRESSED);
	  lv_obj_set_style_text_color(btn_level[i], lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	  lv_obj_center(lb_level);
	  lv_obj_set_style_text_font(lb_level , &lv_font_montserrat_30, 0);
		  lv_obj_add_flag(btn_level[i],LV_OBJ_FLAG_HIDDEN);
		  lv_obj_set_style_shadow_width(btn_level[i],10,0);
		  lv_obj_set_style_shadow_spread(btn_level[i],3,0);
		  lv_obj_set_style_shadow_color(btn_level[i],lv_color_hex(0x000000),0);
		  lv_obj_set_style_bg_grad_dir(btn_level[i], LV_GRAD_DIR_VER, 0); // 第三个参数 0 表示应用到主要部分 (main part)
		  lv_obj_set_style_bg_grad_color(btn_level[i], lv_color_hex(0xFF5220), 0); 
		  lv_obj_set_style_bg_main_stop(btn_level[i], 0, 0);   // 主色从 0 开始
		  lv_obj_set_style_bg_grad_stop(btn_level[i], 255, 0); // 渐变色在 255 结束
	}

}
void game_btn_item_bomb_load(void) //加载十字道具按钮
{
    btn_item_bomb = lv_btn_create(scr_game);
    lv_obj_set_size(btn_item_bomb, 100, 100);
    lv_obj_align(btn_item_bomb, LV_ALIGN_BOTTOM_RIGHT, -20, -400); // 右下角
    lv_obj_add_event_cb(btn_item_bomb, btn_item_bomb_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *lb_bomb = lv_label_create(btn_item_bomb);
    lv_label_set_text(lb_bomb, "BOMB");
    lv_obj_set_style_bg_color(btn_item_bomb, lv_color_hex(0xFF4757), LV_PART_MAIN);
    lv_obj_set_style_radius(btn_item_bomb, 50, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_item_bomb, lv_color_hex(0xE02020), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(btn_item_bomb, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_center(lb_bomb);
    lv_obj_set_style_text_font(lb_bomb, &lv_font_montserrat_30, 0);
	lv_obj_set_style_shadow_width(btn_item_bomb,10,0);
	lv_obj_set_style_shadow_spread(btn_item_bomb,3,0);
	lv_obj_set_style_shadow_color(btn_item_bomb,lv_color_hex(0x000000),0);
	
}

void game_btn_item_row_load(void) //加载横消道具按钮
{
    btn_item_row = lv_btn_create(scr_game);
    lv_obj_set_size(btn_item_row, 100, 100);
    lv_obj_align(btn_item_row, LV_ALIGN_BOTTOM_RIGHT, -20, -280); // 炸弹下面
    lv_obj_add_event_cb(btn_item_row,btn_item_row_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *lb_row = lv_label_create(btn_item_row);
    lv_label_set_text(lb_row, "ROW");
    lv_obj_set_style_bg_color(btn_item_row, lv_color_hex(0x3742FA), LV_PART_MAIN);
    lv_obj_set_style_radius(btn_item_row, 50, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_item_row, lv_color_hex(0x1927D0), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(btn_item_row, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_center(lb_row);
    lv_obj_set_style_text_font(lb_row, &lv_font_montserrat_30, 0);
	lv_obj_set_style_shadow_width(btn_item_row,10,0);
	lv_obj_set_style_shadow_spread(btn_item_row,3,0);
	lv_obj_set_style_shadow_color(btn_item_row,lv_color_hex(0x000000),0);
}
void game_btn_item_col_load(void) //加载竖消道具按钮
{
	  btn_item_col = lv_btn_create(scr_game);
    lv_obj_set_size(btn_item_col, 100, 100);
    lv_obj_align(btn_item_col, LV_ALIGN_BOTTOM_RIGHT, -20, -160); // 最底部
    lv_obj_add_event_cb(btn_item_col, btn_item_col_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *lb_col = lv_label_create(btn_item_col);
    lv_label_set_text(lb_col, "COL");
    lv_obj_set_style_bg_color(btn_item_col, lv_color_hex(0x20B620), LV_PART_MAIN);
    lv_obj_set_style_radius(btn_item_col, 50, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_item_col, lv_color_hex(0x0A9E0A), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(btn_item_col, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_center(lb_col);
    lv_obj_set_style_text_font(lb_col, &lv_font_montserrat_30, 0);
	lv_obj_set_style_shadow_width(btn_item_col,10,0);
	lv_obj_set_style_shadow_spread(btn_item_col,3,0);
	lv_obj_set_style_shadow_color(btn_item_col,lv_color_hex(0x000000),0);
}

// 加载【清除最高分】按钮
void game_btn_clear_score_load(){
    // 创建按钮
    btn_clear_score = lv_btn_create(scr_menu);
    lv_obj_set_size(btn_clear_score, 128, 50);
    lv_obj_align(btn_clear_score, LV_ALIGN_BOTTOM_RIGHT, -10, -10); 
    
    // 绑定点击回调
    lv_obj_add_event_cb(btn_clear_score, btn_clear_score_cb, LV_EVENT_CLICKED, NULL);
    
    // 文字
    lv_obj_t *lb_clear = lv_label_create(btn_clear_score);
    lv_label_set_text(lb_clear, "CLEAR MAX");
    
    lv_obj_set_style_bg_color(btn_clear_score, lv_color_hex(0xFF4757), LV_PART_MAIN);
    lv_obj_set_style_radius(btn_clear_score, 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_clear_score, lv_color_hex(0xD93548), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(btn_clear_score, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_center(lb_clear);
    lv_obj_set_style_text_font(lb_clear, &lv_font_montserrat_14, 0);
    
    // 阴影
    lv_obj_set_style_shadow_width(btn_clear_score,10,0);
    lv_obj_set_style_shadow_spread(btn_clear_score,3,0);
    lv_obj_set_style_shadow_color(btn_clear_score,lv_color_hex(0x000000),0);
    
    // 渐变
    lv_obj_set_style_bg_grad_dir(btn_clear_score, LV_GRAD_DIR_VER, 0);
    lv_obj_set_style_bg_grad_color(btn_clear_score, lv_color_hex(0xFF2020), 0);
    lv_obj_set_style_bg_main_stop(btn_clear_score, 0, 0);
    lv_obj_set_style_bg_grad_stop(btn_clear_score, 255, 0);
}
// 加载【游戏说明】按钮（主菜单右下角）
void game_btn_help_load(){
    // 创建按钮 → 父对象是 scr_menu（只在主菜单显示）
    btn_help = lv_btn_create(scr_menu);
    
    // 按钮大小
    lv_obj_set_size(btn_help,128 , 50);
    
    // 位置：右下角，CLEAR MAX 按钮上方一点
    lv_obj_align(btn_help, LV_ALIGN_BOTTOM_RIGHT, -10, -70); 
    
    // 点击事件
    lv_obj_add_event_cb(btn_help, btn_help_cb, LV_EVENT_CLICKED, NULL);
    
    // 文字
    lv_obj_t *lb_help = lv_label_create(btn_help);
    lv_label_set_text(lb_help, "HELP");
    
    // 样式完全跟你的 START / OPTION 统一
    lv_obj_set_style_bg_color(btn_help, lv_color_hex(0x3742FA), LV_PART_MAIN);
    lv_obj_set_style_radius(btn_help, 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_help, lv_color_hex(0x1927D0), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(btn_help, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_center(lb_help);
    lv_obj_set_style_text_font(lb_help, &lv_font_montserrat_14, 0);
    
    // 阴影
    lv_obj_set_style_shadow_width(btn_help, 10, 0);
    lv_obj_set_style_shadow_spread(btn_help, 3, 0);
    lv_obj_set_style_shadow_color(btn_help, lv_color_hex(0x000000), 0);
    
    // 渐变
    lv_obj_set_style_bg_grad_dir(btn_help, LV_GRAD_DIR_VER, 0);
    lv_obj_set_style_bg_grad_color(btn_help, lv_color_hex(0x20B2FF), 0); 
    lv_obj_set_style_bg_main_stop(btn_help, 0, 0);
    lv_obj_set_style_bg_grad_stop(btn_help, 255, 0);
}

