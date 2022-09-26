#include "d2_layout_handler.h"

D2LayoutHandler::D2LayoutHandler(const std::filesystem::path &importConfigPath,
                                 const std::filesystem::path &exportConfigPath) {
	// file selection error handling
	if (!std::filesystem::exists(importConfigPath) || !std::filesystem::exists(exportConfigPath)) {
		if (std::filesystem::exists(importConfigPath)) { // export file doesn't exist
			throw std::runtime_error("export config does not exist");
		} else if (std::filesystem::exists(exportConfigPath)) { // import file doesn't exist
			throw std::runtime_error("import config does not exist");
		} else { // both don't exist
			throw std::runtime_error("import and export config don't exist");
		}
	}

	// same import and export file handling
	if (std::filesystem::equivalent(importConfigPath, exportConfigPath)) {
		throw std::runtime_error("config paths cannot be the same");
	}

	// json parsing error handling
	try {
		importConfig = new D2Layout(importConfigPath);
	} catch (Json::RuntimeError &jsonRuntimeError) {
		throw std::runtime_error("could not parse json from import config");
	}
	try {
		exportConfig = new D2Layout(exportConfigPath);
	} catch (Json::RuntimeError &jsonRuntimeError) {
		throw std::runtime_error("could not parse json from export config");
	}
}

std::vector<std::string> D2LayoutHandler::getImportLayoutNames() const {
	return importConfig->getLayoutNames();
}

std::vector<std::string> D2LayoutHandler::getExportLayoutNames() const {
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

bool D2LayoutHandler::commitChanges() {
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

	// TODO: Actually add error checking
	return true;

}
