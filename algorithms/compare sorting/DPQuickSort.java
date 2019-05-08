public class DPQuickSort extends Sort {

    public DPQuickSort(ComparingOrder order) {
        super(order);
    }

    public void sort(int[] array) {
        resetTotals();
        this.size = array.length;
        long startTime = System.nanoTime();
        quickSort(array, 0, size-1);
        long stopTime = System.nanoTime();
        this.totalTime = (stopTime - startTime) / 1000;
    }

    private void quickSort(int[] array, int low, int high) {
        if (low >= high)
            return;
        if(compareKeys(array[low], array[high]) && array[low] != array[high]) {
            int tmp = array[low];
            array[low] = transposition(array[low], array[high]);
            array[high] = transposition(array[high], tmp);
        }

        int p = array[low];
        int q = array[high];

        int i = low + 1;
        int k = high - 1;
        int j = i;
        int counter = 0;

        while( j <= k ) {
            if (counter >= 0) {
                if (compareKeys(p, array[j]) && array[j] != p) {
                    array[i] = swap(array[j], array[j] = array[i]);     
                    i++;
                    j++;
                    counter++;
                } else 
                if (compareKeys(q, array[j]) && array[j] != q) {
                    j++;
                } else {
                    array[j] = swap(array[k], array[k] = array[j]);
                    k--;
                    counter--;
                }
            } else {
                if (!compareKeys(q, array[k])) {
                    k--;
                    counter--;
                } else
                if (compareKeys(p, array[k]) && array[k] != p) {
                    int tmp = array[k];
                    array[k] = transposition(array[k], array[j]);
                    array[j] = transposition(array[j], array[i]);
                    array[i] = transposition(array[i], tmp);
                    j++;
                    i++;
                    counter++;
                } else {
                    array[j] = swap(array[k], array[k] = array[j]);
                    j++;
                }
                
            }
        }
        array[low] = swap(array[i-1], array[i-1] = array[low]);
        array[high] = swap(array[k+1], array[k+1] = array[high]);
        
        quickSort(array, low, i-2);
        quickSort(array, i, k);
        quickSort(array, k+2, high);
    }
}