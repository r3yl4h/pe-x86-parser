#include <algorithm>
#include <iostream>
#include <vector>
#include "exp.hpp"


std::string get_reloc_name(const uint16_t typ) {
    switch (typ) {
        case IMAGE_REL_BASED_ABSOLUTE: return "IMAGE_REL_BASED_ABSOLUTE";
        case IMAGE_REL_BASED_HIGH: return "IMAGE_REL_BASED_HIGH";
        case IMAGE_REL_BASED_LOW: return "IMAGE_REL_BASED_LOW";
        case IMAGE_REL_BASED_HIGHLOW: return "IMAGE_REL_BASED_HIGHLOW";
        case IMAGE_REL_BASED_HIGHADJ: return "IMAGE_REL_BASED_HIGHADJ";
        case IMAGE_REL_BASED_MIPS_JMPADDR: return "IMAGE_REL_BASED_MIPS_JMPADDR";
        case IMAGE_REL_BASED_DIR64: return "IMAGE_REL_BASED_DIR64";
        default: return "";
    }
}

void get_reloc_file(std::ifstream& file, const IMAGE_DATA_DIRECTORY& reloc_dir, const std::vector<IMAGE_SECTION_HEADER>& sections) {
    if (reloc_dir.Size && reloc_dir.VirtualAddress) {
        auto rsec = std::ranges::find_if(sections, [&](const IMAGE_SECTION_HEADER& sec) {
            return finder(sec, reloc_dir);
            });
        std::cout << "----------------------------------------------------------------------" << std::endl;
        std::cout << "RELOC TABLE:\n" << std::endl;
        const int pos_file = static_cast<int>(reloc_dir.VirtualAddress - rsec->VirtualAddress +rsec->PointerToRawData);
        file.seekg(pos_file, std::ios::beg);

        int pt = 0;
        while (pt < reloc_dir.Size) {
            IMAGE_BASE_RELOCATION reloc;
            file.read(reinterpret_cast<char*>(&reloc), sizeof(IMAGE_BASE_RELOCATION));

            const int size_entry = static_cast<int>((reloc.SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / 2);
            auto* rel_entry = new uint16_t[size_entry];
            file.read(reinterpret_cast<char*>(rel_entry), size_entry * 2);

            for (int i = 0; i < size_entry; i++) {
                const uint16_t rva = rel_entry[i] & 0xfff;
                const uint16_t typ = rel_entry[i] >> 12;
                std::cout << "\trva : 0x"  << std::hex << rva + reloc.VirtualAddress << " - relc type : " << get_reloc_name(typ) << std::endl;
            }

            delete[] rel_entry;
            pt += static_cast<int>(reloc.SizeOfBlock);
        }
    }
}

