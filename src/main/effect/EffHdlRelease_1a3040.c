#include "types.h"

/* lane N4 family: EffHdlRelease_1a3040 / EffHdlRelease_1a4040 (200 B each) - the two
   listings are byte-identical apart from the symbol name.
   The second parameter is HOMED (`sw $5,0x38($29)`) and then read back as
   two halfwords, so its address is taken in the source. */

typedef struct Obj Obj;
struct Obj {
    u8 pad00[4];
    u32 f4;
    u8 pad08[0xC];
    s32 *f14;
    u8 f18[4];
    s32 f1C;
    s32 *f20;
};

extern char D_0045A650[];
extern char D_0045A660[];
extern char D_0045A680[];

extern void __assert(char *, s32, char *);
extern void VectorU32InsertN_1a4e80(void *, s32 *, s32, u32 *);

void EffHdlRelease_1a3040(Obj *o, u32 key)
{
    u32 i;
    u16 v;
    s32 x;

    i = *(u16 *)&key;
    v = *(u16 *)((u8 *)&key + 2);
    if (i >= o->f4) {
        __assert(D_0045A650, 0x9A, D_0045A660);
    }
    x = o->f14[i];
    if (x != v) {
        __assert(D_0045A650, 0x9B, D_0045A680);
    }
    o->f14[i] = 0;
    VectorU32InsertN_1a4e80(&o->f18, &o->f20[o->f1C], 1, &i);
}
