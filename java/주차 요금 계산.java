import java.util.*;

/*
  https://school.programmers.co.kr/learn/courses/30/lessons/92341
  2022 KAKAO BLIND RECRUITMENT
  ---
  구현..
*/

class Solution {
    // 차량 번호는 0~9999로 총 10^4이므로 레드블랙트리를 사용해도 큰 지장이 없다고 판단, 오름차순으로 정렬된 결과 만들어야하므로 TreeMap 선택 
    private final Map<Integer, Record> recordsMap = new TreeMap<>();
    
    public int[] solution(int[] fees, String[] records) {
        int[] answer = {};
        
        Record.setFees(fees);
        Arrays.stream(records).forEach(record->{
            String[] tokens = record.split(" ");
            Integer key = Integer.parseInt(tokens[1]);
          
            //putIfAbsent는 이미 차량번호로 객체가 생성되었다면, new Record(k)로 매번 사용하지 않는 새 객체를 생성하므로 computeIfAbsent 사용
            Record rc = recordsMap
                .computeIfAbsent(key, (k)->new Record(k));  
            
            if(tokens[2].equals("IN")) rc.setStartTime(tokens[0]);
            else rc.addAccumulate(tokens[0]);
        });
        
        answer = recordsMap.values().stream().mapToInt(Record::getFee).toArray();
        return answer;
    }
    
    static class Record{
        // 사실상 하나의 클래스에서 공유해야되는 값이므로 클래스 멤버로 선언 
        private static int[] fees = new int[0];
        private int startTime;  // 마지막 입차 시간을 나타낸다.
        private int carNumber;  // 차량번호 
        private int accumulate = 0; // 누적된 주차시간
        private boolean isFinish = false; // 누적시간 계산이 완전히 끝났는지 여부를 나타내는 상태변수 
        
        Record(){};
        Record(int number) {
            this.carNumber = number;
        }
        
        public static void setFees(int[] info) {
            fees = Arrays.copyOf(info, info.length);
        }
        
        public void setStartTime(String time) {
            this.startTime = convertTimeToInt(time);
            this.isFinish = false;  // 함수명에서 isFinish라는 상태변수값도 같이 변함을 나타내는게 좀 더 나았을까? 사=
        }
        
        public void addAccumulate(String time) {
            int endTime = convertTimeToInt(time);
            this.accumulate += (endTime - startTime);
            this.isFinish = true;
        }
        
        public int getFee() {
            if(!this.isFinish) {
                this.accumulate += ((23*60+59) - startTime);
            }
            
            int ret = fees[1];
            if(this.accumulate > fees[0]) {
                ret += Math.ceil((this.accumulate-fees[0])/(float)fees[2]) * fees[3];
            }
            return ret;
        }
        
        private static int convertTimeToInt(String time) {
            int[] timeInfos = Arrays.stream(time.split(":"))
                .mapToInt(Integer::parseInt).toArray();
            return timeInfos[0] * 60 + timeInfos[1];
        }
    }
}
