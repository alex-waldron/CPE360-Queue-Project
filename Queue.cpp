#include "Queue.h"
#include <random>
#include <iostream>
using namespace std;
Customer::Customer(){
    //arriveTime = storeClock;
    departTime = 0;
    //waitTime = 0;
    orderTime = rand()%6 + 1;
    next = NULL;
}


Queue::Queue(){
    head = NULL;
}

void Queue::enqueue(){
    Customer *temp = new Customer();
    //code for enqueue, add this customer to Queue
    //cout << "Just added a new customer to line: "<< temp->inTime << " and order: " << temp->orderTime << endl;

    if(head == NULL){
        head = temp;
    }
    else{
        Customer *another;
        another = head; //start at the beginning
        while(another->next != NULL){
            another = another->next;
        }
        //when we are at the end, we want to make this new chunk(temp) the last one
        another->next = temp;
        temp->next = NULL;
    }
}

void Queue::dequeue(){
        if (head == NULL) {
            cout << "Empty queue, nothing to delete" << endl;
        } else {
            Customer *temp;
            temp = head; //grab the addr of the first custpmer -- we want to delete this
            head = head->next; //head moves to the next customer
            //cout << "At this time: " << storeClock << " we have a departing customer" << endl;
            delete temp;
        }

    }