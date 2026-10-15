#include "types.h"

typedef struct Res1 {
    s16 id;
    u8 pad2[0xA];
    char *name;
    u8 pad10[4];
    s16 *m14;
} Res1;

typedef struct E1 {
    Res1 *p0;
    s16 state;
    s16 step;
    u8 pad8[4];
    s32 fd;
    s32 m10;
    s32 m14;
    u8 b0:1;
    u8 b1:7;
    u8 pad19[3];
} E1;

typedef struct Res2 {
    s16 id;
    u8 pad2[2];
    char *name;
} Res2;

typedef struct E2 {
    Res2 *p0;
    char *m4;
    u8 pad8[4];
    s16 state;
    s16 step;
    s16 m10;
    u8 pad12[2];
    s32 fd;
    s32 m18;
    s32 m1C;
    s16 m20;
    s16 m22;
    u8 b0:1;
    u8 b1:7;
    u8 pad25[3];
} E2;

typedef struct Sub18_3 {
    u8 pad0[6];
    s16 m6;
} Sub18_3;

typedef struct Own3 {
    u8 pad0[0x18];
    Sub18_3 *m18;
} Own3;

typedef struct Res3 {
    s32 a;
    char *name;
    u8 pad8[4];
    s16 *mC;
} Res3;

typedef struct E3 {
    Res3 *p0;
    char *m4;
    s16 state;
    s16 step;
    u8 padC[4];
    s32 fd;
    s32 m14;
    s32 m18;
    u8 b0:1;
    u8 b1:7;
    u8 pad1D[3];
} E3;

typedef struct E4 {
    s16 m0;
    s16 state;
    s16 step;
    u8 pad6[2];
    s32 fd;
    s32 mC;
    s32 m10;
    u8 b0:1;
    u8 b1:7;
} E4;

typedef struct Elem48 {
    u8 pad[0x30];
} Elem48;

typedef struct T2390 {
    u8 pad0[0x34];
    s32 m34;
} T2390;

typedef struct Ldr {
    Own3 *m0;
    u8 pad4[8];
    E1 *mC;
    u8 pad10[8];
    E2 *m18;
    u8 pad1C[4];
    E3 *m20;
    u8 pad24[4];
    E4 *m28;
} Ldr;

extern "C" {
s32 Sprintf_1343b8(char *, char *, ...);
void *MemStackNew_14e0b0(s32, T2390 *);
void LoaderReleaseById_1cd340(s32 *, s32);
s32 LoaderGetData_1cd490(s32 *, s32, s32 *);
s32 LoaderGetStatus_1cd4f0(s32 *, s32);
void LoaderQueueAppendSeparator_1cd670(s32 *);
s32 LoaderRequestFile_1cd870(s32 *, char *, s32);
s32 ArchiveGetFileByPath_1c2800(s32, char *, s32 *);
s32 *GetLoaderMgr_1f59d0(void);
void MapApplySaveStateMaybe_1fe560(void);
void NpcObjTableReleaseByGroupId_2fa910(s32, s32);
void NpcCfgRun_2fcdd0(s32, s32, E2 *, void *, s32, s32 *);
void EventScriptRunTwoPassFwd_2fd960(s32, s32, char *, s32, s32);
void NavGraphLoadCfg_30a420(s32, s32, char *, s32, s32);
s32 GetNpcObjTable_312860(void);
s32 GetTreasureBoxPool_3389b0(void);
void TreasureBoxPoolResetByGroupId_3389c0(s32, s32);
void GameDataUnlockByMinGaugeLevelMaybe_3e4110(Own3 *);
void GameDataPurposeRefresh_3eb5c0(Own3 *, s32);
void NpcDataRefreshCondsMaybe_3eb930(Own3 *, s32);
void TreasureBoxParamRefreshCondsMaybe_3eca40(Own3 *, s32);
void TranspParamRefreshCondsMaybe_3ecce0(Own3 *, s32);
void BgmParamRefreshCondsMaybe_3ece90(Own3 *, s32);
void MapObjParamRefreshCondsMaybe_3ed0a0(Own3 *, s32);
s32 EvtInfoGetIdMaybe_3ed810(Own3 *);
char *ZoneDataSelectNameMaybe_3eff20(Res2 *, char *);
char *WorldDataGetPurposePacPath_3f0230(Ldr *, s32);
void WorldDataMgrRelease_3f0320(Ldr *, s32);
void WorldDataMgrSetupPurpose_3f0450(Ldr *, s32);
void WorldDataMgrSelectPurpose_3f05f0(Ldr *, s32);
void HandleEntryRelease_3f12f0(Ldr *, E3 *, s32);
void HandleEntryLinkNop_3f1380(Ldr *, E3 *, s32);
void HandleEntryResetStack_3f1390(Ldr *, E3 *, s32);
void HandleEntryRelease_3f1d80(Ldr *, E2 *, s32);
void WorldDataMgrZoneEntryLink_3f1ef0(Ldr *, E2 *, s32);
void WorldDataMgrZoneEntryAttach_3f1fc0(Ldr *, E2 *, s32);
T2390 *MemStackArrayGet_3f2390(Ldr *, s32);
void HandleEntryRelease_3f2500(Ldr *, E1 *, s32);
void WorldDataMgrPlanetEntryLink_3f2640(Ldr *, E1 *, s32);
void WorldDataMgrPlanetEntryAttach_3f2770(Ldr *, E1 *, s32);
void *memset(void *, s32, u32);
char *strcat(char *, char *);
char *strcpy(char *, char *);
extern char *D_0047FFE0;
extern char *D_0047FFE4;
extern char *D_0047FFF0;
extern char *D_0047FFF4;
extern char *D_00480130;
extern char *D_00480134;
extern char *D_0048013C;
extern s32 D_004644A0[];
extern s32 D_004644C8[];
}

