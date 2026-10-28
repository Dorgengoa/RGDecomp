/* rgp:protos */
#define RGP_SELF_MenuCatalogItemGridFill_35d5e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off
#pragma opt_propagation off

typedef struct {
    u8 pad[0x1C];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
} Unk;

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
/*rgp*/
/*rgp*/

void MenuCatalogItemGridFill_35d5e0(s8 *arg0) {
    s32 it[2];
    s32 buf[8] __attribute__((aligned(16)));
    volatile s32 x;
    volatile s32 y;
    s8 *obj;
    s8 *hdr;
    s32 i;
    s32 lim;
    s8 *e;
    s32 base;
    s32 idx;
    s32 slot;
    s8 *fp;
    s32 id0;
    s32 id1;
    s32 x1;
    s32 y1;
    s32 s0v;
    s32 s6v;
    s32 m;
    u64 bits;
    s32 m1;
    s32 cx;
    s32 cy;

    obj = ((s8 *)GetGameData_1fede0());
    m1 = -1;
    InvViewCtorFromOwner_3cec70(buf, obj, 6, m1, m1, m1);
    IterInit_370170(it, buf, 0, 0);
    hdr = ((s8 *)UiEntryListFindByTag_28ea40(*(s32 *)(arg0 + 0x278), 0x24));
    i = 0;
    lim = *(s16 *)(hdr + 0x16) + *(s16 *)(hdr + 0x1A);
    do {
        UiSetSpriteSizeUvSize_28f670(*(volatile s32 *)(arg0 + 0x274), 0x1FA, 0, 0, 0, 0, i);
        UiSetSpriteSizeUvSize_28f670(*(volatile s32 *)(arg0 + 0x274), 0x1FB, 0, 0, 0, 0, i);
        UiSetSpriteSizeUvSize_28f670(*(volatile s32 *)(arg0 + 0x274), 0x201, 0, 0, 0, 0, i);
        UiSetSpriteSizeUvSize_28f670(*(volatile s32 *)(arg0 + 0x274), 0x202, 0, 0, 0, 0, i * 2);
        UiSetSpriteSizeUvSize_28f670(*(volatile s32 *)(arg0 + 0x274), 0x202, 0, 0, 0, 0, i * 2 + 1);
        i++;
    } while (i < 12);
    i = 0;
    do {
        UiSetSpriteSizeUvSize_28f670(*(volatile s32 *)(arg0 + 0x274), 0x24E, 0, 0, 0, 0, i);
        i++;
    } while (i < 4);
    if (*(s16 *)(hdr + 0x16) == 2) {
        lim -= 2;
    }
    while ((e = ((s8 *)IterNext_370040(it))) != NULL) {
        base = InvIdGetMinorIndex_3d5440(*(s16 *)(e + 6));
        idx = InvIdGetMidIndex_3d52b0(*(s16 *)(e + 6));
        if (idx < lim) continue;
        if (idx > lim + 2) continue;
        slot = base + (idx - lim) * 4;
        fp = ((s8 *)DataTableFindRowById_3fd770(*(s32 *)(*(s8 **)(*(s8 **)(obj + 8) + 0x94) + 0xC), *(s16 *)(*(s8 **)(e + 0x10) + 6)));
        UiSetSpriteSize_28fc30(*(volatile s32 *)(arg0 + 0x274), 0x1FA, 0x40, 0x32, slot);
        cx = 0x4C;
        cy = 0x54;
        UiSetSpriteSizeUvSize_28f670(*(volatile s32 *)(arg0 + 0x274), 0x201, cx, cy, cx, cy, slot);
        if (fp == NULL) continue;
        MenuCatalogItemIconUv_35ccf0(arg0, *(s16 *)(fp + 0xA), (s32 *)&x, (s32 *)&y);
        y1 = y;
        id0 = 0x1FA;
        x1 = x;
        id1 = 0x1FB;
        s0v = slot;
        s6v = slot;
        if (*(s16 *)(fp + 0xA) >= 20) {
            id0 = 0x24E;
            id1 = id0;
            s0v = (slot % 4) * 2;
            x1 += 0x40;
            s6v = s0v + 1;
        }
        UiSetSpriteUvRect_28f9d0(*(volatile s32 *)(arg0 + 0x274), id0, x, y, 0x40, 0x32, s0v);
        bits = *(u8 *)(fp + 0x1C);
        if (((bits << 0x3C) >> 0x3F) != 0) {
            UiSetSpriteUvRect_28f9d0(*(volatile s32 *)(arg0 + 0x274), id0, x, y, 0, 0, s0v);
            UiSetSpriteSize_28fc30(*(volatile s32 *)(arg0 + 0x274), id0, 0, 0, s0v);
            UiSetSpriteUvRect_28f9d0(*(volatile s32 *)(arg0 + 0x274), id1, x1, y1, 0x40, 0x32, s6v);
            UiSetSpriteSize_28fc30(*(volatile s32 *)(arg0 + 0x274), id1, 0x40, 0x32, s6v);
            cx = 0x56;
            cy = 0x30;
            UiSetSpriteSizeUvSize_28f670(*(volatile s32 *)(arg0 + 0x274), 0x202, cx, cy, cx, cy, slot * 2);
        } else if (((bits << 0x3D) >> 0x3F) != 0) {
            UiSetSpriteUvRect_28f9d0(*(volatile s32 *)(arg0 + 0x274), id0, x, y, 0, 0, s0v);
            UiSetSpriteSize_28fc30(*(volatile s32 *)(arg0 + 0x274), id0, 0, 0, s0v);
            UiSetSpriteUvRect_28f9d0(*(volatile s32 *)(arg0 + 0x274), id1, x1, y1, 0x40, 0x32, s6v);
            UiSetSpriteSize_28fc30(*(volatile s32 *)(arg0 + 0x274), id1, 0x40, 0x32, s6v);
            cx = 0x56;
            cy = 0x26;
            UiSetSpriteSizeUvSize_28f670(*(volatile s32 *)(arg0 + 0x274), 0x202, cx, cy, cx, cy, slot * 2 + 1);
        }
    }
}
