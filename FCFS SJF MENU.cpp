#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//Suggested to run in Linux running system. It will run in all CPP compiler only error will be shown as 
// ERROR: system("clear"); is not defined. change the lines into system("cls"); for windows dont know for mac
//utility function to get average from an array.

double average(double waiting[], int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++){\
        sum += waiting[i];
    }
    return sum/n;
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
    //Gannt Chart
    for (int i = 0; i < n; i++){
        cout << "P" << processNum[i] << "    ";
    }
    cout << endl;
    //the cpu timer starts with the first process. And this particular program does not take idle time in begining to the sense.
    // but it does count and exclude the idle time.
    double currentTime = arrival[0];
    cout << currentTime << "  ";
    for (int i = 0; i < n; i++){
        cout << currentTime+burstTime[i] << "  ";
        executionTime[i] = currentTime;
        waitingTime[i] = currentTime - arrival[i];
        turnAround[i] = waitingTime[i] + (double) burstTime[i];
        currentTime += burstTime[i];
        //cpu idle checking
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

