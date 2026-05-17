#include "game.h"
#include "stdlib.h"

 sqr cell[GRID_COLS][GRID_ROWS];
 lv_obj_t *frame[GRID_COLS][GRID_ROWS];
extern lv_img_dsc_t cell_struct[5];

// 检查是否会形成 3 个连续
static uint8_t is_bad(uint8_t x, uint8_t y, cell_type t)
{
    // 左两个
    if(x >= 2)
        if(cell[x-1][y].type == t && cell[x-2][y].type == t)
            return 1;

    // 上两个
    if(y >= 2)
        if(cell[x][y-1].type == t && cell[x][y-2].type == t)
            return 1;

    // 左1 + 当前 + 右1
    if(x >= 1 && x < GRID_COLS-1)
        if(cell[x-1][y].type == t && cell[x+1][y].type == t)
            return 1;

    // 上1 + 当前 + 下1
    if(y >= 1 && y < GRID_ROWS-1)
        if(cell[x][y-1].type == t && cell[x][y+1].type == t)
            return 1;

    // 防 L 型（2×2 里 3 个同色）
    if(x>0 && y>0)
    {
        int cnt = 0;
        if(cell[x-1][y].type == t) cnt++;
        if(cell[x][y-1].type == t) cnt++;
        if(cell[x-1][y-1].type == t) cnt++;
        if(cnt >= 2) return 1;
    }

    return 0;
}

// 生成安全颜色
cell_type safe_type(uint8_t x, uint8_t y)
{
    cell_type t;
    int try = 0;

    while(try < 30)
    {
        t = rand() % 5;
        if(!is_bad(x,y,t)) return t;
        try++;
    }

    return (t+1)%5;
}


void game_sqr_field_init(lv_obj_t* scr)  //游戏棋盘初始化
{
    int col, row;

    for(row=0; row<GRID_ROWS; row++)
    {
        for(col=0; col<GRID_COLS; col++)
        {
            // 背景框
            
            frame[col][row] = lv_obj_create(scr);
            lv_obj_set_size(frame[col][row], CELL_LENG, CELL_LENG);
            lv_obj_set_style_border_color(frame[col][row], lv_color_hex(0x888888), 0);
            lv_obj_set_style_border_width(frame[col][row], 1, 0);
            lv_obj_set_style_border_opa(frame[col][row], LV_OPA_50, 0);
            lv_obj_set_style_bg_color(frame[col][row], lv_color_hex(0x333333), 0);
            lv_obj_set_style_bg_opa(frame[col][row], LV_OPA_30, 0);
            lv_obj_clear_flag(frame[col][row], LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_pos(frame[col][row], FIELD_X + col*CELL_LENG, FIELD_Y + row*CELL_LENG);
            lv_obj_clear_flag(frame[col][row], LV_OBJ_FLAG_CLICKABLE);
      			lv_obj_move_to_index(frame[col][row],1);

            
            cell_type t = safe_type(col, row);
            cell[col][row].type = t;

            // 方块图片
            cell[col][row].img = lv_img_create(scr);
            lv_img_set_src(cell[col][row].img, &cell_struct[t]);
            lv_obj_set_pos(cell[col][row].img, FIELD_X + col*CELL_LENG, FIELD_Y + row*CELL_LENG);

          
            lv_obj_add_flag(cell[col][row].img, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_move_foreground(cell[col][row].img);
            lv_obj_set_user_data(cell[col][row].img, &cell[col][row]);
						lv_obj_move_to_index(cell[col][row].img,GRID_ROWS*row+col+GRID_COLS*GRID_ROWS);
            cell[col][row].x = col;
            cell[col][row].y = row;
            lv_obj_add_event_cb(cell[col][row].img, cell_cb, LV_EVENT_ALL, &cell[col][row]);
						
        }
    }
		game_init_coord_map();  
}
