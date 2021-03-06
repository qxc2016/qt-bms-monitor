#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <ui_widget.h>
#include "displaythread.h"
#include "collectionthread.h"
#include "datapool.h"
#include "configure.h"
#include "parsethread.h"
#include "modbustcpserverthread.h"

namespace Ui {
    class Widget;
}

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    ~Widget();
    Ui::Widget *ui;
//    void setAlertItems(QMap<string, QTableWidgetItem*> alertItemMap);

private slots:
    void display();
    void log(QString str);
    void decreaseCluster();
    void increaseCluster();
    void lastPage();
    void nextPage();
    void onIndexChanged(const QString &);

protected:
    void changeEvent(QEvent *e);

private:
    DataPool* dataPool;
    Configure* configure;
    ParseThread *parseThread;
    DisplayThread *displayThread;
    CollectionThread *collectionThread;
    ModbusTCPServerThread *modbusTcpServerThread;

    void deserializeEvent();

//    void setAlertText(QTextBrowser* textBrowser, double value);
};

#endif // WIDGET_H
