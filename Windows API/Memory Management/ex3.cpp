#include <iostream>
#include <filesystem>
using namespace std;
namespace fs = filesystem;
int main() {
    freopen("a.inp", "r", stdin);
    freopen("a.out", "w", stdout);
    string path;
    getline(cin, path);
    for (char x:path) {
        if (x == '\\')
            x = '/';
    }
    if (fs::exists(path) && fs::is_directory(path)) {
        cout << "File in directory " << path << endl;
        for (const auto& entry:fs::directory_iterator(path))
            cout << entry.path().filename().string() << endl;
    }
    else
        cout << "Not found directory";
}