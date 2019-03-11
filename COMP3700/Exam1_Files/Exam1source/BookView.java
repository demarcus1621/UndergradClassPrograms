import javax.swing.*;
import java.awt.*;

public class BookView extends JFrame{
	public JTextField txtBookBarcode = new JTextField(30);
	public JTextField txtBookName = new JTextField(30);
	public JTextField txtBookISBN = new JTextField(30);
	public JTextField txtReaderID = new JTextField(30);
	
	public JButton btnLoad = new JButton("Load");
	public JButton btnCheckout = new JButton("Check Out");
	
	public BookView(){
		setTitle("Book View");
		setSize(new Dimension(600, 300));
		getContentPane().setLayout(new BoxLayout(
			getContentPane(), BoxLayout.PAGE_AXIS));
		
		JPanel line1 = new JPanel();
		line1.add(new JLabel("Book Title"));
		line1.add(txtBookName);
		getContentPane().add(line1);
		
		JPanel line2 = new JPanel();
		line2.add(new JLabel("Barcode"));
		line2.add(txtBookBarcode);
		getContentPane().add(line2);
		
		JPanel line3 = new JPanel();
		line3.add(new JLabel("ISBN"));
		line3.add(txtBookISBN);
		getContentPane().add(line3);
		
		JPanel line4 = new JPanel();
		line4.add(new JLabel("Reader ID"));
		line4.add(txtReaderID);
		getContentPane().add(line4);
		
		JPanel buttonPanel = new JPanel();
		buttonPanel.add(btnLoad);
		buttonPanel.add(btnCheckout);
		
		getContentPane().add(buttonPanel);
	}
}