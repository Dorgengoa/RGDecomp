#include "types.h"

typedef struct {
    s8 name[8];
    s8 *s;
    s32 u9C;
    s8 *np;
    s32 uA4;
    s32 uA8;
    s32 uAC;
} Req1AEFF0;

extern void OperatorDeleteArray_100820(s8 *);
extern s8 *OperatorNewArray_100900(s32);
extern s8 *SlotGetInt_15f720(s32);
extern s32 ArchiveGetFileData_181dd0(s32, s8 *, s32 *);
extern void ModelObjExAddEffDef_1afd40(s32, s32, Req1AEFF0 *);
extern void strcpy(s8 *, void *);
extern s32 strlen(void *);
extern u8 D_0045A818[0x400];
extern u8 D_0049D450[0x400];
extern u8 D_0049D45C[0x400];
extern u8 D_0049D4E0[0x400];
extern u8 D_0049D4E4[0x400];

s32 ParamScriptEffectCmd_1aeff0(s32 arg0, s32 arg1)
{
    Req1AEFF0 r;
    s32 spBC;
    s32 a;
    s32 b;
    s32 i;
    s8 *str;
    s32 k;
    s8 *buf;
    s8 *dot;
    s8 *p;
    s8 c;
    s32 c2;

    a = *(s32 *)D_0049D4E0;
    c2 = *(s32 *)D_0049D45C;
    if (a == 0 || c2 == 0) {
        return 0;
    }
    b = *(s32 *)D_0049D450;
    for (i = 0; i < arg1; i++) {
        str = SlotGetInt_15f720(arg0 + i * 8);
        k = ArchiveGetFileData_181dd0(b, str, &spBC);
        if (k != 0) {
            buf = OperatorNewArray_100900(strlen(str) + 1);
            if (buf != NULL) {
                strcpy(buf, str);
                dot = NULL;
                for (p = buf; (c = *p) != 0; p++) {
                    if (c == '.') {
                        dot = p;
                    }
                }
                if (dot != NULL) {
                    *dot = 0;
                }
                r.s = NULL;
                r.u9C = 0;
                r.uA4 = 0;
                strcpy(r.name, D_0045A818);
                r.np = r.name;
                r.s = buf;
                r.uA4 = *(s32 *)D_0049D45C;
                r.uAC = *(s32 *)D_0049D45C;
                r.uA8 = *(s32 *)D_0049D4E4;
                ModelObjExAddEffDef_1afd40(a, k, &r);
                OperatorDeleteArray_100820(buf);
            }
        }
    }
    return 1;
}
