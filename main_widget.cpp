#include "main_widget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
	/*
	 * ---------------------------------
	 * |                               |
	 * |                               |
	 * | Stacked Widget (active area)  |
	 * |                               |
	 * |                               |
	 * |-------------------------------|
	 */
	setWindowTitle("Dota 2 Layout Handler");
	resize(570, 250);
	setMinimumSize(550,250);
	auto *mainQVBoxLayout = new QVBoxLayout(this);
	auto *mainStackedWidget = new QStackedWidget;
	mainQVBoxLayout->addWidget(mainStackedWidget);
	QWidget *fsWidget = new FileSelectorWidget(mainStackedWidget);
	mainStackedWidget->addWidget(fsWidget);
	mainStackedWidget->setCurrentIndex(mainStackedWidget->indexOf(fsWidget));
}


MainWidget::~MainWidget() {
}