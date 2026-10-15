#include "types.h"
/* insect 0x004EF8D0 -- 408 bytes, 102 instructions.
 *
 * Five consecutive u8[7][5] grids live at 0x13B, 0x15E, 0x181, 0x1A4 and
 * 0x1C7 (each 35 bytes, back to back), which is what makes every address in
 * this unit a plain `base + j*5 + i` with a hoisted constant term.
 *
 * The `dsll32/dsra32 ..,16` pairs are an (s16) cast of an s32 local, not an
 * s16 local -- normal-s16-cast-sign-extension.  The `sq`/`lq` at 0xA0($29) is
 * mwcc spilling the byte read of f1A4 across the insect_InsectBoardIsHole_4ee7e0 call,
 * which is why the reload re-masks with 0xFF before the `& 0xF`.
 */

typedef struct Obj {
    u8  pad0000[0x13B];
    u8  f13B[7][5];                 /* +0x13B */
    u8  f15E[7][5];                 /* +0x15E */
    u8  f181[7][5];                 /* +0x181 */
    u8  f1A4[7][5];                 /* +0x1A4 */
    u8  f1C7[7][5];                 /* +0x1C7 */
} Obj;

extern void insect_InsectBoardWebFlagsRefresh_4ee3b0(void);
extern void insect_InsectBoardHoleClear_4ee780(Obj *o, s32 i, s32 j);
extern s32  insect_InsectBoardIsHole_4ee7e0(Obj *o, s32 i, s32 j);

void insect_InsectBoardFxUpdate_4ef8d0(Obj *o)
{
    u8 *pa;
    u8 *pb;
    u8 *pc;
    s32 j;
    s32 i;
    s32 k;
    u8 v;
    s32 t;
    u8 *p;
    u8 *q;

    pc = o->f1A4[0];
    pa = o->f15E[0];
    pb = o->f181[0];
    insect_InsectBoardWebFlagsRefresh_4ee3b0();
    for (j = 0; j < 7; j++) {
        for (i = 0; i < 5; i++) {
            k = j * 5 + i;
            v = pc[k];
            p = &pb[k];
            if (((o->f1C7[j][i] & 0xF0) >> 4) != 0) {
                t = (s16)(*p + 8);
                if (t >= 0x80) {
                    t = 0x80;
                }
            } else {
                t = (s16)(*p - 8);
                if (t <= 0) {
                    t = 0;
                    o->f13B[j][i] &= 0xEF;
                }
            }
            *p = (u8)t;
            q = &pa[k];
            if (insect_InsectBoardIsHole_4ee7e0(o, i, j) != 0) {
                if ((v & 0xF) == 0) {
                    insect_InsectBoardHoleClear_4ee780(o, i, j);
                }
                t = (s16)(*q + 8);
                if (t >= 0x80) {
                    t = 0x80;
                }
            } else {
                t = (s16)(*q - 8);
                if (t <= 0) {
                    t = 0;
                }
            }
            *q = (u8)t;
        }
    }
}
