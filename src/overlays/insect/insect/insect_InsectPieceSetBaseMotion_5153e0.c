#include "types.h"
/* insect 0x005153E0 -- 424 bytes, 106 instructions.
 * D_00481020 is MAIN-image small data (_gp 0x00485170 - 0x4150), inside the
 * gp window 0x47D170..0x48D170, so it stays a PLAIN non-const extern.
 * D_005252xx are OVERLAY rodata outside that window and are const. */

typedef struct Obj {
    u8  pad00[0x38];
    s8  f38;                        /* +0x38 */
    u8  pad39[0x4C - 0x39];
    s8  f4C;                        /* +0x4C */
    u8  pad4D[0x58 - 0x4D];
    s32 f58;                        /* +0x58 */
    u8  pad5C[0x6C - 0x5C];
    s16 f6C;                        /* +0x6C */
} Obj;

extern s32 D_00481020[2];
extern const char D_005252B8[];
extern const char D_005252D0[];
extern const char D_005252D8[];

extern void func_131B60(void *p, s32 c, s32 n);
extern void func_1343B8(char *buf, const char *fmt, ...);
extern void func_134690(char *buf, const char *s);
extern void func_171E00(s32 p);
extern void func_1867A0(s32 h, char *buf, s32 c);
extern void func_1ADD20(s32 h, f32 v);
extern s32 func_1C4A90(s32 p, s16 id);
extern s32 func_1F5BE0(void);
extern s32 insect_InsectPieceTestStatus_513280(Obj *o, s32 k);

void insect_InsectPieceSetBaseMotion_5153e0(Obj *o, s32 idx, s32 col, s32 n, s32 dst)
{
    char buf[16];
    s32 p;
    s32 q;

    func_131B60(buf, 0, 0x10);
    if (n != -1) {
        if (idx == 0) {
            func_1343B8(buf, D_005252D8, D_00481020[idx], n + 1);
        } else {
            func_1343B8(buf, D_005252B8, D_00481020[idx]);
        }
    } else {
        func_1343B8(buf, D_005252B8, D_00481020[idx]);
    }
    if (o->f38 == 12) {
        if (o->f4C <= 0 || insect_InsectPieceTestStatus_513280(o, 0x18) != 0) {
            func_134690(buf, D_005252D0);
        }
    }
    if (dst != 0) {
        func_1867A0(dst, buf, col);
        return;
    }
    p = func_1F5BE0();
    if (p == 0) {
        return;
    }
    q = func_1C4A90(p, o->f6C);
    if (q == 0) {
        return;
    }
    func_1867A0(q, buf, col);
    if (o->f58 != 0) {
        func_1867A0(o->f58, buf, 2);
        func_1ADD20(o->f58, 1.0f);
        func_171E00(o->f58 + 0x1F0);
    }
}
