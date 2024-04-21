import java.util.LinkedList;
import java.util.Queue;


public class GameController {
    
    int victoryLocation;
    Cell[] board;
    Dice dice;
    Player Rohitaas, Harsimrat;

    public void initialize(int victoryLocation)
    {
        this.victoryLocation=victoryLocation;
        board = new Cell[victoryLocation+1];
        for(int i = 0;i<=victoryLocation;i++)
        {
            Cell newCell = new Cell(i);
            board[i]=newCell;
        }
        dice = new Dice();
        Rohitaas = new Player("Rohitaas");
        Harsimrat = new Player("Harsimrat");
    }

    public void addEntity(Entity entity)
    {
        int location= entity.getInitialLocation();
        board[location].setEntity(entity);
    }

    public String playGame()
    {
        Queue<Player> players = new LinkedList<>();
        players.add(Rohitaas);
        players.add(Harsimrat);

        while(true)
        {
            int diceThrow = dice.getDiceValue();
        
            Player currentPlayer = players.peek();

            System.out.println(currentPlayer.name + " threw " +diceThrow + " on the dice ");

            int newLocation = currentPlayer.getLocation()+ diceThrow;

            if(newLocation>=victoryLocation)
            {
                break;
            }

            if(board[newLocation].containsEntity())
            {
                newLocation= board[newLocation].getEntity().getFinalLocation();
            }

            currentPlayer.setLocation(newLocation);
            players.remove();
            players.add(currentPlayer);

            System.out.println(currentPlayer.name + " 's current location is " +currentPlayer.getLocation());
        }

        return players.peek().name;
    }
}
