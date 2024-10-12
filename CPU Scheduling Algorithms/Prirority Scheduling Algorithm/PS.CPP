#include <stdio.h>
#include <stdlib.h>

struct process {
int id;
int at, bt, priority;
int ct, tat, wt, rt;
struct process *next;
};

struct queue {
struct process *f;
struct process *r;
};

void createProcess(struct queue **q, int id, int a, int b, int p) {
struct process *newprocess = (struct process*)malloc(sizeof(struct process));
newprocess->id = id;
newprocess->at = a;
newprocess->bt = b;
newprocess->priority = p;
newprocess->ct = newprocess->tat = newprocess->wt = newprocess->rt = 0;
newprocess->next = NULL;

if (*q == NULL) {
*q = (struct queue *)malloc(sizeof(struct queue));
(*q)->f = (*q)->r = newprocess;

} else {
(*q)->r->next = newprocess;
(*q)->r = newprocess;
}
}

struct process *dequeue(struct queue *q) {
if (q->f == NULL)
return NULL;
struct process *temp = q->f;
q->f = q->f->next;
if (q->f == NULL)
q->r = NULL;

return temp;
}

void sortprocess(struct queue *q) {
if (q->f == NULL || q->f->next == NULL)
return;
struct process *sort = NULL;
struct process *curr = q->f;

while (curr != NULL) {
struct process *next = curr->next;
if (sort == NULL || sort->priority > curr->priority) {
curr->next = sort;
sort = curr;
} else {
struct process *temp = sort;
while (temp->next != NULL && temp->next->priority < curr->priority) {

temp = temp->next;
}
curr->next = temp->next;
temp->next = curr;
}
curr = next;
}
q->f = sort;
while (sort->next != NULL) {
sort = sort->next;
}
q->r = sort;
}

void cal_time(struct queue *q) {
int t = 0;
struct process *curr = q->f;

while (curr != NULL) {
if (t < curr->at) {
t = curr->at;
}
curr->rt = t - curr->at;
curr->ct = t + curr->bt;
curr->tat = curr->ct - curr->at;
curr->wt = curr->tat - curr->bt;
t = curr->ct;
curr = curr->next;
}
}

void printTable(struct queue *q) {
printf("\nProcess\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurn Around Time\tWaitingTime\tResponse Time\n");
struct process *curr = q->f;
while (curr != NULL) {
printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", curr->id, curr->at, curr->bt, curr->priority, curr->ct, curr->tat, curr->wt, curr->rt);
curr = curr->next;
}
}

void ganttchart(struct queue *q) {
printf("\n\tGantt Chart\t\n");
printf(" ");
struct process *curr = q->f;
int t = 0;
while (curr != NULL) {
if (t < curr->at) {
for (int j = 0; j < (curr->at - t); j++) {
printf(" ");
}
t = curr->at;
}
for (int j = 0; j < curr->bt; j++) {
printf("--");
}
printf(" ");
t += curr->bt;
curr = curr->next;
}
printf("\n|");
curr = q->f;

t = 0;
while (curr != NULL) {
if (t < curr->at) {
for (int j = 0; j < (curr->at - t); j++) {
printf(" ");
}
t = curr->at;
}
for (int j = 0; j < curr->bt - 1; j++) {
printf(" ");
}
printf("P%d", curr->id);
for (int j = 0; j < curr->bt - 1; j++) {
printf(" ");
}
printf("|");
t += curr->bt;
curr = curr->next;
}
printf("\n ");
curr = q->f;
t = 0;
while (curr != NULL) {
if (t < curr->at) {
for (int j = 0; j < (curr->at - t); j++) {
printf(" ");
}
t = curr->at;
}
for (int j = 0; j < curr->bt; j++) {
printf("--");

}
printf(" ");
t += curr->bt;
curr = curr->next;
}
printf("\n");
curr = q->f;
t = 0;
while (curr != NULL) {
if (t < curr->at) {
for (int j = 0; j < (curr->at - t); j++) {
printf(" ");
}
t = curr->at;
}
printf("%d", t);
for (int j = 0; j < (curr->bt * 2) - 1; j++) {
printf(" ");
}
t += curr->bt;
curr = curr->next;
}
printf("%d\n", t);
}

int main() {
int n;
printf("Enter the number of processes: ");
scanf("%d", &n);
struct queue *q = NULL;
for (int i = 0; i < n; i++) {

printf("Enter arrival time, burst time and priority of process %d: ", i + 1);
int a, b, p;
scanf("%d %d %d", &a, &b, &p);
createProcess(&q, i + 1, a, b, p);
}
sortprocess(q);
cal_time(q);
printTable(q);
ganttchart(q);
return 0;
}