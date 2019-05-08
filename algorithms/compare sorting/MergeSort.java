public class MergeSort extends Sort {

    public MergeSort(ComparingOrder order) {
        super(order);
    }

    public void sort(int[] array) {
        resetTotals();
        this.size = array.length;
        long startTime = System.nanoTime();
        mergeSort(array, 0, array.length - 1);
        long stopTime = System.nanoTime();
        this.totalTime = (stopTime - startTime) / 1000;
    }

    private void mergeSort(int[] array, int low, int high) {
        if (isSmaller(low, high)) {
            int mid = (low + high) / 2;

            mergeSort(array, low, mid);
            mergeSort(array, mid+1, high);

            merge(array, low, mid, high);
        }
    }

    private void merge(int[] array, int low, int mid, int high) {
        int sizeA = mid - low + 1;
        int sizeB = high - mid;

        int[] A = new int[sizeA];
        int[] B = new int[sizeB];

        for (int i = 0; i < sizeA; i++)
            A[i] = array[low + i];
        for (int i = 0; i < sizeB; i++)
            B[i] = array[mid + 1 + i];

        int a = 0;
        int b = 0;


        while (isSmaller(a, sizeA) && isSmaller(b, sizeB)) {
            if (compareKeys(B[b], A[a])) {
                array[low] = transposition(array[low], A[a]);
                a++;
            } else {
                array[low] = transposition(array[low], B[b]);
                b++;
            }
            low++;
        }

        while (isSmaller(a, sizeA)) {
            array[low] = transposition(array[low], A[a]);
            a++;
            low++;
        }

        while (isSmaller(b, sizeB)) {
            array[low] = transposition(array[low], B[b]);
            b++;
            low++;
        }
    }
}