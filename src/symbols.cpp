#include <iostream>
#include <windows.h>
#include <dbghelp.h>
#include <dia2.h>


const char* GetTagString(const DWORD tag) {
    switch (tag) {
        case SymTagNull:
            return "SymTagNull";
        case SymTagExe:
            return "SymTagExe";
        case SymTagCompiland:
            return "SymTagCompiland";
        case SymTagCompilandDetails:
            return "SymTagCompilandDetails";
        case SymTagCompilandEnv:
            return "SymTagCompilandEnv";
        case SymTagFunction:
            return "SymTagFunction";
        case SymTagBlock:
            return "SymTagBlock";
        case SymTagData:
            return "SymTagData";
        case SymTagAnnotation:
            return "SymTagAnnotation";
        case SymTagLabel:
            return "SymTagLabel";
        case SymTagPublicSymbol:
            return "SymTagPublicSymbol";
        case SymTagUDT:
            return "SymTagUDT";
        case SymTagEnum:
            return "SymTagEnum";
        case SymTagFunctionType:
            return "SymTagFunctionType";
        case SymTagPointerType:
            return "SymTagPointerType";
        case SymTagArrayType:
            return "SymTagArrayType";
        case SymTagBaseType:
            return "SymTagBaseType";
        case SymTagTypedef:
            return "SymTagTypedef";
        case SymTagBaseClass:
            return "SymTagBaseClass";
        case SymTagFriend:
            return "SymTagFriend";
        case SymTagFunctionArgType:
            return "SymTagFunctionArgType";
        case SymTagFuncDebugStart:
            return "SymTagFuncDebugStart";
        case SymTagFuncDebugEnd:
            return "SymTagFuncDebugEnd";
        case SymTagUsingNamespace:
            return "SymTagUsingNamespace";
        case SymTagVTableShape:
            return "SymTagVTableShape";
        case SymTagVTable:
            return "SymTagVTable";
        case SymTagCustom:
            return "SymTagCustom";
        case SymTagThunk:
            return "SymTagThunk";
        case SymTagCustomType:
            return "SymTagCustomType";
        case SymTagManagedType:
            return "SymTagManagedType";
        case SymTagDimension:
            return "SymTagDimension";
        default:
            return "Unknown";
    }
}



BOOL call_back(PSYMBOL_INFO info, ULONG size, PVOID ctx) {
    std::cout << "\n Name: " << info->Name << std::endl;
    std::cout << "     Address: 0x" << std::hex << info->Address << std::endl;
    std::cout << "     Size: " << info->Size << " bytes" << " - Value: " << info->Value << std::endl;
    std::cout << "     TagStr: " << GetTagString(info->Tag) << std::endl;
    std::cout << "     Reserved: " << info->Reserved << std::endl;
    std::cout << "     Scope: 0x" << info->Scope << " - NameLen: 0x" << info->NameLen << std::endl;
    std::cout << "     Flags: " << info->Flags << " - Tag: 0x" << info->Tag << std::endl;
    std::cout << std::endl;
    return TRUE;
}



void get_symbole(const char* path) {
    HANDLE h_proc = GetCurrentProcess();
    if (!SymInitialize(h_proc, nullptr, 0)) {
        std::cerr << "SymInit failed. Error: " << GetLastError() << std::endl;
        return;
    }

    const DWORD64 base_addr = SymLoadModule64(h_proc, nullptr, path, nullptr, 0, 0);

    if (!base_addr) {
        std::cerr << "File load failed. Error: " << GetLastError() << std::endl;
        SymCleanup(h_proc);
        CloseHandle(h_proc);
        return;
    }

    IMAGEHLP_MODULE modInfo;
    modInfo.SizeOfStruct = sizeof(IMAGEHLP_MODULE);

    if (SymGetModuleInfo64(h_proc, base_addr, &modInfo)) {
        std::cout << "Module: " << modInfo.ModuleName << std::endl;
        std::cout << "  Base: 0x" << std::hex << modInfo.BaseOfImage << std::dec << std::endl;
        std::cout << "  Size: " << modInfo.ImageSize << " bytes" << std::endl;
        std::cout << "  Loaded: " << modInfo.LoadedImageName << std::endl;
        std::cout << "  Type: " << modInfo.SymType << "\n" << std::endl;

        if (!SymEnumSymbols(h_proc, base_addr, nullptr, call_back, nullptr)) {
            std::cerr << "Enum symbols failed. Error: " << GetLastError() << std::endl;
        }
        std::cout << std::endl;
    } else {
        std::cerr << "Module info failed. Error: " << GetLastError() << std::endl;
    }

    SymUnloadModule64(h_proc, base_addr);
    SymCleanup(h_proc);
    CloseHandle(h_proc);
}