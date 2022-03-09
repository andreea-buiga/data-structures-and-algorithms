#include "Set.h"
#include "SetIterator.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <stack>
#include <iostream>
#include <chrono>
#include <cassert>

using namespace std;

void printS(Set& s){
    SetIterator it = s.iterator();
    while (it.valid()){
        std::cout << it.getCurrent() << " ";
        it.next();
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

void test_get_range() {
    Set set;
    assert(set.isEmpty());
    assert(set.getRange() == -1);
    set.add(4);
    assert(set.getRange() == 0);
    set.add(5);
    assert(set.size() == 2);
    assert(set.getRange() == 1);
    set.add(-9);
    assert(set.getRange() == 14);
    set.add(10);
    assert(set.getRange() == 19);
}

int main() {
    chrono::time_point<chrono::system_clock>start_time = chrono::system_clock::now();
    cout << "\nTest new functionality!\n" << endl;
    test_get_range();
	testAll();
	testAllExtended();
    chrono::time_point<chrono::system_clock>end_time = chrono::system_clock::now();
    cout << "\nThat's all!" << endl;
    cout << "\n\n";
    cout << chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count() / 1000.0f << " seconds.\n\n";

    return 0;
}



