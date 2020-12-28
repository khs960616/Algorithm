#include <string>
#include <vector>

using namespace std;    

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    int mv_size = moves.size();
    int grid_size = board.size();
    int prev = 0;
    vector<int> bucket;
    
    for(int i = 0; i < mv_size; i++){
        int move = (moves[i]-1);
        
        for(int j=0;j<grid_size;j++){
            if(board[j][move]==0) continue;
            
            int doll_num = board[j][move];
            board[j][move] = 0;
            
            if(!bucket.empty()) prev = bucket.back();
            else prev=0;
            
            if(prev != doll_num){
                bucket.push_back(doll_num);
            }
            else{
                answer+=2;
                bucket.pop_back();
            }
            break;
        }
    }
    return answer;
}
