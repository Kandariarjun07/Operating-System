#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct Process
{
    int pid, bt, at, priority, ct, tat, wt, is_completed;
};

void findPriority(struct Process p[], int n)
{
    int completed = 0, currentTime = 0;
    printf("Gantt Chart:");
    while (completed < n)
    {
        int idx = -1, highestPriority = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= currentTime && !p[i].is_completed)
            {
                if (p[i].priority < highestPriority)
                {
                    highestPriority = p[i].priority;
                    idx = i;
                }
            }
        }
        if (idx != -1)
        {
            completed++;
            currentTime += p[idx].bt;
            p[idx].ct = currentTime;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].is_completed = 1;
            printf("P%d ", p[idx].pid);
        }
        else
        {
            currentTime++;
        }
    }
    printf("\n");
}

void printPriority(struct Process p[], int n)
{
    printf("Pid\t\tAT\t\tBT\tPriority\tCT\t\tTAT\t\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].priority, p[i].ct, p[i].tat, p[i].wt);
    }
}

int main()
{
    printf("Name - Arjun Singh Kandari , Section - A2 , Roll No - 21..\n");
    int n;
    printf("Number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("Enter arrival time, burst time, and priority for process %d: ", p[i].pid);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].is_completed = 0;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].at > p[j].at || (p[i].at == p[j].at && p[i].priority > p[j].priority))
            {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    findPriority(p, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].pid > p[j].pid)
            {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    printPriority(p, n);
    float totalTat = 0.0, totalWt = 0.0;
    for (int i = 0; i < n; i++)
    {
        totalTat += p[i].tat;
        totalWt += p[i].wt;
    }
    printf("\nAverage Turnaround Time: %.2f\n", totalTat / n);
    printf("Average Waiting Time: %.2f\n", totalWt / n);
    return 0;
}