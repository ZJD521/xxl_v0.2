#include "game.h"

ItemType cur_use_item = ITEM_NONE;
extern lv_obj_t *btn_bomb;
extern lv_obj_t *btn_row;
extern lv_obj_t *btn_col;
extern uint8_t clear_flag[GRID_COLS][GRID_ROWS];
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

