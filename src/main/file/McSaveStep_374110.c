#include "types.h"

typedef struct {
    s8 v[0x80];
} Buf_00374110;

typedef struct {
    s16 h0;
} Rec_00374110;

typedef struct {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    s32 x14;
    s32 x18;
} Port_00374110;

typedef struct {
    u8 pad0[0x8];
    s32 x8;
} Q_00374110;

typedef struct {
    u8 pad0[0x4A4];
    Port_00374110 ports[1];             /* 0x4A4 */
} McPorts_00374110;

typedef struct {
    u8 pad0[0x78];
    s16 slots[0x30];                    /* 0x78 */
    u8 padD8[0xE0 - 0xD8];
    u8 xE0[0x4E0 - 0xE0];               /* 0xE0 */
    s32 state;                          /* 0x4E0 */
    u8 pad4E4[0x4E8 - 0x4E4];
    s32 fd;                             /* 0x4E8 */
    s16 port;                           /* 0x4EC */
    s16 slot;                           /* 0x4EE */
    u8 pad4F0[0x50C - 0x4F0];
    Q_00374110 *x50C;                   /* 0x50C */
    s32 x510;                           /* 0x510 */
    u8 *x514;                           /* 0x514 */
    u8 pad518[0x51C - 0x518];
    s32 x51C;                           /* 0x51C */
} Mc_00374110;

typedef struct {
    u8 pad0[0x24];
    u8 *x24;
} G_00374110;

extern G_00374110 *GetGameData_1fede0(void);
extern Rec_00374110 *SaveMgrGetResult_375a00(Mc_00374110 *);
extern s32 sceMcSync_12d098(s32, s32 *, s32 *);
extern u8 McCardIsReady_376280(Port_00374110 *, s32);
extern void SaveSlotEntrySetBroken_376120(s16 *);
extern void McBuildIconPath_376400(Buf_00374110 *, s32, s32);
extern void sceMcRename_12db48(s32, s32, Buf_00374110 *, void *);
extern void McSetErrorResult_375890(Mc_00374110 *, s32);
extern void MemcardBuildSavePath_376380(s32, Buf_00374110 *);
extern s32 sceMcOpen_12ca58(s32, s32, Buf_00374110 *, s32);
extern s32 McSaveSerialize_375c60(Mc_00374110 *, s32);
extern s32 SaveDataBuildWriteBuffer_375b80(Mc_00374110 *, s32);
extern s32 SlotRecordFindLatestMaybe_3e4c90(G_00374110 *, s32);
extern s32 sceMcWrite_12cf20(s32, u8 *, s32);
extern void SaveProgressAdd_373650(Mc_00374110 *, s32);
extern s32 sceMcFlush_12d8b8(s32);
extern s32 sceMcClose_12cbb8(s32, s32);
extern void SaveSlotEntrySetValid_376080(s16 *);
extern s32 sceMcGetInfo_12d1b8(s32, s32, s32 *, s32 *, s32 *);
extern u8 D_004638D8[];
extern u8 D_004638E8[];

