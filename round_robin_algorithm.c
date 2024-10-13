#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef struct process
{
    int pid, at, bt, ct, tat, wt, rt, st, remaining, visited;
} Process;

int comp(const void *a, const void *b)
{
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;
    return p1->at - p2->at;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void averageTime(Process *arr, int n, float total_it)
{
    float total_wt = 0, total_tat = 0, total_rt = 0;
    printf("\nPid\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        total_wt += arr[i].wt;
        total_tat += arr[i].tat;
        total_rt += arr[i].rt;
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", arr[i].pid, arr[i].at, arr[i].bt, arr[i].ct, arr[i].tat, arr[i].wt, arr[i].rt);
    }
    printf("\nAverage Waiting time: %f\n", total_wt / (float)n);
    printf("Average Turn Around time: %f\n", total_tat / (float)n);
    printf("Average Response time: %f\n", total_rt / (float)n);
    printf("CPU utilization: %f%%\n", ((arr[n - 1].ct - total_it) / (float)arr[n - 1].ct) * 100);
    printf("Throughput: %f\n", (float)n / (arr[n - 1].ct - arr[0].at));
}

void roundRobin(Process *arr, int n, int qn)
{
    int queue[100];
    int front = 0, rear = 0, completed = 0, curr_time = 0;
    float total_it = 0;
    qsort(arr, n, sizeof(Process), comp);
    queue[rear] = 0;
    arr[0].visited = 1;
    printf("\nGantt Chart : ");
    while (completed != n)
    {
        int index = queue[front];
        front++;
        if (arr[index].bt == arr[index].remaining)
        {
            arr[index].st = max(curr_time, arr[index].at);
            total_it += (arr[index].st - curr_time);
            curr_time = arr[index].st;
        }
        if (arr[index].remaining > qn)
        {
            arr[index].remaining -= qn;
            curr_time += qn;
        }
        else
        {
            curr_time += arr[index].remaining;
            arr[index].remaining = 0;
            completed++;
            arr[index].ct = curr_time;
            arr[index].tat = arr[index].ct - arr[index].at;
            arr[index].wt = arr[index].tat - arr[index].bt;
            arr[index].rt = arr[index].st - arr[index].at;
        }
        printf("P%d ", arr[index].pid);
        for (int i = 1; i < n; i++)
        {
            if (arr[i].at <= curr_time && arr[i].visited == 0)
            {
                queue[++rear] = i;
                arr[i].visited = 1;
            }
        }
        if (arr[index].remaining > 0)
        {
            queue[++rear] = index;
        }
    }
    printf("\n");
    averageTime(arr, n, total_it);
}

int main()
{
    printf("Name - Arjun Singh Kandari , Section - A2 , Roll No - 21..\n");
    int n, qn;
    printf("Enter the Number of processes: ");
    scanf("%d", &n);
    Process arr[n];
    printf("Enter the Quantum Number: ");
    scanf("%d", &qn);
    for (int i = 0; i < n; i++)
    {
        printf("Enter the Arrival Time and Burst Time of Process %d: ", i + 1);
        scanf("%d %d", &arr[i].at, &arr[i].bt);
        arr[i].pid = i + 1;
        arr[i].remaining = arr[i].bt;
        arr[i].visited = 0;
    }
    roundRobin(arr, n, qn);
    return 0;
}
