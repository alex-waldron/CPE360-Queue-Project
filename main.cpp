#include<iostream>
#include<random>

using namespace std;


class Customer{
    public:
        int arriveTime;
        int departTime;
        int orderTime;
};

class Queue{
    public:
        Customer *head;
        Queue(){
            head = NULL;

        }    
        void enqueue(int arriveTime, int orderTime){
            Customer *temp = new Customer();
            //code for enqueue, add this customer to Queue
            cout << "Just added a new customer to line: "<< temp->inTime << " and order: " << temp->orderTime << endl;

            if(head == NULL){
                head = temp;
            }
            else{
                Customer *another;
                another = head; //start at the beginning
                while(another->next != NULL){
                    another = another->next;
                }
                //when we are at the end, we want to make this new chunk(temp0 the last one
                another->next = temp;
                temp->next = NULL;
            }
        }

    void dequeue() {
        if (head == NULL) {
            cout << "Empty queue, nothing to delete" << endl;
        } else {
            Customer *temp;
            temp = head; //grab the addr of the first custpmer -- we want to delete this
            head = head->next; //head moves to the next customer
            cout << "At this time: " << storeClock << " we have a departing customer" << endl;
            delete temp;
        }

        int queSize() {
            return 1;

        }
    }
};


int main(){
    int TIME = 0;
    int guess,randNum, count = 0;
    const int OPEN_MINUTES = 1020;
    const int TEN_AM = 120;
    srand(time(NULL));

    while(TIME < OPEN_MINUTES){
        //1 - should we add a new customer
        storeClock++;

        if(TIME <= TEN_AM ){
            //8 am through 10 am
            randNum = rand() % 100 ;
            if(randNum < 30){
                cout << "At time: " << storeClock << " we have 1 new customer" << endl;
                customerCount++;
                queue_length++;
                myStore.enqueue();
            }
            else{
                cout << "At time: " << storeClock << " no new customer arrived " << endl;
            }

        }
    }
        //2. is the customer going to place an order at this minute
        int orderTime = rand() % 6;
        //3. is a customer ready to depart the store at this minute?
    if(myStore.head != NULL){
        if(myStore.head->orderTime == 0){
            cout << "Customer departing" << endl;
            myStore.dequeue();
        }
        else
            myStore.head->orderTime--;
    }
}
