/* rgp:protos */
#line 1
#include "types.h"
/* insect 0x0051DC30 -- 1,036 B, br 18.  NINE parameters: $4-$11 (arg 4 = $7 is
 * unused) plus one at 0xB0($29).  C++: two virtual calls through the vptr at
 * +0x1B0, slots 0x5C (#21) and 0x50 (#18) [[jalr-is-cpp-virtual]]; the vptr
 * itself is STORED by this function (lui 0x47 / addiu 0x0F50), so it goes
 * through a `volatile` alias member.
 *
 * `sq $2,0xA0($29)` / `lq $2,0xA0($29)` above the callee-saved area is the
 * SPILL of the func_2D9040 result -- nine callee-saved registers are already
 * live, so one more value has to go to the stack.
 *
 * Two jump tables: insect_jtbl_00525510 is nine cases 0x1A..0x22 that ALL share one
 * body; insect_jtbl_005254B0 is 0xE..0x22.  Source arm order = ascending arm ADDRESS
 * (0xE, 0xF, {0x12,0x15,0x16}, 0x1A, 0x10, 0x13, 0x11, 0x17, 0x1E,
 * {0x18,0x19}, {0x1B,0x1C,0x1D,0x1F}), not test order.
 */

typedef struct E {
    u8  pad000[0x8];
    s32 f08;                        /* +0x08 */
    u8  pad00C[0x14 - 0xC];
    s32 f14;                        /* +0x14 */
} E;

typedef struct A {
    s32 f00;                        /* +0x00 */
    s32 f04;                        /* +0x04 */
    E  *f08[15];                    /* +0x08 */
    s32 f44;                        /* +0x44 */
    f32 f48;                        /* +0x48 */
} A;

typedef struct N {
    void *f00;                      /* +0x00 */
    s32   f04;                      /* +0x04 */
    s32   f08;                      /* +0x08 */
    s32   f0C;                      /* +0x0C */
    s32   f10;                      /* +0x10 */
    s32   f14;                      /* +0x14 */
    s16   f18;                      /* +0x18 */
    s16   f1A;                      /* +0x1A */
    s16   f1C;                      /* +0x1C */
    s16   f1E;                      /* +0x1E */
} N;

typedef struct ObjR {
    u8  pad000[0x1B0];
    u8 *volatile f1B0;              /* +0x1B0 -- the vptr retail stores */
    u8  pad1B4[0x538 - 0x1B4];
    s32 f538;                       /* +0x538 */
    s32 f53C;                       /* +0x53C */
} ObjR;

class ObjV {
public:
    u8 pad000[0x1B0];
    VC_VPTR_MEMBER;    
        
        
        
        
        
    void f50() { VCM0(void, 0x50); }                       /* slot 0x50 = 8 + 4*18 */
      
    void f5C() { VCM0(void, 0x5C); }                       /* slot 0x5C = 8 + 4*21 */
};

extern "C" u8  D_00470F50[];
extern "C" u8  insect_D_00525408[];
extern "C" s32 D_0047E180;

extern "C" s32   GetEffectMgr_2d9040(void);
extern "C" s32   MemStackHeapAlloc_14db10(s32 h, s32 a, s32 b, s32 c);
extern "C" void *MemStackNew_14e230(s32 n, s32 h);
extern "C" void  MemStackReturnToOwnerMaybe_14dad0(s32 h);
extern "C" s32   ObjRecGetLiveObject_1c4a90(s32 h, s32 k);
extern "C" void  ModelObjExCopy_1aff40(s32 r, ObjR *o, s32 h);
extern "C" void  ModelObjPlayMotionByName_1867a0(ObjR *o, u8 *s, s32 k);
extern "C" void  insect_InsectBattleEffectNodeReset_51e120(N *n);
extern "C" void insect_ModelObjExCtor_4f78f0(ObjR *, int, int, int);
extern "C" void  insect_InsectPlaySe_510870(s32 k);
extern "C" void  insect_InsectBattlePlayBankSe_5107d0(s32 k);
extern "C" s32   insect_InsectBattleEffectsAddSlot_51dbe0(A *a, N *n);