s32 McSaveStep_374110(Mc_00374110 *m)
{
    s32 slot;
    static s32 D_004831AC;
    G_00374110 *g;
    Rec_00374110 *rec;
    Port_00374110 *p;
    s32 sp16C;
    s32 sp168;
    s32 sp164;
    Buf_00374110 buf2;
    Buf_00374110 buf;
    s32 r;
    Q_00374110 *q;
    s32 n;
    s32 k;

    slot = m->slot;
    g = GetGameData_1fede0();
    rec = SaveMgrGetResult_375a00(m);
    p = &((McPorts_00374110 *)m)->ports[m->port];
    if (g == 0) {
        {
            Rec_00374110 *e = SaveMgrGetResult_375a00(m);
            e->h0 = 0xC;
        }
        return 1;
    }
    switch (m->state) {
    case 0:
        if (sceMcSync_12d098(1, 0, 0) == 0) {
            break;
        }
        r = McCardIsReady_376280(p, 1);
        if (r == 0) {
            return 1;
        }
        if (m->x50C == 0) {
            {
            Rec_00374110 *e = SaveMgrGetResult_375a00(m);
            e->h0 = 0xC;
        }
            return 1;
        }
        m->state = 0x32;
        break;
    case 0x32:
    case 0xC8:
        if (m->state == 0x32) {
            SaveSlotEntrySetBroken_376120(&m->slots[m->slot]);
            McBuildIconPath_376400(&buf, slot, 0);
            sceMcRename_12db48(m->port, 1, &buf, D_004638D8);
        } else {
            McBuildIconPath_376400(&buf, slot, 1);
            sceMcRename_12db48(m->port, 1, &buf, D_004638E8);
        }
        m->state++;
        break;
    case 0x33:
    case 0xC9:
        if (sceMcSync_12d098(1, &sp168, &sp16C) == 0) {
            break;
        }
        if (sp16C < 0) {
            McSetErrorResult_375890(m, sp16C);
            SaveSlotEntrySetBroken_376120(&m->slots[m->slot]);
            return 1;
        }
        if (m->state == 0x33) {
            m->state = 0x5A;
        } else {
            m->state = 0x12C;
        }
        break;
    case 0x5A:
        MemcardBuildSavePath_376380(slot, &buf2);
        if (sceMcOpen_12ca58(m->port, 1, &buf2, 0x202) == -200) {
            sceMcSync_12d098(1, 0, 0);
        } else {
            m->state = 0x64;
        }
        break;
    case 0x64:
        if (sceMcSync_12d098(1, &sp168, &sp16C) == 0) {
            break;
        }
        if (sp16C < 0) {
            McSetErrorResult_375890(m, sp16C);
            return 1;
        }
        if (**(s32 **)(g->x24 + 0x1188) == 0) {
            r = McSaveSerialize_375c60(m, sp16C);
        } else {
            r = SaveDataBuildWriteBuffer_375b80(m, sp16C);
        }
        if (r != 0) {
            q = m->x50C;
            q->x8 = SlotRecordFindLatestMaybe_3e4c90(g, 0) + 1;
        } else {
            McSetErrorResult_375890(m, sp16C);
            rec->h0 = 0xC;
            SaveSlotEntrySetBroken_376120(&m->slots[m->slot]);
            return 1;
        }
        n = m->x510;
        {
            u8 *b = (u8 *)m->x50C;
            D_004831AC = n;
            m->x514 = b;
        }
        m->x51C = 0;
        m->fd = sp16C;
        k = 0x200;
        if (n < 0x200) {
            k = n;
        }
        if (sceMcWrite_12cf20(m->fd, m->x514, k) == 0) {
            m->state++;
            break;
        }
        return -1;
    case 0x65:
        if (sceMcSync_12d098(1, &sp168, &sp164) == 0) {
            break;
        }
        if (sp164 < 0) {
            McSetErrorResult_375890(m, sp164);
            SaveSlotEntrySetBroken_376120(&m->slots[m->slot]);
            return 1;
        }
        m->x51C += sp164;
        SaveProgressAdd_373650(m, sp164);
        if (m->x51C >= D_004831AC) {
            if (sceMcFlush_12d8b8(m->fd) == 0) {
                m->state++;
                break;
            }
            return -1;
        }
        n = D_004831AC - m->x51C;
        k = 0x200;
        if (n < 0x200) {
            k = n;
        }
        sceMcWrite_12cf20(m->fd, m->x514 + m->x51C, k);
        break;
    case 0x66:
        if (sceMcSync_12d098(1, &sp168, &sp16C) == 0) {
            break;
        }
        if (sp16C < 0) {
            McSetErrorResult_375890(m, sp16C);
            return 1;
        }
        if (sceMcClose_12cbb8(m->fd, sp16C) == 0) {
            m->state++;
        }
        break;
    case 0x67:
        if (sceMcSync_12d098(1, &sp168, &sp16C) == 0) {
            break;
        }
        if (sp16C < 0) {
            McSetErrorResult_375890(m, sp16C);
            return 1;
        }
        m->state = 0x78;
        break;
    case 0x78:
        McBuildIconPath_376400(&buf2, m->slot, 1);
        if (sceMcOpen_12ca58(m->port, 1, &buf2, 3) == 0) {
            m->state++;
        }
        break;
    case 0x79:
        if (sceMcSync_12d098(1, &sp168, &sp16C) == 0) {
            break;
        }
        m->fd = sp16C;
        m->x51C = 0;
        m->x514 = m->xE0;
        n = m->fd;
        D_004831AC = 0x3C4;
        if (sceMcWrite_12cf20(n, m->xE0, 0x3C4) != 0) {
            rec->h0 = 0xC;
            return 1;
        }
        m->state++;
        break;
    case 0x7A:
        if (sceMcSync_12d098(1, &sp168, &sp164) == 0) {
            break;
        }
        if (sp164 < 0) {
            if (sp164 < -10) {
                p->x0 = 0;
            }
            McSetErrorResult_375890(m, sp164);
            return 1;
        }
        m->x51C += sp164;
        SaveProgressAdd_373650(m, sp164);
        if (m->x51C >= D_004831AC) {
            m->x51C = 0;
            if (sceMcFlush_12d8b8(m->fd) == 0) {
                m->state++;
                break;
            }
            return -1;
        }
        n = D_004831AC - m->x51C;
        k = 0x200;
        if (n < 0x200) {
            k = n;
        }
        sceMcWrite_12cf20(m->fd, m->x514 + m->x51C, k);
        break;
    case 0x7B:
        if (sceMcSync_12d098(1, &sp168, &sp16C) == 0) {
            break;
        }
        if (sp16C < 0) {
            McSetErrorResult_375890(m, sp16C);
            return 1;
        }
        if (sceMcClose_12cbb8(m->fd, sp16C) == 0) {
            m->state++;
            break;
        }
        rec->h0 = 2;
        return 1;
    case 0x7C:
        if (sceMcSync_12d098(1, &sp168, &sp16C) == 0) {
            break;
        }
        if (sp16C < 0) {
            McSetErrorResult_375890(m, sp16C);
            return 1;
        }
        SaveSlotEntrySetValid_376080(&m->slots[m->slot]);
        m->state = 0xC8;
        break;
    case 0x12C:
        if (sceMcGetInfo_12d1b8(m->port, 1, &p->x4, &p->x10, &p->x8) == 0) {
            m->state++;
            break;
        }
        rec->h0 = 0xC;
        return 1;
    case 0x12D:
        if (sceMcSync_12d098(1, &sp168, &sp16C) == 0) {
            break;
        }
        p->x0 = 1;
        p->x14 = sp16C;
        p->x18 = 1;
        if (sp16C != 0) {
            rec->h0 = 0xC;
            if (sp16C < -10) {
                p->x0 = 0;
            }
        } else {
            p->x18 = 0;
        }
        return 1;
    default:
        break;
    }
    return 0;
}
