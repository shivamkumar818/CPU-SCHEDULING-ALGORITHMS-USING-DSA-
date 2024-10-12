#include <stdio.h>
#include <limits.h>
#include <stdlib.h> // Added for malloc

struct Process {
int pid;
int burst_time;
int arrival_time;
int remaining_time;
int waiting_time;
int turnaround_time;
};

struct Queue {
int front, rear;
int size;
int capacity;
int array[100];
};

struct Queue* createQueue(int capacity) {
struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
queue->capacity = capacity;
queue->front = queue->size = 0;
queue->rear = capacity - 1;
return queue;
}

int isFull(struct Queue* queue) {
return (queue->size == queue->capacity);
}

int isEmpty(struct Queue* queue) {
return (queue->size == 0);
}

void enqueue(struct Queue* queue, int item) {
if (isFull(queue))
return;
queue->rear = (queue->rear + 1) % queue->capacity;
queue->array[queue->rear] = item;
queue->size = queue->size + 1;
}

int dequeue(struct Queue* queue) {
if (isEmpty(queue))
return -1;
int item = queue->array[queue->front];
queue->front = (queue->front + 1) % queue->capacity;
queue->size = queue->size - 1;
return item;
}

int findShortestProcess(struct Queue* queue, struct Process p[], int time) {
int shortest = -1;
int min_remaining_time = INT_MAX;

for (int i = 0; i < queue->size; i++) {
int process_index = queue->array[(queue->front + i) % queue->capacity];

if (p[process_index].remaining_time < min_remaining_time && p[process_index].arrival_time
<= time && p[process_index].remaining_time > 0) {
min_remaining_time = p[process_index].remaining_time;
shortest = process_index;
}
}
return shortest;
}

void ganttChart(int process[], int total_time) {
printf("\nGantt Chart:\n");
printf(" ");
for (int i = 0; i < total_time; i++)
printf("--");
printf("\n|");

for (int i = 0; i < total_time; i++) {
if (process[i] != -1)
printf("P%d|", process[i] + 1);
else
printf("ID|");
}
printf("\n ");
for (int i = 0; i < total_time; i++)
printf("--");
printf("\n ");

for (int i = 0; i <= total_time; i++)
printf("%d ", i);
printf("\n");
}

int main() {
int n;

printf("Enter the number of processes: ");
scanf("%d", &n);

struct Process p[n];

for (int i = 0; i < n; i++) {
p[i].pid = i + 1;
printf("Enter arrival time and burst time for Process P%d: ", i + 1);
scanf("%d%d", &p[i].arrival_time, &p[i].burst_time);
p[i].remaining_time = p[i].burst_time;
}

struct Queue* queue = createQueue(n);
int completed_processes = 0;
int current_time = 0;
int total_waiting_time = 0;
int total_turnaround_time = 0;
int gantt[100];
int index = 0;

for (int i = 0; i < 100; i++) {
gantt[i] = -1;
}

while (completed_processes < n) {
for (int i = 0; i < n; i++) {
if (p[i].arrival_time == current_time) {

enqueue(queue, i);
}
}

int shortest = findShortestProcess(queue, p, current_time);

if (shortest == -1) {
gantt[index++] = -1;
current_time++;
continue;
}

gantt[index++] = shortest;
p[shortest].remaining_time--;
current_time++;

if (p[shortest].remaining_time == 0) {
completed_processes++;
p[shortest].turnaround_time = current_time - p[shortest].arrival_time;
p[shortest].waiting_time = p[shortest].turnaround_time - p[shortest].burst_time;
total_waiting_time += p[shortest].waiting_time;
total_turnaround_time += p[shortest].turnaround_time;
}
}

printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
for (int i = 0; i < n; i++) {
printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time,
p[i].waiting_time, p[i].turnaround_time);
}

ganttChart(gantt, current_time);

printf("\nAverage Waiting Time: %.2f", (float)total_waiting_time / n);
printf("\nAverage Turnaround Time: %.2f\n", (float)total_turnaround_time / n);

return 0;
}