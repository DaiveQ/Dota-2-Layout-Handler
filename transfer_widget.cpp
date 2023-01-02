#include "transfer_widget.h"

// TODO: Move logic to generate window to functions and allow for reloading (after layout set)

TransferWidget::TransferWidget(D2LayoutHandler* d2LayoutHandler, QWidget *parent) : QWidget(parent) {
	this->d2LayoutHandler = d2LayoutHandler;

	/*
	 *  (import list) (transfer options) (export list)
	 *
	 * ------------------------------------------------
	 * | item A      |                  | item X      |
	 * | item B      |    [transfer]    | item Y      |
	 * | item C      |     [remove]     | *item A*    |
	 * | item D      |                  |             |
	 * ------------------------------------------------
	 * |                             [commit changes] |
	 * ------------------------------------------------
	*/


	auto *mainQVBoxL = new QVBoxLayout(this);

	auto *transferManagementPanel = new QHBoxLayout;

	mainQVBoxL->addLayout(transferManagementPanel);

	// commit changes button
	commitBtn = new QPushButton;
	commitBtn->setText("Commit Changes");
	mainQVBoxL->addWidget(commitBtn, 0, Qt::AlignRight);
	connect(commitBtn, SIGNAL(clicked()), this, SLOT(commitChanges()));

	// import/export list
	importList = new QListWidget;
	exportList = new QListWidget;

	populateQListWidget(importList, this->d2LayoutHandler->getImportLayoutNames());
	populateQListWidget(exportList, this->d2LayoutHandler->getExportLayoutNames());

	// transfer options
	auto *transferOptionsQVBoxL = new QVBoxLayout;
	auto *transferBtn = new QPushButton;
	transferBtn->setText("Transfer");
	transferOptionsQVBoxL->addWidget(transferBtn);

	// TODO: think of better name
	auto *undoTransferBtn = new QPushButton;
	undoTransferBtn->setText("Undo Transfer");
	transferOptionsQVBoxL->addWidget(undoTransferBtn);

	connect(transferBtn, SIGNAL(clicked()), this, SLOT(queueTransfer()));
	connect(undoTransferBtn, SIGNAL(clicked()), this, SLOT(unqueueTransfer()));
	connect(importList, SIGNAL(itemDoubleClicked(QListWidgetItem * )),
	        this, SLOT(queueTransfer()));
	connect(exportList, SIGNAL(itemDoubleClicked(QListWidgetItem * )),
	        this, SLOT(unqueueTransfer()));

	// add to main layout in order
	transferManagementPanel->addWidget(importList);
	transferManagementPanel->addLayout(transferOptionsQVBoxL);
	transferManagementPanel->addWidget(exportList);
}


TransferWidget::~TransferWidget() {
	// TODO: free whatever else needs to be free (read docs)
	free(d2LayoutHandler);
}

void TransferWidget::populateQListWidget(QListWidget *list, const std::vector<std::string>& strings) {
	for (const auto &string: strings) {
		auto *item = new QListWidgetItem;
		item->setText(string.c_str());
		list->addItem(item);
	}
}

bool TransferWidget::addLayoutToTransferQueue(QListWidgetItem *item) {
	std::string layoutName = item->text().toStdString();
	return d2LayoutHandler->addLayoutToTransferQueue(layoutName);
}

void TransferWidget::addQueuedLayoutToExportList(QListWidgetItem *item) {
	auto *queuedLayout = new QListWidgetItem;
	queuedLayout->setText(item->text());
	queuedLayout->setForeground(greyedOutFGColor);
	queuedLayout->setBackground(greyedOutBGColor);
	exportList->addItem(queuedLayout);
}


void TransferWidget::queueTransfer() {
	// I can't seem to select multiple items, but it should be handled regardless
	auto itemList = importList->selectedItems();
	for (auto *item: itemList) {
		if (addLayoutToTransferQueue(item)) {
			addQueuedLayoutToExportList(item);
		}
	}
}

void TransferWidget::removeLayoutFromTransferQueue(QListWidgetItem *item) {
	std::string layoutName = item->text().toStdString();
	d2LayoutHandler->removeLayoutFromTransferQueue(layoutName);
}

// does this even do anything?
void TransferWidget::removeLayoutFromExportList(QListWidgetItem *item) {
	exportList->removeItemWidget(item);
}

void TransferWidget::unqueueTransfer() {
	auto itemList = exportList->selectedItems();
	for (auto *item: itemList) {
		// TODO: Find better way to check/keep track than color
		if (item->background().color() == greyedOutBGColor) {
			// TODO: Should be delegated to always happen together
			removeLayoutFromTransferQueue(item);
			removeLayoutFromExportList(item);
			delete item;
		}
	}
}

void TransferWidget::commitChanges() {
    commitBtn->setEnabled(false);
	d2LayoutHandler->commitChanges(this);
    commitBtn->setEnabled(true);
}

