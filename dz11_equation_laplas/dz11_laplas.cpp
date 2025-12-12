#include <iostream>
#include "laplas.h"

using namespace std;

int main()
{   
    int N;
    cout << "Enter szie Grid N = ";
    cin >> N;
    grid g(N);
    double eps = 9999999.0;

    while( eps > g.get_eps() ) {
        eps = g.calc_laplas();
    }

    cout << "eps=" << eps << endl;
    g.print_grid();

    system("PAUSE");
    return 0;
}