#include "game.h"


uint16_t game_score = 0;
uint16_t high_score = 0;
extern uint16_t game_time ;
extern uint16_t game_step ;
extern uint16_t game_goal ;
uint8_t  game_over  = 0;

lv_obj_t *label_score;
lv_obj_t *label_time;
lv_obj_t *label_high;
lv_obj_t *label_step;
lv_obj_t *label_goal;

lv_obj_t *game_end_bg;
lv_obj_t *game_end_title;
lv_obj_t *game_end_score;
lv_obj_t *btn_back_main;
extern lv_timer_t * gametime;
extern lv_obj_t * btn_exit;
extern bool game_mode;

void btn_back_main_cb(lv_event_t *e);
void game_timer_cb(lv_timer_t* timer);



void game_score_label_create(lv_obj_t *scr)
{
    label_score = lv_label_create(scr);
    lv_label_set_text(label_score, "Score:0");
    lv_obj_set_style_text_color(label_score, lv_color_hex(0xFFFC29), 0);
	  lv_obj_set_style_text_font(label_score, &lv_font_montserrat_40, 0);
    lv_obj_align(label_score, LV_ALIGN_TOP_LEFT, 20, 100);

  if(game_mode == false)
    {
    label_time = lv_label_create(scr);
    lv_label_set_text(label_time, "Time:");
    lv_obj_set_style_text_color(label_time, lv_color_hex(0x00FF00), 0);
	  lv_obj_set_style_text_font(label_time, &lv_font_montserrat_40, 0);
    lv_obj_align(label_time, LV_ALIGN_TOP_LEFT, 20, 200);
    }
    
  else
    {
    label_step = lv_label_create(scr);
    lv_label_set_text(label_step, "Step:");
    lv_obj_set_style_text_color(label_step, lv_color_hex(0x00FF00), 0);
	  lv_obj_set_style_text_font(label_step, &lv_font_montserrat_40, 0);
    lv_obj_align(label_step, LV_ALIGN_TOP_LEFT, 20, 200);
    }
    label_goal = lv_label_create(scr);
    lv_label_set_text(label_goal, "Goal:");
    lv_obj_set_style_text_color(label_goal, lv_color_hex(0x00FF00), 0);
	  lv_obj_set_style_text_font(label_goal, &lv_font_montserrat_40, 0);
    lv_obj_align(label_goal, LV_ALIGN_TOP_LEFT, 20, 300);
    
    label_high = lv_label_create(scr);
	  char buff[20];
    sprintf(buff, "High:%d", high_score);
    lv_label_set_text(label_high, buff);
    lv_obj_set_style_text_color(label_high, lv_color_hex(0xFFFFFF), 0);
	  lv_obj_set_style_text_font(label_high, &lv_font_montserrat_40, 0);
    lv_obj_align(label_high, LV_ALIGN_TOP_LEFT, 20, 400);
}

void game_init_data(void)
{
    game_score = 0;
    
    game_over  = 0;
    
}

void game_timer_cb(lv_timer_t* timer)
{
    if(game_over == 0&&game_mode == false)
    {
        game_time--;

        char buff[20];
        sprintf(buff, "Time:%d", game_time);
        lv_label_set_text(label_time, buff);
        char buff0[20];
        sprintf(buff0, "Goal:%d", game_goal);
        lv_label_set_text(label_goal, buff0);
        if(game_time <= 0)
        {
            game_over = 1;
			gametime=NULL;
            lv_timer_del(timer);

            if(game_score > high_score)
            {
                high_score = game_score;
            }

            game_end_show();
        }
    }
    else if(game_over == 0&&game_mode == true)
    {
        
        char buff1[20];
        char buff2[20];
        sprintf(buff1, "Step:%d", game_step);
        sprintf(buff2, "Goal:%d", game_goal);
        lv_label_set_text(label_step, buff1);
        lv_label_set_text(label_goal, buff2);
        if(game_step <= 0)
        {
            game_over = 1;
            gametime=NULL;
            lv_timer_del(timer);
            if(game_score > high_score)
            {
                high_score = game_score;
            }
            game_end_show();
        }
    }
    else if(game_over == 1)
    {
        game_end_show();
    }
}

void game_end_show(void)  //弹出结束界面
{
	  char buf[60];
    game_fall_stop_all();   //停掉下落链，避免带入下一局
    status = NORMAL;
    lv_anim_del_all();
    game_end_bg = lv_obj_create(lv_scr_act());
    lv_obj_set_size(game_end_bg, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_style_bg_color(game_end_bg, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(game_end_bg, 180, 0);
    lv_obj_clear_flag(game_end_bg, LV_OBJ_FLAG_SCROLLABLE);

    game_end_title = lv_label_create(game_end_bg);
    if(game_score<game_goal)
        lv_label_set_text(game_end_title, "YOU LOSE");
    else 
        lv_label_set_text(game_end_title,"YOU WIN");
    lv_obj_set_style_text_color(game_end_title, lv_color_hex(0xFFFC29), 0);
    lv_obj_set_style_text_font(game_end_title, &lv_font_montserrat_40, 0);
    lv_obj_align(game_end_title, LV_ALIGN_CENTER, 0, -50);

    game_end_score = lv_label_create(game_end_bg);
    sprintf(buf, "Score: %d\nBest Record: %d", game_score, high_score);
    lv_label_set_text(game_end_score, buf);
    lv_obj_set_style_text_color(game_end_score, lv_color_white(), 0);
    lv_obj_align(game_end_score, LV_ALIGN_CENTER, 0, 10);

    btn_back_main = lv_btn_create(game_end_bg);
    lv_obj_set_size(btn_back_main, 140, 50);
    lv_obj_align(btn_back_main, LV_ALIGN_CENTER, 0, 80);
    lv_obj_add_event_cb(btn_back_main, btn_back_main_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *lab = lv_label_create(btn_back_main);
    lv_label_set_text(lab, "BACK");
    lv_obj_center(lab);
}

void btn_back_main_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code != LV_EVENT_CLICKED) return;
    lv_obj_set_parent(btn_exit,scr_menu);
    // 删除结束界面
    if(game_end_bg != NULL) {
        lv_obj_del(game_end_bg);
        game_end_bg = NULL;
    }
    
    //清理游戏资源
    game_cleanup_all();
    
    // 恢复主菜单按钮状态
    lv_obj_clear_flag(btn_start, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(btn_choose, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn_def, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(btn_ice, LV_OBJ_FLAG_HIDDEN);
    
    // 重置Exit按钮
    lv_obj_set_parent(btn_exit, scr_menu);
    lv_obj_set_size(btn_exit, 256, 100);
    lv_obj_align(btn_exit, LV_ALIGN_CENTER, 0, 150);
    lv_obj_add_flag(btn_exit, LV_OBJ_FLAG_HIDDEN);
    
    // 切换回主菜单
    lv_scr_load(scr_menu);
}

void game_cleanup_all(void)  //清理本局资源
{
    game_fall_stop_all();   //停掉下落检测定时器
    //清理倒计时
    if(gametime != NULL) {
        lv_timer_del(gametime);
        gametime = NULL;
    }
    
    //  清理游戏界面
    if(scr_game != NULL && lv_obj_is_valid(scr_game)) {
        lv_obj_clean(scr_game);
    }
    
    // 重置游戏状态
    status = NORMAL;
    game_over = 0;
    game_score = 0;
    game_time = 0;
    
    //  重置坐标映射
    for(uint8_t i = 0; i < GRID_COLS; i++) {
        for(uint8_t j = 0; j < GRID_ROWS; j++) {
            coord_map[i][j] = NULL;
        }
    }
}
