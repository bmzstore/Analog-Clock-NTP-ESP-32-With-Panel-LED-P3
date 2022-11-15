// - RGB matrix Panel Library: https://github.com/3tawi/RGBmatrixPanelGP
// - DS1307ESP Library: https://github.com/3tawi/DS1307ESP

#include "WiFi.h"
#include <RGBmatrixPanelGP.h>
#include <DS1307ESP.h>
#include <font/fontclock.h>
#include <font/bmz5x7.h>
DS1307ESP rtc;

char ssid[] = "bmzstore"; // Nama Wifi Anda
char pass[] = "11223344"; // Password Wifi Anda
#define TZ (+7*60*60) //Timezone

uint8_t sdapin = 21, sclpin = 22; 
//                        R1, G1, B1, R2, G2, B2  RGB Pins
uint8_t listrgbpins[6] = {19, 13, 18, 5, 12, 17};

#define P_A    16
#define P_B    14
#define P_C    4
#define P_D    27
#define P_E    25
#define P_CLK  2
#define P_LAT  26 
#define P_OE   15

RGBmatrixPanelGP matrix(P_A, P_B, P_C, P_D, P_E, P_CLK, P_LAT, P_OE, true, 64, listrgbpins);

#define WIDTH 64
#define HEIGHT 64
const byte CENTRE_X = (WIDTH / 2) - 1;
const byte CENTRE_Y = (HEIGHT / 2) - 1;
#define R_HOUR 17
#define R_MIN  25
#define R_SEC   29
uint32_t lastTime; 



void setup() {
 Serial.begin(115200);

  Serial.print("Attempting to connect to Network named: ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  configTime(TZ, 0, "ntp.nict.jp", "ntp.jst.mfeed.ad.jp"); 
  
  matrix.begin();
  delay(1000);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED)
    ESP.restart();

  
  drawtime();
  matrix.swapBuffers(false);
  delay(1000);
}

