#pragma once
#include <direct.h>
#include <string>
#include "VideoDownloader/python/pyhelper.hpp"
#include <regex>

inline void DownloadVideo(std::string url){
    START_PYTHON;
    // define values
    PyRun_SimpleString(std::string("URL_TO_DOWNLOAD = \"" + url + "\"").c_str());
    PyRun_SimpleString(
    R"END(
from pytube import YouTube
import os

# url input from user
yt = YouTube(URL_TO_DOWNLOAD)

# extract only audio
video = yt.streams.filter(only_audio=True).first()
# download the file
out_file = video.download(output_path="./Resources/data")

# save the file
base, ext = os.path.splitext(out_file)
new_file = base + '.mp3'
os.rename(out_file, new_file)
)END"
);
};
