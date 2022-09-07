#ifndef DOTA_2_LAYOUT_HANDLER_D2_LAYOUT_HANDLER_H
#define DOTA_2_LAYOUT_HANDLER_D2_LAYOUT_HANDLER_H

#include <stdio.h>
#include <string>
#include <vector>

//#include <json/json.h>

class D2LayoutHandler {
	std::vector<std::string> getLayouts(FILE* file);
};


#endif //DOTA_2_LAYOUT_HANDLER_D2_LAYOUT_HANDLER_H
