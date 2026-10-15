#include "types.h"
/* insect 0x0050DB60 -- 300 bytes, 75 instructions, 7 calls.
 * A four-case switch (every compare is `beql` INTO the arm, so the source
 * case order is the compare chain reversed: 3, 4, 5, 6) with a fall-back
 * path that zeroes a 0x20-word stack buffer.
 */

typedef struct R3 {
    u8 pad00[0xD];
    s8 fD[1];                       /* +0x0D */
} R3;

typedef struct R4 {
    u8  pad00[0x10];
    s32 f10;                        /* +0x10 */
} R4;

typedef struct R6 {
    u8  pad00[0xF0];
    s32 fF0;                        /* +0xF0 */
} R6;

typedef struct Handle {
    u8  pad00[0x18];
    s32 f18;                        /* +0x18 */
    u8  pad1C[0x24 - 0x1C];
    s32 f24;                        /* +0x24 */
} Handle;

typedef struct Obj {
    u8  pad00[0x5DA8];
    s32 f5DA8;                      /* +0x5DA8 */
} Obj;

extern Handle *func_1FEDE0(void);
extern s32     insect_InsectBattleTestFlag_50da40(Obj *o, s32 k);
extern R3     *func_430B70(s32 h);
extern R4     *func_430B50(s32 h);
extern void    func_430B30(s32 h);
extern R6     *func_430AF0(s32 h);
extern s32     func_3C4D90(s32 h, s32 *buf, s32 n);

s32 insect_InsectBattleGetPoolCount_50db60(Obj *o, s32 a)
{
    Handle *h;
    R4 *p;
    s8 *q;
    s32 r;
    s32 i;
    s32 buf[0x20];

    h = func_1FEDE0();
    if (h != 0) {
        if (insect_InsectBattleTestFlag_50da40(o, 2) != 0) {
            r = 0;
            switch (o->f5DA8) {
            case 3:
                q = (s8 *)func_430B70(h->f24);
                r = q[a + 0xD];
                break;
            case 4:
                r = func_430B50(h->f24)->f10;
                if (a != 0) {
                    r = 5;
                }
                break;
            case 5:
                func_430B30(h->f24);
                r = 5;
                break;
            case 6:
                r = func_430AF0(h->f24)->fF0;
                break;
            }
            return r;
        }
        for (i = 0; i < 0x20; i++) {
            buf[i] = 0;
        }
        return func_3C4D90(h->f18, buf, 0x20);
    } else {
        return -1;
    }
}
