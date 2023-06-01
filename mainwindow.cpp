#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QHostAddress"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->m_tcp = new QTcpSocket(this);


    connect(m_tcp, &QTcpSocket::stateChanged, this, [=](){
       ui->info->append("m_tcp state:  " + QString(m_tcp->state()));
    });

    connect(m_tcp, &QTcpSocket::readyRead,this,[=](){
        QByteArray data =  m_tcp->readAll();
        ui->info->append("接受："+data);
    });

    connect(m_tcp, &QTcpSocket::disconnected, this, [=]{
        m_tcp->close();
        ui->connect->setEnabled(true);
        ui->disconnect->setEnabled(false);
        ui->send->setEnabled(false);
        ui->info->append("断开服务器连接！");
    });
    connect(m_tcp, &QTcpSocket::connected, this, [=]{
        ui->info->append("连接服务器成功！");
        ui->connect->setEnabled(false);
        ui->disconnect->setEnabled(true);
        ui->send->setEnabled(true);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_connect_clicked()
{
    if(not m_tcp){
        m_tcp =  new QTcpSocket(this);
        ui->info->append("创建新的m_tcp 对象");

    }
    QString ip = ui->ip->text();
    unsigned short port = ui->port->text().toUShort();
    ui->info->append("connect info:" + ip +  ": " +ui->port->text());
    m_tcp->connectToHost(QHostAddress("192.168.3.54"),4999);
}

void MainWindow::on_disconnect_clicked()
{
    m_tcp->close();
}

void MainWindow::on_send_clicked()
{
    QString msg = ui->msg->text();
    m_tcp->write(msg.toUtf8());
    ui->info->append("send info:"+msg);
}
