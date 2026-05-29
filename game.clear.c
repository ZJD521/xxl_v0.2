#include "game.h"

extern sqr cell[GRID_COLS][GRID_ROWS];  
extern lv_img_dsc_t cell_struct[5];
extern sqr* coord_map[GRID_COLS][GRID_ROWS] ;  
uint8_t clear_flag[GRID_COLS][GRID_ROWS] = {0};//0:正常,1:待消除,2:行炸弹 3：列炸弹



uint8_t game_check_clear(void)
{
    uint8_t ret = 0;
    cell_type t;

    // 重置标记：保留炸弹(2/3)，其余清空为0
    for (uint8_t y = 0; y < GRID_ROWS; y++)
    {
        for (uint8_t x = 0; x < GRID_COLS; x++)
        {
            if (clear_flag[x][y] < 2)
            {
                clear_flag[x][y] = 0;
            }
        }
    }

    //  初始化炸弹队列
    queue_clear();

    // 水平方向连续块检测 
    for (uint8_t y = 0; y < GRID_ROWS; y++)
    {
        uint8_t x = 0;
        while (x < GRID_COLS)
        {
            if (!coord_map[x][y] || coord_map[x][y]->type == DEL)
            {
                x++;
                continue;
            }
            t = coord_map[x][y]->type;

            // 截取完整连续同色块
            uint8_t endX = x;
            while (endX < GRID_COLS && coord_map[endX][y] && coord_map[endX][y]->type == t)
            {
                endX++;
            }
            uint8_t count = endX - x;
            if (count < 3)
            {
                x = endX;
                continue;
            }

            // 判断区块内是否有炸弹
            uint8_t HasBomb = 0;
            for (uint8_t k = x; k < endX; k++)
            {
                if (clear_flag[k][y] >= 2)
                {
                    HasBomb = 1;
                    break;
                }
            }

            if (!HasBomb)
            {
                // 无炸弹：正常标记消除 + 长连生成行炸弹
                for (uint8_t k = x; k < endX; k++)
                {
                    if (clear_flag[k][y] < 2)
                    {
                        clear_flag[k][y] = 1;
                        ret++;
                    }
                }
                if (count > 3)
                {
                    uint8_t bombCreated = 0;
                    for (uint8_t j = x; j < endX; j++)
                    {
                        if (!coord_map[j][y]) 
													continue;
                        if (coord_map[j][y]->moved == 1)
                        {
                            clear_flag[j][y] =BOMB_ROW;
                            bomb_creat(coord_map[j][y], BOMB_ROW);
                            bombCreated = 1;
                            break;
                        }
                    }
                    if (!bombCreated)
                    {
                        clear_flag[x][y] = BOMB_ROW;
                        bomb_creat(coord_map[x][y], BOMB_ROW);
                    }
                }
            }
            else
            {
                // 区块含炸弹：普通块标1，炸弹入队
                for (uint8_t k = x; k < endX; k++)
                {
                    if (clear_flag[k][y] < 2)
                    {
                        clear_flag[k][y] = 1;
                        ret++;
                    }
                }
                for (uint8_t k = x; k < endX; k++)
                {
                    if (clear_flag[k][y] >= 2)
                    {
                        enqueue(k, y);
                    }
                }
            }
            x = endX;
        }
    }

    // 垂直方向连续块检测
    for (uint8_t x = 0; x < GRID_COLS; x++)
    {
        uint8_t y = 0;
        while (y < GRID_ROWS)
        {
            if (!coord_map[x][y] || coord_map[x][y]->type == DEL)
            {
                y++;
                continue;
            }
            t = coord_map[x][y]->type;

            uint8_t endY = y;
            while (endY < GRID_ROWS && coord_map[x][endY] && coord_map[x][endY]->type == t)
            {
                endY++;
            }
            uint8_t count = endY - y;
            if (count < 3)
            {
                y = endY;
                continue;
            }

            uint8_t HasBomb = 0;
            for (uint8_t k = y; k < endY; k++)
            {
                if (clear_flag[x][k] >= 2)
                {
                    HasBomb = 1;
                    break;
                }
            }

            if (!HasBomb)
            {
                // 无炸弹：正常标记 + 生成列炸弹
                for (uint8_t k = y; k < endY; k++)
                {
                    if (clear_flag[x][k] < 2)
                    {
                        clear_flag[x][k] = 1;
                        ret++;
                    }
                }
                if (count> 3)
                {
                    uint8_t bombCreated = 0;
                    for (uint8_t j = y; j < endY; j++)
                    {
                        if (!coord_map[x][j]) continue;
                        if (coord_map[x][j]->moved == 1)
                        {
                            clear_flag[x][j] = BOMB_COL;
                            bomb_creat(coord_map[x][j], BOMB_COL);
                            bombCreated = 1;
                            break;
                        }
                    }
                    if (!bombCreated)
                    {
                        clear_flag[x][y] = BOMB_COL;
                        bomb_creat(coord_map[x][y], BOMB_COL);
                    }
                }
            }
            else
            {
                // 区块含炸弹：普通块标1，炸弹入队
                for (uint8_t k = y; k < endY; k++)
                {
                    if (clear_flag[x][k] < 2)
                    {
                        clear_flag[x][k] = 1;
                        ret++;
                    }
                }
                for (uint8_t k = y; k < endY; k++)
                {
                    if (clear_flag[x][k] >= 2)
                    {
                        enqueue(x, k);
                    }
                }
            }
            y = endY;
        }
    }

    // 取出炸弹引爆
    uint8_t curX, curY;  //用于接受坐标
    while (dequeue(&curX, &curY))
    {
        uint8_t bombType = clear_flag[curX][curY];
        if (bombType < BOMB_ROW)
					continue;  //给个容错，防止不是炸弹

        if (bombType == BOMB_ROW)
        {
            // 行炸弹：整行普通块标1，同行新炸弹入队
            for (uint8_t i = 0; i < GRID_COLS; i++)
            {
                if (clear_flag[i][curY] < BOMB_ROW)  //把这一行非炸弹全部标1
                {
                    clear_flag[i][curY] = 1;
                    ret++;
                }
                else if (clear_flag[i][curY] >= BOMB_ROW)
                {
                    enqueue(i, curY);
                }
            }
        }
        else if (bombType == BOMB_COL)
        {
            // 列炸弹：整列普通块标1，同列新炸弹入队
            for (uint8_t i = 0; i < GRID_ROWS; i++)
            {
                if (clear_flag[curX][i] < BOMB_ROW)
                {
                    clear_flag[curX][i] = 1;
                    ret++;
                }
                else if (clear_flag[curX][i] >= BOMB_ROW)
                {
                    enqueue(curX, i);
                }
            }
        }
        // 炸弹本体标记为1，本轮消除
        clear_flag[curX][curY] = 1;
        ret++;
    }

    if (ret > 1)
    {
        game_score += ret * 5;
    }

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
  
	
	







