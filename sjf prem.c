#include <stdio.h>
#include <limits.h>

typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Process;

void find_waiting_time(Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    int shortest_index;
    int min_remaining_time;
    int is_any_process_running = 0;

    while (completed != n) {
        min_remaining_time = INT_MAX;
        shortest_index = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0 &&
                processes[i].remaining_time < min_remaining_time) {
                min_remaining_time = processes[i].remaining_time;
                shortest_index = i;
                is_any_process_running = 1;
            }
        }

        if (shortest_index == -1) {
            current_time++;
            continue;
        }

        processes[shortest_index].remaining_time--;
        current_time++;

        if (processes[shortest_index].remaining_time == 0) {
            processes[shortest_index].completion_time = current_time;
            processes[shortest_index].turnaround_time = processes[shortest_index].completion_time - processes[shortest_index].arrival_time;
            processes[shortest_index].waiting_time = processes[shortest_index].turnaround_time - processes[shortest_index].burst_time;
            completed++;
            is_any_process_running = 0;
        }
    }
}

void find_average_times(Process processes[], int n) {
    find_waiting_time(processes, n);

    float total_waiting_time = 0;
    float total_turnaround_time = 0;

    printf("Process\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n",
               processes[i].id, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("Average waiting time: %.2f\n", total_waiting_time / n);
    printf("Average turnaround time: %.2f\n", total_turnaround_time / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    find_average_times(processes, n);

    return 0;
}
