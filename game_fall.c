#include "game.h"

extern sqr cell[GRID_COLS][GRID_ROWS];

extern sqr* coord_map[GRID_COLS][GRID_ROWS]; 

extern state status;

extern lv_img_dsc_t cell_struct[5];

static uint16_t falling_cell_count = 0;   //当前下落动画数量

static lv_timer_t * fall_check_timer = NULL;  //下落完成检测定时器

static lv_timer_t * col_start_timer = NULL;   //错峰启动下一列定时器

static uint8_t next_fall_col = 0;

static uint8_t fall_all_active = 0;



//删除并清空下落检测定时器

static void fall_check_timer_del(void)

{

    if(fall_check_timer) {  //如果还在

        lv_timer_del(fall_check_timer);  //删掉

        fall_check_timer = NULL;

    }

}



//登记新的下落检测定时器

static void fall_check_timer_bind(lv_timer_t * timer)

{

	fall_check_timer_del();   //引用上面的删除定时器

    fall_check_timer = timer;   //创建新的

}



//判断棋盘是否还有空格需要重填（只是判断）

static uint8_t game_need_refill(void)

{

    for(uint8_t x = 0; x < GRID_COLS; x++) {

        for(int8_t y = GRID_ROWS - 1; y >= 0; y--) {

            if(coord_map[x][y] && coord_map[x][y]->type == DEL)  //有del，则需要填补

                return 1;

        }

    }

    return 0;

}



static void col_start_timer_del(void)  //方块消除定时器

{

    if(col_start_timer) {

        lv_timer_del(col_start_timer);

        col_start_timer = NULL;

    }

}



static void fall_all_continue_cb(lv_timer_t * t)//用于控制异步下落，延时下落

{

    col_start_timer = NULL;

    lv_timer_del(t);

    game_fall_all();

}

static void refill_continue_cb(lv_timer_t * t)//用于控制异步重填，延时填补

{

    col_start_timer = NULL;

    lv_timer_del(t);
    if (game_need_refill()){
    game_refill(NULL);}
    tool_check();

}

void game_fall_stop_all(void)   //停止下落链，清零计数，清空状态

{

    fall_check_timer_del();

    col_start_timer_del();

    falling_cell_count = 0;

    next_fall_col = 0;

    fall_all_active = 0;

}



void game_init_fall_system(void)     //初始化下落系统

{

	game_fall_stop_all();  //上面的函数

}



void game_fall_all(void) {   //全盘下落（错峰按列，最多两列同时在动）

    uint8_t x;  //当前在处理第几列

    uint8_t col_has_anim;  //这一列有没有方块在下落

    if(!fall_all_active) {  //处在下落状态

        status = FALLING;

        tool_check();

        falling_cell_count = 0;

        next_fall_col = 0;

        fall_all_active = 1;  

        fall_check_timer_bind(lv_timer_create(fall_complete_check, duration + 10, NULL));

        lv_timer_set_repeat_count(fall_check_timer, -1);

    }



    for(x = next_fall_col; x < GRID_COLS; x++) {  //一列一列处理

        uint8_t write_y = GRID_ROWS - 1;   

        col_has_anim = 0;



        for(int8_t read_y = write_y; read_y >= 0; read_y--) {  //从最底部开始填补
            if (!coord_map[x][write_y]){  //如果这个位置没有方块
                write_y--;  //标记落脚点
                continue;
            }
                if (!coord_map[x][read_y]){
                    write_y=read_y-1;
                    continue;
                }
            
            
            sqr* src_cell = coord_map[x][read_y];



            if(src_cell && src_cell->type != DEL) {

                if(read_y != write_y&&coord_map[x][write_y]->type==DEL&&coord_map[x][read_y+1]) {

                    lv_coord_t current_y = lv_obj_get_y(src_cell->img);

                    lv_coord_t target_y_pos = FIELD_Y + write_y * CELL_LENG;



                    if(current_y != target_y_pos) {

                        game_fall_one(src_cell, write_y);

                        col_has_anim = 1;

                    }

                }

                write_y--;

            }

        }



        if(col_has_anim)

            break;

    }



    if(x >= GRID_COLS) {

        fall_all_active = 0;

        next_fall_col = 0;

        return;

    }



    next_fall_col = x + 1;

    col_start_timer_del();

    col_start_timer = lv_timer_create(fall_all_continue_cb, duration / 2, NULL);

    lv_timer_set_repeat_count(col_start_timer, 1);

}



