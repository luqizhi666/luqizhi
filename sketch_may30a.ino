/* *****************************************************************
 *
 * Download latest Blinker library here:
 * https://github.com/blinker-iot/blinker-library/archive/master.zip
 * 
 * 
 * Blinker is a cross-hardware, cross-platform solution for the IoT. 
 * It provides APP, device and server support, 
 * and uses public cloud services for data transmission and storage.
 * It can be used in smart home, data monitoring and other fields 
 * to help users build Internet of Things projects better and faster.
 * 
 * Make sure installed 2.7.4 or later ESP8266/Arduino package,
 * if use ESP8266 with Blinker.
 * https://github.com/esp8266/Arduino/releases
 * 
 * Make sure installed 1.0.5 or later ESP32/Arduino package,
 * if use ESP32 with Blinker.
 * https://github.com/espressif/arduino-esp32/releases
 * 
 * Docs: https://diandeng.tech/doc
 *       
 * 
 * *****************************************************************
 * 
 * Blinker 库下载地址:
 * https://github.com/blinker-iot/blinker-library/archive/master.zip
 * 
 * Blinker 是一套跨硬件、跨平台的物联网解决方案，提供APP端、设备端、
 * 服务器端支持，使用公有云服务进行数据传输存储。可用于智能家居、
 * 数据监测等领域，可以帮助用户更好更快地搭建物联网项目。
 * 
 * 如果使用 ESP8266 接入 Blinker,
 * 请确保安装了 2.7.4 或更新的 ESP8266/Arduino 支持包。
 * https://github.com/esp8266/Arduino/releases
 * 
 * 如果使用 ESP32 接入 Blinker,
 * 请确保安装了 1.0.5 或更新的 ESP32/Arduino 支持包。
 * https://github.com/espressif/arduino-esp32/releases
 * 
 * 文档: https://diandeng.tech/doc
 *       
 * 
 * *****************************************************************/
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>


#define TFT_CS         D4
#define TFT_RST        D2
#define TFT_DC         D3

#define TFT_MOSI D1  // Data out
#define TFT_SCLK D0  // Clock out

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

float p = 3.1415926;


#define BLINKER_WIFI
#define BLINKER_ESP_SMARTCONFIG

#include <Blinker.h>

// Download OneButton library here:
// https://github.com/mathertel/OneButton
#include "OneButton.h"

#if defined(ESP32)
    #define BLINKER_BUTTON_PIN 4
#else
    #define BLINKER_BUTTON_PIN D7
#endif
// button trigged when pin input level is LOW
OneButton button(BLINKER_BUTTON_PIN, true);

char auth[] = "ec712f5d8f38";



// other

BlinkerButton Button1("btn-abc");
BlinkerButton Button2("fmq");
BlinkerSlider Slider1("voice");
BlinkerNumber Number1("num-abc");

int counter = 0;
// 按下按键即会执行该函数
void button1_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
// other end
// 按下按键即会执行该函数
void button2_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    pinMode(D5, OUTPUT); 
    digitalWrite(D5, !digitalRead(D5));

}

void slider1_callback(int32_t value)
{
    BLINKER_LOG("get slider value: ", value);

}


// 如果未绑定的组件被触发，则会执行其中内容
void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);
    counter++;
    Number1.print(counter);
    tft.fillScreen(0xFF3333);
    testdrawtext(data , ST77XX_WHITE,2);


    
}












void deviceReset()
{
    // Reset device ,erase WiFi config.
    Blinker.reset();
}



void setup()
{
    tft.initR(INITR_MINI160x80);  // Init ST7735S mini display
    tft.fillScreen(0xFF3333);
    tft.setRotation(3);
    
    testdrawtext("Happy Children's Day!", ST77XX_WHITE, 2);

  
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);

    pinMode(LED_BUILTIN, OUTPUT);

    
    Blinker.begin(auth);
    Blinker.attachData(dataRead);

    Button1.attach(button1_callback);    
    Button2.attach(button2_callback);    
    Slider1.attach(slider1_callback);

    button.attachLongPressStop(deviceReset);



}

void loop()
{
    Blinker.run();
    button.tick();




    
}


void testdrawtext(const String text, uint16_t color, int size) {
  tft.setCursor(1, 1);
  tft.setTextColor(color);
  tft.setTextSize(size);
  tft.setTextWrap(true);
  tft.print(text);
}
