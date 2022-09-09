create database watchful;
use watchful;

create table user (
	id integer not null primary key auto_increment,
	user varchar(50) not null,
	password varchar(50) not null
);

create table logger (
	id integer not null primary key auto_increment,
	description varchar(150)
);

create table definable (
	id integer not null primary key auto_increment,
	description varchar(50) not null,
	definable varchar(200) not null,
	date_create datetime,
	date_update datetime
);

create table template (
	id integer not null primary key auto_increment,
	description varchar(50) not null unique,
	date_create datetime,
	date_update datetime,
	definable_id integer,
	constraint fk_template_define foreign key (definable_id) references definable(id)
);

create table executable (
	id integer not null primary key auto_increment,
	description varchar(50) not null,
	date_create datetime,
	date_update datetime,
	executable varchar(200) not null,
	sequence integer not null,
	template_id integer,
	constraint fk_executable_template foreign key (template_id) references template(id)
);
