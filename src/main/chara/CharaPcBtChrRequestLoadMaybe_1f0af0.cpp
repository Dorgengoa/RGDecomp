#include "types.h"

class VObj {
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual s32 slot70(s16);
};

typedef struct {
    u8 pad0[0xC];
    VObj *unkC;
} Holder;

typedef struct {
    u8 pad0[0x60];
    Holder *unk60;
} Ctx;

typedef struct Desc {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s8 *f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
    s32 f30;
    s32 f34;
} Desc;

extern "C" {
s32 Sprintf_1343b8(s8 *, const s8 *, ...);
void LoaderQueueAppendSeparator_1cd670(s32);
s32 CharaDataLoadSubRecById_1eda70(s32, Desc *);
s32 PcIdToResIndexMaybe_1f4f90(s32);
s32 PcDefGetCharaDataId_1f5060(s32);
s32 GetLoaderMgr_1f59d0(void);
s32 GetCharaDataMgr_1fdb70(void);
Ctx *GetWorldDataMgr_1fedf0(void);
s32 CharaBtResNameFormat_401730(s32);
extern s8 D_0045B790[];
}

extern "C" s32 CharaPcBtChrRequestLoadMaybe_1f0af0(s32 arg0, s32 arg1)
{
    s8 buf[0x20];
    Desc d;
    s32 mgr;
    s32 o;
    s32 id;
    s32 r;

    mgr = GetCharaDataMgr_1fdb70();
    o = GetWorldDataMgr_1fedf0()->unk60->unkC->slot70(arg1);
    if (o == 0) {
        return 0;
    }
    id = PcDefGetCharaDataId_1f5060(arg1);
    d.f0 = -1;
    d.f4 = -1;
    d.f8 = -1;
    d.fC = -1;
    d.f14 = -1;
    d.f1C = -1;
    d.f24 = -1;
    d.f30 = -1;
    d.f10 = -1;
    d.f18 = 0;
    d.f20 = 0;
    d.f28 = 0;
    d.f2C = 0;
    d.f34 = 0;
    d.f0 = id - 0x3DD;
    d.f4 = 1;
    d.f8 = 4;
    d.fC = 2;
    d.f14 = id;
    d.f1C = PcIdToResIndexMaybe_1f4f90(arg1);
    d.f18 = buf;
    Sprintf_1343b8(buf, D_0045B790, CharaBtResNameFormat_401730(o));
    r = CharaDataLoadSubRecById_1eda70(mgr, &d);
    LoaderQueueAppendSeparator_1cd670(GetLoaderMgr_1f59d0());
    return r;
}
