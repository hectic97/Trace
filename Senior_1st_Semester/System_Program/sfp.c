#include "sfp.h"
#include <stdlib.h>
#include <string.h>

typedef unsigned short sfp;

// bias =  2^ (5-1) -1 (5 exp bits)
#define BIAS 15 


sfp int2sfp(int input){
	

    // SPECIAL CASE
    if (!input){ //0
        return 0;
    } 
	else if (input > 65504){ // +inf
        return 31744; 
    } 
	else if (input < -65504){ // -inf
        return 64512; 
    } 
    
    // Initialize variables
    
    sfp result = 0;

    int E = 0;
	int sign=0;
	int frac = 0;
    int exp;
    int i;


    long long rank = 1 ;
    long long bin = 0 ; 
    long long tb ;  


    int index = 0;
    int count = -1;


    int bc = 0; // variable for counting length of bin number
    int bin_rank = 1;

    // move index to 2^15
    index = 32768;

	if (input < 0){

        result = index + result;
		input = input * -1; 
        sign = 1;
        
    }

    // move index 5 times
    index = index / 32;


    // Convert decimal to binary
	while (1)
	{ 

		bin = bin + (input % 2 * rank) ; // convert decimal num to bin
		rank = 10 * rank;

        // count binary rank

		bc = bc + 1; 
		input = input / 2;
		if (!input) {
            // if input became 0 break the loop
			break;
		}
	}


    // check bianry count for adjust binary number
	if (bc > 11)
    {
		while (bc != 11)
        {
			bin /= 10;
			bc = bc - 1;
			
		}
		if (sign) // if sign bit represents 1, negative
			bin = bin + 1;
	}

    // copy binary for saving
	tb = bin;
	while (0 != (tb /= 10)) E++;
	exp = BIAS + E; //exp 
	result = result + (exp * index); 
	
    // Re-initialize rank and tb (variable for copying bin)
    
    rank = 1;
    tb = bin;
	
    // calculate rank by using tb
	while (tb >=10 ) { 
        count = count + 1; // count rank of binary number
        rank = rank * 10; // times 10 for decimal rank
        tb = tb / 10; // move index 
	}

    //set index using count
	for (i = 0; i < count+1; i++) 
		index = index / 2;
    // remove Assumeing 1 (1.xx)
	bin = bin -  rank;


    long long bin_temp;
    // calculate frac 
	while (bin)
	{ 
        bin_temp = bin % 10 * bin_rank;
        frac = frac +  bin_temp ;


        bin_rank *= 2;
		bin /= 10;
	}

    // calculate Final result by adding frac * index to result
	result = result + frac * index;
	
	return result;


}

int sfp2int(sfp input){

    // CHECK SPECIAL CASES

    if (!input){ // input is 0
        return 0;
    }
	if (input == 31744){ // +inf
        return 2147483647; 
    } 
	if ((input/1024)%32 == 31 || input == 64512 ){ // -inf
        return -2147483647;
    } 



    // Initialize variables

    int result = 0;
	int bin = 0;
    

    int cur_pos = 0;
    int bin_count=0;


    int rank = 1;
    int bin_rank=1;


	int E;
    int exp=0;

    // FINDING 1 for starting to convert to int

	cur_pos = 15;
    if (!(input % 2))
	{
        while (1) {
            input = input / 2;
            cur_pos = cur_pos - 1;
            if (input % 2) // if first 1 found break the loop
                break;
        }
    }
	
    
    long long bin_temp ; // variable for saving temporary values
    // Frac parts calculation
    // move current position to 15;
    for (;cur_pos!=5;cur_pos--)
    {
        
        bin_count = bin_count + 1;

		
        bin_temp = input % 2 * rank;
        bin = bin + bin_temp;
    
        rank = rank * 10;
		input = input /2;
    }
    bin = bin + rank;

    // Exp parts calcualtion
    for (;cur_pos;cur_pos--) // if cur_pos is same as  curpos is not 0 (over 0)
    {
        bin_temp = input % 2 * bin_rank;
        exp = exp + bin_temp;

        // rank up (move position)
		bin_rank = bin_rank * 2;
        input = input / 2;
    }
    // exp = E + BIAS
	E = exp - BIAS; 


    // Compare E and binary for Round Process
	if (bin_count > (1 + E)) { 
		while ((E + 1) != bin_count )
        {
            bin_count = bin_count - 1;
			bin = bin / 10;
		}
	}
    // Re-initialize binary_rank to 1
	bin_rank = 1;

    // calculate result with converted binary number and it's rank
    for (;bin;bin /= 10)
    {
        bin_temp = bin % 10 * bin_rank;
        result = result + bin_temp;

        // update rank (move position)
		bin_rank = bin_rank * 2;
    }
	if (input == 1)
        result = result * -1; // convert to negative num
    
    // return final result
	return result;
}



