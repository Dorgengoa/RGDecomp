/* rgp:protos */
#define RGP_SELF_NpcTalkTextRequest_41de00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 pad8[8];
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 *unk1C;
    s32 unk20;
    s32 unk24;
} Obj;

typedef struct {
    s32 unk0;
    s32 *unk4;
} Sub;

typedef struct {
    u8 pad0[0x94];
    Sub *unk94;
} Ent;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 NpcTalkTextRequest_41de00(Obj *arg0, s32 arg1, s32 arg2)
{
    s32 buf[32] __attribute__((aligned(16)));
    s32 h;
    Ent *e;
    Sub *s;
    s32 a;
    s32 *b;
    s32 r;

    if (arg0->unk4 == 0) {
        return 0;
    }
    if (arg0->unk10 == 2) {
        return 0;
    }
    h = ((s32)GetLoaderMgr_1f59d0());
    if (h == 0) {
        return 0;
    }
    e = ((Ent *)GroupFindByKey_41e130(arg0, arg1));
    if (e == NULL) {
        return 0;
    }
    s = e->unk94;
    if (s == NULL) {
        return 0;
    }
    a = s->unk0;
    if (a == 0) {
        return 0;
    }
    b = s->unk4;
    if (b == NULL) {
        return 0;
    }
    r = StrCacheFind_3f01a0(arg0->unk4, 2, *b, arg2);
    if (r != 0) {
        arg0->unk18 = a;
        arg0->unk1C = b;
        arg0->unk20 = arg2;
        arg0->unk24 = r;
        arg0->unk10 = 3;
        return 1;
    }
    if (NpcTalkTextPacPath_41dff0(arg0, buf, a) == 0) {
        return 0;
    }
    arg0->unk14 = LoaderRequestFile_1cd870(h, buf, 0);
    if (arg0->unk14 < 0) {
        return 0;
    }
    LoaderQueueAppendSeparator_1cd670(h);
    arg0->unk10 = 2;
    arg0->unk18 = a;
    arg0->unk1C = b;
    arg0->unk20 = arg2;
    arg0->unk24 = 0;
    return 1;
}
