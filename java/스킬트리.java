import java.util.*;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/49993
  스킬트리 
*/

class Solution {
    private char hasPriorSkill[] = new char[26];
    
    public void setHasPriorSkill(String skill) {
        Arrays.fill(hasPriorSkill, '0');
        char prev = skill.charAt(0);
        int len = skill.length();
        
        for(int i=1; i<len; ++i) {
            char c = skill.charAt(i);
            hasPriorSkill[c-'A'] = prev;
            prev = c;
        }
    }

    public boolean isIncrease(String skill_tree) {
        boolean isExist[] = new boolean[26];
        Arrays.fill(isExist, false);
        
        int cnt = skill_tree.length();
        for(int i=0; i<cnt; ++i) {
            char skill = skill_tree.charAt(i);
            if(!isValid(skill, isExist)) return false;
            isExist[skill-'A'] = true;
        }
        return true;
    }
    
    public boolean isValid(char skill, boolean isExist[]) {
        char current = skill;
        while(true) {
            current = hasPriorSkill[current-'A'];
            if(current == '0') break;
            if(isExist[current-'A'] == false) return false;
        }
        return true;
    }
    
    public int solution(String skill, String[] skill_trees) {
        int answer = 0;
        setHasPriorSkill(skill);
        
        int len = skill_trees.length;
        for(int i=0; i<len; ++i) {
            if(isIncrease(skill_trees[i])) answer++;
        }
        
        return answer;
    }
}
