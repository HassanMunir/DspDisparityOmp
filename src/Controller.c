/*
 * Controller.c
 *
 *  Created on: 25 Mar 2014
 *      Author: Hassan
 */

#include "stdint.h"
#include <stdio.h>
#include <xdc/runtime/Memory.h>
#include <ti/omp/omp.h>

#include "../header/Controller.h"
#include "../header/Disparity.h"
#include "../header/DataTransfer.h"
#include <xdc/runtime/Timestamp.h>
#include <xdc/runtime/Types.h>

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

extern void GetDisparityMapInline(uint8_t* leftImg, uint8_t* rightImg, uint8_t* outImg);

void DisparityCalculationWorker(Socket s) {

	printf("Computing disparity map.. \n");
	GetDisparityMapInline(g_leftImg, g_rightImg, g_outImg);
	printf("Sending disparity map.. \n");
	SendImage(s, g_outImg, HEIGHT * WIDTH);
}

void ImageAcquisitionWorker(SOCKET s) {

		printf("Receiving left image..\n");
		ReceiveImage(s, g_leftImg, HEIGHT * WIDTH);

		printf("Receiving right image..\n");
		ReceiveImage(s, g_rightImg, HEIGHT * WIDTH);

}



void Controller(SOCKET s) {

	while(1)
	{
		ImageAcquisitionWorker(s);
		DisparityCalculationWorker(s);

	}

}

