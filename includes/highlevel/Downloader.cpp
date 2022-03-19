#include "Downloader.h"
#include <algorithm>
#include "lowlevel/UTILITY.h"
#include "windows.h"
#include <iostream>
#include <thread>




Downloader::Downloader(){}
void Downloader::Download(std::string text) {
	std::thread download_Thread = std::thread(&__download, text);
	download_Thread.detach();
}

int Downloader::__download(std::string __text) {
	
		system((std::string("c: & cd C:\\Users\\user\\Documents\\GitHub\\TRANSPARENT-TRIANGLE\\dependencies & youtube-dl -o ") +
			std::string("C:\\Users\\user\\Documents\\GitHub\\TRANSPARENT-TRIANGLE\\data\\out.mp4  ") + __text).c_str());

		std::vector v = listdir("data");
		if (std::find(v.begin(), v.end(), "out.mp4") != v.end()) {
			/* v contains mp4 file */
			system((std::string("cd C:\\Users\\user\\Documents\\GitHub\\TRANSPARENT-TRIANGLE\\dependencies & ") +
				std::string("ffmpeg -i C:\\Users\\user\\Documents\\GitHub\\TRANSPARENT-TRIANGLE\\data\\out.mp4 - vn out.mp3 && del out.mp4")).c_str());
		}
		if (std::find(v.begin(), v.end(), "out.mkv") != v.end()) {
			/* v contains mkv file */
			system((std::string("cd C:\\Users\\user\\Documents\\GitHub\\TRANSPARENT-TRIANGLE\\dependencies & ") +
				std::string("ffmpeg -i C:\\Users\\user\\Documents\\GitHub\\TRANSPARENT-TRIANGLE\\data\\out.mkv - vn out.mp3 && del out.mkv")).c_str());
		}
		else {
			/* v does not contain any supported format */
			printf("\n Failed to download video ");
			printf(__text.c_str());
			printf("\n");
			return 1;
		}
		return 0;

}