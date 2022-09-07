#ifndef WIDGET_H
#define WIDGET_H

#include <vector>

#include <QColor>
#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QWidget>

// TODO: move ALL transfer queue logic to d2_layout_handler as originally intended

class Widget : public QWidget {
Q_OBJECT
private:
	const QColor greyedOutBGColor = QColor(0xE5E5E5);
	const QColor greyedOutFGColor = QColor(0x747474);

	static void populateQListWidget(QListWidget *list, std::vector<std::string> strings);

	std::vector<std::string> transferQueue;

	QListWidget *importList;
	QListWidget *exportList;

	// TODO: these are also part of transfer queue layout and should take string instead
	bool addLayoutToTransferQueue(QListWidgetItem *item);
	void removeLayoutFromTransferQueue(QListWidgetItem *item);

	void addQueuedLayoutToExportList(QListWidgetItem *item);
	void removeLayoutFromExportList(QListWidgetItem *item);


public:
	Widget(QWidget *parent = nullptr);

	~Widget();

private slots:

	void queueTransfer();
	void unqueueTransfer();
	void commitChanges();
};

#endif // WIDGET_H
