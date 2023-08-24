#!bin/bash

set -e

echo "Create database db.dat with 100 rows and 512 max data for name and email"
./a.out db.dat c 100 512

echo "Set up 4 rows"
./a.out db.dat s 0 oleg oleg@gmail.com
./a.out db.dat s 1 albina top@gmail.com
./a.out db.dat s 2 seva hochetvameriku@gmail.com
./a.out db.dat s 3 seva poedetvameriku@gmail.com

echo "List of db.dat"
./a.out db.dat l

echo "Ordered list of db.dat"
./a.out db.dat l s

echo "Get 1st row"
./a.out db.dat g 1

echo "Delete 1st row"
./a.out db.dat d 1

echo "Redact 2nd row"
./a.out db.dat r 2

echo "Copy the database to another file"
./a.out db.dat y copy.dat 100 512 

echo "Copy.dat list"
./a.out db.dat l

echo "Delete databases"
rm -rf db.dat copy.dat
