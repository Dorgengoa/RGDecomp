/* rgp:protos */
#define RGP_SELF_CharaMgrPoolSetGameData_3a9290 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S003A9290_sub {
    u8 pad0[0x60];
    s32 f60;                  /* +0x60 */
} S003A9290_sub;

typedef struct S003A9290_src {
    u8 pad0[0x8];
    struct S003A9290_sub *f8; /* +0x8 */
} S003A9290_src;

extern S003A9290_src *D_004837E8;
extern S003A9290_sub *D_004837EC;
extern s32 D_004837F0;

s32 CharaMgrPoolSetGameData_3a9290(void *self, S003A9290_src *p)
{
    S003A9290_sub *t;

    if (p == 0) {
        return 0;
    }
    D_004837E8 = p;
    t = p->f8;
    D_004837EC = t;
    if (t != 0) {
        D_004837F0 = t->f60;
    }
    return 1;
}
