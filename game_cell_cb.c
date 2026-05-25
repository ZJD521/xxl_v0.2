#include "game.h"
extern sqr cell[GRID_COLS][GRID_ROWS];
sqr* coord_map[GRID_COLS][GRID_ROWS] = {NULL};//坐标-方块查找索引
state status=NORMAL;
extern bool game_mode;
extern bool game_level_map[5][8][7];
extern uint16_t game_step;
extern void item_bomb_effect(uint8_t x,uint8_t y);
extern void item_row_clear(uint8_t row);
extern void item_col_clear(uint8_t col);


void cell_cb(lv_event_t * e) {      //方块滑动回调
    lv_event_code_t code = lv_event_get_code(e); 
	  if(game_over) 
			return;
		if(status!=NORMAL)   //非正常状态直接退出
		  return;

    sqr* current_cell = (sqr*)lv_event_get_user_data(e); // 获取当前对象的数据指针 
    if (!coord_map[current_cell->x][current_cell->y]){  //如果数据是空的，不处理
        return;
    }
    
    static lv_point_t start_point;  // 保存起始点
    
	uint8_t x0 = current_cell->x; 
    uint8_t y0 = current_cell->y; 
	game_check_clear();
	if(cur_use_item != ITEM_NONE)
    {
        switch(cur_use_item)
        {
            case ITEM_BOMB:
                item_bomb_effect(x0,y0);
                break;
            case ITEM_ROW_CLEAR:
                item_row_clear(y0);
                break;
            case ITEM_COL_CLEAR:
                item_col_clear(x0);
                break;
            default:
                break;
        }
        cur_use_item = ITEM_NONE;
        game_do_clear(NULL);
        return;
    }

    if(code == LV_EVENT_PRESSED) { 
        lv_indev_t * indev = lv_indev_get_act();   
        if(indev) { 
            lv_indev_get_point(indev, &start_point); //录入起点
        } 
    } 
    else if(code == LV_EVENT_RELEASED) {    //手指松开，判断方向 
        
        lv_indev_t * indev = lv_indev_get_act(); 
        lv_point_t end_point;       
        
        if(indev) { 
            lv_indev_get_point(indev, &end_point);   //录入终点
            
            lv_coord_t diff_x = end_point.x - start_point.x;    
            lv_coord_t diff_y = end_point.y - start_point.y; //计算位移，diffx：水平；diffy：竖直
            

            // 获取当前坐标

            


			sqr*lat=NULL;
            if(abs(diff_y) < abs(diff_x)){        // 水平滑动 
                if(diff_x > 0 && x0 < GRID_COLS - 1) { 
                    // 向右交换
					lat=coord_map[x0+1][y0];
					if (lat){
						status=SWAPPING;
                        tool_check();
                      cell_swap_exec(current_cell, lat);}
                    else
                      return;
                    if(game_mode == true)
                    {
                        game_step--;
                    }				  
										  
					else
						return;
                } 
				else if(diff_x < 0 && x0 > 0) { 
                    // 向左交换
                    lat=coord_map[x0-1][y0];
					if (lat){
						status=SWAPPING;
                        tool_check();
                      cell_swap_exec(current_cell, lat);}
                    else
                        return;
                    if(game_mode == true)
                      {
                          game_step--;
                      }				  
					else
						return;
                }
            } 
			else {      // 垂直滑动
                if(diff_y > 0 && y0 < GRID_ROWS - 1) { //向下交换
                    lat=coord_map[x0][y0+1];
					if (lat){
						status=SWAPPING;
                        tool_check();
                      cell_swap_exec(current_cell, lat);}
                    else
                        return;
                    if(game_mode == true)
                      {
                          game_step--;
                      }					
					else
						return;
                } 
				else if(diff_y < 0 && y0 > 0) {       //向上交换
                    lat=coord_map[x0][y0-1];
					if (lat){
						status=SWAPPING;
                        tool_check();
                      cell_swap_exec(current_cell, lat);}
                    else
                        return; 
                    if(game_mode == true)
                      {
                          game_step--;
                      }					
					else
						return;
                }
         
            }
						
        } 
    } 
}

