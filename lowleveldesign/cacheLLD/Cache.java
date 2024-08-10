package CacheLLD;

import java.util.HashMap;
import java.util.LinkedList;

public class Cache {

    private LinkedList<Entry> list ;
    private HashMap< Key, Entry > addressMap; 
    private int capacity;
    private EvictionStrategy strategy;

    Cache(int capacity, EvictionStrategy strategy )
    {
        list = new LinkedList<>();
        addressMap= new HashMap<>();
        this.capacity=capacity;
        this.strategy=strategy;
    }


    public LinkedList<Entry> getList()
    {
        return list;
    }

    public HashMap<Key, Entry> getAddressMap()
    {
        return addressMap;
    }


    public void update(Key  key, Value val)
    {
        strategy.updateCache(this, new Entry(key, val));

        if(list.size()>capacity)
        {
            strategy.evictFromCache(this);
        }
    }

    public Value get(Key key)
    {
        if(addressMap.get(key)==null)
        {
            return new Value(-1);
        }

        Value value = addressMap.get(key).value;
        strategy.updateCache(this, new Entry(key, value));
        return value;
    }

}
