#include <iostream>
#include <bits/stdc++.h>
#include <queue>

using namespace std;
struct process {
    char name;
    int arrivalTime;
    int servingTime;
    int remainingServingTime;
    int finishTime = -1;
    char *state;
    int turnaroundTime = -1;
    int waitingTime=0;
    float normTurn=-1;
};
struct comp_SPN{
    bool operator()(struct process*  a, struct process* b){
        return (a->servingTime > b->servingTime);
    }
};
struct comp_SRT{
    bool operator()(struct process*  a, struct process* b){
        //Sorting on the basis of height(Just for example)
        return (a->remainingServingTime > b->remainingServingTime);
    }
};
struct comp_HRRN{
    bool operator()(struct process*  a, struct process* b){
        //Sorting on the basis of height(Just for example)
        return ((( a->waitingTime + a->remainingServingTime)/float(a->remainingServingTime)) < (( b->waitingTime+b->remainingServingTime)/float(b->remainingServingTime)));
    }
};
struct algorithm {
    int name;
    int quantum;
};

void bubbleSort(process *processes[], int number_of_processes)
{
    int i, j;
    process *temp;
    for (i = 0; i < number_of_processes - 1; i++)

        for (j = 0; j < number_of_processes - i - 1; j++)
            if (processes[j]->arrivalTime > processes[j+1]->arrivalTime)
            {
                temp=processes[j+1];
                processes[j+1]=processes[j];
                processes[j]=temp;
            }

}
void firstComeFirstServe(process *processes[], int number_of_processes, int total_serving_time) {
    queue<process *> waiting_queue;
    process *running_process = NULL;
    int waiting_time;
    for (int i = 0; i < number_of_processes; i++) {
        waiting_queue.push(processes[i]);
    }

    for (int i = 0, j = 0; i < total_serving_time; i++) {

        if (running_process == NULL) {
            running_process = waiting_queue.front();
            waiting_queue.pop();
            running_process->remainingServingTime--;
            running_process->state[i] = '*';
            continue;
        }
        if (running_process->remainingServingTime == 0) {
            running_process->finishTime = i;
            running_process->turnaroundTime = running_process->finishTime - running_process->arrivalTime;
            running_process->normTurn=running_process->turnaroundTime/float(running_process->servingTime);
            processes[j] = running_process;
            j++;
            running_process = waiting_queue.front();
            waiting_time = running_process->arrivalTime;
            while (waiting_time <= i) {
                running_process->state[waiting_time] = '.';
                waiting_time++;
            }
            waiting_queue.pop();
        }
        if (running_process->remainingServingTime > 0) {
            running_process->remainingServingTime--;
            running_process->state[i] = '*';
        }
    }
    running_process->finishTime = total_serving_time;
    running_process->turnaroundTime = running_process->finishTime - running_process->arrivalTime;
    running_process->normTurn=running_process->turnaroundTime/float(running_process->servingTime);

    processes[number_of_processes] = running_process;
    waiting_queue.pop();
}
void show(process *processes[], int numberOfProcesses) {
    for (int i = 0; i < numberOfProcesses; i++) {
        cout << "Name:" << processes[i]->name << " ";
        cout << "Ar:" << processes[i]->arrivalTime << " ";
        cout << "SerT :" << processes[i]->servingTime << " ";
        cout << "Rem Ser:" << processes[i]->remainingServingTime << " ";
        cout << "FinT:" << processes[i]->finishTime << " ";
        cout << "Turn T:" << processes[i]->turnaroundTime << " ";
        cout << "State :" << processes[i]->state << endl;

    }
    cout << "----------------------------------------------------" << endl;
}

