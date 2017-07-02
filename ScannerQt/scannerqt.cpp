#include "scannerqt.h"
#include "ui_scannerqt.h"

#include <QFileDialog>

ScannerQt::ScannerQt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ScannerQt) {

    ui->setupUi(this);

	ui->progressBar->setRange(0, 100);
	ui->progressBar->setValue(ui->progressBar->minimum());

	ui->scan_data->setDisabled(true);
	ui->scan_files->setDisabled(true);
	ui->stop_scan->setDisabled(true);

	qRegisterMetaType<result_type>("result_type");
	qRegisterMetaType<unique_path_store>("unique_path_store");

	connect(this, SIGNAL(paths_collected(unique_path_store)),
		this, SLOT(on_paths_collected(unique_path_store)), Qt::QueuedConnection);

	connect(this, SIGNAL(result_ready(result_type)),
		this, SLOT(on_result_received(result_type)), Qt::QueuedConnection);

	file_path_collector = std::make_shared<FilePathCollector>(
		std::move([this](const unique_path_store& ups) {
		emit paths_collected(ups);
	}));

	try {

		scanner_obj = boost::dll::import<IScanner>(
			boost::filesystem::path("..\\Debug\\Scanner"), 
			"SimpleScanner", 
			boost::dll::load_mode::append_decorations);

	} catch (...) {

		throw;

	}

	try {

		t_service = std::make_unique<TService<result_type>>(
			std::move([this](result_type res) {
			emit result_ready(res);
		}));

	}
	catch (...) {

		throw;

	}

	//TODO: handle correctly exceptions above
}

ScannerQt::~ScannerQt() {
    delete ui;
}

void ScannerQt::on_load_sigs_clicked() {
	
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::ExistingFile);
	dialog.setViewMode(QFileDialog::List);
	QStringList filenames;
	if (dialog.exec())
	{
		filenames = dialog.selectedFiles();
		
		ui->listWidget->clear();
		ui->progressBar->setMaximum(0);

		result_type res = 
			scanner_obj->load_signatures_file(filenames[0].toLocal8Bit().constData());
		if (res.first == IScanner::Results::SCANNER_OK) {
			ui->scan_data->setDisabled(false);
			ui->scan_files->setDisabled(false);
		}
		else {
			ui->scan_data->setDisabled(true);
			ui->scan_files->setDisabled(true);
			ui->stop_scan->setDisabled(true);
		}
		emit result_ready(res);

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

		filenames = dialog.selectedFiles();
		input_path_store ips;
		for (auto const& filename: filenames) {
			ips.push_back(filename.toLocal8Bit().constData());
		}

		ui->progressBar->setMaximum(0);
		emit result_ready(std::make_pair<IScanner::Results, std::string>(
			IScanner::Results::SCANNER_OK, std::string("Collecting unique files info, please wait...")));
		
		unique_path_store ups;
		t_service->enqueue_job(&FilePathCollector::collect_file_paths, file_path_collector, ips, ups);

	}
}

void ScannerQt::on_paths_collected(const unique_path_store& ups) {

	ui->progressBar->setMaximum(scanner_obj->get_sig_storage_size() * int(ups.size()));
	timer_id = startTimer(200);
	ui->stop_scan->setDisabled(false);

	for (auto const& path : ups) {
		t_service->enqueue_job(&IScanner::scan_file, scanner_obj, path.string());
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
		emit result_ready(std::make_pair<IScanner::Results, std::string>(
			IScanner::Results::SCANNER_ERROR, std::string("Data sequence is empty!")));
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
	ui->listWidget->scrollToBottom();
}

void ScannerQt::timerEvent(QTimerEvent *) {
	
	if (ui->progressBar->value() < ui->progressBar->maximum()) {
		
		ui->progressBar->setValue(scanner_obj->get_data_counter());

	} else {
		
		on_stop_scan_clicked();
		ui->progressBar->setValue(scanner_obj->get_data_counter());
		emit result_ready(std::make_pair<IScanner::Results, std::string>(
			IScanner::Results::SCANNER_OK, std::string("Scanning completed!")));
	
	}
}

void ScannerQt::on_result_received(const result_type& result) {

	if (result.first == IScanner::Results::SCANNER_ERROR || result.first == IScanner::Results::SCANNER_INFECTED) {
		set_colored_item(QString(result.second.c_str()), Qt::darkRed);
	}
	else if (result.first == IScanner::Results::SCANNER_WARN) {
		set_colored_item(QString(result.second.c_str()), Qt::darkYellow);
	}
	else if (result.first == IScanner::Results::SCANNER_STAT) {
		ui->filename->setText(QString(result.second.c_str()));
	}
	else {
		set_colored_item(QString(result.second.c_str()), Qt::darkGreen);
	}

	QApplication::processEvents();

}

void ScannerQt::set_colored_item(QString text, Qt::GlobalColor color) {
	QListWidgetItem* pItem = new QListWidgetItem(text);
	pItem->setForeground(color);
	ui->listWidget->addItem(pItem);
	ui->listWidget->scrollToBottom();
}
