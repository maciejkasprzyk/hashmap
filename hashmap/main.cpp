#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "HashMap.h"
#include <iostream>

using namespace std;

int main() {

   HashMap <int> map(1000);

   ifstream file("ext.txt");
   if (!file)
   {
        cout<<"Couldnt open file."<<endl;
        return -1;
   }
   string s;
   while(file>>s){
      cout<<s<<endl;
   }
//
//   for (int i = 0 ; i < s.size() ; i ++){
//      cout<<s[i]<<":"<<(int)(unsigned char)(s[i])<<" ";
//   } cout<<endl;
//
//
//
//	for (int i = 0; i < 1000; i++) {
//         map[s] = i;
//   }

   return 0;
}