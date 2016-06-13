#include <iostream>
#include"Expr.h"
using namespace std;

int main()
{
	Expr t = Expr("*", Expr("-", 5), Expr("+", 3, 4));
	cout << t << " = " << t.eval() << endl;
	cout << "((-5)*(3+4)) = -35" << endl;

	t = Expr("*", t, t);
	cout << t << " = " << t.eval() << endl;
	cout << "(((-5)*(3+4))*((-5)*(3+4))) = 1225" << endl;
	system("pause");
	return 0;
}
