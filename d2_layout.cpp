#include "d2_layout.h"

D2Layout::D2Layout(std::filesystem::path path) {
	this->path = path;
	std::ifstream config(path);
	config >> jsonData;

	int version = jsonData["version"].asInt();
	if (version != SUPPORTED_VERSION) {
		throw std::logic_error("unsupported version " + std::to_string(version)
		                       + " when only version 3 is supported");
	}
	layoutCount = jsonData["configs"].size();
}

std::vector<std::string> D2Layout::getLayoutNames() const {
	std::vector<std::string> layoutNames;

	// TODO: Perhaps can change to not use index by using enhanced for loops if jsoncpp implements it
	for (Json::ArrayIndex i = 0; i < layoutCount; i++) {
		layoutNames.emplace_back(jsonData["configs"][i]["config_name"].asString());
	}

	return layoutNames;
}

Json::Value D2Layout::getLayout(const std::string &layoutName) const {
	// TODO: Perhaps can change to not use index by using enhanced for loops if jsoncpp implements it
	for (Json::ArrayIndex i = 0; i < layoutCount; i++) {
		if (layoutName == jsonData["configs"][i]["config_name"].asString()) {
			return jsonData["configs"][i];
		}
	}
	throw std::logic_error("invalid layout to get");
}

void D2Layout::addLayout(const Json::Value &layout) {
	jsonData["configs"].append(layout);
}

bool D2Layout::backupFile() const {
	// TODO: Implement checking and return a meaningful bool
	// or throw error and handle it
	// currently always a success
	std::filesystem::path backupRoot = path.parent_path();
	backupRoot.append("backup");
	if (!std::filesystem::exists(backupRoot)) {
		std::filesystem::create_directory(backupRoot);
	}

	std::string backupFileName = path.filename().string();


	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	char timeStampSuffix[80];
	std::strftime(timeStampSuffix, 80, "-%Y-%m-%d-%H-%M-%S", localtime(&now));
	std::stringstream timeStamp;
	backupFileName += std::string(timeStampSuffix) + ".bak";

	std::filesystem::path backupPath = backupRoot;
	backupPath.append(backupFileName);

	std::filesystem::copy(path, backupPath);

	// TODO: Error check
	return true;
}

// returns false if badbit or failbit is set after closing
bool D2Layout::flushBuffer() const {
	std::ofstream config(path);

	Json::StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = "\t";
	Json::StreamWriter *writer = builder.newStreamWriter();

	writer->write(jsonData, &config);
	config.flush();
	config.close();

	if (config.fail()) {
		return false;
	} else {
		return true;
	}
}
