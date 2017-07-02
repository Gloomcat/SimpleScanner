#pragma once

#ifndef SCANNERQT_H
#define SCANNERQT_H

#include <QMetaType>
#include <QMainWindow>
#include <QTimer>

#include <boost\dll\import.hpp>

#include "threading_service.h"
#include "file_path_collector.h"


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
	void on_result_received(const result_type& result);
	void on_paths_collected(const unique_path_store& ups);

signals:

	void result_ready(const result_type& result);
	void paths_collected(const unique_path_store& ups);

private:
	void set_colored_item(QString text, Qt::GlobalColor color);

	int timer_id;

	std::unique_ptr<TService<result_type>> t_service;
	std::shared_ptr<FilePathCollector> file_path_collector;
    boost::shared_ptr<IScanner> scanner_obj;

    Ui::ScannerQt *ui;
};

#endif // SCANNERQT_H
