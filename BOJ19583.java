import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

/*
  https://www.acmicpc.net/problem/19583
  싸이버 개강 총회 
  구현, String 처리
  ---
  30분 
*/
public class BOJ19583 {
	
	private static int answer;
	private static int startTime, endTime, streamingEndTime;
	private static Map<String, List<Integer>> userInfos = new HashMap<>();
	
	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] tokens = br.readLine().split(" ");
		
		startTime = getTime(tokens[0]);
		endTime = getTime(tokens[1]);
		streamingEndTime = getTime(tokens[2]);
		
		String info;
		while((info = br.readLine()) != null) {
			tokens = info.split(" ");
			List<Integer> timeInfos = userInfos.getOrDefault(tokens[1], new ArrayList<>());
			timeInfos.add(getTime(tokens[0]));
			userInfos.put(tokens[1], timeInfos);
		}
		
		Set<String> keySet = userInfos.keySet();
		for(String key: keySet) {
			if(isAttendance(userInfos.get(key))) ++answer;
		}
		
		System.out.println(answer);
	}
	
	private static boolean isAttendance(List<Integer> chatLogs) {
		boolean start = false, end = false;
		
		for(Integer log: chatLogs) {
			if(log<=startTime) start = true;
			if(log>=endTime && log<=streamingEndTime) end = true;
		}
		return (start && end);
	}
	
	private static int getTime(String s) {
		int ret = 0;
		String[] tokens = s.split(":");
		ret = Integer.parseInt(tokens[0])*60 + Integer.parseInt(tokens[1]);
		return ret;
	}
}
