/*
 * NccCore.c
 *
 *  Created on: 13 Mar 2014
 *      Author: Hassan
 */

#include <stdint.h>
#include "../header/Config.h"
#include "../header/Disparity.h"
#include <mathlib.h>

float NccCore(uint8_t* restrict leftImg, uint8_t* restrict rightImg, int iWinStart, int iWinEnd, int jWinStartTemplate, int jWinStartMatch, int jWinEndMatch)
{
	uint8_t templatePixel, matchPixel;
	float ncc, denominator;
	float numerator = 0;
	float denominatorRight = 0;
	float denominatorLeft = 0;

	int x,y,v, baseAddr;

	//Telling the compiler to optimise this makes it even slower
	//	_nassert(((int) (leftImg) & 8)==0);
	//	_nassert(((int) (rightImg) & 8)==0);
#pragma MUST_ITERATE(WIN_Y, WIN_Y)
	for(y = iWinStart; y <= iWinEnd; y++)
	{
		v = jWinStartTemplate;
		baseAddr = y * WIDTH;

#pragma MUST_ITERATE(WIN_X, WIN_X)
		for(x = jWinStartMatch; x <= jWinEndMatch; x++)
		{
			templatePixel = rightImg[baseAddr + v];
			matchPixel = leftImg[baseAddr + x];
			numerator += (templatePixel * matchPixel);
			denominatorLeft += (matchPixel * matchPixel);
			denominatorRight += (templatePixel * templatePixel);
			v++;
		}
	}

	denominator = denominatorLeft * denominatorRight;


	//	ncc = numerator * 1/(sqrtsp(denominator));
	//	ncc = numerator * rsqrtsp(denominator);

	ncc  = (numerator * numerator) * _rcpsp(denominator);
	//	ncc  = (numerator * numerator) * (1/denominator);

	return ncc;
	//	return _rcpsp(denominator);
	//	return denominator;
}


float NccCoreUnrolled(uint8_t* restrict leftImg, uint8_t* restrict rightImg, int iWinStart, int iWinEnd, int jWinStartTemplate, int jWinStartMatch, int jWinEndMatch)
{

	uint16_t tempNum1, tempNum2, tempNum3, tempNum4, tempNum5, tempNum6, tempNum7, tempNum8, tempNum9, tempNum10, tempNum11;
	uint16_t tempDenL1, tempDenL2, tempDenL3, tempDenL4, tempDenL5, tempDenL6, tempDenL7, tempDenL8, tempDenL9, tempDenL10, tempDenL11;
	uint16_t tempDenR1, tempDenR2, tempDenR3, tempDenR4, tempDenR5, tempDenR6, tempDenR7, tempDenR8, tempDenR9, tempDenR10, tempDenR11;

	uint64_t numerator = 0, denominatorLeft = 0, denominatorRight = 0;


	float ncc, denominator;
	int x,y,v, baseAddr;
	v = jWinStartTemplate;
	x = jWinStartMatch;

#pragma MUST_ITERATE(WIN_Y, WIN_Y)
	for(y = iWinStart; y <= iWinEnd; y++)
	{
		baseAddr = y * WIDTH;

		tempNum1 = rightImg[baseAddr + v] * leftImg[baseAddr + x];
		tempDenL1 = leftImg[baseAddr + x] * leftImg[baseAddr + x];
		tempDenR1 = rightImg[baseAddr + v] * rightImg[baseAddr + v];

		tempNum2 = rightImg[baseAddr + v + 1] * leftImg[baseAddr + x + 1];
		tempDenL2 = leftImg[baseAddr + x + 1] * leftImg[baseAddr + x + 1];
		tempDenR2 = rightImg[baseAddr + v + 1] * rightImg[baseAddr + v + 1];

		tempNum3 = rightImg[baseAddr + v + 2] * leftImg[baseAddr + x + 2];
		tempDenL3 = leftImg[baseAddr + x + 2] * leftImg[baseAddr + x + 2];
		tempDenR3 = rightImg[baseAddr + v + 2] * rightImg[baseAddr + v + 2];

		tempNum4 = rightImg[baseAddr + v + 3] * leftImg[baseAddr + x + 3];
		tempDenL4 = leftImg[baseAddr + x + 3] * leftImg[baseAddr + x + 3];
		tempDenR4 = rightImg[baseAddr + v + 3] * rightImg[baseAddr + v + 3];

		tempNum5 = rightImg[baseAddr + v + 4] * leftImg[baseAddr + x + 4];
		tempDenL5 = leftImg[baseAddr + x + 4] * leftImg[baseAddr + x + 4];
		tempDenR5 = rightImg[baseAddr + v + 4] * rightImg[baseAddr + v + 4];

		tempNum6 = rightImg[baseAddr + v + 5] * leftImg[baseAddr + x + 5];
		tempDenL6 = leftImg[baseAddr + x + 5] * leftImg[baseAddr + x + 5];
		tempDenR6 = rightImg[baseAddr + v + 5] * rightImg[baseAddr + v + 5];

		tempNum7 = rightImg[baseAddr + v + 6] * leftImg[baseAddr + x + 6];
		tempDenL7 = leftImg[baseAddr + x + 6] * leftImg[baseAddr + x + 6];
		tempDenR7 = rightImg[baseAddr + v + 6] * rightImg[baseAddr + v + 6];

		tempNum8 = rightImg[baseAddr + v + 7] * leftImg[baseAddr + x + 7];
		tempDenL8 = leftImg[baseAddr + x + 7] * leftImg[baseAddr + x + 7];
		tempDenR8 = rightImg[baseAddr + v + 7] * rightImg[baseAddr + v + 7];

		tempNum9 = rightImg[baseAddr + v + 8] * leftImg[baseAddr + x + 8];
		tempDenL9 = leftImg[baseAddr + x + 8] * leftImg[baseAddr + x + 8];
		tempDenR9 = rightImg[baseAddr + v + 8] * rightImg[baseAddr + v + 8];

		tempNum10 = rightImg[baseAddr + v + 9] * leftImg[baseAddr + x + 9];
		tempDenL10 = leftImg[baseAddr + x + 9] * leftImg[baseAddr + x + 9];
		tempDenR10 = rightImg[baseAddr + v + 9] * rightImg[baseAddr + v + 9];

		tempNum11 = rightImg[baseAddr + v + 10] * leftImg[baseAddr + x + 10];
		tempDenL11 = leftImg[baseAddr + x + 10] * leftImg[baseAddr + x + 10];
		tempDenR11 = rightImg[baseAddr + v + 10] * rightImg[baseAddr + v + 10];

		numerator += tempNum1 + tempNum2 +
				tempNum3 +  tempNum4 +
				tempNum5 + tempNum6 +
				tempNum7 + tempNum8 +
				tempNum9 + tempNum10 +
				tempNum11;

		denominatorLeft += tempDenL1 + tempDenL2 +
				tempDenL3 + tempDenL4 +
				tempDenL5 + tempDenL6 +
				tempDenL7 + tempDenL8 +
				tempDenL9 + tempDenL10 +
				tempDenL11;

		denominatorRight += tempDenR1 + tempDenR2 +
				tempDenR3 + tempDenR4 +
				tempDenR5 + tempDenR6 +
				tempDenR7 + tempDenR8 +
				tempDenR9 + tempDenR10 +
				tempDenR11;

	}

	denominator = denominatorLeft * denominatorRight;
//	numerator = numerator * numerator;

//	ncc  = numerator * (1/denominator);
	ncc  = (numerator * numerator) * _rcpsp(denominator);



	return ncc;

}
