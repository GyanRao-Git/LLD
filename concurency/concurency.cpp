#include<iostream>
#include<vector>
#include<string>
using namespace std;

/*
    Atomics: 
        - For single variables only
        - Use atomics for counters, flags, and simple statistics.
        - Under the hood, they use CPU instructions like compare-and-swap (CAS) that complete in one uninterruptible step.
*/
#include <atomic>
atomic<int> counter(0);
// counter ++; Thread safe

//------------------------------------------------------

/*  
    Locks (Mutexes)
        - Lock a critical section so only one thread can enter at a time
        

*/
#include <mutex>

mutex mtx;
vector<string> names;
int main()
{
    {
        lock_guard<mutex> lock(mtx);
        names.push_back("Gyan");

        // lock is released after scope runs out 
        // or explicitely use unique_lock<mutex>lock and call lock.unlock()
    }
};

//-----------------------------------------------------------------

/*
    Semaphore - Some n number of threads allowed

*/
#include <semaphore>
// counting_semaphore<5> permits(5);
// permits.aquire();
// try{
//     //do work
// }
// catch{
//     permits.release();
//     throw;
// }

// counting_semaphore only available cpp 20 onwards


//-----------------------------------------------------------------
/*
    Conditional Variables
    A condition variable lets a thread sleep until some condition becomes true.

*/
#include <mutex>
#include<condition_variable>

mutex mx;
condition_variable cv;
bool ready = false;

bool waitForReady(){
    unique_lock<mutex>lock(mx);

    // takes a lock and a lambda, lambda checks for condition
    cv.wait(lock, []{
        return ready; //condition
    });
    return ready;
} 

bool makeReady(){
    unique_lock<mutex> lock;
    ready = true;
    cv.notify_one(); // notify that ready is true
}

// usage 
#include <thread>
int main(){
    thread t1(waitForReady);
    thread t2(makeReady);
    t1.join();
    t2.join();
}

//-----------------------------------------------------------------
