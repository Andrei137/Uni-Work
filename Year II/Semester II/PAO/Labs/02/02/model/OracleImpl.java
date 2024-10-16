package model;

// public class OracleImpl extends DbConnection
public class OracleImpl implements DbConnectionI
{
    @Override
    public void connectToDatabase() 
    {
        System.out.println("Connecting to database with oracle!");
    }
}
