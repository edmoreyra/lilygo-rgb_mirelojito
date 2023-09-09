#include "TRGBSuppport.h"

#include "ui.h"
// #include "WiFi.h"
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <HTTPClient.h>
#include <DateTime.h>

#define buf_size 50

const char* ntpServer = "pool.ntp.org";
const char* ssid = "";
const char* password = "";
const long  gmtOffset_sec = -10800; //;-5400;
const int   daylightOffset_sec = 0;
const int backlightPin = EXAMPLE_PIN_NUM_BK_LIGHT;
WiFiManager wm;

TRGBSuppport trgb;
String clima_tactual = "";
String clima_fecha_enletras = "";
String clima_ciudad = "";
unsigned long prev_clima; 
bool circular = false;
struct Timer
{
  unsigned long time;
  long duration = 5000;
  bool active;
};

Timer screenTimer;
Timer alertTimer;
Timer searchTimer;
float batterylevel = -1; // Being set when reading battery level - used to avoid deep sleep when unde
int8_t percentage_ant = 0;
void showAlert();
// Callback from UI if Standby-Button is pressed
void ui_ev_standby(lv_event_t * e) {
	trgb.deepSleep();
}

void ui_event_brightnessSlide(lv_event_t * e) {
	// trgb.deepSleep();
}


void ui_event_batterySlider(lv_event_t * e) {
	// trgb.deepSleep();
}

void onBrightnessChange(lv_event_t *e)
{
  // Your code here
  lv_obj_t *slider = lv_event_get_target(e);
  setBrightness(lv_slider_get_value(slider));
}
void onTimeoutChange(lv_event_t *e)
{
  
  lv_obj_t *obj = lv_event_get_target(e);
  uint16_t sel = lv_dropdown_get_selected(obj);
  
Serial.println("Dentro de  onTimeoutChange");
Serial.println(sel);
  if (sel == 4)
  {
    screenTimer.duration = -1; // always on
  }
  else if (sel == 0)
  {
    screenTimer.duration = 5000; // 5 seconds
    screenTimer.active = true;
  }
  else if (sel < 4)
  {
    screenTimer.duration = 10000 * sel; // 10, 20, 30 seconds
    screenTimer.active = true;
  }
   screenTimer.time = millis();
}

void setBrightness(uint8_t value)
{
    static uint8_t level = 0;
    static uint8_t steps = 16;
    if (value == 0) {
        digitalWrite(backlightPin, 0);
        delay(3);
        level = 0;
        return;
    }
    if (level == 0) {
        digitalWrite(backlightPin, 1);
        level = steps;
        delayMicroseconds(30);
    }
    int from = steps - level;
    int to = steps - value;
    int num = (steps + to - from) % steps;
    for (int i = 0; i < num; i++) {
        digitalWrite(backlightPin, 0);
        digitalWrite(backlightPin, 1);
    }
    level = value;
}
void onScrollMode(lv_event_t *e)
{
  lv_obj_t *obj = lv_event_get_target(e);
  circular = lv_obj_has_state(obj, LV_STATE_CHECKED);
  lv_obj_scroll_by(ui_settingsList, 0, circular ? 1 : -1, LV_ANIM_ON);
}
static void onScroll(lv_event_t *e)
{
  lv_obj_t *list = lv_event_get_target(e);

  lv_area_t list_a;
  lv_obj_get_coords(list, &list_a);
  lv_coord_t list_y_center = list_a.y1 + lv_area_get_height(&list_a) / 2;

  lv_coord_t r = lv_obj_get_height(list) * 7 / 10;
  uint32_t i;
  uint32_t child_cnt = lv_obj_get_child_cnt(list);
  for (i = 0; i < child_cnt; i++)
  {
    lv_obj_t *child = lv_obj_get_child(list, i);
    lv_area_t child_a;
    lv_obj_get_coords(child, &child_a);

    lv_coord_t child_y_center = child_a.y1 + lv_area_get_height(&child_a) / 2;

    lv_coord_t diff_y = child_y_center - list_y_center;
    diff_y = LV_ABS(diff_y);

    /*Get the x of diff_y on a circle.*/
    lv_coord_t x;
    /*If diff_y is out of the circle use the last point of the circle (the radius)*/
    if (diff_y >= r)
    {
      x = r;
    }
    else
    {
      /*Use Pythagoras theorem to get x from radius and y*/
      uint32_t x_sqr = r * r - diff_y * diff_y;
      lv_sqrt_res_t res;
      lv_sqrt(x_sqr, &res, 0x8000); /*Use lvgl's built in sqrt root function*/
      x = r - res.i;
    }

    /*Translate the item by the calculated X coordinate*/
    lv_obj_set_style_translate_x(child, circular ? x : 0, 0);

    /*Use some opacity with larger translations*/
    // lv_opa_t opa = lv_map(x, 0, r, LV_OPA_TRANSP, LV_OPA_COVER);
    // lv_obj_set_style_opa(child, LV_OPA_COVER - opa, 0);
  }
}

