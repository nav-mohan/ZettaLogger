#if !defined(MAINWINDOW_H)
#define MAINWINDOW_H

#include <QDebug>
#include <QDateTime>
#include <QMainWindow>

#include "zettalistenerconnection.h"
#include "databaseconnection.h"
#include "httpserver.h"

namespace Ui {class MainWindow;}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_pushButton_clearLogs_clicked();
    void on_pushButton_connectDatabase_clicked();
    void on_pushButton_connectZettaListener_clicked();
    void on_comboBox_connectionType_currentIndexChanged(int);
    void on_pushButton_startWebApi_clicked();
    void readSocket();
    void deleteSocket();
    void displayMessage(QString windowTitle, QString windowInfo);
    void zettaListenerConnectionChanged(bool,int);
    void databaseConnectionChanged(bool);

#ifdef IS_TESTING
public:
#else
private:
#endif
    Ui::MainWindow *m_ui;
    DatabaseConnection *m_databaseConnection;
    ZettaListenerConnection *m_zettaListenerConnection;
    HttpServer *m_httpServer;
    bool m_zettaListenerConnectionStatus;
    int m_zettaListernConnectionType;
    bool m_databaseConnectionStatus;
};

#endif // MAINWINDOW_H
