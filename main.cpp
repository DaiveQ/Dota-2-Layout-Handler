#include "main_widget.h"

#include <QApplication>

// Overall TODO
// TODO: Create QWidget to initialize D2LayoutHandler
// TODO: Mark functions as static and const wherever possible
// TODO: Clean up

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	auto* d2LayoutHandler = new D2LayoutHandler("test_config/import.json", "test_config/export.json");
    MainWidget w(d2LayoutHandler);
    w.show();
    return a.exec();
}
