/* rgp:protos */
#define RGP_SELF_TreasureBoxPlaceFromMapRec_33b1e0 1
#define RGP_SELF_Zero 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec4 { f32 x, y, z, w; } Vec4;
typedef struct Mtx { f32 m[4][4]; } Mtx;

typedef struct Obj {
    Vec4 pos;       /* 0x00 */
    Vec4 rot;       /* 0x10 */
    s16 h20;        /* 0x20 */
    s16 h22;        /* 0x22 */
    s16 h24;        /* 0x24 */
    s16 h26;        /* 0x26 */
    s32 pad28;      /* 0x28 */
    s16 h2C;        /* 0x2C */
    s16 pad2E;
    s32 w30;        /* 0x30 */
    s16 h34;        /* 0x34 */
    s16 pad36;
    s32 w38;
    s32 w3C;
    s32 w40;
    s32 w44;
    s32 w48;
    s32 w4C;
    s32 w50;
    s32 w54;
    u8 pad58[0x10];
    u8 *src;        /* 0x68 */
    f32 f6C;        /* 0x6C */
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
    u8 b5 : 1;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern volatile f32 D_0047F610;
extern volatile f32 D_0047F614;
extern volatile f32 D_0047F618;
extern volatile f32 D_0047F61C;


static inline void Zero(void *dst, u32 n) {
    u8 *p = (u8 *)dst;
    if (p != NULL) {
        while (n != 0) {
            *p = 0;
            n--;
            p++;
        }
    }
}

s32 TreasureBoxPlaceFromMapRec_33b1e0(Obj *self, u8 *arg1) {
    Vec4 pos __attribute__((aligned(16)));
    u8 *info;
    s32 mgr;
    s32 node;
    u8 *d;
    Vec4 *pv;
    u8 *p;
    u32 n;
    s32 z;

    TreasureBoxReset_33b4c0(self);
    if (arg1 == NULL) return 0;
    if (*(s32 *)(arg1 + 4) == 0) return 0;
    info = *(u8 **)(arg1 + 0x3C);
    if (info == NULL) return 0;
    if (*(s16 **)info == NULL) return 0;
    if (((s32)GetGameData_1fede0()) == 0) return 0;
    mgr = ((s32)GetMapMgr_201a90());
    if (mgr == 0) return 0;
    self->src = arg1;
    self->h20 = **(s16 **)info;
    self->h22 = *(s16 *)self->src;
    self->h24 = *(s16 *)(info + 8);
    d = self->src;
    pv = (Vec4 *)(d + 0x14);
    pos.x = D_0047F610;
    pos.y = D_0047F614;
    pos.z = D_0047F618;
    pos.w = D_0047F61C;
    pos.x = pv->x;
    pos.y = pv->y;
    pos.z = pv->z;
    {
    Vec4 rot __attribute__((aligned(16))) = {0};
    Vec4 b __attribute__((aligned(16)));
    Vec4 a __attribute__((aligned(16)));
    Mtx m __attribute__((aligned(16)));
    Vec4 t __attribute__((aligned(16)));
    Vec4 r __attribute__((aligned(16)));
    rot.y = pv->w;
    node = ((s32)MapFindAreaSlotById_1e4cb0(mgr, self->h24));
    if (node != 0 && (*(u8 *)(info + 0xA) & 1)) {
        MapDataGetPosVec4_1e7740(node, &b);
        MapDataGetRotVec4_1e7720(node, &a);
        MatFromRotPos_1caf90(&m, &a, &b);
        MatMulPoint_1cb8e0(&t, &m, &pos);
        VecCopy_1cbe30(&pos, &t);
        VecCopy_1cbe30(&r, &rot);
        r.x = AngleWrap_1cbf30(rot.x + a.x);
        r.y = AngleWrap_1cbf30(rot.y + a.y);
        r.z = AngleWrap_1cbf30(rot.z + a.z);
        VecCopy_1cbe30(&rot, &r);
    }
    VecCopy_1cbe30(&self->pos, &pos);
    VecCopy_1cbe30(&self->rot, &rot);
    self->w30 = 0;
    self->h34 = -1;
    z = 0;
    self->w38 = 0;
    self->w3C = 0;
    self->w40 = 0;
    self->w44 = 0;
    self->w48 = 0;
    self->w4C = 0;
    self->w50 = 0;
    self->w54 = 0;
    self->f6C = -1.0f;
    self->b0 = z;
    self->b1 = z;
    self->b2 = z;
    self->b3 = z;
    self->b4 = z;
    self->b5 = z;
    self->h2C = 0;
    self->h26 = 0;
    return 1;
    }
}
