#include "game.h"

ItemType cur_use_item = ITEM_NONE;
extern lv_obj_t *btn_bomb;
extern lv_obj_t *btn_row;
extern lv_obj_t *btn_col;
extern uint8_t clear_flag[GRID_COLS][GRID_ROWS];
extern state status;
uint8_t item_bomb_used = 0;
uint8_t item_row_used  = 0;
uint8_t item_col_used  = 0;
void item_bomb_effect(uint8_t x,uint8_t y)
{
    // 自身+上下左右4格标记消
    clear_flag[x][y] = 1;
    if(x>0) clear_flag[x-1][y] = 1;
    if(x<GRID_COLS-1) clear_flag[x+1][y] = 1;
    if(y>0) clear_flag[x][y-1] = 1;
    if(y<GRID_ROWS-1) clear_flag[x][y+1] = 1;
		 item_bomb_used = 1;

}

void item_row_clear(uint8_t row)  //整行消除
{

    for(uint8_t i=0;i<GRID_COLS;i++)
    {
        clear_flag[i][row] = 1;
    }
		item_row_used  = 1;
}

void item_col_clear(uint8_t col)  //整列消除
{
    for(uint8_t j=0;j<GRID_ROWS;j++)
    {
        clear_flag[col][j] = 1;
    }
		item_col_used=1;
}

void tool_check( ){
    if (status!=NORMAL){
        if (btn_item_bomb && btn_item_col && btn_item_row){
            if (!item_bomb_used){
                lv_obj_clear_flag(btn_item_bomb, LV_OBJ_FLAG_CLICKABLE); // 按钮变灰不可点
			    lv_obj_set_style_bg_color(btn_item_bomb, lv_color_hex(0x666666), LV_PART_MAIN);
            }
            if (!item_col_used){
                lv_obj_clear_flag(btn_item_col, LV_OBJ_FLAG_CLICKABLE); 
			    lv_obj_set_style_bg_color(btn_item_col, lv_color_hex(0x666666), LV_PART_MAIN);
            }
            
            if (!item_row_used){
                lv_obj_clear_flag(btn_item_row, LV_OBJ_FLAG_CLICKABLE); 
			    lv_obj_set_style_bg_color(btn_item_row, lv_color_hex(0x666666), LV_PART_MAIN); 
            }
            
        }
    }
    else if (btn_item_bomb && btn_item_col && btn_item_row) {
        if (!item_bomb_used){
        lv_obj_add_flag(btn_item_bomb, LV_OBJ_FLAG_CLICKABLE); // 按钮可点
        lv_obj_set_style_bg_color(btn_item_bomb, lv_color_hex(0xFF4757), LV_PART_MAIN);
        }
        if (!item_col_used){
        lv_obj_add_flag(btn_item_col, LV_OBJ_FLAG_CLICKABLE); 
        lv_obj_set_style_bg_color(btn_item_col, lv_color_hex(0x20B620), LV_PART_MAIN);
        }
        if (!item_row_used){
        lv_obj_add_flag(btn_item_row, LV_OBJ_FLAG_CLICKABLE); 
        lv_obj_set_style_bg_color(btn_item_row, lv_color_hex(0x3742FA), LV_PART_MAIN); 
        }       
    }
    else
    return;
}
