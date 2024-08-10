package CacheLLD;

public interface EvictionStrategy {
    void evictFromCache(Cache cache);
    void updateCache(Cache cache, Entry entry);
} 