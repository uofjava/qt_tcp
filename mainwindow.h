#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTcpSocket *m_tcp;

private slots:
    void on_connect_clicked();

    void on_disconnect_clicked();

    void on_send_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
