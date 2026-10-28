/* rgp:protos */
#line 1
#include "types.h"
/* normal 0x004FA870 -- the 0x47 prompt line.  Walks the normal_D_005263A0 id table
 * until its -1 sentinel looking for a live func_3C8370 hit; the hit flips the
 * gp state byte 0x44E to 2 and selects the second string / second placement.
 * The two label buffers are then bound into the 0x533E record and the widget is
 * moved to the normal_D_00526390 / normal_D_00526392 pair for the chosen state.
 *
 * C++ virtual: `lw $25,0x60($25)` -> slot (0x60-8)/4 = 22.
 * `daddiu $19,$0,1` for the flag is the C++ `bool` spelling -- every integer
 * width gives `addiu` (levers.d/jalr-is-cpp-virtual).
 * `andi $17,$2,0xFF` on the index is a `u8` counter. */
class Ent {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 s022() { return VCM0(s32, 0x60); }
};

typedef struct Ctx  { u8 pad00[0x18]; s32 f18; } Ctx;
typedef struct St   { u8 pad000[0x44E]; s16 f44E; } St;
typedef struct Hold { u8 pad00[0x20]; void *f20; } Hold;
typedef struct Rec  { u8 pad00[4]; void *f04; u8 pad08[0x14 - 8]; void *f14; } Rec;

extern "C" u8  normal_D_00527820[];
extern "C"       u8  normal_D_00527860[64];
extern "C"       u8  normal_D_005278A0[64];
extern "C" u8  normal_D_005263B0[];
extern "C" s32 normal_D_005263A0[];
extern "C" s16 normal_D_00526390[];
extern "C" s16 normal_D_00526392[];

extern "C" {
extern St   *D_00484454;          /* gp - 0xD1C  */
extern s16   D_004804DC;          /* gp - 0x4C94 */
extern void *D_00481BBC;          /* gp - 0x35B4 */

extern Ctx        *GetGameData_1fede0(void);
extern Ent        *InvFindInCategoryRange_3c8370(s32 w, s32 a, s32 b, s32 c, s32 d, s32 e);
extern Hold       *UiFindWidget_290460(const u8 *p, u16 id);
extern Ent        *PartyGetMemberChara_3c2420(s32 w, s32 i);
extern void       *GetMenuResGroup_206a40(void);
extern Rec        *ResGroupListFindValueById_42c270(void *o, s32 id);
extern void       *ResGroupListFindValueById_42c3a0(void *o, s32 id);
extern const void *MsgTableLookup_28aa30(void *p, s32 id);
extern void        Sprintf_1343b8(void *d, const void *f, ...);
extern void        UiSetTextCenteredX_28f300(const u8 *p, u16 id, s32 c, s32 d);
extern void        UiSetWidgetPos_290f60(const u8 *p, u16 id, s32 x, s32 y);
}

extern "C" void normal_BtlChgMenuLeaderDownNoticeMaybe_4fa870(void)
{
    Ctx  *c;
    s32   i;
    bool  flag;
    Ent  *e;
    Hold *h;
    void *o;
    Rec  *r;
    s32   v;

    flag = false;
    i = 0;
    c = GetGameData_1fede0();
    if (c == 0) {
        return;
    }
    D_00484454->f44E = 1;
    while ((v = normal_D_005263A0[(u8)i]) != -1) {
        if (InvFindInCategoryRange_3c8370(c->f18, v, 0, -1, 0, 0) != 0) {
            D_00484454->f44E = 2;
            flag = true;
            break;
        }
        i = (u8)(i + 1);
    }
    h = UiFindWidget_290460(normal_D_00527820, 0x47);
    if (h != 0) {
        e = PartyGetMemberChara_3c2420(c->f18, D_004804DC);
        o = GetMenuResGroup_206a40();
        r = ResGroupListFindValueById_42c270(o, 0x533E);
        h->f20 = ResGroupListFindValueById_42c3a0(o, flag + 0x5244);
        if (e != 0) {
            Sprintf_1343b8(normal_D_00527860, MsgTableLookup_28aa30(D_00481BBC, 0x32), e->s022());
            if (flag) {
                Sprintf_1343b8(normal_D_005278A0, normal_D_005263B0, MsgTableLookup_28aa30(D_00481BBC, 0x33));
                UiSetTextCenteredX_28f300(normal_D_00527820, 0x47, 0xCA, 0);
                UiSetTextCenteredX_28f300(normal_D_00527820, 0x47, 0xCA, 1);
            } else {
                Sprintf_1343b8(normal_D_005278A0, normal_D_005263B0, MsgTableLookup_28aa30(D_00481BBC, 0x34));
                UiSetTextCenteredX_28f300(normal_D_00527820, 0x47, 0xA6, 0);
                UiSetTextCenteredX_28f300(normal_D_00527820, 0x47, 0xA6, 1);
            }
        }
        r->f04 = normal_D_00527860;
        r->f14 = normal_D_005278A0;
    }
    UiSetWidgetPos_290f60(normal_D_00527820, 0x47, normal_D_00526390[flag * 2], normal_D_00526392[flag * 2]);
}
