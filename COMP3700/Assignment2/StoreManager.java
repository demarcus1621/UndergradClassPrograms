public class StoreManager{
	
	static SQLiteDataAccess db = new SQLiteDataAccess();
	static ProductView pViewer = new ProductView();
	static ProductController pController = new ProductController(pViewer, db);
	static MenuView mViewer = new MenuView();
	static CheckoutView cViewer = new CheckoutView();
	static MenuController mController = new MenuController(mViewer, pViewer, cViewer);
	static CheckoutController cController = new CheckoutController(cViewer, db);
	
	public static void main(String[] args){
		db.connect();
		ProductModel pModel = db.loadProduct(1);
		if( pModel != null )
			System.out.println("Product ID: " + pModel.productID + "\nName: " + pModel.name +
				"\nPrice: " + pModel.price + "\nQuantity: " + pModel.quantity);
		
		pModel.productID = 100;
		pModel.name = "Samsung TV";
		pModel.price = 399.99;
		pModel.quantity = 1000;
		db.saveProduct(pModel);
		
		pModel = db.loadProduct(100);
		if( pModel != null )
			System.out.println("Product ID: " + pModel.productID + "\nName: " + pModel.name +
				"\nPrice: " + pModel.price + "\nQuantity: " + pModel.quantity);
		mViewer.setVisible(true);
	}
}