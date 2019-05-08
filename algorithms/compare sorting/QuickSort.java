public class QuickSort extends Sort {

    public QuickSort(ComparingOrder order) {
        super(order);
    }

    public void sort(int[] array) {
        resetTotals();
        this.size = array.length;
        long startTime = System.nanoTime();
        quickSort(array, 0, size - 1);
        long stopTime = System.nanoTime();
        this.totalTime = (stopTime - startTime) / 1000;
    }

    private void quickSort(int[] array, int low, int high) {
        if (low >= high)
            return;
        int partitionIndex = partition(array, low, high);

        quickSort(array, low, partitionIndex - 1);
        quickSort(array, partitionIndex + 1, high);
    }

    private int partition(int[] array, int low, int high) {
        int pivot = array[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (compareKeys(pivot, array[j])) {
                i++;
                
                int tmp = array[i];
                array[i] = transposition(array[i], array[j]);
                array[j] = transposition(array[j], tmp);
            }
        }

        int tmp = array[i+1];
        array[i+1] = transposition(array[i+1], pivot);
        array[high] = transposition(pivot, tmp);

        return i+1;
    }

}