#include <iostream>
using namespace std;

class CheckSyntax {
public:
	bool state = true;
	void checkSyntax(char *arr, bool &state);
	void printState(bool &state);
};

int main(void) {
	CheckSyntax check;
	int n = 0;
	cin >> n;
	char **arr= new char*[n];

	for (int i = 0; i < n; i++) {
		arr[i] = new char[200];
		cin >> arr[i];
	}

	for (int i = 0; i < n; i++) {
		check.checkSyntax(arr[i],check.state);
		check.printState(check.state);
	}

	for (int i = 0; i < n; i++) delete[] arr[i];
	delete[] arr;
	return 0;
}

void CheckSyntax::checkSyntax(char *arr, bool &state) {
	if (arr[0] == '\0') return;                  
	if (arr[0] == '0') {
		if (arr[1] == '1') checkSyntax(arr + 2, state);
		else {
			state = false;
			return;
		}
	}
	else if (arr[0] == '1') { 
		if (arr[1] == '0' && arr[2] == '0') {
			int temp = 3;
			while (arr[temp] == '0') temp += 1;
			if (arr[temp] == '\0') {
				state = false;
				return;
			} 
			else if (arr[temp] == '1') {
				int temp2 = temp;
				while (arr[temp + 1] == '1') temp += 1;

				if (temp != temp2) { 
					if (arr[temp + 1] == '0' && arr[temp + 2] == '0') temp -= 1;
				}
				checkSyntax(arr + temp + 1, state);
			}
		}
		else {
			state = false;
			return;
		}
	}
	return;
}
void CheckSyntax::printState(bool &state) {
	if (state) cout << "YES" << endl;
	else cout << "NO" << endl;
	state = true;
}