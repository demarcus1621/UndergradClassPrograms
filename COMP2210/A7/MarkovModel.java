import java.io.File;
import java.io.IOException;
import java.util.HashMap;
import java.util.Random;
import java.util.Scanner;
import java.util.Set;

/**
 * MarkovModel.java Creates an order K Markov model of the supplied source
 * text. The value of K determines the size of the "kgrams" used to generate
 * the model. A kgram is a sequence of k consecutive characters in the source
 * text.
 *
 * @author     DeMarcus Campbell (dec0013@auburn.edu)
 * @author     Dean Hendrix (dh@auburn.edu)
 * @version    2017-11-28
 *
 */
public class MarkovModel {

   // Map of <kgram, chars following> pairs that stores the Markov model.
   private HashMap<String, String> model;
   private String txt;
   private String fkgram;

   // add other fields as you need them ...


   /**
    * Reads the contents of the file sourceText into a string, then calls
    * buildModel to construct the order K model.
    *
    * DO NOT CHANGE THIS CONSTRUCTOR.
    *
    */
   public MarkovModel(int K, File sourceText) {
      model = new HashMap<>();
      try {
         String text = new Scanner(sourceText).useDelimiter("\\Z").next();
         buildModel(K, text);
      }
      catch (IOException e) {
         System.out.println("Error loading source text: " + e);
      }
   }


   /**
    * Calls buildModel to construct the order K model of the string sourceText.
    *
    * DO NOT CHANGE THIS CONSTRUCTOR.
    *
    */
   public MarkovModel(int K, String sourceText) {
      model = new HashMap<>();
      buildModel(K, sourceText);
   }


   /**
    * Builds an order K Markov model of the string sourceText.
    */
   private void buildModel(int K, String sourceText) {
      txt = sourceText;
      fkgram = txt.substring(0,K);
      if ( txt.length() == K ) {
         model.put(sourceText, String.valueOf('\u0000'));
      }
      for ( int i = 0 ; i < sourceText.length() - K ; i++ ) {
         String key = sourceText.substring(i, i + K );
         txt = sourceText.substring(i);
         if ( model.containsKey( sourceText.substring(i, i + K) )) {
            model.put( key, model.get(key).concat(String.valueOf(getNextCharBuilder(key))) );
         }
         else {
            model.put( key, String.valueOf(getNextCharBuilder(key)) );
         }
      }
      //txt = sourceText.substring(i);
   }


   /** Returns the first kgram found in the source text. */
   public String getFirstKgram() {
      //return model.keySet().toArray(new String[0])[0];
      return fkgram;
   }


   /** Returns a kgram chosen at random from the source text. */
   public String getRandomKgram() {
      String[] temp = model.keySet().toArray(new String[0]);
      Random r = new Random();
      return temp[Math.abs(r.nextInt() % temp.length)];
   }


   /**
    * Returns the set of kgrams in the source text.
    *
    * DO NOT CHANGE THIS METHOD.
    *
    */
   public Set<String> getAllKgrams() {
      return model.keySet();
   }


   /**
    * Returns a single character that follows the given kgram in the source
    * text. This method selects the character according to the probability
    * distribution of all characters that follow the given kgram in the source
    * text.
    */
   public char getNextChar(String kgram) {
      String x = model.get(kgram);
      Random r = new Random();
      return x.toCharArray()[Math.abs(r.nextInt() % x.toCharArray().length )];
   }

   public char getNextCharBuilder(String kgram) {
      int k = kgram.length();
      String str = txt;
      if ( str.equals(kgram) ) {
         return '\u0000';
      }
      else {
         return str.charAt( str.indexOf(kgram) + k );
      }
   }

   /**
    * Returns a string representation of the model.
    * This is not part of the provided shell for the assignment.
    *
    * DO NOT CHANGE THIS METHOD.
    *
    */
   @Override
   public String toString() {
      return model.toString();
   }
   
   public String get(String X) {
      return model.get(X);
   }

}