void trace(process *processes[], algorithm algo, int totalServingTime, int number_of_processes) {
    bubbleSort(processes,number_of_processes);
    if (algo.name == 1)
        cout << "FCFS  ";
    else if (algo.name ==2)
        cout << "RR-"<<algo.quantum<<"  ";
    else if (algo.name==3)
        cout << "SPN   ";
    else if (algo.name==4)
        cout << "SRT   ";
    else if (algo.name==5)
        cout << "HRRN  ";
    else if (algo.name==6)
        cout << "FB-1  ";
    else if (algo.name==7)
        cout << "FB-2i ";
    for (int i = 0; i <= totalServingTime; i++) {
        cout << i % 10 << " ";
    }
    cout << endl;
    for (int i = 0; i <= 2 * totalServingTime + 7; i++) {
        cout << "-";
    }
    cout << endl;
    for (int i = 0; i < number_of_processes; i++) {
        cout << processes[i]->name << "     ";
        for (int j = 0; j <= totalServingTime-1; j++) {
            cout << "|";
            if (processes[i]->state[j] == '-')
                cout << " ";
            else
                cout << processes[i]->state[j];
        }
    cout <<"| " << endl;
    }
    for (int i = 0; i <= 2 * totalServingTime + 7; i++) {
        cout << "-";
    }
    cout << endl << endl;

}

void state(process *processes[], algorithm algo, int totalServingTime, int number_of_processes) {
    bubbleSort(processes,number_of_processes);
    float mean = 0;
    if (algo.name == 1)
        cout << "FCFS" << endl;
    else if (algo.name ==2)
        cout << "RR-" <<algo.quantum << endl;
    else if (algo.name ==3)
        cout << "SPN" << endl;
    else if (algo.name ==4)
        cout << "SRT" << endl;
    else if (algo.name==5)
        cout << "HRRN"<<endl;
    else if (algo.name==6)
        cout << "FB-1"<<endl;
    else if (algo.name==7)
        cout << "FB-2i"<<endl;
    cout << "Process  ";
    for (int i = 0; i < number_of_processes; i++) {
        cout << "  |  " << processes[i]->name;
    }
    cout << "  |" << endl;

    cout << "Arrival    ";
    for (int i = 0; i < number_of_processes; i++) {
        printf("|%3d  ", processes[i]->arrivalTime);

    }
    cout << "|" << endl;
    cout << "Service    ";
    for (int i = 0; i < number_of_processes; i++) {
        printf("|%3d  ", processes[i]->servingTime);

    }
    cout << "| Mean|" << endl;
    cout << "Finish     ";
    for (int i = 0; i < number_of_processes; i++) {
        printf("|%3d  ", processes[i]->finishTime);

    }
    cout << "|-----|" << endl;
    cout << "Turnaround ";
    for (int i = 0; i < number_of_processes; i++) {
        printf("|%3d  ", processes[i]->turnaroundTime);
        mean += processes[i]->turnaroundTime;
    }
    printf("|%5.2f|\n", mean / float(number_of_processes));
    mean=0;
    cout << "NormTurn   ";
    for (int i = 0; i < number_of_processes; i++) {
        printf("| %3.2f", processes[i]->normTurn);
        mean += processes[i]->normTurn;
    }
    printf("|%5.2f|\n\n", mean / float(number_of_processes));
}

