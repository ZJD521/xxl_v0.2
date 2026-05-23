#include "drivers.h"
#include "lvgl.h"
#include "game.h"
extern lv_obj_t * btn_start ;
extern lv_obj_t * btn_choose ;
extern lv_obj_t * btn_def ;
extern lv_obj_t * btn_ice ;
extern lv_obj_t * btn_exit;
extern lv_obj_t * btn_mode;
extern lv_obj_t * btn_theme;
extern lv_obj_t * btn_time;
extern lv_obj_t * btn_step;
extern lv_obj_t * btn_level[5];
extern bac bg;
extern lv_obj_t * scr_menu; 
extern lv_obj_t * scr_game;
extern lv_timer_t * gametime;
extern char buf[60];
extern uint16_t game_level;
extern uint8_t item_bomb_used;
extern uint8_t item_row_used;
extern uint8_t item_col_used;

bool game_mode = false;//游戏模式，false为时间模式，true为步数模式

void btn_start_cb(lv_event_t*e){  //开始游戏，和start键交互就会调用这个函数
	lv_event_code_t code = lv_event_get_code(e);  //获取事件发生类型 
	if(code == LV_EVENT_CLICKED){ //点击则会执行
		srand(lv_tick_get());
	    lv_obj_add_flag(btn_start,LV_OBJ_FLAG_HIDDEN); //隐藏start
	    lv_obj_add_flag(btn_choose,LV_OBJ_FLAG_HIDDEN);  //隐藏option
		for (int i=0;i<5;i++){  //显示5个难度按钮
			lv_obj_clear_flag(btn_level[i],LV_OBJ_FLAG_HIDDEN);  //清除隐藏
		}
	    lv_obj_clear_flag(btn_exit,LV_OBJ_FLAG_HIDDEN);

	}
		
	 

}
void btn_choose_cb(lv_event_t*e){  //加载两个主题按钮
	  lv_event_code_t code = lv_event_get_code(e); 
	  if(code == LV_EVENT_CLICKED){
		lv_obj_add_flag(btn_start,LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(btn_choose,LV_OBJ_FLAG_HIDDEN);
			
    lv_obj_clear_flag(btn_theme,LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(btn_mode,LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(btn_exit,LV_OBJ_FLAG_HIDDEN);
    
	  
		}

}
void btn_def_cb(lv_event_t*e){   //标记主题(默认)
	  lv_event_code_t code = lv_event_get_code(e); 
	  if(code == LV_EVENT_CLICKED){
    srand(lv_tick_get());
		lv_obj_add_flag(btn_def,LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(btn_ice,LV_OBJ_FLAG_HIDDEN);
		bg.theme=DEFAULT;
		lv_obj_clear_flag(btn_theme,LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(btn_mode,LV_OBJ_FLAG_HIDDEN);
			
	  
		}
	 

}
void btn_ice_cb(lv_event_t*e){   ////标记主题(蔬果)
	  lv_event_code_t code = lv_event_get_code(e); 
	  if(code == LV_EVENT_CLICKED){
	  srand(lv_tick_get());
		lv_obj_add_flag(btn_def,LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(btn_ice,LV_OBJ_FLAG_HIDDEN);
		bg.theme=ICE;
		lv_obj_clear_flag(btn_theme,LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(btn_mode,LV_OBJ_FLAG_HIDDEN);
			
	  
		}
	 
}
void btn_exit_cb(lv_event_t*e){    //返回
    lv_event_code_t code = lv_event_get_code(e); 
    if(code == LV_EVENT_CLICKED && lv_scr_act() == scr_menu){
        lv_obj_add_flag(btn_ice, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(btn_def, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(btn_exit, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(btn_mode, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(btn_time, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(btn_step, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(btn_theme, LV_OBJ_FLAG_HIDDEN);
        for (int i=0;i<5;i++){
			lv_obj_add_flag(btn_level[i],LV_OBJ_FLAG_HIDDEN);
		}
        lv_obj_clear_flag(btn_start, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(btn_choose, LV_OBJ_FLAG_HIDDEN);
    }
    else if(code == LV_EVENT_CLICKED && lv_scr_act() == scr_game ){
        game_over = 1;
        game_fall_stop_all();   //中途退出时停掉下落链
        
        //清理倒计时
        if (gametime != NULL) {
            lv_timer_del(gametime);
            gametime = NULL;
        }

        // 更新最高分
        if(game_score > high_score) {
            char buff[20];
            high_score = game_score;
            sprintf(buff, "High: %d", high_score);
            lv_label_set_text(label_high, buff);
        }
        
        // 显示结束界面
        game_end_show();
    }
}
void btn_mode_cb(lv_event_t*e){  //显示两个模式按钮
	lv_event_code_t code = lv_event_get_code(e); 
	if(code == LV_EVENT_CLICKED){
	  lv_obj_add_flag(btn_mode,LV_OBJ_FLAG_HIDDEN);
	  lv_obj_add_flag(btn_theme,LV_OBJ_FLAG_HIDDEN);
		  
      lv_obj_clear_flag(btn_time,LV_OBJ_FLAG_HIDDEN);
	  lv_obj_clear_flag(btn_step,LV_OBJ_FLAG_HIDDEN);
	  
  
	
	  }

}
void btn_time_cb(lv_event_t*e){  //时间模式
	lv_event_code_t code = lv_event_get_code(e); 
	if(code == LV_EVENT_CLICKED){
		game_mode = false;
		lv_obj_add_flag(btn_time,LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(btn_step,LV_OBJ_FLAG_HIDDEN);

		lv_obj_clear_flag(btn_mode,LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(btn_theme,LV_OBJ_FLAG_HIDDEN);
	
	}
}
void btn_step_cb(lv_event_t*e){  //步数模式
	lv_event_code_t code = lv_event_get_code(e); 
	if(code == LV_EVENT_CLICKED){
		game_mode = true;
		lv_obj_add_flag(btn_time,LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(btn_step,LV_OBJ_FLAG_HIDDEN);

		lv_obj_clear_flag(btn_mode,LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(btn_theme,LV_OBJ_FLAG_HIDDEN);
	}
}
void btn_theme_cb(lv_event_t*e){  //主题按钮
	lv_event_code_t code = lv_event_get_code(e); 
	if(code == LV_EVENT_CLICKED){
		lv_obj_add_flag(btn_theme,LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(btn_mode,LV_OBJ_FLAG_HIDDEN);

		lv_obj_clear_flag(btn_def,LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(btn_ice,LV_OBJ_FLAG_HIDDEN);
		
	}
}
void btn_level_cb(lv_event_t*e){
	lv_event_code_t code = lv_event_get_code(e); 
	if(code == LV_EVENT_CLICKED){
		int level_choose=(int)lv_event_get_user_data(e);
		game_level=level_choose;
		for (int i=0;i<5;i++){
			lv_obj_add_flag(btn_level[i],LV_OBJ_FLAG_HIDDEN);
		}
		lv_scr_load(scr_game);
		lv_obj_set_size(btn_exit,128,50);  
		lv_obj_align(btn_exit,LV_ALIGN_CENTER,430,150); 
 		lv_obj_set_parent(btn_exit,scr_game);

		
		
	}
}
void btn_item_bomb_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
			  if(item_bomb_used == 0)
				{
        // 选中炸弹道具
        cur_use_item = ITEM_BOMB;
			  item_bomb_used = 1;   // 标记已使用
        lv_obj_add_flag(btn_item_bomb, LV_OBJ_FLAG_CLICKABLE); // 按钮变灰不可点
				lv_obj_set_style_bg_color(btn_item_bomb, lv_color_hex(0x666666), LV_PART_MAIN);
				}
				else
				{
					return;
				}
    }
}
void btn_item_row_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
			if(item_row_used==0)
			{
				cur_use_item = ITEM_ROW_CLEAR;
				item_row_used = 1;   // 标记已使用
        lv_obj_add_flag(btn_item_row, LV_OBJ_FLAG_CLICKABLE); // 按钮变灰不可点
				lv_obj_set_style_bg_color(btn_item_row, lv_color_hex(0x666666), LV_PART_MAIN);
			}
        // 选中横排消除
        else
				{
					return;
				}
    }
}

void btn_item_col_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
			if(item_col_used==0)
			{
			   cur_use_item = ITEM_COL_CLEAR;
				item_col_used = 1;   // 标记已使用
        lv_obj_add_flag(btn_item_col, LV_OBJ_FLAG_CLICKABLE); // 按钮变灰不可点
				lv_obj_set_style_bg_color(btn_item_col, lv_color_hex(0x666666), LV_PART_MAIN);
			}
        // 选中竖列消除
        else
				{
					return;
				}
    }
}
