import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {

    private static int CONVERT_NUMBER = 32;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        char[] cs = br.readLine().toCharArray();

        StringBuilder sb = new StringBuilder();
        for(char c: cs) {
            if(c<97) c+=32;
            else c-=32;
            sb.append(c);
        }

        System.out.println(sb.toString());
    }
}
