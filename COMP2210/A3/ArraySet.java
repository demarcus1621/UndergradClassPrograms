import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * ArraySet.java.
 *
 * Provides an implementation of the Set interface using an
 * array as the underlying data structure. Values in the array
 * are kept in ascending natural order and, where possible,
 * methods take advantage of this. Many of the methods with parameters
 * of type ArraySet are specifically designed to take advantage
 * of the ordered array implementation.
 *
 * @author DeMarcus Campbell (dec0013@auburn.edu)
 * @author Dean Hendrix (dh@auburn.edu)
 * @version 10-06-2017
 *
 */
public class ArraySet<T extends Comparable<? super T>> implements Set<T> {

   ////////////////////////////////////////////
   // DO NOT CHANGE THE FOLLOWING TWO FIELDS //
   ////////////////////////////////////////////
   T[] elements;
   int size;

   ////////////////////////////////////
   // DO NOT CHANGE THIS CONSTRUCTOR //
   ////////////////////////////////////
   /**
    * Instantiates an empty set.
    */
   @SuppressWarnings("unchecked")
   public ArraySet() {
      elements = (T[]) new Comparable[1];
      size = 0;
   }
   
   private ArraySet(T[] array, int s) {
      elements = java.util.Arrays.copyOf(array, array.length);
      size = s;
   }

   ///////////////////////////////////
   // DO NOT CHANGE THE SIZE METHOD //
   ///////////////////////////////////
   /**
    * Returns the current size of this collection.
    *
    * @return  the number of elements in this collection.
    */
   @Override
   public int size() {
      return size;
   }

   //////////////////////////////////////
   // DO NOT CHANGE THE ISEMPTY METHOD //
   //////////////////////////////////////
   /**
    * Tests to see if this collection is empty.
    *
    * @return  true if this collection contains no elements,
    *               false otherwise.
    */
   @Override
   public boolean isEmpty() {
      return size == 0;
   }

   ///////////////////////////////////////
   // DO NOT CHANGE THE TOSTRING METHOD //
   ///////////////////////////////////////
   /**
    * Return a string representation of this ArraySet.
    *
    * @return a string representation of this ArraySet
    */
   @Override
   public String toString() {
      if (isEmpty()) {
         return "[]";
      }
      StringBuilder result = new StringBuilder();
      result.append("[");
      for (T element : this) {
         result.append(element + ", ");
      }
      result.delete(result.length() - 2, result.length());
      result.append("]");
      return result.toString();
   }

   /**
    * Ensures the collection contains the specified element. Elements are
    * maintained in ascending natural order at all times. Neither duplicate nor
    * null values are allowed.
    *
    * @param  element  The element whose presence is to be ensured.
    * @return true if collection is changed, false otherwise.
    */
   @Override
   public boolean add(T element) {
      if ( element == null ) {
         return false;
      }
      
      if ( size == 0 ) {
         elements[0] = element;
         size++;
         return true;
      }
      
      if ( size == elements.length ) {
         elements = java.util.Arrays.copyOf(elements, elements.length * 2);
      }
      int loc = getLocation(element);
      if ( loc < 0 ) {
         return false;
      }
      else if ( loc >= 0 && loc < size ) {
         shift(loc, 1);
         elements[loc] = element;
         size++;
         return true;
      }
      else {
         elements[loc] = element;
         size++;
         return true;
      }
   }

   /**
    * Ensures the collection does not contain the specified element.
    * If the specified element is present, this method removes it
    * from the collection. Elements are maintained in ascending natural
    * order at all times.
    *
    * @param   element  The element to be removed.
    * @return  true if collection is changed, false otherwise.
    */
   @Override
   public boolean remove(T element) {
      int loc = getLocation(element);
      if ( loc > 0 ) {
         return false;
      }
      shift(-(loc + 1), -1);
      size--;
      if ( size < elements.length * 0.25 ) {
         elements = java.util.Arrays.copyOf(elements, elements.length / 2);
      }
      return true;
   }

