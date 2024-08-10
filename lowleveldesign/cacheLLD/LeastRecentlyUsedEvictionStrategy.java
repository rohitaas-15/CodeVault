package CacheLLD;
import java.util.HashMap;
import java.util.LinkedList;
public class LeastRecentlyUsedEvictionStrategy implements EvictionStrategy {
    @Override
    public void evictFromCache(Cache cache) {
       
        LinkedList<Entry> list = cache.getList();
        HashMap<Key,Entry> map = cache.getAddressMap();

        Entry EntryToRemove = list.removeFirst();
        map.remove(EntryToRemove.key);      
    }

    public void updateCache(Cache cache, Entry entry)
    {
        LinkedList<Entry> list = cache.getList();
        HashMap<Key,Entry> map = cache.getAddressMap();
        list.remove(entry);
        list.add(entry);
        map.put(entry.key, entry);
    }
}
