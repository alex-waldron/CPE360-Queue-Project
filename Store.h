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
    private:
        int queueCount;
        int serverCount;
    public:
        Metric *customerWaitTime;
        Metric *customerServiceTime;
        Metric *queueLengths[10];
        StoreMetrics(int numQueues);
};

class Server{
    public:
        Customer *customerBeingServed;
        Server();
        bool hasCustomer();
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
        int serverCount;
        int queueCount;
        
        
    public:
        Queue *storeLines[10];
        Server *servers[10];
        StoreMetrics *storeMetrics;
        Store(int numServer, int numQueues);
        bool isOpen();
        void incrementTime();
        void removeCompletedOrders();
        bool hasNewCustomer();
        void addCustomerToLine();
        void workOnOrders();
        void updateQueueMetric();
        void updateCustomerMetrics(Customer *customer);
        void printSummaryOfMetrics();
        void moveCustomersFromQueueToServer();
};



#endif // STORE_H