#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <chrono>
#include <cassert>

using namespace std;

void test_main_diag() {
    Matrix invalid_matrix(4,7);
    try {
        invalid_matrix.setMainDiagonal(6);
        assert(false);
    }
    catch (exception&) {
        assert(true);
    }
    Matrix m(5, 5);
    m.setMainDiagonal(6);
    int i;
    for(i = 0; i < 5; i++) {
        assert(m.element(i, i) == 6);
    }
    Matrix m2(8, 8);
    m2.setMainDiagonal(10);
    for(i = 0; i < 8; i++) {
        assert(m2.element(i, i) == 10);
    }
}

int main() {
    chrono::time_point<chrono::system_clock>start_time = chrono::system_clock::now();
    test_main_diag();
    cout << "\nTest new functionality!\n" << endl;
	testAll();
	testAllExtended();
    chrono::time_point<chrono::system_clock>end_time = chrono::system_clock::now();
	cout << "Test End" << endl;
    cout << chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count() / 1000.0f << " seconds.\n\n";
	return 0;
}