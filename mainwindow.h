#include <QDebug>
#include <QDateTime>
#include <QMainWindow>

#include "zettalistenerconnection.h"
#include "databaseconnection.h"

namespace Ui {class MainWindow;}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_connectDatabase_clicked();
    void on_pushButton_connectZettaListener_clicked();
    void readSocket();
    void deleteSocket();
    void setMessageQueueKey(int);

private:
    Ui::MainWindow *m_ui;
    DatabaseConnection *m_databaseConnection;
    ZettaListenerConnection *m_zettaListenerConnection;
};