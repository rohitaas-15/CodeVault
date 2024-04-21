
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class GameController {
    Board board;
    Queue<Player> players = new LinkedList<>();
    SymbolFactory factory = new SymbolFactory();
    Symbol X, O;

    GameController(String player_1, String player_2) {
        board = new Board(3);
        X = factory.getSymbol('X');
        O = factory.getSymbol('O');

        Player Player_1 = new Player(player_1, O);
        Player Player_2 = new Player(player_2, X);
        O.setPlayer(Player_1);
        X.setPlayer(Player_2);

        players.add(Player_1);
        players.add(Player_2);
    }

    public void play() {
        while (!isWinner(players.peek().getSymbol()) && !isGameDraw()) {
            players.add(players.peek());
            players.remove();

            @SuppressWarnings("resource")
            Scanner scanner = new Scanner(System.in);

            System.out.println(players.peek().getName() + ", Enter location of the next symbol");
            printBoard();
            int row = scanner.nextInt();
            int column = scanner.nextInt();

            if (row<0 || row>=board.dimension || column<0 || column>=board.dimension || board.getBoard().get(row).get(column) != null ) {
                System.out.println("Please enter a valid location!");
                players.add(players.peek());
                players.remove();
                continue;
            }

            board.fillSquare(row, column, players.peek().getSymbol());
        }

        if(isGameDraw())
        {
            System.out.println("The Game is Drawn! Well played to the players");
            return ;
        }
        System.out.println(players.peek().getName() + " Wins! Congratulations!");
    }

    public boolean isWinner(Symbol symbol) {
        // check for row
        int dimension = board.getDimension();
        boolean isWinner = false;
        for (int row = 0; row < dimension; row++) {
            boolean rowSatisfies = true;
            for (int column = 0; column < dimension; column++) {
                if (board.getBoard().get(row).get(column) == null
                        || board.getBoard().get(row).get(column).getSymbolChar() != symbol.getSymbolChar()) {
                    rowSatisfies = false;
                    break;
                }
            }
            if (rowSatisfies) {
                isWinner |= true;
                break;
            }
        }

        // check for column
        for (int column = 0; column < dimension; column++) {
            boolean colSatisfies = true;
            for (int row = 0; row < dimension; row++) {
                if (board.getBoard().get(row).get(column) == null
                        || board.getBoard().get(row).get(column).getSymbolChar() != symbol.getSymbolChar()) {
                    colSatisfies = false;
                    break;
                }
            }
            if (colSatisfies == true) {
                isWinner |= true;
                break;
            }
        }

        // check for right diagonal
        boolean diagonalSatisfies = true;
        for (int row = 0; row < dimension; row++) {
            if (board.getBoard().get(row).get(row) == null
                    || board.getBoard().get(row).get(row).getSymbolChar() != symbol.getSymbolChar()) {
                diagonalSatisfies = false;
                break;
            }
        }
        if (diagonalSatisfies) {
            isWinner |= true;
        }

        
        // check for left diagonal
        diagonalSatisfies = true;
        for (int row = 0; row < dimension; row++) {

            if (board.getBoard().get(row).get(dimension - 1 - row) == null
                    || board.getBoard().get(row).get(dimension - 1 - row).getSymbolChar() != symbol.getSymbolChar()) {
                diagonalSatisfies = false;
                break;
            }
        }

        if (diagonalSatisfies) {
            isWinner |= true;
        }

        if (isWinner == true) {
            return true;
        }
        return false;
    }

    public boolean isGameDraw()
    {
        int dimension = board.getDimension();
        for(int row =0;row<dimension;row++)
        {
            for(int column = 0;column<dimension;column++)
            {
                if(board.getBoard().get(row).get(column)==null)
                {
                    return false;
                }
            }
        }
        return true;
    }

    public void printBoard() {
        int cnt = 0;
        int row = 0;
        int dimension = board.getDimension();
        while (cnt < 5) {
            if (cnt % 2 == 0) {
                for (int column = 0; column < dimension; column++) {
                    if (board.getBoard().get(row).get(column) == null) {
                        System.out.print(" |");
                    } else if (board.getBoard().get(row).get(column).getSymbolChar() == factory.getSymbol('X')
                            .getSymbolChar()) {
                        System.out.print("X|");
                    } else
                        System.out.print("O|");
                }
                System.out.println("");
            } else {
                for (int i = 0; i < dimension * dimension; i++) {
                    System.out.print('-');
                }
                row++;
                System.out.println("");
            }
            cnt++;
        }
    }

}
