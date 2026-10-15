#include "types.h"

extern s32 CharaNormalTableGetCount_225810(void *);
extern s32 CharaNormalTableGetArray_225820(void *);
extern void CharaTableDataInit_226f80(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 ScriptArgGetStr_23fba0(s32);
extern s32 StrDupArena_23fc40(s32);
extern s32 D_00481EA0;
extern s32 D_00481EA4;
extern s32 D_00481EA8;
extern s32 D_00481EAC;
extern s32 D_00481EB0;
extern s32 D_00481EB4;
extern s32 D_00481EB8;
extern s32 D_00481EBC;
extern s32 D_00481EC0;
extern s32 D_00481EC4;
extern s32 D_00481EC8;
extern s32 D_00481ECC;
extern s32 D_00481ED0;
extern s32 D_00481ED4;
extern s32 D_00481ED8;
extern s32 D_00481EDC;
extern s32 D_00481F00;
extern u8 D_004BCDB0[];

s32 CharaNormalTableMtnNormalStart_23ccd0(s32 q, s32 n)
{
    s32 p;
    s32 i;

    D_00481F00 = 0;
    if (n <= 0) {
        return 0;
    }
    if ((CharaNormalTableGetArray_225820(D_004BCDB0) == 0) || (CharaNormalTableGetCount_225810(D_004BCDB0) >= 0x10)) return 1;
    {
        p = CharaNormalTableGetArray_225820(D_004BCDB0);
        p += CharaNormalTableGetCount_225810(D_004BCDB0) * 0x34;
        D_00481F00 = n;
        i = 0;
        while (i < D_00481F00) {
            CharaTableDataInit_226f80(p, StrDupArena_23fc40(ScriptArgGetStr_23fba0(q)), D_00481EA0 + D_00481EA4 * 8, 0,
                         D_00481EA8 + D_00481EAC * 0x10, 0, D_00481EB0 + D_00481EB4 * 0x20, 0,
                         D_00481EB8 + D_00481EBC * 0x10, 0, D_00481EC0 + D_00481EC4 * 0x14, 0,
                         D_00481EC8 + D_00481ECC * 0x10, 0, D_00481ED0 + D_00481ED4 * 0x14, 0,
                         D_00481ED8 + D_00481EDC * 0x14, 0);
            q += 8;
            i++;
            p += 0x34;
        }
    }
    return 1;
}
