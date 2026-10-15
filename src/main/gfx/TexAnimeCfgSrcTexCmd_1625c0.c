#include "types.h"
typedef struct { s32 a, b; } E8_1625c0;
struct H1625c0 { s16 m00; };
extern s32 SlotGetInt_15f720(E8_1625c0 *);
extern s32 VariantGetInt_15f780(E8_1625c0 *);
extern s32 NameTableFindByName_159fb0(s32, s32, s32);
extern s32 D_00481138;
extern s32 D_00481148;
extern struct { struct H1625c0 *v; s32 pad[3]; } D_00495E74;
extern struct { s16 v; s16 pad[7]; } D_00495E7C;
extern struct { s16 v; s16 pad[7]; } D_00495E7E;
extern struct { s16 v; s16 pad[7]; } D_00495E80;
extern struct { s16 v; s16 pad[7]; } D_00495E82;

s32 TexAnimeCfgSrcTexCmd_1625c0(E8_1625c0 *p0)
{
    s32 r;
    struct H1625c0 *h;

    r = SlotGetInt_15f720(p0++);
    if (r == 0) {
        return 0;
    }
    D_00495E74.v = (struct H1625c0 *)NameTableFindByName_159fb0(D_00481138, r, -1);
    D_00495E7C.v = VariantGetInt_15f780(p0++) << 4;
    D_00495E7E.v = VariantGetInt_15f780(p0++) << 4;
    D_00495E80.v = VariantGetInt_15f780(p0++) << 4;
    D_00495E82.v = VariantGetInt_15f780(p0) << 4;
    h = D_00495E74.v;
    if (h == 0) {
        goto out;
    }
    if (D_00481148 < 0) {
        D_00481148 = h->m00;
    }
out:
    return 1;
}
