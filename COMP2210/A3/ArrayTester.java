public class ArrayTester {
   public static void main(String[] args) {
      ArraySet<Integer> array = new ArraySet<Integer>();
      System.out.println(array);
      for(int i = 0; i < 10; i++ ) {
         array.add(i);
         System.out.println(array +" "+ " "+array.size());
      }
      for( int i = 0 ; i < 10 ; i++) {
         array.remove(i);
         System.out.println(array +" "+ " "+array.size());
      }
      for ( int i = 0 ; i < 10 ; i++ ) {
         array.add(i);
         System.out.println(array);
      }
      for ( int i = 0 ; i < 10 ; i++ ) {
        System.out.println(array.add(i) +" "+" "+ array.size());
      }
   }
}