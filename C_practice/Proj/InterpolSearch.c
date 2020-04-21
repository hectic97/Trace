

//#include <stdio.h>
//
//int ISearch(int ar[], int first, int last, int target)
//{
//	int mid;
//
//	if (ar[first]>target || ar[last]<target)
//		return -1;
//
//	mid = ((double)(target - ar[first]) / (ar[last] - ar[first]) * (last - first)) + first;
//
//	if (ar[mid] == target)
//		return mid;
//	else if (ar[mid] < target)
//		return ISearch(ar, mid + 1, last, target);
//	else
//		return ISearch(ar, first, mid - 1, target);
//
//}
#include <stdio.h>
int main(void)
{
	int a = 3;
	int b;
	b = a;
	b++;
	printf("%d %d", a, b);
}