void game_fall_one(sqr* cell, uint8_t target_y) {  //下落单个方块



    lv_coord_t start_y = lv_obj_get_y(cell->img);

    lv_coord_t target_pos_y = FIELD_Y + target_y * CELL_LENG;
    if (!coord_map[cell->x][target_y] || !cell){
        return;
    }
    sqr * del = coord_map[cell->x][target_y];

    

    uint8_t old_x = cell->x;

    uint8_t old_y = cell->y;

    cell->y = target_y;

    if(old_x != cell->x || old_y != cell->y) {

        coord_map[old_x][old_y] = del;

        coord_map[cell->x][cell->y] = cell;

    }

    

    lv_obj_move_to_index(cell->img, GRID_COLS * GRID_ROWS * 5);

    lv_obj_move_to_index(del->img, GRID_COLS * GRID_ROWS * 5 + 1);

    lv_anim_t a;

    lv_anim_init(&a);

    lv_anim_set_var(&a, cell->img);

    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);

    lv_anim_set_values(&a, start_y, target_pos_y);

    lv_anim_set_time(&a, duration);

    lv_anim_set_path_cb(&a, lv_anim_path_linear);

    lv_anim_set_user_data(&a, cell);

    lv_anim_set_ready_cb(&a, fall_anim_ready_cb);

    

    falling_cell_count++;

    lv_anim_start(&a);

}



void fall_anim_ready_cb(lv_anim_t* a) {   //下落动画完成回调

    (void)a;

    if(falling_cell_count > 0)

        falling_cell_count--;

}



void game_refill(lv_timer_t* timer){  //重填所有空方块

    if (game_over == 1) { //熔断判断

        lv_timer_del(timer); 

        return;

    }

    falling_cell_count = 0;
    uint8_t is_refilling;
    for(uint8_t x = 0; x < GRID_COLS; x++) {
        is_refilling=0;
        for(int8_t read_y = GRID_ROWS - 1; read_y >= 0; read_y--){

            if (coord_map[x][read_y] && coord_map[x][read_y]->type == DEL){

                game_create_new_cell(x, read_y);
                is_refilling=1;
            }

        }
        if (is_refilling){
            break;
        }

    }

    fall_check_timer_bind(lv_timer_create(fall_complete_check, duration + 20, NULL));

    lv_timer_set_repeat_count(fall_check_timer, -1);

    col_start_timer_del();//异步重填
    

    col_start_timer = lv_timer_create(refill_continue_cb, duration / 2, NULL);

    lv_timer_set_repeat_count(col_start_timer, 1);


    
}



void game_create_new_cell(uint8_t x, uint8_t y) {  //生成单个重填方块
    if (!coord_map[x][y]){
        return;;
    }
    lv_obj_del(coord_map[x][y]->img);

    sqr* new_cell = coord_map[x][y];

    

    cell_type t = safe_type(x, y,rand()%5);

    

    new_cell->type = t;

    new_cell->x = x;

    new_cell->y = y;

    

    new_cell->img = lv_img_create(lv_scr_act());

    lv_img_set_src(new_cell->img, &cell_struct[t]);

    lv_obj_set_pos(new_cell->img, FIELD_X + x * CELL_LENG, FIELD_Y - CELL_LENG); //从屏幕上方开始

    lv_obj_add_flag(new_cell->img, LV_OBJ_FLAG_CLICKABLE);



    lv_obj_set_user_data(new_cell->img, new_cell);

    lv_obj_add_event_cb(new_cell->img, cell_cb, LV_EVENT_ALL, new_cell);

    lv_obj_move_foreground(new_cell->img);

    

    coord_map[x][y] = new_cell;

    game_fall_one(coord_map[x][y], y);

}



void fall_complete_check(lv_timer_t* timer) {  //下落/重填完成后的统一出口

    if(game_over == 1) { //熔断判断

        if(timer == fall_check_timer)

            fall_check_timer = NULL;

        lv_timer_del(timer); 

        return;

    }

    if(falling_cell_count > 0) {

        lv_timer_reset(timer);

        return;

    }



    if(timer == fall_check_timer)

        fall_check_timer = NULL;

    lv_timer_del(timer);



    if(game_need_refill()) {

        lv_timer_t * rtimer = lv_timer_create(game_refill, 10, NULL);

        lv_timer_set_repeat_count(rtimer, 1);

        return;

    }



    if(game_check_clear()) {

        lv_timer_t * ctimer = lv_timer_create(game_do_clear, 50, NULL);

        lv_timer_set_repeat_count(ctimer, 1);

    } else {
        
        status=NORMAL;
        status=FALLING;    /*暂时使用一个不可操作状态
                            以避免使用虚拟交换中的数据*/
        
        if (deadlock_det()){
             tool_check();
            game_deadlock();
            
        }
        else{
            status=NORMAL; //恢复可操作状态
            tool_check();
        }
    

    }

}


