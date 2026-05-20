#include "drivers.h"
#include "lvgl.h"
#include "game.h"

extern lv_obj_t * scr_menu; 
extern void btn_start_cb(lv_event_t*e);
extern void btn_choose_cb(lv_event_t*e);
extern void btn_def_cb(lv_event_t*e);
extern void btn_ice_cb(lv_event_t*e);
extern lv_obj_t * scr_game;
extern lv_obj_t * btn_level[5];
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


void game_btn_start_load(){        //加载开始按钮
	
    btn_start = lv_btn_create(scr_menu);
	  lv_obj_set_size(btn_start,256,100);
	  lv_obj_align(btn_start,LV_ALIGN_CENTER,-200,0); //右移200
	  lv_obj_add_event_cb(btn_start,btn_start_cb,LV_EVENT_CLICKED,NULL);
	  lv_obj_t *lb_start=lv_label_create(btn_start);
	  lv_label_set_text(lb_start,"START");
    lv_obj_set_style_bg_color(btn_start, lv_color_hex(0xFFC107), LV_PART_MAIN);//按钮颜色
    lv_obj_set_style_radius(btn_start, 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_start, lv_color_hex(0xCC8400), LV_PART_MAIN | LV_STATE_PRESSED);
	  lv_obj_set_style_text_color(btn_start, lv_color_hex(0xFFFFFF), LV_PART_MAIN);//字体颜色
	  lv_obj_center(lb_start); //居中
    lv_obj_set_style_text_font(lb_start , &lv_font_montserrat_40, 0);  //字体大小40
}
void game_btn_choose_load(){        
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



}
void game_btn_theme_default_load(){        
    btn_def = lv_btn_create(scr_menu);
	  lv_obj_set_size(btn_def,256,100);
	  lv_obj_align(btn_def,LV_ALIGN_CENTER,0,0); 
	  lv_obj_add_event_cb(btn_def,btn_def_cb,LV_EVENT_CLICKED,NULL);
	  lv_obj_t *lb_def=lv_label_create(btn_def);
	  lv_label_set_text(lb_def,"DEFAULT\n  THEME");
    lv_obj_set_style_bg_color(btn_def, lv_color_hex(0xFFC107), LV_PART_MAIN);
    lv_obj_set_style_radius(btn_def, 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_def, lv_color_hex(0xCC8400), LV_PART_MAIN | LV_STATE_PRESSED);
	  lv_obj_set_style_text_color(btn_def, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	  lv_obj_center(lb_def);
    lv_obj_set_style_text_font(lb_def , &lv_font_montserrat_40, 0);
 		lv_obj_add_flag(btn_def,LV_OBJ_FLAG_HIDDEN);


}
void game_btn_theme_ice_load(){        
    btn_ice = lv_btn_create(scr_menu);
	  lv_obj_set_size(btn_ice,256,100);
  	lv_obj_align(btn_ice,LV_ALIGN_CENTER,0,-150); //上移150
	  lv_obj_add_event_cb(btn_ice,btn_ice_cb,LV_EVENT_CLICKED,NULL);
	  lv_obj_t *lb_ice=lv_label_create(btn_ice);
	  lv_label_set_text(lb_ice,"SUMMER\n  THEME");
    lv_obj_set_style_bg_color(btn_ice, lv_color_hex(0xFFC107), LV_PART_MAIN);
    lv_obj_set_style_radius(btn_ice, 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_ice, lv_color_hex(0xCC8400), LV_PART_MAIN | LV_STATE_PRESSED);
	  lv_obj_set_style_text_color(btn_ice, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	  lv_obj_center(lb_ice);
    lv_obj_set_style_text_font(lb_ice , &lv_font_montserrat_40, 0);
		lv_obj_add_flag(btn_ice,LV_OBJ_FLAG_HIDDEN);


}
void game_btn_exit_load(lv_obj_t*scr){        
    btn_exit = lv_btn_create(scr);
	if(scr==scr_menu){
		lv_obj_set_size(btn_exit,256,100);
  	lv_obj_align(btn_exit,LV_ALIGN_CENTER,0,150); //下移150
	}
	else if(scr==scr_game){
		lv_obj_set_size(btn_exit,128,50);
		lv_obj_align(btn_exit,LV_ALIGN_CENTER,430,150); 
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



}
void game_btn_mode_load(){        
    btn_mode = lv_btn_create(scr_menu);
	  lv_obj_set_size(btn_mode,256,100);
  	lv_obj_align(btn_mode,LV_ALIGN_CENTER,0,-150); //上移150
	lv_obj_add_event_cb(btn_mode,btn_mode_cb,LV_EVENT_CLICKED,NULL);
	  lv_obj_t *lb_mode=lv_label_create(btn_mode);
	  lv_label_set_text(lb_mode,"MODE");
    lv_obj_set_style_bg_color(btn_mode, lv_color_hex(0xFFC107), LV_PART_MAIN);
    lv_obj_set_style_radius(btn_mode, 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_mode, lv_color_hex(0xCC8400), LV_PART_MAIN | LV_STATE_PRESSED);
	  lv_obj_set_style_text_color(btn_mode, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	  lv_obj_center(lb_mode);
    lv_obj_set_style_text_font(lb_mode , &lv_font_montserrat_40, 0);
		lv_obj_add_flag(btn_mode,LV_OBJ_FLAG_HIDDEN);


}

void game_btn_time_load(){        
    btn_time = lv_btn_create(scr_menu);
	  lv_obj_set_size(btn_time,256,100);
  	lv_obj_align(btn_time,LV_ALIGN_CENTER,0,-150); //上移150
	lv_obj_add_event_cb(btn_time,btn_time_cb,LV_EVENT_CLICKED,NULL);
	  lv_obj_t *lb_time=lv_label_create(btn_time);
	  lv_label_set_text(lb_time,"TIME");
    lv_obj_set_style_bg_color(btn_time, lv_color_hex(0xFFC107), LV_PART_MAIN);
    lv_obj_set_style_radius(btn_time, 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_time, lv_color_hex(0xCC8400), LV_PART_MAIN | LV_STATE_PRESSED);
	  lv_obj_set_style_text_color(btn_time, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	  lv_obj_center(lb_time);
	  lv_obj_set_style_text_font(lb_time , &lv_font_montserrat_40, 0);
		  lv_obj_add_flag(btn_time,LV_OBJ_FLAG_HIDDEN);
}
void game_btn_step_load(){        
    btn_step = lv_btn_create(scr_menu);
	  lv_obj_set_size(btn_step,256,100);
  	lv_obj_align(btn_step,LV_ALIGN_CENTER,0,0); 
	lv_obj_add_event_cb(btn_step,btn_step_cb,LV_EVENT_CLICKED,NULL);
	  lv_obj_t *lb_step=lv_label_create(btn_step);
	  lv_label_set_text(lb_step,"STEP");
    lv_obj_set_style_bg_color(btn_step, lv_color_hex(0xFFC107), LV_PART_MAIN);
    lv_obj_set_style_radius(btn_step, 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_step, lv_color_hex(0xCC8400), LV_PART_MAIN | LV_STATE_PRESSED);
	  lv_obj_set_style_text_color(btn_step, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	  lv_obj_center(lb_step);
	  lv_obj_set_style_text_font(lb_step , &lv_font_montserrat_40, 0);
		  lv_obj_add_flag(btn_step,LV_OBJ_FLAG_HIDDEN);
}
void game_btn_theme_load(){        
    btn_theme = lv_btn_create(scr_menu);
	  lv_obj_set_size(btn_theme,256,100);
  	lv_obj_align(btn_theme,LV_ALIGN_CENTER,0,0); 
	lv_obj_add_event_cb(btn_theme,btn_theme_cb,LV_EVENT_CLICKED,NULL);
	  lv_obj_t *lb_theme=lv_label_create(btn_theme);
	  lv_label_set_text(lb_theme,"THEME");
    lv_obj_set_style_bg_color(btn_theme, lv_color_hex(0xFFC107), LV_PART_MAIN);
    lv_obj_set_style_radius(btn_theme, 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_theme, lv_color_hex(0xCC8400), LV_PART_MAIN | LV_STATE_PRESSED);
	  lv_obj_set_style_text_color(btn_theme, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	  lv_obj_center(lb_theme);
	  lv_obj_set_style_text_font(lb_theme , &lv_font_montserrat_40, 0);
		  lv_obj_add_flag(btn_theme,LV_OBJ_FLAG_HIDDEN);
}
void game_btn_level_load(){
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
	}
}