void drawtime() {
  time_t t;
  static time_t last_t;
  struct tm *tm;
  t = time(NULL);
  if (last_t == t) return;
  last_t = t;
  tm = localtime(&t);
  

            double radians;
            int x;
            int y;
            char jam[9];
            char menit[9];
            int j = 0;
            rtc.DSread();
            uint8_t hour = tm->tm_hour;
            if (hour > 12)
                hour -= 12;
            uint16_t lineColor1 = matrix.ColorHSV((tm->tm_sec + tm->tm_min) * 30, 255, 255, true);
            uint16_t lineColor2 = matrix.ColorHSV(random(0, 1536), 255, 255, true);
            uint16_t lineColor3 = matrix.ColorHSV(random(0, 1536), 255, 255, true);
            uint16_t lineColor4 = matrix.ColorHSV(random(0, 1536), 255, 255, true);
            matrix.fillScreen(0);
            matrix.drawCircle(CENTRE_X,CENTRE_Y, 31, lineColor1);
            for (int i = 0; i < 60; i+=15) {
            radians = (90.0F - (i * 6.0F)) * M_PI / 180.0;
            x = round(CENTRE_X + 30 * cos(radians));
            y = round(CENTRE_Y - 30 * sin(radians));
            //matrix.fillCircle(x,y, 2, lineColor2);

            //Panah 9
            matrix.drawLine(0,29, 0,33, lineColor2);
            matrix.drawLine(1,29, 1,33, lineColor2);
            matrix.drawLine(2,30, 2,32, lineColor2);
            matrix.fillCircle(2,31, 1, lineColor2);

            //Panah 3
            matrix.drawLine(62,29, 62,33, lineColor2);
            matrix.drawLine(61,29, 61,33, lineColor2);
            matrix.drawLine(60,30, 60,32, lineColor2);
            matrix.fillCircle(60,31, 1, lineColor2);
            }

            //Panah 12
            matrix.drawLine(29,0, 33,0, lineColor2);
            matrix.drawLine(29,1, 33,1, lineColor2);
            matrix.drawLine(30,2, 32,2, lineColor2);
            matrix.fillCircle(31,2, 1, lineColor2);

            //Panah 6
            matrix.drawLine(29,62, 33,62, lineColor2);
            matrix.drawLine(29,61, 33,61, lineColor2);
            matrix.drawLine(30,60, 32,60, lineColor2);
            matrix.fillCircle(31,60, 1, lineColor2);
            
            
            matrix.setFont(&bmz5x7);
            matrix.setTextColor(lineColor3);
            //Jam 1
            matrix.setCursor(43,9);
            matrix.print(char(1));

            //Jam 2
            matrix.setCursor(51,19);
            matrix.print(char(2));
            
            //Jam 3
            matrix.setCursor(54,30);
            matrix.print(char(3));
            
            //Jam 4
            matrix.setCursor(51,42);
            matrix.print(char(4));

            //Jam 5
            matrix.setCursor(42,51);
            matrix.print(char(5));
            
            //Jam 6
            matrix.setCursor(29,54);
            matrix.print(char(6));

            //Jam 7
            matrix.setCursor(16,51);
            matrix.print(char(7));
            
            //Jam 8
            matrix.setCursor(8,42);
            matrix.print(char(8));
            
            //Jam 9
            matrix.setCursor(4,30);
            matrix.print(char(9));

            //Jam 10
            matrix.setCursor(6,19);
            matrix.print(char(1));
            matrix.setCursor(11,19);
            matrix.print(char(0));

            //Jam 11
            matrix.setCursor(17,8);
            matrix.print(char(11));

            //Jam 12
            matrix.setCursor(28,6);
            matrix.print(char(12));
            
           //Jam Digital
            matrix.setFont(&bmz5x7);
            matrix.setTextColor(lineColor3);
            
            

            for (int i = 0; i < 60; i+=5) {
            radians = (90.0F - (i * 6.0F)) * M_PI / 180.0;
            x = round(CENTRE_X + 30 * cos(radians));
            y = round(CENTRE_Y - 30 * sin(radians));
            matrix.fillCircle(x,y, 1, lineColor2);
            x = round(CENTRE_X + 26 * cos(radians));
            y = round(CENTRE_Y - 26 * sin(radians));
            matrix.setCursor(x,y);
            //matrix.print(char(j));
            j++;
            if (j == 10) { j = 11;}
            }
            
            matrix.setFont();

            
            // hour
            radians = (90.0F - ((hour * 30.0F) + ((tm->tm_min * 29.0F) / 60.0F))) * M_PI / 180.0F;
            x = round(CENTRE_X + R_HOUR * cos(radians));
            y = round(CENTRE_Y - R_HOUR * sin(radians));
            matrix.drawLine(x,y, CENTRE_X, CENTRE_Y-1, 0xf000);
            matrix.drawLine(x,y, CENTRE_X, CENTRE_Y+1, 0xf000);
            matrix.drawLine(x,y, CENTRE_X-1, CENTRE_Y, 0xf000);
            matrix.drawLine(x,y, CENTRE_X+1, CENTRE_Y, 0xf000);

            // minute
            radians = (90.0F - (tm->tm_min * 6.0F)) * M_PI / 180.0;
            x = round(CENTRE_X + R_MIN * cos(radians));
            y = round(CENTRE_Y - R_MIN * sin(radians));
            matrix.drawLine(x,y, CENTRE_X, CENTRE_Y-1, 0x0f00);
            matrix.drawLine(x,y, CENTRE_X, CENTRE_Y+1, 0x0f00);
            matrix.drawLine(x,y, CENTRE_X-1, CENTRE_Y, 0x0f00);
            matrix.drawLine(x,y, CENTRE_X+1, CENTRE_Y, 0x0f00);

            // second
            radians = (90.0F - ((float)tm->tm_sec * 6.0F)) * M_PI / 180.0F;
            x = round(CENTRE_X + R_SEC * cos(radians));
            y = round(CENTRE_Y - R_SEC * sin(radians));
            matrix.drawLine(x,y, CENTRE_X-1, CENTRE_Y, lineColor4);
            matrix.drawLine(x,y, CENTRE_X+1, CENTRE_Y, lineColor4);
            matrix.drawLine(x,y, CENTRE_X, CENTRE_Y-1, lineColor4);
            matrix.drawLine(x,y, CENTRE_X, CENTRE_Y+1, lineColor4);
            matrix.fillCircle(x,y, 1, lineColor4);
    }

