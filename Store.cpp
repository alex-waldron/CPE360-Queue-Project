#include "Store.h"
#include "Queue.h"
#include <random>
#include <iostream>
using namespace std;
Store::Store(int numServers, int numQueues){
    
    storeTime = new StoreTime();

    serverCount = numServers;
    for(int i = 0; i < numServers; i++){
        servers[i] = new Server();
    }
    queueCount = numQueues;
    for(int i = 0; i < numQueues ; i++){
        storeLines[i] = new Queue();
    }
    
    storeMetrics = new StoreMetrics(numQueues);
}

bool Store::isOpen(){
    return storeTime->isTimeValid();
}

void Store::updateQueueMetric(){
    for (int i = 0; i < queueCount; i++){
        Queue *storeLine = storeLines[i];
        int currentQueueLength = storeLine->length();
        int currentTime = storeTime->currentTime;

        TimeStampedValue queueLengthValue;
        queueLengthValue.value = currentQueueLength;
        queueLengthValue.time = currentTime;
        Metric *queueLengthMetric = storeMetrics->queueLengths[i];
        queueLengthMetric->updateWithTimeStampedVal(queueLengthValue);
    }
}

void Store::updateCustomerMetrics(Customer *customer){
    int waitTime = customer->waitTime;
    int serviceTime = customer->orderTime + waitTime;
    int currentTime = storeTime->currentTime;

    TimeStampedValue timeStampedServiceTime;
    timeStampedServiceTime.value = serviceTime;
    timeStampedServiceTime.time = currentTime;

    storeMetrics->customerServiceTime->updateWithTimeStampedVal(timeStampedServiceTime);


    TimeStampedValue timeStampedWaitTime;
    timeStampedWaitTime.value = waitTime;
    timeStampedWaitTime.time = currentTime;

    storeMetrics->customerWaitTime->updateWithTimeStampedVal(timeStampedWaitTime);

}

void Store::printSummaryOfMetrics(){
    cout << "\nCustomer Wait Time Metrics: \n\n" << storeMetrics->customerWaitTime->getSummary() << "\n\n";
    cout << "Customer Service Time Metrics: \n\n" << storeMetrics->customerServiceTime->getSummary() << "\n\n";
    for(int i = 0 ; i < queueCount; i++){
        cout << "Queue " << i <<" Length Metrics: \n\n" << storeMetrics->queueLengths[i]->getSummary() << "\n\n";
    }
    
}

void Store::incrementTime(){
    for(int i = 0; i < queueCount; i++){
        Queue *storeLine = storeLines[i];
        storeLine->increaseCustomerWaitTimes();
    }
    storeTime->increaseTime();
}

void Store::removeCompletedOrders(){
    for (int i = 0; i < serverCount; i++){
        Server *server = servers[i];
        Customer *orderInProgress = server->customerBeingServed;
        if ((orderInProgress != NULL) && (orderInProgress->isOrderComplete())){
            
            updateCustomerMetrics(orderInProgress);
            server->customerBeingServed = NULL;
            delete orderInProgress;
        }
    }
}

void Store::workOnOrders(){
    for(int i = 0; i < serverCount; i++){
        Server *currentServer = servers[i];
        if (currentServer->hasCustomer()){
            currentServer->customerBeingServed->decreaseRemainingOrderTimeBy(1);
        }
    }
}

void Store::addCustomerToLine(){
    Queue *shortestQueue = NULL;
    for (int i = 0; i < queueCount; i++){
        Queue *queue = storeLines[i];
        if (shortestQueue == NULL){
            shortestQueue = queue;
        }else{
            shortestQueue = shortestQueue->length() < queue->length() ? shortestQueue : queue;

        }
    }
    shortestQueue->enqueue();

}

bool Store::hasNewCustomer(){
    
    int arrivalProbability = storeTime->getArrivalProbability();
    int randNum = rand() % 100 ;
    
    return randNum < arrivalProbability;
}

void Store::moveCustomersFromQueueToServer(){
    // TODO - move from the queues to the server
    if (queueCount == serverCount){
        //for each index i, queue[i] must go to server[i]
        for(int i = 0; i < queueCount; i++){
            Queue *queue = storeLines[i];
            Server *server = servers[i];
            if (!server->hasCustomer()){
                server->customerBeingServed = queue->dequeue();
            }
        }
    } else{
        //each queue can move to any server
        for(int i=0; i < queueCount; i++){
            Queue *queue = storeLines[i];
            if (!queue->isEmpty()){
                for(int j = 0; j < serverCount; j++){
                    Server *server = servers[j];
                    if (!server->hasCustomer()){
                        server->customerBeingServed = queue->dequeue();
                        
                    }
                }
            }
        }
    }
}

int StoreTime::getArrivalProbability(){
    const int TEN_AM = 120;
    const int ELEVEN_THIRTY_AM = 210; 
    const int ONE_THIRTY_PM = 330;
    const int FIVE_THIRTY_PM = 570;
    const int EIGHT_PM = 720;
    const int ELEVEN_PM = 900;
    const int ONE_AM = 1020;
    
    const int NUM_TIMES = 7;
    int endTimes[] = {TEN_AM, ELEVEN_THIRTY_AM, ONE_THIRTY_PM, FIVE_THIRTY_PM, EIGHT_PM, ELEVEN_PM, ONE_AM};
    int arrivalProbabilities[] = {30,10,40,10,25,20,10};
    for(int i = 0; i < NUM_TIMES; i++){
        int endTime = endTimes[i];
        int arrivalProbability = arrivalProbabilities[i];
        if (currentTime <= endTime){
            return arrivalProbability;
        }
    }
    return 0;
}


StoreTime::StoreTime(){
    OPEN_MINUTES = 1020;
    currentTime = 0;
}

void StoreTime::increaseTime(){
    currentTime++;
    
}

bool StoreTime::isTimeValid(){
    return currentTime < OPEN_MINUTES;
}


StoreMetrics::StoreMetrics(int numQueues){
    customerWaitTime = new Metric();
    customerServiceTime = new Metric();

    for (int i = 0; i < numQueues; i++){
        queueLengths[i] = new Metric();
    }
    
}

Metric::Metric(){
    max.value = INT32_MIN;
    max.time = 0;

    min.value = INT32_MAX;
    min.time = 0;

    total = 0;
    numSamples = 0;

}

double Metric::getAverage(){
    return (double) total / (double) numSamples;
}

void Metric::updateWithTimeStampedVal(TimeStampedValue timeVal){
    numSamples++;
    total += timeVal.value;
    max = timeVal.value > max.value ? timeVal : max;
    min = timeVal.value <= min.value ? timeVal : min;
}

std::string Metric::getSummary(){
    std::string maxString = "Max of ";
    maxString += std::to_string(max.value);
    maxString +=  " occurred at time ";
    maxString += std::to_string(max.time);
    maxString += " minutes\n";

    std::string minString = "Min of ";
    minString += std::to_string(min.value);
    minString +=  " occurred at time ";
    minString += std::to_string(min.time);
    minString += " minutes\n";

    std::string avgString = "Average value: ";
    avgString += std::to_string(getAverage());
    avgString += "\n";

    return avgString + minString + maxString;
}

Server::Server(){
    customerBeingServed = NULL;
}
bool Server::hasCustomer(){
    return customerBeingServed != NULL;
}