sfp float2sfp(float input){

	float checkSpecialCase;
	if (input < 0) 
	{
		checkSpecialCase = -input;
	}	
	else
	{ 
		checkSpecialCase = input;
	}

	if (0.000001 > checkSpecialCase){ // condition for return 0
		return 0;
	} 
	if (input > 65504){
		return 31744;// + inf
	} 
	if (input < -65504){
		return 64512; // -inf
	} 


	int frac = 0;
	int E = 1;
	int index = 0;

	sfp result = 0;

	int i = 0;
	int temp_int;

	int exp;
	int sign =0;
	int pos_one = 0;


	int ct_int = 0;
	int int_num = 0;
	int bin_int_num = 0;
	
	int rank = 1;
	int frac_position;


	int bin_i = 0;
	int bin_rank = 1;

	int b_array[16];


	// move index to start position;
	index = index + 32768;


	// Initialize binary array
	memset(b_array, 0, sizeof(int)*16); 

	if (0 >= input)
	{ // check sign bits

		sign = 1; // assign 1 to sign bits 
		result = result + index;
		input = input * -1;
	}
	index = index / 32; //move index


	while (input >= 1)
	{
		int_num = int_num + 1;
		input = input - 1;
		
	}
	
	// save original int_num variable

	temp_int = int_num; 

	int temp_rank;
	// convert int_num to binary num

	while (int_num)
	{
		temp_rank = rank * (int_num % 2) ;
		bin_int_num  = bin_int_num + temp_rank;
		// count int +1
		ct_int = ct_int + 1;
		int_num = int_num / 2;
		// 1 position moving
		rank = 10 * rank;
	}
	


	for (i = ct_int - 1; !(i < 0); i--) {
		b_array[i] = bin_int_num % 10;
		// assign b_array[i] remainder of (bin_int_num % 10 )
		// move position
		bin_int_num = bin_int_num / 10;
	}

	// adjust bin_i
	bin_i = bin_i + ct_int;
	
	// Decimal places processing

	while (1) { 
		input = input * 2;

		if (input <= 1) 
			b_array[bin_i] = 0;
		else 
		{
			input = input - 1;
			b_array[bin_i] = 1;
		}
		
		if (input-1 < 0) 
		{
			checkSpecialCase = -1 * (input-1);
		}	
		else
		{ 
			checkSpecialCase = (input - 1);
		}


		if (checkSpecialCase < 0.001) // save binary num
		{ 
			b_array[bin_i] = 1;
			bin_i = bin_i + 1;
			break;
		}


		bin_i = bin_i + 1;
	}


	if (bin_i > 10)
	{ 
		while (bin_i != 10)
		{
			b_array[bin_i] = 0;
			// round to zero process
			bin_i = bin_i - 1;
		}	

		if (sign) // check sign is 1
		{
			if (b_array[bin_i])
			{
				b_array[bin_i] = 0;
				int i = 9;
				while (b_array[i] != 0)
				{
					b_array[i] = 0;
					i = i - 1;
				}
				b_array[i] = 1;
			}
				
			else 
				b_array[bin_i] = 1;
			
		}
	}
	

	// find position of first 1
	while (b_array[pos_one] != 1)
	{ 
		E = E + 1;
		pos_one = pos_one + 1;
	
	}


	// Calculating E
	if (E > 1)
	{ 
		E = -1 * E;
		frac_position = bin_i + E;
	}
	else if (!temp_int){

		E = E * -1;
		frac_position = bin_i + E;

	}

	pos_one = pos_one + 1;

	if (0 < ct_int) 
	{
		frac_position = bin_i - pos_one;
		E = ct_int - 1;
	}
	

	bin_rank = 1;

	// exp = E + BIAS;

	exp = E + BIAS;


	// Add exp * position to result variable
	result = result +  exp * index; 
	

	// set rank(position) of binary number
	for (i = 1; i < frac_position; i++)
	{ 
		bin_rank *= 2;
	}	

	index = index / (2 * bin_rank);
	
	// calculating frac for result
	while (bin_rank) 
	{ 

		// move all position 
		if (b_array[pos_one++] == 1) {
			// add binary rank to frac
			frac = frac + bin_rank;
		}
		bin_rank = bin_rank / 2;
	}
	// add frac * index to result
	result = result +  frac * index; 

	return result;
}