   /**
    * Searches for specified element in this collection.
    *
    * @param   element  The element whose presence in this collection
    *                   is to be tested.
    * @return  true if this collection contains the specified element,
    *               false otherwise.
    */
   @Override
   public boolean contains(T element) {
      int low = 0;
      int high = size;
      
      while ( low <= high ) {
         int mid = ( low + high ) / 2;
         
         if ( mid == size || elements[mid] == null ) {
            break;
         }
         
         if ( element.compareTo(elements[mid]) == 0 ) {
            return true;
         }
         else if ( element.compareTo(elements[mid]) > 0 ) {
            low = mid + 1;
         }
         else {
            high = mid - 1;
         }
      }
      return false;
   }

   /**
    * Tests for equality between this set and the parameter set.
    * Returns true if this set contains exactly the same elements
    * as the parameter set, regardless of order.
    *
    * @return  true if this set contains exactly the same elements
    *               as the parameter set, false otherwise
    */
   @Override
   public boolean equals(Set<T> s) {
      if ( size != s.size() ) {
         return false;
      }
      for ( T x : this ) {
         if ( !s.contains(x) ) {
            return false;
         }
      }
      return true;
   }

   /**
    * Tests for equality between this set and the parameter set.
    * Returns true if this set contains exactly the same elements
    * as the parameter set, regardless of order.
    *
    * @return  true if this set contains exactly the same elements
    *               as the parameter set, false otherwise
    */
   public boolean equals(ArraySet<T> s) {
      if ( size != s.size ) {
         return false;
      }
      for ( int i = 0 ; i < size ; i++ ) {
         if ( elements[i] != s.elements[i] ) {
            return false;
         }
      }
      return true;
   }

   /**
    * Returns a set that is the union of this set and the parameter set.
    *
    * @return  a set that contains all the elements of this set and
    *            the parameter set
    */
   @Override
   public Set<T> union(Set<T> s) {
      ArraySet<T> array = new ArraySet<T>(elements, size);
      for ( T x : s ) {
         array.add(x);
      }
      return array;
   }

   /**
    * Returns a set that is the union of this set and the parameter set.
    *
    * @return  a set that contains all the elements of this set and
    *            the parameter set
    */
   public Set<T> union(ArraySet<T> s) {
      ArraySet<T> array = new ArraySet<T>(this.elements,size);
      if ( array.size == 0 ) {
         return s;
      }
      for ( int i = 0 ; i < s.size ; i++ ) {
         int location = array.getLocation(s.elements[i]);
         if ( array.size == array.elements.length ) {
            array.elements = java.util.Arrays.copyOf(array.elements, array.elements.length * 2);
         }
         if ( location >= 0 && location < array.size ) {
            array.shift(location,1);
            array.elements[location] = s.elements[i];
            array.size++;
         }
         else if ( location > 0 ) {
            array.elements[location] = s.elements[i];
            array.size++;
         }
      }
      return array;
   }


   /**
    * Returns a set that is the intersection of this set
    * and the parameter set.
    *
    * @return  a set that contains elements that are in both
    *            this set and the parameter set
    */
   @Override
   public Set<T> intersection(Set<T> s) {
      ArraySet<T> array = new ArraySet<T>();
      for ( T x : this ) {
         if ( s.contains(x) ) {
            array.add(x);
         }
      }
      return array;
   }

   /**
    * Returns a set that is the intersection of this set and
    * the parameter set.
    *
    * @return  a set that contains elements that are in both
    *            this set and the parameter set
    */
   public Set<T> intersection(ArraySet<T> s) {
      ArraySet<T> array = new ArraySet<T>();
      int i = 0;
      while ( i < s.size && i < size ) {
         if ( getLocation(s.elements[i]) < 0 ) {
            array.add(s.elements[i]);
         }
         i++;
      }
      return array;
   }

   /**
    * Returns a set that is the complement of this set and
    * the parameter set.
    *
    * @return  a set that contains elements that are in this
    *            set but not the parameter set
    */
   @Override
   public Set<T> complement(Set<T> s) {
      ArraySet<T> array = new ArraySet<T>();
      for ( T x : this ) {
         if ( !(s.contains(x)) ) { 
            array.add(x);
         }
      }
      return array;
   }

   /**
    * Returns a set that is the complement of this set and
    * the parameter set.
    *
    * @return  a set that contains elements that are in this
    *            set but not the parameter set
    */
   public Set<T> complement(ArraySet<T> s) {
      ArraySet<T> array = new ArraySet<T>();
      int i = 0;
      if ( s.size == 0 ) {
         return this;
      }
      while ( i < size ) {
         if ( s.getLocation(elements[i]) >= 0 ) {
            array.add(elements[i]);
         }
         i++;
      }
      return array;
   }


