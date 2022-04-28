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

        }    
        void enqueue(int arriveTime, int orderTime){

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

        
        if(TIME <= TEN_AM ){
            //8 am through 10 am
            randNum = rand() % 100 ;
            if(randNum < 30){

            }
        }
        //2. is the customer going to place an order at this minute
        int orderTime = rand() % 6;
        //3. is a customer ready to depart the store at this minute? 
    }
}