/*
void updateIP(const String &str) {
	lv_label_set_text(ui_SWifiLabelIPAddr, ("IP: " + str).c_str());
}
*/
void updateClock() {
	// lv_label_set_text(ui_S1LabelClock, str.c_str());
 DateTimeParts p = DateTime.getParts();
 
String hhtime_str  = "";
 if (p.getHours()< 10)
 {
  hhtime_str="0"+ String(p.getHours());;
 }
 else
 {
  hhtime_str  = String(p.getHours());
 }
String mmtime_str  = "";
if (p.getMinutes()< 10)
 {
  mmtime_str="0"+ String(p.getMinutes());;
 }
 else
 {
  mmtime_str  = String(p.getMinutes());
 }

String sstime_str  = String(p.getSeconds());
  
  lv_label_set_text(ui_hourLabel,hhtime_str.c_str());
  lv_label_set_text(ui_minuteLabel,mmtime_str.c_str());
   
  
  String diatime_str = String(p.getMonthDay());
  
  String mestime_str = String(p.getMonth());
  if (mestime_str=="0")
  {
    mestime_str="Enero";
  };
  if (mestime_str=="1")
  {
    mestime_str="Febrero";
  };
  if (mestime_str=="2")
  {
    mestime_str="Marzo";
  };
  if (mestime_str=="3")
  {
    mestime_str="Abril";
  };
  if (mestime_str=="4")
  {
    mestime_str="Mayo";
  };
  if (mestime_str=="5")
  {
    mestime_str="Junio";
  };
  if (mestime_str=="6")
  {
    mestime_str="Julio";
  };
  if (mestime_str=="7")
  {
    mestime_str="Agosto";
  };
  if (mestime_str=="8")
  {
    mestime_str="Setiembre";
  };
  if (mestime_str=="9")
  {
    mestime_str="Octubre";
  };
  if (mestime_str=="10")
  {
    mestime_str="Noviembre";
  };
  if (mestime_str=="12")
  {
    mestime_str="Diciembre";
  };

  String fechacompleta = diatime_str + " de\n" + mestime_str + " \n"+String(p.getYear());
  
  // ui_dateLabel,"08\nJuly")
   lv_label_set_text(ui_dateLabel,fechacompleta.c_str());
   lv_label_set_text(ui_S1LabelClock, sstime_str.c_str());
  String wdtime_str  = String(p.getWeekDay());
  if (wdtime_str=="0")
  {
    wdtime_str="Domingo";
  };
  if (wdtime_str=="1")
  {
    wdtime_str="Lunes";
  };
  if (wdtime_str=="2")
  {
    wdtime_str="Martes";
  };
  if (wdtime_str=="3")
  {
    wdtime_str="Miercoles";
  };
  if (wdtime_str=="4")
  {
    wdtime_str="Jueves";
  };
  if (wdtime_str=="5")
  {
    wdtime_str="Viernes";
  };
  if (wdtime_str=="6")
  {
    wdtime_str="Sabado";
  };

   lv_label_set_text(ui_dayLabel, wdtime_str.c_str());
   if (clima_tactual!="")
   {
    String climayciudad = clima_tactual+" °C"+"\n"+clima_ciudad;
    lv_label_set_text(ui_weatherTemp, climayciudad.c_str());

   }
}



/*
void onMusicPlay(lv_event_t * e);
void onMusicPrevious(lv_event_t * e);
void onMusicNext(lv_event_t * e);

void onMusicPlay(lv_event_t *e)
{
  watch.musicControl(MUSIC_TOGGLE);
}

void onMusicPrevious(lv_event_t *e)
{
  watch.musicControl(MUSIC_PREVIOUS);
}

void onMusicNext(lv_event_t *e)
{
  watch.musicControl(MUSIC_NEXT);
}

*/

