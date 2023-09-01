/**
* @author      Rafael Fuentes
* @version     1.0
*/
#ifndef __UTIL_H_GUARD__
#define __UTIL_H_GUARD__

#include <Windows.h>

#define EXIT_ON_FAILURE(exp) \
	if (FAILED(exp)) { return EXIT_FAILURE; } 

#define THROW_ON_FAILURE(exp) \
	if (FAILED(exp)) { return E_FAIL; } 

/**
 * @brief Ensure that the token has the SeBackupPrivilege privilege.
 * @return Wether the token has the SeBackupPrivilege privilege.
*/
_Success_(return == S_OK) _Must_inspect_result_
HRESULT AssertPrivilege(VOID) {

	// 1. Get handle to the token object.
	HANDLE hProcess = (HANDLE) -1;
	HANDLE hToken = INVALID_HANDLE_VALUE;
	OpenProcessToken(hProcess, TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &hToken);
	if (hToken == INVALID_HANDLE_VALUE)
		return E_FAIL;

	// 2. Adjust the token privileges if required.
	TOKEN_PRIVILEGES TokenPrivileges = { 0x00 };
	DWORD dwTokenLenght = 0x00;
	LUID LocalIdentifier = { 0x00 };


	if (LookupPrivilegeValueW(NULL, L"SeBackupPrivilege", &LocalIdentifier)) {
		TokenPrivileges.Privileges[0x0].Luid = LocalIdentifier;
		TokenPrivileges.Privileges[0x00].Attributes = SE_PRIVILEGE_ENABLED_BY_DEFAULT | SE_PRIVILEGE_ENABLED;
		TokenPrivileges.PrivilegeCount = 0x01;

		if (!AdjustTokenPrivileges(hToken, FALSE, &TokenPrivileges, 0x00, NULL, &dwTokenLenght)) {
			CloseHandle(hToken);
			return E_FAIL;
		}
	}

	// 3. Close handle and return.
	CloseHandle(hToken);
	return S_OK;
}
