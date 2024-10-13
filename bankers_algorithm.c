#include <stdio.h>
#include <stdbool.h>

typedef struct
{
    int max[10];
    int allocated[10];
    int need[10];
} processInfo;

int noOfProcess, noOfResource;

void inputProcesses(processInfo process[], int resourceVector[], int available[])
{
    int totalAllocated[10] = {0};
    for (int i = 0; i < noOfProcess; i++)
    {
        printf("\nEnter process[%d] info\n", i);
        printf("Enter the max Need: ");
        for (int j = 0; j < noOfResource; j++)
        {
            scanf("%d", &process[i].max[j]);
        }
        printf("Enter the allocated resource of the process: ");
        for (int j = 0; j < noOfResource; j++)
        {
            scanf("%d", &process[i].allocated[j]);
            process[i].need[j] = process[i].max[j] - process[i].allocated[j]; // Calculate need
            totalAllocated[j] += process[i].allocated[j];
        }
    }

    printf("\nEnter the Resource Vector (total resources in the system): ");
    for (int i = 0; i < noOfResource; i++)
    {
        scanf("%d", &resourceVector[i]);
        available[i] = resourceVector[i] - totalAllocated[i];
    }
}

void displayProcessInfo(processInfo process[])
{
    printf("\nPid\tMax\t\tAllocated\tNeed\n");
    for (int i = 0; i < noOfProcess; i++)
    {
        printf("P[%d]\t", i);
        for (int j = 0; j < noOfResource; j++)
        {
            printf("%d ", process[i].max[j]);
        }
        printf("\t\t");
        for (int j = 0; j < noOfResource; j++)
        {
            printf("%d ", process[i].allocated[j]);
        }
        printf("\t\t");
        for (int j = 0; j < noOfResource; j++)
        {
            printf("%d ", process[i].need[j]);
        }
        printf("\n");
    }
}

bool isSafeState(processInfo process[], int available[], int safeSequence[])
{
    bool finish[noOfProcess];
    int work[10];
    for (int i = 0; i < noOfResource; i++)
        work[i] = available[i];

    for (int i = 0; i < noOfProcess; i++)
        finish[i] = false;

    int count = 0;
    while (count < noOfProcess)
    {
        bool found = false;
        for (int i = 0; i < noOfProcess; i++)
        {
            if (!finish[i])
            {
                bool canAllocate = true;
                for (int j = 0; j < noOfResource; j++)
                {
                    if (process[i].need[j] > work[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate)
                {
                    for (int j = 0; j < noOfResource; j++)
                        work[j] += process[i].allocated[j];

                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                    i = -1;
                }
            }
        }

        if (!found)
        {
            return false; // If no process can be allocated, deadlock is detected
        }
    }
    return true;
}

int main()
{
    printf("Name - Arjun Singh Kandari , Section - A2 , Roll No - 21..\n");
    printf("Enter No of Processes: ");
    scanf("%d", &noOfProcess);
    printf("Enter the No of Resource Instances in System: ");
    scanf("%d", &noOfResource);

    int resourceVector[10];
    int available[10];
    int safeSequence[10];
    processInfo process[10];

    inputProcesses(process, resourceVector, available);

    displayProcessInfo(process);

    if (isSafeState(process, available, safeSequence))
    {
        printf("\nRequest can be fulfilled\nSafe Sequence: ");
        for (int i = 0; i < noOfProcess; i++)
        {
            printf("P[%d] ", safeSequence[i]);
        }
        printf("\n");
    }
    else
    {
        printf("\nRequest cannot be fulfilled\n");
    }

    return 0;
}
