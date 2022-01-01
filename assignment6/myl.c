/**
 * @file ass2_19CS30033.c
 * @author Parth Jindal (pmjindal@gmail.com)
 * @brief Library implementation for the assignment 2
 * @version 0.1
 * @date 2021-09-01
 * 
 * @copyright Copyright (c) 2021
 *  
 */

#include "myl.h"

#include <stdio.h>
#define BUFFSIZE 100
#define INT32_MAX +2147483647
#define INT32_MIN -2147483648

/**
 * @brief Prints the string to the console (stdout)
 * 
 * @param str : Pointer to the string to be printed
 * @return int : Returns no. of characters printed
 */
int printStr(char *str) {
    int len = 0;
    while (str[len] != '\0') len++;
    // inline asm
    __asm__ __volatile__(
        "movl $1, %%eax \n\t"  // sys_write
        "movq $1, %%rdi \n\t"  // stdout
        "syscall \n\t"
        :
        : "S"(str), "d"(len));  // input
    return len;
}

/**
 * @brief Prints the integer to the console (stdout)
 * 
 * @param n : Integer to be printed
 * @return int : Returns no. of characters printed
 */
int printInt(int n) {
    char buff[20], zero = '0';
    int i = 0, bytes;
    int flag = 1;
    if (n == 0)
        buff[i++] = zero;
    else {
        // if negative store the sign at the first index
        if (n < 0) {
            buff[i++] = '-';
            flag = -1;
        }
        while (n) {
            int d = n % 10;
            d = d * flag;
            buff[i++] = (char)(zero + d);
            n /= 10;
        }
        int j = 0;
        if (flag == -1) j = 1;
        int k = i - 1;
        // reverse the string
        while (j < k) {
            char temp = buff[j];
            buff[j++] = buff[k];
            buff[k--] = temp;
        }
    }
    bytes = i;
    // inline assembly to print the string
    __asm__ __volatile__(
        "movl $1, %%eax\n\t"  // sys_write
        "movq $1, %%rdi\n\t"  // stdout
        "syscall \n\t"
        :
        : "S"(buff), "d"(bytes));  // input
    return bytes;                  // return chars written
}

/**
 * @brief Reads an integer from the console (stdin)
 * 
 * @param n : Pointer to the integer to store the read value
 * @return int : OK if successful, ERROR otherwise
 * @note: If more than 12 characters are read, the function returns ERROR or 
 *        if the input is out of range(INT32_MIN, INT32_MAX), 
 *        it returns ERROR
 */
int readInt(int *ep) {
    char buff[BUFFSIZE];
    int ret;
    int res = 0;

    __asm__ __volatile__(
        "movl $0, %%eax\n\t"  // sys_read
        "movq $0, %%rdi\n\t"  // stdin
        "syscall \n\t"
        : "=a"(ret)                   // output
        : "S"(buff), "d"(BUFFSIZE));  // input
    if (ret <= 1) {
        *ep = ERR;
        return res;
    }  // system-error or LF or EOF

    int sgn = 1;
    int i = 0;

    /* check for +/- */
    if (buff[0] == '-') {
        sgn = -1;
        i++;
    }
    if (buff[0] == '+') i++;

    // check for more than 12 characters
    if ((sgn == -1 && ret > 12) ||
        (sgn == 1 && ret > 11) || (buff[0] == '+' && ret > 12)) {
        *ep = ERR;
        return res;
    }

    // '\0' in the end (not-required)
    buff[ret - 1] = 0;
    // convert the string to integer
    for (; i < ret - 1; i++) {
        if (!(buff[i] >= '0' && buff[i] <= '9')) {
            *ep = ERR;
            return res;
        }
        res = res * 10LL + (buff[i] - '0') * sgn;
        // check for overflow
        if (res > INT32_MAX || res < INT32_MIN) {
            *ep = ERR;
            return res;
        }
    }
    *ep = OK;
    return res;
}

/**
 * @brief Reads a floating point number from the console (stdin)
 * 
 * @param f : Pointer to the floating point number to store the read value
 * @return int : OK if successful, ERROR otherwise
 * @note: Checks for read characters being from the set {0-9, '.', '-','e','E'},
 *        and checks according the format of IEEE 754 floating point numbers. 
 */
