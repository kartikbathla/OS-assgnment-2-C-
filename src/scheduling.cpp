#include <string.h>
#include <fstream>
#include <iostream>
#include <queue>
#include <list>
#include <stdio.h>
#include "scheduling.h"

using namespace std;

pqueue_arrival read_workload(string filename)
{
  pqueue_arrival workload;
  ifstream procs;
  procs.open(filename);
  int a, b;
  if(procs.is_open())
  {while(procs >> a >> b){
    Process temp ;
    temp.arrival = stoi(to_string(a));
    temp.duration=   stoi(to_string(b)); 
    workload.push(temp);
  }}

  return workload;
}




void show_workload(pqueue_arrival workload)
{
  pqueue_arrival xs = workload;
  cout << "Workload:" << endl;
  while (!xs.empty())
  {
    Process p = xs.top();
    cout << '\t' << p.arrival << ' ' << p.duration << endl;
    xs.pop();
  }
}

void show_processes(list<Process> processes)
{
  list<Process> xs = processes;
  cout << "Processes:" << endl;
  while (!xs.empty())
  {
    Process p = xs.front();
    cout << "\tarrival=" << p.arrival << ", duration=" << p.duration
         << ", first_run=" << p.first_run << ", completion=" << p.completion << endl;
    xs.pop_front();
  }
}

list<Process> fifo(pqueue_arrival workload)
{
  list<Process> complete;
  while(!workload.empty()){
    Process temp ; 
    temp  = workload.top() ; 
     temp.first_run=temp.arrival>0?temp.arrival:0;
     temp.completion=temp.first_run+temp.duration;
     complete.push_back(temp);
     workload.pop();
   }
  return complete;
}

list<Process> sjf(pqueue_arrival workload)
{
  list<Process> complete;
  pqueue_duration ordered_queue; 
  int counter=0;
  while(!workload.empty()||!ordered_queue.empty()){
    while(!workload.empty()&& workload.top().arrival<=counter){
      ordered_queue.push(workload.top());
      workload.pop();
    }
    if (!ordered_queue.empty()){
        Process temp =ordered_queue.top(); 
        temp.first_run=counter;
        temp.completion=temp.first_run+temp.duration;
        complete.push_back(temp);
        ordered_queue.pop();
    }
    else{
      counter++;
    }
  }
  return complete;
}

list<Process> stcf(pqueue_arrival workload)
{
  list<Process> complete;
  Process temp; 
  int counter =0 ; 
  pqueue_duration stcf_queue;
  if (!workload.empty())
  {
    temp = workload.top();
  }
  while(workload.top().arrival<=counter && !workload.empty()){
    Process temp2 = workload.top();
    workload.pop();
		if(temp2.completion < temp.completion){
				stcf_queue.push(temp);
				temp = temp2;
			}
		else{
				stcf_queue.push(temp2);
			}
    if(temp.duration == temp.completion)
    {
    temp.first_run = counter;
    }
		counter++;
		temp.completion--;
		if(temp.completion <= 0){
			temp.completion = counter;
			complete.push_back(temp); 
			if(!stcf_queue.empty()){
				temp = stcf_queue.top();
				stcf_queue.pop();
			}
			else if(!workload.empty()){
				temp = workload.top();
				counter = temp.arrival;
				workload.pop();
			}
		}
  }
  return complete;
}

list<Process> rr(pqueue_arrival workload)
{
	list<Process> complete;
	queue<Process> rr_queue;
  int counter = 0;
	
	while(!workload.empty() || !rr_queue.empty()){
		while(workload.top().arrival <= counter && !workload.empty()){
			rr_queue.push(workload.top());
			workload.pop();
		}
		if(!rr_queue.empty()){
			Process temp = rr_queue.front();
			rr_queue.pop();
			if(temp.duration == temp.completion)
      {
        temp.first_run = counter;
      }
			counter++;
			temp.completion--;
			if(temp.completion <= 0){
				temp.completion = counter;
				complete.push_back(temp);
			}
			else{
				rr_queue.push(temp);
			}
		}
		else{
			counter++;
		}
	}
	return complete;
}

float avg_turnaround(list<Process> processes)
{
  
  int counter = 0;
  float total_time = 0; 
  while(!processes.empty())
  {
    counter++;
    total_time+= (processes.front().completion-processes.front().arrival); 
    processes.pop_front();
  }

   if (counter!=0){
  return  total_time/counter;}
  else return 0;
}

float avg_response(list<Process> processes)
{
  int total_time=0;
  int counter =0 ; 
  while (!processes.empty()){
    counter++;
    total_time+= processes.front().first_run-processes.front().arrival;
    processes.pop_front();
  }
  if (counter!=0){
  return  total_time/counter;}
  else return 0;
}

void show_metrics(list<Process> processes)
{
  show_processes(processes);
  cout << '\n';
  cout << "Average Turnaround Time: " << avg_turnaround(processes) << endl;
  cout << "Average Response Time:   " << avg_response(processes) << endl;
}
