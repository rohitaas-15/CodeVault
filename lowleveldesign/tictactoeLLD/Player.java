public class Player {
    String name;
    Symbol assignedSymbol;

    Player(String name, Symbol assignedSymbol) {
        this.name = name;
        this.assignedSymbol = assignedSymbol;
    }

    public String getName() {
        return name;
    }

    public Symbol getSymbol() {
        return assignedSymbol;
    }

}
