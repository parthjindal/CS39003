#include <bits/stdc++.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "assgn6_19CS30033_19CS30036_translator.h"

using namespace std;

extern FILE *yyin;
extern vector<string> stringList;

// file name parameters
string IPFname;
string ASMfn;

// map from quads to labels
map<int, int> Mlabel;

// counter variable to count the number of labels in the asm file
int countLabel = 0;
// vector of quads
vector<quad> Qarr;

// function to compute activation record
void ActivationRec(symTable *S) {
    // p -> parameter
    // l -> local
    int l = -24, p = -20;

    for (auto it = S->table.begin(); it != S->table.end(); it++) {
        if (it->name == "return") continue;
        // checking category
        else if (it->cat == "param") {  // parameter
            // assigning p (param)
            S->AR[it->name] = p;
            // adding entry size to p
            p = p + it->size;
        } else {  // case for local symbols
            // assigning l (local)
            S->AR[it->name] = l;
            // subtracting entry size from l
            l = l - it->size;
        }
    }
    return;
}

// generate ASM
void ASMgenerate() {
    Qarr = QArray.array;
    int ctr = 0;

    // Array traversal to update goto labels
    vector<quad>::iterator i = Qarr.begin();
    vector<string> vv = {"NEOP", "EQOP", "GOTOOP", "GT", "LE", "LT", "GE"};
    while (i != Qarr.end()) {
        for (auto x : vv) {
            if (x.compare(i->op) == 0) {
                // converting string to int
                int k = atoi(i->res.c_str());
                Mlabel[k] = 1;
            }
        }
        ++i;
    }

    // traversing the label map and mapping quads to labels
    map<int, int>::iterator j = Mlabel.begin();
    while (j != Mlabel.end()) {
        j->second = ctr;
        ctr++;
        j++;
    }
    // list of tables
    list<symTable *> TList;
    // collect all tables
    for (auto it = globalST->table.begin(); it != globalST->table.end(); it++) {
        if (it->nestedST != nullptr)
            TList.push_back(it->nestedST);
    }
    // traversing nested tablelist and computing activation record
    for (auto it = TList.begin(); it != TList.end(); it++) {
        ActivationRec(*it);
    }
    // stream for assembly file (.s)
    ofstream sout;
    // open .s for writing
    sout.open(ASMfn.c_str(), ios::out);

    sout << "\t.file\t\"test.c\""
         << "\n";

    // writing .globl for all global variables (skip functions for now)
    for (auto m = ST->table.begin(); m != ST->table.end(); m++) {
        string cy = m->cat;         // category
        string ch = m->type->type;  // type
        string nm = m->name;        // name

        if (cy == "function")  // skip function
            continue;
        else {
            // INT
            if (ch == "INT") {
                if (m->val == "")
                    sout << "\t.comm\t" << nm << ", 4, 4"
                         << "\n";
                else {
                    sout << "\t.globl\t" << nm << "\n";
                    sout << "\t.data"
                         << "\n";
                    sout << "\t.align 4"
                         << "\n";
                    sout << "\t.type\t" << nm << ", @object"
                         << "\n";
                    sout << "\t.size\t" << nm << ", 4"
                         << "\n";
                    sout << nm << ":"
                         << "\n";
                    sout << "\t.long\t" << m->val << "\n";
                }
            } else if (ch == "CHAR") {
                if (m->val == "")
                    sout << "\t.comm\t" << nm << ", 1, 1"
                         << "\n";

                else {
                    sout << "\t.globl\t" << nm << "\n";
                    sout << "\t.type\t" << nm << ", @object"
                         << "\n";
                    sout << "\t.size\t" << nm << ", 1"
                         << "\n";
                    sout << nm << ":"
                         << "\n";
                    int vd = atoi(m->val.c_str());
                    sout << "\t.byte\t" << vd << "\n";
                }
            }
        }
    }

    // input strings being outputted
    if (stringList.size() > 0) {
        sout << "\t.section\t.rodata\n";
        vector<string>::iterator i = stringList.begin();

        while (i != stringList.end()) {
            int temp = i - stringList.begin();
            sout << ".LC" << temp << ":"
                 << "\n";
            sout << "\t.string\t" << *i << "\n";
            i++;
        }
    }

    // TEXT SEGMENT
    // start
    sout << "\t.text	"
         << "\n";

    vector<string> params;
    std::map<string, int> theMap;
    for (vector<quad>::iterator it = Qarr.begin(); it != Qarr.end(); it++) {
        if (Mlabel.count(it - Qarr.begin())) {
            sout << ".L" << (2 * countLabel + Mlabel.at(it - Qarr.begin()) + 2) << ": " << endl;
        }
        string op = it->op;
        string result = it->res;
        string arg1 = it->arg1;
        string arg2 = it->arg2;
        string s = arg2;

        // if param -> add to the param list
        if (op == "PARAM") {
            params.push_back(result);
            cout << "here" << endl;
        } else {
            sout << "\t";

            // Binary Operations
            // addition operation
            if (op == "ADD") {
                bool flag = true;
                if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
                    flag = false;
                else {
                    char *p;
                    strtol(s.c_str(), &p, 10);
                    if (*p == 0)
                        flag = true;
                    else
                        flag = false;
                }
                if (flag) {
                    sout << "addl \t$" << atoi(arg2.c_str()) << ", " << ST->AR[arg1] << "(%rbp)";
                } else {
                    sout << "movl \t" << ST->AR[arg1] << "(%rbp), "
                         << "%eax" << endl;
                    sout << "\tmovl \t" << ST->AR[arg2] << "(%rbp), "
                         << "%edx" << endl;
                    sout << "\taddl \t%edx, %eax\n";
                    sout << "\tmovl \t%eax, " << ST->AR[result] << "(%rbp)";
                }
            }
            // subtract operation
            else if (op == "SUB") {
                sout << "movl \t" << ST->AR[arg1] << "(%rbp), "
                     << "%eax" << endl;
                sout << "\tmovl \t" << ST->AR[arg2] << "(%rbp), "
                     << "%edx" << endl;
                sout << "\tsubl \t%edx, %eax\n";
                sout << "\tmovl \t%eax, " << ST->AR[result] << "(%rbp)";
            }
            // multiplcation operator
            else if (op == "MULT") {
                sout << "movl \t" << ST->AR[arg1] << "(%rbp), "
                     << "%eax" << endl;
                bool flag = true;
                if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
                    flag = false;
                else {
                    char *p;
                    strtol(s.c_str(), &p, 10);
                    if (*p == 0)
                        flag = true;
                    else
                        flag = false;
                }
                if (flag) {
                    sout << "\timull \t$" << atoi(arg2.c_str()) << ", "
                         << "%eax" << endl;
                    symTable *t = ST;
                    string val;
                    for (list<symbol>::iterator it = t->table.begin(); it != t->table.end(); it++) {
                        if (it->name == arg1) val = it->val;
                    }
                    theMap[result] = atoi(arg2.c_str()) * atoi(val.c_str());
                } else
                    sout << "\timull \t" << ST->AR[arg2] << "(%rbp), "
                         << "%eax" << endl;
                sout << "\tmovl \t%eax, " << ST->AR[result] << "(%rbp)";
            }
            // divide operation
            else if (op == "DIVIDE") {
                sout << "movl \t" << ST->AR[arg1] << "(%rbp), "
                     << "%eax" << endl;
                sout << "\tcltd" << endl;
                sout << "\tidivl \t" << ST->AR[arg2] << "(%rbp)" << endl;
                sout << "\tmovl \t%eax, " << ST->AR[result] << "(%rbp)";
            }

            // Bit Operators /* Ignored */
            else if (op == "MODOP")
                sout << result << " = " << arg1 << " % " << arg2;
            else if (op == "XOR")
                sout << result << " = " << arg1 << " ^ " << arg2;
            else if (op == "INOR")
                sout << result << " = " << arg1 << " | " << arg2;
            else if (op == "BAND")
                sout << result << " = " << arg1 << " & " << arg2;
            // Shift Operations /* Ignored */
            else if (op == "LEFTOP")
                sout << result << " = " << arg1 << " << " << arg2;
            else if (op == "RIGHTOP")
                sout << result << " = " << arg1 << " >> " << arg2;

            // copy
            else if (op == "EQUAL") {
                s = arg1;
                bool flag = true;
                if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
                    flag = false;
                else {
                    char *p;
                    strtol(s.c_str(), &p, 10);
                    if (*p == 0)
                        flag = true;
                    else
                        flag = false;
                }
                if (flag)
                    sout << "movl\t$" << atoi(arg1.c_str()) << ", "
                         << "%eax" << endl;
                else
                    sout << "movl\t" << ST->AR[arg1] << "(%rbp), "
                         << "%eax" << endl;
                sout << "\tmovl \t%eax, " << ST->AR[result] << "(%rbp)";
            } else if (op == "EQUALSTR") {
                sout << "movq \t$.LC" << arg1 << ", " << ST->AR[result] << "(%rbp)";
            } else if (op == "EQUALCHAR") {
                sout << "movb\t$" << atoi(arg1.c_str()) << ", " << ST->AR[result] << "(%rbp)";
            }

            // Relational Operations
            else if (op == "EQOP") {
                sout << "movl\t" << ST->AR[arg1] << "(%rbp), %eax\n";
                sout << "\tcmpl\t" << ST->AR[arg2] << "(%rbp), %eax\n";
                sout << "\tje .L" << (2 * countLabel + Mlabel.at(atoi(result.c_str())) + 2);
            } else if (op == "NEOP") {
                sout << "movl\t" << ST->AR[arg1] << "(%rbp), %eax\n";
                sout << "\tcmpl\t" << ST->AR[arg2] << "(%rbp), %eax\n";
                sout << "\tjne .L" << (2 * countLabel + Mlabel.at(atoi(result.c_str())) + 2);
            } else if (op == "LT") {
                sout << "movl\t" << ST->AR[arg1] << "(%rbp), %eax\n";
                sout << "\tcmpl\t" << ST->AR[arg2] << "(%rbp), %eax\n";
                sout << "\tjl .L" << (2 * countLabel + Mlabel.at(atoi(result.c_str())) + 2);
            } else if (op == "GT") {
                sout << "movl\t" << ST->AR[arg1] << "(%rbp), %eax\n";
                sout << "\tcmpl\t" << ST->AR[arg2] << "(%rbp), %eax\n";
                sout << "\tjg .L" << (2 * countLabel + Mlabel.at(atoi(result.c_str())) + 2);
            } else if (op == "GE") {
                sout << "movl\t" << ST->AR[arg1] << "(%rbp), %eax\n";
                sout << "\tcmpl\t" << ST->AR[arg2] << "(%rbp), %eax\n";
                sout << "\tjge .L" << (2 * countLabel + Mlabel.at(atoi(result.c_str())) + 2);
            } else if (op == "LE") {
                sout << "movl\t" << ST->AR[arg1] << "(%rbp), %eax\n";
                sout << "\tcmpl\t" << ST->AR[arg2] << "(%rbp), %eax\n";
                sout << "\tjle .L" << (2 * countLabel + Mlabel.at(atoi(result.c_str())) + 2);
            } else if (op == "GOTOOP") {
                sout << "jmp .L" << (2 * countLabel + Mlabel.at(atoi(result.c_str())) + 2);
            }

            // Unary Operators
            else if (op == "ADDRESS") {
                sout << "leaq\t" << ST->AR[arg1] << "(%rbp), %rax\n";
                sout << "\tmovq \t%rax, " << ST->AR[result] << "(%rbp)";
            } else if (op == "PTRR") {
                sout << "movl\t" << ST->AR[arg1] << "(%rbp), %eax\n";
                sout << "\tmovl\t(%eax),%eax\n";
                sout << "\tmovl \t%eax, " << ST->AR[result] << "(%rbp)";
            } else if (op == "PTRL") {
                sout << "movl\t" << ST->AR[result] << "(%rbp), %eax\n";
                sout << "\tmovl\t" << ST->AR[arg1] << "(%rbp), %edx\n";
                sout << "\tmovl\t%edx, (%eax)";
            } else if (op == "UMINUS") {
                sout << "negl\t" << ST->AR[arg1] << "(%rbp)";
            } else if (op == "BNOT")
                sout << result << " = ~" << arg1;
            else if (op == "LNOT")
                sout << result << " = !" << arg1;
            else if (op == "ARRR") {
                int off = 0;
                off = theMap[arg2] * (-1) + ST->AR[arg1];
                sout << "movq\t" << off << "(%rbp), "
                     << "%rax" << endl;
                sout << "\tmovq \t%rax, " << ST->AR[result] << "(%rbp)";
            } else if (op == "ARRL") {
                int off = 0;
                off = theMap[arg1] * (-1) + ST->AR[result];
                sout << "movq\t" << ST->AR[arg2] << "(%rbp), "
                     << "%rdx" << endl;
                sout << "\tmovq\t"
                     << "%rdx, " << off << "(%rbp)";
            } else if (op == "RETURN") {
                if (result != "")
                    sout << "movl\t" << ST->AR[result] << "(%rbp), "
                         << "%eax";
                else
                    sout << "nop";
            } else if (op == "PARAM") {
                params.push_back(result);
            }

            // call a function
            else if (op == "CALL") {
                // Function Table
                symTable *t = globalST->lookup(arg1)->nestedST;
                int i, j = 0;  // index
                for (list<symbol>::iterator it = t->table.begin(); it != t->table.end(); it++) {
                    i = distance(t->table.begin(), it);
                    if (it->cat == "param") {
                        if (j == 0) {
                            // the first parameter to the function
                            sout << "movl \t" << ST->AR[params[i]] << "(%rbp), "
                                 << "%eax" << endl;
                            sout << "\tmovq \t" << ST->AR[params[i]] << "(%rbp), "
                                 << "%rdi" << endl;
                            j++;
                        } else if (j == 1) {
                            // the second parameter to the function
                            sout << "movl \t" << ST->AR[params[i]] << "(%rbp), "
                                 << "%eax" << endl;
                            sout << "\tmovq \t" << ST->AR[params[i]] << "(%rbp), "
                                 << "%rsi" << endl;
                            j++;
                        } else if (j == 2) {
                            // the third parameter to the function
                            sout << "movl \t" << ST->AR[params[i]] << "(%rbp), "
                                 << "%eax" << endl;
                            sout << "\tmovq \t" << ST->AR[params[i]] << "(%rbp), "
                                 << "%rdx" << endl;
                            j++;
                        } else if (j == 3) {
                            // the fourth parameter to the function
                            sout << "movl \t" << ST->AR[params[i]] << "(%rbp), "
                                 << "%eax" << endl;
                            sout << "\tmovq \t" << ST->AR[params[i]] << "(%rbp), "
                                 << "%rcx" << endl;
                            j++;
                        } else {
                            sout << "\tmovq \t" << ST->AR[params[i]] << "(%rbp), "
                                 << "%rdi" << endl;
                        }
                    } else
                        break;
                }
                params.clear();
                sout << "\tcall\t" << arg1 << endl;
                sout << "\tmovl\t%eax, " << ST->AR[result] << "(%rbp)";
            }

            else if (op == "FUNC") {
                // prologue of a function
                sout << ".globl\t" << result << "\n";
                sout << "\t.type\t" << result << ", @function\n";
                sout << result << ": \n";
                sout << ".LFB" << countLabel << ":" << endl;
                sout << "\t.cfi_startproc" << endl;
                sout << "\tpushq \t%rbp" << endl;
                sout << "\t.cfi_def_cfa_offset 8" << endl;
                sout << "\t.cfi_offset 5, -8" << endl;
                sout << "\tmovq \t%rsp, %rbp" << endl;
                sout << "\t.cfi_def_cfa_register 5" << endl;
                ST = globalST->lookup(result)->nestedST;
                sout << "\tsubq\t$" << ST->table.back().offset + 24 << ", %rsp" << endl;

                // Function Table
                symTable *t = ST;
                int i = 0;
                for (list<symbol>::iterator it = t->table.begin(); it != t->table.end(); it++) {
                    if (it->cat == "param") {
                        if (i == 0) {
                            sout << "\tmovq\t%rdi, " << ST->AR[it->name] << "(%rbp)";
                            i++;
                        } else if (i == 1) {
                            sout << "\n\tmovq\t%rsi, " << ST->AR[it->name] << "(%rbp)";
                            i++;
                        } else if (i == 2) {
                            sout << "\n\tmovq\t%rdx, " << ST->AR[it->name] << "(%rbp)";
                            i++;
                        } else if (i == 3) {
                            sout << "\n\tmovq\t%rcx, " << ST->AR[it->name] << "(%rbp)";
                            i++;
                        }
                    } else
                        break;
                }
            }

            // epilogue of a function
            // function ends
            else if (op == "FUNCEND") {
                sout << "leave\n";
                sout << "\t.cfi_restore 5\n";
                sout << "\t.cfi_def_cfa 4, 4\n";
                sout << "\tret\n";
                sout << "\t.cfi_endproc" << endl;
                sout << ".LFE" << countLabel++ << ":" << endl;
                sout << "\t.size\t" << result << ", .-" << result;
            } else
                sout << "op";
            sout << endl;
        }
    }
    // footnote
    sout << "\t.ident\t	\"Compiled by 19CS30033\"\n";
    sout << "\t.section\t.note.GNU-stack,\"\",@progbits\n";
    sout.close();
}

// printing overloaded operator
template <class T>
ostream &operator<<(ostream &out, const vector<T> &vec) {
    copy(vec.begin(), vec.end(), ostream_iterator<T>(out, " "));
    return out;
}

int main(int argc, char *argv[]) {
    string temp = string(argv[argc - 1]);
    ASMfn = temp.substr(0, temp.find(".")) + ".s";
    IPFname = temp;
    globalST = new symTable("global");
    ST = globalST;
    // setting parser for taking input and opening file
    yyin = fopen(IPFname.c_str(), "r");
    yyparse();
    globalST->update();
    globalST->print();
    QArray.print();

    ASMgenerate();

    return 0;
}
