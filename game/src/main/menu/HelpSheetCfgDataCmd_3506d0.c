/* rgp:protos */
#define RGP_SELF_HelpSheetCfgDataCmd_3506d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 a;
    s16 b;
    s16 c;
    s16 d;
    s16 e;
    char name[0x40];
    char n2[0x20];
    char n3[0x10];
} Rec3506;

/*rgp*/
/*rgp*/
extern void *memset(void *, s32, u32);
extern char *strcpy(char *, const char *);
extern s32 D_00482E94;
extern Rec3506 *D_00482E9C;

s32 HelpSheetCfgDataCmd_3506d0(s64 *arg0)
{
    char *s;

    if (D_00482E9C != 0) {
        D_00482E9C[D_00482E94].a = VariantGetInt_15f780((s32)arg0++);
        D_00482E9C[D_00482E94].b = VariantGetInt_15f780((s32)arg0++);
        D_00482E9C[D_00482E94].c = VariantGetInt_15f780((s32)arg0++);
        D_00482E9C[D_00482E94].d = VariantGetInt_15f780((s32)arg0++);
        D_00482E9C[D_00482E94].e = VariantGetInt_15f780((s32)arg0++);
        memset(D_00482E9C[D_00482E94].name, 0, 0x40);
        memset(D_00482E9C[D_00482E94].name, 0, 0xC);
        if ((s = ((char *)SlotGetInt_15f720((s32)arg0++))) != 0) {
            strcpy(D_00482E9C[D_00482E94].name, s);
        }
        if ((s = ((char *)SlotGetInt_15f720((s32)arg0++))) != 0) {
            strcpy(D_00482E9C[D_00482E94].n2, s);
        }
        if ((s = ((char *)SlotGetInt_15f720((s32)arg0))) != 0) {
            strcpy(D_00482E9C[D_00482E94].n3, s);
        }
        D_00482E94++;
    }
    return 1;
}
