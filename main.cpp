#include <QApplication>

#include "main_widget.h"

// Overall TODO
// TODO: Create QWidget to initialize D2LayoutHandler
// TODO: Mark functions as static and const wherever possible
// TODO: Clean up

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	MainWidget mainWidget;
	mainWidget.show();
    return a.exec();
}
