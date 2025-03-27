#include <iostream>
#include <string>
using namespace std;

class mhs {
    public: 
    string mhsName; 

    mhs(string name){
        mhsName = name;
    }

    void printName(){
        cout << "Nama Mahasiswa: " << mhsName << endl;
    }
};

int main() {
    mhs mhs1("Rahmat Budi");
    mhs1.printName();
    return 0;
}
