import java.util.Scanner;

public class Main {
    public static void main(String args[]) {

        System.out.println("Welcome, enter the player names");

        @SuppressWarnings("resource")
        Scanner scanner = new Scanner(System.in);
        String player_1= scanner.next();
        String player_2 = scanner.next();
        GameController controller = new GameController(player_1, player_2);
        controller.play();
        controller.printBoard();
    }
}
