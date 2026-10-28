/* rgp:protos */
#line 1
#include "types.h"
/* insect 0x0050C100 -- 944 B, br 24.  C++: two `lw $25,0x1B0($18) /
 * lw $25,K($25) / jalr $25` calls are virtuals #4 (slot 0x18) and #15
 * (slot 0x44) on the vptr at 0x1B0.  [[jalr-is-cpp-virtual]]
 *
 * The three 0x790-byte sub-objects at +0x17B0 / +0x1F40 / +0x26D0 are the
 * same class insect_InsectBattleLoadTrainerCharas_4f83f0 allocates (0x1F40 - 0x17B0 = 0x790).
 *
 * The byte-clear of the 16-byte vector is written out, not memset, with the
 * null test on a frame address mwcc cannot fold and an UNSIGNED counter --
 * insect_InsectBattleDrawDimOverlay_4f52a0's recorded spelling; the two hazard `nop`s are mwcc's.
 *
 * `lwc1 $f2, -0x7F74($28)` is `extern f32 D_0047D1FC` (gp = 0x485170) and
 * `lui $2, 0x4334` is the ordinary literal 180.0f.  The angle must be a NAMED
 * local COMPUTED BEFORE the byte-clear loop: written at its store site the
 * whole mul/div sinks below the loop and the `beqz` delay slot swallows the
 * `addiu $v0,$zero,0x10`, which is one word SHORT.
 *
 * Every switch arm ends in `break` -- a `return` leaves mwcc's pre-retarget
 * copy of the arm head as dead code, one word per arm (see the ix18f report).
 */

typedef struct Grp  { u8 pad[0x994]; } Grp;

typedef struct Node {
    u8 pad00[0x38];
    s8 f38;                          /* +0x38 */
} Node;

class Ent {
public:
    u8 pad000[0x1B0];
    VC_VPTR_MEMBER;    
    
    void f18(f32 t) { VCM(void, (void *, f32), 0x18, t); }                  /* slot 0x18 = 8 + 4*4  */
        
        
        
    
    void f44(f32 t) { VCM(void, (void *, f32), 0x44, t); }                  /* slot 0x44 = 8 + 4*15 */
};

typedef struct Ins {
    u8   pad0000[0x17B0];
    u8   f17B0[0x1F40 - 0x17B0];     /* +0x17B0 */
    u8   f1F40[0x26D0 - 0x1F40];     /* +0x1F40 */
    u8   f26D0[0x35F8 - 0x26D0];     /* +0x26D0 */
    Grp  f35F8[2];                   /* +0x35F8, stride 0x994 */
    u8   pad4920[0x4960 - 0x4920];
    u8   f4960[0x4F90 - 0x4960];     /* +0x4960 */
    u8   f4F90[0x5D8C - 0x4F90];     /* +0x4F90 */
    f32  f5D8C;                      /* +0x5D8C */
    u8   pad5D90[0x5EF1 - 0x5D90];
    u8   f5EF1;                      /* +0x5EF1 */
} Ins;

extern "C" f32 D_0047D1FC;

extern "C" void  ModelSetRot_151080(u8 *h, f32 *v);
extern "C" void  ModelSetPos_151110(u8 *h, f32 *v);
extern "C" void  ObjGetAttachNodePos_1adec0(Ent *e, s32 k, f32 *v);
extern "C" void  insect_InsectBoardCellToWorld_4eda70(u8 *t, f32 *a, f32 *b, f32 *c, s32 k,
                                     f32 x, f32 y);
extern "C" Node *insect_InsectBoardGetPiece_4ee9a0(u8 *t, s16 x, s16 y);
extern "C" void  insect_InsectCursorSetGetCell_511a40(u8 *t, s32 k, s32 *a, s32 *b);
extern "C" Node *insect_InsectTeamGetPiece_5138d0(Grp *g, s32 i);
extern "C" s32   insect_InsectBattleGetState_50d6f0(Ins *o, s32 k);
extern "C" Ent  *insect_InsectBattleGetPieceModel_50df60(Ins *o, Node *p);
extern "C" s32   insect_InsectBattleTestFlag_50da40(Ins *o, s32 k);

