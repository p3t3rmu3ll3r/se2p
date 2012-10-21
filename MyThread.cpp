#include "MyThread.h"
#include <iostream>
#include <unistd.h>

#include "HAL/HAL.h"

using namespace std;


namespace thread {

MyThread::MyThread() {
    // TODO Auto-generated constructor stub

}

MyThread::~MyThread() {
    // TODO Auto-generated destructor stub
}

void MyThread::shutdown() {
    cout << "Shutting down..." << endl;
}

void MyThread::execute(void *arg) {
    while(!isStopped()) {
    	HAL* hal = HAL::getInstance();
        cout << "Ich bin ein Thread." << endl;
        sleep(1);
        hal->lightGreen(true);
        sleep(1);
        hal->lightGreen(false);
    }
}

}
