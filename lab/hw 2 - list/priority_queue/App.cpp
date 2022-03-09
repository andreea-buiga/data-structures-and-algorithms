#include <iostream>
#include "PriorityQueue.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <ctime>
#include <chrono>
#include <cassert>

using namespace std;

bool rel_1(TPriority p1, TPriority p2) {
    if (p1 <= p2) {
        return true;
    }
    else {
        return false;
    }
}

void test_merge_pq() {
    PriorityQueue pq_1(rel_1);
    assert(pq_1.isEmpty() == true);
    PriorityQueue pq_2(rel_1);
    pq_1.push(5, 5);
    pq_1.push(3, 3);
    pq_1.push(10, 10);
    pq_1.push(2, 2);
    pq_1.push(12, 12);

    pq_2.push(1, 22);
    pq_2.push(1, 1);
    pq_2.push(2, 1);
    pq_1.merge(pq_2);
    assert(pq_1.pop().second == 1);
    assert(pq_1.pop().second == 1);
    assert(pq_1.pop().second == 2);
}

int main() {
    chrono::time_point<chrono::system_clock>start_time = chrono::system_clock::now();
    test_merge_pq();
    cout << "test merge pq successful!\n" << endl;
	testAll();
	testAllExtended();
    chrono::time_point<chrono::system_clock>end_time = chrono::system_clock::now();
	cout << "End" << endl;
	cout << "\n\n";
    cout << chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count() / 1000.0f << " seconds.\n\n";
    return 0;
}
