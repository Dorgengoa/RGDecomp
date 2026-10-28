/* MATCH (s41m). Stale pre-match note follows -- PARK improved in main s22 by [[mwcc-const-sdata-load-hoist]] (const +
   .sdata on this unit's READ-ONLY gp float externs): 20 -> 19 bad.  Real progress,
   not a close -- the rest of the residue is a different class. */
#include "types.h"
#include "vec.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct {
    u8 pad0[0x190];
    Vec4 unk190;
    u8 pad1a0[0x1B0 - 0x1A0];
    struct {
        u8 pad0[0x44];
        void (*unk44)(void *, f32);
    } *unk1B0;
} Obj16_00386150;

typedef struct {
    u8 pad0[0x4CC];
    f32 unk4CC;
} Obj18_00386150;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} Buf00386150;

typedef struct {
    Obj18_00386150 *unk0;
    Obj16_00386150 *unk4;
    s32 unk8;
    f32 unkC;
    f32 unk10;
} Obj00386150;

f32 Sinf_128fd0(f32);                              /* extern */
void ModelSetRot_151080(Obj16_00386150 *, Vec4 *);        /* extern */
void ModelSetPos_151110(Obj16_00386150 *, Buf00386150 *); /* extern */
void ObjGetAttachNodePos_1adec0(Obj18_00386150 *, s32, Buf00386150 *); /* extern */
extern f32 D_0047D1FC __attribute__((section(".sdata")));
extern f32 D_0047D400 __attribute__((section(".sdata")));
extern f32 D_0047D93C __attribute__((section(".sdata")));

class VC_0 {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f(f32 x0) { VCM(void, (void *, f32), 0x44, x0); }
};
void MenuCursorObjBobUpdate_386150(Obj00386150 *arg0) {
    Buf00386150 sp60 __attribute__((aligned(16)));
    Vec4 sp50 __attribute__((aligned(16)));
    f32 temp_f1;
    f32 lim;
    f32 temp_f20;
    Obj16_00386150 *temp_16;
    Obj18_00386150 *temp_18;

    if ((arg0->unk0 != NULL) && (arg0->unk8 != 0)) {
        temp_16 = arg0->unk4;
        if (temp_16 != NULL) {
            temp_f1 = arg0->unk10 + D_0047D93C;
            lim = D_0047D1FC;
            arg0->unk10 = temp_f1;
            if (!(temp_f1 <= lim)) {
                arg0->unk10 = (f32) (temp_f1 - lim);
            }
            sp50 = temp_16->unk190;
            temp_f20 = 0.0f;
            temp_f20 = temp_f20 + Sinf_128fd0(arg0->unk10);
            temp_18 = arg0->unk0;
            if (temp_18 != NULL) {
                ObjGetAttachNodePos_1adec0(temp_18, 0, &sp60);
                sp60.unk4 = sp60.unk4 + (0.5f * temp_18->unk4CC);
            }
            sp50.y = sp50.y + D_0047D400;
            sp60.unk4 = sp60.unk4 + (arg0->unkC + temp_f20);
            ModelSetPos_151110(temp_16, &sp60);
            ModelSetRot_151080(temp_16, &sp50);
            ((VC_0 *)(temp_16))->f(1.0f);
        }
    }
}

}
