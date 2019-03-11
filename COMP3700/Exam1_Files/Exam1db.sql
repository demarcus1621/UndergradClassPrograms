/*
Demarcus Campbell
Exam 1
*/

create table Books(
Barcode varchar(255) not null primary key,
ISBN int not null,
Name varchar(255) not null
);

create table Readers(
User_ID int not null primary key auto_increment,
Name varchar(50) not null,
Billing_Address varchar(255) not null
);

create table Records(
Record_ID int not null,
User_ID int not null,
Barcode varchar(255) not null,
Checkout_Date date,
Return_Date date,
foreign key(User_ID) references Readers(User_ID),
foreign key(Barcode) references Books(Barcode),
primary key(User_ID, Barcode)
);

