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
	 * | footer with link to repo      |
	 * ---------------------------------
	 */
	auto *mainQVBoxLayout = new QVBoxLayout(this);
	auto *mainStackedWidget = new QStackedWidget;
	mainQVBoxLayout->addWidget(mainStackedWidget);
	setWindowTitle("Dota 2 Layout Handler");
	QWidget *fsWidget = new FileSelectorWidget(mainStackedWidget);
	mainStackedWidget->addWidget(fsWidget);
	mainStackedWidget->setCurrentIndex(mainStackedWidget->indexOf(fsWidget));
	// TODO: add footer with fixed size and pin to bottom
}


MainWidget::~MainWidget() {
}