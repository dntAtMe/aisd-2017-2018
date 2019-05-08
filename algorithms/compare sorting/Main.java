import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        String sortInput = null;
        Sort sort = null;
        int k = 0;
        String fileName = null;
        String order = null;
        boolean isStat = false;

        for (int i = 0; i < args.length; i++) {
            switch (args[i]) {
                case "--type":
                    sortInput = args[++i];
                    break;
                case "--comp":
                    order = args[++i];
                    break;
                case "--stat":
                    isStat = true;
                    fileName = args[++i];
                    k = Integer.parseInt(args[++i]);
                    break;
                default:
                    System.err.println("Unkown command");
                    System.exit(-1);
                    break;
            }   
        }
        if(sortInput == null || order == null)
            return;
        sort = SortFactory.createSortAlgorithm(sortInput, order);
        
        if(!isStat) {
            Scanner in = new Scanner(System.in);
            int n = in.nextInt();
            int[] array = new int[n];
            for (int i = 0; i < array.length; i++) 
                array[i] = in.nextInt();
            sort.sort(array);
            System.err.printf("size comparisons swaps time: %s\n", sort.getData() + "ms");
            if (!sort.isSorted(array)) {
                System.err.println("NOT SORTED");
                System.exit(-1);
            }
            System.out.println("n = " + array.length);
            sort.printArray(array);
            
        } else {
            Scanner in = new Scanner(System.in);
            Random random = new Random();
            
            int pa = in.nextInt();

            for (int n = 100; n <= 10000; n+= 100) {
                int[] array = new int[n];
                for (int i = 0; i < k; i++) {
                    fillArray(random, array);
                    sort.sort(array);
                    appendToFile(fileName, sort.getData());
                }
            }
        }

    }

    static void appendToFile(String fileName, String str) {
        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter(fileName, true));
            writer.append(str);
            writer.newLine();
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    static void fillArray(Random random, int[] array) {
        for (int i = 0; i < array.length; i++) {
            array[i] = random.nextInt();
        }
    }
}