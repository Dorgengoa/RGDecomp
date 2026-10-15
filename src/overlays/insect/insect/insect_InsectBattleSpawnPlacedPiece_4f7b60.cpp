#include "types.h"
/* insect 0x004F7B60 -- C++ virtual dispatch, vptr at +0x1B0, slot 0x44 =
 * virtual #15.  [[jalr-is-cpp-virtual]]
 *
 * A five-arm `insect_InsectBattleGetStep_50d6a0(o, 1)` dispatch.  Chain 0x12, 0x3C, 0x3D, 6,
 * 1 with `beql` INTO each arm, so the source order is the REVERSE: 1, 6, 0x3D,
 * 0x3C, 0x12 -- and the arm addresses ascend in exactly that order.  Case 0x3C
 * FALLS THROUGH into case 0x12, which is why the 0x12 test alone is a plain
 * `beq` with a `nop`: its block is a fall-through target as well.
 *
 * `dsll32/dsra32 $21,..,16` off a value that came from an `lh` is an s32 local
 * carrying an EXPLICIT `(s16)` cast [[normal-s16-cast-sign-extension]].
 */

class VE {
public:
    u8 pad000[0x1B0];
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual void s04(); virtual void s05();
    virtual void s06(); virtual void s07(); virtual void s08();
    virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(f32 a);          /* slot 0x44 */
};

struct Ent {
    u8  pad000[0x39];
    s8  f39;                        /* +0x39 */
    u8  pad03A[0x58 - 0x3A];
    s32 f58;                        /* +0x58 */
    u8  pad05C[0x6C - 0x5C];
    s16 f6C;                        /* +0x6C */
    u8  pad06E[0xDC - 0x6E];
    s16 fDC;                        /* +0xDC */
};

struct O {
    u8    pad000[0x870];
    void *f870;                     /* +0x0870 */
    u8    pad874[0x5000 - 0x874];
    u8    f5000[0x20];              /* +0x5000 */
    u8    pad5020[0x5EF1 - 0x5020];
    u8    f5EF1;                    /* +0x5EF1 */
};

extern u8 D_00524C88[];

extern "C" void  func_1343B8(void *d, const u8 *t, s32 v);
extern "C" VE   *func_1C4A90(void *h, s32 k);
extern "C" void  func_1C3E80(void *h, s32 a, s32 id);
extern "C" void  func_1CF9E0(void *h, s32 id, s32 k);
extern "C" void  func_1CFB10(void *h, s32 id, f32 v);
extern "C" void  insect_InsectBoardCellToWorld_4eda70(u8 *g, f32 x, f32 y, f32 *ox, f32 *oy,
                                     f32 *oz, s32 k);
extern "C" s32   insect_InsectBattleGetStep_50d6a0(O *o, s32 k);
extern "C" void  insect_InsectBattleSetStep_50d7a0(O *o, s32 a, s32 b, s32 c);
extern "C" s32   insect_InsectBattleSpawnBombModel_50ee60(Ent *p);
extern "C" s32   insect_InsectBattleRequestBombModel_50f100(Ent *p);
extern "C" void  insect_InsectBattlePieceApplyColor_50fa30(VE *g, Ent *p);
extern "C" void  insect_InsectBattlePieceSetDesignVisible_50fa80(VE *g, Ent *p, s32 k);
extern "C" void  insect_InsectCursorSetGetCell_511a40(u8 *t, s32 k, s32 *a, s32 *b);
extern "C" void *insect_InsectFileSlotGetData_511fa0(u8 *p, s32 *out);
extern "C" s32   insect_InsectFileSlotIsLoaded_512010(u8 *p);
extern "C" void  insect_InsectFileSlotRelease_512020(u8 *p);
extern "C" void  insect_InsectFileSlotRequest_512140(u8 *p, void *t, s32 k);
extern "C" s32   insect_InsectModelMemCreatePiece_5125f0(u8 *w, void *h, s32 n);
extern "C" Ent  *insect_InsectTeamGetPiece_5138d0(u8 *b, s32 i);
extern "C" void  insect_InsectPieceSetBaseMotion_5153e0(Ent *p, s32 a, s32 b, s8 c, s32 d);
extern "C" void  insect_InsectPieceSetPos_5159b0(Ent *p, f32 x, f32 y, f32 z);

