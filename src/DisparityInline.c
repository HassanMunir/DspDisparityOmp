/*
 * DisparityInline.c
 *
 *  Created on: 18 Mar 2014
 *      Author: Hassan
 */
#include "../header/Config.h"
#include <stdint.h>
#include <xdc/runtime/Memory.h>
#include <ti/omp/omp.h>

void GetDisparityMapInline(uint8_t* leftImg, uint8_t* rightImg, uint8_t* outImg){

	omp_set_num_threads(8);

	int iWinStart, iWinEnd;
	int i, j;

	/*Bottom row*/
	iWinStart = HEIGHT - WIN_Y - I_SIDE;
	iWinEnd = HEIGHT - WIN_Y + I_SIDE;

#pragma omp parallel
	{
#pragma omp for private(j) firstprivate(i, iWinStart, iWinEnd)
		for(j = WIN_X; j < WIDTH - WIN_X - MAX_DISP ; j++)
		{
			int jWinStart = j - J_SIDE;
			int jWinEnd = j + J_SIDE;

			int jWinStartMatch, jWinEndMatch, currentBestMatch;
			int k, x, y , v;

			float prevCorr = 0, ncc, denLeft, denRight, den, num;

			for(k = 0; k < MAX_DISP; k++)
			{
				jWinStartMatch = jWinStart + k;
				jWinEndMatch = jWinEnd + k;

				denLeft = 0; denRight = 0; num = 0;

#pragma MUST_ITERATE(WIN_Y, WIN_Y)
				for(y = iWinStart; y <= iWinEnd; y++)
				{
					v = jWinStart;

#pragma MUST_ITERATE(WIN_X, WIN_X)
					for(x = jWinStartMatch; x <= jWinEndMatch; x++)
					{
						uint8_t templatePixel = rightImg[y * WIDTH + v];
						uint8_t matchPixel = leftImg[y * WIDTH + x];
						num += (templatePixel * matchPixel);
						denLeft += (matchPixel * matchPixel);
						denRight += (templatePixel * templatePixel);
						v++;
					}
				}

				den = denLeft* denRight;
//							ncc  = (num * num) * (1/den);
				ncc = (num*num) * _rcpsp(den);

				//			ncc = NccCore(leftImg, rightImg, iWinStart, iWinEnd, jWinStart, jWinStartMatch, jWinEndMatch);
				if(ncc > prevCorr)
				{
					prevCorr = ncc;
					currentBestMatch = k;
				}
			}

			outImg[(HEIGHT - WIN_Y) * WIDTH + j] = currentBestMatch;
		}
	}

	//Iterate over the rows
	for(i = HEIGHT - WIN_Y - 1; i > WIN_Y; i--)
	{
		iWinStart = i - I_SIDE;
		iWinEnd = i + I_SIDE;

		//TODO - This is where parallel processing should start
		//Iterate over the columns

#pragma omp parallel
		{
#pragma omp for private(j) firstprivate(i, iWinStart, iWinEnd)
			for(j = WIN_X; j < WIDTH - WIN_X - MAX_DISP - 1; j++)	//the -1 term is added so that the number of iterations are a multiple of 8
			{
				int jWinStart = j - J_SIDE;
				int jWinEnd = j + J_SIDE;

				uint8_t searchRange[9];
				uint8_t searchRangeUnique[9];

				int uniqueCount = 0, uniqueExists;
				int jWinStartMatch, jWinEndMatch, currentBestMatch;
				int k, x, y , v, l, q;

				float prevCorr = 0, ncc, denLeft, denRight, den, num;

				searchRange[0] = outImg[ ((i + 1 )* WIDTH) + (j- 1)] - 1;
				searchRange[3] = outImg[ ((i + 1 )* WIDTH) + (j - 2)] - 1;
				searchRange[6] = outImg[ ((i + 1 )* WIDTH) + (j)] - 1;

				searchRange[1] = searchRange[0] + 1;
				searchRange[2] = searchRange[0] + 2;

				searchRange[4] = searchRange[3] + 1;
				searchRange[5] = searchRange[3] + 2;

				searchRange[7] = searchRange[6] + 1;
				searchRange[8] = searchRange[6] + 2;



				// Find unique values in the search range
				for(l = 0; l < 9; l++)
				{
					if(searchRange[l] > MIN_DISP && searchRange[l] < MAX_DISP )
					{
						uniqueExists = 0;
						for(q = 0; q < uniqueCount; q++)
						{
							if(searchRange[l] == searchRangeUnique[q])
							{
								uniqueExists = 1;
								break;
							}
						}
						if(uniqueExists == 0){
							searchRangeUnique[uniqueCount] = searchRange[l];
							uniqueCount++;
						}
					}
				}


				for(k = 0; k < uniqueCount; k++)
				{
					jWinStartMatch = jWinStart + searchRangeUnique[k];
					jWinEndMatch = jWinEnd + searchRangeUnique[k];

					denLeft = 0; denRight = 0; num = 0;


					for(y = iWinStart; y <= iWinEnd; y++)
					{
						v = jWinStart;

						for(x = jWinStartMatch; x <= jWinEndMatch; x++)
						{
							uint8_t templatePixel = rightImg[y * WIDTH + v];
							uint8_t matchPixel = leftImg[y * WIDTH + x];
							num += (templatePixel * matchPixel);
							denLeft += (matchPixel * matchPixel);
							denRight += (templatePixel * templatePixel);
							v++;
						}
					}

					den = denLeft* denRight;
					//ncc  = (num * num) * (1/den);
					ncc = (num*num) * _rcpsp(den);


					//				ncc = NccCore(leftImg, rightImg, iWinStart, iWinEnd, jWinStart, jWinStartMatch, jWinEndMatch);

					if(ncc > prevCorr)
					{
						prevCorr = ncc;
						currentBestMatch = searchRangeUnique[k];
					}
				}
				outImg[i* WIDTH + j] =  currentBestMatch;
			}
		}
	}
}
