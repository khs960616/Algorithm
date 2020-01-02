#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
int main(void) {
	int n = 0, input = 0, check = 0;
	vector <char> result;
	stack <int> index;
	scanf("%d",&n); 
	scanf("%d",&input);
	int max = input; 
	input = 1;
	while (input<max+1) {
		result.push_back('+');
		index.push(input++);
	}
	index.pop();
	result.push_back('-');
	n--;
	while (n--) {
		scanf("%d", &input);
		if (input > max) {
			for (int i = max + 1; i < input + 1; i++) {
				index.push(i);
				result.push_back('+');
			}
			index.pop();
			result.push_back('-');
			max = input;
		}
		else {
			if (index.top() == input) {
				index.pop();
				result.push_back('-');
			}
			else
				check = 1;
		}
	}
	if (check) printf("NO");
	else 
		for (int i = 0; i < 2 * max; i++)
			printf("%c\n", result[i]);
	return 0;
}