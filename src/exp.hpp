#ifndef pe-x86-parser_EXP_HPP
#define pe-x86-parser_EXP_HPP
#include <cstdint>
#include <fstream>
#include <vector>
#include <Windows.h>
#include "arg.h"




bool finder(const IMAGE_SECTION_HEADER&, const IMAGE_DATA_DIRECTORY&);
void parse_header(std::ifstream&, const arg& args);
void print_opt64(const IMAGE_OPTIONAL_HEADER64&);
void print_opt32(const IMAGE_OPTIONAL_HEADER32&);
std::vector<IMAGE_SECTION_HEADER> getSection(std::ifstream&, uint16_t, uint32_t, bool print_sec);
void get_export(const IMAGE_DATA_DIRECTORY&, const std::vector<IMAGE_SECTION_HEADER>&, std::ifstream&);
void get_import(const IMAGE_DATA_DIRECTORY&, const std::vector<IMAGE_SECTION_HEADER>&, uint16_t, std::ifstream&);
void get_symbole(const char* path);
void get_reloc_file(std::ifstream&, const IMAGE_DATA_DIRECTORY&, const std::vector<IMAGE_SECTION_HEADER>&);
void get_except_dir(const IMAGE_DATA_DIRECTORY&, std::vector<IMAGE_SECTION_HEADER>&, std::ifstream&);
arg parse_arg(char** argv, int argc);
void help();
#endif
