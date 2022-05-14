#ifndef STORE_H
#define STORE_H
#include "Queue.h"
#include <iostream>

struct TimeStampedValue{
    int time;
    int value;
};

class Metric{
    public:
        TimeStampedValue max;
        TimeStampedValue min;
        int total;
        int numSamples;
        Metric();
        double getAverage();
        void updateWithTimeStampedVal(TimeStampedValue timeVal);
        std::string getSummary();
};

class StoreMetrics{
    public:
        Metric *customerWaitTime;
        Metric *customerServiceTime;
        Metric *queueLength;
        StoreMetrics();
};

class StoreTime{
    
    private:
        
        int OPEN_MINUTES;
        
    public:
        int currentTime;
        void increaseTime();
        int getArrivalProbability();
        StoreTime();
        bool isTimeValid();

};

class Store{
    private:
        StoreTime *storeTime;
        
        
        
    public:
        Queue *storeLine;
        StoreMetrics *storeMetrics;
        Store();
        bool isOpen();
        void incrementTime();
        void removeCompletedOrders();
        bool hasNewCustomer();
        void addCustomerToLine();
        void workOnOrder();
        void updateQueueMetric();
        void updateCustomerMetrics(Customer *customer);
        void printSummaryOfMetrics();
};



#endif // STORE_H