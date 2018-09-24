/**
* LinkedStrand.java
* Provides a linked chunk list implementation of the DnaStrand interface.
* 
* @author   DeMarcus Campbell (dec0013@auburn.edu)
* @author   Dean Hendrix (dh@auburn.edu)
* @version  2017-10-17
*
*/
public class LinkedStrand implements DnaStrand {

   /**
    * Container for storing DNA information. A given DNA strand is
    * represented by a chain of nodes.
    *
    * D O   N O T   M A K E   A N Y   C H A N G E S   T O
    *
    * T H E   N O D E   C L A S S 
    *
    */
   class Node {
      String dnaInfo;
      Node next;

      public Node() {
         dnaInfo = "";
         next = null;
      }

      public Node(String s, Node n) {
         dnaInfo = s;
         next = n;
      }
   }

   /** An empty strand. */
   public static final LinkedStrand EMPTY_STRAND = new LinkedStrand();

   /** The first and last node in this LinkedStrand. */
   // D O   N O T   C H A N G E   T H E S E   F I E L D S 
   Node front;
   Node rear;


   /** The number of nucleotides in this strand. */
   long size;

   /**
    * Create a strand representing an empty DNA strand, length of zero.
    *
    * D O   N O T   C H A N G E   T H I S   C O N S T R U C T O R
    */
   public LinkedStrand() {
      front = null;
      rear = null;
      size = 0;
   }


   /**
    * Create a strand representing s. No error checking is done to see if s represents
    * valid genomic/DNA data.
    *
    * @param s is the source of cgat data for this strand
    */
   public LinkedStrand(String s) {
      // YOU MUST COMPLETE THIS METHOD
      if ( s.length() == 0 ) {
         new LinkedStrand();
      }
      else {
         front = new Node(s,null);
         rear = front;
         size = s.length();
      }
   }


   /**
    * Appends the parameter to this strand changing this strand to represent
    * the addition of new characters/base-pairs, e.g., changing this strand's
    * size.
    * 
    * If possible implementations should take advantage of optimizations
    * possible if the parameter is of the same type as the strand to which data
    * is appended.
    * 
    * @param dna is the strand being appended
    * @return this strand after the data has been added
    */
   @Override
   public DnaStrand append(DnaStrand dna) {
      // YOU MUST COMPLETE THIS METHOD
      if ( this.front == null || dna == null) {
         return append(dna.toString());
      }
      if ( dna instanceof LinkedStrand ) {
         LinkedStrand t = (LinkedStrand) dna;
         Node p = this.rear;
         this.rear = t.rear;
         p.next = t.front;
         size += t.size;
         return this;
      }   
      return append(dna.toString());
   }


   /**
    * Similar to append with a DnaStrand parameter in
    * functionality, but fewer optimizations are possible. Typically this
    * method will be called by the append method with an DNAStrand
    * parameter if the DnaStrand passed to that other append method isn't the same 
    * class as the strand being appended to.
    * 
    * @param dna is the string appended to this strand
    * @return this strand after the data has been added
    */
   @Override
   public DnaStrand append(String dna) {
      // YOU MUST COMPLETE THIS METHOD
      if ( this.front == null ) {
         LinkedStrand t = new LinkedStrand(dna);
         this.front = t.front;
         this.rear = t.rear;
         this.size = t.size;
         return this;
      }
      else if ( dna == null ) {
         this.rear = this.front;
         return this;
      }
      Node p = this.rear;
      this.rear = new Node(dna,null);
      p.next = this.rear;
      this.size += dna.length();
      return this;
   }


   /**
    * Cut this strand at every occurrence of enzyme, replacing
    * every occurrence of enzyme with splice.
    *
    * @param enzyme is the pattern/strand searched for and replaced
    * @param splice is the pattern/strand replacing each occurrence of enzyme
    * @return the new strand leaving the original strand unchanged.
    */
   @Override
   public DnaStrand cutAndSplice(String enzyme, String splice) {
      // YOU MUST COMPLETE THIS METHOD
      LinkedStrand tempStrand = new LinkedStrand(this.front.dnaInfo);
      String tempstring = tempStrand.rear.dnaInfo;
      int temp = tempstring.indexOf(enzyme);
      while ( temp >= 0 ) {
         if ( temp == 0 ) {
            Node p = tempStrand.rear;
            p.dnaInfo = splice;
            tempStrand.rear = new Node(tempstring.substring(temp + enzyme.length()),null);
            p.next = tempStrand.rear;
         }
         else {
            Node p = tempStrand.rear;
            p.dnaInfo = tempstring.substring(0,temp);
            tempStrand.rear = new Node(tempstring.substring(temp + enzyme.length()),null);
            p.next = new Node(splice, tempStrand.rear);
         }
         tempstring = tempStrand.rear.dnaInfo;
         temp = tempstring.indexOf(enzyme);
         tempStrand.size = tempStrand.size - enzyme.length() + splice.length();
      }
      return tempStrand;
   }


   /**
    * Simulate a restriction enzyme cut by finding the first occurrence of
    * enzyme in this strand and replacing this strand with what comes before
    * the enzyme while returning a new strand representing what comes after the
    * enzyme. If the enzyme isn't found, this strand is unaffected and an empty
    * strand with size equal to zero is returned.
    * 
    * @param enzyme is the string being searched for
    * @return the part of the strand that comes after the enzyme
    */
   @Override
   public DnaStrand cutWith(String enzyme) {
      // YOU MUST COMPLETE THIS METHOD
      int temp = front.dnaInfo.indexOf(enzyme);
      String ts = front.dnaInfo;
      if ( temp < 0 ) {
         return EMPTY_STRAND;
      }
      else if ( temp == 0 && enzyme.equals(this.front.dnaInfo) ) {
         this.front = null;
         this.rear = null;
         this.size = 0;
         return EMPTY_STRAND;
      }  
      this.front.dnaInfo = ts.substring(0, temp);
      this.size = front.dnaInfo.length();
      return new LinkedStrand(ts.substring(temp + enzyme.length()));
   }


   /**
    * Initialize by copying DNA data from the string into this strand,
    * replacing any data that was stored. The parameter should contain only
    * valid DNA characters, no error checking is done by the this method.
    * 
    * @param source is the string used to initialize this strand
    */
   @Override
   public void initializeFrom(String source) {
      // YOU MUST COMPLETE THIS METHOD
      this.front.dnaInfo = source;
      this.front.next = null;
      this.size = source.length();
      this.rear = this.front;
   }


   /**
    * Returns the number of elements/base-pairs/nucleotides in this strand.
    * @return the number of base-pairs in this strand
    */
   @Override
   public long size() {
      // YOU MUST COMPLETE THIS METHOD
      return this.size;
   }


   /**
    * Returns a string representation of this LinkedStrand.
    */
   @Override
   public String toString() {
      // YOU MUST COMPLETE THIS METHOD
      Node p = this.front;
      StringBuilder sb = new StringBuilder();
      while ( p != null ) {
         sb.append(p.dnaInfo);
         p = p.next;
      }
      return sb.toString();
   }


}

