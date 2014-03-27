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

extern void GetDisparityMapInline(uint8_t* leftImg, uint8_t* rightImg, uint8_t* outImg);

void Controller(SOCKET socket) {

	int filesize;
	uint8_t *leftImg, *rightImg, *outImg;

	uint32_t startTime, timeTaken;
	Types_FreqHz freq;

	Timestamp_getFreq(&freq);

	filesize = HEIGHT * WIDTH;

	// Allocate memory
	leftImg =  Memory_alloc(NULL, filesize, 8, NULL);
	rightImg =  Memory_alloc(NULL, filesize, 8, NULL);
	outImg =  Memory_alloc(NULL, filesize, 8, NULL);

	while(1)
	{
		printf("Receiving left image..\n");
		ReceiveImage(socket, leftImg, filesize);

		printf("Receiving right image..\n");
		ReceiveImage(socket, rightImg, filesize);

		printf("Computing disparity map.. \n");
		startTime = Timestamp_get32();

//		GetDisparityMap(leftImg, rightImg, outImg);
		GetDisparityMapInline(leftImg,rightImg, outImg);

		timeTaken = Timestamp_get32() - startTime;
		printf("Disparity map computation complete [%f s] \n", (double)timeTaken/freq.lo);

		printf("Sending disparity map.. \n");
		SendImage(socket, outImg, filesize);
	}

	Memory_free(NULL, leftImg, filesize);
	Memory_free(NULL, rightImg, filesize);
	Memory_free(NULL, outImg, filesize);

}

