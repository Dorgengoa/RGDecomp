/* rgp:protos */
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARK 1/3: length-wrong (91w vs retail 90w, ours LONGER). VTable/struct layout (VT96C) is a rough guess from m2c's dot-chains; fixed a strcat() implicit-conversion compile error and an arity mismatch on Sprintf_1343b8 (one call site showed 3 args, another 4 -- padded the 3-arg site with a guessed trailing 0). */
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct VT96C {
    u8 pad10[0x10];
    u8 unkC[4];
    u8 pad118m[0x104];
    char *(*unk118)(void *, s32);
    u8 pad1a4[0x8C];
    s32 (*unk1A4)(void *);
    u8 pad1c0m[0x18];
    s32 (*unk1C0)(void *);
} VT96C;

typedef struct Obj96C {
    VT96C *unk0;
    u8 pad10[0x10 - 4];
} Obj96C;

void Sprintf_1343b8(...);
void UiSetTextCenteredX_28f300(s32, s32, s32, s32);
s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
void UiSetWidgetPos_290f60(s32, s32, s32, s32);
void UiWindowFrameSetSize_388380(s32, s32, s32);
char *InsectCageMenuMsgLookup_389d30(s32);
s32 ScreenGetHeight_390ce0(void);
s32 ScreenGetWidth_390d10(void);
char *strcat(char *, const char *);
char *strcpy(char *, const char *);
extern u8 D_00463F38[];
extern u8 *D_00483304;
extern s32 D_00483308;

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    char * f(s32 x0) { return VCM(char *, (void *, s32), 0x118, x0); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    char * f(s32 x0) { return VCM(char *, (void *, s32), 0x118, x0); }
};
class VC_2 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x1A4); }
};
class VC_3 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x1C0); }
};
void InsectCageNameLabelSetMaybe_388040(u8 *arg0) {
    char sp90[96] __attribute__((aligned(16)));
    char sp30[96] __attribute__((aligned(16)));
    u8 sp20[16] __attribute__((aligned(16)));
    s32 temp_16_2;
    s32 temp_5;
    Obj96C *temp_16;

    if ((arg0 != NULL) && (D_00483304 != NULL)) {
        temp_16 = *(Obj96C **)(arg0 + 0x96C);
        sp30[0] = 0;
        sp90[0] = 0;
        if (((VC_0 *)(temp_16))->f(0) != 0) {
            strcpy(sp90, ((VC_1 *)(temp_16))->f(0));
        }
        temp_5 = *(s32 *)(*(u8 **)((u8 *)temp_16 + 0x10) + 0xC);
        if (temp_5 != 0) {
            strcpy(sp30, (char *)temp_5);
        }
        Sprintf_1343b8(sp20, D_00463F38, ((VC_2 *)(temp_16))->f());
        if (!(((VC_3 *)(temp_16))->f() == 0)) {
            strcat(sp30, InsectCageMenuMsgLookup_389d30(3));
        } else {
            strcat(sp30, (const char *)sp20);
        }
        Sprintf_1343b8(D_00483304, InsectCageMenuMsgLookup_389d30(1), sp90, sp30);
        UiWindowFrameSetSize_388380(UiGetWidgetSprite_28fe10(D_00483308, 0x7544, 0), 0x190, 0x28);
        UiSetTextCenteredX_28f300(D_00483308, 0x7544, 0xAE, 0);
        temp_16_2 = (ScreenGetWidth_390d10() >> 1) - 0xC8;
        UiSetWidgetPos_290f60(D_00483308, 0x7544, temp_16_2, ScreenGetHeight_390ce0() - 0x3C);
    }
}

}