void roundRobin(process *processes[], int number_of_processes, int total_serving_time,int quantum)
{
    unordered_map<int,process*> processes_map;
    deque<process *> waiting_queue;
    process *running_process = NULL;
    int j=0;
    int q=0;
    for (int i = 0; i < number_of_processes; i++) {
        processes_map[processes[i]->arrivalTime]=processes[i];
    }

    for (int i = 0; i < total_serving_time; i++) {

        if (processes_map.find(i) != processes_map.end())
            waiting_queue.push_back(processes_map.find(i)->second);
        if (q==0) {
            if (running_process == NULL) {
                running_process = waiting_queue.front();
                waiting_queue.pop_front();
                q = quantum;
            }
            else if (running_process != NULL && running_process->remainingServingTime > 0 && q == 0) {
                waiting_queue.push_back(running_process);
                q = quantum;
                running_process = waiting_queue.front();
                waiting_queue.pop_front();

            }
        }
        if(q!=0)
        {
            if (running_process == NULL ) {
                running_process = waiting_queue.front();
                waiting_queue.pop_front();
            }
            //5adema 3aleihaa
            running_process->remainingServingTime--;
            running_process->state[i]='*';
            q--;
            if(running_process->remainingServingTime ==0)
            {
                running_process->finishTime = i+1;
                running_process->turnaroundTime = running_process->finishTime - running_process->arrivalTime;
                running_process->normTurn=running_process->turnaroundTime/float(running_process->servingTime);
                processes[j] = running_process;
                j++;
                running_process=NULL;
                q=0;
            }
        }
        //less 3ayza serivce we fadel quantum 7ot odam
        if(running_process!=NULL && running_process->remainingServingTime!=0 && q!=0 )
        {
            waiting_queue.push_front(running_process);
            running_process=NULL;
        }

    }
    for (int i = 0; i < number_of_processes; i++) {
        for (int j = 0; j < total_serving_time; j++) {
            if (j >= processes[i]->arrivalTime &&  j < processes[i]->finishTime)
                if(processes[i]->state[j] == '-')
                    processes[i]->state[j]='.';
        }
    }
}

void SPN(process *processes[], int number_of_processes, int total_serving_time)
{
    unordered_map<int,process*> processes_map;
    priority_queue<process*, vector<process*>, comp_SPN> waiting_queue;
    process *running_process = NULL;
    int waiting_time=0;
    for (int i = 0; i < number_of_processes; i++) {
        processes_map[processes[i]->arrivalTime]=processes[i];
    }
    for (int i = 0; i < total_serving_time; i++) {
        if (processes_map.find(i) != processes_map.end())
            waiting_queue.push(processes_map.find(i)->second);
        if (running_process==NULL)
        {
            running_process=waiting_queue.top();
            waiting_queue.pop();
            waiting_time=running_process->arrivalTime;
            while (waiting_time <= i) {
                running_process->state[waiting_time] = '.';
                waiting_time++;
            }
        }
        else if(running_process!=NULL && running_process->remainingServingTime==0)
        {
            running_process->finishTime = i;
            running_process->turnaroundTime = running_process->finishTime - running_process->arrivalTime;
            running_process->normTurn=running_process->turnaroundTime/float(running_process->servingTime);

            running_process=waiting_queue.top();
            waiting_queue.pop();
            waiting_time=running_process->arrivalTime;
            while (waiting_time <= i) {
                running_process->state[waiting_time] = '.';
                waiting_time++;
            }
        }
        if(running_process->remainingServingTime>0)
        {
            running_process->remainingServingTime--;
            running_process->state[i]='*';
        }

    }
    running_process->finishTime = total_serving_time;
    running_process->turnaroundTime = running_process->finishTime - running_process->arrivalTime;
    running_process->normTurn=running_process->turnaroundTime/float(running_process->servingTime);



}

