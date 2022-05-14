#include "Store.h"
#include "Queue.h"
#include <random>
#include <iostream>
using namespace std;
Store::Store(){
    storeTime = new StoreTime();
    storeLine = new Queue();
    storeMetrics = new StoreMetrics();
}

bool Store::isOpen(){
    return storeTime->isTimeValid();
}

void Store::updateQueueMetric(){
    int currentQueueLength = storeLine->length();
    int currentTime = storeTime->currentTime;

    TimeStampedValue queueLengthValue;
    queueLengthValue.value = currentQueueLength;
    queueLengthValue.time = currentTime;

    storeMetrics->queueLength->updateWithTimeStampedVal(queueLengthValue);
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
    cout << "\nCustomer Wait Time Metrics: \n\n" << storeMetrics->customerWaitTime->getSummary() << "\n\n\n";
    cout << "Customer Service Time Metrics: \n\n" << storeMetrics->customerServiceTime->getSummary() << "\n\n\n";
    cout << "Queue Length Metrics: \n\n" << storeMetrics->queueLength->getSummary() << "\n\n\n";
}

void Store::incrementTime(){
    storeLine->increaseCustomerWaitTimes();
    storeTime->increaseTime();
}

void Store::removeCompletedOrders(){
    Customer *orderInProgress = storeLine->getHead();
    if ((orderInProgress != NULL) && (orderInProgress->isOrderComplete())){
        Customer *completedOrder = storeLine->dequeue();
        updateCustomerMetrics(completedOrder);
        delete completedOrder;
    }
}

void Store::workOnOrder(){
    Customer *orderInProgress = storeLine->getHead();
    if (orderInProgress != NULL){
        orderInProgress->decreaseRemainingOrderTimeBy(1);
    }
}

void Store::addCustomerToLine(){
    
    storeLine->enqueue();

}

bool Store::hasNewCustomer(){
    
    int arrivalProbability = storeTime->getArrivalProbability();
    int randNum = rand() % 100 ;
    
    return randNum < arrivalProbability;
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


StoreMetrics::StoreMetrics(){
    customerWaitTime = new Metric();
    customerServiceTime = new Metric();
    queueLength = new Metric();
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
    maxString +=  " occured at time ";
    maxString += std::to_string(max.time);
    maxString += " minutes\n";

    std::string minString = "Min of ";
    minString += std::to_string(min.value);
    minString +=  " occured at time ";
    minString += std::to_string(min.time);
    minString += " minutes\n";

    std::string avgString = "Average value: ";
    avgString += std::to_string(getAverage());
    avgString += "\n";

    return avgString + minString + maxString;
}

