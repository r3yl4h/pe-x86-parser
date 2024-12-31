#include "exp.hpp"
#include <iostream>



void get_except_dir(const IMAGE_DATA_DIRECTORY& pdata, std::vector<IMAGE_SECTION_HEADER>& sections, std::ifstream& file) {
    if (pdata.VirtualAddress && pdata.Size) {
        const auto rsec = std::ranges::find_if(sections, [&](const IMAGE_SECTION_HEADER& sec) {
            return finder(sec, pdata);
        });

        const int pos = static_cast<int>(pdata.VirtualAddress - rsec->VirtualAddress + rsec->PointerToRawData);
        file.seekg(pos, std::ios::beg);
        const auto count_elem = pdata.Size / sizeof(IMAGE_RUNTIME_FUNCTION_ENTRY);
        std::cout << "\nEXCEPT DIRECTORY: " << std::endl;

        for (int i = 0; i < count_elem; i++) {
            IMAGE_RUNTIME_FUNCTION_ENTRY entry;
            file.read(reinterpret_cast<char*>(&entry), sizeof(IMAGE_RUNTIME_FUNCTION_ENTRY));

            std::cout << "Entry " << i + 1 << ": "
                      << "BeginAddress=0x" << std::hex << entry.BeginAddress << ", "
                      << "EndAddress=0x" << entry.EndAddress << ", "
                      << "UnwindInfoAddress=0x" << entry.UnwindInfoAddress << std::dec << "\n";
        }
    }
}