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


/* BIOS6 include */
#include <ti/sysbios/BIOS.h>

#include <xdc/runtime/Timestamp.h>
#include <xdc/runtime/Types.h>

#include <ti/sysbios/knl/Semaphore.h>
#include <xdc/cfg/global.h>


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

void DisparityCalculationWorker(SOCKET s) {

//	Semaphore_pend(buf1Sem, BIOS_WAIT_FOREVER);
//
//	printf("Computing disparity map.. \n");
//	GetDisparityMapInline(g_leftImg1, g_rightImg1, g_outImg1);
//	printf("Sending disparity map.. \n");
//	SendImage(s, g_outImg1, HEIGHT * WIDTH);
//
//	Semaphore_post(buf1Sem);

	Semaphore_pend(buf0Sem, BIOS_WAIT_FOREVER);

	printf("Computing disparity map.. \n");
	GetDisparityMapInline(g_leftImg, g_rightImg, g_outImg);
	printf("Sending disparity map.. \n");
	SendImage(s, g_outImg, HEIGHT * WIDTH);

	Semaphore_post(buf0Sem);

}

void NetworkWorker(SOCKET s)
{
	Semaphore_pend(buf0Sem, BIOS_WAIT_FOREVER);

	printf("Receiving left image..\n");
	ReceiveImage(s, g_leftImg, HEIGHT * WIDTH);

	printf("Receiving right image..\n");
	ReceiveImage(s, g_rightImg, HEIGHT * WIDTH);

	Semaphore_post(buf0Sem);

//	Semaphore_pend(buf1Sem, BIOS_WAIT_FOREVER);
//
//	printf("Receiving left image..\n");
//	ReceiveImage(s, g_leftImg1, HEIGHT * WIDTH);
//
//	printf("Receiving right image..\n");
//	ReceiveImage(s, g_rightImg1, HEIGHT * WIDTH);
//
//	Semaphore_post(buf1Sem);

}


void Controller(SOCKET s) {
	//
	//#pragma omp parallel
	//	{
	//#pragma omp master
	//		{
	//			NetworkWorker(s);
	//		}
	//#pragma omp single
	//		{
	//			DisparityCalculationWorker(s);
	//		}
	//	}
	while(1){
		NetworkWorker(s);
		//		ImageAcquisitionWorker(s);
		DisparityCalculationWorker(s);
	}


}

