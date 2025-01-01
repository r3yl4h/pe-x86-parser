#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cstdint>
#include <numeric>
#include <string>
#include <iomanip>
#include "exp.hpp"


std::vector<uint8_t> patch_long_name(uint32_t smptroffs, std::ifstream& file, std::vector<uint8_t> name_bytes) {
    if (const auto index = std::ranges::find(name_bytes, '/'); index != name_bytes.end()) {
        auto offset_str = std::string(index + 1, name_bytes.end());
        const auto cleaned_insn = std::accumulate(offset_str.begin(), offset_str.end(), std::string(), [](std::string acc, char c) {
            if (std::isdigit(c) || c == '-')
                acc.push_back(c);
            return acc;
        });
        const int offset = static_cast<int>(std::stoull(cleaned_insn));
        std::vector<uint8_t> table_string(256, 0);
        file.seekg(offset + smptroffs);
        file.read(reinterpret_cast<char*>(table_string.data()), 256);
        const auto name_length = std::ranges::find(table_string, 0) - table_string.begin();
        std::vector result(name_bytes.begin(), index);
        result.insert(result.end(), table_string.begin(), table_string.begin() + name_length);
        return result;
    }

    return name_bytes;
}


std::vector<IMAGE_SECTION_HEADER> getSection(std::ifstream &file, uint16_t section_num, uint32_t symbol_table_offs, bool print_s) {
    std::vector<IMAGE_SECTION_HEADER> sections;
    for (int i = 0; i < section_num; ++i) {
        IMAGE_SECTION_HEADER section;
        file.read(reinterpret_cast<char*>(&section), sizeof(IMAGE_SECTION_HEADER));
        sections.push_back(section);
    }
    if (print_s) {
        std::cout << "\n----------------------------------------------------------------------" << std::endl;
        std::cout << "SECTION TABLE:\n" << std::endl;
        std::cout << std::left
                  << std::setw(20) << "Name"
                  << std::setw(12) << "VSize"
                  << std::setw(12) << "VA"
                  << std::setw(18) << "SizeOfRawData"
                  << std::setw(18) << "PtrToRawData"
                  << std::setw(18) << "PtrToReloc"
                  << std::setw(20) << "Characteristics"
                  << std::endl;
        std::cout << std::string(120, '_') << std::endl;
    }

    for (const auto& sec : sections) {
        const std::vector name_og(sec.Name, sec.Name + sizeof(sec.Name));
        std::vector<uint8_t> name_byte = patch_long_name(symbol_table_offs, file, name_og);

        std::string section_name;
        for (const auto& byte : name_byte)
            section_name += static_cast<char>(byte);

        if (print_s) {
            std::cout << std::left
          << std::setw(20) << section_name
          << std::hex << std::showbase
          << std::setw(12) << sec.Misc.VirtualSize
          << std::setw(12) << sec.VirtualAddress
          << std::setw(18) << sec.SizeOfRawData
          << std::setw(18) << sec.PointerToRawData
          << std::setw(18) << sec.PointerToRelocations
          << std::setw(20) << sec.Characteristics
          << std::noshowbase << std::endl;
        }
    }

    std::cout << "\n";
    return sections;
}