void SRT(process *processes[], int number_of_processes, int total_serving_time)
{
    unordered_map<int,process*> processes_map;
    priority_queue<process*, vector<process*>, comp_SRT> waiting_queue;
    process *running_process = NULL;
    int q=0;
    for (int i = 0; i < number_of_processes; i++) {
        processes_map[processes[i]->arrivalTime]=processes[i];
    }
    for (int i = 0; i < total_serving_time; i++) {
        if (processes_map.find(i) != processes_map.end())
            waiting_queue.push(processes_map.find(i)->second);
        if (q==0) {
            if (running_process == NULL) {
                running_process = waiting_queue.top();
                waiting_queue.pop();
                q = 1;
            }
            else if (running_process != NULL && running_process->remainingServingTime > 0 && q == 0) {
                waiting_queue.push(running_process);
                q = 1;
                running_process = waiting_queue.top();
                waiting_queue.pop();

            }
        }
        if(q!=0)
        {
            if (running_process == NULL ) {
                running_process = waiting_queue.top();
                waiting_queue.pop();
            }
            //5adema 3aleihaa
            running_process->remainingServingTime--;
            running_process->state[i]='*';
            q--;
            if(running_process->remainingServingTime ==0)
            {
                running_process->finishTime = i+1;
                running_process->turnaroundTime = running_process->finishTime - running_process->arrivalTime;
                running_process->normTurn=running_process->turnaroundTime/float(running_process->servingTime);

                running_process=NULL;
                q=0;
            }
        }
        //less 3ayza serivce we fadel quantum 7ot odam
        if(running_process!=NULL && running_process->remainingServingTime!=0 && q!=0 )
        {
            waiting_queue.push(running_process);
            running_process=NULL;
        }
        for (int i = 0; i < number_of_processes; i++) {
            for (int j = 0; j < total_serving_time; j++) {
                if (j >= processes[i]->arrivalTime &&  j < processes[i]->finishTime)
                    if(processes[i]->state[j] == '-')
                        processes[i]->state[j]='.';
            }
        }
    }
    for (int i = 0; i < number_of_processes; i++) {
        for (int j = 0; j < total_serving_time; j++) {
            if (j >= processes[i]->arrivalTime &&  j < processes[i]->finishTime)
                if(processes[i]->state[j] == '-')
                    processes[i]->state[j]='.';
        }
    }

}

void HRRN(process *processes[], int number_of_processes, int total_serving_time)
{
    unordered_map<int,process*> processes_map;
    queue<process*> temp_queue;
    priority_queue<process*, vector<process*>, comp_HRRN> waiting_queue;
    process *running_process = NULL;
    process *temp_process=NULL;
    int waiting_time=0;
    for (int i = 0; i < number_of_processes; i++) {
        processes_map[processes[i]->arrivalTime]=processes[i];
    }
    for (int i = 0; i < total_serving_time; i++) {
        //If a process arrive ad it to the queue
        while (!waiting_queue.empty()) {
            temp_process=waiting_queue.top();
            waiting_queue.pop();
            temp_process->waitingTime++;
            temp_queue.push(temp_process);
        }
        while (!temp_queue.empty()) {
            waiting_queue.push(temp_queue.front());
            temp_queue.pop();
        }
        if (processes_map.find(i) != processes_map.end())
            waiting_queue.push(processes_map.find(i)->second);

        //if it is the first process
        if (running_process==NULL)
        {
            running_process=waiting_queue.top();
            waiting_queue.pop();
            waiting_time=running_process->arrivalTime;
            while (waiting_time <= i) {
                running_process->state[waiting_time] = '.';
                waiting_time++;
            }
        }
        //if the running process finished it serving time
        else if(running_process!=NULL && running_process->remainingServingTime==0)
        {

            running_process->finishTime = i;
            running_process->turnaroundTime = running_process->finishTime - running_process->arrivalTime;
            running_process->normTurn=running_process->turnaroundTime/float(running_process->servingTime);

            running_process=waiting_queue.top();
            waiting_queue.pop();
            waiting_time=running_process->arrivalTime;
            while (waiting_time <= i) {
                running_process->state[waiting_time] = '.';
                waiting_time++;
            }
        }
        //if the running process still need serving time
        if(running_process->remainingServingTime>0)
        {
            running_process->remainingServingTime--;
            running_process->state[i]='*';
        }
    }
    running_process->finishTime = total_serving_time;
    running_process->turnaroundTime = running_process->finishTime - running_process->arrivalTime;
    running_process->normTurn=running_process->turnaroundTime/float(running_process->servingTime);

}

