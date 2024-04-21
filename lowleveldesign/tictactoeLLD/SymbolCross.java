public class SymbolCross implements Symbol {
    Player assignedPlayer;

    public SymbolCross getSymbol() {
        return this;
    }

    public void setPlayer(Player player) {
        assignedPlayer = player;
    }

    public Player getPlayer() {
        return assignedPlayer;
    }

    @Override
    public char getSymbolChar() {
        return 'X';
    }

}
