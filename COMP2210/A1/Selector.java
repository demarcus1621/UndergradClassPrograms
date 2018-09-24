import java.util.Arrays;

/**
* Defines a library of selection methods
* on arrays of ints.
*
* @author   DeMarcus Campbell (dec0013@auburn.edu)
* @author   Dean Hendrix (dh@auburn.edu)
* @version  2017-08-24
*
*/
public final class Selector {

   /**
    * Can't instantiate this class.
    *
    * D O   N O T   C H A N G E   T H I S   C O N S T R U C T O R
    *
    */
   private Selector() { }


   /**
    * Selects the minimum value from the array a. This method
    * throws IllegalArgumentException if a is null or has zero
    * length. The array a is not changed by this method.
    */
   public static int min(int[] a) {
      IllegalArgumentException ill = new IllegalArgumentException(); 
      if (a == null || a.length == 0) {
         throw ill;
      }
      int min = a[0];
      for (int x : a) {
         if (x < min) {
            min = x;
         }
      }
      return min;
   }


   /**
    * Selects the maximum value from the array a. This method
    * throws IllegalArgumentException if a is null or has zero
    * length. The array a is not changed by this method.
    */
   public static int max(int[] a) {
      IllegalArgumentException nill = new IllegalArgumentException();
      if (a == null || a.length == 0) {
         throw nill;
      }
      int maxim = a[0];
      for (int m : a) {
         if (maxim < m) {
            maxim = m;
         }
      }
      return maxim;
   }


   /**
    * Selects the kth minimum value from the array a. This method
    * throws IllegalArgumentException if a is null, has zero length,
    * or if there is no kth minimum value. Note that there is no kth
    * minimum value if k < 1, k > a.length, or if k is larger than
    * the number of distinct values in the array. The array a is not
    * changed by this method.
    */
   public static int kmin(int[] a, int k) {
      IllegalArgumentException nill = new IllegalArgumentException();
      if (a == null || a.length == 0) {
         throw nill;
      }
      int[] sorted = Arrays.copyOf(a, a.length);
      Arrays.sort(sorted);
      int[] distinct = {};
      for ( int x : sorted ) {
         int counter = 0;
         for ( int y : distinct ) {
            if ( y == x ) {
               counter++;
            }
         }
         if (counter == 0) {
            distinct = Arrays.copyOf(distinct, distinct.length + 1);
            distinct[distinct.length - 1] = x;
         }
      }
      if (k < 1 || k > distinct.length) {
         throw nill;
      }
      return distinct[k - 1];
   }


   /**
    * Selects the kth maximum value from the array a. This method
    * throws IllegalArgumentException if a is null, has zero length,
    * or if there is no kth maximum value. Note that there is no kth
    * maximum value if k < 1, k > a.length, or if k is larger than
    * the number of distinct values in the array. The array a is not
    * changed by this method.
    */
   public static int kmax(int[] a, int k) {
      IllegalArgumentException nullem = new IllegalArgumentException();
      if (a == null || a.length == 0) {
         throw nullem;
      }
      int[] sorted = Arrays.copyOf(a, a.length);
      Arrays.sort(sorted);
      int[] distinct = {};
      for ( int x : sorted ) {
         int counter = 0;
         for ( int y : distinct ) {
            if ( y == x ) {
               counter++;
            }
         }
         if (counter == 0) {
            distinct = Arrays.copyOf(distinct, distinct.length + 1);
            distinct[distinct.length - 1] = x;
         }
      }
      if (k < 1 || k > distinct.length) {
         throw nullem;
      }
      return distinct[distinct.length - k];
   }


   /**
    * Returns an array containing all the values in a in the
    * range [low..high]; that is, all the values that are greater
    * than or equal to low and less than or equal to high,
    * including duplicate values. The length of the returned array
    * is the same as the number of values in the range [low..high].
    * If there are no qualifying values, this method returns a
    * zero-length array. Note that low and high do not have
    * to be actual values in a. This method throws an
    * IllegalArgumentException if a is null or has zero length.
    * The array a is not changed by this method.
    */
   public static int[] range(int[] a, int low, int high) {
      IllegalArgumentException nullem = new IllegalArgumentException();
      if (a == null || a.length == 0) {
         throw nullem;
      }
      int counter = 0;
      int[] array = {};
      for (int x : a) {
         if (x >= low && x <= high) {
            array = Arrays.copyOf(array,counter + 1);
            array[counter] = x;
            counter++;
         }
      }
      return array;
   }


   /**
    * Returns the smallest value in a that is greater than or equal to
    * the given key. This method throws an IllegalArgumentException if
    * a is null or has zero length, or if there is no qualifying
    * value. Note that key does not have to be an actual value in a.
    * The array a is not changed by this method.
    */
   public static int ceiling(int[] a, int key) {
      IllegalArgumentException nill = new IllegalArgumentException();
      if (a == null || a.length == 0) {
         throw nill;
      }
      for (int x : a) {
         if (x >= key) {
            for (int y : a) {
               if (y < x && y >= key) {
                  x = y;
               }
            }
            return x;
         }
      }
      throw nill;
   }


   /**
    * Returns the largest value in a that is less than or equal to
    * the given key. This method throws an IllegalArgumentException if
    * a is null or has zero length, or if there is no qualifying
    * value. Note that key does not have to be an actual value in a.
    * The array a is not changed by this method.
    */
   public static int floor(int[] a, int key) {
      IllegalArgumentException ill = new IllegalArgumentException();
      if (a == null || a.length == 0) {
         throw ill;
      }
      for (int x : a) {
         if (x <= key) {
            for (int y : a) {
               if (y > x && y <= key) {
                  x = y;
               }
            }
            return x;
         }
      }
      throw ill;
   }

}
