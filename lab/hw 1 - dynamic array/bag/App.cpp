#include "Bag.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>
#include <cassert>

using namespace std;

void test_no_of_max_frequency() {
    Bag b;
    assert(b.isEmpty() == true);
    assert(b.size() == 0);
    assert(b.elementsWithMaximumFrequency() == 0);
    int i;
    for(i = 0; i < 5; i++)
        b.add(1);
    for(i = 0; i < 5; i++)
        b.add(2);
    for(i = 0; i < 4; i++)
        b.add(0);
    assert(b.elementsWithMaximumFrequency() == 2);
    Bag b2;
    for(i = 0; i < 10; i++)
        b2.add(1);
    assert(b2.elementsWithMaximumFrequency() == 1);
    Bag b3;
    for(i = 0; i < 10; i++)
        b3.add(i + 1);
    assert(b3.elementsWithMaximumFrequency() == 10);
}

int main() {
    test_no_of_max_frequency();

    cout << "New implementation test over." << endl << endl;

	testAll();
	cout << "Short tests over." << endl << endl;
	testAllExtended();

	cout << "All test over." << endl;
    return 0;
}