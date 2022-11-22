#include <iostream>
#include <bits/stdc++.h>
#include <queue>

using namespace std;
struct process {
    char name;
    int arrivalTime;
    int servingTime;
    int remainingServingTime;
    int finishTime=-1;
    char * state ;
    int turnaroundTime=-1;

};
struct algorithm
{
    int name;
    int quantum;
};
void show(process *processes[], int numberOfProcesses)
{
    for (int i = 0; i < numberOfProcesses; i++) {
        cout <<"Name:" << processes[i]->name <<" ";
        cout <<"Ar:" << processes[i]->arrivalTime<<" ";
        cout <<"SerT :" << processes[i]->servingTime << " ";
        cout <<"Rem Ser:" << processes[i]->remainingServingTime << " ";
        cout <<"FinT:" << processes[i]->finishTime << " ";
        cout <<"Turn T:" << processes[i]->turnaroundTime << " ";
        cout << "State :" << processes[i]->state << endl ;

    }
    cout <<"----------------------------------------------------" <<endl;
}

int main() {
    string mode;
    string line2;
    int totalServingTime;
    int numberOfProcesses;
    char *token;
    char *tem_char_array;
    int temp_int = 0;
    int temp_int2 = 0;
    string temp_string;
    algorithm algo;
    cin >> mode;
    cin >> line2;
    cin >> totalServingTime;
    cin >> numberOfProcesses;
    process *processes[numberOfProcesses];


    {
        temp_int = 0;
        tem_char_array = &line2[0];
        token = strtok(tem_char_array, "-");
        while (token != NULL) {
            if (temp_int == 0) {
                sscanf(token, "%d", &temp_int2);
                algo.name = temp_int2;
            } else if (temp_int == 1) {
                sscanf(token, "%d", &temp_int2);
                algo.quantum = temp_int2;
            }
            token = strtok(NULL, ",");
            temp_int++;
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
        processes[i]->state = new char[totalServingTime + 1];
        processes[i]->state[totalServingTime] = '\0';
        for (int f = 0; f < totalServingTime; f++) {

            processes[i]->state[f] = '-';
        }
    }


    cout << "Output data" << endl;
    cout << mode << endl;
    cout << algo.name << "\t";
    cout << algo.quantum << endl;
    cout << totalServingTime << endl;
    cout << numberOfProcesses << endl;
    show(processes, numberOfProcesses);


    return 0;
}