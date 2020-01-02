#include <iostream>
#include <stack>
#define outputCheck -1 
using namespace std;
void clearBuffer(void) {
	while (getchar() != '\n');
}
int main(void) {
	int t;
	cin >> t;
	clearBuffer();
	stack<char> vps;
	for (; t > 0; t--) {
		while (char temp = getchar()) {
			if (temp == '\n')break;
			if (temp == '(')vps.push(temp);
			else {
				if (vps.empty()) {
					cout << "NO" << endl;
					vps.push(outputCheck);
					clearBuffer(); // clear stdin buffer 
					break;
				}
				else vps.pop();
			}
		}
		if (vps.empty())cout << "YES" << endl;
		else {
			if(vps.top()!=-1) cout << "NO" << endl;
			while (!vps.empty())vps.pop();
		}
	}
}