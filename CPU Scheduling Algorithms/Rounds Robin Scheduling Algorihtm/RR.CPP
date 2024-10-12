#include<stdio.h>
#include<stdlib.h>

struct process{
int id;
int at, bt, ct;
int tat, wt, rt;
int bt_rem; // remaining burst time
struct process *next;
};

struct queue{
struct process *f;
struct process *r;
};

void createProcess(struct queue **q, int id, int a, int b){
struct process *newprocess = (struct process*)malloc(sizeof(struct process));
newprocess->id = id;
newprocess->at = a;
newprocess->bt = b;
newprocess->bt_rem = b; // initialize remaining burst time
newprocess->tat = 0;
newprocess->wt = 0;
newprocess->rt = 0;
newprocess->next = NULL;

if(*q == NULL){

*q = (struct queue *)malloc(sizeof(struct queue));
(*q)->f = (*q)->r = newprocess;
}
else{
(*q)->r->next = newprocess;
(*q)->r = newprocess;
}
}

struct process *dequeue(struct queue *q){
if(q->f == NULL)
return NULL;
struct process *temp = q->f;
q->f = q->f->next;
if(q->f == NULL)
q->r = NULL;

return temp;
}

void sortprocess(struct queue *q){
if(q->f == NULL || q->f->next == NULL)
return;
struct process *sort = NULL;
struct process *curr = q->f;

while(curr != NULL)
{
struct process *next = curr->next;
if(sort == NULL || sort->at > curr->at){
curr->next = sort;

sort = curr;
}
else{
struct process *temp = sort;
while(temp->next != NULL && temp->next->at < curr->at){
temp = temp->next;
}
curr->next = temp->next;
temp->next = curr;
}
curr = next;
}
q->f = sort;
while(sort->next != NULL)
{
sort = sort->next;
}
q->r = sort;
}

void cal_time(struct queue *q, int quantum){
int t = 0;
struct process *curr = q->f;
while(1){
int flag = 1;
curr = q->f;
while(curr != NULL){
if(curr->bt_rem > 0){
flag = 0;
if(t < curr->at){
t = curr->at;

}
int bt_exec = (curr->bt_rem > quantum) ? quantum : curr->bt_rem;
t += bt_exec;
curr->bt_rem -= bt_exec;
if(curr->bt_rem == 0){
curr->ct = t;
curr->tat = curr->ct - curr->at;
curr->wt = curr->tat - curr->bt;
curr->rt = curr->wt;
}
}
curr = curr->next;
}
if(flag){
break;
}
}
}

void printTable(struct queue *q){
printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\tResponseTime\n");
struct process *curr = q->f;
while(curr != NULL){
printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", curr->id, curr->at, curr->bt, curr->ct, curr->tat, curr->wt,
curr->rt);
curr = curr->next;
}
}
void ganttchart(struct queue *q){
printf("\n\tGantt Chart\t\n");
int t = 0;

struct process *curr = q->f;
while(curr != NULL){
if(t < curr->at){
for(int j=0; j<(curr->at-t); j++){
printf(" ");
}
t = curr->at;
}
for(int j=0; j<curr->bt; j++){
printf("--");
}
printf(" ");
t += curr->bt;
curr = curr->next;
}
printf("\n|");
curr = q->f;
t = 0;
while(curr != NULL){
if(t < curr->at){
for(int j=0; j<(curr->at-t); j++){
printf(" ");
}
t = curr->at;
}
for(int j=0; j<curr->bt-1; j++){
printf(" ");
}
printf("P%d", curr->id);
for(int j=0; j<curr->bt-1; j++){
printf(" ");

}
printf("|");
t += curr->bt;
curr = curr->next;
}
printf("\n ");
curr = q->f;
t = 0;
while(curr != NULL){
if(t < curr->at){
for(int j=0; j<(curr->at-t); j++){
printf(" ");
}
t = curr->at;
}
for(int j=0; j<curr->bt; j++){
printf("--");
}
printf(" ");
t += curr->bt;
curr = curr->next;
}
printf("\n");
curr = q->f;
t = 0;
while(curr != NULL){
if(t < curr->at){
for(int j=0; j<(curr->at-t); j++){
printf(" ");
}
t = curr->at;

}
printf("%d", t);
for(int j=0; j<(curr->bt*2)-1; j++){
printf(" ");
}
t += curr->bt;
curr = curr->next;
}
printf("%d\n", t);
}

int main(){
int n;
printf("Enter the number of processes: ");
scanf("%d", &n);

struct queue *q = NULL;

char at_choice;
printf("Do you want to input arrival times? (y/n): ");
scanf(" %c", &at_choice);

for(int i=0; i<n; i++){
int a, b;
if(at_choice == 'y' || at_choice == 'Y'){
printf("Enter arrival time and burst time for process P%d: ", i+1);
scanf("%d %d", &a, &b);
}
else{
a = 0;
printf("Enter burst time for process P%d: ", i+1);

scanf("%d", &b);
}
createProcess(&q, i+1, a, b);
}

sortprocess(q);

int quantum;
printf("Enter the time quantum: ");
scanf("%d", &quantum);

cal_time(q, quantum);

printTable(q);

ganttchart(q);

return 0;

}