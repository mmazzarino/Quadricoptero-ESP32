#include <Wire.h>
#include <SPIFFS.h>
#include <FS.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>		

#include "HTML_CSS_JS.h"

/*includes para dshot*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "Arduino.h"
#include "esp32-hal.h" 
