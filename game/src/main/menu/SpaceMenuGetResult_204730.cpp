/* rgp:protos */
#line 1
#include "types.h"
struct Tag { s16 tag; s32 value; };
extern "C" {
void func_511660(void *);
}
extern "C" Tag SpaceMenuGetResult_204730(void)
{
    Tag a __attribute__((aligned(16))) = ({ Tag rgp_sret; func_511660((void *)&rgp_sret); rgp_sret; });
    Tag t __attribute__((aligned(16))) = a;
    Tag r __attribute__((aligned(16)));
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
