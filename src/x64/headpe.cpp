#include <windows.h>
#include <iostream>

void print_opt64(const IMAGE_OPTIONAL_HEADER64 &head) {
    std::cout << "\nOPTIONAL HEADER64: " << std::endl;
    std::cout << "0x18: (uint16_t) Magic: 0x" << std::hex << head.Magic << std::endl;
    std::cout << "0x1A: (uinht8_t) MajorLinkerVersion: " << static_cast<int>(head.MajorLinkerVersion) << std::endl;
    std::cout << "0x1B: (uint16_t) MinorLinkerVersion: " << static_cast<int>(head.MinorLinkerVersion) << std::endl;
    std::cout << "0x1C: (uint32_t) SizeOfCode: " << head.SizeOfCode << std::endl;
    std::cout << "0x20: (uint32_t) SizeOfInitializedData: " << head.SizeOfInitializedData << std::endl;
    std::cout << "0x24: (uint32_t) SizeOfUninitializedData: " << head.SizeOfUninitializedData << std::endl;
    std::cout << "0x28: (uint32_t) AddressOfEntryPoint: " << head.AddressOfEntryPoint << std::endl;
    std::cout << "0x2C: (uint32_t) BaseOfCode: " << head.BaseOfCode << std::endl;
    std::cout << "0x34: (uint64_t) ImageBase: " << head.ImageBase << std::endl;
    std::cout << "0x38: (uint32_t) SectionAlignment: " << head.SectionAlignment << std::endl;
    std::cout << "0x3C: (uint32_t) FileAlignment: " << head.FileAlignment << std::endl;
    std::cout << "0x40: (uint16_t) MajorOperatingSystemVersion: " << head.MajorOperatingSystemVersion << std::endl;
    std::cout << "0x42: (uint16_t) MinorOperatingSystemVersion: " << head.MinorOperatingSystemVersion << std::endl;
    std::cout << "0x44: (uint16_t) MajorImageVersion: " << head.MajorImageVersion << std::endl;
    std::cout << "0x46: (uint16_t) MinorImageVersion: " << head.MinorImageVersion << std::endl;
    std::cout << "0x48: (uint16_t) MajorSubsystemVersion: " << head.MajorSubsystemVersion << std::endl;
    std::cout << "0x4A: (uint16_t) MinorSubsystemVersion: " << head.MinorSubsystemVersion << std::endl;
    std::cout << "0x4C: (uint32_t) Reserved1" << std::endl;
    std::cout << "0x50: (uint32_t) SizeOfImage: " << head.SizeOfImage << std::endl;
    std::cout << "0x54: (uint32_t) SizeOfHeaders: " << head.SizeOfHeaders << std::endl;
    std::cout << "0x58: (uint32_t) CheckSum: " << head.CheckSum << std::endl;
    std::cout << "0x5C: (uint16_t) Subsystem: " << head.Subsystem << std::endl;
    std::cout << "0x5E: (uint16_t) DllCharacteristics: " << head.DllCharacteristics << std::endl;
    std::cout << "0x60: (uint64_t) SizeOfStackReserve: " << head.SizeOfStackReserve << std::endl;
    std::cout << "0x68: (uint64_t) SizeOfStackCommit: " << head.SizeOfStackCommit << std::endl;
    std::cout << "0x70: (uint64_t) SizeOfHeapReserve: " << head.SizeOfHeapReserve << std::endl;
    std::cout << "0x78: (uint64_t) SizeOfHeapCommit: " << head.SizeOfHeapCommit << std::endl;
    std::cout << "0x80: (uint32_t) LoaderFlags: " << head.LoaderFlags << std::endl;
    std::cout << "0x84: (uint32_t) NumberOfRvaAndSizes: " << head.NumberOfRvaAndSizes << std::endl;
    std::cout << "0x88: (uint32_t) ExportDirectory VA: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress << std::endl;
    std::cout << "0x8C: (uint32_t) ExportDirectory Size: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size << std::endl;
    std::cout << "0x90: (uint32_t) ImportDirectory VA: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress << std::endl;
    std::cout << "0x94: (uint32_t) ImportDirectory Size: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size << std::endl;
    std::cout << "0x98: (uint32_t) ResourceDirectory VA: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress << std::endl;
    std::cout << "0x9C: (uint32_t) ResourceDirectory Size: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].Size << std::endl;
    std::cout << "0xA0: (uint32_t) ExceptionDirectory VA: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].VirtualAddress << std::endl;
    std::cout << "0xA4: (uint32_t) ExceptionDirectory Size: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].Size << std::endl;
    std::cout << "0xA8: (uint32_t) SecurityDirectory VA: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].VirtualAddress << std::endl;
    std::cout << "0xAC: (uint32_t) SecurityDirectory Size: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].Size << std::endl;
    std::cout << "0xB0: (uint32_t) BaseRelocationTable VA: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress << std::endl;
    std::cout << "0xB4: (uint32_t) BaseRelocationTable Size: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size << std::endl;
    std::cout << "0xB8: (uint32_t) DebugDirectory VA: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].VirtualAddress << std::endl;
    std::cout << "0xBC: (uint32_t) DebugDirectory Size: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size << std::endl;
    std::cout << "0xC0: (uint32_t) ArchitectureSpecificData VA: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_ARCHITECTURE].VirtualAddress << std::endl;
    std::cout << "0xC4: (uint32_t) ArchitectureSpecificData Size: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_ARCHITECTURE].Size << std::endl;
    std::cout << "0xC8: (uint32_t) RVAofGP VA: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_GLOBALPTR].VirtualAddress << std::endl;
    std::cout << "0xCC: (uint32_t) RVAofGP Size: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_GLOBALPTR].Size << std::endl;
    std::cout << "0xD0: (uint32_t) TLSDirectory VA: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress << std::endl;
    std::cout << "0xD4: (uint32_t) TLSDirectory Size: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].Size << std::endl;
    std::cout << "0xD8: (uint32_t) LoadConfigurationDirectory VA: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].VirtualAddress << std::endl;
    std::cout << "0xDC: (uint32_t) LoadConfigurationDirectory Size: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG].Size << std::endl;
    std::cout << "0xE0: (uint32_t) BoundImportDirectoryinheaders VA: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress << std::endl;
    std::cout << "0xE4: (uint32_t) BoundImportDirectoryinheaders Size: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].Size << std::endl;
    std::cout << "0xE8: (uint32_t) ImportAddressTable VA: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress << std::endl;
    std::cout << "0xEC: (uint32_t) ImportAddressTable Size: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].Size << std::endl;
    std::cout << "0xF0: (uint32_t) DelayLoadImportDescriptors VA: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT].VirtualAddress << std::endl;
    std::cout << "0xF4: (uint32_t) DelayLoadImportDescriptors Size: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT].Size << std::endl;
    std::cout << "0xF8: (uint32_t) COMRuntimedescriptor VA: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress << std::endl;
    std::cout << "0xFC: (uint32_t) COMRuntimedescriptor Size: " << head.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].Size << std::endl;
}