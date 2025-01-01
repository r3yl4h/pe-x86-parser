#include <iostream>
#include <fstream>
#include "exp.hpp"

void parse_header(std::ifstream& file, const arg& args) {
    auto last_pos = file.tellg();
    IMAGE_NT_HEADERS file_header;
    file.read(reinterpret_cast<char*>(&file_header), sizeof(IMAGE_NT_HEADERS));
    if (!file) {
        std::cerr << "Error reading file header." << std::endl;
        return;
    }
    if (args.nt_h) {
        std::cout << "\nFILE HEADER: " << std::endl;
        std::cout << "0x00: (uint32_t) Pe signature: 0x" << file_header.Signature << std::endl;
        std::cout << "0x04: (uint16_t) Machine: 0x" << file_header.FileHeader.Machine << std::endl;
        std::cout << "0x06: (uint16_t) Number of Sections: " << std::dec << file_header.FileHeader.NumberOfSections << std::hex << std::endl;
        std::cout << "0x08: (uint32_t) TimeDateStamp: " << file_header.FileHeader.TimeDateStamp << std::endl;
        std::cout << "00xC: (uint32_t) PointerToSymbolTable: 0x" << file_header.FileHeader.PointerToSymbolTable << std::endl;
        std::cout << "0x10: (uint32_t) NumberOfSymbols: " << file_header.FileHeader.NumberOfSymbols << std::endl;
        std::cout << "0x14: (uint16_t) SizeOfOptionalHeader: " << file_header.FileHeader.SizeOfOptionalHeader << std::endl;
        std::cout << "0x16: (uint16_t) Characteristics: " << file_header.FileHeader.Characteristics << std::endl;
    }

    std::vector<IMAGE_SECTION_HEADER> sectionv;
    IMAGE_DATA_DIRECTORY data_dir[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
    if (file_header.FileHeader.Machine == 0x8664) {
        if (args.nt_h)
            print_opt64(file_header.OptionalHeader);

        sectionv = getSection(file, file_header.FileHeader.NumberOfSections, file_header.FileHeader.PointerToSymbolTable + file_header.FileHeader.NumberOfSymbols * 18, args.section);
        std::copy(file_header.OptionalHeader.DataDirectory, std::end(file_header.OptionalHeader.DataDirectory), data_dir);
    }
    else if (file_header.FileHeader.Machine == 0x14c) {
        IMAGE_NT_HEADERS32 file_header32;
        file.seekg(last_pos, std::ios::beg);
        file.read(reinterpret_cast<char*>(&file_header32), sizeof(IMAGE_NT_HEADERS32));
        if (args.nt_h)
            print_opt32(file_header32.OptionalHeader);

        sectionv = getSection(file, file_header.FileHeader.NumberOfSections, file_header.FileHeader.PointerToSymbolTable + file_header.FileHeader.NumberOfSymbols * 18, args.section);
        std::copy(file_header32.OptionalHeader.DataDirectory, std::end(file_header32.OptionalHeader.DataDirectory), data_dir);
    }else {
        std::cerr << "unsopported machine type : 0x" << std::hex << file_header.FileHeader.Machine << std::endl;
        return;
    }
    if (args.edt)
        get_export(data_dir[0], sectionv, file);

    if (args.iat)
        get_import(data_dir[1], sectionv, file_header.FileHeader.Machine, file);

    if (args.excpt)
        get_except_dir(data_dir[3], sectionv, file);
    if (args.reloc)
        get_reloc_file(file, data_dir[5], sectionv);
}