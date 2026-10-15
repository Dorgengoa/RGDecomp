#include "types.h"
/* insect 0x00512400 -- 484 bytes, 121 instructions.
 *
 * Two five-iteration scans over the same pair of lists (o->f438 / o->f43C),
 * the first looking for the entry whose f6C is `id`, the second for a
 * DIFFERENT entry sharing its f3A.  The 0x5C-byte stride at the tail is a
 * `Slot slots[]` at +0x64: 0xBC = 0x64 + 0x58. */

typedef struct Slot {
    u8  pad00[0x58];
    s32 f58;                        /* +0x58 */
} Slot;                             /* 0x5C */

typedef struct Ent {
    u8  pad00[0x3A];
    s16 f3A;                        /* +0x3A */
    u8  pad3C[0x58 - 0x3C];
    s32 f58;                        /* +0x58 */
    u8  pad5C[0x6C - 0x5C];
    s16 f6C;                        /* +0x6C */
} Ent;

typedef struct Obj {
    s32  f0;                        /* +0x00 */
    s32  f4;                        /* +0x04 */
    u8   pad08[0x64 - 0x08];
    Slot slots[1];                  /* +0x64 */
    u8   padC0[0x400 - 0xC0];
    s16  f400[1];                   /* +0x400 */
    u8   pad402[0x438 - 0x402];
    void *f438;                     /* +0x438 */
    void *f43C;                     /* +0x43C */
} Obj;

extern void  func_14DCB0(s32 *a, s32 b);
extern void  func_14DFF0(Slot *s);
extern void  func_151460(s32 a);
extern void  func_158AC0(s32 a, s32 b);
extern s32   func_15DE40(void);
extern void  func_1C4C70(s32 a, s32 b);
extern Ent  *insect_InsectTeamGetPiece_5138d0(void *l, s32 i);

s32 insect_InsectModelMemReleasePiece_512400(Obj *o, s32 id)
{
    Ent *found;
    s32 i;
    s32 k;
    s32 t;
    s32 m;
    Ent *e;
    void *l;

    found = 0;
    k = id - 0x80;
    for (i = 0; i < 5; i++) {
        l = o->f438;
        if (l != 0) {
            e = insect_InsectTeamGetPiece_5138d0(l, i);
            if (e != 0) {
                if (id == e->f6C) {
                    found = e;
                    break;
                }
            }
        }
        l = o->f43C;
        if (l != 0) {
            e = insect_InsectTeamGetPiece_5138d0(l, i);
            if (e != 0) {
                if (id == e->f6C) {
                    found = e;
                    break;
                }
            }
        }
    }
    if (found == 0) {
        return 0;
    }
    for (i = 0; i < 5; i++) {
        l = o->f438;
        if (l != 0) {
            e = insect_InsectTeamGetPiece_5138d0(l, i);
            if (e != 0) {
                if (id != e->f6C) {
                    if (e->f3A == found->f3A) {
                        break;
                    }
                }
            }
        }
        l = o->f43C;
        if (l != 0) {
            e = insect_InsectTeamGetPiece_5138d0(l, i);
            if (e != 0) {
                if (id != e->f6C) {
                    if (e->f3A == found->f3A) {
                        break;
                    }
                }
            }
        }
    }
    func_1C4C70(o->f0, id);
    t = func_15DE40();
    func_158AC0(t, k + 0x243);
    if (found->f58 != 0) {
        func_151460(found->f58);
        found->f58 = 0;
        func_1C4C70(o->f0, id + 0x40);
        func_158AC0(t, k + 0x263);
    }
    found->f6C = -1;
    o->f400[k] = -1;
    m = o->slots[k].f58;
    func_14DFF0(&o->slots[k]);
    func_14DCB0(&o->f4, m);
    return 1;
}
