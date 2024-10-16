import model.Animal;
import model.Catel;
import model.Pisica;
import java.util.Arrays;

public class Main
{
    public static void main(String[] args)
    {
        int [] arr1 = {2, 3, 1, 5, 6};
        int [] arr2 = {5, 6, 7, 8};
        // int [][] arr2 = {{},{},{}};

        // System.out.println("Printing array: ");
        // System.out.println(Arrays.toString(arr1));

        // System.out.println("Printing array as list: ");
        // System.out.println(Arrays.asList(arr1));

        Arrays.sort(arr1);
        System.out.println(Arrays.toString(arr1));

        // (-insertion point)-1
        System.out.println(Arrays.binarySearch(arr1, 7));
        System.out.println(Arrays.equals(arr1, arr2));

        // problema anagramelor
        // ITALIA, ALIATI
        // String s1="ITALIA";
        // s1.split("");

        Catel c1 = new Catel("c1","c1");
        Pisica p1 = new Pisica("c2","21");

        System.out.println(c1);
        System.out.println(p1);

        Animal animal = new Catel("c1");

        //instanceOf
        System.out.println(c1 instanceof Catel);
    }
}