extern "C" s32 insect_InsectBattleEffectsSpawn_51dc30(A *a, s32 b, s32 c, s32 p3, s32 d, s32 e,
                                   s32 f, s32 g, s32 h9)
{
    s32   x;
    s32   i;
    N    *n;
    s32   hh;
    s32   res;
    s32   flags;
    s32   q;
    s32   ctr;
    E    *ent;
    ObjR *o;

    x = GetEffectMgr_2d9040();
    if (c == -1) {
        return -1;
    }
    for (i = 0; i < 0xF; i++) {
        ent = a->f08[i];
        if (ent != 0) {
            if (ent->f08 == b && c == ent->f14) {
                return 1;
            }
        }
    }
    hh = MemStackHeapAlloc_14db10(a->f00, 2, 0, 0x40);
    if (hh == 0 || a->f04 == 0 || a->f00 == 0) {
        return 0;
    }
    n = (N *)MemStackNew_14e230(0x20, a->f00);
    if (n == 0) {
        return 0;
    }
    insect_InsectBattleEffectNodeReset_51e120(n);
    n->f10 = hh;
    n->f08 = b;
    n->f0C = d;
    n->f14 = c;
    n->f1C = (s16)e;
    n->f1E = (s16)f;
    n->f18 = -1;
    n->f04 = h9;
    o = (ObjR *)MemStackNew_14e230(0x790, a->f00);
    if (o != 0) {
        insect_ModelObjExCtor_4f78f0(o, 0, 0, 0);
        o->f1B0 = D_00470F50;
    }
    flags = 0;
    switch (c) {
    case 0x1A:
    case 0x1B:
    case 0x1C:
    case 0x1D:
    case 0x1E:
    case 0x1F:
    case 0x20:
    case 0x21:
    case 0x22:
        res = a->f44;
        break;
    default:
        res = ObjRecGetLiveObject_1c4a90(a->f04, c + 0x80);
        break;
    }
    switch (c) {
    case 0xE:
        flags |= 2;
        break;
    case 0xF:
        flags |= 2;
        if (g != 0) {
            insect_InsectPlaySe_510870(6);
        }
        break;
    case 0x12:
    case 0x15:
    case 0x16:
        flags |= 2;
        break;
    case 0x1A:
        if (g != 0) {
            insect_InsectBattlePlayBankSe_5107d0(0x139);
        }
        flags |= 2;
        break;
    case 0x10:
        flags |= 2;
        if (g != 0) {
            insect_InsectPlaySe_510870(8);
        }
        break;
    case 0x13:
        n->f18 = (s16)(60.0f / a->f48);
        break;
    case 0x11:
        n->f18 = (s16)(60.0f / a->f48);
        if (g != 0) {
            insect_InsectPlaySe_510870(5);
        }
        break;
    case 0x17:
        n->f18 = (s16)(60.0f / a->f48);
        n->f1A = (s16)(25.0f / a->f48);
        break;
    case 0x1E:
        n->f18 = (s16)(30.0f / a->f48);
        n->f1A = (s16)(25.0f / a->f48);
        break;
    case 0x18:
    case 0x19:
        n->f18 = (s16)(50.0f / a->f48);
        n->f1A = (s16)(25.0f / a->f48);
        break;
    case 0x1B:
    case 0x1C:
    case 0x1D:
    case 0x1F:
        flags |= 2;
        break;
    case 0x14:
    case 0x20:
    case 0x21:
    case 0x22:
        break;
    }
    if (res != 0) {
        ((ObjV *)o)->f5C();
        ((ObjV *)o)->f50();
        ModelObjExCopy_1aff40(res, o, a->f00);
        q = x + 0x58;
        o->f53C = q;
        if (q != 0) {
            ctr = D_0047E180;
            D_0047E180 = ctr + 1;
            o->f538 = ctr;
        }
        n->f00 = o;
        ModelObjPlayMotionByName_1867a0(o, insect_D_00525408, flags);
    }
    MemStackReturnToOwnerMaybe_14dad0(a->f00);
    return insect_InsectBattleEffectsAddSlot_51dbe0(a, n);
}
