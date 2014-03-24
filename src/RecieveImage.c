/********************************************************************************
 * 		Filename 	:	RecieveImage.c											*
 *																				*
 *  	Edited on	: 	24 Feb 2014												*
 *      Editor		: 	Hassan Munir 											*/

#include <xdc/cfg/global.h>

#include <ti/ndk/inc/netmain.h>
#include "ti/platform/platform.h"
#include <ti/ndk/inc/serrno.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/System.h>


/* BIOS6 include */
#include <ti/sysbios/BIOS.h>

/* Platform utilities include */
#include "ti/platform/platform.h"

/* Resource manager for QMSS, PA, CPPI */
#include "ti/platform/resource_mgr.h"

#include <xdc/runtime/Types.h>
#include <xdc/runtime/Timestamp.h>

#include "../header/Disparity.h"
#include "../header/Config.h"


#define TCP_BUFSIZE 1024

int SendImage(SOCKET s, uint8_t* image, int size);
uint8_t* RecieveImage(SOCKET s, int filesize);
StereoImage RecieveStereoImage(SOCKET s, int filesize);

int dtask_tcp_echo(SOCKET s, UINT32 unused) {
	printf("hello\n");
	struct timeval to;
	char *message = malloc(sizeof(char) * 50);
	to.tv_sec = 3;
	to.tv_usec = 0;

	int filesize;



	setsockopt(s, SOL_SOCKET, SO_SNDTIMEO, &to, sizeof(to));
	setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &to, sizeof(to));


	//		if(g_transmissionError == 1)
	//			break;


	filesize = WIDTH * HEIGHT;

	StereoImage images = RecieveStereoImage(s, filesize);

	//		if(g_transmissionError == 1)
	//			break;

	int bytesSent = 0;

	//CALCULATIONS

	Types_FreqHz freq;

	Timestamp_getFreq(&freq);

	uint32_t start = Timestamp_get32();
//	uint8_t* image = GetDisparityMap(&images);

//	uint8_t* image = GetDisparityMapInline(images.Left, images.Right);

	uint32_t timeTaken = Timestamp_get32() - start;

	printf("[%f s]\n", (double)timeTaken/freq.lo);

	printf("Sending disparity map..\n");
	bytesSent = SendImage(s, images.Left, filesize);
	if(bytesSent > 0)
		printf("Sent disparity map [%d bytes]\n", bytesSent);

	Memory_free(NULL, images.Left, filesize);
	Memory_free(NULL, images.Right, filesize);
//	Memory_free(NULL, image, filesize);

	return -1;
}

StereoImage RecieveStereoImage(SOCKET s, int filesize)
{
	StereoImage image;
	printf("Receiving left image..\n");
	image.Left = RecieveImage(s, filesize);
	printf("Receiving right image..\n");
	image.Right = RecieveImage(s, filesize);
	return image;
}

uint8_t* RecieveImage(SOCKET s, int filesize)
{
	int bytesReceived, errors, i ;
	bytesReceived = 0;
	errors = 0;

	uint8_t* image;
	uint8_t buffer[TCP_BUFSIZE];

	image = Memory_alloc(NULL, filesize, 8, NULL);

	while(bytesReceived < filesize)
	{
		i = recv(s, buffer, TCP_BUFSIZE,0);
		if( i == 0)
		{
			printf("Connection closed - restart program\n");

			break;
		} else if(i == -1)
		{
			errors++;
			if(errors>=5)
			{

				break;
			}
			printf("Error in transmission [%d]\n",errors);

		}else{
			mmCopy((image + bytesReceived), buffer, i);
			bytesReceived += i;
		}
	}
	printf("Read %d bytes with %d errors\n", bytesReceived, errors);
	return image;
}

int SendImage(SOCKET s, uint8_t* image, int size)
{
	int bytesSent = 0;
	int total = 0;
	while(size > 0)
	{
		bytesSent = send(s, image + total, size,0);
		if(bytesSent > 0)
		{
			size -= bytesSent;
			total += bytesSent;
		}
	}

	return total;
}
