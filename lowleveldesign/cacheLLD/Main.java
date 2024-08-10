package CacheLLD;

public class Main {
    @SuppressWarnings("unused")
    public static void main(String[] args) {
        Key p1 = new Key("Person1");
        Key p2 = new Key("Person2");
        Key p3 = new Key("Person3");

        Value one = new Value(1);
        Value two = new Value(2);
        Value three = new Value(3);


        EvictionStrategy LRU = new LeastRecentlyUsedEvictionStrategy();
        Cache cache = new Cache(5, LRU);

        cache.update(p1, one);
        cache.update(p2, three);
        cache.update(p1, two);

        System.out.println(cache.get(p1).value);
    }
}
