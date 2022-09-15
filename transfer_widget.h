#ifndef DOTA_2_LAYOUT_HANDLER_TRANSFER_WIDGET_H
#define DOTA_2_LAYOUT_HANDLER_TRANSFER_WIDGET_H

#include <vector>

#include <QColor>
#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "d2_layout_handler.h"


class TransferWidget : public QWidget {
Q_OBJECT
private:
	D2LayoutHandler *d2LayoutHandler;

	const QColor greyedOutBGColor = QColor(0xE5E5E5);
	const QColor greyedOutFGColor = QColor(0x747474);

	static void populateQListWidget(QListWidget *list, const std::vector<std::string> &strings);

	QListWidget *importList;
	QListWidget *exportList;

	void addQueuedLayoutToExportList(QListWidgetItem *item);

	void removeLayoutFromExportList(QListWidgetItem *item);

	// TODO: Refactor to remove?
	bool addLayoutToTransferQueue(QListWidgetItem *item);

	void removeLayoutFromTransferQueue(QListWidgetItem *item);

public:
	explicit TransferWidget(D2LayoutHandler *d2LayoutHandler, QWidget *parent = nullptr);

	~TransferWidget();

private slots:

	void queueTransfer();

	void unqueueTransfer();

	void commitChanges();
};

#endif // DOTA_2_LAYOUT_HANDLER_TRANSFER_WIDGET_H
