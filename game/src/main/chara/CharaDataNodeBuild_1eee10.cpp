/* rgp:protos */
#line 1
#include "types.h"

/* jalr $25 == C++ virtual dispatch; slot = 8 + 4*index. */

class VE {
    u8 pad_[0x1B0];
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f5C() { VCM0(void, 0x5C); }
};

struct Obj {
    u8 pad000[0x44C];
    s32 f44C;
    u8 pad450[0xA0];
    s32 f4F0;
    u8 pad4F4[0x8];
    s32 f4FC;
    u8 pad500[0x18];
    s32 f518;
    u8 pad51C[0x4];
    f32 f520;
    f32 f524;
    u8 pad528[0xC];
    s32 f534;
};

struct Self {
    u8 pad00[0x8];
    s16 f8;
    s16 fA;
    u8 pad0C[0x4];
    void *f10;
    s16 f14[4];
    s16 f1C;
    u8 pad1E[0x2];
    Obj *f20;
    s32 f24;
    s16 f28;
    s16 f2A;
    void *f2C;
    s32 f30;
    s16 f34;
    s16 f36;
    s32 f38;
};

struct Desc {
    u8 pad00[0x28];
    s32 f28;
    void *p2C;
    s32 f30;
    s32 f34;
    void *p38;
    s32 f3C;
    s32 a40[8];
    s32 a60[8];
    u8 pad80[0x1C];
};

extern "C" void *memset(void *, s32, s32);
extern "C" void *memcpy(void *, void *, s32);
extern "C" void MemStackAlign64_14d8e0(void *);
extern "C" void CharaDataNodeFree_1eeba0(Self *);
extern "C" Obj *Character2NewFromInfoCfg_1ed270(Desc *, void *, void *, void *, s32);
extern "C" void IdSlotTableAdd_1efb10(void *, Obj *, s32);
extern "C" void *ArchiveGetFileByPath_1c2800(void *, char *, s32 *);
extern "C" void ActCfgLoadText_23b1d0(void *, s32, s32);
extern "C" void MovCfgParse_311aa0(void *, s32, s32);
extern "C" void *MemStackNew_14e1b0(s32, void *);
extern "C" void *ConstructNewArray_100710(void *, void *, s32, s32, s32);
extern "C" void ModelObjExCopy_1aff40(Obj *, void *, void *);
extern "C" s32 IdSlotTableFind_1efa60(void *, s32);
extern "C" Obj *IdSlotTableGet_1efaa0(void *, s32);
extern "C" s32 Character2LoadInfoCfgModels_1ed190(Desc *, void *, void *, void *, Obj *);
extern "C" s32 InfoCfgLoad_1ed0d0(Desc *, void *, void *, void *, Obj *);
extern "C" void *MemStackAllocAligned64_14da10(void *, s32);
extern "C" Obj *SoundBankLoad_1b9f00(s32, void *, void *);
extern "C" u8 *GetCurrentScene_1f5be0(void);
extern "C" s32 GameSceneSoundSlot1GetHandle_1d07b0(s32);
extern "C" void CharaDataNodeLoadFailStub_1ef7a0(void);
extern "C" void Character2Ctor_1ef2d0(void);
extern "C" f32 D_0045B080[];
extern "C" u8 D_004B3910[];
extern "C" char D_0045B750[];
extern "C" char D_0045B758[];

