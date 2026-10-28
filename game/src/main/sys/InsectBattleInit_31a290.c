/* rgp:protos */
#define RGP_SELF_InsectBattleInit_31a290 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 v[2];
} W2;

typedef struct {
    char *v[2];
} N2;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern char *strcpy(char *, const char *);
extern u32 strlen(const char *);
extern W2 D_0047F238;
extern N2 D_0047F240;
extern u8 *D_00482AF0;
extern s32 D_00482AF8;

void InsectBattleInit_31a290(void)
{
    W2 w __attribute__((aligned(16)));
    f32 *pf;
    N2 names __attribute__((aligned(16)));

    u8 *p;
    u8 *o;
    u8 *q;
    s32 i;
    s32 k;
    s32 off;
    s32 *pw;
    char *nm;

    GetCurrentScene_1f5be0();
    InsectDataStackInit_31a7e0();
    p = ((u8 *)InsectBattleGetMemStack_31a8c0());
    MemStackReset_14d830(p);
    D_00482AF8 = ((s32)MemStackHeapAlloc_14db10(p, 2, 0, 0x40));
    if (D_00482AF8 == 0) {
        InsectBattleShutdown_31a230();
        return;
    }
    if ((o = ((u8 *)MemStackNew_14e230(0x5FD0, p))) != NULL) {
        q = o + 0xE0;
        do {
            MemStackCtor_14e030(q);
            q += 0x58;
        } while (q < o + 0x818);
        MemStackCtor_14e030(o + 0x818);
        Character2Ctor_1ef2d0(o + 0x890, 0, 0, 0);
        Character2Ctor_1ef2d0(o + 0x1020, 0, 0, 0);
        q = o + 0x17B0;
        do {
            Character2Ctor_1ef2d0(q, 0, 0, 0);
            q += 0x790;
        } while (q < o + 0x35F0);
        InsectModelMemCtor_31a550(o + 0x4B4C);
        InsectBattleLogCtor_31a520(o + 0x5080);
        InsectAbilityTableCtor_31a4f0(o + 0x50E8);
        func_522C90(o + 0x51C4);
    }
    D_00482AF0 = o;
    func_50E810(o);
    pf=(f32*)&w;
    pf[0] = *(f32 *)&D_0047F238.v[0];
    pf[1] = *(f32 *)&D_0047F238.v[1];
    pf=(f32*)&names;
    pf[0] = *(f32 *)&D_0047F240.v[0];
    pf[1] = *(f32 *)&D_0047F240.v[1];
    for (i = 0; i < 2; i++) {
        q = ((u8 *)MemStackNew_14e230(0x58, p));
        if (q != NULL) {
            q = ((u8 *)MemStackCtor_14e030(q));
        }
        if (q == NULL) {
            continue;
        }
        MemStackClear_14dff0(q);
        pw = &w.v[i];
        if (*pw == -1) {
            *pw = *(s32 *)(p + 0x34) - *(s32 *)(p + 0x2C);
        }
        off = (u32)i * 4;
        pw = (s32 *)((u8 *)w.v + off);
        k = *pw;
        MemStackHeapInit_14dee0(q, MemStackAllocQw_14d950(p, k), k);
        nm = *(char **)((u8 *)names.v + off);
        if (strlen(nm) < 0x10) {
            strcpy((char *)q, nm);
        }
        MemStackHeapReinit_14de90(q);
        func_50E5D0(D_00482AF0, q, i);
    }
    MemStackReturnToOwnerMaybe_14dad0(p);
    func_50E370(D_00482AF0);
    func_50E310(D_00482AF0);
    func_50E2B0(D_00482AF0);
    func_50E260(D_00482AF0);
    func_50E5E0(D_00482AF0);
    InsectBattleReinit_31a5b0();
}
