#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    int cSize = commands.size();
    for(int i=0;i<cSize;i++){
        vector<int> rangeSort;
        int start = commands[i][0]-1;
        int end = commands[i][1]-1;
        for(int j=start;j<=end;j++){
            rangeSort.push_back(array.at(j));
        }
        sort(rangeSort.begin(),rangeSort.end());
        answer.push_back(rangeSort.at(commands[i][2]-1));
    }
    return answer;
}
