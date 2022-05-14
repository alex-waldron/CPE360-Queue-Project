#ifndef STORE_H
#define STORE_H
#include "Queue.h"

class StoreTime{
    
    private:
        int currentTime;
        int OPEN_MINUTES;
    public:
        void increaseTime();
        StoreTime();
        bool isTimeValid();

};

class Store{
    private:
        StoreTime *storeTime;
        Queue *storeLine;
    public:
        Store();
        bool isOpen();
        void prepareForNextMinute();
        void removeCompletedOrders();
        bool hasNewCustomer();
        void addCustomerToLine();
        void workOnOrder();
};



#endif // STORE_H