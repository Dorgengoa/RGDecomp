#include "types.h"
/* insect 0x0050F730 -- 560 bytes, 140 instructions.
 *
 * Unpacks an ARGB word into a Vec4 and hands it, plus one row copied out of
 * the handle, to func_2D2DA0.  The `bltz`/halve/`or`/`cvt.s.w`/`add.s` fan is
 * mwcc's UNSIGNED int-to-float sequence, so every colour term is `u32`.
 * The two byte-clears are written out, not memset (insect_InsectBattleDrawDimOverlay_4f52a0), and
 * the `lq`/`sq` pair is a 16-byte ALIGNED struct assignment (include/vec.h).
 *
 * The five `slti $3` land in a GPR with a `bnel` consumer, which
 * at-compare-class reads as a strict `<` taken-condition, i.e. the source
 * guard is `>= K` -- not `> K-1`.
 */

typedef struct Vec4 { f32 x; f32 y; f32 z; f32 w; } __attribute__((aligned(16))) Vec4;

typedef struct Obj {
    u8  pad00[0x6C];
    s16 f6C;                        /* +0x6C */
} Obj;

typedef struct Hnd {
    u8   pad000[0x180];
    Vec4 f180;                      /* +0x180 */
} Hnd;

extern f32  D_0047D354;             /* _gp - 0x7E1C */
extern f32  D_0047DC88;             /* _gp - 0x74E8 */

extern s32  insect_InsectGetDamagePopupList_5108c0(void);
extern Hnd *func_1C4A90(s32 m, s16 i);
extern s32  func_1F5BE0(void);
extern void func_2D2DA0(s32 k, s32 t, Vec4 *b, Vec4 *a, s32 mode, s32 z, f32 s);

void insect_InsectBattleDamagePopupSpawn_50f730(Obj *o, s32 t, u32 col)
{
    Vec4 a;
    Vec4 b;
    u8  *p;
    u32  n;
    s32  m;
    s32  k;
    s32  mode;
    f32  s;
    Hnd *h;

    if (o == 0) {
        return;
    }
    m = func_1F5BE0();
    k = insect_InsectGetDamagePopupList_5108c0();
    h = func_1C4A90(m, o->f6C);
    s = 1.0f;
    if (t >= 100) {
        s = D_0047D354;
    }
    if (t >= 250) {
        s = 1.5f;
    }
    if (t >= 300) {
        s = D_0047DC88;
    }
    if (t >= 400) {
        s = 2.0f;
    }
    if (k == 0) {
        return;
    }
    if (h == 0) {
        return;
    }
    p = (u8 *)&a;
    n = 0x10;
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
    a.x = (f32)((col & 0xFF000000) >> 24);
    a.y = (f32)((col & 0x00FF0000) >> 16);
    a.z = (f32)((col & 0x0000FF00) >> 8);
    a.w = (f32)(col & 0xFF);
    p = (u8 *)&b;
    n = 0x10;
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
    b = h->f180;
    mode = 2;
    if (t <= 0) {
        mode = 6;
        if (t == 0) {
            mode = 5;
        }
        t = 0;
    }
    func_2D2DA0(k, t, &b, &a, mode, 0, s);
}
