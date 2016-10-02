
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char* data;
	int length;
} pwmConverterOutputSet;

pwmConverterOutputSet pwmConverter( int pwm){

    // Get the decimal and integer portion of the pwm
    int decValue = pwm % 1000 % 100 % 10;
    int intValue = (pwm-decValue) / 10;

	//if given v_target that is larger than v_norm,
	//causing >=100% pwm, output 100%, maximum
	//or if negative, or 0 is given,
    if( intValue >= 100){
    	char* outputAdjusted = malloc( sizeof(char) );
        outputAdjusted[0] = 'm';
        pwmConverterOutputSet outputSet;
    	outputSet.data = outputAdjusted;
    	outputSet.length = 1;
        return outputSet;
    }else if( intValue <= 0 ){
        char* outputAdjusted = malloc( sizeof(char) );
        outputAdjusted[0] = '0';
        pwmConverterOutputSet outputSet;
    	outputSet.data = outputAdjusted;
    	outputSet.length = 1;
        return outputSet;
    }

    // Create variable to store output data
    char* output = malloc( sizeof(char) * 11 );

    // if not max or min, parse each digit.
    int intValueDigits, intValueTens;

    // the digit value
    intValueDigits = intValue % 10;

    // the tens value
    intValueTens = (intValue - intValueDigits)/10;

    // translate
    char theChar[2];
    int theTimes[2];
    if( intValueDigits >= 5){

    	// first char is the tens digit.
		// if given ex. 96%, decrease from 100% ( ie. m)
		if( intValueTens == 9)
			output[0] = 'm';
		else
			output[0] = intValueTens + 1 +'0';


		// decrease to proper unit/decimal digit
		if( decValue >= 5 && intValue != 99 ){
			theChar[0]='-';
			theChar[1]='l';
			theTimes[0]=9-intValueDigits;
			theTimes[1]=10-decValue;
		}else{
			theChar[0]='-';
			theChar[1]='g';
			theTimes[0]=10-intValueDigits;
			theTimes[1]=decValue;
		}
    }else{

    	// first char is the tens digit
    	output[0] = intValueTens + '0';


    	// increase to proper unit/decimal digit
		if( decValue >= 5 ){
			theChar[0]='+';
			theChar[1]='l';
			theTimes[0]=intValueDigits+1;
			theTimes[1]=10-decValue;
		}else{
			theChar[0]='+';
			theChar[1]='g';
			theTimes[0]=intValueDigits;
			theTimes[1]=decValue;
		}

    }

    //printf("%d", intValue);
    for( int i=1; i<=theTimes[0]; i=i+1 ){
    	output[i]=theChar[0];
    }
    for( int i=1; i<=theTimes[1]; i=i+1 ){
    	output[i+theTimes[0]]=theChar[1];
    }

    //resize
    int realLength = theTimes[0]+theTimes[1]+1;
    //printf("RealLength: %d", realLength);
    char* outputAdjusted = malloc( sizeof(char) * realLength );
    for( int i=0; i<realLength; i=i+1){
    	
    	outputAdjusted[i]=output[i];
    	//printf("%c", outputAdjusted[i]);
    }
    free(output);

    pwmConverterOutputSet outputSet;
    outputSet.data = outputAdjusted;
    outputSet.length = realLength;
    return outputSet;
    
}



