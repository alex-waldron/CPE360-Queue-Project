#ifndef QUEUE_H
#define QUEUE_H

class Customer{
    public:
        int waitTime;
        int orderTime;
        int remainingOrderTime;
        Customer *next;
        void decreaseRemainingOrderTimeBy(int seconds);
        void increaseWaitTimeBy(int seconds);
        bool isOrderComplete();
        Customer();
};

class Queue{
    private:
        Customer *head;
    public:
        
        Queue();
        void enqueue();
        int length();
        Customer *dequeue();
        Customer *getHead();
        void increaseCustomerWaitTimes();
};
#endif //QUEUE_H