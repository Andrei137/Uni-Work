import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        System.out.println("Salut!!!");
        //jdk -> java development kit
        //jre -> java runtime environment (executable)

        //variable declaration:
        //primitive types: long short byte double float int boolean char - alocate pe stiva + se transmit ca parametrii
        //wrapper classes: Long Short Byte Double Float Integer Boolean Character - alocate pe heap + se transmit ca referinte
        // String -> clasa string
//
//        int n1 = 5;
//        int n2 = 10;
//
//        Integer n3 = 5;
//        Integer n4 = 10;
//        System.out.println(n3.compareTo(n4));
//
//        //static -> o singura instanta pentru toate
//        //final -> imutabilitate
//
//        //instructiuni de control:
//        //for, while, do while, forEach, enhancedFor
//        //if else if, switch case...
//
//        switch (n3) {
//            case 1:
//                System.out.println("Valoarea este 1");
//                break;
//            default:
//                System.out.println("Sout valoare default!!!");
//        }
//        // case 1 -> System.out.println(""); in versiunile mai noi (de la 11 incolo cred)
//
//        int [] arr1 = {1,2,3,4,5,6};
//        for(int i=0;i<arr1.length; i++)
//        {
//            System.out.println("val: " + arr1[i]);
//        }
//
//        for(int i : arr1) // (enhanced for sau for in)
//        {
//            System.out.println(i);
//        }
//
//        Arrays.asList(arr1).forEach(i -> System.out.println(i)); // vom face detaliat mai incolo (foreach)
//        Book book = new Book("B1","A1");

//        Scanner sc = new Scanner(System.in); // citeste din consola
//        System.out.println("Introduceti o variabila in consola: ");
//        while(true)
//        {
//            int value = sc.nextInt();
//            if(value>10)
//            {
//                System.out.println("Exiting program...");
//                break;
//            }
//            else
//            {
//                System.out.println("Introduceti o alta valoare...");
//            }
//        }
//
//        int[] arr = new int[0];
//        arr = addElement(arr,1);
//        arr = addElement(arr,2);
//        arr = addElement(arr,4);
//        arr = addElement(arr,6);
//
//        arr = removeElement(arr,2);
//
//        System.out.println(Arrays.toString(arr));

//        int[] arr1 = {1,6,3,4,7};
//        Book[] arr2 = {
//            new Book("B5","A5"),
//            new Book("B4","A4"),
//            new Book("B6","A6"),
//        };
//        Comparator<Book> bookComparator = (b1, b2) -> b1.getName().compareTo(b2.getName());
//        Arrays.sort(arr2, bookComparator);
//        System.out.println(Arrays.toString(arr2));

        /* Exercitiu individual
         * Car -> culoare, marca, pret
         * Car [] -> add car
         *        -> list cars
         *
         * citire instructiuni din consola
         * 1. -> add car -> read from console values for car
         * 2. -> list cars
         * 3. -> exit
         */

        Car[] cars = new Car[0];
        Scanner sc = new Scanner(System.in); // citeste din consola
        boolean ok=true;
        while (ok) {
            System.out.println("Choose a number: ");
            System.out.println("1. Add a car.");
            System.out.println("2. List cars.");
            System.out.println("3. Exit program.");
            int value = sc.nextInt();
            switch (value) {
                case 1:
                    System.out.println("Tell me the color");
                    String color = sc.next();
                    System.out.println("Tell me the brand");
                    String brand = sc.next();
                    System.out.println("Tell me the price");
                    int price = sc.nextInt();
                    cars = addCar(cars, color, brand, price);
                    break;
                case 2:
                    System.out.println(Arrays.toString(cars));
                    break;
                case 3:
                    System.out.println("Bye =(");
                    ok=false;
                    break;
                default:
                    System.out.println("This is not a valid number. Please choose a number from 1 to 3.");
            }
        }
    }

    private static Car[] addCar(Car[] cars, String color, String brand, int price)
    {
        Car[] temp = new Car[cars.length +1];
        for(int i=0;i<cars.length;i++)
        {
            temp[i]=cars[i];
        }
        temp[cars.length] = new Car(color,brand,price);
        return temp;
    }

    private static int [] addElement(int[] arr,int elem)
    {
        int[] temp = new int[arr.length +1];
        for(int i=0;i<arr.length;i++)
        {
            temp[i]=arr[i];
        }
        temp[arr.length]=elem;
        return temp;
    }

    //exercitiu 1 - sa dai remove la un element (apare sigur in array si e unic)
    private static int [] removeElement(int[] arr,int value)
    {
        int k=0;
        int[] temp = new int[arr.length-1];
        for(int i=0;i<arr.length;i++)
            if(arr[i]!=value)
            {
                temp[k]=arr[i];
                k++;
            }
        return temp;
    }
}