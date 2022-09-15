#include "main_widget.h"

MainWidget::MainWidget(QWidget *parent) : QStackedWidget(parent) {
	setWindowTitle("Dota 2 Layout Handler");
	QWidget *fsWidget = new FileSelectorWidget(this);
	addWidget(fsWidget);
	setCurrentIndex(indexOf(fsWidget));
}


MainWidget::~MainWidget() {
}