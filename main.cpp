#include<iostream>
#include <unistd.h>
#include "Store.h"
using namespace std;

int main(){
    srand(time(NULL));
    Store *myStore = new Store(1,1);

    while(myStore->isOpen()){
        if (myStore->hasNewCustomer()){
            
            myStore->addCustomerToLine();
            
        }
        
        myStore->moveCustomersFromQueueToServer();

        myStore->workOnOrders();
        
        myStore->removeCompletedOrders();

        myStore->updateQueueMetric();

        myStore->incrementTime();
        
    }
    myStore->printSummaryOfMetrics();
    
}
