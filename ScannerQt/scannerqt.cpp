#include "scannerqt.h"
#include "ui_scannerqt.h"

#include "file_path_collector.h"

#include <boost/dll/runtime_symbol_info.hpp>

#include <QFileDialog>

ScannerQt::ScannerQt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ScannerQt)
{
    ui->setupUi(this);

	ui->progressBar->setRange(0, 100);
	ui->progressBar->setValue(ui->progressBar->minimum());

	ui->scan_data->setDisabled(true);
	ui->scan_files->setDisabled(true);
	ui->stop_scan->setDisabled(true);

	try {

		scanner_obj = boost::dll::import<IScanner>(
			boost::filesystem::path("..\\Release\\Scanner"), 
			"SimpleScanner", 
			boost::dll::load_mode::append_decorations);

	} catch (...) {

		throw;

	}

	try {

		t_service = std::make_unique<TService<std::pair<IScanner::Results, std::string>>>(
			std::move([this](std::pair<IScanner::Results, std::string> res) {
			std::lock_guard<std::mutex> lock(out_results);
			if (res.first == IScanner::Results::SCANNER_INFECTED || res.first == IScanner::Results::SCANNER_ERROR)
				set_colored_item(QString(res.second.c_str()), Qt::darkRed);
			else if (res.first == IScanner::Results::SCANNER_WARN) {
				set_colored_item(QString(res.second.c_str()), Qt::darkYellow);
			}
			else {
				ui->filename->setText(QString(res.second.c_str()));
			}
		}));

	}
	catch (...) {

		throw;

	}

	//TODO: handle correctly exceptions above
}

ScannerQt::~ScannerQt()
{
    delete ui;
}

void ScannerQt::on_load_sigs_clicked()
{
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::ExistingFile);
	dialog.setViewMode(QFileDialog::List);
	QStringList filenames;
	if (dialog.exec())
	{
		filenames = dialog.selectedFiles();
		
		ui->listWidget->clear();
		ui->progressBar->setMaximum(0);

		std::pair<IScanner::Results, std::string> res = 
			scanner_obj->load_signatures_file(filenames[0].toLocal8Bit().constData());
		if (res.first == IScanner::Results::SCANNER_OK) {
			set_colored_item(QString(res.second.c_str()), Qt::darkGreen);
			ui->scan_data->setDisabled(false);
			ui->scan_files->setDisabled(false);
		}
		else {
			set_colored_item(QString(res.second.c_str()), Qt::darkRed);
			ui->scan_data->setDisabled(true);
			ui->scan_files->setDisabled(true);
			ui->stop_scan->setDisabled(true);
		}

		ui->progressBar->setMaximum(100);
	}
}

void ScannerQt::on_scan_files_clicked() {
    
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::Directory);
	dialog.setViewMode(QFileDialog::List);
	QStringList filenames;

	scanner_obj->reset_data_counter();

	if (dialog.exec())
	{
		ui->listWidget->clear();

		ui->scan_data->setDisabled(true);
		ui->load_sigs->setDisabled(true);
		ui->stop_scan->setDisabled(false);

		filenames = dialog.selectedFiles();
		input_path_store ips;
		for (auto const& filename: filenames) {
			ips.push_back(filename.toLocal8Bit().constData());
		}
		unique_path_store ups = ScannerFilePathCollector::collect_file_paths(ips);

		ui->progressBar->setMaximum(scanner_obj->get_sig_storage_size() * int(ups.size()));
		timer_id = startTimer(200);

		for (auto const& path : ups) {
			t_service->enqueue_job(&IScanner::scan_file, scanner_obj, path.string());
		}
	}
}

void ScannerQt::on_scan_data_clicked() {
	
	ui->listWidget->clear();
	scanner_obj->reset_data_counter();

	if (ui->plainTextEdit->toPlainText().size()) {

		ui->scan_files->setDisabled(true);
		ui->load_sigs->setDisabled(true);
		ui->stop_scan->setDisabled(false);

		ui->progressBar->setMaximum(scanner_obj->get_sig_storage_size());

		timer_id = startTimer(200);

		t_service->enqueue_job(&IScanner::scan_bytes, scanner_obj,
			std::basic_string<unsigned char>((unsigned char*)ui->plainTextEdit->toPlainText().toLocal8Bit().constData()));
	} else {
		set_colored_item(QString("Data sequence is empty!"), Qt::darkRed);
	}
}

void ScannerQt::on_stop_scan_clicked() {
    
	ui->stop_scan->setDisabled(true);
	ui->scan_files->setDisabled(false);
	ui->load_sigs->setDisabled(false);
	ui->scan_data->setDisabled(false);

	t_service->reset();
	killTimer(timer_id);
	ui->progressBar->setValue(ui->progressBar->minimum());
	ui->filename->setText(QString(""));
}

void ScannerQt::timerEvent(QTimerEvent *) {
	
	if (ui->progressBar->value() < ui->progressBar->maximum()) {
		
		ui->progressBar->setValue(scanner_obj->get_data_counter());
		ui->listWidget->scrollToBottom();

	} else {
		
		on_stop_scan_clicked();
		ui->progressBar->setValue(scanner_obj->get_data_counter());
		set_colored_item(QString("Scanning completed!"), Qt::darkGreen);
		ui->listWidget->scrollToBottom();
	
	}
}

void ScannerQt::set_colored_item(QString text, Qt::GlobalColor color) {
	QListWidgetItem* pItem = new QListWidgetItem(text);
	pItem->setForeground(color);
	ui->listWidget->addItem(pItem);
}
