#include "drivers.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
#include "game.h"
lv_timer_t * gametime;
bac bg ;
extern lv_obj_t * scr_menu; 
extern lv_obj_t * scr_game;
extern lv_obj_t * btn_exit;
extern int read_file_to_array(const char* filename, uint8_t* buffer, uint32_t max_size);  //要读的；我的地方；最大容量
lv_img_dsc_t bg_struct;    //背景图片数据结构体定义                      
uint8_t *bg_buffer=NULL;   //准备读取

void game_bg_load(lv_obj_t *scr ){       //加载背景
	
	  if(bg_buffer != NULL) {
        sdram_free(bg_buffer);
        bg_buffer = NULL; // 防止野指针
    }
		
	  bg.img = lv_img_create(scr);
	  bg_buffer=sdram_malloc(BG_SIZE);
		
		if (bg.theme==DEFAULT){
	  read_file_to_array("0:/bg_default.bin",bg_buffer,BG_SIZE+4);}//读取；＋4跳过头文件
	  else if(bg.theme==ICE){
		read_file_to_array("0:/bg_theme.bin",bg_buffer,BG_SIZE+4);}
		else{
		read_file_to_array("0:/bg_default.bin",bg_buffer,BG_SIZE+4);}
		
    bg_struct.header.always_zero = 0;                  //背景图参数
    bg_struct.header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;  
    bg_struct.header.w = BG_W;                          
    bg_struct.header.h = BG_H;                         
    bg_struct.header.reserved = 0;                     
    bg_struct.data_size = BG_SIZE;               
    bg_struct.data = bg_buffer + 4; 
	
	  lv_img_set_src(bg.img,&bg_struct);       //导入
    lv_obj_align(bg.img,LV_ALIGN_CENTER,0,0);  //居中
	  lv_img_set_zoom(bg.img,1024);         //放大4倍
	  lv_obj_move_background(bg.img);         //移动到底层，默认屏蔽触摸
}

void screen_cb(lv_event_t*e)    //游戏回调
{
    game_fall_stop_all();       //新局开始前清下落链
    game_init_fall_system();
    game_bg_load(scr_game);
    game_score_label_create(scr_game);
    game_init_data();
    game_level_data_init();
    if(gametime != NULL) {
        lv_timer_del(gametime);
        gametime = NULL;
    }
    lv_obj_clear_flag(btn_exit,LV_OBJ_FLAG_HIDDEN);
  
      game_score_read();
    
    // 启动倒计时
    gametime = lv_timer_create(game_timer_cb, 1000, NULL);
    game_sqr_src_load();
    game_sqr_field_init(scr_game);
    clear_bomb();
}
