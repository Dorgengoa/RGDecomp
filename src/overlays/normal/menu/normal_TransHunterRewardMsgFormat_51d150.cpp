#include "types.h"
/* normal 0x0051D150 -- formats the two 0x791D caption buffers for entry `a`.
 * `a - 1` indexes the 20-byte record table hanging off the save block; `b`
 * picks between the "have" pair (0x40FE / +6) and the "want" pair (+2 / +4).
 * The chosen text id is resolved through the catalogue's slot-26 lookup and
 * both buffers are re-rendered, then the 0x7920 box takes the caption's 0x2C
 * string id.
 *
 * C++ virtual: `lw $25,0x70($25)` -> slot (0x70-8)/4 = 26.
 * `dsll32/dsra32 ..,16` at the call is the `(s16)` narrowing of an s32 id. */
struct Txt;
class Cat {
public:
    virtual void s000();
    virtual void s001();
    virtual void s002();
    virtual void s003();
    virtual void s004();
    virtual void s005();
    virtual void s006();
    virtual void s007();
    virtual void s008();
    virtual void s009();
    virtual void s010();
    virtual void s011();
    virtual void s012();
    virtual void s013();
    virtual void s014();
    virtual void s015();
    virtual void s016();
    virtual void s017();
    virtual void s018();
    virtual void s019();
    virtual void s020();
    virtual void s021();
    virtual void s022();
    virtual void s023();
    virtual void s024();
    virtual void s025();
    virtual Txt *find(s16 k);
};

typedef struct Txt { u8 pad00[0x2C]; s16 f2C; } Txt;
typedef struct Row { u8 pad00[2]; s16 f02; s16 f04; s16 f06; } Row;
typedef struct Tab { u8 pad00[0x7C]; s16 f7C; u8 pad7E[0x8C - 0x7E]; Row *f8C; } Tab;
typedef struct Sav { u8 pad00[0x94]; struct Hdr *f94; } Sav;
typedef struct Hdr { u8 pad00[0x10]; Tab *f10; } Hdr;
typedef struct Own { u8 pad00[8]; Sav *f08; } Own;
typedef struct Pak { u8 pad00[8]; Cat *f08; } Pak;
typedef struct Src { u8 pad00[0x40]; Pak *f40; } Src;
typedef struct Blk { s32 f00; u8 pad04[0xC - 4]; s32 f0C; u8 pad10[0xAC - 0x10]; } Blk;

extern u8 D_00527FD0[64];
extern u8 D_00527FF0[64];

extern "C" {
extern void *D_00484718;          /* gp - 0xA58 */
extern void *D_00484770;          /* gp - 0xA00 */

extern Own        *func_1FEDE0(void);
extern Src        *func_1FEDF0(void);
extern void        func_28AA00(Blk *b);
extern void        func_131B60(void *p, s32 v, s32 n);
extern const void *func_28AA30(void *p, s32 id);
extern void        func_28A9A0(void *d, const void *t, Blk *b, s32 n);
extern void        func_28F510(void *p, s32 id, const void *q, s32 d);
extern void       *func_28FE10(void *p, s32 id, s32 n);
extern void        func_288E50(void *p, s16 a, s32 b, s32 c);
}

extern "C" s32 normal_TransHunterRewardMsgFormat_51d150(s32 a, s32 b)
{
    Blk  b1;
    Blk  b2;
    Tab *tab;
    Row *p;
    Txt *s;
    void *w;
    s32  k;
    s32  t;
    s32  u;

    tab = func_1FEDE0()->f08->f94->f10;
    k = a - 1;
    if (k >= 0) {
        if (k >= tab->f7C) {
            p = 0;
        } else {
            p = (Row *)((u8 *)tab->f8C + k * 20);
        }
    } else {
        p = 0;
    }
    if (b != 0) {
        t = p->f06;
        u = 0x40FE;
    } else {
        u = p->f02;
        t = p->f04;
    }
    s = func_1FEDF0()->f40->f08->find((s16)u);
    func_28AA00(&b1);
    b1.f00 = a;
    func_131B60(D_00527FD0, 0, 0x20);
    func_28A9A0(D_00527FD0, func_28AA30(D_00484770, 7), &b1, 0);
    func_28F510(D_00484718, 0x791D, D_00527FD0, 0);
    func_28AA00(&b2);
    func_131B60(&b2, 0, 0xAC);
    b2.f00 = t;
    b2.f0C = u;
    func_131B60(D_00527FF0, 0, 0x40);
    func_28A9A0(D_00527FF0, func_28AA30(D_00484770, 0x3F4), &b2, 1);
    func_28F510(D_00484718, 0x791D, D_00527FF0, 1);
    w = func_28FE10(D_00484718, 0x7920, 0);
    if (w == 0) {
        return 0;
    }
    func_288E50(w, s->f2C, 0x28, 0x2D);
    return u;
}
