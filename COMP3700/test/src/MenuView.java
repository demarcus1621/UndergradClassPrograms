import java.awt.*;
import javax.swing.*;

public class MenuView extends JFrame{
	
	public JButton btnProduct = new JButton("Product Information");
	public JButton btnCheckout = new JButton("Check Out");
	
	public MenuView(){
		setTitle("Main Menu");
		setSize(300,300);
		getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.PAGE_AXIS));
		
		JPanel buttonPanel = new JPanel();
		buttonPanel.add(btnProduct);
		buttonPanel.add(btnCheckout);
		getContentPane().add(buttonPanel);
	}
}