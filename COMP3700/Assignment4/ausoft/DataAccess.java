package com.ausoft;

public interface DataAccess {

    public boolean connect();
    public boolean disconnect();

    public ProductModel loadProduct(int id);
    public boolean saveProduct(ProductModel p);

    // ... similarly for load/save OrderModel, UserModel, ProviderModel, CustomerModel...
}
