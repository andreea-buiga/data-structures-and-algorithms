#include "ExtendedTest.h"
#include "ShortTest.h"
#include "Map.h"
#include "MapIterator.h"
#include <iostream>
#include <chrono>
#include <cassert>

using namespace std;

void test_key_set() {
    Map m;
    assert(m.isEmpty());
    int i;
    for(i = 0; i < 10; i++)
        m.add(i, i + 1);
    vector<TKey> keys = m.keySet();
    assert(keys.size() == 10);
    int elem = 0;
    for(i = 0; i < keys.size(); i++) {
        assert(elem == keys[i]);
        elem = elem + 1;
    }
}

int main() {
    chrono::time_point<chrono::system_clock>start_time = chrono::system_clock::now();
    test_key_set();
    cout << "\nTest new functionality!\n" << endl;
	testAll();
	testAllExtended();
    chrono::time_point<chrono::system_clock>end_time = chrono::system_clock::now();
	cout << "That's all!\n\n" << endl;
    cout << chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count() / 1000.0f << " seconds.\n\n";

	return 0;
}


