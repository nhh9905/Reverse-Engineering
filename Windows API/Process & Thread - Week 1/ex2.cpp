#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <string>
using namespace std;

// Hàm kết thúc tiến trình theo Process ID
bool TerminateByPID(DWORD processID) {
    // PROCESS_TERMINATE: quyền yêu cầu khi mở tiến trình
    // FALSE: ko cần kế thừa từ các tiến trình cha
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processID);

    if (hProcess == NULL) {
        cout << "Can't open process with PID: " << processID << ". Fault: " << GetLastError() << endl;
        return false;
    }

    // TerminateProcess: dùng để kết thúc 1 tiến trình
    if (TerminateProcess(hProcess, 0)) {
        cout << "Process PID " << processID << " has been ended." << endl;
        CloseHandle(hProcess);
        return true;
    } else {
        cout << "Can't end proces with PID: " << processID << ". Fault: " << GetLastError() << endl;
        CloseHandle(hProcess);
        return false;
    }
}

// Hàm tìm và kết thúc tiến trình theo tên Image
bool TerminateByImageName(const string& imageName) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        cout << "Can't take tasklist. Fault: " << GetLastError() << endl;
        return false;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hSnapshot, &pe32)) {
        cout << "Can't take info from first process. Fault: " << GetLastError() << endl;
        CloseHandle(hSnapshot);
        return false;
    }

    bool terminated = false;
    do {
        //stricmp: không phân biệt chữ hoa với chữ thường
        if (_stricmp(pe32.szExeFile, imageName.c_str()) == 0) {
            if (TerminateByPID(pe32.th32ProcessID)) {
                terminated = true;
            }
        }
    } while (Process32Next(hSnapshot, &pe32));
    CloseHandle(hSnapshot);
    
    if (!terminated)
        cout << "Can't find process with name: " << imageName << endl;
    return terminated;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Use: " << argv[0] << " [PID | IMAGENAME] [ProcessID | ImageName]" << endl;
        return 1;
    }
    string method = argv[1];
    if (method == "PID") {
        DWORD processID = atoi(argv[2]);
        TerminateByPID(processID);
    } else if (method == "IMAGENAME") {
        string imageName = argv[2];
        TerminateByImageName(imageName);
    } else {
        cout << "Invalid method. Only accept PID or IMAGENAME" << endl;
    }
    return 0;
}
//Command: ex2.exe PID process.PID
//         exe.exe IMAGENAME process.IMAGENAME