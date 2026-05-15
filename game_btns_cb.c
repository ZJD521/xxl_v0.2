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
extern lv_timer_t * gametime;
extern char buf[60];
void btn_start_cb(lv_event_t*e){  //直接切屏进入游戏
	  lv_event_code_t code = lv_event_get_code(e); 
	  if(code == LV_EVENT_CLICKED){
	  srand(lv_tick_get());

	  lv_scr_load(scr_game);
		lv_obj_add_flag(btn_start,LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(btn_choose,LV_OBJ_FLAG_HIDDEN);
			
		lv_obj_set_size(btn_exit,128,50);  
		lv_obj_align(btn_exit,LV_ALIGN_CENTER,430,150); 
 		lv_obj_set_parent(btn_exit,scr_game);

		}
		
	 

}
void btn_choose_cb(lv_event_t*e){  //加载两个主题按钮
	  lv_event_code_t code = lv_event_get_code(e); 
	  if(code == LV_EVENT_CLICKED){
	  srand(lv_tick_get());
		lv_obj_add_flag(btn_start,LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(btn_choose,LV_OBJ_FLAG_HIDDEN);
			
    lv_obj_clear_flag(btn_def,LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(btn_ice,LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(btn_exit,LV_OBJ_FLAG_HIDDEN);
    
	  
		}

}
void btn_def_cb(lv_event_t*e){   //标记主题并切屏进入游戏
	  lv_event_code_t code = lv_event_get_code(e); 
	  if(code == LV_EVENT_CLICKED){
    srand(lv_tick_get());
		lv_obj_add_flag(btn_def,LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(btn_ice,LV_OBJ_FLAG_HIDDEN);
	
		lv_obj_set_size(btn_exit,128,50);  
		lv_obj_align(btn_exit,LV_ALIGN_CENTER,430,150); 
 		lv_obj_set_parent(btn_exit,scr_game);
			
	  bg.theme=DEFAULT;
    lv_scr_load(scr_game);
		}
	 

}
void btn_ice_cb(lv_event_t*e){   ////标记主题并切屏进入游戏
	  lv_event_code_t code = lv_event_get_code(e); 
	  if(code == LV_EVENT_CLICKED){
	  srand(lv_tick_get());
		lv_obj_add_flag(btn_def,LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(btn_ice,LV_OBJ_FLAG_HIDDEN);
	
		lv_obj_set_size(btn_exit,128,50);  
		lv_obj_align(btn_exit,LV_ALIGN_CENTER,430,150); 
 		lv_obj_set_parent(btn_exit,scr_game);
			
  	bg.theme=ICE;
    lv_scr_load(scr_game);
    }
	 
}
void btn_exit_cb(lv_event_t*e){    //返回
	  lv_event_code_t code = lv_event_get_code(e); 
	 if(code == LV_EVENT_CLICKED&&lv_scr_act()==scr_menu){
		lv_obj_add_flag(btn_ice,LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(btn_def,LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(btn_exit,LV_OBJ_FLAG_HIDDEN);
		 
    lv_obj_clear_flag(btn_start,LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(btn_choose,LV_OBJ_FLAG_HIDDEN);
		
		}
	else if(code == LV_EVENT_CLICKED&&lv_scr_act()==scr_game){
		 lv_obj_set_parent(btn_exit,scr_menu);
		 lv_obj_add_flag(btn_exit,LV_OBJ_FLAG_HIDDEN);
		 lv_obj_set_size(btn_exit,256,100);
  	 lv_obj_align(btn_exit,LV_ALIGN_CENTER,0,150); //下移150
		
		 game_over = 1;
            lv_timer_del(gametime);

            if(game_score > high_score)
            {
                high_score = game_score;
                sprintf(buf, "High: %d", high_score);
                lv_label_set_text(label_high, buf);
            }
	  game_end_show();
    	}
	
		
	 

}
