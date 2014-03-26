/*
 * DataTransfer.c
 *
 *  Created on: 25 Mar 2014
 *      Author: Hassan
 */

#include "../header/DataTransfer.h"


int ReceiveImage(SOCKET s,uint8_t* outImg,  int size) {
	int bytesReceived = 0, errors = 0, i;
	while(bytesReceived < size)
	{
		i = recv(s, outImg + bytesReceived, size, 0);
		if(i > 0)
			bytesReceived += i;
		else if(i == -1)
		{
			errors++;
			if(errors >= RETRY_ATTEMPS)
				return -1;
		}
		else if(i == 0)	//connection closed
			return 0;
	}
	return bytesReceived;
}

int SendImage(SOCKET s, uint8_t* img, int size){
	int i, errors = 0, total = 0;
	while(size > 0){
		i = send(s, img + total, size, 0);
		if(i > 0)
		{
			size -= i;
			total += i;
		}
		else if(i == -1)
		{
			errors++;
			if(errors >= RETRY_ATTEMPS)
				return -1;
		}
		else if(i == 0)	//connection closed
			return 0;
	}
	return total;
}


