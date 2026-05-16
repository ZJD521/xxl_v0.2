#include "game.h"
extern sqr cell[GRID_COLS][GRID_ROWS];
extern sqr* coord_map[GRID_COLS][GRID_ROWS]; 
extern state status;
extern lv_img_dsc_t cell_struct[5];
static uint16_t falling_cell_count = 0;
void game_fall_all(void) {
    status = FALLING;
    uint8_t find_count=0;
    for(uint8_t x = 0; x < GRID_COLS; x++) {
        uint8_t write_y = GRID_ROWS - 1;
        
        // 从底部向上扫描
        for(int8_t read_y = GRID_ROWS - 1; read_y >= 0; read_y--) {
            sqr* src_cell = coord_map[x][read_y];
            
            if(src_cell && src_cell->type != DEL) {
                if(read_y != write_y) {
                    // 需要下落
                    lv_coord_t current_y = lv_obj_get_y(src_cell->img);
                    lv_coord_t target_y_pos = FIELD_Y + write_y * CELL_LENG;
                    
                    // 只有在位置不同时才执行动画
                    if(current_y != target_y_pos) {
											  find_count++;
                        game_fall_one(src_cell, write_y);
                    }
                }
                write_y--;
            }
        }
        
        
    }
		
    
    // 使用定时器检查下落完成
    lv_timer_t* ftimer = lv_timer_create(fall_complete_check, duration+10, NULL);
    lv_timer_set_repeat_count(ftimer, 1);
		if (find_count==0){
			lv_timer_del(ftimer);
			status=FALLING;
		  lv_timer_t* rtimer = lv_timer_create(game_refill, duration*2+5, NULL);
      lv_timer_set_repeat_count(rtimer, 1);
		}
}

void game_fall_one(sqr* cell, uint8_t target_y) {

    lv_coord_t start_y = lv_obj_get_y(cell->img);
    lv_coord_t target_pos_y = FIELD_Y + target_y * CELL_LENG;
    sqr * del =coord_map[cell->x][target_y];
    
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
    
    // 增加下落计数器
    falling_cell_count++;
    
    lv_anim_start(&a);
}

void fall_anim_ready_cb(lv_anim_t* a) {  //下落动画回调
    
    // 减少下落计数器
    if(falling_cell_count > 1) {
        falling_cell_count--;
    }
		else if(falling_cell_count<=1){  //触发重填
		  lv_timer_t* timer = lv_timer_create(game_refill, duration*2+10, NULL);
      lv_timer_set_repeat_count(timer, 1);
	 }
		else
			return;
   
}

void game_refill(lv_timer_t* timer){  //重填函数
	if (game_over == 1) { // 熔断判断
        lv_timer_del(timer); 
        return;
    }
  falling_cell_count=0;
  for(uint8_t x = 0; x < GRID_COLS; x++) {
        for(int8_t read_y = GRID_ROWS - 1; read_y >= 0; read_y--){
					if (coord_map[x][read_y]->type==DEL){
					  game_create_new_cell(x,read_y);

					}
				}
		 }
		 lv_timer_t* timer1 = lv_timer_create(fall_complete_check, duration+20, NULL);
     lv_timer_set_repeat_count(timer1, 1);
}

void game_create_new_cell(uint8_t x, uint8_t y) {  //生成新方块
    //  创建新方块
	  lv_obj_del(coord_map[x][y]->img);
    sqr* new_cell = coord_map[x][y];
    
    //  生成安全类型
    cell_type t;
        t = safe_type( x,y);
        
       
    
    // 设置方块属性
    new_cell->type = t;
    new_cell->x = x;
    new_cell->y = y;
    
    //  创建UI
    new_cell->img = lv_img_create(lv_scr_act());
    lv_img_set_src(new_cell->img, &cell_struct[t]);
    lv_obj_set_pos(new_cell->img, FIELD_X + x * CELL_LENG, FIELD_Y - CELL_LENG); // 从屏幕上方开始
    lv_obj_add_flag(new_cell->img, LV_OBJ_FLAG_CLICKABLE);

    //  添加事件回调
    lv_obj_set_user_data(new_cell->img, new_cell);
    lv_obj_add_event_cb(new_cell->img, cell_cb, LV_EVENT_ALL, new_cell);
    lv_obj_move_foreground(new_cell->img);
    
    //  更新映射
    coord_map[x][y] = new_cell;
    
    //  执行下落动画
    game_fall_one(coord_map[x][y], y);
}
void fall_complete_check(lv_timer_t* timer) {
		if (game_over == 1) { // 熔断判断
        lv_timer_del(timer); 
        return;
    }
    // 如果还有下落的方块，继续等待
    if(falling_cell_count > 0) {
        lv_timer_reset(timer);
        return;
    }
    else{
    // 所有下落完成
    if(game_check_clear()) {
			  lv_timer_t* timer = lv_timer_create(game_do_clear, duration+5, NULL);
        lv_timer_set_repeat_count(timer, 1);
        game_do_clear(timer);
    } else {
        status = NORMAL;
    }
	}
}
void game_init_fall_system(void) {
    falling_cell_count = 0;
}