void setup() {  
  delay(100);   // Rumors say it helps avoid sporadical crashes after wakeup from deep-sleep
  trgb.init();
  
  // Print some info to Serial
  //TRGBSuppport::print_chip_info();
  //TRGBSuppport::scan_iic();

  // Initialize SD Card. It can be accessed by SD_MMC object.
  // trgb.SD_init();
  conectaWifi();
//  configTime(-3600, -3600, ntpServer);   // Configure Timezone and NTP
configTime(gmtOffset_sec, daylightOffset_sec, ntpServer );
  

  // load UI
  ui_init();
  lv_obj_add_event_cb(ui_settingsList, onScroll, LV_EVENT_SCROLL, NULL);
  prev_clima = millis();
  // add your own stuff ..
  screenTimer.active = false;
  screenTimer.time = millis();
  screenTimer.duration=-1;
 
 isDay();

}
void conectaWifi()
{
  wm.setConfigPortalBlocking(true);
  wm.setConfigPortalTimeout(360); // espera tres minutos para cerrar portal de coneccion  
  if (wm.autoConnect("ConnectMiRelojitoTRGB")) {
   Serial.println(F("connected...:)"));
   //tft.drawString("connectado a WIFI :) ", 0, 0, 4);
   
  }
  else {
    Serial.println(F("Configportal running"));
  
  }
   }
 
void loop() {
  wm.process();
	static uint32_t Millis = 0;
		static uint16_t time_counter = 0;
	lv_timer_handler();
	if (millis() - Millis > 500) {	// every 500ms
		time_counter++;
		Millis=millis();
	    time_t now;
	    time(&now);
	    updateClock();
	} else {
		delay(2);
    readBattery();
	}
 if ((millis() - prev_clima > 10000UL) && (clima_tactual == "")) {  // cada 10 segundos
  prev_clima = millis();
  leerClima();
  Serial.println(" leerClima ");
}
if ((millis() - prev_clima > 3600000UL) && (clima_tactual != "")) {  // cada 60 minutos
  prev_clima = millis();
  leerClima();
 
  Serial.println(" leerClima ");
}

if (screenTimer.active)
  {
    //uint8_t lvl = lv_slider_get_value(ui_brightnessSlider);
    // setBrightness(lvl);
    //Serial.println("  screenTimer.active setBrightness(lvl);");
    if (screenTimer.duration < 0)
    {
      
      screenTimer.active = false;
      Serial.println("  screenTimer.active = false Always On active ");
    }
    else if (screenTimer.time + screenTimer.duration < millis())
    {
      Serial.println("  screenTimer.time ");
      Serial.println( screenTimer.time );
      
      Serial.println("  screenTimer.duration ");
      Serial.println( screenTimer.duration );
      Serial.println("  screenTimer.duration ");
      Serial.println( screenTimer.duration );
        Serial.println("  millis() ");
      Serial.println( millis() );
      
      screenTimer.active = false;
      Serial.println("  screenTimer.active = false Screen timeout ");
      Serial.println("  deepSleep  ");
      screenTimer.active = false;
      screenTimer.duration=-1;
       trgb.deepSleep();
      //setBrightness(0);
      //lv_disp_load_scr(ui_clockScreen);
    }
  }

}



void leerClima()
{
 String clima_fecha = "";
String clima_fecha_diasemana = "";

boolean clima_muestra = false;                                        //Make the request
  HTTPClient http;
  http.begin("http://syssistemas.com.ar/weather/index_esp.php"); //Specify the URL
  int httpCode = http.GET();                                        //Make the request

Serial.println(" get  httpCode  " +String(httpCode));
  if (httpCode > 0) { //Check for the returning code

    String ls_clima = http.getString();
    if (httpCode == 200)
    {

      int from, to;
      from = ls_clima.indexOf("_", 1) + 1;
      to  = ls_clima.indexOf("</br>", from + 1) ;
      clima_ciudad =  ls_clima.substring(from, to);
      char texte[50];
      clima_ciudad.toCharArray(texte, 50);
      LookForAccents (texte, strlen(texte));
      clima_ciudad = texte;
      from = ls_clima.indexOf("_", to) + 1;
      to  = ls_clima.indexOf("</br>", from + 1) ;
      clima_fecha = ls_clima.substring(from, to);
      clima_fecha_diasemana = clima_fecha.substring(0, clima_fecha.indexOf(",", 1) );
      clima_fecha_diasemana.toCharArray(texte, 50);
      // LookForAccents (texte, strlen(texte));
      clima_fecha_diasemana = texte;
      clima_fecha_enletras = clima_fecha.substring(clima_fecha.indexOf(",", 1) + 1  );
      from = ls_clima.indexOf("_", to) + 1;
      to  = ls_clima.indexOf("C", from + 1) ;
      // to  = ls_clima.indexOf("</br>", from + 1) ;
      clima_tactual = ls_clima.substring(from, to);
 Serial.println(" clima_tactual " + clima_tactual);
      }
    else {
    Serial.println("Error on HTTP httpCode no es 200 ");
    clima_tactual="";
  }
  }
  else {
    Serial.println("Error on HTTP request"+String());
    clima_tactual="";
  }

  http.end(); //Free the resources
/* */


}

