#include "../inc/head.h"


int *nest_index(int length, int height)
{
	int index_len = 8*(length - 1)*(height - 1);
	int *index = (int *)malloc(sizeof(int)*index_len);
	int p_index = 0;
	for(int i = 0;i < height - 1; i ++)
	{
		for(int j = 0; j < length - 1; j++)
		{
			index[p_index] = i * length + j;
			index[p_index+1] = (i + 1)*length + j;
			index[p_index+2] = (i + 1)*length + j + 1;
			index[p_index+3] = -1;

			index[p_index+4] = i * length + j;
			index[p_index+5] = (i + 1)*length + j + 1;
			index[p_index+6] = i * length + j + 1;
			index[p_index+7] = -1;

			p_index += 8;
		}
	}
	return index;
}