int readFlt(float *f) {
    char buff[BUFFSIZE];
    float val = 0.0;
    int ret;
    int sgn = 1;
    int i = 0;
    int bfore_d = 0, after_d = 0;

    __asm__ __volatile__(
        "movl $0, %%eax\n\t"  // sys_read
        "movq $0, %%rdi\n\t"  // stdin
        "syscall \n\t"
        : "=a"(ret)                   // output
        : "S"(buff), "d"(BUFFSIZE));  // input
    if (ret <= 1) return ERR;         // system-error or LF or EOF
    int len = ret - 1;
    float den = 1.0;

    /*check for minus sign*/
    if (buff[i] == '-') {
        sgn = -1;
        i++;
    }
    if (buff[0] == '+') i++;

    int dot = 0;
    int e = 0;
    int exp = 0;

    /* read till '.' or 'e' or 'E' */
    while (i < len && (buff[i] >= '0' && buff[i] <= '9')) {
        bfore_d = bfore_d * 10 + (buff[i] - '0');  //store value in bfore_d
        i++;
    }

    /* checks for '.' */
    if (buff[i] == '.') {
        dot = 1;
        i++;
        //read till 'e' or 'E'
        while (i < len && (buff[i] >= '0' && buff[i] <= '9')) {
            after_d = after_d * 10 + (buff[i] - '0');  //store value in after_d
            den *= 10;                                 // store exponent in den
            i++;
        }
    }
    int exp_sign = 1;
    // checks for 'e' or 'E'
    if (buff[i] == 'e' || buff[i] == 'E') {
        e = 1;
        i++;
        if (buff[i] == '-') {  //exp sign check
            exp_sign = -1;
            i++;
        } else if (buff[i] == '+') {
            i++;
        }
        //read till end
        while (i < len && (buff[i] >= '0' && buff[i] <= '9')) {
            exp = exp * 10 + (buff[i] - '0');
            i++;
        }
    }

    //if not all characters are read then return error
    if (i != len) return ERR;

    *f = sgn * (bfore_d + after_d / den);
    float E = 1;
    if (e) {
        while (exp > 0) {
            E *= 10;
            exp--;
        }
        if (exp_sign == -1)
            *f /= E;
        else
            *f *= E;
    }
    return OK;
}
/**
 * @brief Prints a floating point number to the console (stdout)
 * 
 * @param n : The floating point number to print
 * @return int : Number of characters printed
 */
int printFlt(float n) {
    char buff[BUFFSIZE];  // buffer for the string
    char after_d[7];      // store the value after decimal point

    int sgn = n < 0 ? -1 : 1;  // sign
    int a = (int)n;            // integer part

    /* decimal part, add 0.5 to round */
    int dec = (int)((n - a) * 1000000 + 0.5);
    int i = 0;
    if (sgn == -1) buff[i++] = '-';  // add minus sign
    int j = i;
    if (a == 0)
        buff[i++] = '0';
    else
        while (a) {  // convert integer part to string
            int d = a % 10;
            d = d * sgn;
            buff[i++] = (char)('0' + d);
            a /= 10;
        }
    int k = i - 1;
    while (j < k) {  // reverse the string
        char temp = buff[j];
        buff[j++] = buff[k];
        buff[k--] = temp;
    }
    buff[i++] = '.';  // add decimal point
    int l = 0;
    while (dec) {  // convert decimal part to string
        int d = dec % 10;
        d = d * sgn;
        after_d[l++] = (char)('0' + d);
        dec /= 10;
    }
    int m = 6 - l;                       // add zeros
    while (m--) buff[i++] = '0';         // add zeros
    while (l--) buff[i++] = after_d[l];  // add decimal part

    // inline assembly for printing
    __asm__ __volatile__(
        "movl $1, %%eax\n\t"  // sys_write
        "movq $1, %%rdi\n\t"  // stdout
        "syscall \n\t"
        :
        : "S"(buff), "d"(i));  // input
    return i;
}
