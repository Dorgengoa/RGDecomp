#include "types.h"
/* insect 0x0051C2F0 -- 584 bytes, 148 instructions, 6 calls, 21 conditional
 * branches.  The text-wrap / line-splitter: walk the source string one CR/LF
 * delimited line at a time, copy each line into a 0x50-byte stack buffer and
 * hand it to the first FREE row of o->f4 (stride 0x5A, f54 is the in-use flag).
 *
 * FIVE parameters -- the fifth arrives in $8 under the PS2 EABI.
 *
 * `first` ($23) and `more` ($22) are set with `daddiu`, which is
 * [[mwcc-daddiu-unsigned-narrow]]: a register-resident u8/u16.
 *
 * The two stack slots at 0xA0 (`sq`/`lq`) and 0xB0 (`sw`/`lw`) are mwcc
 * SPILLS of the two loop-invariant values -w and (fl != 0), not source
 * locals -- there is no `&` on either.
 *
 * The i == 0 / i == 1 / else chain is an if/else chain, NOT a switch: the
 * annulled `sb $3,0x26($21)` in the `bnel $16,$3` delay slot is the ELSE arm
 * ([[THE ANNULLED DELAY SLOT NAMES THE else ARM]]).
 */

typedef struct Row {
    u8   pad00[0x50];
    s8   f50;                       /* +0x50 */
    s8   f51;                       /* +0x51 */
    u8   f52;                       /* +0x52 */
    u8   pad53;
    s8   f54;                       /* +0x54 */
    u8   pad55;
    s16  f56;                       /* +0x56 */
    s16  f58;                       /* +0x58 */
} Row;                              /* 0x5A */

typedef struct Obj {
    u8   pad00[4];
    Row *f4;                        /* +0x04 */
    u8   pad08[0x18 - 0x08];
    s16  f18;                       /* +0x18 */
    u8   pad1A[0x20 - 0x1A];
    s16  f20;                       /* +0x20 */
    u8   pad22[0x26 - 0x22];
    s8   f26;                       /* +0x26 */
} Obj;

extern s8  *func_1347C0(s8 *s, s32 c);
extern s32  func_134BB0(const s8 *s);
extern void func_134F78(void *d, const s8 *s, s32 n);
extern void insect_InsectBattleLogLineSetText_51c6f0(Row *r, s8 *t);
extern void insect_InsectBattleLogLineFadeTo_51c7d0(Row *r, s32 a, s32 b);

void insect_InsectBattleLogPush_51c2f0(Obj *o, s8 *s, s32 w, s16 h, s32 fl)
{
    s8   buf[0x50];
    Row *rows;
    s8  *p;
    Row *row;
    Row *r2;
    s8  *q;
    s32  n;
    s32  i;
    s32  j;
    s32  t;
    s32  nw;
    u8   fb;
    u8   first;
    u8   more;

    if (o->f4 != 0) {
        p = s;
        nw = -w;
        first = 1;
        fb = (fl != 0);
        while (*p != 0) {
            q = func_1347C0(p, 0xD);
            if (q == 0) {
                q = func_1347C0(p, 0xA);
            }
            if (q == 0) {
                q = p + func_134BB0(p);
            }
            n = q - p;
            func_134F78(buf, p, n);
            buf[n] = 0;
            p = q;
            if (*q == 0xD) {
                p = q + 1;
            }
            if (*p == 0xA) {
                p = p + 1;
            }
            more = 0;
            if (*p != 0) {
                more = 1;
            }
            rows = o->f4;
            row = rows;
            i = 0;
            while (i < 0x50) {
                if (row->f54 == 0) {
                    if (i == 0) {
                        o->f26 = 0;
                    } else if (i == 1) {
                        if (rows->f52 == 0 || o->f20 < 0xA) {
                            o->f26 = 0;
                        } else {
                            o->f26 = 1;
                        }
                    } else {
                        o->f26 = 1;
                    }
                    row->f54 = 1;
                    insect_InsectBattleLogLineSetText_51c6f0(row, buf);
                    row->f51 = 0;
                    insect_InsectBattleLogLineFadeTo_51c7d0(row, 0x80, 0x10);
                    if (first) {
                        row->f58 = h;
                        t = w;
                        if (w < 0) {
                            if (i == 0) {
                                t = 0;
                            } else {
                                t = nw;
                            }
                        }
                        row->f56 = t;
                    } else {
                        row->f58 = -1;
                        row->f56 = 0;
                    }
                    if (more) {
                        row->f50 = 0;
                    } else {
                        row->f50 = fb;
                        if (fl != 0 && i > 0 && i < o->f18 - 2) {
                            r2 = o->f4;
                            for (j = 0; j < i; j++) {
                                r2->f50 = 0;
                                r2++;
                            }
                        }
                    }
                    break;
                }
                i++;
                row++;
            }
            first = 0;
        }
    }
}
