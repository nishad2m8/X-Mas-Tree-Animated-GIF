// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.11
// Project name: Xmas tree

#include "../ui.h"

void ui_Screen1_screen_init(void)
{
ui_Screen1 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Screen1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Screen1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Screen1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Image_Tree = lv_img_create(ui_Screen1);
lv_img_set_src(ui_Image_Tree, &ui_img_tree_frame_00_png);
lv_obj_set_width( ui_Image_Tree, LV_SIZE_CONTENT);  /// 135
lv_obj_set_height( ui_Image_Tree, LV_SIZE_CONTENT);   /// 135
lv_obj_set_align( ui_Image_Tree, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Image_Tree, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_Image_Tree, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

uic_Image_Tree = ui_Image_Tree;

}