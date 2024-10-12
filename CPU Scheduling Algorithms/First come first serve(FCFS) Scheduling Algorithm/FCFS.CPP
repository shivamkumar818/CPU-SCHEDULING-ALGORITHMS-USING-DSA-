#include<stdio.h>
#include<stdlib.h>

struct process{
int id;
int at,bt,ct;
int tat,wt,rt;
struct process *next;
};

struct queue{
struct process *f;
struct process *r;
};

void createProcess(struct queue **q,int id,int a,int b){
struct process *newprocess = (struct process*)malloc(sizeof(struct process));
newprocess->id=id;
newprocess->at=a;
newprocess->bt=b;
newprocess->tat=0;
newprocess->wt=0;
newprocess->rt=0;
newprocess->next=NULL;

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
else
{
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

void cal_time (struct queue *q){
int t = 0;
struct process *curr = q->f;
while(curr != NULL){
if(t < curr->at){
t = curr->at;
}
curr->rt = t-curr->at;
curr->ct = t + curr->bt;

curr->tat = curr->ct - curr->at;
curr->wt = curr->tat - curr->bt;
t = curr->ct;
curr = curr->next;
}
}

void printTable(struct queue *q){
printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaitingTime\tResponse Time\n");
struct process *curr = q->f;
while(curr != NULL){
printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",curr->id,curr->at,curr->bt,curr->ct,curr->tat,curr->wt,curr->rt);
curr = curr->next;
}
}

void ganttchart(struct queue *q){
printf("\n\tGantt Chart\t\n");
printf(" ");
struct process *curr = q->f;
while(curr != NULL){
for(int j=0;j<curr->bt;j++){
printf("--");
}
printf(" ");
curr = curr->next;
}
printf("\n|");
curr = q->f;
while(curr != NULL){

for(int j=0;j<curr->bt-1;j++){
printf(" ");
}
printf("P%d",curr->id);
for(int j=0;j<curr->bt-1;j++){
printf(" ");
}
printf("|");
curr = curr->next;
}
printf("\n ");
curr = q->f;
while(curr != NULL){
for(int j=0;j<curr->bt;j++){
printf("--");
}
printf(" ");
curr = curr->next;
}
printf("\n");
int t=0;
curr=q->f;
while(curr != NULL){
if(t < curr->at){
t = curr->at;
}
printf("%d",t);
for(int j=0;j<curr->bt*2;j++){
printf(" ");
}
t += curr->bt;

curr = curr->next;
}
printf("%d\n",t);
}

void calAvg(struct queue *q){
double avgTAT,avgWT,avgRT,count=0;
struct process *temp = q->f;
while(temp != NULL){
avgTAT += temp->at;
avgWT += temp->wt;
avgRT += temp->rt;
count++;
temp=temp->next;
}
avgTAT /= count;
avgWT /= count;
avgRT /= count;
printf("\nAverage Turn Around Time: %.2f",avgTAT);
printf("\nAverage Waiting Time: %.2f",avgWT);
printf("\nAverage Response Time: %.2f\n",avgRT);
}
int main()
{
int n;
printf("Enter Number of process: ");
scanf("%d",&n);
struct queue *q = NULL;
int m;
printf("Press 1 if you want to enter Arrival time and Press 0 if you do not want to.");
scanf("%d",&m);

for(int i=1;i<=n;i++){
int a=0,b;
if(m){
printf("Enter arrival time for P%d: ",i);
scanf("%d",&a);
}
printf("Enter Burst time for P%d: ",i);
scanf("%d",&b);
createProcess(&q,i,a,b);
}
if(m){
sortprocess(q);
}
cal_time(q);
printTable(q);
ganttchart(q);
calAvg(q);
}