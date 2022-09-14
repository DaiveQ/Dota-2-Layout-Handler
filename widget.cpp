#include "widget.h"

#include "d2_layout.h" // TODO: Don't include this. Only include d2_layout_handler.h

// TODO: Move logic to generate window to functions and allow for reloading (after layout set)

Widget::Widget(QWidget *parent) : QWidget(parent) {
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

	setWindowTitle("Dota 2 Layout Handler");


	auto *mainQVBoxL = new QVBoxLayout(this);

	auto *transferManagementPanel = new QHBoxLayout;

	mainQVBoxL->addLayout(transferManagementPanel);


	// commit changes button
	auto *commitBtn = new QPushButton;
	commitBtn->setText("Commit Changes");
	mainQVBoxL->addWidget(commitBtn, 0, Qt::AlignRight);
	connect(commitBtn, SIGNAL(clicked()), this, SLOT(commitChanges()));

	// import/export list
	importList = new QListWidget;
	exportList = new QListWidget;

	// TODO: TEMP
	// TODO: Allow file selection
	importConfig = new D2Layout("test_config/import.json");
	exportConfig = new D2Layout("test_config/export.json");

	populateQListWidget(importList, importConfig->getLayoutNames());
	populateQListWidget(exportList, exportConfig->getLayoutNames());

	// transfer options
	auto *transferOptionsQVBoxL = new QVBoxLayout;
	auto *transferBtn = new QPushButton;
	transferBtn->setText("Transfer");
	transferOptionsQVBoxL->addWidget(transferBtn);

	// TODO: think of better name
	auto *undoTransferBtn = new QPushButton;
	undoTransferBtn->setText("Undo Transfer");
	transferOptionsQVBoxL->addWidget(undoTransferBtn);

	// transfer panel handlers
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


Widget::~Widget() {
}

void Widget::populateQListWidget(QListWidget *list, std::vector<std::string> strings) {
	for (const auto &string: strings) {
		auto *item = new QListWidgetItem;
		item->setText(string.c_str());
		list->addItem(item);
	}
}

bool Widget::addLayoutToTransferQueue(QListWidgetItem *item) {
	std::string configName = item->text().toStdString();

	for (const auto &queueItemConfigName: transferQueue) {
		if (configName == queueItemConfigName) {
			return false;
		}
	}

	transferQueue.emplace_back(configName);
	return true;

}

void Widget::addQueuedLayoutToExportList(QListWidgetItem *item) {
	auto *queuedLayout = new QListWidgetItem;
	queuedLayout->setText(item->text());
	queuedLayout->setForeground(greyedOutFGColor);
	queuedLayout->setBackground(greyedOutBGColor);
	exportList->addItem(queuedLayout);
}


void Widget::queueTransfer() {
	// I can't seem to select multiple items, but it should be handled regardless
	auto itemList = importList->selectedItems();
	for (auto *item: itemList) {
		if (addLayoutToTransferQueue(item)) {
			addQueuedLayoutToExportList(item);
		}
	}
}

void Widget::removeLayoutFromTransferQueue(QListWidgetItem *item) {
	std::string configName = item->text().toStdString();

	for (auto it = begin(transferQueue); it != end(transferQueue); it++) {
		if (configName == *it) {
			transferQueue.erase(it);
			return;
		}
	}

	throw std::runtime_error("attempt to remove invalid layout");
}

// does this even do anything?
void Widget::removeLayoutFromExportList(QListWidgetItem *item) {
	exportList->removeItemWidget(item);
}

void Widget::unqueueTransfer() {
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

void Widget::commitChanges() {
	// TODO: transfer layouts in transferQueue
	// TODO: backup before transferring layouts
	// TODO: reload window with updated changes (change by reading config files, not based on logic)
}

