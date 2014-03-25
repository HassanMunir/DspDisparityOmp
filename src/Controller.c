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
#include "../header/DataTransfer.h"

extern void GetDisparityMapInline(uint8_t* leftImg, uint8_t* rightImg, uint8_t* outImg);


void Controller(SOCKET socket) {
	int filesize;
	double startTime, endTime;

	uint8_t *leftImg, *rightImg, *outImg;

	filesize = HEIGHT * WIDTH;

	// Allocate a working buffer
	leftImg =  Memory_alloc(NULL, filesize, 8, NULL);
	rightImg =  Memory_alloc(NULL, filesize, 8, NULL);
	outImg =  Memory_alloc(NULL, filesize, 8, NULL);

	while(1)
	{
		printf("Receiving left image..\n");
		if(ReceiveImage(socket, leftImg, filesize) <= 1)
			printf("Receiving left image failed.. \n");

		printf("Receiving right image..\n");
		if(ReceiveImage(socket, rightImg, filesize) <= 1)
			printf("Receiving right image failed.. \n");

		printf("Computing disparity map.. \n");

		startTime = omp_get_wtime();
		GetDisparityMapInline(leftImg,rightImg, outImg);
		endTime = (omp_get_wtime() - startTime) / 1000000000;
		printf("Disparity map computation complete [%f s] \n", endTime);

		printf("Sending disparity map.. \n");
		if(SendImage(socket, outImg, filesize) <= 1)
			printf("Sending disparity map failed.. \n");
	}

	Memory_free(NULL, leftImg, filesize);
	Memory_free(NULL, rightImg, filesize);
	Memory_free(NULL, outImg, filesize);

}

