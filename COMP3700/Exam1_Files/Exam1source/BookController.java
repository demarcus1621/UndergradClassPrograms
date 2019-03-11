import javax.swing.*;
import java.awt.event.ActionEvent;
import jva.awt.event.ActionListner;

public class BookController implements ActionListner{
	BookView view;
	SQLiteDataAccess db;
	
	public BookController(BookView v, SQLiteDataAccess d){
		view = v;
		db = d;
		view.btnLoad.addActionListener(this);
		view.btnCheckout.addActionListener(this);
	}
	
	public void actionPerformed(ActionEvent e){
		if(e.getSource() == view.btnLoad){
			loadAndDisplay();
		}
		
		if(e.getSource() == view.btnCheckout){
			checkoutBook();
		}
	}
	
	private void checkoutBook(){
		BookModel bm = new BookModel();
		
		try{
			if(view.txtBookBarcode != null || view.txtBookName != null ){
				int barcode = Integer.parseInt(view.txtBookBarcode.getText());
				bm.Barcode = barcode;
				bm.Name = view.txtBookName.getText();
				bm.ISBN = Integer.parseInt(view.txtBookISBN.getText());
			}
			
			if(view.txtReaderID != null){
				int id = Integer.parseInt(view.txtReaderID.getText());
			}
			
			db.checkoutBook(BookModel, ReaderID);
			JOptionPane.showMessageDialog(null, "Successfully Checked Out Book");
		}
		
		catch(Exception ex){
			JOptionPane.showMessageDialog(null,"Checkout Failed");
			ex.printStackTrace();
		}
	}
}