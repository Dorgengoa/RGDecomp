/* rgp:protos */
#define RGP_SELF_ResGroupCmdGlyphListDefine_42a770 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Tok {
    s32 a;
    s32 b;
} Tok;

extern void *D_00483FE0;
extern void *D_00483FEC;
extern s16 D_00484004;

/*rgp*/
/*rgp*/
extern s32 strlen(const char *s);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ResGroupCmdGlyphListDefine_42a770(Tok *p)
{
    char *s;
    s32 a;
    s32 count;
    s32 i;
    void *obj;
    u8 *e;

    D_00484004 = -1;
    D_00483FEC = 0;
    a = VariantGetInt_15f780(p++);
    s = ((char *)SlotGetInt_15f720(p++));
    count = strlen(s);
    obj = ResGroupListAppendNew_42c400(D_00483FE0, a, count);
    D_00483FEC = obj;
    D_00484004 = 0;
    if (obj == 0) {
        return 1;
    }
    for (i = 0; i < count; i++) {
        e = ((u8 *)ResGroupListCurElem_42a5a0());
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
    UiLayoutStringGlyphs_28a800(ResGroupListGetElem_42a140(D_00483FEC, 0), s, 0, 0, -2);
    return 1;
}
