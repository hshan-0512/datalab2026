# datalab 报告

姓名：韩卉珊

学号：2024202630

| 总分 | bitAnd | bitXor | samesign | logtwo | byteSwap | reverse | logicalShift | leftBitCount | float_i2f | floatScale2 | float64_f2i | floatPower2 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 37 | 1 | 1 | 2 | 4 | 4 | 3 | 3 | 4 | 4 | 4 | 3 | 4 |


test 截图：


<!-- TODO: 用一个通过的截图，本地图片，放到 imgs 文件夹下，不要用这个 github，pandoc 解析可能有问题 -->

## 解题报告
### bitAnd

先把两个数取反，再按位或，最后取反。只有原来的两位都是1，结果才是1。

```c
return ~(~x|~y);
```

### bitXor

异或在两位不同时为1。我分别排除两位都是1和两位都是0的情况，再把两个结果按位与。

```c
return ~(x&y)&~(~x&~y);
```

### samesign

零既不是正数也不是负数，所以先单独处理。两个数都非零时，用异或比较最高的符号位，相同就返回1。

```c
if(!x){
    return !y;
}
if(!y){
    return !x;
}
return !((x^y)>>31);
```

### logtwo

就是寻找最高的1所在的位编号，依次检查16、8、4、2、1位，每确定一段位置，就把v右移，继续检查剩下的部分。

```c
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
```

每段结果只占不同的二进制位，所以最后可以用|合起来。

### byteSwap

一个字节有8位，所以先将字节编号乘以8，再右移并用0xFF取出两个字节。用异或找出它们不同的位，再在原数的两个位置翻转这些位，完成交换。

```c
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
```

### reverse

每次取出原数的最低位，接到结果末尾。结果在接下一位之前先左移，重复32次后，位的顺序就反过来了。

```c
unsigned m=0;
int c=32;
while(c){
    m=m<<1;
    m=m|(v&1);
    v=v>>1;
    c--;
}
return m;
```

### logicalShift

负数算术右移会在左边补1。我先右移，再用高n位为0、其余位为1的掩码清除这些位。

```c
int flag=!n;
int m=n+flag;
int p=((0x7fffffff>>m)<<1)|1;
int q=~flag+1;
p=p|q;
int res=(x>>n)&p;
return res;
```

n为0时，先让m取1，避免构造掩码时出现不安全的左移，再用q将掩码变成全1。真正右移x时仍使用n。

### leftBitCount

先把x取反，原来的前导1就变成前导0。再用与logtwo类似的方法找到最高的1，位置记为p，结果就是31-p。

```c
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
```

!!把非零结果变成1。原数全是1时，取反得到0，普通计算会少算一位，所以用flag补上，得到32。

### float_i2f

先保存符号，再用unsigned保存整数的大小。不断左移，直到最高位是1，同时调整指数。然后取出23位小数，最后根据被丢掉的8位决定是否舍入。

```c
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
```

158是31+127。丢弃部分超过一半时进位，恰好一半时，保留部分末位为1才进位。

### floatScale2

先拆出符号、指数和小数。指数为255时原样返回；指数为0时将小数左移一位；其他情况将指数加一。

```c
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
```

指数加到255后要清空小数，让结果表示无穷，避免变成NaN。

### float64_f2i

uf2是高32位，uf1是低32位。先取出符号和指数。大小小于1时返回0，e大于等于31时返回规定的位模式。其他情况拼出有效位，再右移丢掉小数，最后处理符号。

```c
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
```

隐含的1被放在第30位，所以右移30-e位。先截断大小再恢复符号，可以得到向零取整的结果。最小int的正确编码也恰好是0x80000000。

### floatPower2

按指数范围分成四种情况：太小返回0，太大返回正无穷，中间分别用非规格化数和正规数表示。

```c
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
```

最小非规格化数的指数是-126-23=-149。正规数的小数部分为0，只需要把x+127放到指数的位置。
### 亮点

<!-- 告诉助教哪些函数是你实现得最优秀的，比如你可以排序。不需要展开，展开请放到后文中。 -->

1. bitXor
2. logicalShift


## 反馈/收获/感悟/总结

<!-- 这一节，你可以简单描述你在这个 lab 上花费的时间/你认为的难度/你认为不合理的地方/你认为有趣的地方 -->

<!-- 或者是收获/感悟/总结 -->

<!-- 200 字以内，可以不写 -->

## 参考的重要资料
ppt 2编码上 3编码下
<!-- 有哪些文章/论文/PPT/课本对你的实现有重要启发或者帮助，或者是你直接引用了某个方法 -->

<!-- 请附上文章标题和可访问的网页路径 -->
