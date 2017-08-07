package Model;

public class ProcessObj{

    private int burstTime;
    private double arrival;
    private int priority;
    private int processNum;
    private double executionTime;
    private double waitingTime;
    private double lastExecuted;
    private double executionTimeFrame;
    private int remainingBurstTime;

    public double getWaitingTime() {
        return waitingTime;
    }

    public void setWaitingTime(double waitingTime) {
        this.waitingTime = waitingTime;
    }

    public ProcessObj(int processNum, double arrival, int burstTime){
        this.processNum= processNum;
        this.arrival = arrival;
        this.burstTime = burstTime;
    }

    public ProcessObj(int processNum, double arrival, int burstTime, int priority){
        this.processNum = processNum;
        this.arrival = arrival;
        this.burstTime = burstTime;
        this.priority = priority;
    }

    public ProcessObj(ProcessObj obj){
        this.burstTime = obj.getBurstTime();
        this.arrival = obj.getArrival();
        this.priority = obj.getPriority();
        this.processNum = obj.getProcessNum();
        this.executionTime = obj.getExecutionTime();
        this.waitingTime = obj.getWaitingTime();
        this.lastExecuted = obj.getLastExecuted();
        this.executionTimeFrame = obj.getExecutionTimeFrame();
        this.remainingBurstTime = obj.getRemainingBurstTime();
    }

    public ProcessObj(){
        lastExecuted = -1;
    }

    public int getBurstTime() {
        return burstTime;
    }

    public void setBurstTime(int burstTime) {
        this.burstTime = burstTime;
    }

    public double getArrival() {
        return arrival;
    }

    public void setArrival(double arrival) {
        this.arrival = arrival;
    }

    public int getPriority() {
        return priority;
    }

    public void setPriority(int priority) {
        this.priority = priority;
    }

    public int getProcessNum() {
        return processNum;
    }

    public void setProcessNum(int processNum) {
        this.processNum = processNum;
    }

    public double getExecutionTime() {
        return executionTime;
    }

    public void setExecutionTime(double executionTime) {
        this.executionTime = executionTime;
    }

    public double getLastExecuted() {
        return lastExecuted;
    }

    public void setLastExecuted(double lastExecuted) {
        this.lastExecuted = lastExecuted;
    }

    public double getExecutionTimeFrame() {
        return executionTimeFrame;
    }

    public void setExecutionTimeFrame(double executionTimeFrame) {
        this.executionTimeFrame = executionTimeFrame;
    }

    public int getRemainingBurstTime() {
        return remainingBurstTime;
    }

    public void setRemainingBurstTime(int remainingBurstTime) {
        this.remainingBurstTime = remainingBurstTime;
    }
}