extern "C" void insect_InsectBattleSpawnPlacedPiece_4f7b60(O *o)
{
    s32   px;
    s32   py;
    s32   x;
    s32   y;
    s32   u;
    s32   v;
    s32   w;
    f32   fa;
    f32   fb;
    f32   fc;
    u8    buf[0x10];
    u8   *t4960;
    Ent  *r;
    u8   *t4B4C;
    s32   k;
    VE   *g;
    s32   id;
    void *h;

    insect_InsectCursorSetGetCell_511a40((u8 *)o + 0x4F90, 8, &u, &v);
    insect_InsectCursorSetGetCell_511a40((u8 *)((s32)o + 0x4F90), 9, &x, &y);
    t4960 = (u8 *)o + 0x4960;
    t4B4C = (u8 *)o + 0x4B4C;
    r = insect_InsectTeamGetPiece_5138d0((u8 *)o + o->f5EF1 * 0x994 + 0x35F8, v);
    if (r == 0) {
        return;
    }
    px = x;
    py = y;
    if (o->f5EF1 == 0) {
        py = py + 5;
    }

    switch (insect_InsectBattleGetStep_50d6a0(o, 1)) {
    case 1:
        func_1343B8(buf, D_00524C88, r->fDC);
        insect_InsectFileSlotRequest_512140(o->f5000, buf, 2);
        insect_InsectBattleSetStep_50d7a0(o, 6, 1, -1);
        break;
    case 6:
        if (insect_InsectFileSlotIsLoaded_512010(o->f5000) != 0) {
            w = 0;
            h = insect_InsectFileSlotGetData_511fa0(o->f5000, &w);
            r->f6C = insect_InsectModelMemCreatePiece_5125f0(t4B4C, h, w);
            insect_InsectFileSlotRelease_512020(o->f5000);
            k = 0x3C;
            if (insect_InsectBattleRequestBombModel_50f100(r) != 0) {
                k = 0x3D;
            }
            insect_InsectBattleSetStep_50d7a0(o, k, 1, -1);
        }
        break;
    case 0x3D:
        if (insect_InsectBattleSpawnBombModel_50ee60(r) != 0) {
            insect_InsectBattleSetStep_50d7a0(o, 0x3C, 1, -1);
        }
        break;
    case 0x3C:
        id = r->f6C;
        g = func_1C4A90(o->f870, id);
        if (g != 0) {
            insect_InsectBattlePieceSetDesignVisible_50fa80(g, r, 0);
            insect_InsectPieceSetBaseMotion_5153e0(r, 0, 4, r->f39, 0);
            g->s15(1.0f);
            func_1C3E80(o->f870, 1, id);
            func_1CFB10(o->f870, id, 0.0f);
            func_1CF9E0(o->f870, id, 0xF);
            if (r->f58 != 0) {
                id = (s16)(r->f6C + 0x40);
                func_1C3E80(o->f870, 1, id);
                func_1CFB10(o->f870, id, 0.0f);
                func_1CF9E0(o->f870, id, 0xF);
            }
            insect_InsectBattlePieceApplyColor_50fa30(g, r);
        }
        insect_InsectBattleSetStep_50d7a0(o, 0x12, 1, -1);
        /* fall through */
    case 0x12:
        insect_InsectBoardCellToWorld_4eda70(t4960, (f32)px, (f32)py, &fa, &fb, &fc, 1);
        insect_InsectPieceSetPos_5159b0(r, fa, fb, fc);
        insect_InsectBattleSetStep_50d7a0(o, 0xB, 1, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0x1B, 0, -1);
        break;
    }
}
