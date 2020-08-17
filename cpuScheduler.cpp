#include <iostream>
#include <bits/stdc++.h>
using namespace std;

double average(double waiting[], int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++){\
        sum += waiting[i];
    }
    return sum/n;
}


void roundRobin()
{
    int burstTime[100];
    double arrival[100];
    double executionTime[100];
    double waitingTime[100];
    double turnAround[100];
    int processNum[100];
    int timeQuantum;
    int n;
    int qu[100][3];
    int quIndex=0;
    int quToIndex=0;
    cout << "Number of process: ";
    cin >> n;
    for (int i = 0; i < n; i++){
        cout << "Arrival time for P" << i << ": ";
        cin >> arrival[i];
        cout << "Burst time for P" << i << ": ";
        cin >> burstTime[i];
        processNum[i] = i;
    }
    cout << endl;
    cout << "Time Quantum: ";
    cin >> timeQuantum;
    system("clear");

    //First sort for the arrival time so that they are in order..
    for (int i = 0; i < n-1; i++){
        for (int j = i+1; j < n; j++){
            if (arrival[i] > arrival[j]){
                swap(arrival[i], arrival[j]);
                swap(burstTime[i], burstTime[j]);
                swap(processNum[i], processNum[j]);
            }
        }
    }

    qu[quIndex][0] = processNum[0];
    qu[quIndex][1] = burstTime[0];
    qu[quIndex][2] = arrival[0];
    quToIndex++;

    bool isDone = false;
    double currentTime = arrival[0];

    int printProcessNum[1000], printTime[1000];
    int processIndex = 0;
    int loopCounter=0;

    //counting total time
    int totalTime = 0;
    for (int i = 0; i < n; i++){
        totalTime += burstTime[i];
        if (totalTime < arrival[i+1]){
            totalTime += arrival[i+1]-totalTime;
        }
    }

    //making all of their waiting time as thei arrival time

    for (int i = 0; i < n; i++){
        waitingTime[i] = arrival[i];
    }
    while (!isDone){
        int tempinc;
        printProcessNum[loopCounter] = qu[quIndex][0];
        printTime[loopCounter] = currentTime;
        if (qu[quIndex][2] == -1){
            waitingTime[qu[quIndex][0]] = currentTime - waitingTime[qu[quIndex][0]];
        }
        else{
            waitingTime[qu[quIndex][0]] += currentTime - qu[quIndex][2];
        }

        if (qu[quIndex][1] < timeQuantum){
            tempinc = qu[quIndex][1];
        }
        else{
            tempinc = timeQuantum;
        }
        //if any process comes during the execution of the previous process;
        while (currentTime >= arrival[processIndex]){
            qu[quToIndex][0] = processNum[processIndex];
            qu[quToIndex][1] = burstTime[processIndex];
            qu[quToIndex][2] = -1;
            processIndex++;
            quToIndex++;
        }
        //check if the current process to go round in the last of the queue
        if (qu[quIndex][1] > timeQuantum){
            qu[quToIndex][0] = qu[quIndex][0];
            qu[quToIndex][1] = qu[quIndex][1]-timeQuantum;
            qu[quToIndex][2] = currentTime+tempinc;
            quToIndex++;
            quIndex++;
        }
        loopCounter++;
        currentTime += tempinc;
        if (currentTime >= totalTime){
            isDone = true;
        }
    }

    //turn around time calculation
    for (int i = 0; i < n; i++){
        turnAround[i] = waitingTime[i] + burstTime[i];
    }


    double averageWaitingTime = average(waitingTime, n);
    double averageTurnAroundTime = average(turnAround, n);

    //printing the processess
    for (int i = 0; i < loopCounter; i++){
        cout << "P" << processNum[printProcessNum[i]] << "   ";
    }
    cout << endl;

    //printing the process times

    for (int i = 0; i < loopCounter; i++){
        cout << printTime[i] << "    ";
    }
    cout << endl;

    cout << "PR   A.T    B.T  ET  WT    TA" << endl;
    for (int i = 0; i < n; i++){
        cout << "P" << processNum[i] << "    " << arrival[i] << "    " << burstTime[i] << "    " << executionTime[i] << "    " << waitingTime[i] << "    " << turnAround[i] << endl;
    }
    cout << endl;
    cout << "Average waiting time = " << averageWaitingTime<< endl;
    cout << "Average turn around time = " << averageTurnAroundTime << endl;
    cout << "Press any key to continue....";
    getchar();
    getchar();
    system("clear");

}



