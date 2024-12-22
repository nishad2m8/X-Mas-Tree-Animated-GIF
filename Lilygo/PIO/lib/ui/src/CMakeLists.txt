SET(SOURCES screens/ui_Screen1.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_tree_frame_00_png.c
    images/ui_img_tree_frame_01_png.c
    images/ui_img_tree_frame_02_png.c
    images/ui_img_tree_frame_03_png.c
    images/ui_img_tree_frame_04_png.c
    images/ui_img_tree_frame_05_png.c
    images/ui_img_tree_frame_06_png.c
    images/ui_img_tree_frame_07_png.c
    images/ui_img_tree_frame_08_png.c
    images/ui_img_tree_frame_09_png.c
    images/ui_img_tree_frame_10_png.c
    images/ui_img_tree_frame_11_png.c
    images/ui_img_tree_frame_12_png.c
    images/ui_img_tree_frame_13_png.c
    images/ui_img_tree_frame_14_png.c
    images/ui_img_tree_frame_15_png.c
    images/ui_img_tree_frame_16_png.c
    images/ui_img_tree_frame_17_png.c
    images/ui_img_tree_frame_18_png.c
    images/ui_img_tree_frame_19_png.c)

add_library(ui ${SOURCES})
