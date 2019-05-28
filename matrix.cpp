#include <iostream>
#include <math.h>
#include <type_traits>
#include "matrix.h"
using namespace std;

int main() {
    Matris<int> m1 = identity<int>(2);

    Matris<int> m2 = Matris<int>(2,2);
    m2(0,0) = 1;
    m2(0,1) = 0;
    m2(1,0) = 0;
    m2(1,1) = 1;

    std::cout << m1 << '\n';

    std::cout << m2 << '\n';

    if (m1 == m2) {
        std::cout << "true" << '\n';
    }else{
        std::cout << "false" << '\n';
    }


    return 0;
}
