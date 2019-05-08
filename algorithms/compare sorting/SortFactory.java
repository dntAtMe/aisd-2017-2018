public class SortFactory {

    public static Sort createSortAlgorithm(String input, String orderInput) {
        ComparingOrder order = ComparingOrderFactory.createComparingOrder(orderInput);
        switch (input) {
            case "merge":
                return new MergeSort(order);
            case "insert":
                return new InsertionSort(order);
            case "quick":
                return new QuickSort(order);
            case "dpquick":
                return new DPQuickSort(order);
            default:
                return null;
        }
    }
}