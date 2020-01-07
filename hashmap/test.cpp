#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <chrono>
#include "HashMap.h"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {

    HashMap<int> map(1000);

    try{
        map.remove("on");
    }
    catch(...){
        cout<<"test1 - ok"<<endl;
    }

    map["on"] = 1;
    map["ona"] = 2;
    map["ono"] = 3;
    map["oni"] = 4;
    if(map["on"] == 1){
        cout<<"test2 - ok"<<endl;
    }

    map.remove("ona");
    if(map.getSize() == 3){
        cout<<"test3 - ok"<<endl;
    }


    for (auto it = map.begin(); it != map.end(); it++) {
        cout<< it->first << " "<< it->second <<endl;
    }

    try{
//        map["ona"] stworzyło by nowy element o wartości 0
        int a = map.valueOf("ona");
        cout<<a;
    }
    catch(...){
        cout<<"test4 - ok"<<endl;
    }

    return 0;
}