#include "game.h"

extern sqr cell[GRID_COLS][GRID_ROWS];  
extern lv_img_dsc_t cell_struct[5];
extern sqr* coord_map[GRID_COLS][GRID_ROWS] ;  
uint8_t clear_flag[GRID_COLS][GRID_ROWS] = {0};//0:正常,1:待消除,2:生成炸弹



uint8_t game_check_clear(void) {  //消除检测，结果写入clear_flag，标记要被删除的格子
    uint8_t ret = 0;//得分点
    cell_type t;
    
    // 重置所有消除标记
    for(uint8_t y = 0; y < GRID_ROWS; y++) {
        for(uint8_t x = 0; x < GRID_COLS; x++) {
            clear_flag[x][y] = 0;
        }
    }
    
    // 检查水平方向
    for(uint8_t y = 0; y < GRID_ROWS; y++) {
        for(uint8_t x = 0; x < GRID_COLS - 2; x++) {
            // 边界检查
            if(!coord_map[x][y] || !coord_map[x+1][y] || !coord_map[x+2][y]) continue;
            
            t = coord_map[x][y]->type;
            if(t == DEL) continue;
            
            // 检查3个连续相同
            if(coord_map[x+1][y]->type == t && coord_map[x+2][y]->type == t ) {
                if (clear_flag[x][y] == 2 || clear_flag[x+1][y] == 2 || clear_flag[x+2][y] == 2)//跳过已生成的炸弹
                    continue;
                // 标记这3个
                clear_flag[x][y] = 1;
                clear_flag[x+1][y] = 1;
                clear_flag[x+2][y] = 1;
                ret += 1;

                //检查T形
                if (coord_map[x][y-1] && coord_map[x][y+1])
                if (coord_map[x][y-1]->type==t && coord_map[x][y+1]->type==t){
                    clear_flag[x][y]=2;
                    clear_flag[x][y-1]=1;
                    clear_flag[x][y+1]=1;
                    bomb_creat(coord_map[x][y],BOMB_CENTER);
                }

                //检查右上L形
                if (coord_map[x][y-1] && coord_map[x][y-2])
                if (coord_map[x][y-1]->type==t && coord_map[x][y-2]->type==t){
                    clear_flag[x][y]=2;
                    clear_flag[x][y-1]=1;
                    clear_flag[x][y-2]=1;
                    bomb_creat(coord_map[x][y],BOMB_CENTER);
                }

                //检查右下L形
                if (coord_map[x][y+1] && coord_map[x][y+2])
                if (coord_map[x][y+1]->type==t && coord_map[x][y+2]->type==t){
                    clear_flag[x][y]=2;
                    clear_flag[x][y+1]=1;
                    clear_flag[x][y+2]=1;
                    bomb_creat(coord_map[x][y],BOMB_CENTER);
                }
                

                // 检查是否超过3个
                uint8_t count = 3;
                for(uint8_t i = x+3; i < GRID_COLS; i++) {
                    if(!coord_map[i][y]) break;
                    if(coord_map[i][y]->type == t) {
                        clear_flag[i][y] = 1;
                        
                        count++;
                        ret+=1;
                    } 
                    else     
                        break; // 遇到不同类型的方块，停止检查
                    
                }
                if (count > 3){//多连生成炸弹
                    for (uint8_t j=x;j<=x+count;j++){
                        if (coord_map[x-1][y]){     //跳过已生成的炸弹
                            if (coord_map[x-1][y]->type==coord_map[x][y]->type){
                                if (clear_flag[x-1][y]==2)
                                    break;
                            }
                        }
                        if (coord_map[j][y]->moved==0&&j<x+count || clear_flag[j][y]==2){
                            continue;
                        }
                        else if(coord_map[j][y]->moved==0&&j==x+count){
                            clear_flag[x][y]=2;
                            bomb_creat(coord_map[x][y],BOMB_ROW);
                        }
                        else if(coord_map[j][y]->moved==1){
                            clear_flag[j][y]=2;
                            bomb_creat(coord_map[j][y],BOMB_ROW);
                            break;
                        }
                        else
                            break;
                        
                    }

                }
                
              
            }
        }
    }
    
    // 检查垂直方向
    for(uint8_t x = 0; x < GRID_COLS; x++) {
        for(uint8_t y = 0; y < GRID_ROWS - 2; y++) {
            // 边界检查
            if(!coord_map[x][y] || !coord_map[x][y+1] || !coord_map[x][y+2] ) continue;
            
            t = coord_map[x][y]->type;
            if(t == DEL) continue;
            
            if(coord_map[x][y+1]->type == t && coord_map[x][y+2]->type == t) {
                if (clear_flag[x][y] == 2 || clear_flag[x][y+1] == 2 || clear_flag[x][y+2] == 2)//跳过已生成的炸弹
                    continue;
                clear_flag[x][y] = 1;
                clear_flag[x][y+1] = 1;
                clear_flag[x][y+2] = 1;
                ret += 1;
                
                //检查T形
                if (coord_map[x-1][y] && coord_map[x+1][y])
                if (coord_map[x-1][y-1]->type==t && coord_map[x+1][y]->type==t){
                    clear_flag[x][y]=2;
                    clear_flag[x-1][y]=1;
                    clear_flag[x+1][y]=1;
                    bomb_creat(coord_map[x][y],BOMB_CENTER);
                }

                //检查左下L形
                if (coord_map[x-1][y] && coord_map[x-2][y])
                if (coord_map[x-1][y]->type==t && coord_map[x-2][y]->type==t){
                    clear_flag[x][y]=2;
                    clear_flag[x-1][y]=1;
                    clear_flag[x-2][y]=1;
                    bomb_creat(coord_map[x][y],BOMB_CENTER);
                }

                //检查左上L形
                if (coord_map[x-1][y+2] && coord_map[x-2][y+2])
                if (coord_map[x-1][y+2]->type==t && coord_map[x-2][y+2]->type==t){
                    clear_flag[x][y+2]=2;
                    clear_flag[x-1][y+2]=1;
                    clear_flag[x-2][y+2]=1;
                    bomb_creat(coord_map[x][y+2],BOMB_CENTER);
                }
                uint8_t count = 3;
                for(uint8_t i = y+3; i < GRID_ROWS; i++) {
                    if(!coord_map[x][i]) break;
                    if(coord_map[x][i]->type == t) {
                        clear_flag[x][i] = 1;
                        count++;
                        ret+=1;
                    } else {
                        break; // 遇到不同类型的方块，停止检查
                    }
                }
                if (count > 3){//多连生成炸弹
                    for (uint8_t j=y;j<=y+count;j++){
                        if (coord_map[x][y-1]){     //跳过已生成的炸弹
                            if (coord_map[x][y-1]->type==coord_map[x][y]->type){
                                if (clear_flag[x][y-1]==2)
                                    break;
                            }
                        }
                        if (coord_map[x][j]->moved==0&&j<y+count || clear_flag[x][j]==2){
                            continue;
                        }
                        else if(coord_map[x][j]->moved==0&&j==y+count){
                            clear_flag[x][y]=2;
                            bomb_creat(coord_map[x][y],BOMB_COL);
                        }
                        else if(coord_map[x][j]->moved==1){
                            clear_flag[x][j]=2;
                            bomb_creat(coord_map[x][j],BOMB_COL);
                            break;
                        }
                        else
                            break;
                        
                    }

                }
               
            }
        }
    }

    
    if (ret > 1)
        game_score += (ret*2);
    return ret;
}


void game_do_clear(lv_timer_t* timer) {  //消除执行
	if (game_over == 1) { //熔断判断
        if(timer) lv_timer_del(timer);
        return;
    }
	//在所有需要check的地方已经配套调用，此处直接执行消除
    for(uint8_t y = 0; y < GRID_ROWS; y++) {
        for(uint8_t x = 0; x < GRID_COLS; x++) {
            if (!coord_map[x][y])   //空的
                continue;
            if(clear_flag[x][y]==1 && coord_map[x][y]) {   //有东西并且要被消除
				if( game_over == 0)
                {
                   game_score += 10;

                    // 刷新当前得分
                   char buf[20];
                   sprintf(buf, "Score:%d", game_score);
                   lv_label_set_text(label_score, buf);
                 }
                // 先删除图像，再设置类型
                if(coord_map[x][y]->img) {
                    lv_obj_add_flag(coord_map[x][y]->img,LV_OBJ_FLAG_HIDDEN);
					lv_obj_invalidate(coord_map[x][y]->img);
                }
                coord_map[x][y]->type = DEL;   //标记被删除的地方为 del
                
                
            }
						
        }
    }
		game_fall_all();
  }
  
	
	







