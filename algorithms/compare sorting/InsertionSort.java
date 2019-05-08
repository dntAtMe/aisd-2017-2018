public class InsertionSort extends Sort {

    public InsertionSort(ComparingOrder order) {
        super(order);
    }

    @Override
    public void sort(int array[]) {
        resetTotals();
        long startTime = System.nanoTime();

        size = array.length;
        
        for (int i = 1; i < size; i++) {
            int key = array[i];
            int j = i-1;

            while (j >= 0 && !compareKeys(key, array[j])) {
                array[j+1] = transposition(array[j+1], array[j]);
                j--;
            }
            array[j+1] = transposition(array[j+1], key);    
        }

        long stopTime = System.nanoTime();
        totalTime = (stopTime - startTime) / 1000;
        //System.out.println(totalTime);
    }

}
