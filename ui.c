#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_S1Main;
lv_obj_t * ui_S1LabelTitle;
lv_obj_t * ui_S1LabelClock;
//lv_obj_t * ui_SWifiLabelIPAddr;
void ui_event_SWifiButtonStandby(lv_event_t * e);
void onLoadHome(lv_event_t * e);
void onBrightnessChange(lv_event_t * e);
void onTimeoutChange(lv_event_t *e);
lv_obj_t * ui_SWifiButtonStandby;
lv_obj_t * ui_ScreenWifiButtonLabelStandby;
lv_obj_t * ui_ScreenChart_Chart1;
/////////////////////// agregado a clock ///////////////
void ui_event_clockScreen( lv_event_t * e);
lv_obj_t *ui_clockScreen;
lv_obj_t *ui_hourLabel;
lv_obj_t *ui_minuteLabel;
lv_obj_t *ui_dateLabel;
lv_obj_t *ui_dayLabel;
lv_obj_t *ui_weatherIcon;
lv_obj_t *ui_weatherTemp;
///////////// setting
void ui_event_settingsScreen( lv_event_t * e);
lv_obj_t *ui_settingsScreen;
lv_obj_t *ui_settingsList;
lv_obj_t *ui_settingsTitle;
lv_obj_t *ui_brightnessPanel;
void ui_event_brightnessSlider( lv_event_t * e);
lv_obj_t *ui_brightnessSlider;
lv_obj_t *ui_brightnessIcon;
lv_obj_t *ui_brightnessLabel;
lv_obj_t *ui_scrollingPanel;
lv_obj_t *ui_scrollIcon;
void ui_event_Switch2( lv_event_t * e);
lv_obj_t *ui_Switch2;
lv_obj_t *ui_scrollLabel;
lv_obj_t *ui_timeoutPanel;
void ui_event_timeoutSelect( lv_event_t * e);
lv_obj_t *ui_timeoutSelect;
lv_obj_t *ui_timeoutIcon;
lv_obj_t *ui_timeoutLabel;
lv_obj_t *ui_batteryPanel;
void ui_event_batterySlider( lv_event_t * e);
lv_obj_t *ui_batterySlider;
lv_obj_t *ui_batteryIcon;
lv_obj_t *ui_batteryLabel;
lv_obj_t *ui_aboutPanel;
lv_obj_t *ui_aboutIcon;
lv_obj_t *ui_aboutText;
///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

void ui_event_SWifiButtonStandby(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_LONG_PRESSED) {
        ui_ev_standby(e);
    }
}



