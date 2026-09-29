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
    return ~(x&y)&~(~x&~y);
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
    if(!x){
        return !y;
    }
    if(!y){
        return !x;
    }
    return !((x^y)>>31);
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
    int b1=((v>>16)>0)<<4;
    v=v>>b1;
    int b2=((v>>8)>0)<<3;
    v=v>>b2;
    int b3=((v>>4)>0)<<2;
    v=v>>b3;
    int b4=((v>>2)>0)<<1;
    v=v>>b4;
    int b5=v>1;
    return b1|b2|b3|b4|b5;
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
    int shift=n<<3;
    int y=x>>shift;
    int q=y&0xFF;
    int shiftm=m<<3;
    int z=x>>shiftm;
    int p=z&0xFF;
    int d=p^q;
    q=d<<shiftm;
    p=d<<shift;

    return x^p^q;
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
    unsigned m=0;
    int c=32;
    while(c){
        m=m<<1;
        m=m|(v&1);
        v=v>>1;
        c--;
    }
    return m;
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
    int flag=!n;
    int m=n+flag;
    int p=((0x7fffffff>>m)<<1)|1;
    int q=~flag+1;
    p=p|q;
    int res=(x>>n)&p;

    return res;
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
int v=~x;
    int flag=!v;
    int b1=(!!(v>>16))<<4;
    v=v>>b1;
    int b2=(!!(v>>8))<<3;
    v=v>>b2;
    int b3=(!!(v>>4))<<2;
    v=v>>b3;
    int b4=(!!(v>>2))<<1;
    v=v>>b4;
    int b5=!!(v>>1);
    int p=b1|b2|b3|b4|b5;
    int count=31+(~p+1)+flag;
    return count;
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
    unsigned s=x&0x80000000;
    unsigned u=x;
    int e=158;
    if(!x){
        return 0;
    }
    if(s){
        u=~u+1;
    }
    while(!(u>>31)){
        u=u<<1;
        e=e-1;
    }
    unsigned res=s|(e<<23)|((u>>8)&0x7fffff);
    if((u&0xff)>128-(res&1)){
        res++;
    }
    return res;
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
    unsigned s=uf&0x80000000;
    unsigned e=(uf>>23)&0xff;
    unsigned m=uf&0x7fffff;
    if(e==255){
        return uf;
    }
    if(e==0){
        return s|(m<<1);
    }
    e=e+1;
    if(e==255){
        m=0;
    }

    return s|(e<<23)|m;
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
    unsigned s=uf2>>31;
    int exp=(uf2>>20)&0x7ff;
    int e=exp-1023;
    if(e<0){
        return 0;
    }
    if(e>=31){
        return 0x80000000;
    }
    unsigned v=0x40000000|((uf2&0xfffff)<<10)|(uf1>>22);
    int res=v>>(30-e);
    if(s){
        return -res;
    }
    return res;
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
    if(x<-149){
        return 0;
    }
    if(x>127){
        return 0x7f800000;
    }
    if(x<-126){
        return 1u<<(x+149);
    }
    return (x+127)<<23;
}
