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
	 * |                       [confirm selection] |
	 * ---------------------------------------------
	 */


	auto *fileSelectorQVBoxL = new QVBoxLayout(this);

	auto *importFileSelectorQHBoxL = new QHBoxLayout;
	auto *exportFileSelectorQHBoxL = new QHBoxLayout;

	fileSelectorQVBoxL->addLayout(importFileSelectorQHBoxL);
	fileSelectorQVBoxL->addLayout(exportFileSelectorQHBoxL);

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

	auto *confirmBtn = new QPushButton;
	confirmBtn->setText("Confirm Selection");
	fileSelectorQVBoxL->addWidget(confirmBtn, 0, Qt::AlignRight);

	// using lambda expression as slot doesn't work with SIGNAL(clicked()) for some reason
	// SIGNAL(clicked()) can easily be replaced by &QPushButton::clicked, but a custom
	// implementation would be required to replace SIGNAL(itemDoubleClicked) with something
	// similar, thus SIGNAL() will continue to be used in situations where it is not required
	connect(chooseImportFileBtn, &QPushButton::clicked, this,
	        [this, importFileQLineEdit]() { promptFileSelection(importFileQLineEdit); });
	connect(chooseExportFileBtn, &QPushButton::clicked, this,
	        [this, exportFileQLineEdit]() { promptFileSelection(exportFileQLineEdit); });
	connect(confirmBtn, &QPushButton::clicked, this,
	        [this, importFileQLineEdit, exportFileQLineEdit]() {
		        confirmSelection(importFileQLineEdit, exportFileQLineEdit);
	        });

	// TODO: add labels for sections


}

FileSelectorWidget::~FileSelectorWidget() {

}

void FileSelectorWidget::switchParentToTransferWidget(D2LayoutHandler *d2LayoutHandler) {
	auto *transferWidget = new TransferWidget(d2LayoutHandler, parent);
	parent->addWidget(transferWidget);
	parent->setCurrentIndex(parent->indexOf(transferWidget));
}

void FileSelectorWidget::promptFileSelection(QLineEdit *pathQLineEdit) {
	QString currentPath = QString::fromStdString(std::filesystem::current_path().string());
	pathQLineEdit->setText(
			QFileDialog::getOpenFileName(this, tr("Open Layout Config"), currentPath, tr("Layout Config (*.json)")));
	QFileDialog dialog(this);
}

void FileSelectorWidget::confirmSelection(QLineEdit *importFileQLineEdit, QLineEdit *exportFileQLineEdit) {
	std::string importFilePath = importFileQLineEdit->text().toStdString();
	std::string exportFilePath = exportFileQLineEdit->text().toStdString();
	auto *d2LayoutHandler = new D2LayoutHandler(importFilePath, exportFilePath);
	switchParentToTransferWidget(d2LayoutHandler);
}
