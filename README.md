# lilygo-ESP32S3_t_rgb_round_mirelojito
Basado en fablabnbg/TRGBArduinoSupport y fbiego / esp32-c3-mini
Ante todo agradezco a fablabnbg y fbiego que sirvieron de inspiración para mi primer desarrollo
de la  pruebas iniciales en el dev kit LilyGO T-RGB round.  
Sugiero primero ver 
https://github.com/Xinyuan-LilyGO/T-RGB/
y luego 
https://github.com/fbiego/esp32-c3-mini
de este último tomé solo brevemente la primer pantalla y la pantalla de setting. 
El wifi lo configuro con WiFiManager el AP se muestra con el nombre de ConnectMiRelojitoTRGB,
la primera vez espera 3 minutos , y si no se conecta al WIFI de su casa, en su dispositivo movil ( tablet. cel, o notebook) aparece ese AP (ConnectMiRelojitoTRGB) y desde ese form seleccionan el WIFI de su casa.

En esta versión El clima lo toma del servicio meteorológico de Argentina, sino no encuentra ninguna localidad de Argentina , reintenta cada 10 segundos. Si encuentra la localidad cada 2 horas vuelve a leer el clima.
Cambia el fondo de pantalla si es de día o de noche. si se deliza hacia la derecha, muestra la pantalla de Configuación, 
La lista de opciones de la pantalla de Configuración funcionan  todas. Gran trabajo de fbiego ( https://github.com/fbiego/esp32-c3-mini.  )


