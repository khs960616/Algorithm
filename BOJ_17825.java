import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/*
  https://www.acmicpc.net/problem/17825
  주사위 윷놀이
  구현, 시뮬레이션
  ---
  1. 문제에서 주어진 그래프를 Node 객체로 선언해서 먼저 만들어야한다.
  2. 각 턴마다 선택 가능한 모든 경우의 수를 시뮬레이션 해야한다.
*/
public class BOJ_17825 {

    private static Node startNode = new Node(0);
    private static Node endNode = new Node(40);
    private static int[] turns;
    private static int answer = 0;

    public static void main(String[] args) throws Exception {
        makeMap();
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        turns = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();

        Node[] players = new Node[] {startNode, startNode, startNode, startNode};
        simulation(players, 0, 0, 0);
        System.out.println(answer);
    }

    private static void simulation(Node[] players, int idx, int endPlayer, int cost) {
        if(endPlayer == 4 || idx == 10) {
            answer = Math.max(answer, cost);
            return;
        }

        for(int i=0; i<4; ++i) {
            Node playerNode = players[i];
            if(playerNode == null) continue;

            Node nextNode = moveNode(playerNode, turns[idx]);
            if(nextNode != null && nextNode.isUsed) continue;

            playerNode.isUsed = false;
            players[i] = nextNode;
            if(nextNode != null) {
                players[i].isUsed = true;
                simulation(players, idx+1, endPlayer, cost+players[i].score);
                players[i].isUsed = false;
            } else {
                simulation(players, idx+1, endPlayer+1, cost);
            }

            players[i] = playerNode;  // playerNode.isUsed만 true로 바꾸고, 실제 players[i]에 원상복구를 안시켜놔서 디버깅할 때 굉장히 오래걸림. 
            players[i].isUsed = true; // 순열 조합 문제 풀 때 항상 주의하며 풀자 .
        }
    }

    private static Node moveNode(Node current, int moveAmount) {
        Node ret = current;
        moveAmount -= 1;
        if(ret.isBlue) {
            ret = ret.nextBlue;
        } else {
            ret = ret.nextNode;
        }

        while(ret != null && moveAmount != 0) {
            ret = ret.nextNode;
            --moveAmount;
        }
        return ret;
    }

    private static void makeMap() {
        List<Node> blueNodes = new ArrayList<>();
        Node prev = endNode;
        for(int i=38; i>0; i-=2) {
            Node current = new Node(i);
            current.nextNode = prev;
            if(i%10 == 0) {
                current.isBlue = true;
                blueNodes.add(current);
            }
            prev = current;
        }
        startNode.nextNode = prev;

        Node centerNode = new Node(25);
        prev = centerNode;
        for(int i=30; i<40; i+=5) {
            prev.nextNode = new Node(i);
            prev = prev.nextNode;
        }
        prev.nextNode = endNode;

        int[][] tmp =  {{28, 27, 26}, {22, 24}, {13, 16, 19}};
        for(int i=0; i<3; ++i) {
            Node prevNode = new Node(tmp[i][0]);
            blueNodes.get(i).nextBlue = prevNode;
            for(int j=1; j<tmp[i].length; ++j) {
                prevNode.nextNode = new Node(tmp[i][j]);
                prevNode = prevNode.nextNode;
            }
            prevNode.nextNode = centerNode;
        }
    }

    static class Node {
        int score;
        boolean isBlue, isUsed;
        Node nextNode, nextBlue;

        Node(int score) {
            this.score = score;
        }
    }
}
