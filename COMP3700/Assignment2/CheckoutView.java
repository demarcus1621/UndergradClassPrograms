import java.awt.*;
import javax.swing.*;

public class CheckoutView extends JFrame{
	
	public JTextField txtProductID = new JTextField(30);
	public JTextField txtProductQuantity = new JTextField(30);
	
	public JButton btnBuy = new JButton("Buy");
	
	public CheckoutView() {
		setTitle("Check Out View");
		setSize(new Dimension(600,300));
		this.getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.PAGE_AXIS));
		
		JPanel line1 = new JPanel();
		line1.add(new JLabel("Product ID"));
		line1.add(txtProductID);
		this.getContentPane().add(line1);
		
		JPanel line2 = new JPanel();
		line2.add(new JLabel("Quantity"));
		line2.add(txtProductQuantity);
		this.getContentPane().add(line2);
		
		JPanel buttonPanel = new JPanel();
		buttonPanel.add(btnBuy);
		this.getContentPane().add(buttonPanel);
	}
}