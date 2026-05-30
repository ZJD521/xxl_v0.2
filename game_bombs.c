#include "game.h"
extern uint8_t clear_flag[GRID_COLS][GRID_ROWS];
extern sqr* coord_map[GRID_COLS][GRID_ROWS]; 
sqr * bomb_line[10]={NULL};
void bomb_creat(sqr * cell0,bomb_type tag){
    lv_obj_set_style_shadow_width(cell0->img,10,0);
    cell0->bomb=tag;
    switch (tag){
        case BOMB_ROW:
            lv_obj_set_style_shadow_color(cell0->img,lv_color_hex(0xFF4757),0);
            break;
        case BOMB_COL:
            lv_obj_set_style_shadow_color(cell0->img,lv_color_hex(0xFFC107),0);
            break;
        default:
            break;
    }
    
    lv_obj_set_style_shadow_spread(cell0->img,3,0);
}

void add_bomb(sqr * cell0){
    for (uint8_t i=0;i<10;i++){
        if (!bomb_line[i]){
            bomb_line[i]=cell0;
            break;
        }
            
    }
    
}

void clear_bomb(){
    for (uint8_t i=0;i<10;i++){
        bomb_line[i]=NULL;
    }
}
void do_bomb (uint8_t num){
    if (game_over == 1) { //熔断判断
        return;
    }
    for (uint8_t i=num;i<10;i++){
        if (!bomb_line[i]){
            continue;
        }
        bomb_type t=bomb_line[i]->bomb;
        uint8_t x0=bomb_line[i]->x;
        uint8_t y0=bomb_line[i]->y;
        switch (t){
            case BOMB_NONE:
                return;
            case BOMB_ROW:
                for (uint8_t j=0;j<GRID_COLS;j++){
                    if (coord_map[j][y0]){
                        clear_flag[j][y0]=0;
                        if( game_over == 0)
                        {
                           game_score += 10;
                         }
                        // 先删除图像，再设置类型
                        if(coord_map[j][y0]->img) {
                            
                            lv_obj_add_flag(coord_map[j][y0]->img,LV_OBJ_FLAG_HIDDEN);
                            coord_map[j][y0]->type = DEL;   //标记被删除的地方为 del
                        }
                        
                        
                        if (coord_map[j][y0]->bomb!=BOMB_NONE && coord_map[j][y0] != bomb_line[i]){
                            add_bomb(coord_map[j][y0]);
                            do_bomb(i+1);
                        }
                    }
                        
                }
                
                break;
            case BOMB_COL:
                for (uint8_t j=0;j<GRID_ROWS;j++){
                     if (coord_map[x0][j]){
                        clear_flag[x0][j]=0;
                        if( game_over == 0)
                        {
                           game_score += 10;
                        if(coord_map[x0][j]->img) {
                            
                            lv_obj_add_flag(coord_map[x0][j]->img,LV_OBJ_FLAG_HIDDEN);
                            coord_map[x0][j]->type = DEL;   //标记被删除的地方为 del                    
                        }
                        
                        
                        if (coord_map[x0][j]->bomb!=BOMB_NONE && coord_map[x0][j] != bomb_line[i]){
                            add_bomb(coord_map[x0][j]);
                            do_bomb(i+1);
                        } 
                    }
                        // 先删除图像，再设置类型
                        
                    }
                }
                break;
            default:
                break;
        }
    }

    
   
    
	clear_bomb();
}


