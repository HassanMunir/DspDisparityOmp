/*
 * udpHello.c
 *
 * This program implements a UDP echo server, which echos back any
 * input it receives.
 *
 * Copyright (C) 2007 Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/********************************************************************************
 * 		Filename 	:	ImgRecv.c												*
 *																				*
 *  	Edited on	: 	5 Jul 2013												*
 *      Editor		: 	Chee Kin Chan (receiving images)                      	*/

#include <xdc/cfg/global.h>

#include <ti/ndk/inc/netmain.h>
#include "ti/platform/platform.h"
//#include <ti/ndk/inc/serrno.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/System.h>

/* BIOS6 include */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>

/* Platform utilities include */
#include "ti/platform/platform.h"

/* Resource manager for QMSS, PA, CPPI */
#include "ti/platform/resource_mgr.h"

//Pothole Detection
#include "pothole.h"

#define UDP_BUFSIZ 1020
#define UDP_BUFSIZ_recv 1020
#define Window_SIZE 2
#define packet_header_recv 3
#define packet_header_send 2

//
// dtask_udp_hello() - UDP Echo Server Daemon Function
// (SOCK_DGRAM, port 7)
//
// Returns "1" if socket 's' is still open, and "0" if its been closed
//

typedef struct stereo_image {
	unsigned char* image_l;
	unsigned char* image_r;
} Stereo;

Stereo receiveData(SOCKET s, int filesize);
void SendData(SOCKET s, int filesize, unsigned char *image, struct sockaddr_in sin1);
void SendAck(SOCKET s, struct sockaddr_in sin1);
void SendStartAck(SOCKET s, struct sockaddr_in sin1);
void SendRetryLength(SOCKET s, struct sockaddr_in sin1);
void SendReadyReceive(SOCKET s, struct sockaddr_in sin1);
void waitAck(SOCKET s, struct sockaddr_in sin1);
void SendImageLength(SOCKET s, struct sockaddr_in sin1, int filesize);
int img_in = 2;

int dtask_udp_hello(SOCKET s, UINT32 unused) {
	struct sockaddr_in sin1;
	struct timeval to;
	int i, tmp;
	char *recv_width, *recv_height;
	char *input_number;
	HANDLE hBuffer;
	int image_width, image_height;

	(void) unused;
	System_printf("udp here\n");

	// Configure our socket timeout to be 3 seconds
	to.tv_sec = 3;
	to.tv_usec = 0;
	setsockopt(s, SOL_SOCKET, SO_SNDTIMEO, &to, sizeof(to));
	setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &to, sizeof(to));

	for (;;) {

		tmp = sizeof(sin1);
//		Get number of inputs
		i = (int) recvncfrom(s, (void **) &input_number, 0, (PSA) &sin1, &tmp,
				&hBuffer);
		if (i > 0) {
			img_in = atoi(input_number);
		} else {
			System_printf("Input Failed\n");
		}
		recvncfree(hBuffer);
		//		Gets the Image Width
		i = (int) recvncfrom(s, (void **) &recv_width, 0, (PSA) &sin1, &tmp,
				&hBuffer);
		if (i > 0) {
			image_width = atoi(recv_width);
		}
		recvncfree(hBuffer);
		//		Gets the Image Height
		i = (int) recvncfrom(s, (void **) &recv_height, 0, (PSA) &sin1, &tmp,
				&hBuffer);
		if (i > 0) {
			image_height = atoi(recv_height);
		}

		if (image_width > 0 && image_height > 0) {
			// Converts the packet data into an integer telling the file size.
			int filesize = image_width * image_height;
			if (filesize > 0) {
				// Free the buffer holding the packet data.
				recvncfree(hBuffer);
				// Sends a starting acknowledgement to the host PC.
				// to start sending the images.
				SendStartAck(s, sin1);
				Stereo images = receiveData(s, filesize);
				if (img_in == 2) {
//					Notify_sendEvent(1, 0, 10, (UInt32) &images, TRUE);
//					Semaphore_pend(mySem0, BIOS_WAIT_FOREVER);
//					Semaphore_pend(mySem0, BIOS_WAIT_FOREVER);
//					SendReadyReceive(s, sin1);
//					SendImageLength(s, sin1, filesize);
//					SendData(s, filesize, completeImage, sin1);
//					Memory_free(NULL, images.image_l, filesize);
//					Memory_free(NULL, images.image_r, filesize);
				} else {

//					SendReadyReceive(s, sin1);
//					SendImageLength(s, sin1, filesize);
//					SendData(s, filesize, images.image_l, sin1);
//					Memory_free(NULL, images.image_l, filesize);


					unsigned char *results = potholeDetection(images.image_l,image_width,image_height);
					Memory_free(NULL, images.image_l, filesize);
					SendReadyReceive(s, sin1);
					SendImageLength(s, sin1, filesize);
					SendData(s, filesize, results, sin1);
					Memory_free(NULL, results, filesize);
				}
			} else {
				System_printf("Retrying\n");
				SendRetryLength(s, sin1);
				recvncfree(hBuffer);
				break;
			}

		} else {
			System_printf("Retrying\n");
			SendRetryLength(s, sin1);
			recvncfree(hBuffer);
			break;
		}
		break;
	}

	// Since the socket is still open, return "1"
	// (we need to leave UDP sockets open)
	return (1);
}

