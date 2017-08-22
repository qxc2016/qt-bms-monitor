#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <sys/ioctl.h>
#include <net/if.h>
#include "ui_widget.h"

class DisplayThread : public QThread
{
    Q_OBJECT
public:
    explicit DisplayThread(QObject *parent = 0);
    
signals:
    void display();

public slots:
    void run();
    void stop();

private:
    bool running;
};

#endif // THREAD_H