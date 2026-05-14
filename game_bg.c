#include "drivers.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
#include "game.h"

bac bg ;
extern lv_obj_t * scr_menu; 
extern lv_obj_t * scr_game;
extern int read_file_to_array(const char* filename, uint8_t* buffer, uint32_t max_size);
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
	  read_file_to_array("0:/bg_default.bin",bg_buffer,BG_SIZE+4);}//读取
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
	  lv_obj_move_background(bg.img);         //移动到底层
}

void screen_cb(lv_event_t*e)
{
    game_bg_load(scr_game);
    game_score_label_create(scr_game);
    game_init_start();

    // 启动倒计时
    lv_timer_create(game_timer_cb, 1000, NULL);

    game_sqr_src_load();
    game_sqr_field_init(scr_game);
}
