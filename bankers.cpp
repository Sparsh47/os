#include <iostream>
#include <vector>

using namespace std;

const int MAX_PROCESSES = 5;
const int MAX_RESOURCES = 3;

vector<int> available(MAX_RESOURCES);
vector<vector<int>> maximum(MAX_PROCESSES, vector<int>(MAX_RESOURCES));
vector<vector<int>> allocation(MAX_PROCESSES, vector<int>(MAX_RESOURCES));
vector<vector<int>> need(MAX_PROCESSES, vector<int>(MAX_RESOURCES));

bool isSafe(int process, vector<int> &work, vector<bool> &finish)
{
    // Check if the process's needs can be satisfied with the current available resources
    for (int i = 0; i < MAX_RESOURCES; ++i)
    {
        if (need[process][i] > work[i])
        {
            return false;
        }
    }

    // Simulate allocating resources to the process
    for (int i = 0; i < MAX_RESOURCES; ++i)
    {
        work[i] += allocation[process][i];
    }

    finish[process] = true;

    // Recursively check for the remaining processes
    for (int i = 0; i < MAX_PROCESSES; ++i)
    {
        if (!finish[i] && isSafe(i, work, finish))
        {
            return true;
        }
    }

    // If no safe sequence is found
    finish[process] = false;
    return false;
}

bool requestResources(int process, vector<int> &request)
{
    // Check if the requested resources are less than or equal to the remaining needs
    for (int i = 0; i < MAX_RESOURCES; ++i)
    {
        if (request[i] > need[process][i])
        {
            return false;
        }
    }

    // Check if the requested resources are less than or equal to the available resources
    for (int i = 0; i < MAX_RESOURCES; ++i)
    {
        if (request[i] > available[i])
        {
            return false;
        }
    }

    // Simulate the allocation of resources
    for (int i = 0; i < MAX_RESOURCES; ++i)
    {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    // Check if the system is in a safe state after the resource allocation
    vector<bool> finish(MAX_PROCESSES, false);
    vector<int> work = available;

    if (isSafe(process, work, finish))
    {
        return true;
    }
    else
    {
        // If the system is not in a safe state, roll back the resource allocation
        for (int i = 0; i < MAX_RESOURCES; ++i)
        {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
        return false;
    }
}

int main()
{
    // Initialize available resources
    cout << "Enter the available resources: ";
    for (int i = 0; i < MAX_RESOURCES; ++i)
    {
        cin >> available[i];
    }

    // Initialize maximum resources
    cout << "Enter the maximum resources for each process:\n";
    for (int i = 0; i < MAX_PROCESSES; ++i)
    {
        cout << "Process " << i << ": ";
        for (int j = 0; j < MAX_RESOURCES; ++j)
        {
            cin >> maximum[i][j];
            need[i][j] = maximum[i][j];
        }
    }

    // Initialize allocation matrix
    cout << "Enter the allocation of resources for each process:\n";
    for (int i = 0; i < MAX_PROCESSES; ++i)
    {
        cout << "Process " << i << ": ";
        for (int j = 0; j < MAX_RESOURCES; ++j)
        {
            cin >> allocation[i][j];
            need[i][j] -= allocation[i][j];
        }
    }

    // Process resource requests
    while (true)
    {
        int process;
        cout << "Enter the process making a request (-1 to exit): ";
        cin >> process;

        if (process == -1)
        {
            break;
        }

        vector<int> request(MAX_RESOURCES);
        cout << "Enter the requested resources for process " << process << ": ";
        for (int i = 0; i < MAX_RESOURCES; ++i)
        {
            cin >> request[i];
        }

        if (requestResources(process, request))
        {
            cout << "Request granted. System in safe state.\n";
        }
        else
        {
            cout << "Request denied. System in unsafe state.\n";
        }

        // Display current state
        cout << "Current state:\n";
        cout << "Available resources: ";
        for (int i = 0; i < MAX_RESOURCES; ++i)
        {
            cout << available[i] << " ";
        }
        cout << endl;

        cout << "Maximum resources:\n";
        for (int i = 0; i < MAX_PROCESSES; ++i)
        {
            cout << "Process " << i << ": ";
            for (int j = 0; j < MAX_RESOURCES; ++j)
            {
                cout << maximum[i][j] << " ";
            }
            cout << endl;
        }

        cout << "Allocation matrix:\n";
        for (int i = 0; i < MAX_PROCESSES; ++i)
        {
            cout << "Process " << i << ": ";
            for (int j = 0; j < MAX_RESOURCES; ++j)
            {
                cout << allocation[i][j] << " ";
            }
            cout << endl;
        }

        cout << "Need matrix:\n";
        for (int i = 0; i < MAX_PROCESSES; ++i)
        {
            cout << "Process " << i << ": ";
            for (int j = 0; j < MAX_RESOURCES; ++j)
            {
                cout << need[i][j] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
