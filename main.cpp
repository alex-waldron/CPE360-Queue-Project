#include<iostream>
#include <unistd.h>
#include "Store.h"
using namespace std;

int main(){
    srand(time(NULL));
    Store *myStore = new Store();

    while(myStore->isOpen()){
        if (myStore->hasNewCustomer()){
            
            myStore->addCustomerToLine();
            
        }

        myStore->workOnOrder();
        
        myStore->removeCompletedOrders();
        
        myStore->updateQueueMetric();

        myStore->incrementTime();
        
    }
    myStore->printSummaryOfMetrics();
    
}
