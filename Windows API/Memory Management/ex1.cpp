#include <iostream>
#include <windows.h>
#define ll long long
#define success ERROR_SUCCESS

using namespace std;
wstring QueryRegistryValue(HKEY root, LPCWSTR subkey, LPCWSTR value_name) {
    HKEY key;
    DWORD type = 0, size = 0;
    wstring val;
    //RegOpenKeyExW: open reg key
    if (RegOpenKeyExW(root, subkey, 0, KEY_READ, &key) == success) {
        //RegQueryValueExW: take value of specified reg key
        if (RegQueryValueExW(key, value_name, nullptr, &type, nullptr, &size) == success) {
            //REG_SZ: address of exe
            if (type == REG_SZ) {
                wchar_t *buf = new wchar_t[size/sizeof(wchar_t)];
                //(LPBYTE)buf: pointer to buffer that receives the data
                if (RegQueryValueExW(key, value_name, nullptr, nullptr, (LPBYTE)buf, &size) == success)
                    val = buf;
                delete[] buf;
            }
        }
        //RegCloseKey: close handle to reg key
        RegCloseKey(key);
    }
    return val;
}
void SystemInfo() {
    //OS name
    wstring osName = QueryRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"ProductName");
    wcout << L"OS Name: " << osName << endl;
    //OS version
    wstring osVer = QueryRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"CurrentVersion");
    wcout << L"OS Version: " << osVer << endl;
    //Name of computer
    CHAR computer_name[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computer_name)/sizeof(computer_name[0]);
    //GetComputerNameA(pointer of buffer, pointer size of buf)
    if (GetComputerNameA(computer_name, &size))
        cout << "Host Name: " << computer_name << endl;
    //Processor Architecture
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    if (sysinfo.wProcessorArchitecture == 9)
        cout << "Processor Architecture: x64" << endl;
    //Physical Memory
    MEMORYSTATUSEX memory;
    memory.dwLength = sizeof(memory);
    if (GlobalMemoryStatusEx(&memory))
        wcout << L"Total Physical Memory: " << memory.ullTotalPhys/(1024*1024) << " MB" << endl;
}
int main() {
    freopen("a.out", "w", stdout);
    SystemInfo();
}