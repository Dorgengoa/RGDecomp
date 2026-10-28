/* rgp:protos */
#define RGP_SELF_MapLinkedAreaGetYMaybe_3f09a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 a;
    f32 b;
    s32 c;
    s32 d;
} R;

typedef struct {
    s16 unk0;
    u8 pad2[0xE];
    s16 *unk10;
} Node;

typedef struct {
    Node *unk0;
    u8 pad4[4];
    s16 unk8;
} Inner;

typedef struct {
    u8 pad0[0x18];
    Inner *unk18;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

f32 MapLinkedAreaGetYMaybe_3f09a0(Obj *arg0, s32 arg1)
{
R r;
Node *n;
Inner *t;
s16 id;
s32 w;
s16 *v;
s32 x,y;
    if (arg1 == 0) {
        return 0.0f;
    }
    t = arg0->unk18;
    id=t->unk8;
    n=t->unk0;
    if (n == NULL) {
        return 0.0f;
    }
    v = n->unk10;
    if (v == NULL) {
        return 0.0f;
    }
    if (*v != 10) {
        return 0.0f;
    }
    w = ((s32)GetMapMgr_201a90());
    if (w == 0) {
        return 0.0f;
    }
    x = ((s32)MapFindAreaSlotById_1e4cb0(w, id));
    if (x == 0) {
        return 0.0f;
    }
    y = MapSlotsFindBlockById_1e49b0(w, MapAreaFindBlockNoByLocationId_1dcce0(x, n->unk0) + 0x4E20, 0);
    if (y == 0) {
        return 0.0f;
    }
    MapDataGetPosVec4_1e7740(y, &r);
    return r.b;
}
