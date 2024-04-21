import java.util.ArrayList;

public class Board {

    int dimension;
    ArrayList<ArrayList<Symbol>> board;

    Board(int dimension) {
        board = new ArrayList<>();
        for (int i = 0; i < dimension; i++) {
            board.add(new ArrayList<Symbol>());
            for (int j = 0; j < dimension; j++) {
                board.get(i).add(null);
            }
        }
        this.dimension = dimension;
    }

    public void fillSquare(int row, int column, Symbol symbol) {
        board.get(row).set(column, symbol);
    }

    public int getDimension() {
        return this.dimension;
    }

    public ArrayList<ArrayList<Symbol>> getBoard() {
        return board;
    }

}
