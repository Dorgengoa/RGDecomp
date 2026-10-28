// rg_u128 in C++ (1957 game .cpp units; vec.h's Vec4::operator= puns
// through u128).  Called from test_u128's sibling exe main via extern "C".
#include <cstring>
#include "port/u128.h"

typedef rg_u128 u128;
typedef float f32;

static_assert(sizeof(u128) == 16 && alignof(u128) == 16, "u128 layout (C++)");

struct Vec4 {
    f32 x, y, z, w;
    Vec4 &operator=(const Vec4 &o) {   // game include/vec.h, after stage int128
        *(u128 *)this = *(const u128 *)&o;
        return *this;
    }
} __attribute__((aligned(16)));

struct Holder { virtual ~Holder() {} u128 q; };   // u128 member after a vptr

extern "C" int test_u128_cpp(void)
{
    Vec4 a = {1, 2, 3, 4}, b = {0, 0, 0, 0};
    b = a;
    int ok = std::memcmp(&a, &b, 16) == 0;
    u128 v = (u128)0xABCDull << 100;
    ok &= (unsigned long long)(v >> 100) == 0xABCDull;
    Holder h;
    ok &= alignof(Holder) == 16 && (reinterpret_cast<unsigned long>(&h.q) & 15) == 0;
    return ok;
}
