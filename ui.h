#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

extern lv_obj_t *ui_S1Main;
// extern lv_obj_t *ui_SWifiLabelIPAddr;
extern lv_obj_t *ui_clockScreen;
extern lv_obj_t *ui_S1LabelClock;
extern lv_obj_t *ui_hourLabel;
extern lv_obj_t *ui_minuteLabel;
extern lv_obj_t *ui_dateLabel;
extern lv_obj_t *ui_dayLabel;
extern lv_obj_t *ui_weatherIcon;
extern lv_obj_t *ui_weatherTemp;
////////// setting /////////////////
void ui_event_settingsScreen( lv_event_t * e);
void onLoadHome(lv_event_t * e);
void onBrightnessChange(lv_event_t * e);
void ui_event_Switch2( lv_event_t * e);
void onScrollMode(lv_event_t *e);
void onTimeoutChange(lv_event_t *e);
extern lv_obj_t *ui_settingsScreen;
extern lv_obj_t *ui_settingsList;
extern lv_obj_t *ui_settingsTitle;
extern lv_obj_t *ui_brightnessPanel;
void ui_event_brightnessSlider( lv_event_t * e);
extern lv_obj_t *ui_brightnessSlider;
extern lv_obj_t *ui_brightnessIcon;
extern lv_obj_t *ui_brightnessLabel;
extern lv_obj_t *ui_scrollingPanel;
extern lv_obj_t *ui_scrollIcon;
void ui_event_Switch2( lv_event_t * e);
extern lv_obj_t *ui_Switch2;
extern lv_obj_t *ui_scrollLabel;
extern lv_obj_t *ui_timeoutPanel;
void ui_event_timeoutSelect( lv_event_t * e);
extern lv_obj_t *ui_timeoutSelect;
extern lv_obj_t *ui_timeoutIcon;
extern lv_obj_t *ui_timeoutLabel;
extern lv_obj_t *ui_batteryPanel;
void ui_event_batterySlider( lv_event_t * e);
extern lv_obj_t *ui_batterySlider;
extern lv_obj_t *ui_batteryIcon;
extern lv_obj_t *ui_batteryLabel;
extern lv_obj_t *ui_aboutPanel;
extern lv_obj_t *ui_aboutIcon;
extern lv_obj_t *ui_aboutText;

/////////////////////////////////////
LV_IMG_DECLARE( cielo_nocturnor);
//LV_IMG_DECLARE( ui_img_753022056);   // assets\night-sky.png
LV_IMG_DECLARE( ui_img_602195540);   // assets\dy-6.png
//LV_IMG_DECLARE( cielo_dia480); // cielo claro
LV_IMG_DECLARE(cielodia480r); // cielo claro
///////setting ///////////
LV_IMG_DECLARE( ui_img_brightness_png);   // assets\brightness.png
LV_IMG_DECLARE( ui_img_scrolling_png);   // assets\scrolling.png
LV_IMG_DECLARE( ui_img_timeout_png);   // assets\timeout.png
LV_IMG_DECLARE( ui_img_bat_png);   // assets\bat.png
LV_IMG_DECLARE( ui_img_info_png);   // assets\info.png

////////////////////
LV_FONT_DECLARE( ui_font_Number_big);
//void ui_event_ScreenWifi_Slider1(lv_event_t * e);
//extern lv_obj_t * ui_ScreenWifi_Slider1;
//extern lv_obj_t * ui_ScreenWifi_Label8;
void ui_event_SWifiButtonStandby(lv_event_t * e);
extern lv_obj_t * ui_SWifiButtonStandby;
extern lv_obj_t * ui_ScreenWifiButtonLabelStandby;
void ui_event_ScreenChart(lv_event_t * e);
extern lv_obj_t * ui_ScreenChart_Chart1;

void ui_ev_bright(lv_event_t * e);
void ui_ev_standby(lv_event_t * e);

void chart_init();
void chart_add_voltage(const float v);

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif
