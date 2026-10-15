#include "types.h"
#pragma opt_propagation off

typedef struct Ent {
    s16 h0;     /* 0x00 */
    u8 b2;      /* 0x02 */
    u8 b3;      /* 0x03 */
    s16 h4;     /* 0x04 */
    s16 h6;     /* 0x06 */
    s16 h8;     /* 0x08 */
    s16 hA;
    s32 wC;     /* 0x0C */
    s32 w10;    /* 0x10 */
    s32 pad14[3];
    void *w20;  /* 0x20 */
} Ent;

s32 SlotGetInt_15f720(s32);
s32 VariantGetInt_15f780(s32);
s32 DataTableStoreString_368ab0(u8 *, s32);
s32 ItemDefIsInsect_40e340(Ent *);
s32 ItemDefIsKind3_40e350(Ent *);
s32 ItemDefIsKind2_40e360(Ent *);
s32 ItemDefIsSpecialWeapon_40e370(Ent *);
s32 ItemDefIsWeapon_40e400(Ent *);
void **ArenaNew_40e500(s32, u8 *, s32, s32);
extern u8 D_004793A0[];
extern u8 D_004793B0[];
extern u8 D_004793C0[];
extern u8 D_004793D0[];
extern u8 D_004793E0[];
extern u8 D_004793F0[];
extern u8 D_00479400[];
extern u8 *D_004830F8;
extern s16 D_004830FC;

s32 ItemDataCmdAddItem_40d7d0(s64 *arg0) {
    u8 *mgr;
    Ent *e;
    void **p;

    mgr = D_004830F8;
    if (*(s16 *)(mgr + 0x7C) <= 0) return 1;
    if (D_004830FC >= *(s16 *)(mgr + 0x7C)) return 1;
    e = (Ent *)(*(u8 **)(mgr + 0x8C) + D_004830FC * 0x34);
    e->h0 = VariantGetInt_15f780((s32)arg0++);
    SlotGetInt_15f720((s32)arg0++);
    e->wC = DataTableStoreString_368ab0(mgr, SlotGetInt_15f720((s32)arg0++));
    e->b2 = VariantGetInt_15f780((s32)arg0++);
    e->h4 = VariantGetInt_15f780((s32)arg0++);
    e->b3 = VariantGetInt_15f780((s32)arg0++);
    e->h8 = VariantGetInt_15f780((s32)arg0++);
    e->w10 = DataTableStoreString_368ab0(mgr, SlotGetInt_15f720((s32)arg0++));
    e->h6 = VariantGetInt_15f780((s32)arg0);
    e->w20 = NULL;
    if (ItemDefIsSpecialWeapon_40e370(e)) {
        p = ArenaNew_40e500(0x34, mgr + 0x6C, 4, -1);
        if (p != NULL) {
            *p = D_00479400;
            *p = D_004793F0;
            *p = D_004793E0;
            *p = D_004793D0;
        }
        e->w20 = p;
    } else if (ItemDefIsWeapon_40e400(e)) {
        p = ArenaNew_40e500(0x2C, mgr + 0x6C, 4, -1);
        if (p != NULL) {
            *p = D_00479400;
            *p = D_004793F0;
            *p = D_004793E0;
        }
        e->w20 = p;
    } else if (ItemDefIsKind2_40e360(e)) {
        p = ArenaNew_40e500(0x18, mgr + 0x6C, 4, -1);
        if (p != NULL) {
            *p = D_00479400;
            *p = D_004793F0;
            *p = D_004793C0;
            *p = D_004793B0;
        }
        e->w20 = p;
    } else if (ItemDefIsKind3_40e350(e)) {
        p = ArenaNew_40e500(0x14, mgr + 0x6C, 4, -1);
        if (p != NULL) {
            *p = D_00479400;
            *p = D_004793F0;
            *p = D_004793C0;
        }
        e->w20 = p;
    } else if (ItemDefIsInsect_40e340(e)) {
        p = ArenaNew_40e500(0x2C, mgr + 0x6C, 4, -1);
        if (p != NULL) {
            *p = D_00479400;
            *p = D_004793A0;
        }
        e->w20 = p;
    }
    D_004830FC++;
    return 1;
}
