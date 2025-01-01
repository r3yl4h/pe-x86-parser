#include <iostream>
#include <algorithm>
#include "exp.hpp"

void get_export(const IMAGE_DATA_DIRECTORY& edt_entry, const std::vector<IMAGE_SECTION_HEADER>& sectionv, std::ifstream& file) {
	if (edt_entry.VirtualAddress && edt_entry.Size) {
		const auto rsec = std::ranges::find_if(sectionv, [&](const IMAGE_SECTION_HEADER& sec) {
			return finder(sec, edt_entry);
			});

		IMAGE_EXPORT_DIRECTORY export_dir = {};
		const int pos_edt = static_cast<int>(edt_entry.VirtualAddress - rsec->VirtualAddress + rsec->PointerToRawData);
		file.seekg(pos_edt, std::ios::beg);
		file.read(reinterpret_cast<char*>(&export_dir), sizeof(IMAGE_EXPORT_DIRECTORY));
		std::cout << "\n-------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "Export Table Address: 0x" << std::hex << rsec->VirtualAddress << std::dec << std::endl;
		int pos_name = static_cast<int>(export_dir.Name - rsec->VirtualAddress + rsec->PointerToRawData);
		file.seekg(pos_name, std::ios::beg);
		char name[260] = {};
		file.read(name, 260);

		std::cout << "name: " << name << std::endl;
		std::cout << "Number of Functions: " << export_dir.NumberOfFunctions << std::endl;
		std::cout << "Number of Names: " << export_dir.NumberOfNames << std::endl;

		auto* addr_func = new uint32_t[export_dir.NumberOfFunctions];
		const int pos_funcptr = static_cast<int>(export_dir.AddressOfFunctions - rsec->VirtualAddress + rsec->PointerToRawData);
		file.seekg(pos_funcptr, std::ios::beg);
		file.read(reinterpret_cast<char*>(addr_func), 4 * export_dir.NumberOfFunctions);

		auto* addr_name = new uint32_t[export_dir.NumberOfNames];
		pos_name = static_cast<int>(export_dir.AddressOfNames - rsec->VirtualAddress + rsec->PointerToRawData);
		file.seekg(pos_name, std::ios::beg);
		file.read(reinterpret_cast<char*>(addr_name), 4 * export_dir.NumberOfNames);
		std::cout << "Export Func:\n";
		for (int i = 0; i < export_dir.NumberOfFunctions; i++) {
			const uint32_t addr_rva = addr_func[i];
			pos_name = static_cast<int>(addr_name[i] - rsec->VirtualAddress + rsec->PointerToRawData);
			file.seekg(pos_name, std::ios::beg);
			char func_name[260] = {};
			file.read(func_name, 260);
			std::cout << std::hex << "\tAddress : 0x" << addr_rva << " - Name : " << func_name << std::dec << std::endl;
		}
		delete[] addr_func;
		delete[] addr_name;
	}
}