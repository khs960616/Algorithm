#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> answers) {
    vector<int> answer;
    int size = answers.size();
    int result[3] = {0,0,0};
    
    vector<int> f_student = {1,2,3,4,5};
    vector<int> s_student = {2,1,2,3,2,4,2,5};
    vector<int> t_student = {3,3,1,1,2,2,4,4,5,5};
    vector<int>::iterator f_iter,s_iter,t_iter;
    
    f_iter = f_student.begin();
    s_iter = s_student.begin();
    t_iter = t_student.begin();
    
    for(int i = 0 ; i < size ; i++){
        if(f_iter == f_student.end()) f_iter = f_student.begin();
        if(s_iter == s_student.end()) s_iter = s_student.begin();
        if(t_iter == t_student.end()) t_iter = t_student.begin();
        if(answers[i]==*f_iter) result[0]++;
        if(answers[i]==*s_iter) result[1]++;
        if(answers[i]==*t_iter) result[2]++;
        
        f_iter++;
        s_iter++;
        t_iter++;
    }
 
    answer.push_back(1);
    
    for(int i=1;i<3;i++){
        if(result[answer.front()-1] > result[i]) continue;
        if(result[answer.front()-1] < result[i]) answer.clear();
        answer.push_back(i+1);
    }
    
    return answer;
}
