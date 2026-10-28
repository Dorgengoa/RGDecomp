/* rgp:protos */
#line 1
#pragma opt_propagation off
#include "types.h"

class Cam {
public:
    u8 pad0[0x40];
    s32 m40;
    s32 m44;
    u8 pad48[4];
    VC_VPTR_MEMBER;
    s32 Check(s32 a0) { return VCM(s32, (void *, s32), 0xC, a0); }
};

extern "C" {
extern char * SlotGetInt_15f720(void *);
extern s32 VariantGetInt_15f780(s32);
extern u8 *ListNodeGetData_18a370(s32);
extern Cam *FuncDataTableNewEntry_190db0(u8 *, s32, s32);
extern s32 strcmp(const char *, const char *);
extern char D_00459C58[];
extern char D_00459C60[];
extern char D_00459C68[];
extern char D_00459CA8[];
extern char D_00459CB0[];
extern char D_00459CB8[];
extern char D_00459CC0[];
extern char D_00459CC8[];
extern char D_00459CD0[];
extern char D_00459CD8[];
extern char D_00459CE0[];
extern char D_00459CF0[];
extern u8 *D_00481250;
extern s32 D_00481254;
extern s32 D_0048125C;
extern Cam *D_004812D8;
extern Cam *D_004812DC;
extern s32 D_004812E4;
}

extern "C" s32 MapCfgFuncData_18b0a0(s32 arg0)
{ __typeof__(arg0) rgp_entry_arg0 = arg0;
    char *s;
    s32 k;
    u8 *x;

    arg0 += 8;
    D_004812DC = 0;
    D_004812D8 = 0;
    s = SlotGetInt_15f720((void *)rgp_entry_arg0);
    if (s == 0) {
        return 0;
    }
    if (strcmp(s, D_00459CA8) == 0) {
        k = 1;
    } else if (strcmp(s, D_00459CB0) == 0) {
        k = 2;
    } else if (strcmp(s, D_00459CB8) == 0) {
        k = 3;
    } else if (strcmp(s, D_00459CC0) == 0) {
        k = 4;
    } else if (strcmp(s, D_00459CC8) == 0) {
        k = 5;
    } else if (strcmp(s, D_00459C58) == 0) {
        k = 7;
    } else if (strcmp(s, D_00459C60) == 0) {
        *(s32 *)(D_00481250 + 0x1660) = 1;
        k = 6;
    } else if (strcmp(s, D_00459CD0) == 0) {
        k = 8;
    } else if (strcmp(s, D_00459C68) == 0) {
        k = 9;
    } else if (strcmp(s, D_00459CD8) == 0) {
        k = 0xB;
    } else if (strcmp(s, D_00459CE0) == 0) {
        k = 0xC;
    } else if (strcmp(s, D_00459CF0) == 0) {
        k = 0xA;
    } else {
        return 0;
    }
    if (D_004812E4 != 0) {
        if (D_00481254 == 0) {
            return 0;
        }
        x = ListNodeGetData_18a370(D_00481254);
        if (x != 0) {
            D_004812D8 = FuncDataTableNewEntry_190db0(x + 0x114, k, D_0048125C);
            if (D_004812D8 != 0) {
                if (D_004812D8->Check(0x271B) != 0) {
                    D_004812DC = D_004812D8;
                } else {
                    D_004812DC = 0;
                }
            } else {
                goto clr;
            }
        } else {
        clr:
            D_004812DC = 0;
        }
    } else {
        D_004812D8 = FuncDataTableNewEntry_190db0(D_00481250 + 0x1664, k, D_0048125C);
        if (D_004812D8 != 0 && D_004812D8->Check(0x271B) != 0) {
            D_004812DC = D_004812D8;
        } else {
            D_004812DC = 0;
        }
    }
    if (D_004812D8 == 0) {
        return 0;
    }
    D_004812D8->m40 = k;
    D_004812D8->m44 = VariantGetInt_15f780(arg0);
    return 1;
}
