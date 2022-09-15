#include "d2_layout_handler.h"

D2LayoutHandler::D2LayoutHandler(const std::filesystem::path &importConfigPath,
                                 const std::filesystem::path &exportConfigPath) {
	importConfig = new D2Layout(importConfigPath);
	exportConfig = new D2Layout(importConfigPath);
}

std::vector<std::string> D2LayoutHandler::getImportLayoutNames() {
	return importConfig->getLayoutNames();
}

std::vector<std::string> D2LayoutHandler::getExportLayoutNames() {
	return exportConfig->getLayoutNames();
}

bool D2LayoutHandler::addLayoutToTransferQueue(const std::string &layoutName) {
	for (const auto &queueLayoutNames: transferQueue) {
		if (layoutName == queueLayoutNames) {
			return false;
		}
	}
	transferQueue.emplace_back(layoutName);
	return true;
}

void D2LayoutHandler::removeLayoutFromTransferQueue(const std::string &layoutName) {
	for (auto it = begin(transferQueue); it != end(transferQueue); it++) {
		if (layoutName == *it) {
			transferQueue.erase(it);
			return;
		}
	}

	throw std::runtime_error("attempt to remove invalid layout");

}

void D2LayoutHandler::commitChanges() {
	// TODO: handle transfer with no layouts queued
	// TODO: handle transfers with conflicting names (ask user to rename)
	//     TODO: let user rename in general

	if (!exportConfig->backupFile()) {
		// TODO: ask user whether to continue or not
	}
	for (const auto &layoutName: transferQueue) {
		exportConfig->addLayout(importConfig->getLayout(layoutName));
	}

	exportConfig->flushBuffer();

	// TODO: reload window with updated changes (change by reading config files, not based on logic)

}
