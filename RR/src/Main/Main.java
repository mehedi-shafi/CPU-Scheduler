package Main;

import Model.ProcessObj;

import java.util.*;

public class Main {

    private static int numberOfProcess;
    private static int timeQuantum;
    private static ArrayList<ProcessObj> processList = new ArrayList<>();
    private static HashMap<Integer, ProcessObj> finalStat = new HashMap<>();

    public static void main(String[] args) {
	// write your code

        System.out.print("Number of processes: ");
        Scanner scan = new Scanner(System.in);

        numberOfProcess = scan.nextInt();

        for (int i = 0; i < numberOfProcess; i++){
            ProcessObj newProc = new ProcessObj();
            System.out.print ("Process P" + i + " arrival time? ");
            newProc.setArrival(scan.nextDouble());
            System.out.print("Process P" + i + " burst time? ");
            newProc.setBurstTime(scan.nextInt());
            newProc.setRemainingBurstTime(newProc.getBurstTime());
            newProc.setProcessNum(i);
            processList.add(newProc);
        }

        System.out.print ("Time quantum: ");
        timeQuantum = scan.nextInt();

        roundRobin();

    }

    private static void roundRobin (){
        ArrayList<ProcessObj> robinQueeue = new ArrayList<>();
        ArrayList<ProcessObj> printQueue = new ArrayList<>();

        //First order them according to their arrival time

        for (int i =0; i < numberOfProcess; i++){
            for (int j = i+1; j < numberOfProcess; j++){
                if (processList.get(i).getArrival() > processList.get(j).getArrival()){
                    Collections.swap(processList, i, j);
                }
            }
        }

        //now start putting them inside the queue to start processing.

        //as the first process will be the first one to get in execution anyways.
        double currentTime = processList.get(0).getArrival();
        robinQueeue.add(processList.get(0));
        int currentProcess = 1;

        int iterationCheck = 0;
        while (robinQueeue.size() != 0){

            //How much time the execution occured.
            //  if the process has lower time remaining than timequantam then its different then TQ
            // else it is the timequantam

            int changeInTimeFrame;
            if (robinQueeue.get(0).getRemainingBurstTime() >= timeQuantum){
                changeInTimeFrame = timeQuantum;
            }
            else{
                changeInTimeFrame = robinQueeue.get(0).getRemainingBurstTime();
            }

            //calculating waiting time for the process.
            if (robinQueeue.get(0).getLastExecuted() == -1){
                robinQueeue.get(0).setWaitingTime(currentTime - robinQueeue.get(0).getArrival());
                robinQueeue.get(0).setLastExecuted(currentTime + changeInTimeFrame);
                robinQueeue.get(0).setExecutionTimeFrame(changeInTimeFrame);
            }
            else{
                robinQueeue.get(0).setWaitingTime(robinQueeue.get(0).getWaitingTime() + (currentTime - robinQueeue.get(0).getLastExecuted()));
                robinQueeue.get(0).setLastExecuted(currentTime + changeInTimeFrame);
                robinQueeue.get(0).setExecutionTimeFrame(changeInTimeFrame);
            }

            //first check if there is any new process came in the mean time
            while (currentProcess < processList.size() && processList.get(currentProcess).getArrival() <= currentTime + changeInTimeFrame){
                robinQueeue.add(processList.get(currentProcess));
                currentProcess ++;
            }

            //Now put the current queue process in the print queue and make it rotate
            printQueue.add(robinQueeue.get(0));
            if (robinQueeue.get(0).getRemainingBurstTime() > timeQuantum){
                ProcessObj tempProc = new ProcessObj(robinQueeue.get(0));
                tempProc.setRemainingBurstTime(tempProc.getRemainingBurstTime() - timeQuantum);
                robinQueeue.add(tempProc);
            }else{
                finalStat.put(robinQueeue.get(0).getProcessNum(), robinQueeue.get(0));
            }
            robinQueeue.remove(0);

            //if robinqueue is empty and there is process still in the process list
            if (robinQueeue.size() == 0 && currentProcess < processList.size()-1){
                robinQueeue.add(processList.get(currentProcess));
                currentProcess++;
                currentTime = robinQueeue.get(0).getArrival();
            }
            currentTime += changeInTimeFrame;
            iterationCheck++;
        }

        //print the queue see the gannt chart
        System.out.println();


        for (ProcessObj proc : printQueue){
            System.out.print("   P" + proc.getProcessNum()+ "    ");
        }
        System.out.println();
        currentTime = 0;

        System.out.print(0 + "   ");
        for (int i = 0; i < printQueue.size(); i++) {
            currentTime += printQueue.get(i).getExecutionTimeFrame();
            System.out.print(currentTime + "   ");
            if (i < printQueue.size() - 2 && printQueue.get(i + 1).getArrival() > currentTime) {
                currentTime = printQueue.get(i + 1).getArrival();
            }
        }
        System.out.println();
        System.out.println ("P#\t\tAT\t\tBT\t\tWT\t\tTA");

        for (int i = 0; i < numberOfProcess; i++){
            System.out.println ("P" + finalStat.get(i).getProcessNum() + "\t\t" + finalStat.get(i).getArrival() + "\t\t" +
                finalStat.get(i).getBurstTime() + "\t\t" + finalStat.get(i).getWaitingTime() + "\t\t" + (finalStat.get(i).getWaitingTime()+
                finalStat.get(i).getBurstTime()));
        }

        double totalWaiting = 0;
        double totalTurnAroundTime = 0;
        //getting average waiting time.
        for (Map.Entry<Integer, ProcessObj> entry : finalStat.entrySet()){
            totalWaiting += entry.getValue().getWaitingTime();
            totalTurnAroundTime += entry.getValue().getBurstTime() + entry.getValue().getWaitingTime();
        }
        double averageWaitingTime =(double) totalWaiting / numberOfProcess;
        double averageTurnAroundTime = (double) totalTurnAroundTime / numberOfProcess;

        System.out.println("Average waiting time: " + averageWaitingTime);
        System.out.println ("Average turnaround time: " + averageTurnAroundTime);
    }

}
