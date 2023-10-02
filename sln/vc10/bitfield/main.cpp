#include <iostream>
#include "tbitfield.h"

using namespace std;

int main() {
	TBitField A(55);
	cout << A.GetMemIndex(54);
}