// //START FROM HERE//



float sfp2float(sfp input) {


	// Initialize variables
	int sign;
	int E;
	int exp = 0;
	// Check input is negative
	if (32768 < input) {
		sign = 1;
	}
	else {
		sign = 0;
	}

	int pos_one = 0;
	int	index = 15;
	int bin_rank = 1;


	int rank =1;	
	int frac_position = 0;
	
	//Initialize binary array
	int b_array[16];
	memset(b_array, 0, sizeof(int) * 16); 


	// frac parts calculation
	while (index != 5)
	{ 
		b_array[index] = b_array[index] +  (input % 2);
		// update current point position
		frac_position = frac_position + 1;

		// next num
		index = index - 1;
		input = input / 2;
	}
	pos_one = index;

	// exp parts calculation

	b_array[index] = 1;
	int b_temp = 0;
	while (0 < index)
	{
		// index - 1
		index = index - 1;

		// calculate exp
		b_temp = input % 2 * bin_rank;
		exp = exp + b_temp;

		
		bin_rank = 2 * bin_rank;
		input = input / 2;
		
	}
	bin_rank = 1;
	// exp = E + BIAS
	E = exp - BIAS;


	int decimal_parts = E  + pos_one; 
	// get decimal parts starting position
	
	
	
	int i = 0;
	int temp_i;
	float temp = 0.5;
	float result = 0.0;

	for (i = decimal_parts; i >= 0; i--)
	{
		temp_i = b_array[i] * bin_rank;
		// save [binary array i th elements* binary_rank(value)]

		result = result + temp_i;
		// Add it to result
		bin_rank = 2 * bin_rank;
	}
	
	decimal_parts = decimal_parts + 1;
	
	
	for (i = decimal_parts; i <= 15; i++) {
		// add [rank * binary array's i th value] to result for decimal parts
		result = result + temp * b_array[i];
		// mul 1/2 for move position
		temp = 0.5 * temp;
	}

	if (!sign){
		return result;
	}
	else{
		return -result;
	}
}


int calExp(sfp in)
{
	return (in/1024)%32;
}

// 
int in2posInfCheck(sfp in1, sfp in2, int exp)
{
	// Return +inf
	if (in2 <= 32768){
		return 31744;
	}
	// Return +inf
	else if (exp != 31){
		return 31744;
	}
	// Return NAN
	else
		return 31745;
	
}

int in2negInfCheck(sfp in1, sfp in2, int exp)
{
	// Return -inf
	if (in2 >= 32768){
		return 64512;
	}
	// Return -inf
	else if (exp != 31){
		return 64512;
	}
	// Return NAN
	else
		return 31745;
}

