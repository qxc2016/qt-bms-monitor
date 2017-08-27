#include "widget.h"
#include <ctime>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);
    log(QString::fromStdString("application start..."));
    log(QString::fromStdString("init data pool..."));
    dataPool = DataPool::newInstance();
    connect(dataPool,SIGNAL(log(QString)),this,SLOT(log(QString)));

    configure = Configure::newInstance();

    // start the display thread.
    log(QString::fromStdString("start display thread..."));
    displayThread = new DisplayThread();
    connect(displayThread,SIGNAL(display()),this,SLOT(display()));
    displayThread->start();

    log(QString::fromStdString("start collection thread..."));
    collectionThread = new CollectionThread();
    connect(collectionThread,SIGNAL(log(QString)),this,SLOT(log(QString)));
    collectionThread->start();

    connect(ui->pbutton_left,SIGNAL(clicked()),this,SLOT(decreaseCluster()));
    connect(ui->pbutton_right,SIGNAL(clicked()),this,SLOT(increaseCluster()));

    configure->setClusterId(1);
}


Widget::~Widget()
{
    delete ui;
    if(displayThread)
    {
        displayThread->stop();
        displayThread->deleteLater();
    }
    if(collectionThread)
    {
        collectionThread->stop();
        collectionThread->deleteLater();
    }
}

void Widget::decreaseCluster()
{
    int currentNum = ui->label_cluster->text().toInt();
    log(QString::fromStdString("current num is ").append(QString::number(currentNum)).append(QString::fromStdString("cluster number is ")).append(QString::number(configure->getClusterNum())));
    if (currentNum > 1){        
        ui->label_cluster->setText(QString::number(currentNum - 1));
        configure->setClusterId(currentNum - 1);
    }else{
        ui->label_cluster->setText(QString::number(configure->getClusterNum()));
        configure->setClusterId(configure->getClusterNum());
    }
    this->display();
}

void Widget::increaseCluster()
{
    int currentNum = ui->label_cluster->text().toInt();
    if (currentNum < configure->getClusterNum()){
        ui->label_cluster->setText(QString::number(currentNum + 1));
        configure->setClusterId(currentNum + 1);
    }else{
        ui->label_cluster->setText(QString::number(1));
        configure->setClusterId(1);
    }
    this->display();
}

void Widget::display()
{
    // page 1
    ui->lcd_soc->display(dataPool->getDouble("soc"));
    ui->lcd_zdl->display(dataPool->getDouble("zdl"));
    ui->lcd_zdwc->display(dataPool->getDouble("zdwc"));
    ui->lcd_zdy->display(dataPool->getDouble("zdy"));
    ui->lcd_zdyc->display(dataPool->getDouble("zdyc"));
    ui->pBar_soc->setValue(dataPool->getDouble("soc"));

    // page 2
    int current_cluster_id = configure->getClusterId();
    ui->lcd_p2_cdcs->display(dataPool->getDouble(current_cluster_id, "mkcdcs"));
    ui->lcd_p2_dczt->display(dataPool->getDouble(current_cluster_id, "dczt"));
    ui->lcd_p2_dl->display(dataPool->getDouble(current_cluster_id, "mkzdl"));
    ui->lcd_p2_gl->display(dataPool->getDouble(current_cluster_id, "mkzdl"));
    ui->lcd_p2_zgwd->display(dataPool->getDouble(current_cluster_id, "mknzgwd"));
    ui->lcd_p2_zdwd->display(dataPool->getDouble(current_cluster_id, "mknzdwd"));
}
void Widget::log(QString str)
{
    ui->text_log->append(str);
}

void Widget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
