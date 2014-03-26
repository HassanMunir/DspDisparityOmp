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

#define SIZE	5
void parallel()
{
	float A[SIZE][SIZE], b[SIZE], c[SIZE];

	int i,j;
	for (i=0; i < SIZE; i++)
	{
		for (j=0; j < SIZE; j++)
			A[i][j] = (j+1) * 1.0;
		b[i] = 1.0 * (i+1);
		c[i] = 0.0;
	}

	float total = 0.0;

#pragma omp parallel shared(A,b,c,total) private(i) num_threads(4)
	{
		printf("number of threads: %d \n", omp_get_num_threads());
		printf("number of procs: %d \n", omp_get_num_procs());

#pragma omp for private(j) reduction(+:total)
		for (i=0; i < SIZE; i++)
		{
			for (j=0; j < SIZE; j++)
				c[i] += (A[i][j] * b[i]);

			total = total + c[i];
		}
	}
}


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
		if(ReceiveImage(socket, leftImg, filesize) <= 1)
			printf("Receiving left image failed.. \n");

		printf("Receiving right image..\n");
		if(ReceiveImage(socket, rightImg, filesize) <= 1)
			printf("Receiving right image failed.. \n");

		printf("Computing disparity map.. \n");
		startTime = Timestamp_get32();

		GetDisparityMap(leftImg, rightImg, outImg);
		//GetDisparityMapInline(leftImg,rightImg, outImg);

		timeTaken = Timestamp_get32() - startTime;
		printf("Disparity map computation complete [%f s] \n", (double)timeTaken/freq.lo);

		printf("Sending disparity map.. \n");
		if(SendImage(socket, outImg, filesize) <= 1)
			printf("Sending disparity map failed.. \n");

//		parallel();
	}

	Memory_free(NULL, leftImg, filesize);
	Memory_free(NULL, rightImg, filesize);
	Memory_free(NULL, outImg, filesize);

}

