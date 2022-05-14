#include "Store.h"
#include "Queue.h"
Store::Store(){
    storeTime = new StoreTime();
    storeLine = new Queue();
}

bool Store::isOpen(){
    return storeTime->isTimeValid();
}

void Store::prepareForNextMinute(){
    storeTime->increaseTime();
}
void Store::removeCompletedOrders(){
    //TODO - remove order with time remaining = 0
}

void Store::workOnOrder(){
    //TODO - work on order if available
}

void Store::addCustomerToLine(){
    //TODO - enqueue a new customer
}

bool Store::hasNewCustomer(){
    //TODO - use probabilities to determine if a new customer has arrived
    return true;
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