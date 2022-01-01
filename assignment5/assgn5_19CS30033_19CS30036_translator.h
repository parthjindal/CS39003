/*
NAMES: PRANAV RAJPUT (19CS30036), PARTH JINDAL(19CS30033)
SUBJECT: COMPILERS LAB
ASSIGNMENT: 5
*/

#ifndef __TRANSLATION_H
#define __TRANSLATION_H

// including header files needed
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>

using namespace std;

extern char* yytext;
extern int yyparse();

// defining constants for type sizes
#define size_of_char 1
#define size_of_int 4
#define size_of_float 8
#define size_of_ptr 4

//sizes are defined as constants as hardcoded values make the program machine-dependent
//these values can be changed according to the machine it is being executed on

//CLASS DECLARATIONS
class symbol;
class quad;
class label;
class symType;
class symTable;
class quadArray;

struct expression;
struct statement;
struct Array;

extern symbol* currS;

extern symTable* ST;
extern symTable* parST;
extern symTable* globalST;

extern quadArray QArray;
extern std::string varType;
extern std::string loopName;
extern long long int tableCount;
extern std::vector<label> labelList;

//CLASS DEFINITIONS

//-- CLASS SYMBOL
class symbol {
   public:
    std::string name;    // name of the symbol
    symType* type;       // type of the symbol
    string val;          // initial value
    int size;            // size of the symbol
    int offset;          // offset of the symbol in ST
    symTable* nestedST;  // ptr to nested symbol table

    /******CONSTRUCTOR********/
    symbol(string name_, string type_ = "int",
           symType* ptr = NULL,
           int width = 0);
    symbol* update(symType* ts);
};

class label {
   public:
    string name;
    int addr;
    std::list<int> nextList;
    label(string name_, int addr_ = -1);
};

//TODO: add a constructor for label

//--CLASS QUAD
class quad {
   public:
    // res = arg1 op arg2
    std::string res;
    std::string arg1;
    std::string op;
    std::string arg2;

    // function to print the current quad
    void print();

    // Constructors for quad initialization
    quad(std::string res, std::string arg1, std::string op = "=", std::string arg2 = "");
};

//--CLASS SYMBO TYPW

class symType {
   public:
    std::string type;  // string to store symbol type
    symType* ptr;      // pointer to elements in case of complex symbol type such as array
    int width;         // width if arrType

    /******CONSTRUCTOR********/
    symType(std::string type, symType* ptr = NULL, int width = 1);
};

// --CLASS QUAD ARRAY

class quadArray {
   public:
    // vector to store all quads in code
    std::vector<quad> array;
    // member function to print all the quads
    void print();
};

//--CLASS SYMTABLE
class symTable {
   public:
    std::string name;         // name of the symbol table
    int count;                // counter for temp variables
    std::list<symbol> table;  // list of symbols in the table
    symTable* parent;         // ptr to parent symbol table

    //member functions
    symTable(std::string name_ = "NULL");
    ~symTable() {}

    void update();                         // update the symbol table
    void print();                          // print the symbol table
    symbol* lookup(std::string symbName);  // lookup a symbol in the symbol table and return prt to it
};

struct statement {
    // list to store statements for dangling exits
    std::list<int> nextList;
};

struct expression {
    // string to store type
    std::string type;
    // pointer to the entry in symbol table
    symbol* loc;
    // next list for statement expressions
    std::list<int> nextList;
    // false list for boolean expressions
    std::list<int> falseList;
    // true list for boolean expressions
    std::list<int> trueList;
};

// emit function used by the parser in overloaded state
void emit(string op, string res, string arg1 = "", string arg2 = "");
void emit(string op, string res, int arg1, string arg2 = "");
void emit(string op, string res, float arg1, string arg2 = "");

//GENTEMP FUNCTION
symbol* gentemp(symType* T, string initVal = "");

// inserting target label into group of quads i.e. list<int> L
void backpatch(list<int> L, int i);
// making a new list with only the integer address passed as parameter
list<int> makelist(int i);
// function to merge the 2 lists L1 and L2 passed as parameters
list<int> merge(list<int>& L1, list<int>& L2);

struct Array {
    // string to store type of array [pointers , elements]
    string artype;
    // symbol type of generated subarray stored
    // important for when multidimensional array in encountered
    symType* type;
    // pointer to store location of array
    symbol* loc;
    // pointer to symbol table entry
    symbol* Sarr;
};

// LIST RELATED FUNCTIONS

// BOOLEAN RELATED FUNCTIONS

// function for conversion of boolean expression to int
expression* convertBool2Int(expression*);
// function for conversion of integer expression to int
expression* convertInt2Bool(expression*);

// overloaded function to check if the symbol type is same for 2 symbols
bool checkType(symbol*& c1, symbol*& c2);
bool checkType(symType* s1, symType* s2);

// function to get the size of the symbol
int typeSize(symType*);

// function to get the type of the symbol
string typeGet(symType*);

// returns the number of the next instruction
int nextInstruction();

// global function for the conversion of symbol to the type stored in string
symbol* convert(symbol*, string);

// changing table passed as paramater to a new symbol table
void changeTable(symTable*);
label* findLabel(string name);

#endif  // __TRANSLATION_H
