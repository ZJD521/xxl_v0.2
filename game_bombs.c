#include "game.h"

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