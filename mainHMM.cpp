#include <iostream>
#include "HMM.h"
using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);

	HMM weather;

	for (int i = 0; i <= 5; i++)
	{
		cout << i << "¹øÂ°" << endl;

		for (int nLoop = 1; nLoop <= weather.mHiddenStateNumber; nLoop++)
		{
			cout << weather.mStartProbability[nLoop] << " ";
		}

		cout << endl << endl;;

		for (int nLoop1 = 1; nLoop1 <= weather.mHiddenStateNumber; nLoop1++)
		{
			for (int nLoop2 = 1; nLoop2 <= weather.mHiddenStateNumber; nLoop2++)
			{
				cout << weather.mHiddenStateSet.probability_matrix[nLoop1][nLoop2] << " ";
			}
			cout << endl;
		}

		cout << endl;

		for (int nLoop1 = 1; nLoop1 <= weather.mHiddenStateNumber; nLoop1++)
		{
			for (int nLoop2 = 1; nLoop2 <= weather.mObservableStateNumber; nLoop2++)
			{
				cout << weather.mObservableStateSet.probability_matrix[nLoop1][nLoop2] << " ";
			}
			cout << endl;
		}

		cout << endl;

		weather.BaumWelch();
	}
	
	return 0;
}