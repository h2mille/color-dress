#include <algorithm>
#include <NeoPixelBus.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "star.h"

#define PIN 2
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(strip_lengh, PIN, NEO_GRB + NEO_KHZ800);
NeoPixelBus<NeoGrbFeature, NeoEsp8266Dma800KbpsMethod> strip(strip_lengh, PIN);
const char ssid[] = "color_dress";
const char password[] = "1234567890";
IPAddress local_IP(192,168,0,1);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);

extern uint8_t stars_numbers;
Star star1;
Star star2;
Star star3;
Star star4;
Star star5;

uint8_t color_instensity=50;

WiFiServer server(80);
WiFiClient client;
String header;

// Auxiliar variables to store the current output state
String output5State = "off";
String output4State = "off";

// Assign output variables to GPIO pins
const int output5 = 5;
const int output4 = 4;

uint8_t strip_color[strip_lengh][3];





void webserver(){
  Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            uint8_t color_temp1[3];
            uint8_t color_temp2[3];
            // turns the GPIOs on and off
            bool new_val=false;
            bool rainbow_val=false;

            //G R B
            if (header.indexOf("GET /blue1") >= 0) {
              Serial.println("BLUE  ! ! !! ! ! ");
              strip_color[0][0]= 0;
              strip_color[0][1]= 0;
              strip_color[0][2]= 255;
              new_val=true;
            } else if (header.indexOf("GET /red1") >= 0) {
              Serial.println("RED  ! ! !! ! ! ");
              strip_color[0][0]= 255;
              strip_color[0][1]= 0;
              strip_color[0][2]= 0;
              new_val=true;
            } else if (header.indexOf("GET /green1") >= 0) {
              strip_color[0][0]= 0;
              strip_color[0][1]= 255;
              strip_color[0][2]= 0;
              new_val=true;
            } else if (header.indexOf("GET /yellow1") >= 0) {
              strip_color[0][0]= 255;
              strip_color[0][1]= 255;
              strip_color[0][2]= 0;
              new_val=true;
            } else if (header.indexOf("GET /purple1") >= 0) {
              strip_color[0][0]= 212;
              strip_color[0][1]= 115;
              strip_color[0][2]= 212;
              new_val=true;
            } else if (header.indexOf("GET /orange1") >= 0) {
              strip_color[0][0]= 255;
              strip_color[0][1]= 127;
              strip_color[0][2]= 0;
              new_val=true;
            } else if (header.indexOf("GET /pink1") >= 0) {
              strip_color[0][0]= 255;
              strip_color[0][1]= 0;
              strip_color[0][2]= 255;
              new_val=true;
            } else if (header.indexOf("GET /white1") >= 0) {
              strip_color[0][0]= 255;
              strip_color[0][1]= 255;
              strip_color[0][2]= 255;
              new_val=true;
            } else if (header.indexOf("GET /grad1") >= 0) {
              strip_color[0][0]= 0;
              strip_color[0][1]= 0;
              strip_color[0][2]= 0;
              rainbow_val=true;
            } else if (header.indexOf("GET /blue2") >= 0) {
              Serial.println("BLUE  ! ! !! ! ! ");
              strip_color[strip_lengh][0]= 0;
              strip_color[strip_lengh][1]= 0;
              strip_color[strip_lengh][2]= 255;
              new_val=true;
            } else if (header.indexOf("GET /red2") >= 0) {
              Serial.println("RED  ! ! !! ! ! ");
              strip_color[strip_lengh][0]= 255;
              strip_color[strip_lengh][1]= 0;
              strip_color[strip_lengh][2]= 0;
              new_val=true;
            } else if (header.indexOf("GET /green2") >= 0) {
              strip_color[strip_lengh][0]= 0;
              strip_color[strip_lengh][1]= 255;
              strip_color[strip_lengh][2]= 0;
              new_val=true;
            } else if (header.indexOf("GET /yellow2") >= 0) {
              strip_color[strip_lengh][0]= 255;
              strip_color[strip_lengh][1]= 255;
              strip_color[strip_lengh][2]= 0;
              new_val=true;
            } else if (header.indexOf("GET /purple2") >= 0) {
              strip_color[strip_lengh][0]= 212;
              strip_color[strip_lengh][1]= 115;
              strip_color[strip_lengh][2]= 212;
              new_val=true;
            } else if (header.indexOf("GET /orange2") >= 0) {
              strip_color[strip_lengh][0]= 255;
              strip_color[strip_lengh][1]= 127;
              strip_color[strip_lengh][2]= 0;
              new_val=true;
            } else if (header.indexOf("GET /pink2") >= 0) {
              strip_color[strip_lengh][0]= 255;
              strip_color[strip_lengh][1]= 0;
              strip_color[strip_lengh][2]= 255;
              new_val=true;
            } else if (header.indexOf("GET /white2") >= 0) {
              strip_color[strip_lengh][0]=255;
              strip_color[strip_lengh][1]=255;
              strip_color[strip_lengh][2]=255;
              new_val=true;
            } else if (header.indexOf("GET /grad2") >= 0) {
              strip_color[strip_lengh][0]=0;
              strip_color[strip_lengh][1]=0;
              strip_color[strip_lengh][2]=0;
              rainbow_val=true;
            } else if (header.indexOf("GET /lesslight") >= 0) {
              if(color_instensity-10<0)
                color_instensity=0;
              else
                color_instensity-=10;
            } else if (header.indexOf("GET /morelight") >= 0) {
              if(color_instensity+10>100)
                color_instensity=100;
              else
                color_instensity+=10;
            } else if (header.indexOf("GET /lessstars") >= 0) {
              if(stars_numbers-1<0)
                stars_numbers=0;
              else
                stars_numbers-=1;
            } else if (header.indexOf("GET /morestars") >= 0) {
              if(stars_numbers+1>20)
                stars_numbers=20;
              else
                stars_numbers+=1;
            }
            
            
            Serial.print(color_instensity);
            Serial.print(",");
            Serial.print(color_temp1[0]);
            Serial.print(",");
            Serial.print(color_temp1[1]);
            Serial.print(",");
            Serial.print(color_temp1[2]);
            Serial.print("|");
            Serial.print(",");
            Serial.print(color_temp2[0]);
            Serial.print(",");
            Serial.print(color_temp2[1]);
            Serial.print(",");
            Serial.print(color_temp2[2]);
            Serial.print("|");
            if(new_val==true)
            {

              
              for (uint32_t i=1;i<strip_lengh-1;i++)
              {
                strip_color[i][0]=(i*strip_color[strip_lengh][0]+(strip_lengh-i)*strip_color[0][0])/strip_lengh;
                strip_color[i][1]=(i*strip_color[strip_lengh][1]+(strip_lengh-i)*strip_color[0][1])/strip_lengh;
                strip_color[i][2]=(i*strip_color[strip_lengh][2]+(strip_lengh-i)*strip_color[0][2])/strip_lengh;
                Serial.print(strip_color[i][0]);
                Serial.print(" ");
                Serial.print(strip_color[i][1]);
                Serial.print(" ");
                Serial.print(strip_color[i][2]);
                Serial.println(" ");
              }
            }
              Serial.println("");
            
            // Display the HTML web page
            client.println("<style>.line,.column{flex:1}a{display:block;text-decoration:none;line-height:100%}.button{font-size:100px}</style><body style=\"display:flex;flex-direction:column;text-align:center;height:100%;margin:0\"><div class=\"line\" style=\"display:flex\"><a class=\"line\" style=\"background-color:blue\" href=\"blue1\">&nbsp;</a><a class=\"line\" style=\"background-color:blue\" href=\"blue2\">&nbsp;</a></div><div class=\"line\" style=\"display:flex\"><a class=\"line\" style=\"background-color:red\" href=\"red1\">&nbsp;</a><a class=\"line\" style=\"background-color:red\" href=\"red2\">&nbsp;</a></div><div class=\"line\" style=\"display:flex\"><a class=\"line\" style=\"background-color:green\" href=\"green1\">&nbsp;</a><a class=\"line\" style=\"background-color:green\" href=\"green2\">&nbsp;</a></div><div class=\"line\" style=\"display:flex\"><a class=\"line\" style=\"background-color:yellow\" href=\"yellow1\">&nbsp;</a><a class=\"line\" style=\"background-color:yellow\" href=\"yellow2\">&nbsp;</a></div><div class=\"line\" style=\"display:flex\"><a class=\"line\" style=\"background-color:purple\" href=\"purple1\">&nbsp;</a><a class=\"line\" style=\"background-color:purple\" href=\"purple2\">&nbsp;</a></div><div class=\"line\" style=\"display:flex\"><a class=\"line\" style=\"background-color:orange\" href=\"orange1\">&nbsp;</a><a class=\"line\" style=\"background-color:orange\" href=\"orange2\">&nbsp;</a></div><div class=\"line\" style=\"display:flex\"><a class=\"line\" style=\"background-color:pink\" href=\"pink1\">&nbsp;</a><a class=\"line\" style=\"background-color:pink\" href=\"pink2\">&nbsp;</a></div><div class=\"line\" style=\"display:flex\"><a class=\"line\" style=\"background-color:white\" href=\"white1\">&nbsp;</a><a class=\"line\" style=\"background-color:white\" href=\"white2\">&nbsp;</a></div><div class=\"line\" style=\"display:flex\"><a class=\"line\" style=\"background:linear-gradient(90deg,#ff2400,#e81d1d,#e8b71d,#e3e81d,#1de840,#1ddde8,#2b1de8,#dd00f3,#dd00f3)\" href=\"grad1\">&nbsp;</a><a class=\"line\" style=\"background:linear-gradient(90deg,#ff2400,#e81d1d,#e8b71d,#e3e81d,#1de840,#1ddde8,#2b1de8,#dd00f3,#dd00f3)\" href=\"grad2\">&nbsp;</a></div><div class=\"line\" style=\"display:flex\"><a href=\"lesslight\" class=\"column button\" style=\"background-color:LightGrey\">-</a><a href=\"morelight\" class=\"column button\" style=\"background-color:DarkGray\">+</a><a href=\"lessstars\" class=\"column button\" style=\"background-color:Goldenrod\">-</a><a href=\"morestars\" class=\"column button\" style=\"background-color:Yellow\">+</a></div></body>");
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");

}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  strip.Begin();
  strip.Show();
  int i;
  //R,G,B
  RgbColor tempcolor(0, 0, 50);
  for (i=0;i<300;i++)
    strip.SetPixelColor(i, tempcolor);
  strip.Show();
  randomSeed(analogRead(0));
  Serial.begin(115200);
  star1.init();
  star2.init();
  star3.init();
  star4.init();
  star5.init();
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(ssid,password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
  strip.Begin();
  for (int i=0;i<strip_lengh;i++)
  {
    strip_color[i][0]=0;
    strip_color[i][1]=0;
    strip_color[i][2]=255;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  client = server.available();   // Listen for incoming clients
  if (client==true)
  {
    Serial.println("Message");
    webserver();
  }
 
  for (int i=0;i<strip_lengh;i++) 
    strip.SetPixelColor(i, RgbColor(strip_color[i][0]*color_instensity/255,strip_color[i][1]*color_instensity/255,strip_color[i][2]*color_instensity/255));
  star1.update();
  star2.update();
  star3.update();
  star4.update();
  star5.update();
  strip.Show();
  delay(10);
}
