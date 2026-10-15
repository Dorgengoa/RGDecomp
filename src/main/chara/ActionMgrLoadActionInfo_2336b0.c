#pragma optimization_level 3
#include "types.h"
#pragma opt_common_subs off

extern void MemStackInit_14d810(void *, s32, s32);
extern void MemStackHeapFree_14dcb0(s32, s32);
extern s32 MemStackHeapAllocBack_14dcf0(s32, s32);
extern void MemStackClear_14dff0(void *);
extern void MemStackCtor_14e030(void *);
extern s32 CharaGetActScopeId_214a70(s32);
extern s32 CharaGetId_214a80(s32);
extern void CharaActInfoClear_214c30(s32);
extern s32 CharaLoadActInfo_214c50(s32, s32, s32, void *);
extern s32 CharaGetActInfoBlock_214cc0(s32);
extern s32 CharaActInfoCalcSize_2157e0(void *, s32);
extern void CharaActInfoReset_2158b0(void *);
extern s32 ActCfgTableGetScopeId_223d00(s32);
extern s32 IntCompare_42ca30(s32, s32);
extern s32 DListGetHead_42ea60(void *);
extern s32 DListGetCountPow2_42ea70(void *);
extern s32 DListNodeAdvance_42eb00(s32, s32);
extern void strcpy(void *, void *);
extern u32 strlen(void *);

extern u8 D_0045D700[0x400];

void ActionMgrLoadActionInfo_2336b0(void *arg0, s32 arg1) {
    s32 lo;
    s32 res;
    s32 n;
    s32 node;
    s32 c;
    s32 key;
    s32 res2;
    s32 sz;
    s32 h;
    s32 lo2;
    s32 n2;
    s32 v;
    s32 c2;
    s32 node2;
    u8 spE0[0x10];
    u8 sp80[0x60];

    if (*(s32 *)((u8 *)arg0 + 0x3C) == 0) {
        return;
    }
    lo = DListGetHead_42ea60((u8 *)arg0 + 0x20);
    if (lo == 0) {
        res = 0;
    } else {
        res = 0;
        n = DListGetCountPow2_42ea70((u8 *)arg0 + 0x20);
        while (n > 0) {
            n >>= 1;
            node = DListNodeAdvance_42eb00(lo, n);
            if (node != 0) {
                c = IntCompare_42ca30(arg1, CharaGetId_214a80(node + 0x10));
                if (c == 0) {
                    res = node;
                    break;
                }
                if (c > 0) {
                    lo = node;
                }
            }
        }
    }
    if (res == 0) res = 0; else res += 0x10;
    if (res == 0) {
        return;
    }
    if (CharaGetActInfoBlock_214cc0(res) != 0) {
        MemStackHeapFree_14dcb0(*(s32 *)((u8 *)arg0 + 0x3C), CharaGetActInfoBlock_214cc0(res));
        CharaActInfoClear_214c30(res);
    }
    key = CharaGetActScopeId_214a70(res);
    lo2 = DListGetHead_42ea60((u8 *)arg0 + 0x10);
    if (lo2 == 0) {
        res2 = 0;
    } else {
        res2 = 0;
        n2 = DListGetCountPow2_42ea70((u8 *)arg0 + 0x10);
        while (n2 > 0) {
            n2 >>= 1;
            node2 = DListNodeAdvance_42eb00(lo2, n2);
            if (node2 != 0) {
                c2 = IntCompare_42ca30(key, ActCfgTableGetScopeId_223d00(node2 + 0x10));
                if (c2 == 0) {
                    res2 = node2;
                    break;
                }
                if (c2 > 0) {
                    lo2 = node2;
                }
            }
        }
    }
    if (res2 == 0) v = 0; else v = res2 + 0x10;
    if (v == 0) {
        return;
    }
    CharaActInfoReset_2158b0(spE0);
    sz = CharaActInfoCalcSize_2157e0(spE0, v);
    h = MemStackHeapAllocBack_14dcf0(*(s32 *)((u8 *)arg0 + 0x3C), sz);
    if (h == 0) return;
    MemStackCtor_14e030(sp80);
    MemStackClear_14dff0(sp80);
    MemStackInit_14d810(sp80, h, sz);
    if (strlen(D_0045D700) < 0x10U) {
        strcpy(sp80, D_0045D700);
    }
    if (!(CharaLoadActInfo_214c50(res, h, v, sp80) & 0xFF)) {
        MemStackHeapFree_14dcb0(*(s32 *)((u8 *)arg0 + 0x3C), h);
        CharaActInfoClear_214c30(res);
    }
}
