/*
Copyright (C) 2016 Arturo Guadalupi. All right reserved.

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
*/

#include <GoPRO.h>

bool connected = false;

bool GoPROClass::begin(String networkName, String password) {
  return begin(networkName, password, CAMERA);
}

bool GoPROClass::begin(String networkName, String password, bool device) {
#ifdef DEBUG
  Serial.begin(115200);
#endif

  cameraOrBacpac = device;

  SSID = networkName;
  pwd = password;

  char ssid[networkName.length()];
  sprintf(ssid, "%s", networkName.c_str());

  char pass[password.length()];
  sprintf(pass, "%s", password.c_str());

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
#ifdef DEBUG
    Serial.println("WiFi module not detected");
#endif
    // don't continue:
    connected = false;
    return false;
  }

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
#ifdef DEBUG
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
#endif
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  WiFiStatus();
#ifdef DEBUG
  Serial.println();
#endif

  host = "10.5.5.9";
  bacpacURL = "http://" + host + "/bacpac/";
  cameraURL = "http://" + host + "/camera/";

  connected = true;
  return true;
}

void GoPROClass::WiFiStatus() {
  ip = WiFi.localIP();
  long rssi = WiFi.RSSI();

#ifdef DEBUG
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
#endif
}

bool GoPROClass::turnOn(void){
  String requestURL;

  if(cameraOrBacpac == CAMERA){
    requestURL = "GET " + cameraURL + "PW?t=" + pwd + "&p=\%01" + " HTTP/1.1";
  }
  else{
    requestURL = "GET " + bacpacURL + "PW?t=" + pwd + "&p=\%00" + " HTTP/1.1";
  }

  return(sendRequest(requestURL));
}

bool GoPROClass::turnOff(void){
  String requestURL;

  if(cameraOrBacpac == CAMERA){
    requestURL = "GET " + cameraURL + "PW?t=" + pwd + "&p=\%00" + " HTTP/1.1";
  }
  else{
    requestURL = "GET " + bacpacURL + "PW?t=" + pwd + "&p=\%00" + " HTTP/1.1";
  }

  return(sendRequest(requestURL));
}

bool GoPROClass::localizationOn(void){
  String requestURL;

  if(cameraOrBacpac == CAMERA){
    requestURL = "GET " + cameraURL + "LL?t=" + pwd + "&p=\%01" + " HTTP/1.1";
  }
  else{
    requestURL = "GET " + bacpacURL + "LL?t=" + pwd + "&p=\%01" + " HTTP/1.1";
  }

  return(sendRequest(requestURL));
}

bool GoPROClass::localizationOff(void){
  String requestURL;

  if(cameraOrBacpac == CAMERA){
    requestURL = "GET " + cameraURL + "LL?t=" + pwd + "&p=\%00" + " HTTP/1.1";
  }
  else{
    requestURL = "GET " + bacpacURL + "LL?t=" + pwd + "&p=\%00" + " HTTP/1.1";
  }

  return(sendRequest(requestURL));
}

bool GoPROClass::startCapture(void){
  String requestURL;

  if(cameraOrBacpac == CAMERA){
    requestURL = "GET " + cameraURL + "SH?t=" + pwd + "&p=\%01" + " HTTP/1.1";
  }
  else{
    requestURL = "GET " + bacpacURL + "SH?t=" + pwd + "&p=\%01" + " HTTP/1.1";
  }

  return(sendRequest(requestURL));
}

bool GoPROClass::stopCapture(void){
  String requestURL;

  if(cameraOrBacpac == CAMERA){
    requestURL = "GET " + cameraURL + "SH?t=" + pwd + "&p=\%00" + " HTTP/1.1";
  }
  else{
    requestURL = "GET " + bacpacURL + "SH?t=" + pwd + "&p=\%00" + " HTTP/1.1";
  }

  return(sendRequest(requestURL));
}

bool GoPROClass::setTimeLapseInterval(float interval){
  String requestURL;
  String stringInterval;

  if(interval == 0.5) stringInterval = "00";
  else if(interval == 1) stringInterval = "01";
  else if(interval == 5) stringInterval = "05";
  else if(interval == 10) stringInterval = "0a";
  else if(interval == 30) stringInterval = "0e";
  else stringInterval = "0c";

  if(cameraOrBacpac == CAMERA){
    requestURL = "GET " + cameraURL + "TI?t=" + pwd + "&p=\%" + stringInterval + " HTTP/1.1";
  }
  else{
    requestURL = "GET " + bacpacURL + "TI?t=" + pwd + "&p=\%" +stringInterval + " HTTP/1.1";
  }

  return(sendRequest(requestURL));
}

