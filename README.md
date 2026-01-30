Library Management System in C++
================================
This project is a console-based Library Management System implemented in C++. It allows a user to manage books in a library by performing operations such as adding books, searching for books, issuing and returning books, and generating receipts with fine calculation for late returns.
The project demonstrates object-oriented programming concepts, file handling, and time/date handling in C++.

Project Overview
================
The Library Management System maintains a collection of books in memory and provides a menu-driven interface for interaction. Each book has a unique ID, title, author, and issue status. When a book is issued or returned, a receipt is generated and saved to a text file.
The system also calculates fines automatically if a book is returned after the allowed borrowing period.

Features
========
Add new books to the library
Display all available books
Search books by Book ID
Issue books and record issue date
Return books with automatic fine calculation
Generate receipt file for issue and return operations
Menu-driven console interface
Uses object-oriented design (classes and encapsulation)

Technologies Used
=================
C++
Standard Template Library (STL)
File handling using fstream
Time and date handling using ctime

Program Structure
================
Classes Used
------------
Book Class

Stores book details such as ID, title, author
Maintains issue status and issue date
Displays book information

Library Class

Manages the collection of books
Handles issuing and returning of books
Calculates fines
Generates receipts

Fine Calculation Logic
======================
Maximum allowed issue period: 30 days
Fine amount: ₹100 per extra day
Fine is calculated automatically during book return

Receipt Generation
===================

For every issue or return operation, a receipt is generated in a file named:
receipt.txt

The receipt includes:

Date and time
Book details
Operation performed (Issued / Returned)
Issue date
Fine amount (if applicable)

Author
======
Neha Kumari
Computer Science Student
