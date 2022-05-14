#include<iostream>

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

        myStore->prepareForNextMinute();
        
    }
    
}

// const int TEN_AM = 120;
//const int ELEVEN_AM = 210; //1130am
    //     if(TIME <= TEN_AM ){
    //         //8 am through 10 am
    //         randNum = rand() % 100 ;
    //         if(randNum < 30){
    //             cout << "At time: " << storeClock << " we have 1 new customer" << endl;
    //             customerCount++;
    //             queue_length++;
    //             myStore.enqueue();
    //         }
    //         else{
    //             cout << "At time: " << storeClock << " no new customer arrived " << endl;
    //         }

    //     }
    //     //brunch time customers
    //     else if(storeClock > TEN_AM && storeClock <= ELEVEN_AM){
    //         random_number = rand()%100 + 1;
    //         if(random_number <= 10){
    //             cout << "At time: " << storeClock << " we have 1 new customer" << endl;
    //             customerCount++;
    //             queue_length++;
    //             myStore.enqueue();
    //         }
    //         else{
    //             cout << "At time " << storeClock << " no new customer arrived" << endl;
    //         }
    //     }
    // }
    //     //2. is the customer going to place an order at this minute
    //     int orderTime = rand() % 6;
    //     //3. is a customer ready to depart the store at this minute?
    // if(myStore.head != NULL){
    //     if(myStore.head->orderTime == 0){
    //         cout << "Customer departing" << endl;
    //         myStore.dequeue();
    //     }
    //     else
    //         myStore.head->orderTime--;
    // }


// int main(){
//     Store *myStore = new Store();
    
//     while(myStore->isOpen()){
        
//         myStore->prepareForNextMinute();
//     }
// }
