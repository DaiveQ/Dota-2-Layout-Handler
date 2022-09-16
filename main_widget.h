#ifndef DOTA_2_LAYOUT_HANDLER_MAIN_WIDGET_H
#define DOTA_2_LAYOUT_HANDLER_MAIN_WIDGET_H

#include <vector>

#include <QColor>
#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QStackedLayout>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>

#include "file_selector_widget.h"
#include "transfer_widget.h"
#include "d2_layout_handler.h"


class MainWidget : public QWidget {
Q_OBJECT
private:
public:
	explicit MainWidget(QWidget *parent = nullptr);

	~MainWidget();
};

#endif // DOTA_2_LAYOUT_HANDLER_TRANSFER_WIDGET_H
