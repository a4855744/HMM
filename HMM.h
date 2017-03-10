#pragma once
#include <string>
#include <vector>

/*
 * struct : StateSet
 * 각 상태들의 정보를 담을수 있는 구조체
*/

struct StateSet
{
	/*
	 * name : 상태의 이름
	 * probability_matrix : 상태의 확률
	*/

	std::vector<std::string> name;
	std::vector<std::vector<double>> probability_matrix;
};

class HMM
{
	public:
		/*
		 * mHiddenStateNumber : 은닉상태들의 갯수
		 * mObservableStateNumber : 관찰상태들의 갯수
		 * mTimeNumber : 관찰열 지속시간
		 * *mStartProbability : start에서 전이 확률
		 * mHiddenStateSet : 은닉상태들의 정보
		 * mObservableStateSet : 관찰상태들의 정보
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
		 * 모델의 매개변수들을 입력받는다.
		*/

		HMM();

		double Forward(int t, int i);

		double Backward(int t, int i);

		//void Viterbi();

		/*
		 * e()
		 * 엡실론
		 * t일때 i이고 t+1일때 j일 확률
		*/
		double e(int t, int i, int j);

		/*
		 * r()
		 * 감마
		 * t에서 i에 있을 확률
		*/
		double r(int t, int i);

		void BaumWelch();
};