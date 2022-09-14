#ifndef DOTA_2_LAYOUT_HANDLER_D2_LAYOUT_H
#define DOTA_2_LAYOUT_HANDLER_D2_LAYOUT_H

#include <exception>
#include <fstream>
#include <vector>

#include <json/json.h>

class D2Layout {
private:
	const int SUPPORTED_VERSION = 3;

	Json::Value layouts;
	Json::ArrayIndex layoutCount;
	std::string path;

public:
	explicit D2Layout(const std::string& path);
	[[nodiscard]] std::vector<std::string> getLayoutNames() const;
	Json::Value getLayout(std::string layoutName) const;
	void addLayout();
};

#endif //DOTA_2_LAYOUT_HANDLER_D2_LAYOUT_H
