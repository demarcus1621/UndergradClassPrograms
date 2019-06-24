import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ProductController implements ActionListener{
	
	ProductView viewer;
	SQLiteDataAccess db;
	
	public ProductController(ProductView v, SQLiteDataAccess d){
		viewer = v;
		db = d;
		viewer.btnLoad.addActionListener(this);
		viewer.btnSave.addActionListener(this);
	}
	
	public void actionPerformed(ActionEvent e){
		if(e.getSource() == viewer.btnLoad)
			loadProductAndDisplay();
		if(e.getSource() == viewer.btnSave)
			saveProduct();
	}
	
	private void saveProduct(){
		ProductModel pModel = new ProductModel();
		
		try{
			int productID = Integer.parseInt(viewer.txtProductID.getText());
			pModel.productID = productID;
			pModel.name = viewer.txtProductName.getText();
			pModel.price = Double.parseDouble(viewer.txtProductPrice.getText());
			pModel.quantity = Double.parseDouble(viewer.txtProductQuantity.getText());
			
			db.saveProduct(pModel);
			JOptionPane.showMessageDialog(null, "Product Saved!");
		}
		catch(NumberFormatException ex){
			JOptionPane.showMessageDialog(null, "Invalid Format");
			ex.printStackTrace();
		}
	}
	
	private void loadProductAndDisplay(){
		try{
			int productID = Integer.parseInt(viewer.txtProductID.getText());
			ProductModel pModel = db.loadProduct(productID);
			viewer.txtProductName.setText(pModel.name);
			viewer.txtProductPrice.setText(String.valueOf(pModel.price));
			viewer.txtProductQuantity.setText(String.valueOf(pModel.quantity));
		}
		catch(NumberFormatException ex){
			JOptionPane.showMessageDialog(null, "Invalid Format");
			ex.printStackTrace();
		}
	}
}