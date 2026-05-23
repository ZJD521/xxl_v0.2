#include "game.h"

extern sqr cell[GRID_COLS][GRID_ROWS];  
extern lv_img_dsc_t cell_struct[5];
extern sqr* coord_map[GRID_COLS][GRID_ROWS] ;  
uint8_t clear_flag[GRID_COLS][GRID_ROWS] = {0};



uint8_t game_check_clear(void) {  //消除检测，结果写入clear_flag，标记要被删除的格子
    uint8_t ret = 0;
    cell_type t;
    
    // 重置所有消除标记
    for(uint8_t y = 0; y < GRID_ROWS; y++) {
        for(uint8_t x = 0; x < GRID_COLS; x++) {
            clear_flag[x][y] = 0;
        }
    }
    
    // 检查水平方向
    for(uint8_t y = 0; y < GRID_ROWS; y++) {
        for(uint8_t x = 0; x < GRID_COLS - 2; x++) {
            // 边界检查
            if(!coord_map[x][y] || !coord_map[x+1][y] || !coord_map[x+2][y]) continue;
            
            t = coord_map[x][y]->type;
            if(t == DEL) continue;
            
            // 检查3个连续相同
            if(coord_map[x+1][y]->type == t && coord_map[x+2][y]->type == t) {
                // 标记这3个
                clear_flag[x][y] = 1;
                clear_flag[x+1][y] = 1;
                clear_flag[x+2][y] = 1;
                ret = 1;
                
                // 检查是否超过3个
                uint8_t count = 3;
                for(uint8_t i = x+3; i < GRID_COLS; i++) {
                    if(!coord_map[i][y]) break;
                    if(coord_map[i][y]->type == t) {
                        clear_flag[i][y] = 1;
                        count++;
                    } else {
                        break; // 遇到不同类型的方块，停止检查
                    }
                }
                
              
            }
        }
    }
    
    // 检查垂直方向
    for(uint8_t x = 0; x < GRID_COLS; x++) {
        for(uint8_t y = 0; y < GRID_ROWS - 2; y++) {
            // 边界检查
            if(!coord_map[x][y] || !coord_map[x][y+1] || !coord_map[x][y+2]) continue;
            
            t = coord_map[x][y]->type;
            if(t == DEL) continue;
            
            if(coord_map[x][y+1]->type == t && coord_map[x][y+2]->type == t) {
                clear_flag[x][y] = 1;
                clear_flag[x][y+1] = 1;
                clear_flag[x][y+2] = 1;
                ret = 1;
                
                uint8_t count = 3;
                for(uint8_t i = y+3; i < GRID_ROWS; i++) {
                    if(!coord_map[x][i]) break;
                    if(coord_map[x][i]->type == t) {
                        clear_flag[x][i] = 1;
                        count++;
                    } else {
                        break; // 遇到不同类型的方块，停止检查
                    }
                }
                
               
            }
        }
    }
    
  
    
    return ret;
}


void game_do_clear(lv_timer_t* timer) {  //消除执行
	if (game_over == 1) { //熔断判断
        if(timer) lv_timer_del(timer);
        return;
    }
	//在所有需要check的地方已经配套调用，此处直接执行消除
    for(uint8_t y = 0; y < GRID_ROWS; y++) {
        for(uint8_t x = 0; x < GRID_COLS; x++) {
            if (!coord_map[x][y])   //空的
                continue;
            if(clear_flag[x][y] && coord_map[x][y]) {   //有东西并且要被消除
				if(clear_flag[x][y] && coord_map[x][y] && game_over == 0)
                {
                   game_score += 10;

                    // 刷新当前得分
                   char buf[20];
                   sprintf(buf, "Score:%d", game_score);
                   lv_label_set_text(label_score, buf);
                 }
                // 先删除图像，再设置类型
                if(coord_map[x][y]->img) {
                    lv_obj_add_flag(coord_map[x][y]->img,LV_OBJ_FLAG_HIDDEN);
					lv_obj_invalidate(coord_map[x][y]->img);
                }
                coord_map[x][y]->type = DEL;   //标记被删除的地方为 del
                
                
            }
						
        }
    }
		game_fall_all();    //标记为DEL后触发下落
  }
  
	
	







