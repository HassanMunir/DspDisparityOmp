#include "../header/Config.h"

//Assumes both the in and out arrays have a length of 9.
//Returns the number of unique elements in the out array
//Doesn't sort the array. Worst case O(n^2)
//On average O(10n) assuming most inputs have 4 unique values
int GetDisparitiesUnique(int* restrict out, int* restrict in)
{
	int count = 0;
	int exists = 0;
	int l,q;

#pragma MUST_ITERATE(9,9)
	for(l = 0; l < 9; l++)
	{
		if(in[l] > MIN_DISP && in[l] < MAX_DISP )
		{
			exists = 0;

			for(q = 0; q < count; q++)
			{
				if(in[l] == out[q])
				{
					exists = 1;
					break;
				}
			}
			if(exists != 1){
				out[count] = in[l];
				count++;
			}
		}
	}
	return count;
}

//Asumes both the in and out arrays have a length of 9
//Returns the number of unique elements in the out array
//Sorts the array before finding unique elements
int GetDisparitiesSortAndUnique(int* restrict out, int* restrict in)
{
	int x, y, temp, uniqueCount = 0;
	for(x = 0; x < 8; x++)
	{
		for(y = 0; y < 8 - x; y++)
		{
			if(in[y] == in[y+1])
			{
				temp = in[y+1];
				in[y+1] = in[y];
				in[y] = temp;
			}
		}
	}

#pragma MUST_ITERATE(9,9)
	for(x = 0; x < 9; x++)
	{
		if(in[x] < MAX_DISP && in[x] > MIN_DISP && in[x] != in[x+1] )
		{
			out[uniqueCount] = in[x];
			uniqueCount ++;
		}
	}
	return uniqueCount;
}
