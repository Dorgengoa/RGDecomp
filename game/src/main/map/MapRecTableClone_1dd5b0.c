/* rgp:protos */
#define RGP_SELF_MapRecTableClone_1dd5b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"


typedef struct {
    u8 pad0[0x24];
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    u8 pad30[0x8];
    s16 unk38;
    s16 unk3A;
    s16 unk3C;
    s16 unk3E;
    u8 *unk40;
    u8 *unk44;
    u8 *unk48;
    u8 *unk4C;
} T1dd5b0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *memcpy(void *, const void *, u32);
/*rgp*/
/*rgp*/

s32 MapRecTableClone_1dd5b0(T1dd5b0 *arg0, s32 arg1)
{
    s32 n;
    u8 *p;
    s32 i;

    if (arg1 == 0) {
        return 0;
    }
    if (arg0->unk40 != 0) {
        n = arg0->unk38;
        if (n > 0) {
            p = ((u8 *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x58 + 0x10, arg1), MapShareCtor_1dd970, 0, 0x58, n));
            if (p == 0) {
                return 0;
            }
            MemStackNew_14e1b0(arg0->unk38 * 4, arg1);
            MemStackNew_14e1b0(arg0->unk38 * 4, arg1);
            memcpy(p, arg0->unk40, arg0->unk38 * 0x58);
            arg0->unk40 = p;
            for (i = 0; i < arg0->unk38; i++, p += 0x58) {
                if (MapShareClone_1ecfe0(p, arg1) == 0) {
                    return 0;
                }
            }
        }
    }
    if (arg0->unk44 != 0) {
        n = arg0->unk3A;
        if (n > 0) {
            p = ((u8 *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 0xCC + 0x10, arg1), MapBlockCtor_1dd920, 0, 0xCC, n));
            if (p == 0) {
                return 0;
            }
            MemStackNew_14e1b0(arg0->unk3A * 4, arg1);
            MemStackNew_14e1b0(arg0->unk3A * 4, arg1);
            memcpy(p, arg0->unk44, arg0->unk3A * 0xCC);
            arg0->unk44 = p;
            for (i = 0; i < arg0->unk3A; i++, p += 0xCC) {
                if (MapBlockClone_1df760(p, arg1) == 0) {
                    return 0;
                }
            }
        }
    }
    if (arg0->unk48 != 0) {
        n = arg0->unk3C;
        if (n > 0) {
            p = ((u8 *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x3C + 0x10, arg1), 0, 0, 0x3C, n));
            if (p == 0) {
                return 0;
            }
            memcpy(p, arg0->unk48, arg0->unk3C * 0x3C);
            arg0->unk48 = p;
            for (i = 0; i < arg0->unk3C; i++, p += 0x3C) {
                if (MapPartTableRemapBlocks_1de570(p, arg1, arg0->unk44, arg0->unk3A) == 0) {
                    return 0;
                }
            }
        }
    }
    if (arg0->unk4C != 0) {
        n = arg0->unk3E;
        if (n > 0) {
            p = ((u8 *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x50 + 0x10, arg1), 0, 0, 0x50, n));
            if (p == 0) {
                return 0;
            }
            memcpy(p, arg0->unk4C, arg0->unk3E * 0x50);
            arg0->unk4C = p;
        }
    }
    arg0->unk24 = ((s32)MemStackStrDup_14cff0(arg0->unk24, arg1));
    arg0->unk28 = ((s32)MemStackStrDup_14cff0(arg0->unk28, arg1));
    arg0->unk2C = ((s32)MemStackStrDup_14cff0(arg0->unk2C, arg1));
    return 1;
}
