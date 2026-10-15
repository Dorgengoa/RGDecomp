#include "types.h"

extern s32 ConstructNewArray_100710(s32, void *, s32, s32, s32);
extern s32 MemStackNew_14e1b0(s32, s32);
extern s32 CharaRefGetCompCount_3121a0(s32);
extern s32 CharaRefGetCompLists_3121b0(s32);
extern s16 CharaRefGetId_3121c0(s32);
extern void CharaRefReset_312390(void);
extern s32 NamedCompListClone_3124c0(s32, s32, s32);

s32 CharaRefClone_3121e0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s16 n;
    s32 r;
    s32 d;
    s32 s;
    s32 i;

    CharaRefReset_312390();
    if (arg1 == 0 || arg2 == 0 || arg3 == 0) {
        return 0;
    }
    if (CharaRefGetCompLists_3121b0(arg2) != 0) {
        n = CharaRefGetCompCount_3121a0(arg2);
        *(s16 *)(arg0 + 0x8) = n;
        r = ConstructNewArray_100710(MemStackNew_14e1b0(n * 0xC + 0x10, arg3), 0, 0, 0xC, n);
        *(s32 *)(arg0 + 0x4) = r;
        if (r == 0) {
            return 0;
        }
        d = r;
        s = CharaRefGetCompLists_3121b0(arg2);
        for (i = 0; i < *(s16 *)(arg0 + 0x8);) {
            if (NamedCompListClone_3124c0(d, s, arg3) == 0) {
                return 0;
            }
            i++;
            d += 0xC;
            s += 0xC;
        }
    }
    *(s32 *)(arg0 + 0x0) = arg1;
    *(s16 *)(arg0 + 0xA) = CharaRefGetId_3121c0(arg2);
    return 1;
}