// Receive image data from the host PC
Stereo receiveData(SOCKET s, int filesize) {
	HANDLE hBuffer;
	struct sockaddr_in sin1;
	int tmp;
	int count = 0;
	int packet_number;
	int currentWindow = Window_SIZE;
	UChar *pBuf;
	int byte;
	Stereo images;
	int z;
	// Calculates the number of packets that is being received
	if (filesize % UDP_BUFSIZ_recv == 0) {
		packet_number = filesize / UDP_BUFSIZ_recv;
	} else {
		packet_number = filesize / UDP_BUFSIZ_recv + 1;
	}
	// Allocate memory for the left and right image
	images.image_l = Memory_alloc(NULL, filesize, 1, NULL);
	if (img_in == 2) {
		images.image_r = Memory_alloc(NULL, filesize, 1, NULL);
	}
	if (packet_number > 1) {
		// Receives a pair of image
		while (count < packet_number) {
			for (z = 0; z < img_in; ++z) {
				byte = (int) recvncfrom(s, (void **) &pBuf, 0, (PSA) &sin1,
						&tmp, &hBuffer);
				if (byte > 0) {
					if (count < packet_number - 1) {
						// Checks if its left image or right image
						if (pBuf[2] == 'L') {
							// Copy packet data to desired memory location
							mmCopy(
									images.image_l
											+ (pBuf[0] + (pBuf[1] * 256))
													* UDP_BUFSIZ_recv,
									pBuf + packet_header_recv, UDP_BUFSIZ_recv);
						} else {
							mmCopy(
									images.image_r
											+ (pBuf[0] + pBuf[1] * 256)
													* UDP_BUFSIZ_recv,
									pBuf + packet_header_recv, UDP_BUFSIZ_recv);
						}
					} else {
						if (pBuf[2] == 'L') {
							mmCopy(
									images.image_l
											+ (pBuf[0] + (pBuf[1] * 256))
													* UDP_BUFSIZ_recv,
									pBuf + packet_header_recv, byte);
						} else {
							mmCopy(
									images.image_r
											+ (pBuf[0] + (pBuf[1] * 256))
													* UDP_BUFSIZ_recv,
									pBuf + packet_header_recv, byte);
						}
					}
					count++;
					recvncfree(hBuffer);
				} else {
					System_printf("Error receiving : %d\n", fdError());
				}
			}

			// Checks if the window size is reached. If yes, send an acknowledgement to host PC.
			if (count == currentWindow && count < packet_number - 1) {
				currentWindow += Window_SIZE;
				SendAck(s, sin1);
			}
		}
	} else {
		byte = (int) recvncfrom(s, (void **) &pBuf, 0, (PSA) &sin1, &tmp,
				&hBuffer);
		mmCopy(images.image_l + (pBuf[0] + (pBuf[1] * 256)) * UDP_BUFSIZ_recv,
				pBuf + packet_header_recv, filesize);
		recvncfree(hBuffer);
	}
	return images;
}

