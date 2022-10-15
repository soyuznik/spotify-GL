#pragma once
#include "lowlevel/TEXT.h"


class Downloader {
public:
	Text* font;
	std::vector<std::string> linesD;
	std::string url;
	int delay = 0;
	Downloader(Text* __argf);
	int Download(std::string argUrl);
	void render();
};