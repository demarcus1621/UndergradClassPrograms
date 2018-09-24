/**
 * Applies the linear scan strategy to counting the number of negative
 * values in an array.
 *
 * @author DeMarcus Campbell (dec0013@auburn.edu)
 * @version 2017-08-23
 */
public class CountNegatives {
   
   /**
    * Returns the number of negative values in the given array.
    */
   public static int countNegatives(int[]a) {
      int counter = 0;
      for(int x: a){
         if(x < 0)
            counter++;
      }
      return counter;
   }
   
   public static void main(String[] args){
      int[] test = {-1,-2,-3,-4,5};
      System.out.println(countNegatives(test));
   }
}
