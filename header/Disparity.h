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

uint8_t* GetDisparityMap(StereoImage* stereoImage);
static inline uint8_t GetBestMatch(int iWinStart, int iWinEnd,int jWinStart, int jWinEnd, uint8_t* template, StereoImage* stereoImage, int* disparitiesToSearch, int disparitiesToSearchLength);

#endif /* DISPARITY_H_ */
