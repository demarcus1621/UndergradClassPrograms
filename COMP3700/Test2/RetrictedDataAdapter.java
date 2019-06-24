import javax.swing.*;

public class RetrictedDataAdapter implements IDataAccess {
    User user;
    IDataAccess dataAccess;

    public RetrictedDataAdapter(User user, IDataAccess dataAccess) {

    }

    @Override
    public Product loadProduct(int id) {
        return dataAccess.loadProduct(id);
    }

    @Override
    public boolean saveProduct(Product product) {
        if (user.isManager())
            return dataAccess.saveProduct(product);
        else
            JOptionPane.showMessageDialog(null, "This user has no right to save a product!");
        return false;
    }


}
