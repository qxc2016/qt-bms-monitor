#include "displaythread.h"

DisplayThread::DisplayThread(QObject *parent) :
    QThread(parent)
{
    running = true;
}

void DisplayThread::run()
{


    while(running)
    {
        display();
        this->sleep(1);
    }

}

void DisplayThread::stop()
{
    running = false;
}