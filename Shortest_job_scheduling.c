#include<stdio.h>

struct process{
	int burst_time;
	int waiting_time;
	int turn_around_time;
		};
void main()
{
	int n,i;
	printf("Enter the number of process");
	scanf("%d",&n);
	struct process *ptr;
	ptr=(struct process*)malloc(n*sizeof(struct process));
	for(i=0;i<n;i++)
	{
		printf("\np%d:- ",i+1);
		scanf("\n%d",&(ptr+i)->burst_time);
	}
	for(i=0;i<n;i++)
	{
		printf("\np%d",i+1);
		printf("\n%d",(ptr+i)->burst_time);
	}	
}
