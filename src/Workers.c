/*
 * Workers.c
 *
 *  Created on: 29 Mar 2014
 *      Author: Hassan
 */

#include "../header/Workers.h"
#include "../header/DataTransfer.h"

void DisparityCalculationWorker(SOCKET s) {


	while(1)
	{

		//#pragma omp critical
		{
			printf("Computing disparity map.. \n");
			GetDisparityMapInline(g_leftImg1, g_rightImg1, g_outImg1);
			printf("Sending disparity map.. \n");
			SendImage(s, g_outImg1, HEIGHT * WIDTH);
		}

		//#pragma omp critical
		{

			printf("Computing disparity map.. \n");
			GetDisparityMapInline(g_leftImg, g_rightImg, g_outImg);
			printf("Sending disparity map.. \n");
			SendImage(s, g_outImg, HEIGHT * WIDTH);
		}
	}

}

void NetworkWorker(SOCKET s) {

	while(1)
	{
		//#pragma omp critical
		{

			printf("Receiving left image..\n");
			ReceiveImage(s, g_leftImg, HEIGHT * WIDTH);

			printf("Receiving right image..\n");
			ReceiveImage(s, g_rightImg, HEIGHT * WIDTH);


		}

		//#pragma omp critical
		{
			printf("Receiving left image..\n");
			ReceiveImage(s, g_leftImg1, HEIGHT * WIDTH);

			printf("Receiving right image..\n");
			ReceiveImage(s, g_rightImg1, HEIGHT * WIDTH);

		}
	}
}
