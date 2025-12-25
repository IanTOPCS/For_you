create table employee (
    ID varchar(5),
    person_name varchar(20) primary key,
    street varchar(20),
    city varchar(20)
);

create table company (
    company_name varchar(20) primary key,
    city varchar(20)
);

create table works (
    ID varchar(5)  primary key,
    company_name varchar(20),
    salary numeric(10, 0)
);

create table manages (
    ID varchar(5) primary key,
    manager_id varchar(5)
);