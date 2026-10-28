/* rgp:protos */
#define RGP_SELF_EffectEntryLoadPoll_2deba0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct Ent { u8 b[0xE0]; } Ent;

typedef struct Q {
    s16 type;
    s16 id;
    s16 pad[3];
    s16 b[2];
    s16 a[2];
} Q;

typedef struct Msg {
    s16 type;
    s32 id;
    s32 z;
    s32 pad;
} Msg;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004B2570[];

s32 EffectEntryLoadPoll_2deba0(u8 *base) {
    Q *volatile q; Msg m0; Msg m1; Msg m2; Msg m3; u8 cnt; s32 r1; s32 h; s32 i; u8 *e; u8 *e2; s32 r2; s32 r3; s32 r4; u8 *e3; s32 j;

    h = ((s32)GetLoaderMgr_1f59d0());
    if (h == 0) {
        return 1;
    }
    for (i = 0; i < 0x30; i++) {
        e = base + i * 0xE0;
        q = (Q *)(e + 0xC);
        cnt = 0;
        if (q->id == -1) continue;
        if (*(s16 *)(e + 0xB4) == 3) continue;
        switch (q->type) {
        case 0:
            for (j = 0; j < 2; j++) {
                if (q->a[j] != -1 && q->b[j] != 1) {
                    q->b[j] = LoaderGetStatus_1cd4f0(h, q->a[j]);
                }
                if (q->b[j] == 1) {
                    cnt++;
                } else if (q->b[j] == -1) {
                    LoaderReleaseById_1cd340(h, q->a[0]);
                    LoaderReleaseById_1cd340(h, q->a[1]);
                    m0.z = 0;
                    m0.type = 2;
                    m0.id = q->id;
                    EffectEntryReleaseByIdx_2de320(base, &m0);
                } else if (q->b[j] == 0) {
                    PadIsHeld_183a20(D_004B2570, 0x1000);
                }
            }
            if (cnt == 2) {
                e2 = base + (u32)i * 0xE0;
                r1 = EffectEntryFinishChr_2dc4d0(e2, i);
                r2 = EffectEntryFinishScript_2dc0a0(e2);
                LoaderReleaseById_1cd340(h, q->a[0]);
                LoaderReleaseById_1cd340(h, q->a[1]);
                if (r1 != 0 || r2 != 0) {
                    m1.z = 0;
                    m1.type = 2;
                    m1.id = q->id;
                    EffectEntryReleaseByIdx_2de320(base, &m1);
                } else {
                    EffectEntryMeasureHeap_2dba80(e);
                    q->a[0] = -1;
                    q->a[1] = -1;
                }
            }
            break;
        case 1:
            for (j = 0; j < 2; j++) {
                if (q->a[j] != -1) {
                    q->b[j] = LoaderGetStatus_1cd4f0(h, q->a[j]);
                }
                if (q->b[j] == 1) {
                    cnt++;
                } else if (q->b[j] == -1) {
                    LoaderReleaseById_1cd340(h, q->a[0]);
                    LoaderReleaseById_1cd340(h, q->a[1]);
                    m2.z = 0;
                    m2.type = 3;
                    m2.id = q->id;
                    EffectEntryReleaseByIdx_2de320(base, &m2);
                } else if (q->b[j] == 0) {
                    PadIsHeld_183a20(D_004B2570, 0x1000);
                }
            }
            if (cnt == 2) {
                e3 = base + (u32)i * 0xE0;
                r3 = EffectEntryFinishImg_2dba30(e3);
                r4 = EffectEntryFinishScript_2dc0a0(e3);
                EffectEntryMeasureHeap_2dba80(e3);
                LoaderReleaseById_1cd340(h, q->a[0]);
                LoaderReleaseById_1cd340(h, q->a[1]);
                if (r3 != 0 || r4 != 0) {
                    m3.z = 0;
                    m3.type = 3;
                    m3.id = q->id;
                    EffectEntryReleaseByIdx_2de320(base, &m3);
                } else {
                    q->a[0] = -1;
                    q->a[1] = -1;
                }
            }
            break;
        }
    }
    return 0;
}
