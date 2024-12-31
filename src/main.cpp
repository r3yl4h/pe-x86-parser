#include <iostream>
#include <fstream>
#include <string>
#include "exp.hpp"


bool finder(const IMAGE_SECTION_HEADER& section, const IMAGE_DATA_DIRECTORY& idt_entry) {
    return idt_entry.VirtualAddress >= section.VirtualAddress &&
        idt_entry.VirtualAddress < section.VirtualAddress + section.SizeOfRawData;
}



void print_dos_h(IMAGE_DOS_HEADER dos_h) {
    std::cout << "DOS HEADER: " << std::endl;
    std::cout << "0x00: (uint16_t) Magic Number MZ: 0x" << std::hex << dos_h.e_magic << std::endl;
    std::cout << "0x02: (uint16_t) Bytes on last page of file: " << dos_h.e_cblp << std::endl;
    std::cout << "0x04: (uint16_t) Pages in file: " << dos_h.e_cp << std::endl;
    std::cout << "0x06: (uint16_t) Relocations: " << dos_h.e_crlc << std::endl;
    std::cout << "0x08: (uint16_t) Size of header in paragraphs: " << dos_h.e_cparhdr << std::endl;
    std::cout << "0x0a: (uint16_t) Minimum extra paragraphs needed: " << dos_h.e_minalloc << std::endl;
    std::cout << "0x0c: (uint16_t) Maximum extra paragraphs needed: " << dos_h.e_maxalloc << std::endl;
    std::cout << "0x0e: (uint16_t) Initial ss value: " << dos_h.e_ss << std::endl;
    std::cout << "0x10: (uint16_t) e_sp: Initial SP value: " << dos_h.e_sp << std::endl;
    std::cout << "0x12: (uint16_t) Checksum: " << dos_h.e_csum << std::endl;
    std::cout << "0x14: (uint16_t) Initial ip value: " << dos_h.e_ip << std::endl;
    std::cout << "0x16: (uint16_t) Initial cs value: " << dos_h.e_cs << std::endl;
    std::cout << "0x18: (uint16_t) File address of relocation table: " << dos_h.e_lfarlc << std::endl;
    std::cout << "0x1a: (uint16_t) e_ovno: Overlay number: " << dos_h.e_ovno << std::endl;
    std::cout << "0x1c: (uint16_t[4]) Reserved words: ";
    for (unsigned short e_re : dos_h.e_res) {
        std::cout << e_re << " ";
    }
    std::cout << std::endl;
    std::cout << "0x24: (uint16_t) OEM identifier: " << dos_h.e_oemid << std::endl;
    std::cout << "0x26: (uint16_t) e_oeminfo: OEM information: " << dos_h.e_oeminfo << std::endl;
    std::cout << "0x28: (uint16[10]) Reserved words2: ";
    for (unsigned short i : dos_h.e_res2) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "0x3c: (uint32_t) Pe header address: 0x" << dos_h.e_lfanew << std::endl;
}


int main(int argc, char* argv[]) {
    arg args;
    if (argc > 1) {
        args = parse_arg(argv, argc);
    }
    else {
        std::string path;
        std::cout << "Enter the path of your PE file: ";
        std::getline(std::cin, path);
        std::cout << std::endl;
        if (path == "exit" || path == "q" || path == "quit" || path.empty())
            return 0;

        args.filename = path;
    }

    std::ifstream file(args.filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }
    IMAGE_DOS_HEADER dos_h;
    file.read(reinterpret_cast<char*>(&dos_h), sizeof(IMAGE_DOS_HEADER));

    if (dos_h.e_magic != 0x5a4d) {
        std::cerr << "Not a valid DOS executable." << std::endl;
        return 1;
    }
    if (args.dos_h)
        print_dos_h(dos_h);

    file.seekg(dos_h.e_lfanew);
    parse_header(file, args);
    if (argc == 1) {
        std::string inp;
        std::cout << "\nget the symbol?(y/n): ";
        std::getline(std::cin, inp);
        if (inp == "yes"|| inp == "y")
            get_symbole(args.filename.c_str());
        main(argc, argv);
    }
    else if (args.symbol)
        get_symbole(args.filename.c_str());

    return 0;
}
