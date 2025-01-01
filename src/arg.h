#ifndef ARG_H
#define ARG_H
#include <string>

struct arg {
    std::string filename;
    bool dos_h;
    bool nt_h;
    bool opt_h;
    bool section;
    bool edt;
    bool iat;
    bool excpt;
    bool reloc;
    bool symbol;

    explicit arg(std::string file) : filename(std::move(file)), dos_h(true), nt_h(true),
          opt_h(true), section(true), edt(true), iat(true), excpt(false), reloc(false), symbol(false) {}

    explicit arg() : dos_h(true), nt_h(true), opt_h(true), section(true), edt(true), iat(true), excpt(false), reloc(false), symbol(false) {}

    void set_all_false() {
        this->dos_h = false;
        this->nt_h = false;
        this->opt_h = false;
        this->edt = false;
        this->iat = false;
        this->excpt = false;
        this->reloc = false;
        this->symbol = false;
        this->section = false;
    }

    void set_all_true() {
        this->dos_h = true;
        this->nt_h = true;
        this->opt_h = true;
        this->edt = true;
        this->iat = true;
        this->excpt = true;
        this->reloc = true;
        this->symbol = true;
        this->section = true;
    }
};
#endif //ARG_H
