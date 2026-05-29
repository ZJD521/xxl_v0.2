#include "game.h"
extern uint8_t clear_flag[GRID_COLS][GRID_ROWS];
extern sqr* coord_map[GRID_COLS][GRID_ROWS]; 
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

void do_bomb (sqr * cell0){
    if (game_over == 1) { //熔断判断
        return;
    }
    bomb_type t=cell0->bomb;
    uint8_t x0=cell0->x;
    uint8_t y0=cell0->y;
    switch (t){
        case BOMB_NONE:
            return;
        case BOMB_ROW:
            for (uint8_t i=0;i<GRID_COLS;i++){
                if (coord_map[i][y0])
                    clear_flag[i][y0]=1;
            }
            
            break;
        case BOMB_COL:
            for (uint8_t j=0;j<GRID_ROWS;j++){
                if (coord_map[x0][j])
                    clear_flag[x0][j]=1;
            }
            break;
        default:
            break;
    }
		return;
}


