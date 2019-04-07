#include<stdio.h>
struct Time
{
       int p,arrival_time,burst_time,wait_time,turnaround_time,remain_time;
};
void sort_arrival_time(struct Time a[],int n)
{
       int x,y;
       struct Time temp;
       for(x=0;x<n;x++)
       {
              for(y=x+1;y<n;y++)
              {
                     if(a[x].arrival_time > a[y].arrival_time)
                     {
                           temp = a[x];
                           a[x] = a[y];
                           a[y] = temp;
                     }
              }
       }
       return;
}

int main()
{      float avg_waiting_time=0,avg_turnaround_time=0;
       int x,y,n,time,remain,flag=0,ts;
       struct Time a[104];

    printf("Scheduling Algorithm where CPU remain idle for first 3 secs and each process gets a total time of 10s for execution.\n");

    printf("Enter Total No. Of Process : ");
    scanf("%d",&n);
       remain=n;
       for(x=0;x<n;x++)
       {
              printf("Enter Arrival time & Burst Time for Process P%d : ",x);
              scanf("%d%d",&a[x].arrival_time,&a[x].burst_time);
              a[x].p = x;
              a[x].remain_time = a[x].burst_time;
       }
       sort_arrival_time(a,n);
       printf("Quantum Number : ");
       scanf("%d",&ts);
       printf("\n==========================================\n");
       printf("Gantt Chart\n");
       printf("0 <CPU Idle> 3");
       for(time=ts-1,x=0;remain!=0;)
       {
              if(a[x].remain_time<=ts && a[x].remain_time>0)
              {
                     time = time + a[x].remain_time;
                     printf(" -> [P%d] <- %d",a[x].p,time);
                     a[x].remain_time=0;
                     flag=1;
              }
              else if(a[x].remain_time > 0)
              {
                     a[x].remain_time = a[x].remain_time - ts;
                     time = time + ts;
                     printf(" -> [P%d] <- %d",a[x].p,time);
              }
              if(a[x].remain_time==0 && flag==1)
              {
                     remain--;
                     a[x].turnaround_time = time-a[x].arrival_time;
                     a[x].wait_time = time-a[x].arrival_time-a[x].burst_time;
                     avg_waiting_time = avg_waiting_time + time-a[x].arrival_time-a[x].burst_time;
                     avg_turnaround_time = avg_turnaround_time + time-a[x].arrival_time;
                     flag=0;
              }
              if(x==n-1)
                     x=0;
              else if(a[x+1].arrival_time <= time)
                     x++;
              else
                     x=0;
       }
       printf("\n\n");
       printf("=========================================\n");
       printf("Process\tArTi\tBuTi\tTaTi\tWtTi\n");
       printf("==========================================\n");
       for(x=0;x<n;x++)
       {
              printf("P%d\t%d\t%d\t%d\t%d\n",a[x].p,a[x].arrival_time,a[x].burst_time,a[x].turnaround_time,a[x].wait_time);
       }
       printf("==========================================\n");
       avg_waiting_time = avg_waiting_time/n;
       avg_turnaround_time = avg_turnaround_time/n;
       printf("Average Waiting Time : %.2f\n",avg_waiting_time);
       printf("Average Turnaround Time : %.2f\n",avg_turnaround_time);
       return 0;
}
