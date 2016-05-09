/*
Copyright (C) 2016 Arturo Guadalupi. All right reserved.

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
*/

#ifndef GO_PRO_H
#define GO_PRO_H

#include "GoPROConstants.h"
#include <Arduino.h>
#include <SPI.h>
#include <WiFi101.h>

#define DEBUG

class GoPROClass
{
  public:
    WiFiClient client;

    int status = WL_IDLE_STATUS;
    bool begin(String networkName, String password);
    bool begin(String networkName, String password, bool device);
    void WiFiStatus(void);

    bool turnOn(void);
    bool turnOff(void);

    bool startCapture(void);
    bool stopCapture(void);

    bool localizationOn(void);
    bool localizationOff(void);

    bool setTimeLapseInterval(float interval);
    bool setContinuousShot(int numberOfShots);
    bool setVideoMode(bool mode);

    bool deleteLast(void);
    bool deleteAll(void);

    bool checkConnection(void);
    void disconnect(void);

#ifdef DEBUG
    void debug(void);
#endif

  private:
    bool cameraOrBacpac;
    String SSID;
    String pwd;
    IPAddress ip;

    String host;
    String bacpacURL;
    String cameraURL;

    bool sendRequest(String thisRequest);
    String listen(void);

#ifdef DEBUG
    String parseCommand(void);
#endif
};
extern GoPROClass GoPRO;

#endif
