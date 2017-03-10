#include <iostream>
#include "HMM.h"
using namespace std;

HMM::HMM()
{

	cout << "은닉상태 갯수 : ";
	cin >> mHiddenStateNumber;
	cout << mHiddenStateNumber << endl;

	cout << "관찰상태 갯수 : ";
	cin >> mObservableStateNumber;
	cout << mObservableStateNumber << endl;

	cout << "관찰지속시간 : ";
	cin >> mTimeNumber;
	cout << mTimeNumber << endl;

	cout << endl;

	mStartProbability.resize(mHiddenStateNumber + 1);

	mHiddenStateSet.name.resize(mHiddenStateNumber + 1);
	mHiddenStateSet.probability_matrix.resize(mHiddenStateNumber + 1);

	for (int nLoop = 1; nLoop <= mHiddenStateNumber; nLoop++)
	{
		mHiddenStateSet.probability_matrix[nLoop].resize(mHiddenStateNumber + 1);
	}

	mObservableStateSet.name.resize(mObservableStateNumber + 1);
	mObservableStateSet.probability_matrix.resize(mHiddenStateNumber + 1);

	for (int nLoop = 1; nLoop <= mHiddenStateNumber; nLoop++)
	{
		mObservableStateSet.probability_matrix[nLoop].resize(mObservableStateNumber + 1);
	}

	mInputSequence.resize(mTimeNumber + 1);

	for (int nLoop = 1; nLoop <= mHiddenStateNumber; nLoop++)
	{
		cout << nLoop << "번째 은닉상태 : ";
		cin >> mHiddenStateSet.name[nLoop];
		cout << mHiddenStateSet.name[nLoop] << endl;
	}

	cout << endl;

	for (int nLoop = 1; nLoop <= mObservableStateNumber; nLoop++)
	{
		cout << nLoop << "번째 관찰상태 : ";
		cin >> mObservableStateSet.name[nLoop];
		cout << mObservableStateSet.name[nLoop] << endl;
	}
	
	cout << endl;

	for (int nLoop = 1; nLoop <= mHiddenStateNumber; nLoop++)
	{
		cout << "초기 전이 확률 start -> " << mHiddenStateSet.name[nLoop] << " : ";
		cin >> mStartProbability[nLoop];
		cout << mStartProbability[nLoop] << endl;
	}

	cout << endl;

	for (int nLoop1 = 1; nLoop1 <= mHiddenStateNumber; nLoop1++)
	{
		for (int nLoop2 = 1; nLoop2 <= mHiddenStateNumber; nLoop2++)
		{
			cout << "은닉상태 전이 확률 " << mHiddenStateSet.name[nLoop1] << " -> " << mHiddenStateSet.name[nLoop2] << " : ";
			cin >> mHiddenStateSet.probability_matrix[nLoop1][nLoop2];
			cout << mHiddenStateSet.probability_matrix[nLoop1][nLoop2] << endl;
		}
	}

	cout << endl;

	for (int nLoop1 = 1; nLoop1 <= mHiddenStateNumber; nLoop1++)
	{
		for (int nLoop2 = 1; nLoop2 <= mObservableStateNumber; nLoop2++)
		{
			cout << "관찰상태 확률 " << mHiddenStateSet.name[nLoop1] << " -> " << mObservableStateSet.name[nLoop2] << " : ";
			cin >> mObservableStateSet.probability_matrix[nLoop1][nLoop2];
			cout << mObservableStateSet.probability_matrix[nLoop1][nLoop2] << endl;
		}
	}

	cout << endl;

	for (int nLoop = 1; nLoop <= mTimeNumber; nLoop++)
	{
		cout << nLoop << "번째 관찰상태열 : ";
		cin >> mInputSequence[nLoop];
		cout << mObservableStateSet.name[mInputSequence[nLoop]] << endl;
	}

	cout << endl;
}

double HMM::Forward(int t, int i)
{
	vector<double> ForwardProbability, newForwardProbability;

	ForwardProbability.resize(mHiddenStateNumber + 1);
	newForwardProbability.resize(mHiddenStateNumber + 1);

	for (int nLoop1 = 1; nLoop1 <= t; nLoop1++)
	{
		if (nLoop1 == 1)
		{
			for (int nLoop2 = 1; nLoop2 <= mHiddenStateNumber; nLoop2++)
			{
				ForwardProbability[nLoop2] = mStartProbability[nLoop2] * mObservableStateSet.probability_matrix[nLoop2][mInputSequence[nLoop1]];
			}
		}
		else
		{
			fill(newForwardProbability.begin(), newForwardProbability.end(), 0);

			for (int nLoop2 = 1; nLoop2 <= mHiddenStateNumber; nLoop2++)
			{
				for (int nLoop3 = 1; nLoop3 <= mHiddenStateNumber; nLoop3++)
				{
					newForwardProbability[nLoop2] = newForwardProbability[nLoop2] + (ForwardProbability[nLoop3] * mHiddenStateSet.probability_matrix[nLoop3][nLoop2] * mObservableStateSet.probability_matrix[nLoop2][mInputSequence[nLoop1]]);
				}
			}

			for (int nLoop2 = 1; nLoop2 <= mHiddenStateNumber; nLoop2++)
			{
				ForwardProbability[nLoop2] = newForwardProbability[nLoop2];
			}
		}
	}

	return ForwardProbability[i];
}

