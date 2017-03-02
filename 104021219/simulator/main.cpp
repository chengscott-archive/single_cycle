#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream dimage("dimage.bin", ios::in | ios::binary),
            iimage("iimage.bin", ios::in | ios::binary);
    int v;
    iimage.read((char *) &v, sizeof(int));
    cout << v << endl;
    return 0;
}
