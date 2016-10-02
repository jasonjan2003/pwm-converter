#include <stdio.h>
#include <stdlib.h>
#include "pwmConverter.h"

int main(){

	//Pwmascii output= pwmConverter( 554 );
	//printf("%d", output.pos);
	//for (int i = 0; i < output.pos; ++i)
	//{
	//	printf("%c, ", output.arr[i]);
	//}
	int test = 555;
	pwmConverterOutputSet outputSet = pwmConverter(test);
	char* outputData = outputSet.data;
	int length = outputSet.length;
	for(int i=0; i< length; i=i+1){
		printf("%c", outputData[i]);
	}
	printf("\n");
	//free(outputSet);

	return 0;
}