public class ComparingOrderFactory {

    public static ComparingOrder createComparingOrder(String input) {
        switch(input) {
            case "<=":
                return new DecComparingOrder();
            case ">=":
                return new IncComparingOrder();
            default:
                return null;
        }
    }
}