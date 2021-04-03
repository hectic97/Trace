#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sfp.h"


int main(int argc, char *argv[])
{
	FILE *input_file;
	FILE *answer_file;
	FILE *output_file;
	
	input_file = fopen(argv[1], "r");
	answer_file = fopen(argv[2], "r");
	output_file = fopen("output.txt", "w");
	

	sfp *sfp1;
	sfp *sfp2;
	char **bit_1;
	char **bit_2;
	char *add_result;


	char ans[17];

	int data_1;
	int data_2;


	int index;
	int a;
	int b;
	int i;
	int j;





	


	//TEST 1
	float f_1;
	float f_2;
	fscanf(input_file, "%d", &data_1);
	printf("Test 1: casting from int to sfp\n");
	
	bit_1 = (char**)malloc(sizeof(char*)*data_1);
	sfp1 = (sfp*)malloc(sizeof(sfp)*data_1);
	
	for(index = 0; index < data_1; index++)
	{
		fscanf(input_file, "%d", &i);
		fscanf(answer_file, "%s", ans);

		sfp1[index] = int2sfp(i);
		bit_1[index] = sfp2bits(sfp1[index]);
		
		
		fprintf(output_file, "%s\n", bit_1[index]);
		printf("int(%d) => sfp(%s), ", i, bit_1[index]);
		if(strcmp(bit_1[index], ans))
			printf("WRONG\n");
		else
			printf("CORRECT\n");
	}
	fprintf(output_file, "\n");
	printf("\n");

	// TEST 2
	printf("Test 2: casting from sfp to int\n");
	for(index = 0; index < data_1; index++)
	{
		i = sfp2int(sfp1[index]);

		
		fscanf(answer_file, "%d", &j);		
		fprintf(output_file, "%d\n", i);
		printf("sfp(%s) => int(%d), ", bit_1[index], i);
		if(i != j)
		{
			printf("WRONG\n");
		}
			
		else
		{
			printf("CORRECT\n");
		}
			
	}

	fprintf(output_file, "\n");
	printf("\n");


	// TEST 3
	printf("Test 3: casting from float to sfp\n");
	fscanf(input_file, "%d", &data_2);


	bit_2 = (char**)malloc(sizeof(char*)*data_2);
	sfp2 = (sfp*)malloc(sizeof(sfp)*data_2);
	
	for(index = 0; index < data_2; index++)
	{
		fscanf(input_file, "%f", &f_1);
		fscanf(answer_file, "%s", ans);

		sfp2[index] = float2sfp(f_1);
		bit_2[index] = sfp2bits(sfp2[index]);


		fprintf(output_file, "%s\n", bit_2[index]);
		printf("float(%f) => sfp(%s), ", f_1, bit_2[index]);
		if(strcmp(bit_2[index], ans))
		{
			printf("WRONG\n");
		}
		else
		{
			printf("CORRECT\n");
		}
			
	}
	fprintf(output_file, "\n");
	printf("\n");

	// TEST 4
	printf("Test 4: casting from sfp to float\n");
	for(index = 0; index < data_2; index++)
	{
		fscanf(answer_file, "%f", &f_2);

		f_1 = sfp2float(sfp2[index]);


		fprintf(output_file, "%f\n", f_1);
		printf("sfp(%s) => float(%f), ", bit_2[index], f_1);

		if(f_1 != f_2)
		{
			printf("WRONG\n");
		}
		
		else
		{
			printf("CORRECT\n");
		}
			
	}


	fprintf(output_file, "\n");
	printf("\n");


	// TEST 5

	printf("Test 5: Addition\n");


	for(a = 0; a < data_1; a++)
	{
		for(b = a; b < data_1; b++)
		{
			sfp result = sfp_add(sfp1[a], sfp1[b]);
			add_result = sfp2bits(result);


			fscanf(answer_file, "%s", ans);
			fprintf(output_file, "%s\n", add_result);


			printf("%s + %s = %s, ", bit_1[a], bit_1[b], add_result);

			if(strcmp(add_result, ans))
			{
				printf("WRONG\n");
			}
				
			else
			{
				printf("CORRECT\n");
			}
				

			// FREE memory
			free(add_result);
		}
	}

	for(a = 0; a < data_2; a++)
	{
		for(b = a; b < data_2; b++)
		{
			sfp result = sfp_add(sfp2[a], sfp2[b]);

			add_result = sfp2bits(result);


			fscanf(answer_file, "%s", ans);
			fprintf(output_file, "%s\n", add_result);
			printf("%s + %s = %s, ", bit_2[a], bit_2[b], add_result);


			if(strcmp(add_result, ans))
			{
				printf("WRONG\n");
			}
				
			else
			{
				printf("CORRECT\n");
			}
				
			free(add_result);
		}
	}


	for(a = 0; a < data_1; a++)
	{
		for(b = 0; b < data_2; b++)
		{
			sfp result = sfp_add(sfp1[a], sfp2[b]);
			add_result = sfp2bits(result);

			fscanf(answer_file, "%s", ans);
			fprintf(output_file, "%s\n", add_result);


			printf("%s + %s = %s, ", bit_1[a], bit_2[b], add_result);
			if(strcmp(add_result, ans))
			{
				printf("WRONG\n");
			}
				
			else
			{
				printf("CORRECT\n");
			}
				
			free(add_result);
		}
	}

	fprintf(output_file, "\n");
	printf("\n");

	// TEST 6
	printf("TEST 6: Multiplication\n");
	printf("\n");

	// FREE allocated memory and close file
	for(index = 0; index < data_1; index++)
	{
		free(bit_1[index]);
	}
	for(index = 0; index < data_2; index++)
	{
		free(bit_2[index]);
	
	}
	fclose(input_file);
	fclose(answer_file);
	fclose(output_file);
	


	free(bit_1);
	free(bit_2);
	free(sfp1);
	free(sfp2);



	return 0;
}