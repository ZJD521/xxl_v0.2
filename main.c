#include "drivers.h"
#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
#include "game.h"
extern int read_file_to_array(const char* filename, uint8_t* buffer, uint32_t max_size);
extern bac bg;
lv_obj_t * scr_menu; 
lv_obj_t * scr_game;
extern void screen_cb(lv_event_t*e);
int main()
{
		sys_init();
		
		rcu_periph_clock_enable(RCU_GPIOA);
		gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
		gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_60MHZ, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
		gpio_bit_reset(GPIOA, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
		
		lv_init();
		lv_port_disp_init();
		lv_port_indev_init();
	  game_init();
		

    lv_obj_add_event_cb(scr_game,screen_cb,LV_EVENT_SCREEN_LOADED,NULL);//注册屏幕加载回调
		while(1){
		lv_task_handler();    
    delay_us(2000);      

    
}
	}
void game_init(){ //游戏初始化
	  scr_menu = lv_obj_create(NULL); 
    scr_game = lv_obj_create(NULL);
   	

  lv_scr_load(scr_menu);
	game_bg_load(scr_menu);
  game_btn_start_load();
  game_btn_choose_load();
	game_btn_level_load();
	game_btn_theme_default_load();
	game_btn_theme_ice_load();
	game_btn_theme_load();
	game_btn_mode_load();
	game_btn_time_load();
	game_btn_step_load();
	game_btn_exit_load(scr_menu);
	game_init_fall_system();
	game_btn_clear_score_load();
	game_btn_help_load();
}
