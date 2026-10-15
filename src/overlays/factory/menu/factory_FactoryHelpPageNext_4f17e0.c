#include "types.h"

/* factory.bin overlay, 0x004F17E0 -- 608 B.  BYTE-IDENTICAL, session 23 (fz23c).
 *
 * The whole unit turned on ONE address spelling ([[insect-cse-two-spellings]]).
 * Retail computes the guard's element as `(f74 + 2) + f6C*4` and the later
 * `o->f74[o->f6C*2]` as a SEPARATE `addu $3,$6,$7` off the same two registers.
 * Writing the guard as `&o->f74[o->f6C*2] + 1` makes mwcc form `f74 + f6C*4`
 * ONCE, read the guard at displacement 2 and CSE the second site onto it -- one
 * word short, and it also forces an early `move s1,a0` because the shift then
 * clobbers $4.  The INTEGER-ADD cast is what mwcc will not fold into a
 * displacement, and the index must still be spelled as the ARRAY SUBSCRIPT so
 * the `sll` stays shared and the index (not the base) is evaluated first:
 *     qq = &((s16 *)((s32)o->f74 + 2))[o->f6C * 2];
 * MEASURED, same unit, same round: `qq = o->f74 + 1;` + `qq[o->f6C*2]` folds all
 * the way back (0x258, two short); `qq = (s16 *)((s32)o->f74 + 2);` + `qq[...]`
 * gets both `addu`s but evaluates the BASE first, so the shift takes $4 and the
 * `move s1,a0` returns (0x264, one long).
 */

typedef struct Scr {
    u8   pad00[0x6C];
    s32  f6C;
    s8   f70;
    s8   f71;
    u8   pad72[0x2];
    s16 *f74;
    s32  f78;
    s32  f7C;
    s32  f80;
    u8   pad84[0x4];
    void *f88;
} Scr;

extern void *D_00484A70;                        /* _gp - 0x700 */
extern u8    D_0050CB20[];

extern void  factory_FactoryHelpPageClose_4f16b0(Scr *o);
extern void  func_1343B8(u8 *dst, u8 *fmt, void *s);
extern u8   *func_1347C0(void *s, s32 c);
extern void  func_158C40(s32 h, u8 *p, s32 k);
extern s32   func_15DE40(void);
extern void  func_1CD670(s32 h);
extern s32   func_1CD870(s32 h, u8 *p, s32 k);
extern s32   func_1F59D0(void);
extern void *func_28AA30(void *bank, s32 id);
extern void  func_290010(void *w, s32 id, s32 a, s32 b);
extern void  func_290690(void *w, s32 id, f32 a, f32 b, f32 c);

void factory_FactoryHelpPageNext_4f17e0(Scr *o)
{
    u8   buf[0x20];
    u8  *p;
    u8  *q;
    u8  *r;
    s32  h;
    s32  id;
    s32  k;
    s32  m;
    s16 *qq;
    u32  n;

    qq = &((s16 *)((s32)o->f74 + 2))[o->f6C * 2];
    if (*qq > 1 && o->f78 < *qq - 1) {
        if (o->f7C == -1) {
            if (o->f78 > 0) {
                m = o->f78 - 1;
                id = o->f74[o->f6C * 2] + 0x2710;
                k = m + id;
                h = func_15DE40();
                func_158C40(h, func_1347C0(func_28AA30(D_00484A70, k - 1), 0xA) + 1, 0x32E);
                if (((o->f78 - 1) % 2) == 0) {
                    func_290010(o->f88, 0x84, 0, -1);
                } else {
                    func_290010(o->f88, 0x85, 0, -1);
                }
            }
            o->f78 = o->f78 + 1;
            k = o->f78 + (o->f74[o->f6C * 2] + 0x2710);
            h = func_1F59D0();
            o->f7C = -1;
            o->f80 = 0;
            q = func_28AA30(D_00484A70, k);
            p = func_1347C0(q, 0xA);
            *p = 0;
            r = buf;
            n = 0x20;
            if (r != 0) {
                do {
                    *r = 0;
                    n--;
                    r++;
                } while (n != 0);
            }
            func_1343B8(buf, D_0050CB20, q);
            *p = 0xA;
            o->f7C = func_1CD870(h, buf, 0);
            if (o->f7C != -1) {
                o->f71 = 0;
                func_1CD670(h);
                if ((o->f78 % 2) == 0) {
                    func_290690(o->f88, 0x85, 0.0f, -0.125f, -1.0f);
                } else {
                    func_290690(o->f88, 0x84, 0.0f, -0.125f, -1.0f);
                }
                o->f70 = 3;
            }
        }
    } else {
        factory_FactoryHelpPageClose_4f16b0(o);
    }
}
