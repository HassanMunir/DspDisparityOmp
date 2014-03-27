/*
 * DataTransfer.c
 *
 *  Created on: 25 Mar 2014
 *      Author: Hassan
 */

#include "../header/DataTransfer.h"


int ReceiveImage(SOCKET s,uint8_t* outImg,  int size) {
	int i, bytes = 0;
	while(size > 0)
	{
		i = recv(s, outImg + bytes, size, 0);
		if(i > 0)
		{
			bytes += i;
			size -= i;
		}
	}
	return bytes;
}

int SendImage(SOCKET s, uint8_t* img, int size){
	int i, bytes = 0;
	while(size > 0){
		i = send(s, img + bytes, size, 0);
		if(i > 0)
		{
			bytes += i;
			size -= i;
		}
	}
	return bytes;
}


