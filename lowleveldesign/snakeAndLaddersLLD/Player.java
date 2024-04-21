public class Player {
    String name;
    int location;

    Player(String name)
    {
        this.name = name;
        location = 0;
    }

    public int getLocation()
    {
        return location;
    }

    public void setLocation(int location)
    {
        this.location = location;
    }
}
