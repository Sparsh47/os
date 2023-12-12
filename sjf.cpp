#include <stdio.h>

struct Process
{
    int processID;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int remainingBurstTime;
};

void sortProcessesByArrivalTime(struct Process processes[], int n)
{
    struct Process temp;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime)
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
        processes[i].waitingTime = currentTime - processes[i].arrivalTime;

        if (processes[i].waitingTime < 0)
        {
            processes[i].waitingTime = 0;
            currentTime = processes[i].arrivalTime;
        }

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

    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].processID,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].waitingTime,
               processes[i].turnaroundTime);

        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

void shortestJobFirst(struct Process processes[], int n)
{
    int currentTime = 0;

    for (int i = 0; i < n; i++)
    {
        int shortestJobIndex = i;

        for (int j = i + 1; j < n; j++)
        {
            if (processes[j].burstTime < processes[shortestJobIndex].burstTime &&
                processes[j].arrivalTime <= currentTime)
            {
                shortestJobIndex = j;
            }
        }

        struct Process temp = processes[i];
        processes[i] = processes[shortestJobIndex];
        processes[shortestJobIndex] = temp;

        currentTime += processes[i].burstTime;
    }
}

int main()
{
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++)
    {
        processes[i].processID = i + 1;
        printf("Process %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);
        processes[i].remainingBurstTime = processes[i].burstTime;
    }

    sortProcessesByArrivalTime(processes, n);
    shortestJobFirst(processes, n);
    findAverageTime(processes, n);

    return 0;
}
