////Bekir Öztürk
////19120205061
////BIL 122 Ödev-3

#include <iostream>
#include <vector>
#include <iomanip>
#include <chrono>

using namespace std;

//aþaðýdaki satýrlarý yoruma alarak kodunuzu farklý þekillerde test edebilirsiniz.
#define _TEST_ITERATIVE_
#define _TEST_RECURSIVE_

// Bu odevde global veya statik degisken tanimlanamaz!!!

/* Ozyinelemeli olarak zip zip kurbaganin kac farkli yoldan gittigini bulan fonksiyondur.
 * Bu fonksiyon icinde for ve while kullanamazsiniz ve en az bir kez recursiveFunction
 * fonksiyonu cagri yapilmalidir.
 */
long long recursiveFunction(int numberOfStones)
{
	if (1 == numberOfStones) {		//base case 1
		return 1;
	}
	else if (2 == numberOfStones) {	//base case 2
		return 2;
	}
	else if (3 == numberOfStones) {	//base case 3
		return 4;
	}
	else {	//if its not base case it goes into recursive
				//i wrote down for 5 and 6. then i realized how it works
				//if you have N stones to jump, you can jump 1, 2 or 3. after that you will have N-1, N-2 or N-3 stones. it keeps going on
				//you will get into new scenario every time
		return recursiveFunction(numberOfStones - 1) + recursiveFunction(numberOfStones - 2) + recursiveFunction(numberOfStones - 3);
	}
}

/* Yinelemeli olarak zip zip kurbaganin kac farkli yoldan gittigini bulan fonksiyondur.
 * Bu fonksiyon icinde for ve while dongusu kullanilmalidir.
 * Bu fonksiyon icinde baska bir fonksiyona (kendisi dahil) cagri yapilamaz.
 */
long long iterativeFunction(int numberOfStones)
{
	long long temp1 = { 1 };	//temp variables for base cases
	long long temp2 = { 2 };
	long long temp3 = { 4 };
	long long temp4 = { 7 };

	switch (numberOfStones) {	//base cases. no need to default
	case 1:
		return temp1;
	case 2:
		return temp2;
	case 3:
		return temp3;
	}

	for (int i = 0; i < numberOfStones - 3; ++i) {	//if its not base case it counts till it is. -3 comes from number of base cases
		temp4 = temp1 + temp2 + temp3;	//changing variables so it can carry on
		temp1 = temp2;
		temp2 = temp3;
		temp3 = temp4;
	}
	return temp4;
}



int main()
{
	const int MAX_NUMBER_OF_STONES{ 72 };

	cout << setfill(' ');

	cout.imbue(locale(""));

	for (auto i = 1; i < MAX_NUMBER_OF_STONES; ++i)
	{

#ifdef _TEST_ITERATIVE_
		{
			long long tempResult = { 0 };

			auto start = std::chrono::steady_clock::now();
			tempResult = iterativeFunction(i);
			auto stop = std::chrono::steady_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();


			cout << "iterative" << setw(4) << i << " -> " << tempResult << " ( " << duration << "us )\n";
		}
#endif

#ifdef _TEST_RECURSIVE_
		{
			long long tempResult = { 0 };

			auto start = std::chrono::steady_clock::now();
			tempResult = recursiveFunction(i);
			auto stop = std::chrono::steady_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

			cout << "recursive" << setw(4) << i << " -> " << tempResult << "\t( " << duration << "us )\n\n";
		}
#endif

	}

	return 0;
}
