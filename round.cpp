#include <iostream>
#include <queue>

using namespace std;

struct Process
{
    int id;
    int burstTime;
};

void roundRobinScheduling(queue<Process> &processes, int timeQuantum)
{
    int totalTime = 0;

    while (!processes.empty())
    {
        Process currentProcess = processes.front();
        processes.pop();

        int executionTime = min(timeQuantum, currentProcess.burstTime);
        currentProcess.burstTime -= executionTime;
        totalTime += executionTime;

        cout << "Process " << currentProcess.id << " executed for " << executionTime << " units. ";

        if (currentProcess.burstTime > 0)
        {
            cout << "Remaining burst time: " << currentProcess.burstTime << endl;
            processes.push(currentProcess);
        }
        else
        {
            cout << "Process " << currentProcess.id << " completed." << endl;
        }
    }

    cout << "Total execution time: " << totalTime << endl;
}

int main()
{
    int numProcesses, timeQuantum;

    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    queue<Process> processes;

    for (int i = 1; i <= numProcesses; ++i)
    {
        Process process;
        process.id = i;

        cout << "Enter burst time for Process " << i << ": ";
        cin >> process.burstTime;

        processes.push(process);
    }

    cout << "Enter time quantum: ";
    cin >> timeQuantum;

    cout << "\nRound Robin Scheduling:\n";
    roundRobinScheduling(processes, timeQuantum);

    return 0;
}
