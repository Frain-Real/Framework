// Математические функции эмуляции фильтров, мат. расчётов и другого
#include "standard.h"

/********          MATH             *******/
// Алгоритм Эвклида по поиску наибольшего общего делителя
u32 Evclide_MCD(u32 a, u32 b) {
    u32 s = 0;
    u32 r = b;
    u32 old_s = 1;
    u32 old_r = a; 
    while (r != 0) {
        u32 q = old_r % r;
        u32 i;
        i = r;
        r = old_r - q * r;
        old_r = i;

        i = s;
        s = old_s - q * s;
        old_s = i;
    }
    return old_r;
}

//Быстрое возведение числа num в степень deg
double powerFast(long num, long degris) {
    double result = 1;
    register long deg = degris;
    if(deg < 0) 
        deg = -deg;
    while(deg) {
        if (deg % 2 == 0) {
            deg /= 2;
            num *= num;
        }
        else {
            deg--;
            result *= num;
        }
    }
    return degris < 0 ? 1 / result : result;
}

/********          RND             *******/
#ifdef __RND_PROGRAMABLE__
u32 random() {
  static u32 seed = 5; // зерно не должно быть 0
  seed = (seed * 73129 + 95121) % 100000;
  return seed;
}
#endif /* __RND_PROGRAMABLE__ */