#include "drivers.h"
#include "lvgl.h"
#include "game.h"
extern lv_obj_t * btn_start ;
extern lv_obj_t * btn_choose ;
extern lv_obj_t * btn_def ;
extern lv_obj_t * btn_ice ;
extern lv_obj_t * btn_exit;
extern bac bg;
extern lv_obj_t * scr_menu; 
extern lv_obj_t * scr_game;
void btn_start_cb(lv_event_t*e){  //直接切屏进入游戏
	  lv_event_code_t code = lv_event_get_code(e); 
	  if(code == LV_EVENT_CLICKED){
	  srand(lv_tick_get());

	  lv_scr_load(scr_game);
		}
		
	 

}
void btn_choose_cb(lv_event_t*e){  //加载两个主题按钮
	  lv_event_code_t code = lv_event_get_code(e); 
	  if(code == LV_EVENT_CLICKED){
	  srand(lv_tick_get());
		lv_obj_add_flag(btn_start,LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(btn_choose,LV_OBJ_FLAG_HIDDEN);
    game_btn_theme_default_load();
	  game_btn_theme_ice_load();
		game_btn_exit_load();
	  lv_obj_del(btn_choose);
    lv_obj_del(btn_start);
		}

}
void btn_def_cb(lv_event_t*e){   //标记主题并切屏进入游戏
	  lv_event_code_t code = lv_event_get_code(e); 
	  if(code == LV_EVENT_CLICKED){
    srand(lv_tick_get());

	  bg.theme=DEFAULT;
    lv_scr_load(scr_game);
		}
	 

}
void btn_ice_cb(lv_event_t*e){   ////标记主题并切屏进入游戏
	  lv_event_code_t code = lv_event_get_code(e); 
	  if(code == LV_EVENT_CLICKED){
	  srand(lv_tick_get());

  	bg.theme=ICE;
    lv_scr_load(scr_game);
    }
	 
}
void btn_exit_cb(lv_event_t*e){    //返回
	  lv_event_code_t code = lv_event_get_code(e); 
	  if(code == LV_EVENT_CLICKED){
		lv_obj_add_flag(btn_ice,LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(btn_def,LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(btn_exit,LV_OBJ_FLAG_HIDDEN);
		game_btn_start_load();
    game_btn_choose_load();
	  lv_obj_del(btn_def);
    lv_obj_del(btn_ice);	  
    lv_obj_del(btn_exit);
		game_score = 0;
		}
		
	 

}
