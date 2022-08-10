#include<bits/stdc++.h>
#define MAX 300000
using namespace std;

/*
  세그먼트 트리를 이용한 구간별 최대, 최소값 구하기 
*/
int nums[MAX][2];	// nums[i][0] -> 구간별 최소값, nums[i][1] -> 구간별 최대값 

void make_segement(int n, int leaf_cnt) {
    for(int i=leaf_cnt; i<leaf_cnt+n; ++i) {
        cin >> nums[i][0];    // 각 트리의 리프 노드에 입력된 배열 값을 입력한다.
        nums[i][1] =  nums[i][0]; // 각 리프노드는 1개의 원소구간만을 포함하므로 구간 최대값, 최소값 모두 자기 자신의 값이다. 
    }

  // 완전 이진트리 구성을 위해 더미 노드를 insert한다. 이때 min값은 INT_MAX, max값은 -1등 이후 연산에 영향을 미치지 않는 값을 대입 해야한다.
	for(int i=leaf_cnt+n; i<(leaf_cnt<<1); ++i) {
		nums[i][0] = INT_MAX;
		nums[i][1] = -1;
	}
  
  // 각 리프노드부터 구간 최대, 최소값을 계산하여 세그먼트 트리를 구성한다.
	for(int i=leaf_cnt-1; i != 0; --i) {
    	nums[i][0] = min(nums[i<<1][0], nums[i<<1|1][0]);
      nums[i][1] = max(nums[i<<1][1], nums[i<<1|1][1]);
    }
}

void change_op(int leaf_cnt) {
  int i, change;
  cin >> i >> change;
  i += leaf_cnt;

	nums[i][0] = nums[i][1] = change;
  
  while(i != 0) {
		int sibling = (i % 2 == 0) ? i+1 : i-1; // 리프노드가 수정된다면, 해당 리프노드와 형제노드를 이용해 조상 노드들의 값을 갱신해야한다.
    nums[i >> 1][0] = min(nums[sibling][0], nums[i][0]);
    nums[i >> 1][1] = max(nums[sibling][1], nums[i][1]);
    i >>= 1;
  }
}

void get_answer(int idx, int from, int to, int l, int r, pair<int, int>& answer) {
    if(r < from || l > to) return;  // 만일 현재 노드가 포함하는 구간 최대, 최소값의 범위가 구하고자 하는 범위와 겹치지 않는다면 더 이상 탐색할 필요가 없다. 
    if(l <=from && r >= to) { // 만일 현재 노드가 포함하는 구간 최대, 최소값이 구하고자하는 l, r 구간내에 포함되면 값을 갱신한다.
      answer.first = min(answer.first, nums[idx][0]);
      answer.second = max(answer.second, nums[idx][1]);
    	return;
    }
    
    // 만일 현재 노드가 구하고자하는 구간 l~r의 일부를 포함하는 경우, 각 구간을 줄여가며 탐색한다.
    int mid = (from + to) / 2;
    get_answer(idx << 1, from , mid, l, r, answer);
    get_answer(((idx << 1)|1),mid+1, to, l, r, answer);
}

int main(int argc, char** argv) {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
    
	int test_case;
	int T;
	cin>>T;
  
	for(test_case = 1; test_case <= T; ++test_case) {
    memset(nums, 0, sizeof(nums));
		int n, q;
    cin >> n >> q;

		int h = (int) ceil(log10(n) / log10(2));
		int leaf_cnt = (int) pow(2, h);   // 완전 이진 탐색 트리로 세그먼트 트리를 구성해야, 이분 탐색 처럼 재귀 구현이 용이하다.
    make_segement(n, leaf_cnt);
    cout << '#' << test_case;
    
    for(int i=0; i != q; ++i) {
      int op;
      cin >> op;
      if(op == 0) {
        change_op(leaf_cnt);
        continue;
      }
      
      int l = 0, r = 0;
      cin >> l >> r;
      pair<int, int> answer = {INT_MAX, -1};
      get_answer(1, 0, leaf_cnt-1, l, r-1, answer);
      cout << ' ' << answer.second - answer.first;
    }
    cout << '\n';
	}
	return 0;
}
