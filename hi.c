#include <stdio.h>
#include <windows.h>

int main(void) {

    STARTUPINFO si = { 0 };
    PROCESS_INFORMATION pi = { 0 };

    if(!CreateProcessW(L"C:\\Windows\\System32\\notepad.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("(-) failed to create process, error: %id", GetLastError());
        return EXIT_FAILURE;
    }

    MessageBox(
        NUL,
        L"My first message box!"
    );
    return  EXIT_SUCCESS;
}