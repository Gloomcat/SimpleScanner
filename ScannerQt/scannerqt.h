#pragma once

#ifndef SCANNERQT_H
#define SCANNERQT_H

#include <QMainWindow>
#include <QTimer>

#include <boost\dll\import.hpp>

#include "..\Scanner\i_scanner.h"
#include "threading_service.h"

using namespace SimpleScanner;

namespace Ui {
class ScannerQt;
}

class ScannerQt : public QMainWindow
{
    Q_OBJECT

public:
    
	explicit ScannerQt(QWidget *parent = 0);
    ~ScannerQt();

protected:
	void timerEvent(QTimerEvent *event);

private slots:
    
	void on_load_sigs_clicked();
    void on_scan_files_clicked();
    void on_scan_data_clicked();
    void on_stop_scan_clicked();

private:
	void set_colored_item(QString text, Qt::GlobalColor color);

	int timer_id;

	std::mutex out_results;
	std::unique_ptr<TService<std::pair<IScanner::Results, std::string>>> t_service;
    boost::shared_ptr<IScanner> scanner_obj;

    Ui::ScannerQt *ui;
};

#endif // SCANNERQT_H
