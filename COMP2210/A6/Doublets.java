import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;

import java.util.Arrays;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import java.util.TreeSet;

import java.util.stream.Collectors;

/**
 * Provides an implementation of the WordLadderGame interface. The lexicon
 * is stored as a TreeSet of Strings.
 *
 * @author DeMarcus Campbell (dec0013@auburn.edu)
 * @author Dean Hendrix (dh@auburn.edu)
 * @version 2017-11-06
 */
public class Doublets implements WordLadderGame {

    // The word list used to validate words.
    // Must be instantiated and populated in the constructor.
    private TreeSet<String> lexicon;


    /**
     * Instantiates a new instance of Doublets with the lexicon populated with
     * the strings in the provided InputStream. The InputStream can be formatted
     * in different ways as long as the first string on each line is a word to be
     * stored in the lexicon.
     */
    public Doublets(InputStream in) {
        try {
            lexicon = new TreeSet<String>();
            Scanner s =
                new Scanner(new BufferedReader(new InputStreamReader(in)));
            while (s.hasNext()) {
                String str = s.next();
                /////////////////////////////////////////////////////////////
                // INSERT CODE HERE TO APPROPRIATELY STORE str IN lexicon. //
                /////////////////////////////////////////////////////////////
                lexicon.add( str.toUpperCase() );
                s.nextLine();
            }
            in.close();
        }
        catch (java.io.IOException e) {
            System.err.println("Error reading from InputStream.");
            System.exit(1);
        }
    }


    //////////////////////////////////////////////////////////////
    // ADD IMPLEMENTATIONS FOR ALL WordLadderGame METHODS HERE  //
    //////////////////////////////////////////////////////////////
    
    public int getHammingDistance(String str1, String str2) {
      str1 = str1.toUpperCase();
      str2 = str2.toUpperCase();
      if ( str1.length() != str2.length() ) {
         return -1;
      }
      int counter = 0;
      for ( int i = 0 ; i < str1.length() ; i++ ) {
         if ( !str1.substring( i , i + 1 ).equals( str2.substring( i , i + 1 ) ) ) {
            counter++;
         }
      }
      return counter;
    }
    
    public List<String> getMinLadder(String start, String end) {
      if (start.equals(end)){
         ArrayList<String> minLadder = new ArrayList<>();
         minLadder.add(start);
         return minLadder;
      }
      if(getHammingDistance(start, end) == 1) {
         ArrayList<String> minLadder = new ArrayList<>();
         minLadder.add(start);
         minLadder.add(end);
         return minLadder;
      }
      ArrayDeque<Item> queue = new ArrayDeque<>();
      ArrayList<String> visited = new ArrayList<>();
      queue.add( new Item( start, null ) );
      while( !queue.isEmpty() ) {
         Item temp = queue.peek();
         for (String n :
                    getNeighbors( temp.str ) ) {
            if ( !visited.contains( n ) ) {
               Item minLadder2 = new Item( n, temp );
               queue.add( minLadder2 );
               visited.add(n);
               if( n.equals( end ) ) {
                  return minLadder2.getLadder();
               
               }
            }
         }
         queue.remove();
      }
   
      return new ArrayList<String>();
   }

   private class Item {
      String str;
      Item k;
      Item(String str, Item k) {
         this.str = str;
         this.k = k;
      }
   
   public List<String> getLadder() {
      ArrayList<String> list = new ArrayList<>();
      ArrayList<String> ladder2 = new ArrayList<>();
      Item pop = k;
      while (pop.k != null) {
         list.add(pop.str);
         pop = pop.k;
      }
      list.add(pop.str);
      for (int i = list.size() - 1; i >= 0; i--) {
         ladder2.add(list.get(i));
      }
      ladder2.add(this.str);
      return ladder2;
   }
   }
   
    public List<String> getLadder(String start, String end) {
      ArrayList<String> list = new ArrayList<String>();
      if ( start.equals( end ) ) {
         list.add( start );
         return list;
      }
      if ( !isWord( start ) || !isWord( end ) ) {
         return new ArrayList<String>();
      }
      if (getHammingDistance( start, end ) == -1) {
         return new ArrayList<String>();
      }
      if ( getNeighbors( start ).isEmpty() || getNeighbors( end ).isEmpty() ) {
         return new ArrayList<String>();
      }
      Deque<String> queue = new ArrayDeque<String>();
      TreeSet<String> ladder = new TreeSet<String>();
      queue.add( start );
      ladder.add( start );
      while ( !queue.isEmpty() ) {
         String word = queue.peekLast();
         List<String> neighbors = getNeighbors( word );
         word = neighbors.get( 0 );
         int inc = 0;
         while ( ladder.contains( word ) ) {         
            if ( inc < neighbors.size() ) {
               word = neighbors.get( inc++ );
            }
            else if ( inc >= neighbors.size() ) {
               inc = 0;
               queue.remove( queue.peekLast() );
               neighbors = getNeighbors( queue.peekLast() );
               if ( neighbors.isEmpty() ) {
                  return neighbors;
               }
               word = neighbors.get( inc );
            }
         }
         queue.add( word );
         ladder.add( word );
         if (queue.contains( end ) ) {
            break;
         }
      }
      for (String key : queue) {
         list.add( key );
      }  
      return list;
    }
   
    public List<String> getNeighbors(String word) {
      ArrayList<String> list = new ArrayList<String>();
      for ( String x : lexicon ) {
         if ( getHammingDistance( x , word.toUpperCase() ) == 1 ) {
            list.add(x);
         }
      }
      return list;
    }
   
    public int getWordCount() {
      return lexicon.size();
    }
   
    public boolean isWord(String str) {
      if ( lexicon.contains( str.toUpperCase() ) ) {
         return true;
      }
      return false;
    }
   
    public boolean isWordLadder(List<String> sequence) {
      for ( int i = 0 ; i < sequence.size() - 1 ; i++ ) {
         if ( !isWord( sequence.get( i ) ) || getHammingDistance( sequence.get( i ),
                                                                 sequence.get( i + 1 ) ) 
                                                                != 1 ) {
            return false;
         }
      }
      return true;
    }
 
}

