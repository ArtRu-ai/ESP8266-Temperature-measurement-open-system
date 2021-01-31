#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <Wire.h>
#include <SparkFun_SHTC3.h>

#include <ArduinoJson.h>
#include <base64.h>


#define SEALEVELPRESSURE_HPA (1013.25)

SHTC3 mySHTC3;
String a;
float temperature, humidity, pressure, altitude;

/* Введите SSID и пароль от вашей сети */
char* ssid = "";   // SSID
char* password = "";  // пароль

String authUsername = ""; //Имя пользователя
String authPassword = ""; //Пароль
String auth = base64::encode(authUsername + ":" + authPassword);
const char* serverAddress = "";  // Адрес сервера хранения данных
int port = 80;

void setup() 
{
  Serial.begin(115200);
  while(Serial == false){};
  Wire.begin();
   WiFi.mode(WIFI_OFF);
       
  delay(1000);
  WiFi.mode(WIFI_STA); 
  Serial.println("Connecting to ");
  Serial.println(ssid);

  // подключиться к вашей локальной wi-fi сети
  WiFi.begin(ssid, password);
  
  // проверить, выполнено ли подключение wi-fi сети
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  
  Serial.println(WiFi.localIP());
  
  mySHTC3.begin();
  
}
void loop() 
{
  a="";
  HTTPClient client;
  HTTPClient cl2;
  SHTC3_Status_TypeDef result = mySHTC3.update();
  temperature = mySHTC3.toDegC();
  humidity = mySHTC3.toPercent();
  //client.begin( serverAddress, port);
  DynamicJsonDocument doc(128);

doc["latitude"] = 56.821375;
doc["longitude"] = 60.632042;

JsonObject values = doc.createNestedObject("values");
values["temperature"] = temperature;
values["pressure"] = 0;
values["humidity"] = humidity;
doc["deviceName"] = "ESP_NMTM_103901";
doc["dateTime"] = "";
serializeJson(doc, a);
Serial.println(serverAddress);
client.begin(serverAddress);
client.addHeader("Content-Type", "application/json");
client.addHeader("Authorization: Basic " , auth);
int httpCode = client.POST(a);

 String payload = client.getString();    //Get the response payload

  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
//Ждем 2 сек. 
delay (2000);

//потом отключаемся
client.end();

//Данные будут отправляться каждые 600 сек 
 delay (600000);
  
}

void errorDecoder(SHTC3_Status_TypeDef message)                             // The errorDecoder function prints "SHTC3_Status_TypeDef" resultsin a human-friendly way
{
  switch(message)
  {
    case SHTC3_Status_Nominal : Serial.print("Nominal"); break;
    case SHTC3_Status_Error : Serial.print("Error"); break;
    case SHTC3_Status_CRC_Fail : Serial.print("CRC Fail"); break;
    default : Serial.print("Unknown return code"); break;
  }
}