void sjf ()
{
    int burstTime[100];
    double arrival[100];
    double executionTime[100];
    double waitingTime[100];
    double turnAround[100];
    int processNum[100];
    int n;
    cout << "Number of process: ";
    cin >> n;
    for (int i = 0; i < n; i++){
        cout << "Arrival time for P" << i << ": ";
        cin >> arrival[i];
        cout << "Burst time for P" << i << ": ";
        cin >> burstTime[i];
        processNum[i] = i;
    }
    system("clear");

    //First sort for the arrival time so that they are in order..
    for (int i = 0; i < n-1; i++){
        for (int j = i+1; j < n; j++){
            if (arrival[i] > arrival[j]){
                swap(arrival[i], arrival[j]);
                swap(burstTime[i], burstTime[j]);
                swap(processNum[i], processNum[j]);
            }
        }
    }
    //now sort them for their burst time to continue with SJF
    //gotta change them according to where they get execute..

    double tempcurr = arrival[0];
    for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++){
            if (arrival[j] <= tempcurr && burstTime[i] > burstTime[j]){
                swap(arrival[i], arrival[j]);
                swap(burstTime[i], burstTime[j]);
                swap(processNum[i], processNum[j]);
            }
        }
        tempcurr += burstTime[i];
        if (tempcurr < arrival[i+1]){
            tempcurr += arrival[i+1];
        }
    }
    for (int i = 0; i < n; i++){
        cout << "P" << processNum[i] << "    ";
    }
    cout << endl;
    double currentTime = arrival[0];
    cout << currentTime << "  ";
    for (int i = 0; i < n; i++){
        cout << currentTime+burstTime[i] << "  ";
        executionTime[i] = currentTime;
        waitingTime[i] = currentTime - arrival[i];
        turnAround[i] = waitingTime[i] + (double) burstTime[i];
        currentTime += burstTime[i];
        if (currentTime < arrival[i+1]){
            currentTime += arrival[i+1];
        }
    }
    cout << endl;
    double avgWaiting = average(waitingTime, n);
    double averageTurnAround = average(turnAround, n);

    cout << "PR   A.T    B.T  ET  WT    TA" << endl;
    for (int i = 0; i < n; i++){
        cout << "P" << processNum[i] << "    " << arrival[i] << "    " << burstTime[i] << "    " << executionTime[i] << "    " << waitingTime[i] << "    " << turnAround[i] << endl;
    }
    cout << endl;
    cout << "Average waiting time = " << avgWaiting << endl;
    cout << "Average turn around time = " << averageTurnAround << endl;
    cout << "Press any key to continue....";
    getchar();
    getchar();
    system("clear");

}


void fcfs()
{
    int bursttime[100];
    double arrival[100];
    int processnum[100];
    double waitingTime[100];
    double turnAround[100];
    double executionTime[100];
    int n;
    cout << "Number of process: " << endl;
    cin >> n;
    for (int i = 0; i < n; i++){
        cout << "Arrival time for process" << i << ": ";
        cin >> arrival[i];
        cout << "Burst time for process" << i << ": ";
        cin >> bursttime[i];
        processnum[i]=i;
    }
    system("clear");

    for (int i = 0; i < n-1; i++){
        for (int j = i+1; j < n; j++){
            if (arrival[i] > arrival[j]){
                swap(arrival[i], arrival[j]);
                swap(bursttime[i], bursttime[j]);
                swap(processnum[i], processnum[j]);
            }
        }
    }
    for (int i = 0; i < n; i++){
        cout << "P" << processnum[i] << "\t";
    }
    cout << endl;
    double currentTime = 0.0;
    cout << currentTime << "  ";
    for (int i = 0; i < n; i++){
        cout << currentTime+bursttime[i] << "  ";
        executionTime[i] = currentTime;
        waitingTime[i] = currentTime - arrival[i];
        turnAround[i] = waitingTime[i] + (double) bursttime[i];
        currentTime += bursttime[i];
        if (currentTime < arrival[i+1]){
            currentTime + arrival[i+1];
        }
    }
    cout << endl;
    double avgWaiting = average(waitingTime, n);
    double averageTurnAround = average(turnAround, n);

    cout << "PR   A.T    B.T  ET  WT    TA" << endl;
    for (int i = 0; i < n; i++){
        cout << "P" << processnum[i] << "    " << arrival[i] << "    " << bursttime[i] << "    " << executionTime[i] << "    " << waitingTime[i] << "    " << turnAround[i] << endl;
    }
    cout << endl;
    cout << "Average waiting time = " << avgWaiting << endl;
    cout << "Average turn around time = " << averageTurnAround << endl;
    cout << "Press any key to continue....";
    getchar();
    getchar();
    system("clear");
}

void menu()
{
    cout << endl;
    cout << "1. FCFS algorithm." << endl;
    cout << "2. SJF algorithm." << endl;
    cout << "3. Round Robin." << endl;
    cout << "0. Exit." << endl;

}

int main ()
{
    int choice;
    while (true){
        cout << "Enter your choice: ";
        menu();
        cin >> choice;

        switch(choice){
            case 1: system("clear");
                    fcfs();
                    break;
            case 2: system("clear");
                    sjf();
                    break;
            case 3: system("clear");
                    roundRobin();
                    break;
            case 0: return 0;
            default : system("clear");
        }
    }
    return 0;
}

