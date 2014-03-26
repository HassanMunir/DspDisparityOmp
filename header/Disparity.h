/*
 * Disparity.h
 *
 *  Created on: 4 Feb 2014
 *      Author: Hassan
 */

#ifndef DISPARITY_H_
#define DISPARITY_H_

#include "stdint.h"

typedef struct stereo {
	uint8_t* Left;
	uint8_t* Right;
} StereoImage;

void GetDisparityMap(uint8_t* leftImg, uint8_t* rightImg, uint8_t* disparityMap);
inline uint8_t GetBestMatch(int iWinStart, int iWinEnd,int jWinStart, int jWinEnd, uint8_t* leftImg, uint8_t* rightImg, int* disparitiesToSearch, int disparitiesToSearchLength);
#endif /* DISPARITY_H_ */
