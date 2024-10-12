#include <stdio.h>
#include <stdlib.h>

struct Proc {
int pid;
int bt;
int at;
int ct;
int tat;
int wt;
int rt;
struct Proc* next;
};

struct Queue {
struct Proc* front;
struct Proc* rear;
};

void enq(struct Queue* q, int pid, int at, int bt) {
struct Proc* newProc = (struct Proc*)malloc(sizeof(struct Proc));
newProc->pid = pid;
newProc->bt = bt;
newProc->at = at;
newProc->ct = newProc->tat = newProc->wt = newProc->rt = 0;
newProc->next = NULL;

if (q->rear == NULL) {

q->front = q->rear = newProc;
return;
}

q->rear->next = newProc;
q->rear = newProc;
}

struct Proc* deq(struct Queue* q) {
if (q->front == NULL)
return NULL;

struct Proc* temp = q->front;
q->front = q->front->next;

if (q->front == NULL)
q->rear = NULL;
return temp;
}

void insReadyQ(struct Queue* rq, struct Proc* newProc) {
if (rq->front == NULL || rq->front->bt > newProc->bt) {
newProc->next = rq->front;
rq->front = newProc;
if (rq->rear == NULL) {
rq->rear = newProc;
}
} else {
struct Proc* cur = rq->front;
while (cur->next != NULL && cur->next->bt <= newProc->bt) {
cur = cur->next;

}
newProc->next = cur->next;
cur->next = newProc;
if (cur->next == NULL) {
rq->rear = newProc;
}
}
}

void dispTable(struct Proc processes[], int n) {
printf("\nProcess Table:\n");
printf("-----------------------------------------------------------------------------------\n");
printf("| PID | Arrival | Burst | Completion | Turnaround | Waiting | Response |\n");
printf("-----------------------------------------------------------------------------------\n");

for (int i = 0; i < n; i++) {
printf("| %3d | %7d | %5d | %10d | %10d | %7d | %8d |\n",
processes[i].pid, processes[i].at, processes[i].bt,
processes[i].ct, processes[i].tat, processes[i].wt, processes[i].rt);
}
printf("-----------------------------------------------------------------------------------\n");
}

void dispGantt(int procOrder[], int Torder[], int n) {
printf("\nGantt Chart:\n");
printf("-------------------------------\n");
for (int i = 0; i < n; i++) {
printf(" P%d |", procOrder[i]);
}
printf("\n");

printf("%d", Torder[0]);
for (int i = 1; i <= n; i++) {
printf(" %d", Torder[i]);
}
printf("\n-------------------------------\n");
}

void exec(struct Queue* pq, struct Proc processes[], int n) {
int curTime = 0;
struct Queue rq = {NULL, NULL};

int procOrder[100], Torder[101], count = 0;

float totalTAT = 0, totalWT = 0, totalRT = 0;
int firstResponse[100] = {0};

while (pq->front != NULL || rq.front != NULL) {
while (pq->front != NULL && pq->front->at <= curTime) {
struct Proc* arrived = deq(pq);
insReadyQ(&rq, arrived);
}

struct Proc* execProc = deq(&rq);

if (execProc != NULL) {
if (firstResponse[execProc->pid] == 0) {
execProc->rt = curTime - execProc->at;
firstResponse[execProc->pid] = 1;
}

procOrder[count] = execProc->pid;

Torder[count] = curTime;
count++;

curTime += execProc->bt;

execProc->ct = curTime;
execProc->tat = execProc->ct - execProc->at;
execProc->wt = execProc->tat - execProc->bt;

totalTAT += execProc->tat;
totalWT += execProc->wt;
totalRT += execProc->rt;

for (int i = 0; i < n; i++) {
if (processes[i].pid == execProc->pid) {
processes[i] = *execProc; 
break;
}
}

free(execProc);
} else {
curTime++;
}
}
Torder[count] = curTime;

dispGantt(procOrder, Torder, count);

printf("\nAverage Turnaround Time: %.2f", totalTAT / count);

printf("\nAverage Waiting Time: %.2f", totalWT / count);
printf("\nAverage Response Time: %.2f\n", totalRT / count);
}

int main() {
struct Queue pq = {NULL, NULL};
int n;

printf("Enter number of processes: ");
scanf("%d", &n);

struct Proc processes[n];

int a;
printf("Do you want to enter arrival time (press 1 for yes and 0 for no): ");
scanf("%d", &a);

if (a == 1) {
for (int i = 0; i < n; i++) {
int pid, at, bt;
printf("Enter PID, Arrival Time, and Burst Time for Process %d: ", i + 1);
scanf("%d %d %d", &pid, &at, &bt);
enq(&pq, pid, at, bt);

processes[i].pid = pid;
processes[i].at = at;
processes[i].bt = bt;
processes[i].ct = processes[i].tat = processes[i].wt = processes[i].rt = 0;
}
} else {
for (int i = 0; i < n; i++) {

int pid, bt;
printf("Enter PID and Burst Time for Process %d: ", i + 1);
scanf("%d %d", &pid, &bt);
enq(&pq, pid, 0, bt);

processes[i].pid = pid;
processes[i].at = 0;
processes[i].bt = bt;
processes[i].ct = processes[i].tat = processes[i].wt = processes[i].rt = 0;
}
}
dispTable(processes, n);
exec(&pq, processes, n);
return 0;
}