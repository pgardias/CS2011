/* 
 * CS:APP Data Lab 
 * 
 * Przemek Gardias (pmgardias)
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
/* We do not support C11 <threads.h>.  */
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
  /* 0x55555555 is half of a max signed 32-bit integer, 
   * which is in binary alternating 1's & 0's with the 
   * least significant bit set to 0 
   */
  int x, shift;
  x = 0x55;
  shift = x | x << 8;
  return shift | shift << 16;
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  /* Return 1 if max val, otherwise 0 */
  return !(~(x + x + 1) + !(x + 1));
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  /* Application of DeMorgan's Law on (~x & y) | (x & ~y) */
  return (~(~(~x & y) & ~(x & ~y)));
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int a;
  /* Reverse state then add one to boolean of x */
  a = ~(!!x) + 1;

  /* Return true if either case is true */
  return (a & y) | (~a & z);
}
/* 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4 
 */
int greatestBitPos(int x) {
  int a;
  /* A equal to compared x shifted right 1 */
  a = x | (x >> 1);

  /* If not equal, shift A right 2^x bits right, x = 0..4 */
  a = a | a >> 1;
  a = a | a >> 2;
  a = a | a >> 4;
  a = a | a >> 8;
  a = a | a >> 16;

  /* Mask with 0100.. */
  return ((a ^ (a >> 1)) | (0x80 << 24)) & a;
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  int negPosMask, round, divide, zeroMask;
  
  /* Set mask based on sign */
  negPosMask = x >> 31;

  /* Round towards 0 */
  round = ((0x01 << n) + (~0x00)) & negPosMask;
  divide = (x + round) >> n;

  /* For negative round to 0 */
  zeroMask = (~(!n) << 31) >> 31;

  /* Handle 0 and non-0 cases */
  return (divide & zeroMask) | (x & (~zeroMask));
}
/* 
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
  // Return true if leading bit is 0 (positive)
  return !(x >> 31);
}
/*
 * satMul3 - multiplies by 3, saturating to Tmin or Tmax if overflow
 *  Examples: satMul3(0x10000000) = 0x30000000
 *            satMul3(0x30000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0x70000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0xD0000000) = 0x80000000 (Saturate to TMin)
 *            satMul3(0xA0000000) = 0x80000000 (Saturate to TMin)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 3
 */
int satMul3(int x) {
  int Tmin, Tmax, xby2, xby3, overflow;
  /* Maximum val */
  Tmin = 0x1 << 31;

  /* Minimum val */
  Tmax = x >> 31;

  /* Multiply by 2 */
  xby2 = x + x;

  /* Multiply by 3 */
  xby3 = xby2 + x;

  /* Compare sign bits of x, xby2, xby3 otherwise overflow */
  overflow = ((x ^ xby2) | (x ^ xby3)) >> 31;

  /* Return correct case */
  return ((~overflow) & xby3) + (overflow & (Tmin + (~Tmax)));
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  /* Different sign OR overflow when subtracting */
  int xor, signCheck, sum;

  /* Xor the variables to get mask */
  xor = x ^ y;

  signCheck = xor & y;
  sum = ~x + y + 1;

  return 1 & (((sum & ~xor) | signCheck) >> 31);
}
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int sign, upper, lower;
  sign = 0x1 << 31;

  /* Upper bound */
  upper = ~(sign | 0x39);

  /* Lower bound */
  lower = ~0x30;

  /* Add x to bound and check sign bit */
  upper = sign & (upper + x) >> 31;
  lower = sign & (lower + x + 1) >> 31;
  
  /* If either result is negative return false */
  return !(upper | lower);
}
/*
 * trueFiveEighths - multiplies by 5/8 rounding toward 0,
 *  avoiding errors due to overflow
 *  Examples: trueFiveEighths(11) = 6
 *            trueFiveEighths(-9) = -5
 *            trueFiveEighths(0x30000000) = 0x1E000000 (no overflow)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 4
 */
int trueFiveEighths(int x) {
  int sign, fraction, temp;

  /* Get sign */
  sign = (x >> 31) & 1;

  /* Isolate fraction bits */
  fraction = x & 7;
  temp = fraction;
  temp = ((temp << 2) + temp) >> 3;

  /* Divide by 8 */
  x = (x >> 3);

  /* Multiply by 5 and afterwards add remainder */
  x = ((x << 2) + x) + temp;

  /* Add one if there was a remainder */
  x = x + ((!!(fraction)) & sign);

  return x;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  
  int mask1, mask2, mask3, mask4, ans, shift;

  /* Masks to check first x bits.., x = 32, 16, 8, 4,... */
  mask1 = 0xFF << 24 | 0xFF << 16;
  mask2 = 0xFF << 8;
  mask3 = 0xF0;
  mask4 = 0x0C;

  /* Grab top 32 bits, shift them down and repeat */
  ans = !!(x & mask1) << 4;
  x >>= ans;

  /* Grab next 16 bits */
  shift = !!(x & mask2) << 3;
  x >>= shift;

  ans += shift;

  /* Next 8 bits */
  shift = !!(x & mask3) << 2;
  x >>= shift;

  ans += shift;

  shift = !!(x & mask4) << 1;
  x >>= shift;

  ans += shift;

  /* Check second to last bit */
  ans += (x >> 1);
  
  return ans;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
  int rshift, fraction;
  /* Right shift float */
  rshift = ((uf >> 23) & 0xFF);

  /* Float fraction */
  fraction = (uf & ((0x1 << 23) + (~0)));

  /* Case for 1111.. */
  if (rshift == 0xFF && fraction) {
    return uf;
  } else {
    /* Flip bits */
    return uf ^ (1u << 31);
  }
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  unsigned int neg, shift, exponent, finalBit, finalBitShifted, guard, ans;
  int Tmin, rounded;

  /* Set minimum val */
  Tmin = 0x80000000;
  shift = 0;

  /* If x is 0, return 0 */
  if (!x) {
    return 0;
  }

  if (x < 0) {
    /* Set to minimum val */
    neg = Tmin;
  } else {
    neg = 0;
  }

  if (neg) {
    x = -x;
  }

  while (!(Tmin & x)) {
    /* Shift and keep track of shift in counter */
    x <<= 1;
    shift++;
  }

  finalBit = x << 1;
  
  /* Get exponent */
  exponent = 158 - shift;
  
  /* Set guard */
  guard = (finalBit & 0x200) >> 9;

  /* Round to nearest number */
  rounded = finalBit & 0x000001ff;

  /* Shift right */
  finalBitShifted = finalBit >> 9;

  /* Final float */
  ans = neg + (exponent << 23) + finalBitShifted;

  if (rounded > 0x00000100 || ((rounded == 0x00000100) && guard)) {
    return neg + (exponent << 23) + finalBitShifted + 1;
  }
  return ans;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  unsigned int exponent, sign, denormFrac;
  /* Get exponent */
  exponent = (uf >> 23) & 0xFF;

  /* Get sign */
  sign = uf & 0x80000000;

  /* Denormalized fraction */
  denormFrac = uf & 0x007FFFFF;

  /* Edge cases of invalid numbers, return if true */
  if (exponent == 255 || (exponent == 0 && denormFrac == 0)) {
    return uf;
  } 
  if (exponent) {
    /* Increment exponent */
    exponent += 1;
  } else if (denormFrac == 0x007FFFFF) {
    /* Decrement fraction by 1, increment exponent */
    denormFrac -= 1;
    exponent += 1;
  } else {
    /* Left shift fraction */
    denormFrac <<= 1;
  }
  
  return sign | (exponent << 23) | denormFrac;
}
