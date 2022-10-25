### 정규식 검색에 사용되는 객체
1. std::regex
2. std::smatch
3. std::ssub_match


### 정규식 검색에 사용되는 함수 
1. std::regex_match
```
Returns whether the target sequence matches the regular expression rgx. 

주어진 타겟(string 또는 char 시퀸스) 전체가 정의한 정규표현식과 일치하는 지 여부를 판단하는 함수이다.

return value는 정규표현식과 문자열 전체가 매칭되는지 여부를 true/false로 반환하다. 

https://cplusplus.com/reference/regex/regex_match/  매칭 시 사용할 flag 변수들은 다음에 정의되어있으므로 필요시 참고하여 사용
```

2. std::regex_serach
```
Returns whether some sub-sequence in the target sequence (the subject) matches the regular expression rgx.
문자열과 정규표현식이 주어졌을 때, 문자열 내부에 정규표현식과 matching되는 sub_string이 있는지 여부를 반환한다. 
return value는 문자열 내부에 정규표현식과 매칭되는 부분이 있는지 여부를 true/false로 반환하다. 
```

3. std::regex_replace
```
Makes a copy of the target sequence (the subject) with all matches of the regular expression rgx (the pattern) replaced by fmt (the replacement). 
문자열과 정규표현식이 주어졌을 때, 문자열 내부에 정규표현식과 matching되는 부분을 인자로 넣은 fmt로 변환한 string을 반환하는 함수이다.
```

4. std::regex_iterator
```
주어진 문자열에서 주어진 정규식과 매칭되는 단어들을 순차적으로 뽑아낼 수 있는 iterator이다. 
```

### Syntax 옵션들

regex 변수명("pattern", std::regex::icase);

icase를 옵션으로 넣을시 기본적으로 대소문자 구분 없이 패턴 매칭을 해준다.

https://cplusplus.com/reference/regex/
https://en.cppreference.com/w/cpp/regex/syntax_option_type
