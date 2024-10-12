1. First-Come, First-Served (FCFS) Scheduling Algorithm


The FCFS scheduling algorithm executes processes in the order they arrive in the ready queue. It is a non-preemptive approach, meaning that once a process starts executing, it runs to completion without interruption. This can lead to the convoy effect, where longer processes delay the execution of shorter ones.



Features:

Simple and straightforward.
Non-preemptive.
Processes are executed based on arrival time.
May cause high waiting times for shorter processes behind long ones.





2. Priority Scheduling Algorithm

   
In the Priority Scheduling algorithm, each process is assigned a priority, and the CPU is allocated to the process with the highest priority. Lower-priority processes may have to wait if higher-priority processes are in the queue. This can be either preemptive or non-preemptive.

Features:

Can be implemented in preemptive or non-preemptive form.
Processes are executed based on priority levels.
Can lead to starvation of lower-priority processes, which can be mitigated using aging (increasing the priority of waiting processes over time).




3. Round Robin (RR) Scheduling Algorithm


Round Robin is a preemptive scheduling algorithm that assigns a fixed time quantum to each process. The CPU cycles through the ready queue, allowing each process to execute for a time slice. If a process is not completed within its time quantum, it moves to the end of the queue, and the next process is scheduled.

Features:

Preemptive.
Ensures fair CPU time allocation.
Suitable for time-sharing systems.
Time quantum size is crucial for balancing response time and throughput.





4. Shortest Job First (SJF) Scheduling Algorithm


The SJF algorithm schedules processes based on their burst time, executing the process with the shortest burst time first. It can be non-preemptive, where a process runs to completion once started, or preemptive, where the current process can be interrupted by a newly arrived process with a shorter burst time.

Features:

Can be preemptive or non-preemptive.
Minimizes average waiting time.
Susceptible to starvation of longer processes if shorter ones keep arriving.
Efficient for batch processing.





5. Shortest Remaining Time First (SRTF) Scheduling Algorithm


SRTF is the preemptive version of the SJF algorithm. It always selects the process with the shortest remaining burst time to execute next. If a new process arrives with a shorter burst time than the currently running process, the CPU switches to the new process.

Features:

Preemptive.
Ensures minimal average turnaround and waiting times.
Can result in starvation for processes with longer burst times.
More complex than non-preemptive SJF due to frequent context switching.
