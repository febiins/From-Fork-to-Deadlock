
#include <stdio.h>

// Structure to store process information
struct Process
{
    int pid;    // Process ID
    int at;     // Arrival Time
    int bt;     // Burst Time
    int ct;     // Completion Time
    int tat;    // Turnaround Time
    int wt;     // Waiting Time
};

int main()
{
    struct Process p[10], temp;

    int n, time = 0;

    float avg_wt = 0, avg_tat = 0;

    // Input number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input process details
    for(int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    // Sort processes according to Arrival Time
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(p[j].at > p[j + 1].at)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Calculate Completion Time, Turnaround Time and Waiting Time
    for(int i = 0; i < n; i++)
    {
        // CPU waits if process has not arrived
        if(time < p[i].at)
        {
            time = p[i].at;
        }

        // Execute process using Burst Time
        time = time + p[i].bt;

        // Completion Time (CT)
        p[i].ct = time;

        // Turnaround Time (TAT) = CT - AT
        p[i].tat = p[i].ct - p[i].at;

        // Waiting Time (WT) = TAT - BT
        p[i].wt = p[i].tat - p[i].bt;

        // Calculate total times
        avg_tat = avg_tat + p[i].tat;
        avg_wt = avg_wt + p[i].wt;
    }

    // Display process table
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }

    // Calculate and display average times
    printf("\nAverage Turnaround Time = %.2f", avg_tat / n);
    printf("\nAverage Waiting Time    = %.2f\n", avg_wt / n);

    return 0;
}
