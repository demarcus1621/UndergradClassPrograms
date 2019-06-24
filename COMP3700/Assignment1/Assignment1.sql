/*
* Demarcus Campbell
* Assignment 1
*/

/*
* Creation of DB tables
*/

create table Products(
Product_ID int not null primary key auto_increment,
Name varchar(255) not null,
Price decimal not null,
Barcode varchar(255) not null,
Stock int,
Producer varchar(255),
Producer_Contact varchar(255)
);

create table Orders(
Order_ID int not null primary key auto_increment,
Total decimal
);

create table Bought(
Order_ID int not null,
Product_ID int not null,
Total decimal not null,
Tax decimal not null,
foreign key (Order_ID) references Orders(Order_ID),
foreign key (Product_ID) references Products(Product_ID),
primary key(Order_ID, Product_ID)
);

/*
* Propagation of table data
*/

insert into Products (Name, Price, Barcode, Stock, Producer) values(
"Cereal", 2.0, "123ABC", 5, "Kellogs");

insert into Products (Name, Price, Barcode, Stock) values(
"B", 5, "ABC123", 10);

insert into Products (Name, Price, Barcode, Stock, Producer, Producer_Contact) values(
"Pancakes", 12.0, "111222", 15, "Me Org.", "Myself");

insert into Products (Name, Price, Barcode, Stock, Producer, Producer_Contact) values(
"D", 13.0, "333444", 18.0, "qwerty", "uiop");

insert into Products (Name, Price, Barcode, Stock, Producer, Producer_Contact) values(
"E", 10000.0, "678900", 1, "PEAR Technology", "James John");

insert into Orders (Total) values(
10000);

insert into Orders (Total) values(
27.0);

insert into Orders (Total) values(
14.0);

insert into Orders (Total) values(
25.00);

insert into Orders (Total) values(
13);

insert into Orders (Total) values(
7);

insert into Orders (Total) values(
24);

insert into Orders (Total) values(
6);

insert into Orders (Total) values(
26);

insert into Orders (Total) values(
10);

insert into Bought values(
1, 5, 10000, 11000);

insert into Bought values(
2, 3, 12, 1.2);

insert into Bought values(
2, 4, 13, 1.3);

insert into Bought values(
2, 1, 2, 0.2);

insert into Bought values(
10, 2, 10, 1);

/*
* Table Dumps
*/

select * from Products;
select * from Orders;
select * from Bought;