void FB2(process *processes[], int number_of_processes, int total_serving_time)
{
    unordered_map<int,process*> processes_map;
    queue<process*> temp_queue;
    vector<deque<process*>>  waiting_queues;
    for (int i = 0; i < total_serving_time; i++)
        waiting_queues.push_back(deque<process*>());
    process *running_process = NULL;
    int q=0,f,level=0;
    int empty=1;
    for (int i = 0; i < number_of_processes; i++) {
        processes_map[processes[i]->arrivalTime]=processes[i];
    }

    for (int i = 0; i < total_serving_time; i++) {
        if (processes_map.find(i) != processes_map.end())
            waiting_queues[0].push_front(processes_map.find(i)->second);

        if( q==0 )
            for (int j = 0; j < total_serving_time; j++)
            {
                if (waiting_queues[j].empty())
                    continue;
                else
                {
                    running_process=waiting_queues[j].front();
                    waiting_queues[j].pop_front();
                    q= int(pow(2, j));
                    level=j;
                    break;
                }
            }

        if(q!=0)
        {

            //5adema 3aleihaa
            running_process->remainingServingTime--;
            running_process->state[i]='*';
            q--;
            if(running_process->remainingServingTime ==0)
            {

                running_process->finishTime = i+1;
                running_process->turnaroundTime = running_process->finishTime - running_process->arrivalTime;
                running_process->normTurn=running_process->turnaroundTime/float(running_process->servingTime);
                processes[f] = running_process;
                f++;
                running_process=NULL;
                q=0;
            }
        }
        //less 3ayza serivce we mach fadel quantum
        if(running_process!=NULL && running_process->remainingServingTime!=0 && q==0)
        {
            for (int v= 0; v < total_serving_time; v++)
            {
                if (waiting_queues[v].empty())
                {
                    empty=1;
                    continue;
                }
                else
                {
                    empty=0;
                    break;
                }
            }
            if(empty)
                waiting_queues[level].push_back(running_process);
            else
                waiting_queues[level+1].push_back(running_process);

            running_process=NULL;
        }
    }
    for (int i = 0; i < number_of_processes; i++) {
        for (int j = 0; j < total_serving_time; j++) {
            if (j >= processes[i]->arrivalTime &&  j < processes[i]->finishTime)
                if(processes[i]->state[j] == '-')
                    processes[i]->state[j]='.';
        }
    }
}

void FB1(process *processes[], int number_of_processes, int total_serving_time)
{
    unordered_map<int,process*> processes_map;
    queue<process*> temp_queue;
    vector<deque<process*>>  waiting_queues;
    for (int i = 0; i < total_serving_time; i++)
        waiting_queues.push_back(deque<process*>());
    process *running_process = NULL;

    int q=0,f,level=0;

    int empty=1;
    for (int i = 0; i < number_of_processes; i++) {
        processes_map[processes[i]->arrivalTime]=processes[i];
    }

    for (int i = 0; i < total_serving_time; i++) {
        if (processes_map.find(i) != processes_map.end())
            waiting_queues[0].push_front(processes_map.find(i)->second);

        if( q==0 )
            for (int j = 0; j < total_serving_time; j++)
            {
                if (waiting_queues[j].empty())
                    continue;
                else
                {
                    running_process=waiting_queues[j].front();
                    waiting_queues[j].pop_front();
                    q= 1;
                    level=j;
                    break;
                }
            }

        if(q!=0)
        {

            //5adema 3aleihaa
            running_process->remainingServingTime--;
            running_process->state[i]='*';
            q--;
            if(running_process->remainingServingTime ==0)
            {

                running_process->finishTime = i+1;
                running_process->turnaroundTime = running_process->finishTime - running_process->arrivalTime;
                running_process->normTurn=running_process->turnaroundTime/float(running_process->servingTime);
                processes[f] = running_process;
                f++;
                running_process=NULL;
                q=0;
            }
        }
        //less 3ayza serivce we mach fadel quantum
        if(running_process!=NULL && running_process->remainingServingTime!=0 && q==0)
        {
            for (int v= 0; v < total_serving_time; v++)
            {
                if (waiting_queues[v].empty())
                {
                    empty=1;
                    continue;
                }
                else
                {
                    empty=0;
                    break;
                }
            }
            if(empty)
                waiting_queues[level].push_back(running_process);
            else
                waiting_queues[level+1].push_back(running_process);

            running_process=NULL;
        }
    }
    for (int i = 0; i < number_of_processes; i++) {
        for (int j = 0; j < total_serving_time; j++) {
            if (j >= processes[i]->arrivalTime &&  j < processes[i]->finishTime)
                if(processes[i]->state[j] == '-')
                    processes[i]->state[j]='.';
        }
    }
}

