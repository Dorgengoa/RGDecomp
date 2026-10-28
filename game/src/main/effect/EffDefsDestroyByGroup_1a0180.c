/* rgp:protos */
#define RGP_SELF_EffDefsDestroyByGroup_1a0180 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern void **HandleTableGet_1a1d50(void *arg0, s32 arg1);
/*rgp*/

typedef struct {
    s32 pad;
    s32 key;
    u8 *end;
    u8 *cur;
} It001a0180;

s32 EffDefsDestroyByGroup_1a0180(u8 *arg0, s32 arg1) {
    It001a0180 s __attribute__((aligned(16)));
    s32 i;
    void **t;
    u8 *v;

    i = 0;
    {
        u8 *e = arg0 + 0xD8;
        u8 *c = *(u8 **)(arg0 + 0xE0);
        s.end = e;
        s.cur = c;
    }
loop:
    if (s.cur != s.end) {
        s.key = *(s32 *)(s.cur + 0x18);
        t = HandleTableGet_1a1d50(arg0 + 0xB0, s.key);
        if (t != NULL) {
            v = *(u8 **)t;
        } else {
            v = NULL;
        }
        if ((v != NULL) && (*(s32 *)(v + 0x4C) == arg1)) {
            EffDefDestroy_1a0a90(arg0, s.key);
            {
                u8 *e = arg0 + 0xD8;
                u8 *c = *(u8 **)(arg0 + 0xE0);
                s.end = e;
                s.cur = c;
            }
            i++;
            goto loop;
        }
        RbTreeIncrement_1a2210(&s.cur);
        goto loop;
    }
    return i;
}
