#include "Downloader.h"
#include "VideoDownloader/Downloader.h"
#include <sstream>
#include <ctime>




Downloader::Downloader(Text* __argf) {
	font = __argf;
}
int Downloader::Download(std::string argUrl) {
	//download stuff
	if ((time(NULL) - delay) > 30) {
		delay = time(NULL);
		{std::stringstream ss;
		ss << "-- Downloading " << argUrl;
		linesD.push_back(ss.str()); }
		DownloadVideo(argUrl);
		{std::stringstream ss;
		ss << "-- Done Downloading " << argUrl;
		linesD.push_back(ss.str()); }
		return 0;
	}
	delay--;
}
void Downloader::render() {
	for (int i = 0; i < linesD.size(); i++) {
		font->drawText(linesD[i], 300, 470 - (30 * i), 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
	}
}