extern "C" void insect_InsectBattleMarkerModelUpdate_50c100(Ins *o)
{
    s32   x8C;
    s32   x88;
    s32   x84;
    s32   x80;
    f32   v70[4] __attribute__((aligned(16)));
    f32   v60[4] __attribute__((aligned(16)));
    f32   v50[4] __attribute__((aligned(16)));
    s32   ok;
    s32   j;
    s32   k;
    u8   *h;
    Node *hn;
    Grp  *g;
    Ent  *e;
    u8   *cp;
    u32   cn;
    f32   ang;

    if (insect_InsectBattleTestFlag_50da40(o, 0x27) != 0 || insect_InsectBattleTestFlag_50da40(o, 0x28) != 0
        || insect_InsectBattleTestFlag_50da40(o, 0x29) != 0) {
        ok = 1;
        j = 0;
        k = -1;
        switch (insect_InsectBattleGetState_50d6f0(o, 0)) {
        case 0x16:
        case 0x19:
            k = 0xB;
            break;
        case 0x10:
        case 0xE:
            k = 2;
            break;
        case 0x13:
            k = 0xA;
            break;
        case 9:
        case 0xA:
            k = 9;
            if (o->f5EF1 == 0) {
                j += 5;
            }
            break;
        default:
            ok = 0;
            break;
        }
        if (k != -1) {
            insect_InsectCursorSetGetCell_511a40(o->f4F90, k, &x8C, &x88);
            x88 += j;
        }
        h = 0;
        if (insect_InsectBattleTestFlag_50da40(o, 0x27) != 0) {
            h = o->f17B0;
        }
        if (insect_InsectBattleTestFlag_50da40(o, 0x28) != 0) {
            h = o->f1F40;
        }
        if (insect_InsectBattleTestFlag_50da40(o, 0x29) != 0) {
            h = o->f26D0;
        }
        if (h == 0) {
            ok = 0;
        }
        if (ok != 0) {
            insect_InsectBoardCellToWorld_4eda70(o->f4960, &v70[0], &v70[1], &v70[2], 0,
                                (f32)x8C, (f32)x88);
            hn = insect_InsectBoardGetPiece_4ee9a0(o->f4960, (s16)x8C, (s16)x88);
            if (insect_InsectBattleGetState_50d6f0(o, 0) == 0xA) {
                g = &o->f35F8[o->f5EF1];
                insect_InsectCursorSetGetCell_511a40(o->f4F90, 8, &x84, &x80);
                hn = insect_InsectTeamGetPiece_5138d0(g, x80);
                if (insect_InsectBattleGetPieceModel_50df60(o, hn) != 0) {
                    insect_InsectBoardCellToWorld_4eda70(o->f4960, &v70[0], &v70[1], &v70[2], 1,
                                        (f32)x8C, (f32)x88);
                } else {
                    hn = insect_InsectBoardGetPiece_4ee9a0(o->f4960, (s16)x8C, (s16)x88);
                }
            }
            if (hn != 0) {
                e = insect_InsectBattleGetPieceModel_50df60(o, hn);
                if (e != 0) {
                    ObjGetAttachNodePos_1adec0(e, 0, v60);
                    v70[1] = v60[1];
                    v70[1] = v70[1] + 3.0f;
                    if (hn->f38 == 0x10) {
                        v70[1] = v70[1] + 0.5f;
                    }
                } else {
                    v70[1] = v70[1] + 1.0f;
                }
            } else {
                v70[1] = v70[1] + 1.0f;
            }
            ModelSetPos_151110(h, v70);
            ang = D_0047D1FC * o->f5D8C / 180.0f;
            cp = (u8 *)v50;
            cn = 0x10;
            if (cp != 0) {
                do {
                    *cp = 0;
                    cn--;
                    cp++;
                } while (cn != 0);
            }
            v50[1] = ang;
            v50[0] = 0.0f;
            v50[2] = 0.0f;
            ModelSetRot_151080(h, v50);
            ((Ent *)h)->f18(1.0f);
            ((Ent *)h)->f44(1.0f);
        }
    }
}