void cell_swap_x(sqr * cell_a , sqr * cell_b){  //横向交换
    ani* a=lv_mem_alloc(sizeof(ani));
	
	  a->cell_a=cell_a;
	  a->cell_b=cell_b;
	
	  lv_coord_t cell_a_x=lv_obj_get_x(a->cell_a->img);//获取坐标
    lv_coord_t cell_b_x=lv_obj_get_x(a->cell_b->img);
	
	  lv_obj_set_user_data(cell_a->img, cell_a);
    lv_obj_set_user_data(cell_b->img, cell_b);
	
	  lv_anim_t a_x;
    lv_anim_init(&a_x);
    lv_anim_set_var(&a_x, a->cell_a->img);
    lv_anim_set_exec_cb(&a_x, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_values(&a_x, cell_a_x, cell_b_x);
    lv_anim_set_time(&a_x, duration/2);
    lv_anim_set_path_cb(&a_x, lv_anim_path_bounce);	//固有动画格式
	
	  lv_anim_t b_x;
    lv_anim_init(&b_x);
    lv_anim_set_var(&b_x, a->cell_b->img);
    lv_anim_set_exec_cb(&b_x, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_values(&b_x, cell_b_x, cell_a_x);
    lv_anim_set_time(&b_x, duration/2);
    lv_anim_set_path_cb(&b_x, lv_anim_path_bounce);  	//固有动画格式
		
		lv_anim_set_user_data(&a_x, a);
		lv_anim_set_user_data(&b_x, a);
		lv_anim_set_ready_cb(&a_x, swap_ready_cb);  //动画播放结束回调注册
		lv_anim_set_ready_cb(&b_x, swap_ready_cb);
		
		lv_anim_start(&a_x);                //动画开始
    lv_anim_start(&b_x);

}
	
void cell_swap_y(sqr * cell_a , sqr * cell_b){  //纵向交换
    ani* a=lv_mem_alloc(sizeof(ani));
	  a->cell_a=cell_a;
	  a->cell_b=cell_b;
	
	  lv_coord_t cell_a_y=lv_obj_get_y(a->cell_a->img);//获取坐标
    lv_coord_t cell_b_y=lv_obj_get_y(a->cell_b->img);
	
	  lv_obj_set_user_data(cell_a->img, cell_a);
    lv_obj_set_user_data(cell_b->img, cell_b);
	
	  lv_anim_t a_y;
    lv_anim_init(&a_y);
    lv_anim_set_var(&a_y, a->cell_a->img);
    lv_anim_set_exec_cb(&a_y, (lv_anim_exec_xcb_t)lv_obj_set_y);        //固有动画格式
    lv_anim_set_values(&a_y, cell_a_y, cell_b_y);
    lv_anim_set_time(&a_y, duration/2);
    lv_anim_set_path_cb(&a_y, lv_anim_path_bounce);	
	
	  lv_anim_t b_y;
    lv_anim_init(&b_y);
    lv_anim_set_var(&b_y, a->cell_b->img);
    lv_anim_set_exec_cb(&b_y, (lv_anim_exec_xcb_t)lv_obj_set_y);           //固有动画格式
    lv_anim_set_values(&b_y, cell_b_y, cell_a_y);
    lv_anim_set_time(&b_y, duration/2);
    lv_anim_set_path_cb(&b_y, lv_anim_path_bounce);  	
		
		lv_anim_set_user_data(&a_y, a);
		lv_anim_set_user_data(&b_y, a);
		lv_anim_set_ready_cb(&a_y, swap_ready_cb);
		lv_anim_set_ready_cb(&b_y, swap_ready_cb);//动画播放结束回调注册
		
		lv_anim_start(&a_y);//动画开始
    lv_anim_start(&b_y);

}

void cell_swap_exec(sqr * cell_a , sqr * cell_b){   //交换图片位置和网格坐标

		if( abs(cell_a->x - cell_b->x) >= 1 )
			cell_swap_x(cell_a , cell_b);     //横向交换
		else if ( abs(cell_a->y - cell_b->y ) >= 1 )
			cell_swap_y(cell_a , cell_b );    //纵向交换
		else 
			return;
}




void swap_ready_cb(lv_anim_t * a) {   //交换回调（两路动画各触发一次）
    static uint8_t anim_count = 0; 
    static uint8_t swap_count = 1;   //弹回交换时跳过首轮回调
    
    if (swap_count == 0) {
        swap_count++;
			status=NORMAL;  /*bug修复 修复了连续无效交换时概率错位的问题
			或许根源在于anim被释放，导致第二次交换的回调函数无法被触发
			将游戏状态在此处设为可操作  效果意外的好*/
            tool_check();
        return;
    }
    
    anim_count++;
    if (anim_count >= 2) {   //两个方块都结束才继续
        anim_count = 0;
        ani * data = (ani *)lv_anim_get_user_data(a);   //拿信息

        // 找到两个方块在cell数组中的索引
        uint8_t i1 = 0, j1 = 0, i2 = 0, j2 = 0;
        bool found1 = false, found2 = false;
        
        for(uint8_t i = 0; i < GRID_COLS; i++) {
            for(uint8_t j = 0; j < GRID_ROWS; j++) {
                if(&cell[i][j] == data->cell_a) {
                    i1 = i; j1 = j; found1 = true;
                }
                if(&cell[i][j] == data->cell_b) {
                    i2 = i; j2 = j; found2 = true;
                }
            }
        }
        
        if(found1 && found2) {  //俩都找到了
            //  交换坐标
            swap_cell_coordinates(i1, j1, i2, j2);
            lv_obj_move_to_index(coord_map[i1][j1]->img, GRID_COLS * GRID_ROWS * 5);
            lv_obj_move_to_index(coord_map[i2][j2]->img, GRID_COLS * GRID_ROWS * 5 + 1); //调整动画层级，防止遮挡
					 
           
                if(game_check_clear()) {
                    game_do_clear(NULL);  //有效交换，进入消除
                    swap_count++; 
									
                } 
								else {
                    status=SWAPPING;                      //无效交换，弹回
                    tool_check();
                    swap_cell_coordinates(i2, j2, i1, j1);
                    swap_count = 0;
                    cell_swap_exec(data->cell_b, data->cell_a);

                }
            
						
        }
				lv_mem_free(data);
				
        if (status==NORMAL){
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
}


// 索引初始化
void game_init_coord_map(void) {
    for(uint8_t i = 0; i < GRID_COLS; i++) {
        for(uint8_t j = 0; j < GRID_ROWS; j++) {
            if (game_level_map[game_level-1][i][j]==0){
                coord_map[i][j]=NULL;
                continue;
            }
            coord_map[i][j] = &cell[i][j];  // 直接映射
            cell[i][j].x = i;  // 确保初始坐标正确
            cell[i][j].y = j;
        }
    }
}


void swap_cell_coordinates(uint8_t i1, uint8_t j1, uint8_t i2, uint8_t j2) {  //交换索引
    if (!coord_map[i1][j1]||!coord_map[i2][j2]){
        return;
    }
    // 保存旧坐标
    uint8_t old_x1 = cell[i1][j1].x;
    uint8_t old_y1 = cell[i1][j1].y;
    uint8_t old_x2 = cell[i2][j2].x;
    uint8_t old_y2 = cell[i2][j2].y;
    
    // 交换实际坐标值
    uint8_t temp_x = cell[i1][j1].x;
    uint8_t temp_y = cell[i1][j1].y;
    cell[i1][j1].x = cell[i2][j2].x;
    cell[i1][j1].y = cell[i2][j2].y;
    cell[i2][j2].x = temp_x;
    cell[i2][j2].y = temp_y;
    
    //  清除旧映射
    coord_map[old_x1][old_y1] = NULL;
    coord_map[old_x2][old_y2] = NULL;
    
    // 设置新映射
    coord_map[cell[i1][j1].x][cell[i1][j1].y] = &cell[i1][j1];
    coord_map[cell[i2][j2].x][cell[i2][j2].y] = &cell[i2][j2];
}
void clear_coord_map_at(uint8_t x, uint8_t y) {  //清除索引
    if(x < GRID_COLS && y < GRID_ROWS) {
        coord_map[x][y] = NULL;
    }
}

void update_coord_map_for_single_cell(sqr* cell, uint8_t old_x, uint8_t old_y) {  //更新索引
    //  清除旧位置
    clear_coord_map_at(old_x, old_y);
    
    // 设置新位置
    if(cell->x < GRID_COLS && cell->y < GRID_ROWS) {
        coord_map[cell->x][cell->y] = cell;
    }
}
