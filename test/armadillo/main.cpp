#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

typedef fmat matrix_t;

int main(int argc, char* argv[]) {

    matrix_t A = randu<matrix_t>(4,5);
    matrix_t B = randu<matrix_t>(4,5);

    cout << A * B.t() << endl;

    return 0;
}