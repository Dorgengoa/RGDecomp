/* rgp:protos */
#define RGP_SELF_ObjMgrSetGameData_3bc2a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S003BC2A0_src {
    u8 pad0[0x8];
    struct S003BC2A0_sub *f8;  /* +0x8 */
} S003BC2A0_src;

typedef struct S003BC2A0_sub {
    u8 pad0[0x64];
    s32 f64;                  /* +0x64 */
} S003BC2A0_sub;

typedef struct S003BC2A0 {
    u8 pad0[0x4];
    S003BC2A0_src *f4;        /* +0x4 */
    S003BC2A0_sub *f8;        /* +0x8 */
    s32 fC;                   /* +0xC */
} S003BC2A0;

s32 ObjMgrSetGameData_3bc2a0(S003BC2A0 *self, S003BC2A0_src *p)
{
    S003BC2A0_sub *t;

    if (p == 0) {
        return 0;
    }
    self->f4 = p;
    t = p->f8;
    self->f8 = t;
    if (t != 0) {
        self->fC = t->f64;
    }
    return 1;
}