   /**
    * Returns an iterator over the elements in this ArraySet.
    * No specific order can be assumed.
    *
    * @return  an iterator over the elements in this ArraySet
    */
   @Override
   public Iterator<T> iterator() {

      // ALMOST ALL THE TESTS DEPEND ON THIS METHOD WORKING CORRECTLY.
      // MAKE SURE YOU GET THIS ONE WORKING FIRST.
      // HINT: JUST USE THE SAME CODE/STRATEGY AS THE ARRAYBAG CLASS
      // FROM LECTURE. THE ONLY DIFFERENCE IS THAT YOU'LL NEED THE
      // ARRAYITERATOR CLASS TO BE NESTED, NOT TOP-LEVEL.
      class ArrayIterator implements Iterator<T> {
         private int current;
         private int count;
         private T[] elem;
         
         public ArrayIterator( T[] array , int size ) {
            current = 0;
            count = size;
            elem = array;
         }
         
         public boolean hasNext() {
            return (current < count);
         }
         
         public void remove() {
            throw new UnsupportedOperationException();
         }
         
         public T next() {
            if ( !hasNext() ) {
               throw new NoSuchElementException();
            }
            return elem[current++];
         }
      }
      
      return new ArrayIterator(elements, size);
   }

   /**
    * Returns an iterator over the elements in this ArraySet.
    * The elements are returned in descending order.
    *
    * @return  an iterator over the elements in this ArraySet
    */
   public Iterator<T> descendingIterator() {
      class ArrayDIterator implements Iterator<T> {
         private int count;
         private int current;
         private T[] elem;
         
         public ArrayDIterator( T[] array, int size ) {
            count = size;
            current = 0;
            elem = array;
         }
         
         public boolean hasNext() {
            return ( count > current );
         }
         
         public void remove() {
            throw new UnsupportedOperationException();
         }
         
         public T next() {
            if ( !hasNext() ) {
               throw new NoSuchElementException();
            }
            return elem[count - 1 - (current++)];
         }
      }
      
      return new ArrayDIterator(elements, size);
   }

   /**
    * Returns an iterator over the members of the power set
    * of this ArraySet. No specific order can be assumed.
    *
    * @return  an iterator over members of the power set
    */
   public Iterator<Set<T>> powerSetIterator() {
      class PowerIterator implements Iterator<Set<T>> {
         private int count;
         private int current;
         private T[] elem;
         
         public PowerIterator( T[] array, int size ) {
            elem = array;
            count = (int) Math.pow(2,size);
            current = 0;
         }
         
         public boolean hasNext() {
            return ( count > current );
         }
         
         public Set<T> next() {
            if ( !hasNext() ) {
               throw new NoSuchElementException();
            }
            if ( current == 0 ) {
               current++;
               return new ArraySet<T>();
            }
            ArraySet<T> array = new ArraySet<T>();
            char[] binary = Integer.toBinaryString(current).toCharArray();
            for ( int i = binary.length ; i > 0 ; i-- ) {
               if ( String.valueOf(binary[i - 1]).equals("1") ) {
                  array.add(elem[i - 1]);
               }
            }
            current++;
            return array;
         }
         
         public void remove() {
            throw new UnsupportedOperationException();
         }
      }
      
      return new PowerIterator(elements,size);
   }
   
   private void shift(int location, int amount) {
      if ( amount > 0 ) {
         for ( int i = size - 1 ; i >= location ; i-- ) {
            T temp = elements[i];
            elements[i + 1] = temp;
         }
      }
      else {
         if ( location == size - 1 ) {
            elements[location] = null;
         }
         
         for ( int i = location ; i < size - 1 ; i++ ) {
            elements[i] = elements[i + 1];
            elements[i + 1] = null;
         }
      }
   }
   
   private int getLocation(T value) {
      for ( int i = 0 ; i < size ; i++ ) {
         if ( value.compareTo(elements[i]) < 0 ) {
            return i;
         }
         else if ( i + 1 == size && value.compareTo(elements[i]) > 0) { //&& elements[i + 1] == null ) {
            return i + 1;
         }
         else if ( value.compareTo(elements[i]) == 0 ) {
            return -(i + 1);
         }
      }
      return -1;
   }
   
}