extern "C" s32 CharaDataNodeBuild_1eee10(Self *self, void *src, s32 len, void *heap)
{
    Desc d __attribute__((aligned(16)));
    Obj *o;
    s32 ok;
    s32 i;
    s32 v;
    void *p;
    f32 c;
    s32 out;

    if (src == 0) {
        return 0;
    }
    memset(&d, 0, 0x88);
    d.p2C = d.a40;
    d.f30 = 8;
    d.p38 = d.a60;
    d.f3C = 8;
    ok = 0;
    MemStackAlign64_14d8e0(heap);
    switch (self->f8) {
    case 0:
        CharaDataNodeFree_1eeba0(self);
        v = self->fA;
        {s32 t = (v < 0x1388) ^ 1;
        if (t != 0) { t = (v < 0x1770); }
        if (t != 0) {
            self->f20 = Character2NewFromInfoCfg_1ed270(&d, src, heap, self->f10, (s16)v);
        } else {
            self->f20 = Character2NewFromInfoCfg_1ed270(&d, src, heap, self->f10, -1);
        }}
        if (self->f20 == 0) {
            return -1;
        }
        c = D_0045B080[0];
        self->f20->f520 = 20.0f * c;
        self->f20->f524 = 80.0f * c;
        IdSlotTableAdd_1efb10(D_004B3910, self->f20, self->fA);
        ({ __typeof__(ArchiveGetFileByPath_1c2800(src, D_0045B750, &out)) rgp_ao0 = ArchiveGetFileByPath_1c2800(src, D_0045B750, &out); ActCfgLoadText_23b1d0(rgp_ao0, out, self->fA); });
        ({ __typeof__(ArchiveGetFileByPath_1c2800(src, D_0045B758, &out)) rgp_ao1 = ArchiveGetFileByPath_1c2800(src, D_0045B758, &out); MovCfgParse_311aa0(rgp_ao1, out, self->fA); });
        i = self->f2A;
        if (i > 0) {
            self->f2C = ConstructNewArray_100710(MemStackNew_14e1b0(i * 0x790 + 0x10, heap),
                                     (void *)Character2Ctor_1ef2d0, 0, 0x790, i);
            if (self->f2C != 0) {
                for (i = 0; i < self->f2A; i++) {
                    ((VE *)((u8 *)self->f2C + i * 0x790))->f5C();
                    ModelObjExCopy_1aff40(self->f20, (u8 *)self->f2C + i * 0x790, heap);
                }
            } else {
                self->f2A = 0;
            }
        }
        ok = 1;
        break;
    case 1:
        if ((o = IdSlotTableGet_1efaa0(D_004B3910, IdSlotTableFind_1efa60(D_004B3910, self->f24))) != 0) {
            CharaDataNodeFree_1eeba0(self);
            if ((ok = Character2LoadInfoCfgModels_1ed190(&d, src, heap, self->f10, o)) == 1) {
                self->f20 = o;
                self->f1C = d.f34;
                for (i = 0; i < self->f1C; i++) {
                    self->f14[i] = d.a60[i];
                }
                self->f20->f44C = self->f38;
            }
        }
        break;
    case 2:
        if ((o = IdSlotTableGet_1efaa0(D_004B3910, IdSlotTableFind_1efa60(D_004B3910, self->f24))) != 0) {
            CharaDataNodeFree_1eeba0(self);
            if ((ok = InfoCfgLoad_1ed0d0(&d, src, heap, self->f10, o)) != 0) {
                self->f20 = o;
                self->f1C = d.f28;
                for (i = 0; i < self->f1C; i++) {
                    self->f14[i] = d.a40[i];
                }
            }
        }
        break;
    case 4:
        p = MemStackAllocAligned64_14da10(heap, len / 16);
        self->f20 = (Obj *)p;
        if (p == 0) {
            return -1;
        }
        if (p != 0) {
            memcpy(p, src, len);
            ok = 1;
        }
        if (self->f34 > 0) {
            p = MemStackAllocAligned64_14da10(heap, self->f34);
            self->f30 = (s32)p;
            if (p == 0) {
                self->f34 = 0;
            }
        }
        break;
    case 5:
        self->f20 = SoundBankLoad_1b9f00(self->f28, src, heap);
        o = IdSlotTableGet_1efaa0(D_004B3910, IdSlotTableFind_1efa60(D_004B3910, self->f24));
        if (o != 0) {
            if ((s32)self->f20 != -1) {
                o->f4FC = (s32)self->f20;
                o->f518 = (s32)((u8 *)GetCurrentScene_1f5be0() + 0xB0A4);
                o->f4F0 = GameSceneSoundSlot1GetHandle_1d07b0((s32)GetCurrentScene_1f5be0());
                o->f534 = 0;
            }
        }
        ok = 1;
        break;
    }
    CharaDataNodeLoadFailStub_1ef7a0();
    return ok;
}
