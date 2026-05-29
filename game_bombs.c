#include "game.h"
extern sqr cell[GRID_COLS][GRID_ROWS];  
extern lv_img_dsc_t cell_struct[5];
extern sqr* coord_map[GRID_COLS][GRID_ROWS] ;  
extern uint8_t clear_flag[GRID_COLS][GRID_ROWS];

BombPos bombqueue[GRID_COLS * GRID_ROWS];
uint16_t q_next_out = 0;
uint16_t q_next_in = 0;
uint8_t inQueue[GRID_COLS][GRID_ROWS] = {0}; //0:没有在队列中；1：在队列中

void bomb_creat(sqr * cell0,bomb_type tag){
    lv_obj_set_style_shadow_width(cell0->img,10,0);
    switch (tag){
        case BOMB_ROW:
            lv_obj_set_style_shadow_color(cell0->img,lv_color_hex(0x3742FA),0);
            break;
        case BOMB_COL:
            lv_obj_set_style_shadow_color(cell0->img,lv_color_hex(0x20B620),0);
            break;
        case BOMB_CENTER:
            lv_obj_set_style_shadow_color(cell0->img,lv_color_hex(0xFF4757),0);
            break;
        default:
            break;
    }
    
    lv_obj_set_style_shadow_spread(cell0->img,2,0);
}

void enqueue(uint8_t x, uint8_t y)
{
    if (inQueue[x][y])
        return;
    bombqueue[q_next_in].x = x;
    bombqueue[q_next_in].y = y;
    inQueue[x][y] = 1;
    q_next_in++;
}

uint8_t dequeue(uint8_t *x, uint8_t *y)
{
    if (q_next_out >= q_next_in)
        return 0;
    *x = bombqueue[q_next_out].x;
    *y = bombqueue[q_next_out].y;
    inQueue[*x][*y] = 0;
    q_next_out++;
    return 1;
}
void queue_clear(void)
{
    q_next_out = 0;
    q_next_in = 0;
    for (uint8_t i = 0; i < GRID_COLS; i++)
    {
        for (uint8_t j = 0; j < GRID_ROWS; j++)
        {
            inQueue[i][j] = 0;
        }
    }
}

