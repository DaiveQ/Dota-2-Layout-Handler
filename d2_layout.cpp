#include "d2_layout.h"

D2Layout::D2Layout(const std::string& path) {
	std::ifstream config(path);
	Json::Value root;
	config >> root;

	int version = root["version"].asInt();
	if (version != SUPPORTED_VERSION) {
		throw std::logic_error("unsupported version " + std::to_string(version)
		                         + " when only version 3 is supported");
	}

	layouts = root["configs"];
	layoutCount = root["configs"].size();
}

std::vector<std::string> D2Layout::getLayoutNames() const {
	std::vector<std::string> layoutNames;

	for (Json::ArrayIndex i = 0; i < layoutCount; i++) {
		layoutNames.emplace_back(layouts[i]["config_name"].asString());
	}

	return layoutNames;
}