double HMM::Backward(int t, int i)
{
	vector<double> BackwardProbability, newBackwardProbability;

	BackwardProbability.resize(mHiddenStateNumber + 1);
	newBackwardProbability.resize(mHiddenStateNumber + 1);

	for (int nLoop1 = mTimeNumber; nLoop1 >= t; nLoop1--)
	{
		if (nLoop1 == mTimeNumber)
		{
			for (int nLoop2 = 1; nLoop2 <= mHiddenStateNumber; nLoop2++)
			{
				BackwardProbability[nLoop2] = 1;
			}
		}
		else
		{
			fill(newBackwardProbability.begin(), newBackwardProbability.end(), 0);

			for (int nLoop2 = 1; nLoop2 <= mHiddenStateNumber; nLoop2++)
			{
				for (int nLoop3 = 1; nLoop3 <= mHiddenStateNumber; nLoop3++)
				{
					newBackwardProbability[nLoop2] = newBackwardProbability[nLoop2] + (BackwardProbability[nLoop3] * mHiddenStateSet.probability_matrix[nLoop2][nLoop3] * mObservableStateSet.probability_matrix[nLoop3][mInputSequence[nLoop1 + 1]]);
				}
			}

			for (int nLoop2 = 1; nLoop2 <= mHiddenStateNumber; nLoop2++)
			{
				BackwardProbability[nLoop2] = newBackwardProbability[nLoop2];
			}
		}
	}

	return BackwardProbability[i];
}

double HMM::e(int t, int i, int j)
{
	double numerator = Forward(t, i) * mHiddenStateSet.probability_matrix[i][j] * mObservableStateSet.probability_matrix[j][mInputSequence[t + 1]] * Backward(t + 1, j);
	double denominator = 0;

	for (int i = 1; i <= mHiddenStateNumber; i++)
	{
		for (int j = 1; j <= mHiddenStateNumber; j++)
		{
			denominator = denominator + (Forward(t, i) * mHiddenStateSet.probability_matrix[i][j] * mObservableStateSet.probability_matrix[j][mInputSequence[t + 1]] * Backward(t + 1, j));
		}
	}

	return numerator / denominator;
}

double HMM::r(int t, int i)
{
	double numerator = Forward(t, i) * Backward(t, i);
	double denominator = 0;

	for (int j = 1; j <= mHiddenStateNumber; j++)
	{
		denominator = denominator + (Forward(t, j) * Backward(t, j));
	}

	return numerator / denominator;
}

void HMM::BaumWelch()
{
	for (int nLoop = 1; nLoop <= mHiddenStateNumber; nLoop++)
	{
		mStartProbability[nLoop] = r(1, nLoop);
	}

	for (int nLoop1 = 1; nLoop1 <= mHiddenStateNumber; nLoop1++)
	{
		for (int nLoop2 = 1; nLoop2 <= mHiddenStateNumber; nLoop2++)
		{
			double numerator = 0;
			double denominator = 0;

			for (int nLoop3 = 1; nLoop3 < mTimeNumber; nLoop3++)
			{
				numerator += e(nLoop3, nLoop1, nLoop2);
				denominator += r(nLoop3, nLoop1);
			}

			mHiddenStateSet.probability_matrix[nLoop1][nLoop2] = numerator / denominator;
		}
	}

	for (int nLoop1 = 1; nLoop1 <= mObservableStateNumber; nLoop1++)
	{
		for (int nLoop2 = 1; nLoop2 <= mHiddenStateNumber; nLoop2++)
		{
			double numerator = 0;
			double denominator = 0;

			for (int nLoop3 = 1; nLoop3 <= mTimeNumber; nLoop3++)
			{
				if (mInputSequence[nLoop3] == nLoop1)
				{
					numerator += r(nLoop3, nLoop2);
				}
				denominator += r(nLoop3, nLoop2);
			}

			mObservableStateSet.probability_matrix[nLoop2][nLoop1] = numerator / denominator;
		}
	}
}