#include<iostream>
#include <unistd.h>
#include "Store.h"
using namespace std;



void runSimulationForStore(Store *store){
    
    while(store->isOpen()){
        if (store->hasNewCustomer()){
            
            store->addCustomerToLine();
            
        }
        
        store->moveCustomersFromQueueToServer();

        store->workOnOrders();
        
        store->removeCompletedOrders();

        store->updateQueueMetric();

        store->incrementTime();
        
    }
    store->printSummaryOfMetrics();
}


int main(){
    srand(time(NULL));
    Store *originalStore = new Store(1,1);
    cout << "\nOne Server One Queue Metrics: \n" << endl; 
    runSimulationForStore(originalStore);

    Store *twoServerTwoQueueStore = new Store(2,2);
    cout << "\nTwo Server Two Queues Metrics: \n" << endl;
    runSimulationForStore(twoServerTwoQueueStore);

    Store *twoServerOneQueueStore = new Store(2,1);
    cout << "\nTwo Server One Queue Metrics: \n" <<endl;
    runSimulationForStore(twoServerOneQueueStore);
}
