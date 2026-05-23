#include "game.h"
#include "stdlib.h"

 sqr cell[GRID_COLS][GRID_ROWS];
 lv_obj_t *frame[GRID_COLS][GRID_ROWS];
extern lv_img_dsc_t cell_struct[5];
extern uint16_t game_level;
extern bool game_level_map[5][8][7];

void game_sqr_field_init(lv_obj_t* scr)  //游戏棋盘初始化
{
    int col, row;
    game_init_coord_map();    //清空地图
    for(col=0; col<GRID_COLS; col++)
    {
        for(row=0; row<GRID_ROWS; row++)
        {
            cell[col][row].type=rand() % 5;
        }
    }
    for(col=0; col<GRID_COLS; col++)
    {
        for(row=0; row<GRID_ROWS; row++)
        {
            cell_type t=cell[col][row].type;
            cell[col][row].type=safe_type(col,row,t);
        }
    }
    for(col=0; col<GRID_COLS; col++)
    {
        for(row=0; row<GRID_ROWS; row++)
        {
            cell_type t=cell[col][row].type;
            cell[col][row].type=safe_type(col,row,t); //检查两遍防止三连
        }
    }

    for(col=0; col<GRID_COLS; col++)  //把地图该空的地方空出来
    {
        for(row=0; row<GRID_ROWS; row++)
        {
            if (game_level_map[game_level-1][col][row]==0)
            {
                coord_map[col][row]=NULL;
                continue;
            }
            // 设置格子参数
            
            frame[col][row] = lv_obj_create(scr);  // 创建格子背景
            lv_obj_set_size(frame[col][row], CELL_LENG, CELL_LENG); // 大小：正方形
            lv_obj_set_style_border_color(frame[col][row], lv_color_hex(0x888888), 0); // 边框灰色
            lv_obj_set_style_border_width(frame[col][row], 1, 0); // 边框宽度1
            lv_obj_set_style_border_opa(frame[col][row], LV_OPA_50, 0); // 边框半透明
            lv_obj_set_style_bg_color(frame[col][row], lv_color_hex(0x333333), 0); // 背景深灰
            lv_obj_set_style_bg_opa(frame[col][row], LV_OPA_30, 0); // 背景半透明
            lv_obj_clear_flag(frame[col][row], LV_OBJ_FLAG_SCROLLABLE); // 禁止滚动
            lv_obj_set_pos(frame[col][row], FIELD_X + col*CELL_LENG, FIELD_Y + row*CELL_LENG); // 摆放位置
            lv_obj_clear_flag(frame[col][row], LV_OBJ_FLAG_CLICKABLE); // 格子不能点击
            lv_obj_move_to_index(frame[col][row],1); // 放在下层

            
          

            // 方块图片
            cell[col][row].img = lv_img_create(scr);
            lv_img_set_src(cell[col][row].img, &cell_struct[cell[col][row].type]);
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
		game_btn_item_bomb_load();
    game_btn_item_row_load();
    game_btn_item_col_load();
}

//检查是否会形成3个连续（按数组下标查邻居，开局时与逻辑格一致）
static uint8_t is_bad(uint8_t x, uint8_t y, cell_type t)
{
    // 左两个
    if(x >= 2&&coord_map[x-1][y]&&coord_map[x-2][y])
        if(coord_map[x-1][y]->type == t && coord_map[x-2][y]->type == t )
            return 1;
    
    // 右两个
    if(x <= 5&&coord_map[x+1][y]&&coord_map[x+2][y])
        if(coord_map[x+1][y]->type == t && coord_map[x+2][y]->type == t )
            return 1;

    // 上两个
    if(y >= 2&&coord_map[x][y-1]&&coord_map[x][y-2])
        if(coord_map[x][y-1]->type == t && coord_map[x][y-2]->type == t )
            return 1;

     // 下两个
     if(y <= 4&&coord_map[x][y+1]&&coord_map[x][y+2])
     if(coord_map[x][y+1]->type == t && coord_map[x][y+2]->type == t )
         return 1;

    // 左1 + 当前 + 右1
    if(x >= 1 && x < GRID_COLS-1&&coord_map[x-1][y]&&coord_map[x+1][y])
        if(coord_map[x-1][y]->type == t && coord_map[x+1][y]->type == t )
            return 1;

    // 上1 + 当前 + 下1
    if(y >= 1 && y < GRID_ROWS-1&&coord_map[x][y-1]&&coord_map[x][y+1])
        if(coord_map[x][y-1]->type == t && coord_map[x][y+1]->type == t )
            return 1;

   

    return 0;
}

//生成安全颜色
cell_type safe_type(uint8_t x, uint8_t y,cell_type t)
{
    
    int try = 0;  //尝试换一个颜色

    while(try<50)
    {
			
		if(!is_bad(x,y,t)) return t;   //如果不是bad，就用它
        else 
            t=rand()%5;
        try++;
    }

    return (t+1)%5;
}

