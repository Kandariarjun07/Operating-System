#include <stdio.h>
#include <limits.h>
struct Process
{
    int pid, arrivalTime, burstTime, completionTime, turnaroundTime, waitingTime;
};
void findSJF(struct Process proc[], int n)
{
    int remainingTime[n];
    for (int i = 0; i < n; i++)
    {
        remainingTime[i] = proc[i].burstTime;
    }
    int currentTime = 0;
    int complete = 0;
    float total_wt = 0, total_tat = 0;
    printf("\nGantt Chart : ");
    while (complete < n)
    {
        int shortest = -1;
        int minBurst = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (proc[i].arrivalTime <= currentTime && remainingTime[i] < minBurst && remainingTime[i] > 0)
            {
                minBurst = remainingTime[i];
                shortest = i;
            }
        }
        remainingTime[shortest]--;
        currentTime++;
        if (remainingTime[shortest] == 0)
        {
            complete++;
            proc[shortest].completionTime = currentTime;
            proc[shortest].turnaroundTime = proc[shortest].completionTime - proc[shortest].arrivalTime;
            proc[shortest].waitingTime = proc[shortest].turnaroundTime - proc[shortest].burstTime;
            total_wt += proc[shortest].waitingTime;
            total_tat += proc[shortest].turnaroundTime;
            if (proc[shortest].waitingTime < 0)
            {
                proc[shortest].waitingTime = 0;
            }
        }
        printf("P%d ", shortest);
    }
    printf("\n");
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
        proc[i].pid = i + 1; // Assigning process ID based on input order
        printf("Process %d - Arrival Time and Burst Time: ", i + 1);
        scanf("%d %d", &proc[i].arrivalTime, &proc[i].burstTime);
    }
    findSJF(proc, n);
    displayProcessDetails(proc, n);
    return 0;
}