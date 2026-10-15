#include "types.h"

typedef struct Tok {
    s32 a;
    s32 b;
} Tok;

extern void *D_00483FE0;
extern void *D_00483FEC;
extern s16 D_00484004;

extern s32 VariantGetInt_15f780(Tok *p);
extern void *ResGroupListAppendNew_42c400(void *ctx, s32 a, s32 b);
extern u8 *ResGroupListCurElem_42a5a0(void);

s32 ResGroupCmdListDefine_42a650(Tok *p)
{
    void *obj;
    s32 a;
    s32 count;
    s32 i;
    u8 *e;

    D_00484004 = -1;
    D_00483FEC = 0;
    a = VariantGetInt_15f780(p++);
    count = VariantGetInt_15f780(p++);
    obj = ResGroupListAppendNew_42c400(D_00483FE0, a, count);
    D_00483FEC = obj;
    D_00484004 = 0;
    if (obj == 0) {
        return 1;
    }
    for (i = 0; i < count; i++) {
        e = ResGroupListCurElem_42a5a0();
        if (e == 0) {
            return 1;
        }
        *(s16 *)(e + 0x00) = 0;
        *(s16 *)(e + 0x02) = 0;
        *(s16 *)(e + 0x04) = 14;
        *(s16 *)(e + 0x06) = 22;
        *(s16 *)(e + 0x08) = 0;
        *(s16 *)(e + 0x0A) = 0;
        *(s16 *)(e + 0x0C) = 14;
        *(s16 *)(e + 0x0E) = 22;
        *(s32 *)(e + 0x10) = 0;
        *(s32 *)(e + 0x14) = 0;
        *(s16 *)(e + 0x18) = -1;
        *(s16 *)(e + 0x1A) = -1;
        D_00484004 = D_00484004 + 1;
    }
    return 1;
}
