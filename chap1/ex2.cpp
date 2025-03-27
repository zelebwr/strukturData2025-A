#include <iostream> 
#include <string>
using namespace std;

class mhs {
    string mhsName;

    public: 
    mhs(string name){
        mhsName = name;
        printName();
    }

    void setterName(string name){
        mhsName = name;
    }

    string getterName(){
        return mhsName;
    }

    void printName() {
        cout << "Nama Mahasiswa: " << mhsName << endl;
    }
};

int main() {
    mhs mhs1("Rahmat Budi");
    mhs1.setterName("Budi Rahmat");
    cout << "Nama Mahasiswa: " << mhs1.getterName() << endl;
    return 0;
}