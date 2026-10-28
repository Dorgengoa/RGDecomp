/* rgp:protos */
#define RGP_SELF_ActCfgTableClone_2244e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8 { u8 d[0x8]; } E8;
typedef struct EC { u8 d[0xC]; } EC;
typedef struct E10 { u8 d[0x10]; } E10;
typedef struct E14 { u8 d[0x14]; } E14;
typedef struct E18 { u8 d[0x18]; } E18;
typedef struct E7C { u8 d[0x7C]; } E7C;

typedef struct Res {
    s64 x0;
    f32 x8;
    f32 xC;
    s16 x10;
    s16 x12;
    s32 x14;
    s32 x18;
    u8 x1C[4];
    E8 *p20;
    E10 *p24;
    E8 *p28;
    EC *p2C;
    E10 *p30;
    E18 *p34;
    E14 *p38;
    E8 *p3C;
    E7C *p40;
    EC *p44;
    EC *p48;
    EC *p4C;
    E8 *p50;
    E18 *p54;
    EC *p58;
    s16 n5C;
    s16 n5E;
    s16 n60;
    s16 n62;
    s16 n64;
    s16 n66;
    s16 n68;
    s16 n6A;
    s16 n6C;
    s16 n6E;
    s16 n70;
    s16 n72;
    s16 n74;
    s16 n76;
    s16 n78;
    s16 x7A;
} Res;

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ActCfgTableClone_2244e0(Res *a, s32 arg1, Res *b, s32 heap) {
    s32 n;
    s32 i;
    s32 t;

    ActCfgTableReset_225160((void *)a);
    if (heap == 0 || arg1 == 0 || b == 0 || b->x12 < 0 || b->x14 == 0) {
        return 0;
    }
    a->x12 = b->x12;
    a->x0 = b->x0;
    a->x10 = b->x10;
    a->x8 = b->x8;
    a->xC = b->xC;
    a->x7A = b->x7A;
    if (b->p20 != 0) {
        n = b->n5C;
        if (n > 0) {
            a->p20 = (E8 *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x8 + 0x10, heap), ActInfoNameCtor_231570, 0, 0x8, n);
            if (a->p20 == 0) {
                return 0;
            }
            a->n5C = b->n5C;
        }
    }
    if (b->p24 != 0) {
        n = b->n5E;
        if (n > 0) {
            a->p24 = (E10 *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x10 + 0x10, heap), ActInfoMoveCtor_231490, 0, 0x10, n);
            if (a->p24 == 0) {
                return 0;
            }
            a->n5E = b->n5E;
        }
    }
    if (b->p28 != 0) {
        n = b->n60;
        if (n > 0) {
            a->p28 = (E8 *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x8 + 0x10, heap), ActInfoNullCtor_2313f0, 0, 0x8, n);
            if (a->p28 == 0) {
                return 0;
            }
            a->n60 = b->n60;
        }
    }
    if (b->p2C != 0) {
        n = b->n62;
        if (n > 0) {
            a->p2C = (EC *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 0xC + 0x10, heap), ActInfoCmndCtor_231310, 0, 0xC, n);
            if (a->p2C == 0) {
                return 0;
            }
            a->n62 = b->n62;
        }
    }
    if (b->p30 != 0) {
        n = b->n64;
        if (n > 0) {
            a->p30 = (E10 *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x10 + 0x10, heap), ActInfoCallCtor_2311d0, 0, 0x10, n);
            if (a->p30 == 0) {
                return 0;
            }
            a->n64 = b->n64;
        }
    }
    if (b->p34 != 0) {
        n = b->n66;
        if (n > 0) {
            a->p34 = (E18 *)MemStackNew_14e1b0(n * 0x18, heap);
            if (a->p34 == 0) {
                return 0;
            }
            a->n66 = b->n66;
        }
    }
    if (b->p38 != 0) {
        n = b->n68;
        if (n > 0) {
            a->p38 = (E14 *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x14 + 0x10, heap), ActInfoClsnCtor_230c40, 0, 0x14, n);
            if (a->p38 == 0) {
                return 0;
            }
            a->n68 = b->n68;
        }
    }
    if (b->p3C != 0) {
        n = b->n6A;
        if (n > 0) {
            a->p3C = (E8 *)MemStackNew_14e1b0(n * 0x8, heap);
            if (a->p3C == 0) {
                return 0;
            }
            a->n6A = b->n6A;
        }
    }
    if (b->p40 != 0) {
        n = b->n6C;
        if (n > 0) {
            a->p40 = (E7C *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x7C + 0x10, heap), CharaEffEntryCtor_230850, 0, 0x7C, n);
            if (a->p40 == 0) {
                return 0;
            }
            a->n6C = b->n6C;
        }
    }
    if (b->p48 != 0) {
        n = b->n70;
        if (n > 0) {
            a->p48 = (EC *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 0xC + 0x10, heap), ActInfoWepActCtor_22f0d0, 0, 0xC, n);
            if (a->p48 == 0) {
                return 0;
            }
            a->n70 = b->n70;
        }
    }
    if (b->p44 != 0) {
        n = b->n6E;
        if (n > 0) {
            a->p44 = (EC *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 0xC + 0x10, heap), ActInfoEvntCtor_22f360, 0, 0xC, n);
            if (a->p44 == 0) {
                return 0;
            }
            a->n6E = b->n6E;
        }
    }
    if (b->p4C != 0) {
        n = b->n72;
        if (n > 0) {
            a->p4C = (EC *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 0xC + 0x10, heap), ActInfoAbltCtor_22ee20, 0, 0xC, n);
            if (a->p4C == 0) {
                return 0;
            }
            a->n72 = b->n72;
        }
    }
    if (b->p50 != 0) {
        n = b->n74;
        if (n > 0) {
            a->p50 = (E8 *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x8 + 0x10, heap), ActInfoAtkPrmCtor_22eb60, 0, 0x8, n);
            if (a->p50 == 0) {
                return 0;
            }
            a->n74 = b->n74;
        }
    }
    if (b->p54 != 0) {
        n = b->n76;
        if (n > 0) {
            a->p54 = (E18 *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x18 + 0x10, heap), ActInfoLocusCtor_22faa0, 0, 0x18, n);
            if (a->p54 == 0) {
                return 0;
            }
            a->n76 = b->n76;
        }
    }
    if (b->p58 != 0) {
        n = b->n78;
        if (n > 0) {
            a->p58 = (EC *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 0xC + 0x10, heap), CharaTableSubRecCtorMaybe_22ea20, 0, 0xC, n);
            if (a->p58 == 0) {
                return 0;
            }
            a->n78 = b->n78;
        }
    }
    for (i = 0; i < a->n5C; i++) {
        if (ActInfoNameClone_2314b0(&a->p20[i], &b->p20[i], heap, a->x1C) == 0) {
            return 0;
        }
    }
    for (i = 0; i < a->n5E; i++) {
        if (ActInfoMoveClone_231410(&a->p24[i], &b->p24[i], heap, a->x1C) == 0) {
            return 0;
        }
    }
    for (i = 0; i < a->n60; i++) {
        if (ActInfoNullClone_231330(&a->p28[i], &b->p28[i], heap, a->x1C) == 0) {
            return 0;
        }
    }
    for (i = 0; i < a->n62; i++) {
        if (ActInfoCmndClone_231220(&a->p2C[i], &b->p2C[i], heap, a->x1C) == 0) {
            return 0;
        }
    }
    for (i = 0; i < a->n64; i++) {
        if (ActInfoCallClone_2310e0(&a->p30[i], &b->p30[i], heap, a->x1C) == 0) {
            return 0;
        }
    }
    for (i = 0; i < a->n66; i++) {
        if (ActInfoVertClone_230e00(&a->p34[i], &b->p34[i], heap, a->x1C) == 0) {
            return 0;
        }
    }
    for (i = 0; i < a->n68; i++) {
        if (ActInfoClsnClone_2309b0(&a->p38[i], &b->p38[i], heap, a->x1C) == 0) {
            return 0;
        }
    }
    for (i = 0; i < a->n6A; i++) {
        if (ActInfoColPrmClone_230880(&a->p3C[i], &b->p3C[i], heap, a->x1C) == 0) {
            return 0;
        }
    }
    for (i = 0; i < a->n6C; i++) {
        if (CharaEffEntryClone_230260(&a->p40[i], &b->p40[i], heap, a->x1C) == 0) {
            return 0;
        }
    }
    for (i = 0; i < a->n6E; i++) {
        if (ActInfoEvntClone_22f1e0(&a->p44[i], &b->p44[i], heap, a->x1C) == 0) {
            return 0;
        }
    }
    for (i = 0; i < a->n70; i++) {
        if (ActInfoWepActClone_22ef20(&a->p48[i], &b->p48[i], heap, a->x1C) == 0) {
            return 0;
        }
    }
    for (i = 0; i < a->n72; i++) {
        if (ActInfoAbltClone_22ec60(&a->p4C[i], &b->p4C[i], heap, a->x1C) == 0) {
            return 0;
        }
    }
    for (i = 0; i < a->n74; i++) {
        if (ActInfoAtkPrmClone_22ea90(&a->p50[i], &b->p50[i], heap, a->x1C) == 0) {
            return 0;
        }
    }
    for (i = 0; i < a->n76; i++) {
        if (ActInfoLocusClone_22f890(&a->p54[i], &b->p54[i], heap, a->x1C) == 0) {
            return 0;
        }
    }
    for (i = 0; i < a->n78; i++) {
        if (CharaTableSubRecCloneMaybe_22e880(&a->p58[i], &b->p58[i], heap, a->x1C) == 0) {
            return 0;
        }
    }
    a->x14 = ((s32)StrPoolIntern_302fd0(a->x1C, b->x14, heap));
    if (a->x14 == 0) {
        return 0;
    }
    a->x18 = arg1;
    return 1;
}
