# lilygo_ESP32S3_t_rgb_round_mirelojito
Basado en fablabnbg/TRGBArduinoSupport y fbiego / esp32-c3-mini
Ante todo agradezco a fablabnbg y fbiego que sirvieron de inspiración para mi primer desarrollo
de la  pruebas iniciales en el dev kit LilyGO T-RGB round.  </br>
Sugiero primero ver </br>
https://github.com/Xinyuan-LilyGO/T-RGB/ </br>
y luego </br>
https://github.com/fbiego/esp32-c3-mini </br>
de este último tomé solo brevemente la primer pantalla y la pantalla de setting. </br>
El wifi lo configuro con WiFiManager el AP se muestra con el nombre de ConnectMiRelojitoTRGB,
la primera vez espera 3 minutos , y si no se conecta al WIFI de su casa, en su dispositivo movil ( tablet, celular, o notebook) aparece el  AP ConnectMiRelojitoTRGB y desde ese formulario  selecciona el WIFI que desea.</br>

En esta versión el clima lo toma del servicio meteorológico de Argentina, sino no encuentra ninguna localidad de Argentina , reintenta cada 10 segundos. Si encuentra la localidad cada 2 horas vuelve a leer el clima.</br>
Cambia el fondo de pantalla si es de día o de noche. </br>
Si se desliza hacia la derecha, muestra la pantalla de Configuración, </br>
La lista de opciones de la pantalla de Configuración funcionan  todas. Gran trabajo de fbiego ( https://github.com/fbiego/esp32-c3-mini.  )</br>
El Rango de brillo va de 1 a 15 con el (backlightPin = EXAMPLE_PIN_NUM_BK_LIGHT) </br>
El scroll circular activa y desactiva onScrollMode() </br>
Screen Timeout utiliza el deepSleep() </br>
El nivel de bateria toma el  batteryPin = BAT_VOLT_PIN </br>
La imagen !ConfiguracionTRGB.gif muestra las opciones de Arduino IDE 2.2.1 >Tools </br>

