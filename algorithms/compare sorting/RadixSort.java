import java.util.Arrays;

public class RadixSort extends Sort {
    int base = 10;

    public RadixSort(ComparingOrder order) {
        super(order);
    }

    @Override
    public void sort(int array[]) {
        resetTotals();
        this.size = array.length;
        int max = Arrays.stream(array).max().getAsInt();
        int min = Arrays.stream(array).min().getAsInt();

        if (min < 0)
            for( int i = 0; i < this.size; i++) 
                array[i] += min;
        
        long startTime = System.nanoTime();
        for (int exp = 1; max/exp > 0; exp *= 10) {
            countSort(array, this.size, exp);
        }
        long stopTime = System.nanoTime();

        if (min < 0)
            for( int i = 0; i < this.size; i++) 
                array[i] -= min;

        this.totalTime = (stopTime - startTime) / 1000;
    }

    private void countSort(int array[], int n, int iteration) {
        int output[] = new int[n];
        int buckets[] = new int[base];
        Arrays.fill(buckets, 0);

        for (int i = 0; i < n; i++){
            buckets[Math.floorMod((array[i]/iteration), base)]++;
        }
        for (int i = 1; i < base; i++) 
            buckets[i] += buckets[i-1];
        
        for (int i = n-1; i >= 0; i--) {
            int index = --buckets[Math.floorMod((array[i]/iteration), base)]; 
            output[index] = array[i];
        }
        
        boolean decreasingOrder = this.compareKeys(1, 0);
        if (decreasingOrder)
            for(int i = 0; i < n; i++)
                array[i] = output[i];
        else
            for(int i = 0; i < n; i++)
                array[(n-1) - i] = output[i];
        
    }
}