/* rgp:protos */
#define RGP_SELF_EntryScriptCmdWriteCells_3228f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EntryScriptCmdWriteCells_3228f0(s64 *arg0) {
    s32 w;
    s32 hh;
    s32 n;
    s32 m;
    u8 *obj;
    u8 *map;
    u8 *q;
    s32 i;
    s32 x;
    s32 y;
    s32 h;
    s32 a;
    s32 b;
    s32 c;

    obj = ((u8 *)GetEntryTableGlobal_32c2e0());
    if (obj == NULL) return 0;
    map = ((u8 *)EntryTableGetCurrent_323530(obj));
    if (map == NULL) return 0;
    switch (*(s32 *)(obj + 0x10)) {
    case 0:
        EntryGetGridSize_323bb0(map, &n, &m);
        for (i = 0; i < n; i++) {
            a = VariantGetInt_15f780((s32)arg0++);
            b = VariantGetInt_15f780((s32)arg0++);
            q = ((u8 *)EntryGridGetCell_323a60(map, ((short)EntryListGetCellCursor_323370(obj))));
            q[0] = a;
            q[1] = b;
            q[2] = 0;
            EntryListStepCellCursor_323360(obj);
        }
        break;
    case 1:
        x = *(s16 *)(obj + 0x24);
        y = *(s16 *)(obj + 0x26);
        h = *(s16 *)(obj + 0x28);
        EntryGetGridSize_323bb0(map, &w, &hh);
        x *= *(s16 *)(obj + 0x30);
        y = y * *(s16 *)(obj + 0x30) - -*(s16 *)(obj + 0x2E);
        for (i = 0; i < h; i++) {
            a = VariantGetInt_15f780((s32)arg0++);
            b = VariantGetInt_15f780((s32)arg0++);
            q = ((u8 *)EntryGridGetCell_323a60(map, x + i + w * y));
            q[0] = a;
            q[1] = b;
            q[2] = 0;
        }
        (*(s16 *)(obj + 0x2E))++;
        break;
    case 2:
        x = *(s16 *)(obj + 0x24);
        y = *(s16 *)(obj + 0x26);
        h = *(s16 *)(obj + 0x28);
        EntryGetGridSize_323bb0(map, &w, &hh);
        x *= *(s16 *)(obj + 0x30);
        y = y * *(s16 *)(obj + 0x30) - -*(s16 *)(obj + 0x2E);
        for (i = 0; i < h; i++) {
            a = VariantGetInt_15f780((s32)arg0++);
            b = VariantGetInt_15f780((s32)arg0++);
            c = VariantGetInt_15f780((s32)arg0++);
            q = ((u8 *)EntryGridGetCell_323a60(map, x + i + w * y));
            q[0] = a;
            q[1] = b;
            q[2] = c;
        }
        (*(s16 *)(obj + 0x2E))++;
        break;
    case 3:
        x = *(s16 *)(obj + 0x24);
        y = *(s16 *)(obj + 0x26);
        h = *(s16 *)(obj + 0x28);
        EntryGetGridSize_323bb0(map, &w, &hh);
        x *= *(s16 *)(obj + 0x30);
        y = y * *(s16 *)(obj + 0x30) - -*(s16 *)(obj + 0x2E);
        for (i = 0; i < h; i++) {
            a = VariantGetInt_15f780((s32)arg0++);
            b = VariantGetInt_15f780((s32)arg0++);
            c = VariantGetInt_15f780((s32)arg0++);
            q = ((u8 *)EntryGridGetCell_323a60(map, x + i + w * y));
            q[0] = a;
            q[1] = b;
            q[2] = c;
        }
        (*(s16 *)(obj + 0x2E))++;
        break;
    }
    return 1;
}
