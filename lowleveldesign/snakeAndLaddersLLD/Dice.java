import java.util.Random;

public class Dice {
    Random random;
    Dice()
    {
        random = new Random();
    }
    public int getDiceValue()
    {
        return random.nextInt(1000)%6 + 1;
    }
}
