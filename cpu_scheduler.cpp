#include <bits/stdc++.h>
#include <string>
using namespace std;

int process_no;
int que_head;

string to_string (int x)
{
  stringstream ss;
  ss << x;
  return ss.str();
}

class Process{
  private:
    string name;
    int proc_no;
    int burst_time;
    int priority;
    int arrival_time;

  public:
    Process(){
      proc_no = process_no;
      name = "P" + to_string(proc_no);
      cout << "arrival_time: ";
      int a_t;
      cin >> a_t;
      setArrivalTime(a_t);
      cout << "burst time: ";
      int b_t;
      cin >> b_t;
      setBurstTime(b_t);
      cout << "priority: (if not applicable set 0)";
      int p;
      cin >> p;
      setPriority(p);
    }
    Process(int b_t, int a_t, int p){
      burst_time = b_t;
      arrival_time = a_t;
      priority = p;
      proc_no = process_no;
    }

    //getters to get the private values
    int getProcNo(){
      return proc_no;
    }

    int getBurstTime(){
      return burst_time;
    }

    int getArrivalTime(){
      return arrival_time;
    }

    int getPriority(){
      return priority;
    }

    string getName(){
      return name;
    }

    //setters for changing values real time. The process number is set by the CPU thus cannot be changed by
    //the process generator or the user[in this case.]
    void setBurstTime (int b_t){
      burst_time = b_t;
    }

    void setArrivalTime(int a_t){
      arrival_time = a_t;
    }

    void setPriority(int p){
        priority = p;
    }

    void setName (string n){
      name = n;
    }
};

vector <Process> job_queue;

void enque_jobque(Process process)
{
  job_queue.push_back(process);
  process_no ++;
}


void add_process()
{
  cout << "How many process to add? ";
  int n;
  cin >> n;
  for (int i = 0; i < n; i++){
    Process temp;
    enque_jobque(temp);
  }
}

Process rr_deque_que(){
  return job_queue[que_head++];
}

void display()
{
  cout << "NAME\tPROCESS NO.\tARRIVAL TIME\tBURST TIME\tPRIORITY" << endl;
  for (int i = que_head; i < job_queue.size(); i++){
    cout << job_queue[i].getName() << "\t\t" <<  job_queue[i].getProcNo() << "\t\t" << job_queue[i].getArrivalTime() << "\t\t" << job_queue[i].getBurstTime() << "\t\t" << job_queue[i].getPriority() << endl;
  }
}

void print_gantt(vector<Process> processes)
{
  display();
  int total_time = 0;
  int init_time = 0;
  int size_queue = processes.size();
  for (int i = 0; i < size_queue; i++){
    total_time += processes[i].getBurstTime();
  }
  for (int i = 0; i <  size_queue; i++){
    if (init_time > 9)
      cout << " ";
    if (processes[i].getArrivalTime() > init_time){
      cout << " IL";
      init_time = processes[i].getArrivalTime();
      --i;
    }
    else{
      cout << " " << processes[i].getName();
      init_time += processes[i].getBurstTime();
    }
  }
  cout << endl;
  init_time = 0;
  for (int i = 0; i <  size_queue; i++){
    if (processes[i].getArrivalTime() > init_time){
      cout << init_time << "  ";
      init_time = processes[i].getArrivalTime();
      --i;
    }
    else{
      cout << init_time << "  ";
      init_time += processes[i].getBurstTime();
    }
  }
  cout << " " << init_time;
  cout << endl;
}

void fcfs()
{
  int size_queue = job_queue.size();
  vector <Process> ready_queue = job_queue;
  for (int i = que_head; i < size_queue; i++){
    for (int j = i + 1; j < size_queue; j++){
      if (ready_queue[i].getArrivalTime() > ready_queue[j].getArrivalTime()){
        swap (ready_queue[i], ready_queue[j]);
      }
    }
  }
  print_gantt(ready_queue);
}

void nsjf()
{
    int size_queue = job_queue.size();
    vector <Process> ready_queue = job_queue;
    vector <Process> current_queue;
    for (int i = que_head; i < size_queue; i++){
        for (int j = i + 1; j < size_queue; j++){
          if (ready_queue[i].getArrivalTime() > ready_queue[j].getArrivalTime()){
            swap (ready_queue[i], ready_queue[j]);
          }
        }
    }
    int time = 0;
    current_queue.push_back(ready_queue[0]);
    time = current_queue[current_queue.size()-1].getArrivalTime() + current_queue[current_queue.size()-1].getBurstTime();
    int current_index = 1;
    while (current_index < size_queue){
        int temp = current_index;
        int shortest_time = 999999, shortest_index;
        while (ready_queue[temp].getArrivalTime() <= time && temp < size_queue){
            if (ready_queue[temp].getBurstTime() < shortest_time){
                shortest_index = temp++;
            }
        }
        ///cout << "Loop one done." << endl;
        if (shortest_time == 999999){
            ///cout << "Condition for idle cpu" << endl;
            temp = current_index;
            while (ready_queue[temp].getBurstTime() == 999999 && temp < size_queue){
                temp++;
            }
            shortest_index = temp;

        }
        ///cout << "Special condition passed." << endl;
        current_queue.push_back(ready_queue[shortest_index]);
        ready_queue[shortest_index].setBurstTime(999999);
        time += current_queue[current_queue.size()-1].getBurstTime();
        current_index++;

        ///cout << "Current index: " << current_index << " Process to go: " << shortest_index << endl;
    }
    print_gantt(current_queue);
}

void psjf()
{

}

void p_prior()
{

}

void n_prior()
{

}

void rr()
{

}

void clear_queue()
{

}


void switch_choice(int choice)
{
  switch (choice) {
    case 1: add_process();
            break;
    case 2: display();
            break;
    case 3: fcfs();
            break;
    case 4: nsjf();
            break;
    case 5: psjf();
            break;
    case 6: p_prior();
            break;
    case 7: n_prior();
            break;
    case 8: rr();
            break;
    case 9: clear_queue();
            break;
    case 10:  exit(0);
    default : cout << "Please enter a valid choice..... " << endl;
  }
}

void main_menu()
{
  // system("clear");
  cout << ">>>>>>>>>>>>>>>Welcome to Single Core CPU Scheduler Simulator<<<<<<<<<<<<<<<<<<<<<" << endl << endl << endl;
  cout << "1. Enter Processes to job queue." << endl;
  cout << "2. View Current queue." << endl;
  cout << "3. Run First Come First Serve on the current job queue." << endl;
  cout << "4. Run Shortest Job First (Non-Preemptive) on the current job queue." << endl;
  cout << "5. Run Shortest Job First (Preemptive) on the current job queue." << endl;
  cout << "6. Run Preemptive Priority Scheduling on the current job queue." << endl;
  cout << "7. Run Non-Preemptive Priority Scheduling on the current job queue." << endl;
  cout << "8. Run Round Robin Scheduling on the current job queue." << endl;
  cout << "9. Clear the current queue." << endl;
  cout << "10. Exit." << endl;
}

int main(){
  process_no = 0;
  que_head = 0;
  int choice;
  while (true){
    main_menu();
    cin >> choice;
    switch_choice(choice);
  }
}
