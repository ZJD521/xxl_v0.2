#include "game.h"

void game_sqr_src_load();

uint8_t *cell_buffer[5];
lv_img_dsc_t cell_struct[5];    //方块图片数据结构体定义                      

extern int read_file_to_array(const char* filename, uint8_t* buffer, uint32_t max_size);
extern bac bg;

void game_sqr_src_load(){       //根据主题读取方块的五种图片
    for(int i=0;i<5;i++){
	    cell_buffer[i]=sdram_malloc(CELL_SIZE);   
		}
		if(bg.theme==DEFAULT){      //默认皮肤
		read_file_to_array("0:/default_red.bin",cell_buffer[0],CELL_SIZE+4);
		read_file_to_array("0:/default_yellow.bin",cell_buffer[1],CELL_SIZE+4);
		read_file_to_array("0:/default_green.bin",cell_buffer[2],CELL_SIZE+4);
		read_file_to_array("0:/default_blue.bin",cell_buffer[3],CELL_SIZE+4);
		read_file_to_array("0:/default_purple.bin",cell_buffer[4],CELL_SIZE+4);
		}
    else if(bg.theme==ICE){   //主题皮肤
		read_file_to_array("0:/theme_red.bin",cell_buffer[0],CELL_SIZE+4);
		read_file_to_array("0:/theme_yellow.bin",cell_buffer[1],CELL_SIZE+4);
		read_file_to_array("0:/theme_green.bin",cell_buffer[2],CELL_SIZE+4);
		read_file_to_array("0:/theme_blue.bin",cell_buffer[3],CELL_SIZE+4);
		read_file_to_array("0:/theme_purple.bin",cell_buffer[4],CELL_SIZE+4);
		}
		else{                        //未选择皮肤，则使用默认皮肤
		read_file_to_array("0:/default_red.bin",cell_buffer[0],CELL_SIZE+4);
		read_file_to_array("0:/default_yellow.bin",cell_buffer[1],CELL_SIZE+4);
		read_file_to_array("0:/default_green.bin",cell_buffer[2],CELL_SIZE+4);
		read_file_to_array("0:/default_blue.bin",cell_buffer[3],CELL_SIZE+4);
		read_file_to_array("0:/default_purple.bin",cell_buffer[4],CELL_SIZE+4);
		}
		for(int i=0;i<5;i++){       //录入方块图片数据结构体
		  cell_struct[i].header.always_zero = 0;                  
      cell_struct[i].header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;  
      cell_struct[i].header.w = CELL_LENG;                          
      cell_struct[i].header.h = CELL_LENG;                         
      cell_struct[i].header.reserved = 0;                     
      cell_struct[i].data_size = CELL_SIZE;               
      cell_struct[i].data = cell_buffer[i] + 4; 
		}

}
