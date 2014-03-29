/*
 * Workers.h
 *
 *  Created on: 29 Mar 2014
 *      Author: Hassan
 */

#ifndef WORKERS_H_
#define WORKERS_H_

#include <ti/ndk/inc/netmain.h>
#include "Config.h"
#include <stdint.h>

#pragma DATA_SECTION(g_leftImg, ".leftImg")
uint8_t g_leftImg[WIDTH * HEIGHT];

#pragma DATA_SECTION(g_rightImg, ".rightImg")
uint8_t g_rightImg[WIDTH * HEIGHT];

#pragma DATA_SECTION(g_outImg, ".outImg")
uint8_t	g_outImg[WIDTH * HEIGHT];


#pragma DATA_SECTION(g_leftImg1, ".leftImg1")
uint8_t g_leftImg1[WIDTH * HEIGHT];

#pragma DATA_SECTION(g_rightImg1, ".rightImg1")
uint8_t g_rightImg1[WIDTH * HEIGHT];

#pragma DATA_SECTION(g_outImg1, ".outImg1")
uint8_t	g_outImg1[WIDTH * HEIGHT];


void DisparityCalculationWorker(SOCKET s);
void NetworkWorker(SOCKET s);



#endif /* WORKERS_H_ */
