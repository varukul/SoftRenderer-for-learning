#pragma once
#include<Windows.h>
#include<memory>
#include<string>
#include<ostream>
#include"color.h"
#include"texture.h"
void generate_color_PPM(const char *filename, const int &w, const int &h, const std::vector<std::vector<color>>& mat);

bool getBmpData(const char *filepath, std::vector<std::vector<color>>& texc);

texture2d readBmp(const char *filepath);