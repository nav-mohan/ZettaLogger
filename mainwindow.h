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

public slots:
    void on_pushButton_connectDatabase_clicked();
    void on_pushButton_connectZettaListener_clicked();
    void on_comboBox_connectionType_currentIndexChanged(int);
    void readSocket();
    void deleteSocket();
    void setMessageQueueKey(int);
    void displayMessage(QString windowTitle, QString windowInfo);
    void zettaListenerConnectionChanged(bool,int);
    void databaseConnectionChanged(bool);


private:
    Ui::MainWindow *m_ui;
    DatabaseConnection *m_databaseConnection;
    ZettaListenerConnection *m_zettaListenerConnection;
    bool m_zettaListenerConnectionStatus;
    int m_zettaListernConnectionType;
    bool m_databaseConnectionStatus;
};