#include "game.h"

uint16_t game_time =0;
uint16_t game_step =0;
uint16_t game_goal =0;
uint16_t game_level=0;//取值1~5关
lv_obj_t * btn_level[5];


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
            game_goal=1500;
            break;
        case 3:
            game_step=35;
            game_time=81;
            game_goal=2100;
            break;
        case 4:
            game_step=40;
            game_time=91;
            game_goal=2600;
            break;
        case 5:
            game_step=40;
            game_time=101;
            game_goal=3200;
            break;
    }



}
