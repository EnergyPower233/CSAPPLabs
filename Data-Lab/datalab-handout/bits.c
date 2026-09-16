/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
// 1
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  int temp1 = x & ~y;
  int temp2 = ~x & y;
  //  德·摩根律
  // !(a && b) == !a || !b
  // res == temp1 || temp2
  // !(temp1 || temp2) == !temp1 && !temp2
  // temp1 || temp2 == !(!temp1 && !temp2)
  return ~(~temp1 & ~temp2);
}
/*
 * tmin - return minimum two's complement integer
 * 返回最小的二进制补码整数（补码, 有符号的）
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;
}
// 2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 *
 *  if x == 0x7FFFFFFF
 */
int isTmax(int x) {
  // 10000000000000000000000000000000
  // 0x7FFFFFFF
  //
  // 11111111111111111111111111111111
  // 0x0
  //
  // x + 1 = 0x80000000
  // int t = (x + 1) ^ (0x80000000); // 0 -> Tmax , 不是0
  // return !t;
  // 我们现在要判断一个东西是不是某个数，我们先考虑这个数字及有没有属于这个数本身的性质：
  // 我们发现它具有加1后溢出，按位取反之后与自身相等的性质，但是——
  // 加1后溢出，再按位取反之后与自身相等的有两个数。一个是-1，一个是最大值
  // ~(x + 1) ^ x == 0
  // 验证相等很容易，只需要利用性质a^a = 0就可以了
  // 我们只需要利用这个性质判断它是不是-1或者最大值

  // 这个数是0 -> x 是 tmax或者-1 如果不是-1或者tmax，值为其他数
  int is_not_max_or_neg1 = (~(x + 1) ^ x);
  // 如果是-1 值为1 如果不是-1 值为0
  int is_neg1 = !~x;

  // 我们只有位运算可以用，所以我们只能判断两个0的情况
  // 在这种情况下，a|b ^ 0 == 0，当且仅当两结果均为0时成立
  // 根据按位异或性质， x^0 == x恒成立,可以化简掉^0
  // a && b == 1 当且仅当a与b均不为0时成立
  // 我们希望判断a与b是否同时为1，等价为去判断!a和!b是否同时为0
  // (是max或者neg1的 && 不是neg1)
  return !(is_not_max_or_neg1 | is_neg1);
}
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  /**
  A = 1010
  temp1 = 1 << 1; 10
  temp1 <<= 2 +temp1; 1010
  temp1 <<= 4 + temp1; 10101010
  temp1 <<= 8 + temp1; 1010101010101010
  temp1 <<= 16 + temp1; 10101010101010101010101010101010 0xAAAAAAAA
                        10101011010101111111111111010101
  !(10101010101010101010101010101010 & 10101011010101111111111111010101 ^
 0xAAAAAAAA)
   *
   */
  int temp1 = 0xAA + (0xAA << 8);  // 0xAAAA
  int r = temp1 + (temp1 << 16);   // 0xAAAAAAAA
  return !((x & r) ^ r);
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
  // 考虑 x与其相反数-x, 有 x+(-x) = 0
  // 对于 补码二进制数字x, 有 x + ~x = 0xFFFFFFFF
  // 我们知道 0xFFFFFFFF + 1 溢出为 0x00000000
  //  于是 x的相反数为 ~x + 1;
}
// 3
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0'
 * to '9') Example: isAsciiDigit(0x35) = 1. isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  // 0x30 < x < 0x39 -> 0 < x - 0x30 < 9
  // - 0x30 = ~0x30 + 1
  int neg30 = ~0x30 + 1;
  int mid1 = x + neg30;
  // 0 < mid < 9
  // 如果是一个负数，那符号位肯定是1，gcc，msvc，clang编译器均执行算数右移
  int res1 = mid1 >> 31;  // 如果这个数是0xFFFFFFFF, 就说明x小于0x39，如果是0,
                          // 那说明它大于等于0x39
  res1 += 1;
  // 我们让它+1，如果这个结果是0，说明小于0x39，如果是1，说明大于等于0x39，其对应的bool值正是我们想要的
  // 接下来考虑 0x39， -9 = ~9 + 1 , 我们想要让mid - 9 <=
  // 0,但0不是负数，不能通过符号位直接判断
  // 考虑以上计算均为整数，上式等价为 mid - 10 < 0
  // -10 = ~10 + 1
  int neg10 = ~10 + 1;
  int mid2 = mid1 + neg10;
  int res2 =
      mid2 >> 31;  // 如果这个是数字是0xFFFFFFFF 意味着小于0，是0，意味着大于0
  res2 += 1;       // 我们让它 +1 意味着如果小于0，结果为0， 大于0 结果为 1
  res2 = !res2;    // 反转它，获得我们想要的对应的bool值
  // 我们判断它是不是asciidigit， 实际上是在返回 res1 && res2
  // 考虑到 res1 和 res2只有可能是 0x00000000 和 0x00000001,
  // 其后31位运算没有任何意义，我们完全可以用&来代替&&
  return res1 & res2;
  // operator数差点超了（汗）
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  // 一个基本思路是根据算出来y和z的掩码应用到上
  // 如果x是1那么算出来应该是y，如果x是0那算出来应该是z
  // 就一位能让这么多东西变化这他妈也太雷霆了
  // 管它几把这么多先把x的值标准化了
  x = !!x;
  // 我让D指导给我了一个非常牛逼的提示：
  // 我们知道位运算实际上是分别对每一位进行操作，这个0是0x00000000 1是0x00000001
  // 都只有一位，这太唐诗了
  // 我们直接把1换成-1，这样所有位都是1了
  // 然后我们只需要考虑逻辑运算就可以了，这里相当于完全没有位移的事情
  x = ~x + 1;  // 这样0是0，1是-1 性质非常优美
  // 思考一下
  // 一个数，跟0算出来是z 跟1算出来是y
  // 我现在要找到这个数
  // 这么雷霆，列个表先
  /**
   * 好吧其实我什么都不会
   * D指导跟我说用加法试试
   *
   * D指导是对的
   * 我想的是错的，根本没有这个数
   * 但是我可以换一种思路，把x当作一种权重
   * 我可以构造一个形式， 让y和z分别乘他们的权重再相加
   * 如果权重为1那就保留这个结果，如果权重为0那就放弃这个结果
   * 要求是x如果是1，那返回y，x如果是0，那返回z
   * x现在已经被我变成了如果是0每一位全是0，如果是1每一位都是1
   *
   * 单独考虑每一位
   * 如果x是1，我们保留y放弃z y的权重是1，z的权重是0
   * 如果x是0，我们保留z放弃y y的权重是0，z的权重是1
   *
   * 从统计学意义上讲（）
   * y的权重是x z的权重是!x
   *
   * 这个运算，如果是1就保留，如果是0就清零
   * 我们不禁想到：
   * & | 0 1
   * -------
   * 0 | 0 0
   * 1 | 0 1
   * temp1 = x && y
   * temp2 = (!x) && z
   * 在上面的这种情况下，乘完权重的结果只能得到 y 0 或者 0 z
   * 我们要想办法让这个结果变成 y 或者 z
   *
   * 对于一个不可能进位的加法（两个不可能同时为0）
   * 的加法...
   * 我们可以用或运算偷鸡...?
   * 把逻辑运算符换成位运算符...
   */
  return (x & y) | ((~x) & z);
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int isneg_x = x >> 31;
  int isneg_y = y >> 31;
  // 这里0是0x00000000，1是0xFFFFFFFF 可以不标准化直接用于conditional

  // 考虑 x - y <= 0
  // 小于等于0不方便用符号位判断，全部减1
  // x - y - 1 <= -1  ->  x - y - 1 < 0
  // -y = ~y + 1
  // -y - 1 = ~y
  // x + ~y < 0

  int x_minus_y_plus_1 = x + ~y;
  // 这个式子的结果只有在不发生溢出的情况下才是准确的
  // 对于上式，只需要判断符号位是否为0

  int symb_x_minus_y_plus_1 = x_minus_y_plus_1 >> 31;  // 右移31位
  // 如果是负数，那结果应该是0xFFFFFFFF,加1后结果是0,这个时候x是小于等于y的
  // 如果是正数，那结果应该是0，加1后结果是1，这个时候x是大于y的

  int is_lessOrEQ = !(symb_x_minus_y_plus_1 + 1);
  // 如果进入is_lessOrEQ这个分支，那说明两者同号，不会发生溢出
  // 这意味着在这个分支下，x_minus_y_plus_1的结果是可信的

  int is_diffop = isneg_x ^ isneg_y;
  // 使用异或检查是否相等可以保证依然每一位相同，方便进入condition分支
  // 如果进入is_difop这个分支，必然异号
  // 此时此刻不会发生两个数相等的情况
  // 并且此时 isneg_x 和 isneg_y 必然有一个是-1 有一个是0

  /*注意，如果使用这个变量，那么意味着进入了将要溢出的分支*/

  // int OVERFLOW_is_x_negative_ones = ((isneg_x & x) | (isneg_y & y)) ^ y;

  // (isneg_x & x) | (isneg_y & y)这一部分是获得两个数中的负数
  // 我异或y，意味着如果较小的数是y，那么这个值是0，即x不是那个较小的数，x不是那个负数
  // 两边的合取式必然有一个是0

  // 在这个情况下 假如isneg_x 等于 0xFFFFFFFF, isneg_y 等于0x00000000
  // 原式 = (x | 0) ^ y = x ^ y
  // 两个数不相等，必然结果不为 0，用!!标准化之后为0x00000001
  // 如果反过来 假如isneg_x 等于 0x00000000, isneg_y 等于0xFFFFFFFF
  // 我们将得到 (0 | y) ^ y = 0，用!!标准化后为0x00000000
  // 从统计学意义上讲，OVERFLOW_is_x_negative_ones和isneg_x标准化后的真值是一致的

  // 因此，我们用isneg_x的真值代替OVERFLOW_is_x_negative_ones的真值，大量简化运算
  int OVERFLOW_is_x_less_than_y = !!isneg_x;
  // 如果x小于y，意味着x不是较大的数,顺便标准化
  // (isdiffop) ? (溢出，返回正数) : (不溢出)
  // 如果x不是较大的数,意味着x较小

  int res =
      (is_diffop & OVERFLOW_is_x_less_than_y) | (~is_diffop & is_lessOrEQ);
  // is_diffop是否为0xFFFFFFFF会决定是否进入OVERFLOW_is_x_less_than_y的值是否被保留
  // 如果is_diffop是0xFFFFFFFF，~is_diffop就是0x00000000,
  // 这个时候x_minus_y_plus_1的值是不可信的，~is_diffop会通过按位与运算丢弃is_lessOrEQ的值
  // 两个括号和中间的|分别实现了对两个括号中其中一个括号内的值的保留和对另一个括号内的值的舍弃

  return res;
}
// 4
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x) {
  int symb = (x | (~x + 1)) /* 取符号位 非0 即为 0xFFFFFFFF */ >> 31;
  return symb + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
#include <stdio.h>
int howManyBits(int x) {
  int symb = x >> 31;
  int flag = x ^ symb;
  // 这个flag会把无论是正数还是负数都转换为最高位为1的一串数
  // 根据性质, 我们需要找到len(最高的1)
  // 然后把它加一, 我们就可以得到结果
  // Find highest 1
  // 二分查找
  int res = 1;
  int in_16 = conditional(!!(flag >> 16), 16, 0);
  // printf("%d\n", res);
  flag >>= in_16;
  int in_8 = conditional(!!(flag >> 8), 8, 0);
  flag >>= in_8;
  int in_4 = conditional(!!(flag >> 4), 4, 0);
  flag >>= in_4;
  int in_2 = conditional(!!(flag >> 2), 2, 0);
  // printf("%8x\n", flag);
  flag >>= in_2;
  int in_1 = conditional(!!(flag >> 1), 1, 0);
  // printf("%8x\n", flag);
  // printf("%d\n", res);
  flag >>= in_1;
  res += in_16 + in_8 + in_4 + in_2 + in_1;
  // 此时res即为下标位置
  // 对于flag ,如果x为0,则 flag为0 需要用1位表示
  // 若 x 不为0, flag不为0 右移到最后flag一定为1(二分查找特性)
  return res + flag;
}
// float
/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  unsigned e = (uf >> 23) & 0xFF;
  unsigned f = uf & 0x7FFFFF;
  unsigned s = uf & 0x80000000;
  if (e == 0)
    return s + (f << 1);
  if (e == 0xFF) {
    return uf;  //  合并分支—— NaN 返回本身,无穷大x2依旧还是无穷大
  }
  e++;
  return (e << 23) + f + s;
}
/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  unsigned e = (uf >> 23) & 0xFF;
  unsigned M = (uf & 0x7FFFFF) + 0x800000;  // 23 24位
  // M = 1.f (frac 前补上隐藏的整数位 1), 是 24 位定点数, 缩放因子 2^23
  unsigned s = uf & 0x80000000;
  unsigned res;
  // val_int = 1.frac * 2 ^ E
  // E = e - bias
  // bias = 127
  // M = 1.frac * 2 ^ 23
  // val_int = M / 2 ^ 23 * 2 ^ E = M * 2 ^ (e - 150)
  // int的数量级是2^30 E不可以超过这个数量级
  // 既然M是1.几 于是M < 2 必然 在 e = 157的时候不会溢出, e = 158的时候必然溢出
  // 乐
  // e <= 157
  if (e == 0 || isLessOrEqual(e, 126)) {
    // denormalized (e==0), or normalized with |value| < 1 (E <= -1)
    return 0;
  }
  if (!isLessOrEqual(e, 157)) {
    // E = e - 127 >= 31: magnitude too large for int, regardless of sign
    // (the exact -2^31 case coincides with this sentinel value anyway)
    return 0x80000000u;
  }
  if (isLessOrEqual(e, 150)) {
    // E <= 23: fraction bits shift off to the right
    res = M >> (150 - e);
  } else {
    // 24 <= E <= 30: still fits in int, but needs a LEFT shift
    res = M << (e - 150);
  }

  if (!!s) {
    return negate(res);
  } else {
    return res;
  }
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
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  return 2;
}
// int main() {
//   printf("\n%d\n", floatFloat2Int(1065353216));
// }
