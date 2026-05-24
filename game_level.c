#include "game.h"

uint16_t game_time =0;
uint16_t game_step =0;
uint16_t game_goal =0;
uint16_t game_level=0;//取值1~5关
lv_obj_t * btn_level[5];

extern bool game_mode;

void swap_cell_types(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2){
    if (!coord_map[x1][y1]||!coord_map[x2][y2]){
        return;
    }
    cell_type temp=coord_map[x1][y1]->type;
    coord_map[x1][y1]->type=coord_map[x2][y2]->type;
    coord_map[x2][y2]->type=temp;
}

bool game_level_map[5][GRID_COLS][GRID_ROWS]={   //游戏地图
    //第一关
    {
        {1,1,1,1,1,1,1},//左下角
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1}//右下角
    },
    //第二关
    {
        {0,0,1,1,1,0,0},//左下角
        {0,0,1,1,1,0,0},
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1},
        {0,0,1,1,1,0,0},
        {0,0,1,1,1,0,0}//右下角
    },
    //第三关
    {
        {1,1,1,1,1,1,1},//左下角
        {1,1,1,1,1,1,1},
        {1,0,1,1,1,0,1},
        {1,0,1,1,1,0,1},
        {1,0,1,1,1,0,1},
        {1,0,1,1,1,0,1},
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1}//右下角
    },
    //第四关
    {
        {1,1,1,1,1,1,1},//左下角
        {1,1,1,1,1,1,1},
        {1,1,0,1,0,1,1},
        {1,1,1,0,1,1,1},
        {1,1,1,0,1,1,1},
        {1,1,0,1,0,1,1},
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1}//右下角
    },
    //第五关
    {
        {0,1,1,1,1,1,0},//左下角
        {1,0,1,1,1,0,1},
        {1,1,0,1,0,1,1},
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1},
        {1,1,0,1,0,1,1},
        {1,0,1,1,1,0,1},
        {0,1,1,1,1,1,0}//右下角
    }
};

void game_level_data_init(){
    switch (game_level){
        case 1:
            game_step=30;
            game_time=61;
            game_goal=1000;
            break;
        case 2:
            game_step=30;
            game_time=71;
            game_goal=1200;
            break;
        case 3:
            game_step=35;
            game_time=81;
            game_goal=1400;
            break;
        case 4:
            game_step=40;
            game_time=91;
            game_goal=1500;
            break;
        case 5:
            game_step=40;
            game_time=101;
            game_goal=1600;
            break;
    }



}
bool deadlock_det(){  //用于检测死局。返回true则无法继续消除。
    
    for(uint8_t y = 0; y < GRID_ROWS; y++) {
        for(uint8_t x = 0; x < GRID_COLS; x++) {
            if (!coord_map[x][y])   //空的
                continue;
            
            if (x<=GRID_COLS-2&&coord_map[x+1][y]){
                swap_cell_types(x,y,x+1,y);
                if (game_check_clear())//向右可消除
                {
                    swap_cell_types(x,y,x+1,y);
                    return false;
                }
                swap_cell_types(x,y,x+1,y);
            }
            
            if (y<=GRID_ROWS-2&&coord_map[x][y+1]){
                swap_cell_types(x,y,x,y+1);
                if (game_check_clear())//向下可消除
                {
                    swap_cell_types(x,y,x,y+1);
                    return false;
                }
                swap_cell_types(x,y,x,y+1);
            }
        }
    }
    return true;
}
void game_deadlock(){  //触发死局时执行
    if (game_over==1){  
        return;
    }
    if (game_mode==0){
        game_time+=4;
    }
    for(uint8_t y = 0; y < GRID_ROWS; y++) {
        for(uint8_t x = 0; x < GRID_COLS; x++) {
            if (!coord_map[x][y])   //空的
                continue;
            if(coord_map[x][y]->img) {
                lv_obj_add_flag(coord_map[x][y]->img,LV_OBJ_FLAG_HIDDEN);
				lv_obj_invalidate(coord_map[x][y]->img);
            }
            coord_map[x][y]->type=DEL;
        }
    }
    game_refill(NULL);
}

