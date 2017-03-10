#pragma once
#include <string>
#include <vector>

/*
 * struct : StateSet
 * �� ���µ��� ������ ������ �ִ� ����ü
*/

struct StateSet
{
	/*
	 * name : ������ �̸�
	 * probability_matrix : ������ Ȯ��
	*/

	std::vector<std::string> name;
	std::vector<std::vector<double>> probability_matrix;
};

class HMM
{
	public:
		/*
		 * mHiddenStateNumber : ���л��µ��� ����
		 * mObservableStateNumber : �������µ��� ����
		 * mTimeNumber : ������ ���ӽð�
		 * *mStartProbability : start���� ���� Ȯ��
		 * mHiddenStateSet : ���л��µ��� ����
		 * mObservableStateSet : �������µ��� ����
		*/

		int mHiddenStateNumber;
		int mObservableStateNumber;
		int mTimeNumber;
		std::vector<double> mStartProbability;
		StateSet mHiddenStateSet;
		StateSet mObservableStateSet;
		std::vector<int> mInputSequence;
	public:
		/*
		 * HMM()
		 * ���� �Ű��������� �Է¹޴´�.
		*/

		HMM();

		double Forward(int t, int i);

		double Backward(int t, int i);

		//void Viterbi();

		/*
		 * e()
		 * ���Ƿ�
		 * t�϶� i�̰� t+1�϶� j�� Ȯ��
		*/
		double e(int t, int i, int j);

		/*
		 * r()
		 * ����
		 * t���� i�� ���� Ȯ��
		*/
		double r(int t, int i);

		void BaumWelch();
};