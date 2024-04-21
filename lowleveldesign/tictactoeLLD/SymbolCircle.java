public class SymbolCircle implements Symbol {
    Player assignedPlayer;

    public SymbolCircle getSymbol() {
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
        return 'O';
    }

}
