import java.io.File;
import java.io.IOException;
import java.util.Random;

/**
 * TextGenerator.java. Creates an order K Markov model of the supplied source
 * text, and then outputs M characters generated according to the model.
 *
 * @author     Your Name (you@auburn.edu)
 * @author     Dean Hendrix (dh@auburn.edu)
 * @version    2017-11-28
 *
 */
public class TextGenerator {

   /** Drives execution. */
   public static void main(String[] args) {

      if (args == null || args.length < 3 ) {
         System.out.println("Usage: java TextGenerator k length input");
         return;
      }
      if ( args[0].equals("null") || args[1].equals("null") ) {
         System.out.println("Error: Both K and M must be non-negative integers.");
         return;
      }
      // No error checking! You may want some, but it's not necessary.
      int K = Integer.parseInt(args[0]);
      int M = Integer.parseInt(args[1]); 
      if ((K < 0) || (M < 0)) {
         System.out.println("Error: Both K and M must be non-negative.");
         return;
      }

      File text;
      try {
         text = new File(args[2]);
         if (!text.canRead()) {
            throw new Exception();
         }
      }
      catch (Exception e) {
         System.out.println("Error: Could not open " + args[2] + ".");
         return;
      }


      // instantiate a MarkovModel with the supplied parameters and
      // generate sample output text ...
      
      MarkovModel mm = new MarkovModel(K,text);
      String output = mm.getRandomKgram();
      Random r = new Random();
      for (int i = 0 ; i  < M - K ; i++) {
         //char[] array = mm.get(output.substring(i, i + K)).toCharArray();
         //output = output.concat( String.valueOf(array[Math.abs(r.nextInt() % array.length)]) );
         if ( mm.getNextChar(output.substring(i, i + K ) ) != '\u0000' ) {
            output = output.concat( String.valueOf(mm.getNextChar( output.substring(i,i+K) )));
         }
         else {
            output = output.concat( mm.getRandomKgram() );
         }
      }
      System.out.println(output.substring(0,M));
   }
}
