#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct ProcessInfo {
    // lưu trữ chuỗi ký tự Unicode
    wstring name;
    DWORD id;
};

bool cmp(const ProcessInfo &a, const ProcessInfo &b) {
    return a.name < b.name;
}

// hàm chuyển từ CHAR hoặc TCHAR sang wstring
wstring ConvertToWString(const TCHAR* str) {
    #ifdef UNICODE
        return wstring(str);
    #else
        return wstring(str, str + strlen(str));
    #endif
}

void ListProcesses() {
    //1 struct chứa thông tin về một process đang chạy trên hệ thống
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    //CreateToolhelp32Snapshot: tạo một snapshot của các tiến trình, thread, module
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    //failed
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        cout << "Can't make snapshot\n";
        return;
    }

    //Process32First: lấy thông tin của process đầu tiên từ snapshot
    if (!Process32First(hProcessSnap, &pe32)) {
        cout << "Can't take info of process\n";
        //free
        CloseHandle(hProcessSnap);
        return;
    }

    vector<ProcessInfo> process;
    do {
        process.push_back(ProcessInfo{ConvertToWString(pe32.szExeFile), pe32.th32ProcessID});
    } while (Process32Next(hProcessSnap, &pe32));
    CloseHandle(hProcessSnap);
    
    sort(process.begin(), process.end(), cmp);
    for (auto x:process) {
        //wide character: xuất chuỗi Unicode
        wcout << L"Image Name: " << x.name << L", PID: " << x.id << endl;
    }
}

int main() {
    freopen("a.out", "w", stdout);
    ListProcesses();
    return 0;
}