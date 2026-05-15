#include "drivers.h"
#include "lvgl.h"
#include "game.h"

extern lv_obj_t * scr_menu; 
extern void btn_start_cb(lv_event_t*e);
extern void btn_choose_cb(lv_event_t*e);
extern void btn_def_cb(lv_event_t*e);
extern void btn_ice_cb(lv_event_t*e);

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

void game_btn_start_load(){        //加载开始按钮
	
    btn_start = lv_btn_create(scr_menu);
	  lv_obj_set_size(btn_start,256,100);
	  lv_obj_align(btn_start,LV_ALIGN_CENTER,-200,0); //右移200
	  lv_obj_add_event_cb(btn_start,btn_start_cb,LV_EVENT_ALL,NULL);
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
	  lv_obj_add_event_cb(btn_choose,btn_choose_cb,LV_EVENT_ALL,NULL);
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
	  lv_obj_add_event_cb(btn_def,btn_def_cb,LV_EVENT_ALL,NULL);
	  lv_obj_t *lb_def=lv_label_create(btn_def);
	  lv_label_set_text(lb_def,"DEFAULT\n  THEME");
    lv_obj_set_style_bg_color(btn_def, lv_color_hex(0xFFC107), LV_PART_MAIN);
    lv_obj_set_style_radius(btn_def, 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_def, lv_color_hex(0xCC8400), LV_PART_MAIN | LV_STATE_PRESSED);
	  lv_obj_set_style_text_color(btn_def, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	  lv_obj_center(lb_def);
    lv_obj_set_style_text_font(lb_def , &lv_font_montserrat_40, 0);


}
void game_btn_theme_ice_load(){        
    btn_ice = lv_btn_create(scr_menu);
	  lv_obj_set_size(btn_ice,256,100);
  	lv_obj_align(btn_ice,LV_ALIGN_CENTER,0,-150); //上移150
	  lv_obj_add_event_cb(btn_ice,btn_ice_cb,LV_EVENT_ALL,NULL);
	  lv_obj_t *lb_ice=lv_label_create(btn_ice);
	  lv_label_set_text(lb_ice,"SUMMER\n  THEME");
    lv_obj_set_style_bg_color(btn_ice, lv_color_hex(0xFFC107), LV_PART_MAIN);
    lv_obj_set_style_radius(btn_ice, 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_ice, lv_color_hex(0xCC8400), LV_PART_MAIN | LV_STATE_PRESSED);
	  lv_obj_set_style_text_color(btn_ice, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	  lv_obj_center(lb_ice);
    lv_obj_set_style_text_font(lb_ice , &lv_font_montserrat_40, 0);


}
void game_btn_exit_load(){        
    btn_exit = lv_btn_create(scr_menu);
	  lv_obj_set_size(btn_exit,256,100);
  	lv_obj_align(btn_exit,LV_ALIGN_CENTER,0,150); //下移150
	  lv_obj_add_event_cb(btn_exit,btn_exit_cb,LV_EVENT_ALL,NULL);
	  lv_obj_t *lb_exit=lv_label_create(btn_exit);
	  lv_label_set_text(lb_exit,"EXIT");
    lv_obj_set_style_bg_color(btn_exit, lv_color_hex(0xFFC107), LV_PART_MAIN);
    lv_obj_set_style_radius(btn_exit, 10, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_exit, lv_color_hex(0xCC8400), LV_PART_MAIN | LV_STATE_PRESSED);
	  lv_obj_set_style_text_color(btn_exit, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	  lv_obj_center(lb_exit);
    lv_obj_set_style_text_font(lb_exit , &lv_font_montserrat_40, 0);


}
