#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int pid, arrival_time, burst_time, completion_time, turnaround_time, waiting_time;
} Process;

int compareByArrivalTime(const void *a, const void *b)
{
    Process *procA = (Process *)a;
    Process *procB = (Process *)b;
    return procA->arrival_time - procB->arrival_time;
}

int compareByPID(const void *a, const void *b)
{
    Process *procA = (Process *)a;
    Process *procB = (Process *)b;
    return procA->pid - procB->pid;
}

void findCompletionTime(Process proc[], int n)
{
    int current_time = 0;
    float total_wt = 0, total_tat = 0;
    printf("\nGantt Chart : ");
    for (int i = 0; i < n; i++)
    {
        if (current_time < proc[i].arrival_time)
        {
            current_time = proc[i].arrival_time;
        }
        proc[i].completion_time = current_time + proc[i].burst_time;
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
        proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
        if (proc[i].waiting_time < 0)
        {
            proc[i].waiting_time = 0;
        }
        printf("P%d ", proc[i].pid);
        current_time = proc[i].completion_time;
    }
    printf("\n");
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

void findFCFS(Process proc[], int n)
{
    qsort(proc, n, sizeof(Process), compareByArrivalTime);
    findCompletionTime(proc, n);
    qsort(proc, n, sizeof(Process), compareByPID);
}

void printFCFS(Process proc[], int n)
{
    printf("\nPID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].pid, proc[i].arrival_time, proc[i].burst_time,
               proc[i].completion_time, proc[i].turnaround_time,
               proc[i].waiting_time);
    }
}

int main()
{
    printf("Name - Arjun Singh Kandari , Section - A2 , Roll No - 21..\n");
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process proc[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        proc[i].pid = i + 1;
        scanf("%d %d", &proc[i].arrival_time, &proc[i].burst_time);
    }
    findFCFS(proc, n);
    printFCFS(proc, n);
    return 0;
}