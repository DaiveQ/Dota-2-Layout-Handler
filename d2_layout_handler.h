#ifndef DOTA_2_LAYOUT_HANDLER_D2_LAYOUT_HANDLER_H
#define DOTA_2_LAYOUT_HANDLER_D2_LAYOUT_HANDLER_H

#include <exception>
#include <string>
#include <vector>

#include <QApplication>
#include <QMessageBox>

#include "d2_layout.h"

class D2LayoutHandler {
private:
	std::vector<std::string> transferQueue;

	D2Layout *importConfig;
	D2Layout *exportConfig;

public:
	D2LayoutHandler(const std::filesystem::path &importConfigPath, const std::filesystem::path &exportConfigPath);

	[[nodiscard]] std::vector<std::string> getImportLayoutNames() const;

	[[nodiscard]] std::vector<std::string> getExportLayoutNames() const;

	bool addLayoutToTransferQueue(const std::string &layoutName);

	void removeLayoutFromTransferQueue(const std::string &layoutName);

	void commitChanges(QWidget *parent);

};

#endif //DOTA_2_LAYOUT_HANDLER_D2_LAYOUT_HANDLER_H
