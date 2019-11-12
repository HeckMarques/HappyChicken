/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 2.4.2 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.3.1 or later version;
     - for iOS 1.3.5 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

const int LM35 = A0; // Define o pino que lera a saída do LM35
float temperatura;
char temp;// Variável que armazenará a temperatura medida
int incomingByte;

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT

#include <RemoteXY.h>
// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "HappyChicken"
#define REMOTEXY_WIFI_PASSWORD "galinha123"
#define REMOTEXY_SERVER_PORT 6377


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,2,0,25,0,115,0,8,13,0,
  67,5,26,12,27,8,2,26,21,129,
  0,55,14,18,5,16,67,101,108,115,
  105,117,115,0,7,52,7,35,38,14,
  2,26,2,68,17,57,33,42,21,8,
  36,129,0,18,3,62,7,16,84,101,
  109,112,101,114,97,116,117,114,97,32,
  97,116,117,97,108,58,0,129,0,66,
  27,21,5,16,72,105,115,116,195,179,
  114,105,99,111,0,129,0,3,27,45,
  5,16,84,101,109,112,101,114,97,116,
  117,114,97,32,108,105,109,105,116,101,
  58,0 };
  
// this structure defines all the variables of your control interface 
struct {

    // input variable
  int16_t limite = 22;  // −32767.. +32767 

    // output variable
  char temperaturab[21];  // string UTF8 end zero 
  float grafico;

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////



void setup() 
{
  RemoteXY_Init (); 
  pinMode(7, OUTPUT);
  // TODO you setup code
  
}

void loop() 
{ 
   RemoteXY_Handler ();

  //Obtendo temperatura do sensor
  temperatura = (float(analogRead(LM35))*5/(1023))/0.01;
         
  Serial.println(temperatura);
  Serial.println(RemoteXY.limite);

  // lIGA RELE/VENTOINHA SE ATINGE TEMPERATURA LIMITE
if (temperatura > RemoteXY.limite){ 
  digitalWrite(7, HIGH);
}else if (temperatura < RemoteXY.limite){
   digitalWrite(7, LOW);
  }
  
  // Convertendo em string e enviando temperatura para RemoteXY
  dtostrf(temperatura, 0, 1, RemoteXY.temperaturab);
  RemoteXY.grafico = temperatura;

// Tempo que espera para rodar loop novamente
delay(200);


}