///////////////////// SCREENS ////////////////////
void ui_settingsScreen_screen_init(void)
{
ui_settingsScreen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_settingsScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_settingsScreen, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_settingsScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_settingsScreen, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_settingsList = lv_obj_create(ui_settingsScreen);
lv_obj_set_width( ui_settingsList, 480);
lv_obj_set_height( ui_settingsList, 480);
lv_obj_set_align( ui_settingsList, LV_ALIGN_TOP_MID );
lv_obj_set_flex_flow(ui_settingsList,LV_FLEX_FLOW_COLUMN);
lv_obj_set_flex_align(ui_settingsList, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_set_scrollbar_mode(ui_settingsList, LV_SCROLLBAR_MODE_OFF);
lv_obj_set_scroll_dir(ui_settingsList, LV_DIR_VER);
lv_obj_set_style_radius(ui_settingsList, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_settingsList, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_settingsList, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_settingsList, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_settingsList, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_settingsList, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_settingsList, 50, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_settingsList, 70, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_settingsTitle = lv_label_create(ui_settingsList);
lv_obj_set_width( ui_settingsTitle, 240);
lv_obj_set_height( ui_settingsTitle, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_settingsTitle, LV_ALIGN_CENTER );
lv_label_set_text(ui_settingsTitle,"Configuracion");
lv_obj_set_style_text_align(ui_settingsTitle, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_settingsTitle, &lv_font_montserrat_20, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_settingsTitle, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_settingsTitle, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_settingsTitle, 1, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_side(ui_settingsTitle, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_settingsTitle, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_settingsTitle, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_settingsTitle, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_settingsTitle, 5, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_brightnessPanel = lv_obj_create(ui_settingsList);
lv_obj_set_width( ui_brightnessPanel, 260);
lv_obj_set_height( ui_brightnessPanel, 64);
lv_obj_set_align( ui_brightnessPanel, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_brightnessPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_brightnessPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_brightnessPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_brightnessPanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_brightnessPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_brightnessPanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_brightnessPanel, 1, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_side(ui_brightnessPanel, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_brightnessPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_brightnessPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_brightnessPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_brightnessPanel, 5, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_brightnessSlider = lv_slider_create(ui_brightnessPanel);
lv_slider_set_range(ui_brightnessSlider, 1,16);
lv_slider_set_value( ui_brightnessSlider, 100, LV_ANIM_OFF);
if (lv_slider_get_mode(ui_brightnessSlider)==LV_SLIDER_MODE_RANGE ) lv_slider_set_left_value( ui_brightnessSlider, 0, LV_ANIM_OFF);
lv_obj_set_width( ui_brightnessSlider, 123);
lv_obj_set_height( ui_brightnessSlider, 10);
lv_obj_set_x( ui_brightnessSlider, 24 );
lv_obj_set_y( ui_brightnessSlider, 12 );
lv_obj_set_align( ui_brightnessSlider, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_brightnessSlider, LV_OBJ_FLAG_GESTURE_BUBBLE );    /// Flags

ui_brightnessIcon = lv_img_create(ui_brightnessPanel);
lv_img_set_src(ui_brightnessIcon, &ui_img_brightness_png);
lv_obj_set_width( ui_brightnessIcon, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_brightnessIcon, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_brightnessIcon, -74 );
lv_obj_set_y( ui_brightnessIcon, 2 );
lv_obj_set_align( ui_brightnessIcon, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_brightnessIcon, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_brightnessIcon, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_img_set_zoom(ui_brightnessIcon,150);

ui_brightnessLabel = lv_label_create(ui_brightnessPanel);
lv_obj_set_width( ui_brightnessLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_brightnessLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_brightnessLabel, 53 );
lv_obj_set_y( ui_brightnessLabel, 3 );
lv_label_set_text(ui_brightnessLabel,"Screen Brightness");

ui_scrollingPanel = lv_obj_create(ui_settingsList);
lv_obj_set_width( ui_scrollingPanel, 200);
lv_obj_set_height( ui_scrollingPanel, 64);
lv_obj_set_align( ui_scrollingPanel, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_scrollingPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_scrollingPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_scrollingPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_scrollingPanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_scrollingPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_scrollingPanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_scrollingPanel, 1, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_side(ui_scrollingPanel, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_scrollingPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_scrollingPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_scrollingPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_scrollingPanel, 5, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_scrollIcon = lv_img_create(ui_scrollingPanel);
lv_img_set_src(ui_scrollIcon, &ui_img_scrolling_png);
lv_obj_set_width( ui_scrollIcon, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_scrollIcon, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_scrollIcon, -74 );
lv_obj_set_y( ui_scrollIcon, 2 );
lv_obj_set_align( ui_scrollIcon, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_scrollIcon, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_scrollIcon, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_img_set_zoom(ui_scrollIcon,150);

ui_Switch2 = lv_switch_create(ui_scrollingPanel);
lv_obj_set_width( ui_Switch2, 50);
lv_obj_set_height( ui_Switch2, 25);
lv_obj_set_x( ui_Switch2, 57 );
lv_obj_set_y( ui_Switch2, 29 );

ui_scrollLabel = lv_label_create(ui_scrollingPanel);
lv_obj_set_width( ui_scrollLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_scrollLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_scrollLabel, 54 );
lv_obj_set_y( ui_scrollLabel, 3 );
lv_label_set_text(ui_scrollLabel,"Circular Scroll");


ui_timeoutPanel = lv_obj_create(ui_settingsList);
lv_obj_set_width( ui_timeoutPanel, 200);
lv_obj_set_height( ui_timeoutPanel, 64);
lv_obj_set_x( ui_timeoutPanel, 37 );
lv_obj_set_y( ui_timeoutPanel, 7 );
lv_obj_set_align( ui_timeoutPanel, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_timeoutPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_timeoutPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_timeoutPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_timeoutPanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_timeoutPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_timeoutPanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_timeoutPanel, 1, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_side(ui_timeoutPanel, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_timeoutPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_timeoutPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_timeoutPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_timeoutPanel, 5, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_timeoutSelect = lv_dropdown_create(ui_timeoutPanel);
lv_dropdown_set_options( ui_timeoutSelect, "5 Seconds\n10 Seconds\n20 Seconds\n30 Seconds\nAlways On" );
lv_obj_set_width( ui_timeoutSelect, 120);
lv_obj_set_height( ui_timeoutSelect, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_timeoutSelect, 20 );
lv_obj_set_y( ui_timeoutSelect, 10 );
lv_obj_set_align( ui_timeoutSelect, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_timeoutSelect, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_set_style_bg_color(ui_timeoutSelect, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_timeoutSelect, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_timeoutSelect, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_timeoutSelect, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_timeoutSelect, 1, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_bg_color(lv_dropdown_get_list(ui_timeoutSelect), lv_color_hex(0x000000),  LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(lv_dropdown_get_list(ui_timeoutSelect), 255,  LV_PART_MAIN| LV_STATE_DEFAULT);

ui_timeoutIcon = lv_img_create(ui_timeoutPanel);
lv_img_set_src(ui_timeoutIcon, &ui_img_timeout_png);
lv_obj_set_width( ui_timeoutIcon, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_timeoutIcon, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_timeoutIcon, -74 );
lv_obj_set_y( ui_timeoutIcon, 2 );
lv_obj_set_align( ui_timeoutIcon, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_timeoutIcon, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_timeoutIcon, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_img_set_zoom(ui_timeoutIcon,150);

ui_timeoutLabel = lv_label_create(ui_timeoutPanel);
lv_obj_set_width( ui_timeoutLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_timeoutLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_timeoutLabel, 61 );
lv_obj_set_y( ui_timeoutLabel, 0 );
lv_label_set_text(ui_timeoutLabel,"Screen Timeout");

ui_batteryPanel = lv_obj_create(ui_settingsList);
lv_obj_set_width( ui_batteryPanel, 200);
lv_obj_set_height( ui_batteryPanel, 64);
lv_obj_set_align( ui_batteryPanel, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_batteryPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_batteryPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_batteryPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_batteryPanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_batteryPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_batteryPanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_batteryPanel, 1, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_side(ui_batteryPanel, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_batteryPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_batteryPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_batteryPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_batteryPanel, 5, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_batterySlider = lv_slider_create(ui_batteryPanel);
lv_slider_set_value( ui_batterySlider, 50, LV_ANIM_OFF);
if (lv_slider_get_mode(ui_batterySlider)==LV_SLIDER_MODE_RANGE ) lv_slider_set_left_value( ui_batterySlider, 0, LV_ANIM_OFF);
lv_obj_set_width( ui_batterySlider, 130);
lv_obj_set_height( ui_batterySlider, 10);
lv_obj_set_x( ui_batterySlider, 22 );
lv_obj_set_y( ui_batterySlider, 12 );
lv_obj_set_align( ui_batterySlider, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_batterySlider, LV_OBJ_FLAG_GESTURE_BUBBLE );    /// Flags

lv_obj_set_style_bg_color(ui_batterySlider, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_batterySlider, 0, LV_PART_KNOB| LV_STATE_DEFAULT);

ui_batteryIcon = lv_img_create(ui_batteryPanel);
lv_img_set_src(ui_batteryIcon, &ui_img_bat_png);
lv_obj_set_width( ui_batteryIcon, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_batteryIcon, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_batteryIcon, -74 );
lv_obj_set_y( ui_batteryIcon, 2 );
lv_obj_set_align( ui_batteryIcon, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_batteryIcon, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_batteryIcon, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_img_set_zoom(ui_batteryIcon,150);

ui_batteryLabel = lv_label_create(ui_batteryPanel);
lv_obj_set_width( ui_batteryLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_batteryLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_batteryLabel, 53 );
lv_obj_set_y( ui_batteryLabel, 3 );
lv_label_set_text(ui_batteryLabel,"Battery 50%");

ui_aboutPanel = lv_obj_create(ui_settingsList);
lv_obj_set_width( ui_aboutPanel, 200);
lv_obj_set_height( ui_aboutPanel, LV_SIZE_CONTENT);   /// 64
lv_obj_set_align( ui_aboutPanel, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_aboutPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_aboutPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_aboutPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_aboutPanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_aboutPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_aboutPanel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_aboutPanel, 1, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_side(ui_aboutPanel, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_aboutPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_aboutPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_aboutPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_aboutPanel, 5, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_aboutIcon = lv_img_create(ui_aboutPanel);
lv_img_set_src(ui_aboutIcon, &ui_img_info_png);
lv_obj_set_width( ui_aboutIcon, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_aboutIcon, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_aboutIcon, -5 );
lv_obj_set_y( ui_aboutIcon, 2 );
lv_obj_add_flag( ui_aboutIcon, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_aboutIcon, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_img_set_zoom(ui_aboutIcon,150);

ui_aboutText = lv_label_create(ui_aboutPanel);
lv_obj_set_width( ui_aboutText, 130);
lv_obj_set_height( ui_aboutText, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_aboutText, 60 );
lv_obj_set_y( ui_aboutText, 7 );
lv_label_set_text(ui_aboutText,"Gracias a fbiego\nESP32 S3 T RGB \nedmoreyra@gmail.com");

lv_obj_add_event_cb(ui_brightnessSlider, ui_event_brightnessSlider, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Switch2, ui_event_Switch2, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_timeoutSelect, ui_event_timeoutSelect, LV_EVENT_ALL, NULL);

lv_obj_add_event_cb(ui_batterySlider, ui_event_batterySlider, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_settingsScreen, ui_event_settingsScreen, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_clockScreen, ui_event_clockScreen, LV_EVENT_ALL, NULL);

}

void ui_clockScreen_screen_init(void)
{
ui_clockScreen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_clockScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_S1LabelTitle = lv_label_create(ui_clockScreen);
    lv_obj_set_width(ui_S1LabelTitle, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_S1LabelTitle, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_S1LabelTitle, 0);
    lv_obj_set_y(ui_S1LabelTitle, -200);
    lv_obj_set_align(ui_S1LabelTitle, LV_ALIGN_CENTER);
    lv_label_set_text(ui_S1LabelTitle, "Mi Relojito");
    lv_obj_set_style_text_font(ui_S1LabelTitle, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);


lv_obj_set_style_bg_img_src( ui_clockScreen, &cielo_nocturnor, LV_PART_MAIN | LV_STATE_DEFAULT );

ui_S1LabelClock = lv_label_create(ui_clockScreen);
    lv_obj_set_width(ui_S1LabelClock, 180);
    lv_obj_set_height(ui_S1LabelClock, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_S1LabelClock, 0);
    lv_obj_set_y(ui_S1LabelClock, 133);
    lv_obj_set_align(ui_S1LabelClock, LV_ALIGN_CENTER);
    lv_label_set_long_mode(ui_S1LabelClock, LV_LABEL_LONG_DOT);
    lv_label_set_text(ui_S1LabelClock, "xx:yy:zz");
    lv_obj_set_style_text_align(ui_S1LabelClock, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_S1LabelClock, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);



ui_SWifiButtonStandby = lv_btn_create(ui_clockScreen);
    lv_obj_set_width(ui_SWifiButtonStandby, 169);
    lv_obj_set_height(ui_SWifiButtonStandby, 50);
    lv_obj_set_x(ui_SWifiButtonStandby, 0);
    lv_obj_set_y(ui_SWifiButtonStandby, lv_pct(38));
    lv_obj_set_align(ui_SWifiButtonStandby, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_SWifiButtonStandby, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_SWifiButtonStandby, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_SWifiButtonStandby, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SWifiButtonStandby, lv_color_hex(0x5D0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SWifiButtonStandby, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_SWifiButtonStandby, lv_color_hex(0x595959), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_SWifiButtonStandby, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_SWifiButtonStandby, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ScreenWifiButtonLabelStandby = lv_label_create(ui_SWifiButtonStandby);
    lv_obj_set_width(ui_ScreenWifiButtonLabelStandby, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ScreenWifiButtonLabelStandby, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_ScreenWifiButtonLabelStandby, LV_ALIGN_CENTER);
    lv_label_set_text(ui_ScreenWifiButtonLabelStandby, "Apagar");
    lv_obj_set_style_text_font(ui_ScreenWifiButtonLabelStandby, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);

//    lv_obj_add_event_cb(ui_ScreenWifi_Slider1, ui_event_ScreenWifi_Slider1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SWifiButtonStandby, ui_event_SWifiButtonStandby, LV_EVENT_ALL, NULL);





ui_hourLabel = lv_label_create(ui_clockScreen);
lv_obj_set_width( ui_hourLabel, 151);
lv_obj_set_height( ui_hourLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_hourLabel, -49 );
lv_obj_set_y( ui_hourLabel, -31 );
lv_obj_set_align( ui_hourLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_hourLabel,"20");
lv_obj_set_style_text_align(ui_hourLabel, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_hourLabel, &ui_font_Number_big, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_minuteLabel = lv_label_create(ui_clockScreen);
lv_obj_set_width( ui_minuteLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_minuteLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_minuteLabel, 35 );
lv_obj_set_y( ui_minuteLabel, 59 );
lv_obj_set_align( ui_minuteLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_minuteLabel,"28");
lv_obj_set_style_text_font(ui_minuteLabel, &ui_font_Number_big, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_dateLabel = lv_label_create(ui_clockScreen);
lv_obj_set_width( ui_dateLabel, 113);
lv_obj_set_height( ui_dateLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_dateLabel, 89 );
lv_obj_set_y( ui_dateLabel, -24 );
lv_obj_set_align( ui_dateLabel, LV_ALIGN_CENTER );
lv_label_set_long_mode(ui_dateLabel,LV_LABEL_LONG_CLIP);
lv_label_set_text(ui_dateLabel,"08\nJuly");
lv_obj_set_style_text_font(ui_dateLabel, &lv_font_montserrat_20, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_dayLabel = lv_label_create(ui_clockScreen);
lv_obj_set_width( ui_dayLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_dayLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_dayLabel, 0 );
lv_obj_set_y( ui_dayLabel, lv_pct(-35));
lv_obj_set_align( ui_dayLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_dayLabel,"Domingo");
lv_obj_set_style_text_font(ui_dayLabel, &lv_font_montserrat_36, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_weatherIcon = lv_img_create(ui_clockScreen);
lv_img_set_src(ui_weatherIcon, &ui_img_602195540);
lv_obj_set_width( ui_weatherIcon, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_weatherIcon, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_weatherIcon, -120 );
lv_obj_set_y( ui_weatherIcon, 20 );
lv_obj_set_align( ui_weatherIcon, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_weatherIcon, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_weatherIcon, LV_OBJ_FLAG_SCROLLABLE );    /// Flags


ui_weatherTemp = lv_label_create(ui_clockScreen);
lv_obj_set_width( ui_weatherTemp, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_weatherTemp, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_weatherTemp, -100 );
lv_obj_set_y( ui_weatherTemp, 72 );
lv_obj_set_align( ui_weatherTemp, LV_ALIGN_CENTER );
lv_label_set_text(ui_weatherTemp,"--°C");
lv_obj_set_style_text_font(ui_weatherTemp, &lv_font_montserrat_20, LV_PART_MAIN| LV_STATE_DEFAULT);



}

static lv_chart_series_t * ser_v;

void ui_init(void)
{
 lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_clockScreen_screen_init();
    ui_settingsScreen_screen_init();
    lv_disp_load_scr(ui_clockScreen);

}


// void chart_add_voltage(const float v) {
// 	lv_obj_t* chart = ui_ScreenChart_Chart1;
// 	lv_chart_set_next_value(chart, ser_v, (int16_t) (v * 100));
//     lv_chart_refresh(chart);
// }

void ui_event_clockScreen( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
//if ( event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT  ) {
//      _ui_screen_change( ui_notificationScreen, LV_SCR_LOAD_ANIM_OVER_RIGHT, 500, 0);
//}
if ( event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT  ) {
      _ui_screen_change( ui_settingsScreen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 500, 0);
}
//if ( event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_BOTTOM  ) {
//      _ui_screen_change( ui_controlScreen, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 500, 0);
//}
//if ( event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP  ) {
//      _ui_screen_change( ui_weatherScreen, LV_SCR_LOAD_ANIM_MOVE_TOP, 500, 0);
//}
if ( event_code == LV_EVENT_SCREEN_LOAD_START) {
      onLoadHome( e );
}
}
void ui_event_settingsScreen( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT  ) {
      _ui_screen_change( ui_clockScreen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 500, 0);
}
}
void ui_event_brightnessSlider( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      onBrightnessChange( e );
}
}
void ui_event_Switch2( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      onScrollMode( e );
}
}

void ui_event_timeoutSelect( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
     
if ( event_code == LV_EVENT_VALUE_CHANGED) {
     
      onTimeoutChange( e );
}
}