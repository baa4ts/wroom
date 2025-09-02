#ifndef DEF_HPP
#define DEF_HPP
// file: ./hook/def.hpp
// autor: baa4ts

#include <Windows.h>
#include <winternl.h>
#include <string>
#include <vector>
#include <algorithm>

const std::vector<std::wstring> procesosObjetivos = { L"brave.exe" };

// typedef para NtQuerySystemInformation
typedef NTSTATUS(NTAPI* NtQuerySystemInformation_t)(
	SYSTEM_INFORMATION_CLASS SystemInformationClass,
	PVOID SystemInformation,
	ULONG SystemInformationLength,
	PULONG ReturnLength
	);

// puntero original inicializado en NULL
NtQuerySystemInformation_t originalNtQuerySystemInformation = NULL;

#endif // DEF_HPP
