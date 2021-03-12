#include <iostream>
using namespace std;
class MinimumMultiplication{
public:
	int matrixSize[7]={5,2,3,4,6,7,8};
	int minimumMul[6][6]={0,};

	void initMinimumMul(void);
	void printMinimumMul(void);
};

void MinimumMultiplication::initMinimumMul(void){
	for(int i=0 ; i<6 ; i++) minimumMul[i][i]=0; //주 대각선 성분은 모두 0으로 초기화
	//각 Dp가 진행되는 과정에서, k가 i~j-1까지의 범위에서 [i][k] [k+1][j]를 이용하기 위해서는, 이전 단계의 대각선 성분이 필요하다.
	for(int diagonal=1 ; diagonal<6 ; diagonal++){ 
		for(int i=0 ; i<6-diagonal ; i++){
			int j=i+diagonal;
			for(int k=i ; k<j ; k++){
				int temp=minimumMul[i][k]+minimumMul[k+1][j];
				int addMulTime = matrixSize[i]*matrixSize[k+1]*matrixSize[j+1];
				temp += addMulTime;
				if(k==i || temp < minimumMul[i][j]) minimumMul[i][j]=temp;
			}
		}
	}
}
void MinimumMultiplication::printMinimumMul(void){
	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++){
			cout << minimumMul[i][j] << '\t';
		}
		cout << endl;
	}
}
int main(void){
	MinimumMultiplication test;
	test.initMinimumMul();
	test.printMinimumMul();
	return 0;
}
