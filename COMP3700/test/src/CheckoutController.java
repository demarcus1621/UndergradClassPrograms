import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class CheckoutController implements ActionListener{
	CheckoutView cViewer;
	ProductView pViewer;
	SQLiteDataAccess db;
	double total = 0;
	
	public CheckoutController(CheckoutView c, SQLiteDataAccess d){
		cViewer = c;
		db = d;
		cViewer.btnBuy.addActionListener(this);
	}
	
	public void actionPerformed(ActionEvent e){
		if( e.getSource() == cViewer.btnBuy )
			performCheckout();
	}
	
	public void performCheckout(){
		try{
			int productID = Integer.parseInt(cViewer.txtProductID.getText());
			ProductModel pModel = db.loadProduct(productID);
			if( pModel.quantity <= 0 ){
				JOptionPane.showMessageDialog(null, "Out of Stock!");
			}
			else {
				pModel.quantity -= Double.parseDouble(cViewer.txtProductQuantity.getText());
				total += Double.parseDouble(cViewer.txtProductQuantity.getText()) * pModel.price;
				JOptionPane.showMessageDialog(null, "Total:\n" + total);
				db.saveProduct(pModel);
			}
		}
		catch(Exception ex){
			JOptionPane.showMessageDialog(null, "Invalid");
			ex.printStackTrace();
		}
	}
}