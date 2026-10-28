/* rgp:protos */
#define RGP_SELF_insect_InsectPieceSetBaseMotion_5153e0 1
#include "port/game_protos.h"
#line 1
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
extern char insect_D_005252B8[];
extern char insect_D_005252D0[];
extern char insect_D_005252D8[];

extern void memset(void *p, s32 c, s32 n);
extern void Sprintf_1343b8(char *buf, const char *fmt, ...);
extern void strcat(char *buf, const char *s);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectPieceSetBaseMotion_5153e0(Obj *o, s32 idx, s32 col, s32 n, s32 dst)
{
    char buf[16] __attribute__((aligned(16)));
    s32 p;
    s32 q;

    memset(buf, 0, 0x10);
    if (n != -1) {
        if (idx == 0) {
            Sprintf_1343b8(buf, insect_D_005252D8, D_00481020[idx], n + 1);
        } else {
            Sprintf_1343b8(buf, insect_D_005252B8, D_00481020[idx]);
        }
    } else {
        Sprintf_1343b8(buf, insect_D_005252B8, D_00481020[idx]);
    }
    if (o->f38 == 12) {
        if (o->f4C <= 0 || insect_InsectPieceTestStatus_513280(o, 0x18) != 0) {
            strcat(buf, insect_D_005252D0);
        }
    }
    if (dst != 0) {
        ModelObjPlayMotionByName_1867a0(dst, buf, col);
        return;
    }
    p = GetCurrentScene_1f5be0();
    if (p == 0) {
        return;
    }
    q = ((s32)ObjRecGetLiveObject_1c4a90(p, o->f6C));
    if (q == 0) {
        return;
    }
    ModelObjPlayMotionByName_1867a0(q, buf, col);
    if (o->f58 != 0) {
        ModelObjPlayMotionByName_1867a0(o->f58, buf, 2);
        ModelObjUpdateMotions_1add20(o->f58, 1.0f);
        MotionListResetAll_171e00(o->f58 + 0x1F0);
    }
}
