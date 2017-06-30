/********************************************************************************
** Form generated from reading UI file 'scannerqt.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCANNERQT_H
#define UI_SCANNERQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScannerQt
{
public:
    QWidget *centralWidget;
    QListWidget *listWidget;
    QLabel *label;
    QProgressBar *progressBar;
    QLabel *label_2;
    QPlainTextEdit *plainTextEdit;
    QLabel *label_3;
    QPushButton *load_sigs;
    QPushButton *scan_files;
    QPushButton *scan_data;
    QPushButton *stop_scan;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ScannerQt)
    {
        if (ScannerQt->objectName().isEmpty())
            ScannerQt->setObjectName(QStringLiteral("ScannerQt"));
        ScannerQt->resize(801, 586);
        centralWidget = new QWidget(ScannerQt);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(0, 180, 801, 361));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 160, 81, 16));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(0, 130, 801, 31));
        progressBar->setValue(24);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 110, 81, 16));
        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(0, 80, 801, 31));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 60, 111, 16));
        load_sigs = new QPushButton(centralWidget);
        load_sigs->setObjectName(QStringLiteral("load_sigs"));
        load_sigs->setGeometry(QRect(10, 10, 131, 41));
        scan_files = new QPushButton(centralWidget);
        scan_files->setObjectName(QStringLiteral("scan_files"));
        scan_files->setGeometry(QRect(160, 10, 131, 41));
        scan_data = new QPushButton(centralWidget);
        scan_data->setObjectName(QStringLiteral("scan_data"));
        scan_data->setGeometry(QRect(310, 10, 131, 41));
        stop_scan = new QPushButton(centralWidget);
        stop_scan->setObjectName(QStringLiteral("stop_scan"));
        stop_scan->setGeometry(QRect(460, 10, 131, 41));
        ScannerQt->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(ScannerQt);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ScannerQt->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ScannerQt);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ScannerQt->setStatusBar(statusBar);

        retranslateUi(ScannerQt);

        QMetaObject::connectSlotsByName(ScannerQt);
    } // setupUi

    void retranslateUi(QMainWindow *ScannerQt)
    {
        ScannerQt->setWindowTitle(QApplication::translate("ScannerQt", "ScannerQt", 0));
        label->setText(QApplication::translate("ScannerQt", "Results:", 0));
        label_2->setText(QApplication::translate("ScannerQt", "Progress:", 0));
        label_3->setText(QApplication::translate("ScannerQt", "Enter data sequence:", 0));
        load_sigs->setText(QApplication::translate("ScannerQt", "Load signatures file", 0));
        scan_files->setText(QApplication::translate("ScannerQt", "Scan files", 0));
        scan_data->setText(QApplication::translate("ScannerQt", "Scan data sequence", 0));
        stop_scan->setText(QApplication::translate("ScannerQt", "Stop scanning", 0));
    } // retranslateUi

};

namespace Ui {
    class ScannerQt: public Ui_ScannerQt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCANNERQT_H
