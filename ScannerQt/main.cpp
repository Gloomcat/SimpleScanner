#include "scannerqt.h"
#include <QApplication>
#include "vld.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	a.setQuitOnLastWindowClosed(true);

    ScannerQt w;
	w.setAttribute(Qt::WA_QuitOnClose);
    w.show();

    return a.exec();
}
