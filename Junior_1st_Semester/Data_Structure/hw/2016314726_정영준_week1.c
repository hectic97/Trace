#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(void)
{
	int len=1;
	int i,j;
	int arr[1000];
	char *element;
	char array_elements[5000];
	int input,position;
	printf("Input array elements: ");
	fgets(array_elements,strlen(array_elements),stdin);  // scanf input to array_element until \n inputted
	array_elements[strlen(array_elements) - 1] = '\0';   // delete '\n'
	printf("Input element to insert: ");
	scanf("%d",&input);
	element = strtok(array_elements, " ");        // input value's shape is '17, 15, 16' So have to split 
	arr[0] = atoi(element);                     //change string to int
	
	while(1)
	{
		element = strtok(NULL, " ");            //iteration until there is no ', ' anymore
		if (element == NULL)
			break;
		arr[len] = atoi(element);
		len++;
	}
	while (1)
	{
		printf("Input position where to insert: ");
		scanf("%d",&position);
		if (position<0 || position>len)            // if inputted value is out of index 
		{
			printf("ERROR : Invalid Insert Position\n");  // print error message
			continue;
		}
			
		break;
	}
	position--;
	for(i = len-1; i >=position; i--)     // push all value in index to make a space for inputted value
		arr[i + 1] = arr[i];
	arr[position] = input;
	len++;                               // length of array increased

	printf("Elements of array are: %d",arr[0]);  // print all elements in array
	for (j = 1; j < len; j++)
	{
		printf(", %d", arr[j]);
	}
	return 0;

	
	
}