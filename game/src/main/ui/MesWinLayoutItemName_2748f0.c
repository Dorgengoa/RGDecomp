/* rgp:protos */
#define RGP_SELF_Check 1
#define RGP_SELF_Emit 1
#define RGP_SELF_MesWinLayoutItemName_2748f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3

typedef struct Vm {
    u8 pad0[0x193C];
    s32 m193C;
    u8 pad1940[0x1C20 - 0x1940];
    s16 m1C20;
    s16 m1C22;
} Vm;

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
extern s32 D_0045F200[];
extern s32 D_0045F208[];

static inline void Emit(Vm *vm, u32 code) {
    u16 k = code;
    MesWinPushChar_2743c0(vm, k);
    MesWinAddPenX_272ae0(vm, (s16)FontGetGaijiWidth_26f890(vm, k));
}

static inline s32 Check(Vm *vm, u32 code) {
    u16 k = code;
    MesWinPushChar_2743c0(vm, k);
    return FontIsAsciiCode_26ed80(vm, k);
}

s32 MesWinLayoutItemName_2748f0(Vm *vm, s32 id) {
    s32 h;
    u16 *pc;
    u16 c;
    s16 base;
    s16 last;
    s32 rel;
    s16 t;


    if (id < 0xFB00) {
        return 0;
    }
    if (id > 0xFBFF) {
        return 0;
    }
    h = MesWinGetItemSlot_2746e0(vm, MesItemCodeFindIndex_277260(id));
    if (h == 0) {
        return 0;
    }
    if (FontGetMesItemNameTable_270610(vm) == 0) {
        return 0;
    }
    pc = ((u16 *)MesItemNameLookup_274580(vm, h));
    if (pc == 0) {
        return 0;
    }
    rel = 0xFAF9 - id;
    base = D_0045F208[0] + 4;
    last = D_0045F200[0] - 1;
    for (;;) {
        c = *pc++;
        switch ((s32)c) {
        case 0xFF01:
            return 1;
        case 0xFF02:
            MesWinPushChar_2743c0(vm, c);
            if (vm->m1C22 >= 0 || vm->m1C20 >= 0) {
                MesWinAddPenX_272ae0(vm, vm->m1C20);
            } else {
                MesWinAddPenX_272ae0(vm, (u8)((unsigned char)TextStyleGetSpaceWidth_26f5d0(vm)));
            }
            break;
        case 0xFF00:
            MesWinPushChar_2743c0(vm, c);
            MesWinSetPenX_272af0(vm, 0);
            MesWinAddPenY_272ab0(vm, base);
            MesWinAddPenY_272ab0(vm, MesWinGetLineSpacing_2722e0(vm, vm->m193C));
            vm->m193C++;
            break;
        default:
            if (c >= 0xFAEA && c < 0xFAFA) {
                MesWinLayoutStrVar_274e60(vm, rel);
            } else if (c >= 0xFD00 && c < 0xFE00) {
                Emit(vm, c);
            } else if (c >= 0xF700 && c < 0xF800) {
                t = (c - 0xF700) * 4;
                vm->m1C22 = t;
                vm->m1C20 = TextCalcGapWidthMaybe_2741c0(vm, t, last, pc - 1);
            } else if (c >= 0xF800 && c < 0xF900) {
                vm->m1C20 = c - 0xF800;
            } else if (c >= 0xF900 && c < 0xFA00) {
                MesWinAddPenX_272ae0(vm, c - 0xF900);
            } else {
                if (Check(vm, c) != 0) {
                    MesWinAddPenX_272ae0(vm, (u8)((unsigned char)FontGetCharWidth_26f4c0(vm, c)));
                } else {
                    MesWinAddPenX_272ae0(vm, last);
                }
            }
            break;
        }
    }
}
