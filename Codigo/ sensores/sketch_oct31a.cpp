/*
void setup()
{
  Serial.begin(9600);
  
  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT);
  }
 
//Takes an average of readings on a given pin
//Returns the average
int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 
 
  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;
 
  return(runningValue);
}
 
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
 
void loop()
{
  int uvLevel = averageAnalogRead(UVOUT);
  int refLevel = averageAnalogRead(REF_3V3);
  
  //Use the 3.3V power pin as a reference to get a very accurate output value from sensor
  float outputVoltage = 3.3 / refLevel * uvLevel;
  
  float uvIntensity = mapfloat(outputVoltage, 0.82, 2.8, 0.0, 15.0); //Convert the voltage to a UV intensity level
 
  Serial.print("ML8511 output: ");
  Serial.println(uvLevel);
 
  Serial.print("ML8511 voltage: ");
  Serial.println(outputVoltage);

  int indice;
  int longonda = map(uvLevel, 0, 4095, 0, 1170);
  Serial.println(longonda);

  if (longonda < 50) { indice = 0; }
  else if (longonda < 227) { indice = 1; }
  else if (longonda < 318) { indice = 2; }
  else if (longonda < 408) { indice = 3; }
  else if (longonda < 503) { indice = 4; }
  else if (longonda < 606) { indice = 5; }
  else if (longonda < 696) { indice = 6; }
  else if (longonda < 795) { indice = 7; }
  else if (longonda < 881) { indice = 8; }
  else if (longonda < 976) { indice = 9; }
  else if (longonda < 1079) { indice = 10; }
  else { indice = 11; }

  Serial.println(indice);

  delay(200);
}
*/
/*
  Alberto y Gabriel
  Complete project details at https://RandomNerdTutorials.com/esp32-esp8266-mysql-database-php/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your network credentials
const char* ssid     = "CENTRO";
const char* password = "";

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "https://ultravioletasuperestacion.000webhostapp.com/post-esp-data.php";

// Keep this API Key value to be compatible with the PHP code provided in the project page. 
// If you change the apiKeyValue value, the PHP file /post-esp-data.php also needs to have the same key 
String apiKeyValue = "tPmAT5Ab3j7F9";
String sensorName = "ML8511";
String sensorLocation = "Home";

int UVOUT = 32; //Output from the sensor
int REF_3V3 = 4; //3.3V power on the ESP32 board

void setup()
{
  Serial.begin(115200);
  
  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED)
  { 
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());
}

//Takes an average of readings on a given pin
//Returns the average
int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 
 
  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;
 
  return(runningValue);
}
 
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int indicereturn()
{
  int uvLevel = averageAnalogRead(UVOUT);
  //Serial.println(uvLevel);
  int refLevel = averageAnalogRead(REF_3V3);
  //Serial.println(refLevel);
  
  //Use the 3.3V power pin as a reference to get a very accurate output value from sensor
  float outputVoltage = 3.3 / refLevel * uvLevel;
  
  float uvIntensity = mapfloat(outputVoltage, 0.82, 2.8, 0.0, 15.0); //Convert the voltage to a UV intensity level
  // uvLevel = ML8511 output
  // outputVoltage = ML8511 voltage

  int indice;
  int longonda = map(uvLevel, 0, 4095, 0, 1170);
  //Serial.println(longonda);

  if (longonda < 50) { indice = 0; }
  else if (longonda < 227) { indice = 1; }
  else if (longonda < 318) { indice = 2; }
  else if (longonda < 408) { indice = 3; }
  else if (longonda < 503) { indice = 4; }
  else if (longonda < 606) { indice = 5; }
  else if (longonda < 696) { indice = 6; }
  else if (longonda < 795) { indice = 7; }
  else if (longonda < 881) { indice = 8; }
  else if (longonda < 976) { indice = 9; }
  else if (longonda < 1079) { indice = 10; }
  else { indice = 11; }

  return indice;
}

String intensidadreturn()
{
  int uvLevel2 = averageAnalogRead(UVOUT);
  //Serial.println(uvLevel);
  int refLevel2 = averageAnalogRead(REF_3V3);
  //Serial.println(refLevel);
  
  //Use the 3.3V power pin as a reference to get a very accurate output value from sensor
  float outputVoltage2 = 3.3 / refLevel2 * uvLevel2;
  
  return String(mapfloat(outputVoltage2, 0.82, 2.8, 0.0, 15.0)); //Convert the voltage to a UV intensity level
  // uvLevel = ML8511 output
  // outputVoltage = ML8511 voltage

}
int oneminute = 60000;
void loop()
{
  
  if(WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    
    //Check WiFi connection status
  
    // Your Domain name with URL path or IP address with path
    http.begin(serverName);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare your HTTP POST request data
    String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName
                          + "&location=" + sensorLocation + "&value1=" + String(indicereturn())
                          + "&value2=" + intensidadreturn();

    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);

    // You can comment the httpRequestData variable above
    // then, use the httpRequestData variable below (for testing purposes without the BMP180 sensor)
    //String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BMP180&location=Home&value1=24.75&value2=49.54&value3=1005.14";
    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
     
    // If you need an HTTP request with a content type: text/plain
    //http.addHeader("Content-Type", "text/plain");
    //int httpResponseCode = http.POST("Hello, World!");
    
    // If you need an HTTP request with a content type: application/json, use the following:
    //http.addHeader("Content-Type", "application/json");
    //int httpResponseCode = http.POST("{\"value1\":\"19\",\"value2\":\"67\",\"value3\":\"78\"}");
        
    if (httpResponseCode>0) {
      //Serial.print("HTTP Response code: ");
      //Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request every 30 seconds
  delay(oneminute * 10); 
}

