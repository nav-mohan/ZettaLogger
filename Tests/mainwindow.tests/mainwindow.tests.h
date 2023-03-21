#if !defined(MAINWINDOW_TESTS_H)
#define MAINWINDOW_TESTS_H

#include "mainwindow.h"
#include <QObject>
#include <QTest>
#include <QString>
#include <QComboBox>
#include <QPushButton>
#include <QListWidget>
#include <QApplication>
#include <QLineEdit>
#include <QPlainTextEdit>

class TestMainWindow : public QObject {
Q_OBJECT

public:
    TestMainWindow(QObject *parent = nullptr){}

private:
    MainWindow *m_win;
    QPushButton *m_clearLogs;
    QPlainTextEdit *m_receivedLogs;
    QLineEdit *m_databaseUrl, *m_databaseName, *m_databaseUsername, *m_databasePassword;
    QPushButton *m_connectToDatabase;
    QComboBox *m_zettaListenerConnectionOptions;
    QLineEdit *m_tcpServerPort, *m_sharedMemoryKey;
    QPushButton *m_connectToZettaListener;
    ZettaListenerConnection *m_zettaListenerConnection = nullptr;
    DatabaseConnection *m_databaseConnection = nullptr;
    bool m_zettaListenerConnectionStatus;
    int m_zettaListernConnectionType;
    bool m_databaseConnectionStatus;

private slots:
    void initTestCase()
    {
        m_win = new MainWindow();
        m_clearLogs = m_win->findChild<QPushButton*>("pushButton_clearLogs");
        m_receivedLogs = m_win->findChild<QPlainTextEdit*>("plainTextEdit_receivedLogs");
        m_databaseUrl = m_win->findChild<QLineEdit*>("databaseUrlValue");
        m_databaseName = m_win->findChild<QLineEdit*>("databaseNameValue");
        m_databaseUsername = m_win->findChild<QLineEdit*>("databaseUsernameValue");
        m_databasePassword = m_win->findChild<QLineEdit*>("databasePasswordValue");
        m_connectToDatabase = m_win->findChild<QPushButton*>("pushButton_connectDatabase");
        m_zettaListenerConnectionOptions = m_win->findChild<QComboBox*>("comboBox_connectionType");
        m_tcpServerPort = m_win->findChild<QLineEdit*>("portNumberValue");
        m_sharedMemoryKey = m_win->findChild<QLineEdit*>("sharedMemoryKeyValue");
        m_connectToZettaListener = m_win->findChild<QPushButton*>("pushButton_connectZettaListener");
        m_zettaListenerConnection = m_win->m_zettaListenerConnection;
        m_databaseConnection = m_win->m_databaseConnection;
        m_zettaListenerConnectionStatus = m_win->m_zettaListenerConnectionStatus;
        m_zettaListernConnectionType = m_win->m_zettaListernConnectionType;
        m_databaseConnectionStatus = m_win->m_databaseConnectionStatus;
    }

    void verify_windowTitle_value()
    {
        QString windowTitle = m_win->property("windowTitle").toString();
        QCOMPARE(windowTitle, "QZettaLogger");
    }

    void verify_window_initialized()
    {
        QCOMPARE(m_receivedLogs->toPlainText(),"");
        QCOMPARE(m_receivedLogs->placeholderText(),"Received Logs:\n");
        QCOMPARE(m_databaseUrl->text(),"");
        QCOMPARE(m_databaseName->text(),"");
        QCOMPARE(m_databaseUsername->text(),"");
        QCOMPARE(m_databasePassword->text(),"");
        QCOMPARE(m_tcpServerPort->text(),"");
        QCOMPARE(m_tcpServerPort->placeholderText(),"");
        QCOMPARE(m_sharedMemoryKey->text(),"");
        QCOMPARE(m_sharedMemoryKey->placeholderText(),"N/A");
        QCOMPARE(m_zettaListenerConnectionOptions->placeholderText(),"ZettaListener Connection Type");
        QCOMPARE(m_zettaListenerConnectionOptions->count(),2);
    }

    void verify_pushButton_clearLogs()
    {
        m_receivedLogs->insertPlainText("RECEIVED LOGS");
        QCOMPARE(m_receivedLogs->toPlainText(),"RECEIVED LOGS");
        m_clearLogs->click();
        QCOMPARE(m_receivedLogs->toPlainText(),"");
    }
    
};

#endif // MAINWINDOW_TESTS_H