bool GoPROClass::setContinuousShot(int numberOfShots){
  String requestURL;
  String stringShots;

  if(numberOfShots == 0) stringShots = "00";
  else if(numberOfShots == 3) stringShots = "03";
  else if(numberOfShots == 5) stringShots = "05";
  else stringShots = "0a";

  if(cameraOrBacpac == CAMERA){
    requestURL = "GET " + cameraURL + "CS?t=" + pwd + "&p=\%" + stringShots + " HTTP/1.1";
  }
  else{
    requestURL = "GET " + bacpacURL + "CS?t=" + pwd + "&p=\%" + stringShots + " HTTP/1.1";
  }

  return(sendRequest(requestURL));
}

bool GoPROClass::setVideoMode(bool mode){
  String requestURL;
  String videoMode;

  if(mode == NTSC) videoMode = "00";
  else videoMode = "01";

  if(cameraOrBacpac == CAMERA){
    requestURL = "GET " + cameraURL + "CS?t=" + pwd + "&p=\%" + videoMode + " HTTP/1.1";
  }
  else{
    requestURL = "GET " + bacpacURL + "CS?t=" + pwd + "&p=\%" +videoMode + " HTTP/1.1";
  }

  return(sendRequest(requestURL));
}

bool GoPROClass::deleteLast(void){
  String requestURL;

  if(cameraOrBacpac == CAMERA){
    requestURL = "GET " + cameraURL + "DL?t=" + pwd + " HTTP/1.1";
  }
  else{
    requestURL = "GET " + bacpacURL + "DL?t=" + pwd + " HTTP/1.1";
  }

  return(sendRequest(requestURL));
}

bool GoPROClass::deleteAll(void){
  String requestURL;

  if(cameraOrBacpac == CAMERA){
    requestURL = "GET " + cameraURL + "DA?t=" + pwd + " HTTP/1.1";
  }
  else{
    requestURL = "GET " + bacpacURL + "DA?t=" + pwd + " HTTP/1.1";
  }

  return(sendRequest(requestURL));
}

#ifdef DEBUG
void GoPROClass::debug(void) {
  String command = parseCommand();
  if (command == "CAMERA")
    cameraOrBacpac = CAMERA;
  if (command == "BACPAC")
    cameraOrBacpac = BACPAC;
  if (command == "turnOn")
    turnOn();
  if (command == "turnOff")
    turnOff();
  if (command == "localizationOn")
    localizationOn();
  if (command == "localizationOff")
    localizationOff();
  if (command == "startCapture")
    startCapture();
  if (command == "stopCapture")
    stopCapture();
  if (command == "deleteLast")
    deleteLast();
  if (command == "deleteAll")
    deleteAll();
}

String GoPROClass::parseCommand(void) {
  while (Serial.available() > 0)
    return Serial.readString();

  return "";
}
#endif

bool GoPROClass::checkConnection(void){
    return connected;
}

void GoPROClass::disconnect(void){
  //  WiFi.end();
}

/* Provate utility functions*/
bool GoPROClass::sendRequest(String thisRequest){
  client.stop();
  if (!client.connect(host.c_str(), 80)) {
#ifdef DEBUG
    Serial.println("Connection failed");
    connected = false;
#endif
    return false;
  }

  client.println(thisRequest);
  client.println("Connection: close");
  client.println();
#ifdef DEBUG
  Serial.println(thisRequest);
  Serial.println("Connection: close");
  Serial.println();
#endif
  if(listen() == "HTTP/1.1 200 OK\r"){
    return true;
  }
  else{
    return false;
  }

}

String GoPROClass::listen(void){
  unsigned long startTime = millis();
  String response;
  bool stopResponse = false;

  while(millis() - startTime < 3000){ //listen for 3 seconds
    while(client.available()){
      char c = client.read();
#ifdef DEBUG
      Serial.print(c);
#else
      client.read();
#endif
      if(c == '\n')
        stopResponse = true;

      if(!stopResponse){
        response += c;
      }
    }
  }
#ifdef DEBUG
  Serial.println();
  Serial.print("Parsed response is:\t");
  Serial.println(response);
  Serial.println();
#endif

  return response;
}

GoPROClass GoPRO;
