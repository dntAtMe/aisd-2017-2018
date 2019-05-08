public abstract class Sort {

    private ComparingOrder order;
    protected int size;
    protected int totalComparisons;
    protected int totalSwaps;
    protected long totalTime;

    public Sort(ComparingOrder order) {
        this.order = order;
        resetTotals();
    }

    public abstract void sort(int array[]);

    public void printArray(int array[]) {
        for (int i = 0; i < array.length; i++)
            System.out.print(array[i] + " ");
        System.out.println();
    }

    public void setOrder(ComparingOrder order) {
        this.order = order;
    }

    public int getTotalComparisons() {
        return this.totalComparisons;
    }

    public int getTotalSwaps() {
        return this.totalSwaps;
    }

    public long getTotalTime() {
        return this.totalTime;
    }

    protected void resetTotals() {
        this.totalComparisons = 0;
        this.totalSwaps = 0;
        this.totalTime = 0;
        this.size = 0;
    }

    public String getData() {
        return this.size + " " + 
        totalComparisons + " " + 
        totalSwaps + " " + 
        totalTime;
    }

    public boolean isSorted(int[] array) {
        for (int i = 0; i < array.length - 1; i++) {
            if (!order.compareKeys(array[i+1], array[i]))
                return false;
        }   
        return true;
    }

    protected boolean compareKeys(int key1, int key2) {
        //System.err.printf("Comparing: %d with %d\n", key1, key2);
        totalComparisons++;
        return order.compareKeys(key1, key2);
    }
    
    protected boolean isSmaller(int a, int b) {
        //System.err.printf("Comparing: %d with %d\n", a, b);
        totalComparisons++;
        return a < b;
    }

    protected int transposition(int target, int key) {
        //System.err.printf("Transposition: %d to %d\n", target, key);
        totalSwaps++;
        return key;
    }

    protected int swap(int itself, int dummy) {
        //System.err.printf("Transposition: %d to %d\n", itself, dummy);
        //System.err.printf("Transposition: %d to %d\n", dummy, itself);
        totalSwaps+=2;
        return itself;
    }

}
