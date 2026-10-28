/* rgp:protos */
#define RGP_SELF_EffSpriteListAlloc_2dc920 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Element stride is 0xC0 (sll 1 / addu / sll 6).  The 0x1A0 store sits at the
   join, so it is a temporary initialised to 0 and overwritten in the guard,
   not two stores. */

typedef struct Heap {
    u8 pad0[0x28];
    u32 f28;                /* 0x28 */
} Heap;

typedef struct Obj {
    u8 pad0[0x1A0];
    void *f1A0;             /* 0x1A0 */
    u8 pad1A4[0xA0];
    u8 *f244;               /* 0x244 */
    s16 h248;               /* 0x248 */
    u8 pad24A[0x26];
    s32 f270;               /* 0x270 */
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EffSpriteListAlloc_2dc920(Obj *o, s32 b, s16 count, Heap *h)
{
    s32 lim;
    u32 size;
    u32 n;
    u8 busy;
    void *p;
    u8 flag;
    s32 i;

    if (!(count > 0)) {
        return -1;
    }
    lim = o->f270 + o->h248 * 0xC0;
    if (MemStackGetFree_1c6d50(((s32)GetEffectMgr_2d9040())) < lim) {
        return 1;
    }
    o->h248 = count;
    busy = h->f28 > 0;
    flag = !busy;
    if (flag) {
        size = o->h248 * 0xC0;
        if ((size & 0xF) != 0) {
            n = (size >> 4) + 1;
        } else {
            n = size >> 4;
        }
        p = MemStackHeapAlloc_14db10(h, 3, n, 0x40);
    } else {
        p = 0;
    }
    o->f1A0 = p;
    o->f244 = ((u8 *)MemStackNew_14e1b0(o->h248 * 0xC0, h));
    if (o->f244 == 0) {
        if (flag) {
            MemStackReturnToOwnerMaybe_14dad0(h);
        }
        return -10;
    }
    for (i = 0; i < o->h248; i++) {
        *(s16 *)(o->f244 + i * 0xC0) = i;
        *(s16 *)(o->f244 + i * 0xC0 + 2) = b;
        *(s32 *)(o->f244 + i * 0xC0 + 4) = 0;
    }
    if (flag) {
        MemStackReturnToOwnerMaybe_14dad0(h);
    }
    return 0;
}
