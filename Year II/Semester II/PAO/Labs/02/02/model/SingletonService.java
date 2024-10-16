package model;

public class SingletonService
{
    private SingletonService() {};

    private static class SINGLETON
    {
        private static final SingletonService INSTANCE = new SingletonService(); 
    }

    public static SingletonService getInstance()
    {
        return SINGLETON.INSTANCE;
    }
}