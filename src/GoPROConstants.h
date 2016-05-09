/*
Copyright (C) 2016 Arturo Guadalupi. All right reserved.

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
*/

// for commands list please refer to https://github.com/KonradIT/goprowifihack/blob/master/HERO3/WifiCommands.md


#ifndef GO_PRO_CONSTANTS_H
#define GO_PRO_CONSTANTS_H

#define CAMERA true
#define BACPAC false

/*Video Modes*/
const int videoMode = 0;
const int photoMode = 1;
const int burstMode = 2;
const int timelapseMode = 3;
const int timerMode = 4;
const int playHDMI = 5;

/*Orientation*/
const int orientationUp = 0;
const int orientationDown = 1;

/*Resolutions*/
const int VRWVGA60 = 0;
const int VRWVGA120 = 1;
const int VRR720_30 = 2;
const int VR720_60 = 3;
const int VR960_30 = 4;
const int VR960_48 = 5;
const int VR1080_30 = 6;

/*Frame Rates*/
const int FPS12 = 0;
const int FPS15 = 1;
const int FPS12p5 = 2;
const int FPS24 = 3;
const int FPS25 = 4;
const int FPS30 = 5;
const int FPS48 = 6;
const int FPS50 = 7;
const int FPS60 = 8;
const int FPS100 = 9;
const int FPS120 = 10;
const int FPS240 = 11;

/*FOV*/
const int wideFOV = 0;
const int mediumFOV = 1;
const int narrowFOV = 2;

/*Photo Resolutions*/
const int photo11mpW = 0;
const int photo8mpW = 1;
const int photo5mpW = 2;
const int photo5mpM = 3;
const int photo12mpW = 4;
const int photo7mpW = 5;
const int photo7mpM = 6;

#define NTSC true
#define PAL false

#endif
