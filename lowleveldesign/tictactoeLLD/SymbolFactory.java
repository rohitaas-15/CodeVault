public class SymbolFactory {
    public Symbol getSymbol(char symbol) {
        switch (symbol) {
            case 'X':
                return new SymbolCross();
            case 'O':
                return new SymbolCircle();
            default:
                return null;
        }

    }
}
