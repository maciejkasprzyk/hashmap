#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <chrono>
#include "HashMap.h"
#include <iostream>
#include <vector>

using namespace std;

// arg 1 -> path to txt file containing list of words
// arg 2 -> k size of array
// arg 3 -> n how many elements
// arg 4 -> random index to remove
int main(int argc, char *argv[]) {

    if (argc != 5) {
        cerr << "Usage:\n./main path n k random\n";
        return -1;
    }

    ifstream file(argv[1]);
    if (!file) {
        cerr << "Couldn't open file." << endl;
        return -1;
    }

    vector <string> words;
    string s;
    while (file >> s) {
        words.push_back(s);
    }

    int n;
    int k;
    int random;
    try {
        k = atoi(argv[2]);
        n = atoi(argv[3]);
        random = atoi(argv[4]);
    } catch (...) {
        cerr << "Usage:\n./main path n k random\n";
        return -1;
    }
    if (n > words.size()) {
        cerr << "To many elements, maximum is " << words.size() << ".\n";
        return -1;
    }

    HashMap<int> map(k);

    for (int i = 0; i < n; i++) {
        map[words[i]] = i;
    }



    auto start = std::chrono::system_clock::now();
    map.remove(words[random]);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout << elapsed_seconds.count() * 1000 << "\n"; // time in ms

    start = std::chrono::system_clock::now();
    map["on"] = 123;
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << elapsed_seconds.count() * 1000 << "\n"; // time in ms

    start = std::chrono::system_clock::now();
    for (auto it = map.begin(); it != map.end(); it++) {
        it->second += 1;
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << elapsed_seconds.count() * 1000 << "\n"; // time in ms

    return 0;
}