int main() {

    string mode;
    string line2;
    int totalServingTime;
    int numberOfProcesses;
    char *token;
    char *token2;
    char *tem_char_array;
    int temp_int = 0;
    int temp_int2 = 0;
    int num_alogs=1;

    string temp_string;
    algorithm *algos;
    cin >> mode;
    cin >> line2;
    cin >> totalServingTime;
    cin >> numberOfProcesses;
    process *processes[numberOfProcesses];

    {
        tem_char_array =  &line2[0];
        char * str1=tem_char_array;
        char* str2;
        token2 = strtok_r(str1, ",",&str1);
        num_alogs=1;
        algos = static_cast<algorithm *>(malloc(num_alogs * sizeof(struct algorithm)));
        while (token2!=NULL)
        {
            algos= static_cast<algorithm *>(realloc(algos, (num_alogs) * sizeof(struct algorithm)));
            temp_int = 0;
            temp_int2=0;
            str2=token2;
            token = strtok_r(token2, "-",&str2);
            while (token != NULL) {
                if (temp_int == 0) {
                    sscanf(token, "%d", &temp_int2);
                    algos[num_alogs-1].name = temp_int2;
                } else if (temp_int == 1) {
                    sscanf(token, "%d", &temp_int2);
                    algos[num_alogs-1].quantum = temp_int2;
                }
                token = strtok_r(str2, "-",&str2);
                temp_int++;
            }
            token2 = strtok_r(str1, ",",&str1);
            num_alogs++;
        }
    }
    temp_int = 0;
    temp_int2 = 0;
    for (int i = 0; i < numberOfProcesses; i++) {
        processes[i] = new process;
        cin >> temp_string;
        tem_char_array = &temp_string[0];
        token = strtok(tem_char_array, ",");
        temp_int = 1;
        while (token != NULL) {
            if (temp_int == 1) { processes[i]->name = token[0]; }
            else if (temp_int == 2) {
                sscanf(token, "%d", &temp_int2);
                processes[i]->arrivalTime = temp_int2;
            } else {
                sscanf(token, "%d", &temp_int2);
                processes[i]->servingTime = temp_int2;
                processes[i]->remainingServingTime = temp_int2;
            }
            token = strtok(NULL, ",");
            temp_int++;
        }
        processes[i]->state = new char[totalServingTime ];

        for (int f = 0; f < totalServingTime; f++) {

            processes[i]->state[f] = '-';
        }
    }

    for (int i =0;i<num_alogs-1;i++)
    {
        if (algos[i].name==1)
            firstComeFirstServe(processes, numberOfProcesses, totalServingTime);
        else if (algos[i].name==2)
            roundRobin(processes, numberOfProcesses, totalServingTime,algos[i].quantum);
        else if (algos[i].name==3)
            SPN(processes, numberOfProcesses, totalServingTime);
        else if (algos[i].name==4)
            SRT(processes, numberOfProcesses, totalServingTime);
        else if (algos[i].name==5)
            HRRN(processes, numberOfProcesses, totalServingTime);
        else if (algos[i].name==6)
            FB1(processes, numberOfProcesses, totalServingTime);
        else if (algos[i].name==7)
            FB2(processes, numberOfProcesses, totalServingTime);

        if(mode=="stats")
            state(processes, algos[i], totalServingTime, numberOfProcesses);
        else
            trace(processes, algos[i],totalServingTime, numberOfProcesses);
    }

    return 0;
}