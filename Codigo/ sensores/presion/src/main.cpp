#include <HTTPClient.h>
#include <WiFiMulti.h>
#include <WiFiClient.h>
#include <SFE_BMP180.h>
#include <Wire.h>

const char* ssid ="Insertar_wifi";
const char* password ="Insrtar_contraseña";


float f;
float h = 0;
double p;
double t;
float hif;
float hic;

WiFiClient client;
SFE_BMP180 pressure;

void setupsensor(){
  Serial.println("REBOOT");
  if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    Serial.println("BMP180 init fail\n\n");
    while(1); // Pause forever.
  }
}


}

void presion(){
  char status;
  status = pressure.startPressure(3);
  if (status != 0)
  {
    delay(status);
    status = pressure.getPressure(p,t);    
  }
  delay(5000);
}

void EnvioDatos(){
  if (WiFi.status() == WL_CONNECTED){ 
     HTTPClient http;  

     String datos_a_enviar = "temperatura=" + String(t) + "&presion=" + String(p);  

     http.begin(client,"http://insertarbasedatos.000webhostapp.com//EspPost.php");
     http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 

     int codigo_respuesta = http.POST(datos_a_enviar);



     if (codigo_respuesta>0){
      Serial.println("Código HTTP: "+ String(codigo_respuesta));
        if (codigo_respuesta == 200){
          String cuerpo_respuesta = http.getString();
          Serial.println("El servidor respondió: ");
          Serial.println(cuerpo_respuesta);
        }
      }

      else {
        Serial.print("Error enviado POST, código: ");
        Serial.println(codigo_respuesta);
      }



       http.end(); 
       
  } else {
     Serial.println("Error en la conexion WIFI");
  }
  delay(50000); 
}

void Conexionwifi(){
  WiFi.begin(ssid, password);
  Serial.print("Conectando...");

  while (WiFi.status()!= WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Conexión OK!");
  Serial.print("IP Local: ");
  Serial.println(WiFi.localIP());
}


void setup() {
  Serial.begin(115200);
  setupsensor();
  Conexionwifi();

}

void loop() {
  presion();
  EnvioDatos();
}


  

