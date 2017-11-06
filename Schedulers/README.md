
Operating Systems: Scheduling algorithms

steps to compile and run:

1. upgrade gcc version to 6.2.0:  (On linux: module load gcc-6.2.0)
2. Run makefile: 	  make
3. Run executable:  ./scheduler <program arguments>

Program arguments: InputFile RandomNumberFile [-v](optional parameter) [-s<schedspec>]
Program arguments can be given in any order

InputFile format for every process:
Arrival Time (AT), Total CPU Time (TC), CPU Burst (CB) and IO Burst (IO).

RandomNumberFile format:
1st line: count, remaining lines(equal to count) contain one number per line

Assumption: Input in InputFile and RandomNumberFile is well formed and does not require any checks
Successfully tested with all input and rfile in same folder

Output format:

a) Scheduler information (which scheduler algorithm and if RR the quantum)
b) Per process information:
    for each process (assume processes start with pid=0), the correct desired format is:
    pid: AT TC CB IO PRIO | FT TT IT CW
    FT: Finishing time
    TT: Turnaround time ( finishing time - AT )
    IT: I/O Time ( time in blocked state)
    PRIO: static priority assigned to the process ( note this only has meaning in PRIO case )
c) CW: CPU Waiting time ( time in Ready state )
d) Summary Information - Finally print a summary for the simulation:
    Finishing time of the last event (i.e. the last process finished execution)
    CPU utilization (i.e. percentage (0.0 – 100.0) of time at least one process is running
    IO utilization (i.e. percentage (0.0 – 100.0) of time at least one process is performing IO
    Average turnaround time among processes
    Average cpu waiting time among processes
    Throughput of number processes per 100 time units
    
Output goes to stdout
