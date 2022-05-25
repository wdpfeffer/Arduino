#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

WiFiUDP Udp;
char packetBuffer[255];
unsigned int localPort = 9999;
const char *ssid = "esp8266";  
const char *password = "test01";

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  Udp.begin(localPort);
  }

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) packetBuffer[len-1] = 0;
    Serial.print("Recibido(IP/Size/Data): ");
    Serial.print(Udp.remoteIP());Serial.print(" / ");
    Serial.print(packetSize);Serial.print(" / ");
    Serial.println(packetBuffer);

    Udp.beginPacket(Udp.remoteIP(),Udp.remotePort());
    Udp.write("recived: ");
    Udp.write(packetBuffer);
    Udp.write("\r\n");
    Udp.endPacket();
     }
}