void LookForAccents (char Text[], int TextLength) {
  int i = 0;
  do {
    char c = Text[i];
    if ((int)c == 195) {
      char c2 = Text[i + 1];
      switch ((int)c2) {
        case 160 ... 166:
          Text[i] = 'a';
          break;
        case 167:
          Text[i] = 'c';
          break;
        case 168 ... 171:
          Text[i] = 'e';
          break;
        case 172 ... 175:
          Text[i] = 'i';
          break;
        case 177:
          Text[i] = '#';
          break;
        case 178 ... 182:
          Text[i] = 'o';
          break;
        case 185 ... 188:
          Text[i] = 'u';
          break;
        case 189 ... 191:
          Text[i] = 'y';
          break;
        case 128 ... 134:
          Text[i] = 'A';
          break;
        case 135:
          Text[i] = 'C';
          break;
        case 136 ... 139:
          Text[i] = 'E';
          break;
        case 140 ... 143:
          Text[i] = 'I';
          break;
        case 146 ... 150:
          Text[i] = 'O';
          break;
        case 153 ... 156:
          Text[i] = 'U';
          break;
        default:
          break;
      }
      for (int j = i + 1; j < TextLength; j++) Text[j] = Text[j + 1];
      TextLength --;
    }
    i++;
  } while (i < TextLength);

}


void onLoadHome(lv_event_t *e)
{
  if (isDay())
  {
    lv_obj_set_style_bg_img_src( ui_clockScreen, &cielodia480r, LV_PART_MAIN | LV_STATE_DEFAULT);
  }
  else
  {
    lv_obj_set_style_bg_img_src( ui_clockScreen, &cielo_nocturnor, LV_PART_MAIN | LV_STATE_DEFAULT);
  }
   // screenTimer.time = millis();
    //screenTimer.active = true;
}
bool isDay()
{
  DateTimeParts p = DateTime.getParts();
  return p.getHours() > 7 && p.getHours() < 20;
}

void readBattery() {
  uint8_t percentage = 100;

  //Adjust the pin below depending on what pin you measure your battery voltage on. 
  //On LOLIN D32 boards this is build into pin 35 - for other ESP32 boards, you have to manually insert a voltage divider between the battery and an analogue pin
  uint8_t batteryPin = BAT_VOLT_PIN ; //34; //FIXME

  // Set OHM values based on the resistors used in your voltage divider http://www.ohmslawcalculator.com/voltage-divider-calculator  
  float R1 = 30;
  float R2 = 100  ;
int vref = 1100;
 // float voltage = analogRead(batteryPin) / 4096.0 * (1/(R1/(R1+R2)));
   uint16_t v = analogRead(batteryPin);
    
   float voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);
  
  
  if (voltage > 1 ) { // Only display if there is a valid reading
   // Serial.println("Voltage = " + String(voltage));
    if (voltage >= 4.1) percentage = 100;
    else if (voltage >= 3.9) percentage = 100;
    else if (voltage >= 3.7) percentage = 75;
    else if (voltage >= 3.6) percentage = 50;
    else if (voltage >= 3.5) percentage = 25;
   
}
if ( percentage_ant!=percentage)
{
  percentage_ant=percentage;
lv_slider_set_value( ui_batterySlider, percentage, LV_ANIM_OFF);
String ls_battery="Bateria "+String(percentage)+"% V:"+String(voltage);
lv_label_set_text(ui_batteryLabel,ls_battery.c_str());
}

}

