import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MenuController implements ActionListener{
	MenuView mViewer;
	ProductView pViewer;
	CheckoutView cViewer;
	
	public MenuController(MenuView v, ProductView p, CheckoutView c){
		mViewer = v;
		pViewer = p;
		cViewer = c;
		mViewer.btnProduct.addActionListener(this);
		mViewer.btnCheckout.addActionListener(this);
	}
	
	public void actionPerformed(ActionEvent e){
		if( e.getSource() == mViewer.btnProduct )
			loadPoductScreen();
		if( e.getSource() == mViewer.btnCheckout )
			loadCheckoutScreen();
	}
	
	public void loadPoductScreen() {
		try{
			mViewer.setVisible(false);
			pViewer.setVisible(true);
		}
		catch(Exception e){
			JOptionPane.showMessageDialog(null, "Could not open screen");
			e.printStackTrace();
		}
	}
	
	public void loadCheckoutScreen() {
		try{
			mViewer.setVisible(false);
			cViewer.setVisible(true);
		}
		catch(Exception e){
			JOptionPane.showMessageDialog(null, "Could not open Check Out");
			e.printStackTrace();
		}
	}
}