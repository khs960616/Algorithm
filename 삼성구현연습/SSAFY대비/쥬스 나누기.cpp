#include<iostream>
using namespace std;
/*

모든 사람은 목이 마른 상태이기 때문에, 최대한의 쥬스를 마시고자 최선의 전략을 쓴다고 가정하자.
또한 이들은 서로 모르기 때문에, 담합 혹은 협력 등은 없다고 가정하자.

왜 난이도가 D3밖에 안되는지 모르겠다.
코드 자체는 너무나 간단하나, 사실 왜 저게 제일 합리적인 답인가에 대한 것은 아직도 이해하지 못함. 
https://koreascience.kr/article/JAKO201307153506285.pdf 여기 수식 봐도 모르겠음.. 

  이 떄 5명이 있다고 가정하자.
  두 번째 사람은 4/5만큼의 음료를 따를 수 있다.
  이 때 두 번째 사람은 1/5 보다 같거나 많은 양의 음료를 마시고자 할 것이다. 
  또한 4/5만큼의 음료로 최소한 3잔 이상의 잔 수를 만들어야, 자기 자신이 못 마시는 경우를 방지할 수 있을 것이다.
  이 때 두 번째 사람이 다른 경우의 수를 계산해서 4/15만큼을 따르게 되면,
  
  세 번째 사람은 8/15 만큼의 음료를 따를 수 있고, 음료를 어떻게 따르던지 간에, 이미 앞 선 두 사람이 선택한 2잔의 음료가 있으므로, 
  자신이 음료를 마실 수 있음은 보장이 된 상태이다.
  따라서 마실 수 있는 음료의 양을 늘리도록 최선의 선택을 할 것이다. 이 때 남은 음료를 4/15 만큼 따르면,
  
  세 번째 사람이 마실 수 있는 음료의 양은 네 번째 사람이 음료를 어떻게 따르느냐에 종속적이다. 
  (네 번째 사람이 4/15를 한 잔에 다 따르면 두 번쨰 사람과, 세번쨰사람은 최적의 선택을 한 것 일 수 있다.)
  ----
  
  그니까 내 생각은,  과반수가 이미 1/n 만큼을 잔에 따라 놨으면,
  그 이후의 사람들은 사실 1/n이상을 따르면 자기 자신이 더 많이 마실수도 있는 기회가 생기는데,
  이미(1/n 만큼 마시는게 보장되었으므로) 그러면 최대한 쥬스를 마시고자 한다면 앞서 다른 사람이 못먹게하는게,
  단순히 내가 마시는 음료수의 양만 고려한다면 더 합리적인 선택이 아닐까?  어려운것같다... 
*/

int main(int argc, char** argv) {
	int test_case;
	int T;
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case) {
		int n;
        cin >> n;
        
        cout << "#" << test_case;
        for(int i = n; i>0; --i) {
        	cout <<' ' << 1 << '/' << n;
        }
        cout << '\n';
	}
	return 0;
}
