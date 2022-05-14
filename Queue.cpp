#include "Queue.h"
#include <random>
#include <iostream>
using namespace std;
Customer::Customer(){
    waitTime = 0;
    orderTime = rand()%6 + 1;
    remainingOrderTime = orderTime;
    next = NULL;
}

void Customer::increaseWaitTimeBy(int seconds){
    waitTime += 1;
}

void Customer::decreaseRemainingOrderTimeBy(int seconds){
    remainingOrderTime -= seconds;
}

bool Customer::isOrderComplete(){
    return remainingOrderTime <= 0;
}

Queue::Queue(){
    head = NULL;
}

void Queue::enqueue(){
    Customer *temp = new Customer();

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

void Queue::increaseCustomerWaitTimes(){
    Customer *tmp = head;
    while (tmp != NULL) {
        tmp->increaseWaitTimeBy(1);
        tmp = tmp->next;
    }
}

Customer *Queue::getHead(){
    return head;
}

int Queue::length(){
    
    Customer *tmp = head;
    int counter = 0;
    while (tmp != NULL){
        tmp = tmp->next;
        counter++;
    }
    return counter;
}

Customer *Queue::dequeue(){
        if (head == NULL) {
            return NULL;
        } else {
            Customer *temp;
            temp = head; //grab the addr of the first customer -- we want to delete this
            head = head->next; //head moves to the next customer
            return temp;
        }

    }