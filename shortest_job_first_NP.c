#include <stdio.h>
#include <limits.h>
struct Process
{
    int pid, arrivalTime, burstTime, completionTime, turnaroundTime, waitingTime;
};
void findSJF(struct Process proc[], int n)
{
    int completed = 0, currentTime = 0;
    float total_wt = 0, total_tat = 0;
    int isCompleted[n];
    printf("\nGantt Chart : ");
    for (int i = 0; i < n; i++)
    {
        isCompleted[i] = 0;
    }
    while (completed < n)
    {
        int shortest = -1;
        int minBurst = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (proc[i].arrivalTime <= currentTime && !isCompleted[i] && proc[i].burstTime < minBurst)
            {
                minBurst = proc[i].burstTime;
                shortest = i;
            }
        }
        if (shortest == -1)
        {
            currentTime++;
            continue;
        }
        printf("P%d ", shortest);
        currentTime += proc[shortest].burstTime;
        proc[shortest].completionTime = currentTime;
        proc[shortest].turnaroundTime = proc[shortest].completionTime - proc[shortest].arrivalTime;
        proc[shortest].waitingTime = proc[shortest].turnaroundTime - proc[shortest].burstTime;
        total_wt += proc[shortest].waitingTime;
        total_tat += proc[shortest].turnaroundTime;
        if (proc[shortest].waitingTime < 0)
        {
            proc[shortest].waitingTime = 0;
        }
        isCompleted[shortest] = 1;
        completed++;
    }
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}
void displayProcessDetails(struct Process proc[], int n)
{
    printf("Process\tArrivalTime\tBurstTime\tCompletionTime\tTurnaroundTime\tWaitingTime\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].pid,
               proc[i].arrivalTime,
               proc[i].burstTime,
               proc[i].completionTime,
               proc[i].turnaroundTime,
               proc[i].waitingTime);
    }
    printf("\n");
}
int main()
{
    printf("Name - Arjun Singh Kandari , Section - A2 , Roll No - 21..\n");
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process proc[n];
    printf("Enter Process Arrival Times and Burst Times\n");
    for (int i = 0; i < n; i++)
    {
        proc[i].pid = i + 1;
        printf("Process %d - Arrival Time and Burst Time: ", i + 1);
        scanf("%d %d", &proc[i].arrivalTime, &proc[i].burstTime);
    }
    findSJF(proc, n);
    displayProcessDetails(proc, n);
    return 0;
}
