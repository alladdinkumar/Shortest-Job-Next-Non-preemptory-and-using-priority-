#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct process{
	int id;
	int arrival_time;
	int burst_time;
	int waiting_time;
	int turn_around_time;
	float priority;
	bool finished;
		};
struct process *ptr, *ready;
int n,i,total_time,total=0,rp=0;
float s_wait=0.0,s_turn=0.0;
bool all_finished=false;

void input();
void calculate_priority();
void set_to_zero();
void calculate_waiting_time();
void calculate_ready_queue();
void show();
void calculate_turn_around();
void process_execute();
void check_all_finished();

void main()
{
	
	input();
	calculate_priority();
	while(!all_finished)
	{
		calculate_ready_queue();
		process_execute();
		calculate_waiting_time();
		calculate_priority();
		check_all_finished();
	
		
	}
	calculate_turn_around();
	show();
	
}

void input()
{
	printf("Enter the number of process:-\t");
	scanf("%d",&n);
	if(n<=0)
	{
		printf("\nInvalid number of process");
		exit(0);
	}
	ptr=(struct process*)malloc(n*sizeof(struct process));
	ready=(struct process*)malloc(n*sizeof(struct process));
	set_to_zero();
	for(i=0;i<n;i++)
	{
		printf("\np%d:- ",i+1);
		printf("arrival time:-\t");
		scanf("\n%d",&(ptr+i)->arrival_time);
		if((ptr+i)->arrival_time<0)
		{
		printf("\nInvalid arrival of process");
		exit(0);
		}
		printf("burst time:-\t");
		scanf("%d",&(ptr+i)->burst_time);
		if((ptr+i)->burst_time<=0)
		{
		printf("\nInvalid burst time of process");
		exit(0);
		}
	}
}
void check_all_finished()
{
	for(i=0;i<n;i++)
	{
		if((ptr+i)->finished ==false)
		{
			all_finished=false;
			return;
		}
	}
	all_finished=true;
}

void calculate_ready_queue()
{
	int j,i,k;
	rp=0;
	k=0;
	for(j=0;j<n;j++)
	{
		if(((ptr+j)->arrival_time<=total_time)&&(ptr+j)->finished==false)
		{
			*(ready+(k++))=*(ptr+j);
			rp++;
		}
	}
}
void calculate_priority()
{
	int j;
	for(j=0;j<n;j++)
	{
		if((ptr+j)->finished==false)
		{
			
			(ptr+j)->priority = 1+(((float)(ptr+j)->waiting_time)/((float)(ptr+j)->burst_time));
		}
	}
}
void calculate_waiting_time()
{
	int i;
	for(i=0;i<n;i++)
	{
		if(((ptr+i)->arrival_time<total_time)&&(ptr+i)->finished==false)
		{
			(ptr+i)->waiting_time = total_time-((ptr+i)->arrival_time);
		}
	}
}
void set_to_zero()
{
	int i;
	for(i=0;i<n;i++)
	{
		(ptr+i)->id=i+1;
		(ptr+i)->priority=0;
		(ptr+i)->arrival_time=0;
		(ptr+i)->burst_time=0;
		(ptr+i)->waiting_time=0;
		(ptr+i)->turn_around_time=0;
		(ptr+i)->finished= false;
	
	}
}
void show()
{
	int i;
	printf("\n\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurn Around Time\t Finished");
	for(i=0;i<n;i++)
	{	
		printf("\n  p%d\t\t%d\t\t%d\t %0.2f\t\t\t%d\t\t%d\t\t   %s",(ptr+i)->id,(ptr+i)->arrival_time,(ptr+i)->burst_time,(ptr+i)->priority,(ptr+i)->waiting_time,(ptr+i)->turn_around_time,(ptr+i)->finished?"true":"false");
		s_wait+=(ptr+i)->waiting_time;
		s_turn+=(ptr+i)->turn_around_time;
	}
	printf("\n\nAverage waiting time is = %f",(float)s_wait/n);
	printf("\nAverage Turn around time = %f",(float)s_turn/n);
}
void process_execute()
{
	int index,i;
	float max=0.0;
	if(rp==0)
	{
		total_time=total_time+1;
		return;
	}
	for(i=0;i<rp;i++)
	{
		if((ready+i)->priority > max)
		{
			max=(ready+i)->priority;
			index=i;
		}
		
	}
	if(max!=0.0)
	{
		int p_id=(ready+index)->id;
		printf("\np%d Executing",p_id);
		printf("\tFrom time=%d",total_time);
		total_time=total_time+(ready+index)->burst_time;
		((ptr+p_id)-1)->finished=true;
		printf("\tTo time=%d",total_time);
	}	
}
void calculate_turn_around()
{
	int j;
	for(j=0;j<n;j++)
	{
		(ptr+j)->turn_around_time = (ptr+j)->waiting_time+(ptr+j)->burst_time;
		
	}
}
