public class Cell {
    int location;
    Entity entity;

    Cell(int location)
    {
        this.location = location;
        entity=null;
    }

    public int getLocation()
    {
        return location;
    }

    public void setEntity(Entity entity)
    {
        this.entity = entity;
    }

    public Entity getEntity()
    {
        return entity;
    }

    public boolean containsEntity()
    {
        return entity!=null;
    }
}