// Send resulting image data to the host PC
void SendData(SOCKET s, int filesize, unsigned char *image, struct sockaddr_in sin1) {
	int totalsize = 0;
	UInt32 var = 0;
	int byte;
	int currentWindow = Window_SIZE;
	unsigned char *buf = (unsigned char *)Memory_alloc(NULL, UDP_BUFSIZ + packet_header_send, 1, NULL);
	while (1) {
		if ((filesize - totalsize) > UDP_BUFSIZ) {
			buf[0] = var & 127;
			buf[1] = var >> 7;
			mmCopy(buf + packet_header_send, image + totalsize, UDP_BUFSIZ * sizeof(unsigned char));
			// Sends packet buf to the host PC
			byte = sendto(s, buf, UDP_BUFSIZ + packet_header_send, 0,
					(PSA) &sin1, sizeof(sin1));
			if (byte == -1) {
				System_printf("error sending : %d\n", fdError());
			}
			totalsize += UDP_BUFSIZ;
		} else {
			buf[0] = var & 127;
			buf[1] = var >> 7;
			mmCopy(buf + packet_header_send, image + totalsize,
					filesize - totalsize);
			byte = sendto(s, buf, filesize - totalsize + packet_header_send, 0,
					(PSA) &sin1, sizeof(sin1));
			break;
		}
		var++;
		if (var == currentWindow) {
			currentWindow += Window_SIZE;
			waitAck(s, sin1);
		}
	}
	Memory_free(NULL, buf, UDP_BUFSIZ + packet_header_send);
}

// Sends a packet to tell the host PC to start sending images.
void SendStartAck(SOCKET s, struct sockaddr_in sin1) {
	char* pBuf = "O";
	int i = sendto(s, pBuf, 1, 0, (PSA) &sin1, sizeof(sin1));
	return;
}

// Sends a packet to ask the host PC to resend the length of the image.
void SendRetryLength(SOCKET s, struct sockaddr_in sin1) {
	char* pBuf = "U";
	int i = sendto(s, pBuf, 1, 0, (PSA) &sin1, sizeof(sin1));
	return;
}

// Sends an acknowledgement packet whenever the window size is reached
void SendAck(SOCKET s, struct sockaddr_in sin1) {
	char* pBuf = "A";
	int i = sendto(s, pBuf, 1, 0, (PSA) &sin1, sizeof(sin1));
	return;
}

// Tells the host PC it is to send the disparity results back.
void SendReadyReceive(SOCKET s, struct sockaddr_in sin1) {
	char* pBuf = "R";
	int i = sendto(s, pBuf, 1, 0, (PSA) &sin1, sizeof(sin1));
	return;
}

// Sends the length of the resulting image to the host PC.
void SendImageLength(SOCKET s, struct sockaddr_in sin1, int filesize) {
	// Sends the file size to the host PC
	int header[1];
	header[0] = filesize;
	sendto(s, header, sizeof(header), 0, (PSA) &sin1, sizeof(sin1));
	return;
}

// Waits for acknowledgement from the host PC whenever the
// window size has been reached.
void waitAck(SOCKET s, struct sockaddr_in sin1) {
	char* pBuf;
	int tmp;
	HANDLE hBuffer;
	int byte;
	while (1) {
		tmp = sizeof(sin1);
		byte = (int) recvncfrom(s, (void **) &pBuf, 0, (PSA) &sin1, &tmp,
				&hBuffer);
		if (byte > 0 && pBuf[0] == 'A') {
			recvncfree(hBuffer);
			return;
		}
	}
}

