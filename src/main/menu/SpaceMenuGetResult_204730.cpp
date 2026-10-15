#include "types.h"
struct Tag { s16 tag; s32 value; };
extern "C" {
extern Tag func_511660(void);
}
extern "C" Tag SpaceMenuGetResult_204730(void)
{
    Tag a = func_511660();
    Tag t = a;
    Tag r;
    switch (t.tag) {
    case 0:
        r.tag = 0;
        r.value = -1;
        break;
    case 2:
        r.tag = 1;
        r.value = -1;
        break;
    case 1:
        r.tag = 2;
        r.value = a.value;
        break;
    }
    return r;
}
