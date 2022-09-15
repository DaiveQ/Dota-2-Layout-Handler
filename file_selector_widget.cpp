#include "file_selector_widget.h"

FileSelectorWidget::FileSelectorWidget(QStackedWidget *parent) {
	this->parent = parent;
	/*
	 * ---------------------------------------------
	 * | Import layouts from:                      |
	 * | [ path text box ************** ] [choose] |
	 * |                                           |
	 * | Export Layouts to:                        |
	 * | [ path text box ************** ] [choose] |
	 * |                                           |
	 * | short helpful message about paths         |
	 * |                            [confirm sele] |
	 * |-------------------------------------------|
	 * | short footer about project/repo link      |
	 * ---------------------------------------------
	 */

	auto *mainQVBoxL = new QVBoxLayout(this);

	auto *footerLabel = new QLabel;
	footerLabel->setText("Created by DaiveQ: https://github.com/DaiveQ/Dota-2-Layout-Handler");

	auto *fileSelectorWidget = new QVBoxLayout;

	mainQVBoxL->addLayout(fileSelectorWidget);
	mainQVBoxL->addWidget(footerLabel);

	auto *importFileSelectorQHBoxL = new QHBoxLayout;
	auto *exportFileSelectorQHBoxL = new QHBoxLayout;
	auto *confirmQHBoxL = new QHBoxLayout;

	fileSelectorWidget->addLayout(importFileSelectorQHBoxL);
	fileSelectorWidget->addLayout(exportFileSelectorQHBoxL);
	fileSelectorWidget->addLayout(confirmQHBoxL);

	auto *importFileQLineEdit = new QLineEdit;
	importFileQLineEdit->setPlaceholderText("import config path");

	auto *chooseImportFileBtn = new QPushButton;
	chooseImportFileBtn->setText("Choose");

	importFileSelectorQHBoxL->addWidget(importFileQLineEdit);
	importFileSelectorQHBoxL->addWidget(chooseImportFileBtn);

	auto *exportFileQLineEdit = new QLineEdit;
	exportFileQLineEdit->setPlaceholderText("export config path");

	auto *chooseExportFileBtn = new QPushButton;
	chooseExportFileBtn->setText("Choose");

	exportFileSelectorQHBoxL->addWidget(exportFileQLineEdit);
	exportFileSelectorQHBoxL->addWidget(chooseExportFileBtn);

	// TODO: add footer(?)
	// TODO: add signal handlers for choose buttons
	// TODO: add labels for sections

}

FileSelectorWidget::~FileSelectorWidget() {

}

void FileSelectorWidget::switchParentToTransferWidget(D2LayoutHandler *d2LayoutHandler) {
	auto* transferWidget = new TransferWidget(d2LayoutHandler, parent);
	parent->addWidget(transferWidget);
	parent->setCurrentIndex(parent->indexOf(transferWidget));
}
