class Test {
    public static void main(String[] args) {
        while(true) {
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                return;
            }
        }
    }
}
