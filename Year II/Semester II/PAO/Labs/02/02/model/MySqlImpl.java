package model;

// public class MySqlImpl extends DbConnection
public class MySqlImpl implements DbConnectionI
{
    @Override
    public void connectToDatabase() 
    {
        System.out.println("Connecting to database with MySql!");
    }
}
