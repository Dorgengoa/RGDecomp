#include "types.h"
#pragma opt_propagation off

typedef struct {
    s16 hdr;
    s16 type[2];
    s16 val[2];
} Req;

extern void *GetGameData_1fede0(void);
extern s16 ScriptSlotGetInt_2cc9c0(s32);
extern s32 CharaMgrPoolFindById_3a8c60(s32, s32);
extern s32 CharaFindSlotByRecId_3ad390(s32, s32);
extern void func_4EFC50(void *, Req *);
extern s32 D_004DB928[4];
extern u8 D_00527020[];

s32 AiCmdFieldHudAllySuggest_2cab80(s64 *arg0, s32 arg1)
{
    u8 *dst;
    Req r;
    s32 i;
    s16 *t;
    s32 j;
    s32 o;

    if (arg1 < 3) {
        return 0;
    }
    dst = D_00527020;
    r.hdr = ScriptSlotGetInt_2cc9c0((s32)arg0++);
    r.type[0] = ScriptSlotGetInt_2cc9c0((s32)arg0++);
    r.val[0] = ScriptSlotGetInt_2cc9c0((s32)arg0++);
    if (arg1 >= 5) {
        r.type[1] = ScriptSlotGetInt_2cc9c0((s32)arg0++);
        r.val[1] = ScriptSlotGetInt_2cc9c0((s32)arg0++);
    } else {
        r.type[1] = -1;
        r.val[1] = -1;
    }
    if ((o = CharaMgrPoolFindById_3a8c60(*(s32 *)((u8 *)GetGameData_1fede0() + 0x14), D_004DB928[0])) != 0) {
        i = 0;
        do {
            t = &r.type[i];
            if (*t == 1) {
                j = 0;
                while (j < 3) {
                    if (CharaFindSlotByRecId_3ad390(o, r.val[i] + j) != 0) {
                        {
                            s32 k_ = i;
                            Req *rp = (Req *)((s16 *)&r + k_);
                            rp->val[0] = rp->val[0] + j;
                        }
                        break;
                    }
                    j++;
                }
                if (j == 3) {
                    {
                        s32 k_ = i;
                        Req *rp = (Req *)((s16 *)&r + k_);
                        *t = -1;
                        rp->val[0] = -1;
                    }
                }
            }
            i++;
        } while (i < 2);
    }
    if (r.type[0] == -1) {
        r.type[0] = r.type[1];
        r.val[0] = r.val[1];
        r.type[1] = -1;
        r.val[1] = -1;
    }
    if (r.type[0] != -1) {
        func_4EFC50(dst, &r);
    }
    return 1;
}
