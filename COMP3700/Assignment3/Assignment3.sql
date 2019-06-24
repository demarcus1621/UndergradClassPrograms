/*
 * Author: Demarcus Campbell
 * ID: 903885028
 * Assignment 3
 */

create table Users(
Username varchar(50) not null primary key,
Password varchar(50) not null,
Name varchar(50) not null,
Address varchar(50),
Role varchar(15)
);

create table Products(
ProductID int not null primary key,
Product_Name varchar(50) not null,
Quantity int not null
);

create table Orders(
Username varchar(50) not null,
ProductID int,
Total decimal not null,
Status varchar(15),
foreign key (Username) references Users(Username),
foreign key (ProductID) references Products(ProductID),
primary key(Username, ProductID)
);