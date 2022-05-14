#ifndef QUEUE_H
#define QUEUE_H

class Customer{
    public:
        int arriveTime;
        int departTime;
        int orderTime;
        Customer *next;

        Customer();
};

class Queue{
    private:
        Customer *head;
    public:
        
        Queue();
        void enqueue();

        void dequeue();
};
#endif //QUEUE_H