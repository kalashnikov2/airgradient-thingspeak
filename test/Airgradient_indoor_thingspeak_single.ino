// https://esp8266-arduino-spanish.readthedocs.io/es/latest/esp8266wifi/readme.html

#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
int keyIndex = 0; 
unsigned long myChannelNumber = 00000;
const char * myWriteAPIKey = "XYZ";
int number = 0;
WiFiClient  client;
void setup()
{
  Serial.begin(115200);
  Serial.println();
  WiFi.begin("WIFI", "WIFI_PASSWORD");
  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Conectado, dirección IP: ");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);
}

void loop() {
  
  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
  int x = ThingSpeak.writeField(myChannelNumber, 1, number, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  // change the value
  number++;
  if(number > 99){
    number = 0;
  }
  
  delay(20000); // Wait 20 seconds to update the channel again
  
  }
