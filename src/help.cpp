#include <iostream>

void help() {
    std::cout << "Usage: ./pe-x86-parser [OPTIONS]\n\n";
    std::cout << "Options:\n";
    std::cout << "  -all, --all              Activate all options.\n";
    std::cout << "  -d, -dos, --dos_header   Parse the DOS header of the file.\n";
    std::cout << "  -n, -nt, --nt_header     Parse the NT header of the file.\n";
    std::cout << "  -o, --optional_header    Parse the Optional header of the file.\n";
    std::cout << "  -e, edt, -export, \n";
    std::cout << "      --export             Parse the Export table.\n";
    std::cout << "  -i, iat, -import, \n";
    std::cout << "      --import             Parse the Import Address Table.\n";
    std::cout << "  -r, --reloc              Parse the Relocation table.\n";
    std::cout << "  -s, --symbol             Parse the Symbol table.\n";
    std::cout << "  -section, --section      Parse the Sections of the file.\n";
    std::cout << "  -pdata, --pdata, \n";
    std::cout << "      --except             Parse the Exception table.\n";
    std::cout << "\nExamples:\n";
    std::cout << "  ./pe-parser -all           Parse all available headers and tables.\n";
    std::cout << "  ./pe-parser -d -n -o       Parse DOS, NT, and Optional headers.\n";
}