int checkRoundToZero(int temp, sfp in2, int bin_rank)
{
	int con1 = temp;
	int con2 = in2 * bin_rank;

	if (con1 == con2)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int checkLeftShiftPreCondition(int s1, int s2)
{
	int point = 0;
	if (s1&&!s2)
	{
		point = point + 1;
	}
	if (!s1&&s2)
	{
		point = point + 1;
	}
	return point;
}


sfp sfp_add (sfp in1, sfp in2)
{
	int exp_1 = calExp(in1);
	int exp_2 = calExp(in2);


	// Check Special Cases

	// in1 = +inf Case
	if (exp_1 == 31)
	{
		if (32768 > in1){
			return in2posInfCheck(in1, in2, exp_2);
		}
		else if (32768 < in1){
			return in2negInfCheck(in1, in2, exp_2);
		}
		else if (!(!(exp_2 / 1024 > 0  && (exp_2 == 31)) && !(in1 / 1024 > 0))) // 
			return 31745; // Nan
	}

	sfp t;
	if (exp_2 > exp_1)
	{
		// Swap in1 and in2
		t = in2;
		in2 = in1;
		in1 = t;

		// Swap exp1 and exp2
		t = exp_2;
		exp_2 = exp_1;
		exp_1 = t;


	}

	//sign bits of two num
	int sign_1 = 0;
	int sign_2 = 0;
	// check sign bit
	if (32768 < in1)
	{
		sign_1 = 1; 
	}
	
	if (32768 < in2)
	{
		sign_2 = 1;
	}


	// Initialize variables
	int sign = 0;
	int checkRound = 0;
	int expVal = 0;
	

	int bin_rank = 1;
	int i;

	
	




	// If exp_2 not bigger than exp_1
	int temp;
	int exp_temp;
	sfp result = 0;
	int frac;
	if (!(exp_1 < exp_2))
	{
		if (exp_1 <= exp_2)
		{
			exp_temp = 0;
			result = result + exp_1 * 1024;
			in1 = in1 % 1024;
			in2 = in2% 1024;
		}
		else
		{
			exp_temp = exp_1 - exp_2;
			result = result + exp_1 * 1024;
			in1 = in1 % 1024;
			in2 = in2% 1024;
		}

		i = 0;
		while (i < exp_temp)
		{
			bin_rank = 2 * bin_rank;
			i = i + 1;
		}
		temp = 1024 + in2;


		// Check in1 exponential  and in2 exponential are same
		if (bin_rank != 1)
		{ 
			in2 = (in2 + 1024 ) / bin_rank;
		}
		
		// If Both sign bits are 1
		if (sign_1 && sign_2)
		{
			frac = in1 + in2;

			if (bin_rank == 1)
			{
				expVal = expVal + 1024;
				frac = frac / 2;
				sign = 1;
			}
			else if (!(1024 > frac ))
			{
				expVal = expVal + 1024;
				frac = frac / 2;
				sign = 1;
			}
			else
			{
				sign = 1;
			}
			
		}
		
		
		else if (sign_1 && !sign_2)
		{


			if (in1+1024 >= in2)
			{
				frac = in1+1024 - in2;
			}
			else
			{
				frac = in2 - in1 - 1024;
			}

			if (exp_1 > exp_2)
			{
				sign = 1;
			}

		}
		else if (!sign_1&&sign_2)
		{
			if (in1 + 1024 >= in2)
			{
				frac = in1 + 1024 - in2;
			}
			else
			{
				frac = in2 - in1 - 1024;
			}
			if (exp_1 < exp_2)
			{
				sign = 1;
			}
		}

		else
		{
		// calculate frac and Check Right shift 
			frac = in1 + in2;
			if (!(frac < 1024))
			{
				expVal = expVal + 1024;
				frac = frac / 2;
			}
			else if (bin_rank == 1)
			{
				expVal = expVal + 1024;
				frac = frac / 2;
			}
		}
		int round;
		// Check Round to zero
		if (checkRoundToZero(temp, in2, bin_rank))
			round = checkRoundToZero(temp, in2, bin_rank);
		// check for left shifting bit calculation
		if (checkLeftShiftPreCondition(sign_1, sign_2))
		{
			// check frac < 1024
			while (frac < 1024)
			{
				expVal = expVal - 1024;
				frac = 2 * frac;
			}


			frac = frac - 1024;
		}


		frac = expVal + frac;

		if (sign)
		{
			// Additional Calculation for negative num (signbit is 1)
			frac = frac + 32768;
		}
		// result + frac 
		result = result + frac;

		// Round to even
		if (result % 2) 
		{
			// Check round variable
			if (round==1)
			{
				// round to even
				result = result + 1;
			}

		}
	}	
	return result;
}


char* sfp2bits(sfp result){
	int i = 15;

	// Need 17 bytes. (1 + 5 + 10 + 1 NULL VALUE)
	char *final_result = (char*)malloc(17);

	// initialize to '0' all elements of string
	memset(final_result, '0',sizeof(char)*17);

	// Null 
	final_result[16] = 0;

	// if remainder of (result % 2) is 0 : record '0' 
	// else '1'
	while (i+1)
	{
		if (result % 2)
		{
			final_result[i] = '1';
		}
		else
		{
			final_result[i] = '0';
		}

		result =  result / 2;
		i = i - 1;
	}
	return final_result;
}