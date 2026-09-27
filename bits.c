/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x|~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x&~y)&~(x&y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if (!x) {
        return !y;
    }
    if (!y) {
        return 0;
    }
    return !((x >> 31) ^ (y >> 31));
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int r;

    r = (v > ((0xFF << 8) | 0xFF)) << 4;
    r = r | (((v >> (r | 8)) > 0) << 3);
    r = r | (((v >> (r | 4)) > 0) << 2);
    r = r | (((v >> (r | 2)) > 0) << 1);
    r = r | ((v >> (r | 1)) > 0);

    return r;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int nshift = n << 3;
    int mshift = m << 3;
    int diff;

    diff = (((x + 0U) >> nshift) & 0xFF) ^
           (((x + 0U) >> mshift) & 0xFF);

    return x ^ ((diff + 0U) << nshift) ^
               ((diff + 0U) << mshift);
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned result = 0;
    int i;

    for (i = 32; i; i = i - 1) {
        result = (result << 1) | (v & 1);
        v = v >> 1;
    }

    return result;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    return ((x + 0U) >> n) & (~0U >> n);
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int y = ~x;
    int count = 0;
    int all;

    all = !(y >> 16);
    count = count + (all << 4);
    y = (y + 0U) << (all << 4);

    all = !(y >> 24);
    count = count + (all << 3);
    y = (y + 0U) << (all << 3);

    all = !(y >> 28);
    count = count + (all << 2);
    y = (y + 0U) << (all << 2);

    all = !(y >> 30);
    count = count + (all << 1);
    y = (y + 0U) << (all << 1);

    all = !(y >> 31);
    count = count + all;
    y = (y + 0U) << all;

    return count + !(y >> 31);
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned ux = x;
    unsigned sign;
    unsigned exponent = 158;
    unsigned fraction;
    unsigned discarded;

    sign = ux & 0x80000000;

    if (sign) {
        ux = -ux;
    }

    if (!ux) {
        return 0;
    }

    while (!(ux & 0x80000000)) {
        ux = ux << 1;
        exponent = exponent - 1;
    }

    fraction = (ux >> 8) & 0x7FFFFF;
    discarded = ux & 0xFF;

    if (discarded > 0x80) {
        fraction = fraction + 1;
    } else if (discarded == 0x80) {
        if (fraction & 1) {
            fraction = fraction + 1;
        }
    }

    /*
     * Addition deliberately allows a rounded fraction of 0x800000
     * to carry into the exponent field.
     */
    return sign | ((exponent << 23) + fraction);
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exponent = uf & 0x7F800000;
    unsigned fraction = uf & 0x007FFFFF;

    if (exponent == 0x7F800000) {
        return uf;
    }

    if (!exponent) {
        return sign | ((uf & 0x7FFFFFFF) << 1);
    }

    exponent = exponent + 0x00800000;

    if (exponent == 0x7F800000) {
        fraction = 0;
    }

    return sign | exponent | fraction;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int exponent;
    unsigned high;
    unsigned value;

    exponent = (uf2 >> 20) & 0x7FF;
    exponent = exponent - 1023;
    high = (uf2 & 0xFFFFF) | 0x100000;

    if (exponent < 0) {
        return 0;
    }

    if (exponent > 30) {
        return 0x80000000u;
    }

    if (exponent <= 20) {
        value = high >> (20 - exponent);
    } else {
        value = (high << (exponent - 20)) |
                (uf1 >> (52 - exponent));
    }

    if (uf2 >> 31) {
        return -value;
    }

    return value;
}
/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x < -149) {
        return 0;
    }

    if (x < -126) {
        return 1 << (x + 149);
    }

    if (x > 127) {
        return 0x7F800000;
    }

    return (x + 127) << 23;
}
