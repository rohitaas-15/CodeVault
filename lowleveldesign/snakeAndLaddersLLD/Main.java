public class Main {
    public static void main(String [] args)
    {
        GameController controller= new GameController();
        controller.initialize(100);

        Entity snake1 = new Entity(99, 1);
        Entity snake2 = new Entity(66, 33);
        Entity ladder1 = new Entity(4, 35);
        controller.addEntity(snake1);
        controller.addEntity(snake2);
        controller.addEntity(ladder1);
        System.out.println(controller.playGame() + " Wins!");
    }
}
