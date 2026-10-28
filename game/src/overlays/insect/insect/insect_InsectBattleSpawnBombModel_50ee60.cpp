/* rgp:protos */
#line 1
#include "types.h"
/* insect 0x0050EE60 -- C++ virtual dispatch, vptr at +0x1B0, slot 0x5C =
 * virtual #21 (8 + 4*21).  [[jalr-is-cpp-virtual]]
 *
 * The `lui 0x47 / addiu 0x0F50 / sw 0x1B0` is the INLINED constructor's vptr
 * write, done through a raw alias struct so mwcc does not emit a vtable of
 * our own for the dummy class.
 */

class VQ {
public:
    u8 pad000[0x1B0];
    VC_VPTR_MEMBER;  
      
      
      
      
     void s16() { VCM0(void, 0x48); } 
      
    void s21() { VCM0(void, 0x5C); }                 /* slot 0x5C */
};

/* Alias for the raw vptr write. */
struct QRaw {
    u8 pad000[0x1B0];
    const void *vptr;
};

struct S {
    u8   pad000[0x38];
    s8   f038;
    u8   pad039[0x58 - 0x39];
    VQ  *f058;
    u8   pad05C[0x6C - 0x5C];
    s16  f06C;
};

struct P {
    u8  pad000[0x2C];
    s32 f02C;
    u8  pad030[0x34 - 0x30];
    s32 f034;
};

struct G {
    u8   pad000[0x1E4];
    char f1E4[4];
};

struct Cfg {
    s32   f00;
    const void *f04;
    void *f08;
    void *f0C;
    void *f10;
    s32   f14;
    s32   f18;
    s32   f1C;
    s32   f20;
    s32   f24;
    s32   f28;
    void *f2C;
    s32   f30;
    s32   f34;
    void *f38;
    s32   f3C;
    s32   f40[8];
    s32   f60[8];
    s32   f80[4];
};

extern "C" u8 D_00470F50[];
extern "C" char insect_D_00525108[];
extern "C" char insect_D_00525110[];
extern "C" u8 insect_D_00524C78[];
extern "C" u8 insect_D_00524EC0[];

extern "C" s32   InsectBattleGet_31a8d0(void);
extern "C" s32   GetCurrentScene_1f5be0(void);
extern "C" void  MemStackHeapAlloc_14db10(void *p, s32 a, s32 b, s32 c);
extern "C" void *MemStackNew_14e230(s32 size, void *pool);
extern "C" void *MemStackCtor_14e030(void *o);
extern "C" void  MemStackClear_14dff0(void *o);
extern "C" s32   MemStackAllocQw_14d950(P *p, s32 n);
extern "C" void  MemStackInit_14d810(void *o, s32 a, s32 n);
extern "C" void  MemStackReturnToOwnerMaybe_14dad0(P *p);
extern "C" void  MemStackReset_14d830(void *o);
extern "C" u32   strlen(const char *s);
extern "C" void  strcpy(void *d, const char *s);
extern "C" void  Sprintf_1343b8(char *d, const char *f, s32 a);
extern "C" G    *GetDrawCtxNameTable_15de40(void);
extern "C" void  memset(void *d, s32 c, s32 n);
extern "C" void  InfoCfgParseAll_1afd00(VQ *q, Cfg *c);
extern "C" void  GameSceneObjBindMaybe_1cfcd0(s32 h, s16 id, VQ *q, s32 k);
extern "C" void  ObjRecSetFlag2_1c3e80(s32 h, s32 k, s16 id);
extern "C" s32   insect_InsectFileSlotIsLoaded_512010(s32 a);
extern "C" void  insect_InsectFileSlotRelease_512020(s32 a);
extern "C" s32   insect_InsectFileSlotGetData_511fa0(s32 a, s32 *out);
extern "C" s32   insect_InsectModelMemFindIndex_512870(s32 b, s16 h);
extern "C" P    *insect_InsectModelMemGetSlot_512820(s32 b, s16 h);
extern "C" void insect_ModelObjExCtor_4f78f0(VQ *, int, int, int);
extern "C" void  insect_InsectPieceAttachSubModel_515210(S *s, const u8 *t);

extern "C" s32 insect_InsectBattleSpawnBombModel_50ee60(S *s)
{
    s32  n;
    char buf[4];
    Cfg  cfg __attribute__((aligned(16)));
    s32  r;
    s32  b;
    s32  rv;
    s32  cc;
    s32  a;
    s32  v23;
    s16  h;
    s32  v22;
    P   *p;
    void *o;
    s32  len;
    VQ  *q;
    G   *g;

    rv = 0;
    if (s->f038 != 0x11) {
        return 0;
    }
    r = InsectBattleGet_31a8d0();
    a = r + 0x5000;
    b = r + 0x4B4C;
    cc = GetCurrentScene_1f5be0();
    if (insect_InsectFileSlotIsLoaded_512010(a) != 0) {
        n = 0;
        v23 = insect_InsectFileSlotGetData_511fa0(a, &n);
        h = s->f06C;
        v22 = insect_InsectModelMemFindIndex_512870(b, h);
        p = insect_InsectModelMemGetSlot_512820(b, h);
        MemStackHeapAlloc_14db10(p, 2, 0, 0x40);
        o = MemStackNew_14e230(0x58, p);
        if (o != 0) {
            o = MemStackCtor_14e030(o);
        }
        len = p->f034 - p->f02C;
        MemStackClear_14dff0(o);
        MemStackInit_14d810(o, MemStackAllocQw_14d950(p, len), len);
        MemStackReturnToOwnerMaybe_14dad0(p);
        MemStackReset_14d830(o);
        if (strlen(insect_D_00525108) < 0x10) {
            strcpy(o, insect_D_00525108);
        }
        q = (VQ *)MemStackNew_14e230(0x790, o);
        if (q != 0) {
            insect_ModelObjExCtor_4f78f0(q, 0, 0, 0);
            ((QRaw *)q)->vptr = D_00470F50;
        }
        Sprintf_1343b8(buf, insect_D_00525110, v22);
        g = GetDrawCtxNameTable_15de40();
        strcpy(g->f1E4, buf);
        memset(&cfg, 0, 0x88);
        cfg.f14 = v22 + 0x263;
        cfg.f30 = 8;
        cfg.f2C = cfg.f40;
        cfg.f3C = 8;
        cfg.f38 = cfg.f60;
        cfg.f00 = v23;
        cfg.f04 = insect_D_00524C78;
        cfg.f18 = 1;
        cfg.f08 = o;
        cfg.f0C = o;
        cfg.f10 = o;
        q->s21();
        InfoCfgParseAll_1afd00(q, &cfg);
        g->f1E4[0] = 0;
        s->f058 = q;
        insect_InsectPieceAttachSubModel_515210(s, insect_D_00524EC0);
        insect_InsectFileSlotRelease_512020(a);
        GameSceneObjBindMaybe_1cfcd0(cc, s->f06C + 0x40, q, 0);
        ObjRecSetFlag2_1c3e80(cc, 1, s->f06C + 0x40);
        rv = 1;
    }
    return rv;
}
