#include <stdio.h>

struct Process
{
    int processID;
    int burstTime;
    int priority;
    int waitingTime;
    int turnaroundTime;
};

void sortProcessesByPriority(struct Process processes[], int n)
{
    struct Process temp;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].priority < processes[j + 1].priority)
            {
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void findWaitingTime(struct Process processes[], int n)
{
    int currentTime = 0;

    for (int i = 0; i < n; i++)
    {
        processes[i].waitingTime = currentTime;
        currentTime += processes[i].burstTime;
    }
}

void findTurnaroundTime(struct Process processes[], int n)
{
    for (int i = 0; i < n; i++)
    {
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}

void findAverageTime(struct Process processes[], int n)
{
    double totalWaitingTime = 0, totalTurnaroundTime = 0;

    findWaitingTime(processes, n);
    findTurnaroundTime(processes, n);

    printf("Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].processID,
               processes[i].burstTime,
               processes[i].priority,
               processes[i].waitingTime,
               processes[i].turnaroundTime);

        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

int main()
{
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    printf("Enter burst time and priority for each process:\n");
    for (int i = 0; i < n; i++)
    {
        processes[i].processID = i + 1;
        printf("Process %d:\n", i + 1);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
    }

    sortProcessesByPriority(processes, n);
    findAverageTime(processes, n);

    return 0;
}
