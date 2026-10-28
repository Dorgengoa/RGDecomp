/* rgp:protos */
#line 1
#include "types.h"

class VO397ee0 {
public:
    u8 pad0[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v21() { VCM0(void, 0x5C); }
};

typedef struct {
    u8 pad0[8];
    s32 m8;
} C397ee0;

typedef struct {
    u8 pad0[4];
    C397ee0 *m4;
    s16 m8;
} B397ee0;

typedef struct {
    u8 pad0[4];
    B397ee0 *m4;
} A397ee0;

typedef struct {
    u8 pad0[4];
    s16 m4;
} E397ee0;

typedef struct {
    u8 pad0[0x18];
    E397ee0 *m18;
} D397ee0;

typedef struct {
    u8 pad0[4];
    D397ee0 *m4;
} P397ee0;

extern "C" {
void Sprintf_1343b8(s32, u8 *, s32);
void MemStackReset_14d830(s32);
s32 MemStackNew_14e0b0(s32, s32);
u8 *MemStackNew_14e130(s32, s32);
void NameTableFreeGroup_158ac0(s32, s32);
s32 GetDrawCtxNameTable_15de40(void);
void PadSetStickDpadThreshold_183950(u8 *, s32);
void PadClearRepeatAll_183960(u8 *);
void PadSetRepeat_183d50(u8 *, s32, s32, s32);
void ModelObjExCtor_1c4920(u8 *, int, int, int);
s32 GetMenuResGroup_206a40(void);
s32 GetMenuTransdataStack_206a60(void);
P397ee0 *GetSelectedInsectEntryMaybe_206ad0(void);
void UiEntryListReset_28ec80(u8 *);
void UiWidgetListReset_2912e0(u8 *);
void InsectMenuResLoadPoll_398420(void);
void InsectMenuResRequest_3987e0(void);
s32 CageRecGetCatchDef_3d09c0(D397ee0 *, int, int, int);
A397ee0 *ItemDefGetInsectData_40e0b0(s32);
void ResGroupUnloadGroup_42b650(s32, s32);
void *memset(void *, s32, u32);
char *strcpy(char *, const char *);
extern u8 D_00454460[];
extern u8 D_004642F0[0x400];
extern char D_00464308[];
extern u8 D_00470F50[];
extern s16 D_0047FF40;
extern s32 D_0047FF44;
extern s32 D_0047FF48;
extern s16 D_0047FF4C;
extern s16 D_0047FF54;
extern s32 D_0047FF5C;
extern s32 D_004834E8;
extern s16 D_004834F0;
extern s32 D_004834F4;
extern u8 *D_004834F8;
extern s16 D_00483500;
extern s16 D_00483504;
extern s16 D_00483508;
extern s8 D_0048350C;
extern u8 *D_00483518;
extern s32 D_0048351C;
extern s8 D_00483528;
extern s8 D_0048352C;
extern s32 D_00483530;
extern s32 D_00483534;
extern s32 D_00483538;
extern s32 D_00483550;
extern s8 D_00483555;
extern s32 D_00483560;
extern s8 D_00483568;
extern s32 *D_0048356C;
extern u8 D_004B2570[];
extern u8 D_004E95C0[];
extern u8 D_004E95E0[];
}

extern "C" void InsectMenuOpen_397ee0(s16 arg0)
{
    s32 i;
    s32 h;
    P397ee0 *p;
    s32 q;
    A397ee0 *r;
    B397ee0 *b;
    C397ee0 *c;
    u8 *o;
    s16 k;

    D_0047FF4C = arg0;
    D_0047FF44 = 0x3F800000;
    D_00483508 = 0;
    D_00483528 = 0;
    D_0048350C = 0;
    D_004834E8 = GetMenuTransdataStack_206a60();
    MemStackReset_14d830(D_004834E8);
    D_00483530 = MemStackNew_14e0b0(0x80, D_004834E8);
    D_00483534 = MemStackNew_14e0b0(0x80, D_004834E8);
    D_00483538 = MemStackNew_14e0b0(0x80, D_004834E8);
    D_0048356C = (s32 *)MemStackNew_14e0b0(0x18, D_004834E8);
    for (i = 0; i < 6; i++) {
        D_0048356C[i] = MemStackNew_14e0b0(0x80, D_004834E8);
    }
    D_0048351C = 0;
    ResGroupUnloadGroup_42b650(GetMenuResGroup_206a40(), 2);
    UiWidgetListReset_2912e0(D_004E95C0);
    UiEntryListReset_28ec80(D_004E95E0);
    D_004834F8 = D_00454460;
    D_004834F4 = 0;
    D_004834F0 = 0;
    PadClearRepeatAll_183960(D_004B2570);
    PadSetRepeat_183d50(D_004B2570, 0xF00C, 0xA, 3);
    PadSetStickDpadThreshold_183950(D_004B2570, 0x78);
    D_00483504 = 1;
    D_00483500 = 1;
    D_0047FF40 = 1;
    D_0047FF48 = -1;
    h = GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(h, 0x32D);
    NameTableFreeGroup_158ac0(h, 0x32E);
    D_00483568 = 0;
    D_0047FF54 = -1;
    D_00483518 = 0;
    D_0048352C = 0;
    if (D_0047FF4C != 0) {
        p = GetSelectedInsectEntryMaybe_206ad0();
        if (p == NULL) {
            return;
        }
        if (p->m4->m18->m4 > 0) {
            q = CageRecGetCatchDef_3d09c0(p->m4, 0, 0, 0);
            if (q == 0) {
                return;
            }
            r = ItemDefGetInsectData_40e0b0(q);
            if (r == NULL) {
                return;
            }
            b = r->m4;
            if (b == NULL) {
                return;
            }
            c = b->m4;
            if (c == NULL) {
                return;
            }
            Sprintf_1343b8(D_00483538, D_004642F0, c->m8);
            D_0047FF5C = D_00483538;
            o = MemStackNew_14e130(0x790, D_004834E8);
            if (o != NULL) {
                ModelObjExCtor_1c4920(o, 0, 0, 0);
                *(u8 **)(o + 0x1B0) = D_00470F50;
            }
            D_00483518 = o;
            ((VO397ee0 *)o)->v21();
            D_00483560 = -1;
            memset(&D_00483550, 0, 0x10);
            strcpy((char *)&D_00483550, D_00464308);
            k = b->m8;
            D_0047FF54 = k;
            D_00483555 = k + 0x31;
        }
    }
    InsectMenuResRequest_3987e0();
    InsectMenuResLoadPoll_398420();
}
