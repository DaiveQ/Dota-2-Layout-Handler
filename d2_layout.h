#ifndef DOTA_2_LAYOUT_HANDLER_D2_LAYOUT_H
#define DOTA_2_LAYOUT_HANDLER_D2_LAYOUT_H

#include <exception>
#include <filesystem>
#include <fstream>
#include <vector>

#include <json/json.h>

class D2Layout {
private:
	const int SUPPORTED_VERSION = 3;

	Json::Value jsonData;
	Json::ArrayIndex layoutCount;
	std::filesystem::path path;

public:
	explicit D2Layout(const std::filesystem::path path);
	[[nodiscard]] std::vector<std::string> getLayoutNames() const;
	Json::Value getLayout(const std::string& layoutName) const;
	void addLayout(const Json::Value& layout);

	bool backupFile();
	bool flushBuffer();
};

#endif //DOTA_2_LAYOUT_HANDLER_D2_LAYOUT_H
