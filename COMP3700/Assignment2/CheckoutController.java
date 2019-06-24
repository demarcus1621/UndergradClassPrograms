import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class CheckoutController implements ActionListener{
	CheckoutView cViewer;
	ProductView pViewer;
	SQLiteDataAccess db;
	
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
			pModel.quantity -= Double.parseDouble(cViewer.txtProductQuantity.getText());
			db.saveProduct(pModel);
		}
		catch(Exception ex){
			JOptionPane.showMessageDialog(null, "Invalid");
			ex.printStackTrace();
		}
	}
}