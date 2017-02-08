# DataStructures

A repository for the data structures I built for my CS-160 course and the projects they were used for.<br /> <br />
All folders labeled something\<T\> are the data structures themselves, all others are the projects. <br /><br />Below is a description of
each project.<br /><br /><br /><br />
###MassiveAdder
An adder or subtractor for number far larger than can be stored in standard data types.<br /><br />
Reads in the operators and operands from a file, with each line representing a number, '+', or '-'.<br /><br />
Uses nine's complement addition for subtraction and outputs the results to the command line.<br /><br />
The file to be read should be of the following format and accepts negative numbers:<br /><br />
minuend<br />
subtrahend<br />
operator(+ or -)<br />
etc.<br /><br /><br />
###PolynomialCalculator<br />
A polynomial calculator for polynomial operators +, -, *. Reads in the operators from a file in postfix notation.<br /><br />
Uses LinkedList\<T\> to store each term in the polynomial and Stack\<T\> to store the operands while they are computed.<br /><br />
Each line representing an operand should be in the following format:<br /><br />
coefficient exponent coefficient exponent coefficient exponent<br /><br />
So<br />
10 5 5 3 2 6 7 4 7 3<br /><br />
Represents<br />
10x^5 + 5x^3 + 2x^6 + 7x^4 + 7x^3<br />
