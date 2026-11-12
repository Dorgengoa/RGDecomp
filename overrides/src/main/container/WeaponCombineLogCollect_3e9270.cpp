/* rg-override: replaces game/src/main/container/WeaponCombineLogCollect_3e9270.cpp sha256 f70059747b5d13de1595fb0c0838487ef4c374aae778071ca72ab43cb0557b4d
 * why: gameplay.frog_log_order (docs/SETTINGS.md "Frog Log order", lane froglog 2026-11-09): with
 * "sorted" the Frog Log rows are collected in rg_froglog_rank order (the item table's row order,
 * src/game/rg_froglog_tab.c), so the US-added 17xxx weapons sit with their tree instead of after
 * every original recipe.  Display only: the gama list (binary-searched by RecTableBinSearch_407bb0)
 * and the save log (WeaponCombineLogFind_3cbf10) are never reordered.  "original" (default) runs
 * the generated loop unchanged. */
/* rgp:protos */
#line 1
#include "types.h"
#pragma optimization_level 3
#pragma opt_propagation off
#pragma opt_repositioncode off
#pragma opt_common_subs off
#undef NULL
#define NULL 0
struct E6 {
    u8 x0;
    u8 x1;
    u8 x2;
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
    s16 x4;
};
struct H8 {
    u8 x0;
    u8 n;
    u8 pad[2];
    E6 *e;
};
extern "C" {
class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s32 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s32, int, int), 0x70, a0, rgp_fwd2, rgp_fwd3); }
};
s32 WeaponCombineLogFind_3cbf10(s32, s16, s32);
s32 WeaponCombineFillRowMaybe_3cd910(s32, s32, void *);
H8 *ListFindByKey_407ee0(s32, s32);

#define G90(a) (*(u8 **)(*(u8 **)((u8 *)(a) + 0x8) + 0x90))

int rg_froglog_sorted(void);       /* src/settings/rg_aspect.c: gameplay.frog_log_order */
int rg_froglog_rank(int item_id);  /* src/game/rg_froglog_tab.c (generated) */

/* sort key: item-table rank, then variant, then the entry's retail position (stable) */
static u32 froglog_key(E6 *e, s32 i) {
    return ((u32)rg_froglog_rank(e->x4) << 9) | ((e->b4 != 0) ? 0x100u : 0u) | (u32)i;
}

/* the generated loop below, over h->e in froglog_key order */
static s32 froglog_collect_sorted(void *arg0, H8 *h, s32 q) {
    u8 ord[256];
    u32 key;
    s32 n;
    s32 i;
    s32 j;
    s32 cnt;
    s32 r;
    E6 *e;

    n = h->n;
    for (i = 0; i < n; i++) {
        key = froglog_key(&h->e[i], i);
        for (j = i; j > 0 && froglog_key(&h->e[ord[j - 1]], ord[j - 1]) > key; j--) {
            ord[j] = ord[j - 1];
        }
        ord[j] = (u8)i;
    }
    cnt = 0;
    for (i = 0; i < n; i++) {
        e = &h->e[ord[i]];
        r = WeaponCombineLogFind_3cbf10(*(s32 *)((u8 *)arg0 + 0x10), e->x4, e->b4 != 0);
        if (r != 0) {
            WeaponCombineFillRowMaybe_3cd910(r, q, h);
            cnt++;
            q += 0x1C;
        }
    }
    *(u16 *)(G90(arg0) + 0x14) = cnt;
    return cnt;
}

s32 WeaponCombineLogCollect_3e9270(void *arg0, s16 arg1, s32 arg2, int rgp_a3) {
    s32 t;
    H8 *h;
    s32 cnt;
    s32 n;
    s32 q;
    E6 *e;
    s32 i;
    s32 r;
    s16 k;

    *(u16 *)(G90(arg0) + 0x14) = 0;
    t = (*(VC_0 **)(G90(arg0) + 0xC))->f(arg1, (int)(long)(arg2), (int)(long)(rgp_a3));
    if (t == 0) {
        return 0;
    }
    h = ListFindByKey_407ee0(t, arg2);
    if (h == NULL) {
        return 0;
    }
    cnt = 0;
    n = h->n;
    e = h->e;
    q = *(s32 *)(G90(arg0) + 0x18);
    if (rg_froglog_sorted()) {
        return froglog_collect_sorted(arg0, h, q);
    }
    for (i = 0; i < n; i++, e++) {
        k = e->x4;
        r = WeaponCombineLogFind_3cbf10(*(s32 *)((u8 *)arg0 + 0x10), k, e->b4 != 0);
        if (r != 0) {
            WeaponCombineFillRowMaybe_3cd910(r, q, h);
            cnt++;
            q += 0x1C;
        }
    }
    *(u16 *)(G90(arg0) + 0x14) = cnt;
    return cnt;
}
}
