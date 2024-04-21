
public class Entity {
    int start, end;

    Entity(int start, int end)
    {
        this.start = start;
        this.end = end;
    }

    public int getInitialLocation()
    {
        return start;
    }
    public int getFinalLocation()
    {
        return end;
    }
}
