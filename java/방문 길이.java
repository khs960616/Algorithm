import java.util.*;

/*
https://school.programmers.co.kr/learn/courses/30/lessons/49994
방문 길이
---
단순 구현 
*/
class Solution {
    public int solution(String dirs) {
        Player player = new Player();
        
        char[] dirictions = dirs.toCharArray();
        for(int i=0; i<dirictions.length; ++i) {
            player.move(dirictions[i]);
        }
        return player.getWalkDistance();
    }
    
    static class Player {
        private static final int MAX = 5;
        private static final int MIN = -5;
        
        private int x = 0;
        private int y = 0;
        private int walkDistance = 0;
        private boolean[][][] isVisit = new boolean[11][11][4];
            
        public void move(char c) {
            DIRECTION dir = Arrays.stream(DIRECTION.values())
                .filter(direction -> direction.dir == c)
                .findFirst().get();
            
            int nextX = x + dir.getX();
            int nextY = y + dir.getY();
            if(!isValid(nextX, nextY)) return;
            
            int[] edges = dir.getEdges();
            if(!isVisit[y+5][x+5][edges[0]]) {
                isVisit[y+5][x+5][edges[0]] = true;
                isVisit[nextY+5][nextX+5][edges[1]] = true;
                ++walkDistance;
            }
            this.x = nextX;
            this.y = nextY;
        }
        
        private boolean isValid(int x, int y) {
            return x>=-5 && x<=5 && y>=-5 && y<=5;
        }
        
        public int getWalkDistance() {
            return this.walkDistance;
        }
    }
    
    public enum DIRECTION {
        U(-1, 0, 'U'),
        D(1, 0, 'D'),
        R(0, 1, 'R'),
        L(0, -1, 'L');
        
        private final char dir;
        private final int x;
        private final int y;
        
        DIRECTION(int y, int x, char c) {
            this.x = x;
            this.y = y;
            this.dir = c;
        }
        
        public int getX() {
            return this.x;
        }
        
        public int getY() {
            return this.y;
        }
        
        public int[] getEdges() {
            int[] ret = {0, 0};
            //switch case 없이 좀 더 깔끔하게 인덱스 정보를 넘길 수 없을까 
            switch(this.dir) {
                case 'U':
                    ret[0] = 0;
                    ret[1] = 1;
                    break;
                case 'D':
                    ret[0] = 1;
                    ret[1] = 0;
                    break;
                case 'R':
                    ret[0] = 2;
                    ret[1] = 3;
                    break;
                case 'L':
                    ret[0] = 3;
                    ret[1] = 2;
                    break;
            }
            return ret;
        }
    }
}


/* 
다른 분 코드 

import java.util.*;

class Solution {
    public static int solution(String dirs) {
        Set<Road> visited = new HashSet<>();    //hashCode override해서 set으로 처리하는 방식 
        Road initRoad = new Road();
        for (char command : dirs.toCharArray()) {
            RoadMover.valueOf(String.valueOf(command)).command(initRoad.getStart())
                    .ifPresent(road -> {
                        initRoad.setStart(road.getEnd());
                        visited.add(road);
                    });
        }
        return visited.size();
    }
}

enum RoadMover implements RoadMoveStrategy {

    U(p -> Optional.ofNullable(Road.of(p, new Point(p.getY() - 1, p.getX())))),
    D(p -> Optional.ofNullable(Road.of(p, new Point(p.getY() + 1, p.getX())))),
    L(p -> Optional.ofNullable(Road.of(p, new Point(p.getY(), p.getX() - 1)))),
    R(p -> Optional.ofNullable(Road.of(p, new Point(p.getY(), p.getX() + 1))));

    public final RoadMoveStrategy robotCommand;

    RoadMover(RoadMoveStrategy robotCommand) {
        this.robotCommand = robotCommand;
    }

    @Override
    public Optional<Road> command(Point p) {
        return robotCommand.command(p);
    }

}

@FunctionalInterface
interface RoadMoveStrategy {

    Optional<Road> command(Point p);
}

class Road {
    private Point start;
    private Point end;

    private Road(Point start, Point end) {
        this.start = start;
        this.end = end;
    }

    public Road() {
        this.start = new Point(0, 0);
    }

    public static Road of(Point start, Point end) {
        return end.isSafe() ? new Road(start, end) : null;
    }

    public Point getStart() {
        return start;
    }

    public Point getEnd() {
        return end;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Road road = (Road) o;
        return start.equals(road.end) && end.equals(road.start) || start.equals(road.start) && end.equals(road.end);
    }

    @Override
    public int hashCode() {
        return Objects.hash(start.hashCode() * end.hashCode());
    }

    public void setStart(Point end) {
        this.start = end;
    }

}

class Point {

    private final int y;
    private final int x;

    private static final int MAX_BOUND = 5;

    public Point(int y, int x) {
        this.y = y;
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public int getX() {
        return x;
    }

    public boolean isSafe() {
        return Math.abs(y) <= MAX_BOUND && Math.abs(x) <= MAX_BOUND;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Point point = (Point) o;
        return y == point.y && x == point.x;
    }

    @Override
    public int hashCode() {
        return Objects.hash(y + x);
    }

}


*/
