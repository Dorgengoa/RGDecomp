/* rgp:protos */
#define RGP_SELF_EffSpriteListSetTexRange_2dc5e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern void strcpy(void *, s32);

struct Obj0;

struct Obj0 {
    u8 pad000[0x244];
    s32 m244;
    s16 m248;
    u8 pad24A[0x22];
    s32 m26C;
};

s32 EffSpriteListSetTexRange_2dc5e0(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    s32 end;
    s32 r0;
    s32 r1;
    s32 i;

    if (p0->m244 != 0) {
        end = p2 + p3;
        if (end <= p0->m248) goto ok;
    }
    return 1;
ok:
    r0 = GetDrawCtxNameTable_15de40();
    r1 = ((s32)NameTableFindByName_159fb0(r0, p1, p0->m26C));
    strcpy((u8 *)p0 + 0x24A, p1);
    i = p2;
    while (i < end) {
        strcpy((u8 *)&p0->pad24A[0], p1);
        *(s32 *)(p0->m244 + i * 192 + 4) = r1;
        i = i + 1;
    }
    return 0;
}