#pragma divbyzerocheck on

extern "C" s32 WorldDataPurposeLoadMaybe_3eefe0(Ldr *self)
{
    s32 sz1;
    s32 cnt;
    s32 sz3;
    char buf1[0x80];
    char buf2[0x80];
    char buf2b[0x40];
    char buf3[0x80];
    char buf3b[0x40];
    char buf4[0x80];
    s32 *ctx;
    E1 *e1;
    E2 *e2;
    E3 *e3;
    E4 *e4;
    s32 i1;
    s32 i2;
    s32 i3;
    s32 n2;
    s32 n3;
    bool err1;
    bool err2;
    bool err3;
    bool err4;

    if (self->m18 == 0) {
        return 0;
    }
    ctx = GetLoaderMgr_1f59d0();
    if (ctx == 0) {
        return 0;
    }
    e1 = self->mC;
    for (i1 = 0; i1 < 2; i1++, e1++) {
        if (e1->p0 == 0) {
            continue;
        }
        if (e1->step <= 0) {
            continue;
        }
        if (e1->state == 4) {
            continue;
        }
        err1 = false;
        switch (e1->step) {
        case 1:
            Sprintf_1343b8(buf1, D_00480130, e1->p0->name, e1->p0->name);
            e1->fd = LoaderRequestFile_1cd870(ctx, buf1, 0);
            if (e1->fd >= 0) {
                LoaderQueueAppendSeparator_1cd670(ctx);
                e1->state = 2;
                e1->step++;
            } else {
                err1 = true;
            }
            break;
        case 2:
            if (e1->fd >= 0) {
                {
                    s32 r = LoaderGetStatus_1cd4f0(ctx, e1->fd);
                    if (r == 1) {
                        e1->m10 = 0;
                        e1->m14 = LoaderGetData_1cd490(ctx, e1->fd, &e1->m10);
                        e1->step++;
                    } else if (r == -1) {
                        err1 = true;
                    }
                }
            } else {
                err1 = true;
            }
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
            if (e1->fd >= 0) {
                if (LoaderGetStatus_1cd4f0(ctx, e1->fd) == 1) {
                    s32 st = e1->step;
                    s32 id = e1->p0->id;
                    e1->b0 = true;
                    if (st == 3) {
                        HandleEntryRelease_3f2500(self, e1, 0);
                    } else if (st >= 4 && st < 9) {
                        WorldDataMgrPlanetEntryAttach_3f2770(self, e1, st - 3);
                    } else if (st >= 9 && st < 14) {
                        WorldDataMgrPlanetEntryLink_3f2640(self, e1, st - 8);
                    } else if (st == 14) {
                        MapObjParamRefreshCondsMaybe_3ed0a0(self->m0, id);
                    } else if (st == 15) {
                        BgmParamRefreshCondsMaybe_3ece90(self->m0, id);
                    } else if (st == 16) {
                        TranspParamRefreshCondsMaybe_3ecce0(self->m0, id);
                    }
                    e1->b0 = false;
                    e1->step++;
                } else {
                    err1 = true;
                }
            } else {
                err1 = true;
            }
            break;
        case 17:
            if (e1->fd >= 0) {
                e1->b0 = true;
                {
                    s32 r = LoaderGetStatus_1cd4f0(ctx, e1->fd);
                    if (r == 1) {
                        MapApplySaveStateMaybe_1fe560();
                        e1->step++;
                    } else if (r == -1) {
                        err1 = true;
                    }
                }
                e1->b0 = false;
            } else {
                err1 = true;
            }
            break;
        case 18:
            if (e1->fd >= 0) {
                if (LoaderGetStatus_1cd4f0(ctx, e1->fd) == 1) {
                    e1->state = 3;
                    LoaderReleaseById_1cd340(ctx, e1->fd);
                    e1->fd = -1;
                    e1->step = 0;
                    GameDataUnlockByMinGaugeLevelMaybe_3e4110(self->m0);
                } else {
                    err1 = true;
                }
                e1->b0 = false;
            } else {
                err1 = true;
            }
            break;
        }
        if (err1) {
            e1->state = -1;
            if (e1->fd >= 0) {
                LoaderReleaseById_1cd340(ctx, e1->fd);
            }
            e1->fd = -1;
            e1->step = 0;
            e1->b0 = false;
        }
    }
    e2 = self->m18;
    n2 = D_004644A0[0];
    for (i2 = 0; i2 < n2; i2++, e2++) {
        if (e2->p0 == 0) {
            continue;
        }
        if (e2->step <= 0) {
            continue;
        }
        if (e2->state == 4) {
            continue;
        }
        err2 = false;
        switch (e2->step) {
        case 1:
            Sprintf_1343b8(buf2, D_00480134, e2->p0->name, e2->p0->name);
            e2->fd = LoaderRequestFile_1cd870(ctx, buf2, 0);
            if (e2->fd >= 0) {
                LoaderQueueAppendSeparator_1cd670(ctx);
                e2->state = 2;
                e2->step++;
            }
            break;
        case 2:
            if (e2->fd >= 0) {
                {
                    s32 r = LoaderGetStatus_1cd4f0(ctx, e2->fd);
                    if (r == 1) {
                        e2->m18 = 0;
                        e2->m1C = LoaderGetData_1cd490(ctx, e2->fd, &e2->m18);
                        e2->step++;
                    } else if (r == -1) {
                        err2 = true;
                    }
                }
            } else {
                err2 = true;
            }
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
            if (e2->fd >= 0) {
                e2->b0 = true;
                if (LoaderGetStatus_1cd4f0(ctx, e2->fd) == 1) {
                    s32 st = e2->step;
                    s32 id = e2->p0->id;
                    if (st == 3) {
                        s32 q = GetTreasureBoxPool_3389b0();
                        if (q != 0) {
                            TreasureBoxPoolResetByGroupId_3389c0(q, id);
                        }
                        q = GetNpcObjTable_312860();
                        if (q != 0) {
                            NpcObjTableReleaseByGroupId_2fa910(q, id);
                        }
                    } else if (st == 4) {
                        HandleEntryRelease_3f1d80(self, e2, 0);
                    } else if (st >= 5 && st < 8) {
                        WorldDataMgrZoneEntryAttach_3f1fc0(self, e2, st - 4);
                    } else if (st >= 8 && st < 11) {
                        WorldDataMgrZoneEntryLink_3f1ef0(self, e2, st - 7);
                    } else if (st == 11) {
                        TreasureBoxParamRefreshCondsMaybe_3eca40(self->m0, id);
                    } else if (st == 12) {
                        NpcDataRefreshCondsMaybe_3eb930(self->m0, id);
                    }
                    e2->step++;
                } else {
                    err2 = true;
                }
                e2->b0 = false;
            } else {
                err2 = true;
            }
            break;
        case 13:
            if (e2->fd >= 0) {
                e2->b0 = true;
                if (LoaderGetStatus_1cd4f0(ctx, e2->fd) == 1) {
                    s32 w = e2->m1C;
                    s32 m18 = e2->m18;
                    if (e2->p0 != 0 && e2->m4 != 0 && w != 0 && m18 > 0) {
                        s32 data;
                        Sprintf_1343b8(buf2b, D_0047FFE4, ZoneDataSelectNameMaybe_3eff20(e2->p0, e2->m4));
                        strcat(buf2b, D_0047FFE0);
                        sz1 = 0;
                        data = ArchiveGetFileByPath_1c2800(w, buf2b, &sz1);
                        if (data != 0 && sz1 > 0) {
                            T2390 *t = MemStackArrayGet_3f2390(self, e2->m10);
                            if (t != 0) {
                                s32 k = t->m34 / 3;
                                void *mem = MemStackNew_14e0b0(k * 48, t);
                                memset(mem, 0, k * sizeof(Elem48));
                                cnt = 0;
                                NpcCfgRun_2fcdd0(data, sz1, e2, mem, k, &cnt);
                                e2->m20 = k;
                                e2->m22 = cnt;
                            }
                        }
                    }
                    e2->step++;
                } else {
                    err2 = true;
                }
                e2->b0 = false;
            } else {
                err2 = true;
            }
            break;
        case 14:
            e2->step++;
            break;
        case 15:
            if (e2->fd >= 0) {
                if (LoaderGetStatus_1cd4f0(ctx, e2->fd) == 1) {
                    e2->state = 3;
                    if (e2->fd >= 0) {
                        LoaderReleaseById_1cd340(ctx, e2->fd);
                    }
                    e2->fd = -1;
                    e2->step = 0;
                    GameDataUnlockByMinGaugeLevelMaybe_3e4110(self->m0);
                } else {
                    err2 = true;
                }
                e2->b0 = false;
            } else {
                err2 = true;
            }
            break;
        }
        if (err2) {
            e2->state = -1;
            LoaderReleaseById_1cd340(ctx, e2->fd);
            e2->fd = -1;
            e2->step = 0;
            e2->b0 = false;
        }
    }
    e3 = self->m20;
    n3 = D_004644C8[0];
    for (i3 = 0; i3 < n3; i3++, e3++) {
        if (e3->p0 == 0) {
            continue;
        }
        if (e3->step <= 0) {
            continue;
        }
        if (e3->state == 4) {
            continue;
        }
        err3 = false;
        switch (e3->step) {
        case 1:
            Sprintf_1343b8(buf3, D_0048013C, e3->p0->name, e3->p0->name);
            e3->fd = LoaderRequestFile_1cd870(ctx, buf3, 0);
            if (e3->fd >= 0) {
                LoaderQueueAppendSeparator_1cd670(ctx);
                e3->state = 2;
                e3->step++;
            }
            break;
        case 2:
            if (e3->fd >= 0) {
                {
                    s32 r = LoaderGetStatus_1cd4f0(ctx, e3->fd);
                    if (r == 1) {
                        e3->m14 = 0;
                        e3->m18 = LoaderGetData_1cd490(ctx, e3->fd, &e3->m14);
                        e3->step++;
                    } else if (r == -1) {
                        err3 = true;
                    }
                }
            } else {
                err3 = true;
            }
            break;
        case 3:
        case 4:
        case 5:
            if (e3->fd >= 0) {
                e3->b0 = true;
                if (LoaderGetStatus_1cd4f0(ctx, e3->fd) == 1) {
                    if (e3->step == 3) {
                        HandleEntryRelease_3f12f0(self, e3, 0);
                    } else if (e3->step == 4) {
                        HandleEntryResetStack_3f1390(self, e3, e3->step - 3);
                    } else if (e3->step == 5) {
                        HandleEntryLinkNop_3f1380(self, e3, e3->step - 4);
                    }
                    e3->step++;
                } else {
                    err3 = true;
                }
                e3->b0 = false;
            } else {
                err3 = true;
            }
            break;
        case 6:
        case 7:
            if (e3->fd >= 0) {
                e3->b0 = true;
                if (LoaderGetStatus_1cd4f0(ctx, e3->fd) == 1) {
                    char *name;
                    s32 a;
                    s32 st = e3->step;
                    s32 w = e3->m18;
                    s32 m14 = e3->m14;
                    s32 k = -1;
                    if (e3->p0 != 0 && w != 0 && m14 > 0) {
                        s16 *mc;
                        name = e3->p0->name;
                        a = e3->p0->a;
                        mc = e3->p0->mC;
                        if (self->m0 != 0 && mc != 0) {
                            if (*mc == 1) {
                                k = EvtInfoGetIdMaybe_3ed810(self->m0);
                            } else {
                                k = self->m0->m18->m6;
                            }
                        }
                        if (name != 0 && a >= 0 && k >= 0) {
                            s32 data;
                            if (st == 6) {
                                Sprintf_1343b8(buf3b, D_0047FFF0, name);
                                strcat(buf3b, D_0047FFE0);
                            } else {
                                Sprintf_1343b8(buf3b, D_0047FFF4, name);
                                strcat(buf3b, D_0047FFE0);
                            }
                            sz3 = 0;
                            data = ArchiveGetFileByPath_1c2800(w, buf3b, &sz3);
                            if (data != 0 && sz3 > 0) {
                                if (st == 6) {
                                    NavGraphLoadCfg_30a420(data, sz3, name, a, k);
                                } else {
                                    EventScriptRunTwoPassFwd_2fd960(data, sz3, name, a, k);
                                }
                            }
                        }
                    }
                    e3->step++;
                } else {
                    err3 = true;
                }
                e3->b0 = false;
            } else {
                err3 = true;
            }
            break;
        case 8:
            if (e3->fd >= 0) {
                if (LoaderGetStatus_1cd4f0(ctx, e3->fd) == 1) {
                    e3->state = 3;
                    if (e3->fd >= 0) {
                        LoaderReleaseById_1cd340(ctx, e3->fd);
                    }
                    e3->fd = -1;
                    e3->step = 0;
                    GameDataUnlockByMinGaugeLevelMaybe_3e4110(self->m0);
                } else {
                    err3 = true;
                }
                e3->b0 = false;
            } else {
                err3 = true;
            }
            break;
        }
        if (err3) {
            e3->state = -1;
            LoaderReleaseById_1cd340(ctx, e3->fd);
            e3->fd = -1;
            e3->step = 0;
            e3->b0 = false;
        }
    }
    e4 = self->m28;
    if (e4->m0 == -1 || e4->step <= 0 || e4->state == 4) {
        goto ret1;
    }
    err4 = false;
    switch (e4->step) {
    case 1:
        {
            char *name = WorldDataGetPurposePacPath_3f0230(self, e4->m0);
            if (name != 0) {
                strcpy(buf4, name);
            } else {
                buf4[0] = 0;
            }
        }
        e4->fd = LoaderRequestFile_1cd870(ctx, buf4, 0);
        if (e4->fd >= 0) {
            LoaderQueueAppendSeparator_1cd670(ctx);
            e4->state = 2;
            e4->step++;
        }
        break;
    case 2:
        if (e4->fd >= 0) {
            {
                s32 r = LoaderGetStatus_1cd4f0(ctx, e4->fd);
                if (r == 1) {
                    e4->mC = 0;
                    e4->m10 = LoaderGetData_1cd490(ctx, e4->fd, &e4->mC);
                    e4->step++;
                } else if (r == -1) {
                    err4 = true;
                }
            }
        } else {
            err4 = true;
        }
        break;
    case 3:
    case 4:
    case 5:
    case 6:
        if (e4->fd >= 0) {
            e4->b0 = true;
            if (LoaderGetStatus_1cd4f0(ctx, e4->fd) == 1) {
                if (e4->step == 3) {
                    WorldDataMgrRelease_3f0320(self, 0);
                } else if (e4->step == 4) {
                    WorldDataMgrSelectPurpose_3f05f0(self, e4->step - 3);
                } else if (e4->step == 5) {
                    WorldDataMgrSetupPurpose_3f0450(self, e4->step - 4);
                } else if (e4->step == 6) {
                    GameDataPurposeRefresh_3eb5c0(self->m0, e4->step - 5);
                }
                e4->step++;
            } else {
                err4 = true;
            }
            e4->b0 = false;
        } else {
            err4 = true;
        }
        break;
    case 7:
        if (e4->fd >= 0) {
            if (LoaderGetStatus_1cd4f0(ctx, e4->fd) == 1) {
                e4->state = 3;
                if (e4->fd >= 0) {
                    LoaderReleaseById_1cd340(ctx, e4->fd);
                }
                e4->fd = -1;
                e4->step = 0;
                GameDataUnlockByMinGaugeLevelMaybe_3e4110(self->m0);
            } else {
                err4 = true;
            }
            e4->b0 = false;
        } else {
            err4 = true;
        }
        break;
    }
    if (err4) {
        e4->state = -1;
        LoaderReleaseById_1cd340(ctx, e4->fd);
        e4->fd = -1;
        e4->step = 0;
        e4->b0 = false;
    }
ret1:
    return 1;
}
