#include "types.h"

typedef struct {
    s32 a;
    s32 b;
} P8;

typedef struct {
    s16 v[5];
    char name[0x40];
} Ent;

extern s16 VariantGetInt_15f780(P8 *);
extern char *SlotGetInt_15f720(P8 *);
extern void memset(void *, s32, u32);
extern char *strcpy(char *, const char *);
extern Ent *D_004835AC;
extern s32 D_004835A4;

s32 InfoEdgeCfgData_39a100(P8 *p)
{
    char *s;

    if (D_004835AC != NULL) {
    D_004835AC[D_004835A4].v[0] = VariantGetInt_15f780(p++);
    D_004835AC[D_004835A4].v[1] = VariantGetInt_15f780(p++);
    D_004835AC[D_004835A4].v[2] = VariantGetInt_15f780(p++);
    D_004835AC[D_004835A4].v[3] = VariantGetInt_15f780(p++);
    D_004835AC[D_004835A4].v[4] = VariantGetInt_15f780(p++);
    memset(D_004835AC[D_004835A4].name, 0, 0x40);
    s = SlotGetInt_15f720(p);
    if (s != NULL) {
        strcpy(D_004835AC[D_004835A4].name, s);
    }
    D_004835A4++;
    }
    return 1;
}
