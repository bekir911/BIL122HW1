#include <iostream>
using namespace std;

class holder
{
private:
	int num;
public:
	explicit holder(int p_num):num(p_num) {

	}

	int getnum() {
		return num;
	}
};

void shownum(holder h)
{
	int i = h.getnum();
	cout << "num: " << i << endl;
}

int main()
{
	//ornek1
	//shownum(42);

	//ornek2
	//holder k = holder(69);
	//shownum(k);
	holder a=holder (55);
	shownum(a);
	return 0;
}