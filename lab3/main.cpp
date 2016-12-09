
#include <iostream>
#include "systems.h"
#include "GaussJordanExclusion.h"
#include "GaussSeidelMethod.h"

using namespace std;


int main() {
	LinearSystem test1(system1::coeficients, system1::constantTerms, system1::systemSize);
	GaussJordanExclusion solver1;
	SystemSolution solution1 = solver1.solve(test1);

	cout << "Gauss Solution"<< endl;
	for( auto iter =  solution1.begin(); iter != solution1.end(); iter++ )
		cout << *iter << endl;

	LinearSystem test2(system2::coeficients, system2::constantTerms, system2::systemSize);
	GaussSeidelMethod solver2(1e-2);
	SystemSolution solution2 = solver2.solve(test2);

	cout << "\n\nSeidel Solution"<< endl;
	for( auto iter =  solution2.begin(); iter != solution2.end(); iter++ )
		cout << *iter << endl;

	return 0;
}