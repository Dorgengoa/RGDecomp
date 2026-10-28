/* rgp:protos */
#define RGP_SELF_InsectPlaceAtRandomSpotMaybe_38acf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
//PRAGMA

typedef rg_u128 u128;

typedef union {
    u128 q;
    struct {
        f32 x;
        f32 y;
        f32 z;
        f32 w;
    } f;
} Vec4;

typedef struct {
    Vec4 pos;
    u8 pad10[8];
    s32 id;
    u8 pad1C[4];
} Spot;

typedef struct {
    f32 x;
    f32 z;
} Pair;

typedef struct {
    u8 pad0[0x984];
    s8 unk984;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_004832B8;
extern Pair D_004540F0[];
extern f32 D_0047D354;
extern f32 D_0047D40C;
extern f32 D_0047D430;
extern f32 D_0047D434;
extern f32 D_0047FC18[2];

void InsectPlaceAtRandomSpotMaybe_38acf0(Obj *self, Spot *outSpot, Spot *list, s32 n)
{
    //DECLS
    s32 tries;
    s32 ok;
    s32 i;
    Spot sp __attribute__((aligned(16)));
    Vec4 pos __attribute__((aligned(16)));
    Vec4 rot __attribute__((aligned(16)));
    //ENDDECLS

    if (self == NULL) {
        return;
    }
    PlacePointInit_3869f0(&sp);
    tries = 0x40;
    do {
        PlacePointInit_3869f0(&sp);
        PlacePointPickRandom_386310(&D_004832B8, &sp, self->unk984);
        if (list == NULL) {
            break;
        }
        ok = 1;
        for (i = 0; i < n; i++) {
            if (sp.id == list[i].id) {
                ok = 0;
            }
        }
        if (ok) {
            break;
        }
    } while (--tries > 0);
    if (outSpot != NULL) {
        Copy20Bytes_3869c0(outSpot, &sp);
    }
    if (tries > 0) {
        pos.q = sp.pos.q;
    } else {
        if (n < 0) {
            n = (s32)(4.0f * RandFloat_13c010());
        }
        pos.f.x = D_004540F0[n].x + D_0047D354 * (1.0f - RandFloat_13c010());
        pos.f.z = D_0047D430 + (D_004540F0[n].z + D_0047D354 * (1.0f - RandFloat_13c010()));
        pos.f.y = D_0047FC18[((signed char)InsectCageGetType_3910c0())];
        if (self->unk984 != 0) {
            pos.f.y = pos.f.y + 4.0f * (D_0047D40C + RandFloat_13c010());
        }
    }
    pos.f.w = 1.0f;
    rot.q = 0;
    rot.f.y = WrapAngle_13c050(D_0047D434 * RandFloat_13c010());
    ModelSetPos_151110(self, &pos);
    ModelSetRot_151080(self, &rot);
}
