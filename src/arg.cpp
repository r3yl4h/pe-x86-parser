#include "exp.hpp"
#include <iostream>

arg parse_arg(char *argv[], const int argc) {
    arg result(argv[1]);
    if (const std::string args = argv[1]; args == "--help" || args == "-h") {
        help();
        exit(0);
    }

    if (argc > 2)
        result.set_all_false();



    for (int i = 2; i < argc; ++i) {
        if (std::string arg = argv[i]; arg == "-all" || arg == "--all") {
            result.set_all_true();
            break;
        }else if (arg == "-d" || arg == "-dos" || arg == "--dos_header") {
            result.dos_h = true;
        }else if (arg == "-n" || arg == "-nt" || arg == "--nt_header") {
            result.nt_h = true;
        } else if (arg == "-o" || arg == "--optional_header") {
            result.opt_h = true;
        } else if (arg == "-e" || arg == "edt" || arg == "-export" || arg == "--export") {
            result.edt = true;
        } else if (arg == "-i" || arg == "iat" || arg == "-import" || arg == "--import") {
            result.iat = true;
        } else if (arg == "-r" || arg == "--reloc") {
            result.reloc = true;
        } else if (arg == "-s" || arg == "--symbol") {
            result.symbol = true;
        } else if (arg == "-section" || arg == "--section") {
            result.section = true;
        }else if (arg == "-pdata" || arg == "--pdata" || arg == "--except") {
            result.excpt = true;
        }
        else {
            std::cerr << "unknow option : " << arg << std::endl;
        }
    }
    return result;
}
