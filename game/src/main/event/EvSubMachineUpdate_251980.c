/* rgp:protos */
#define RGP_SELF_EvSubMachineUpdate_251980 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* m2c needed a synthetic .rodata block for jtbl_0045EDB0 (target labels are
   not in the retail listing since nothing else branches to them) -- see
   build/s17/reports/e.md for the lever. */

typedef struct {
    /* 0x00 */ u8 pad00[0x08];
    /* 0x08 */ void *head0;
    /* 0x0C */ void *tail0;
    /* 0x10 */ void *head1;
    /* 0x14 */ void *tail1;
    /* 0x18 */ void *head2;
    /* 0x1C */ void *tail2;
    /* 0x20 */ void *head3;
    /* 0x24 */ void *tail3;
    /* 0x28 */ void *head4;
    /* 0x2C */ void *tail4;
    /* 0x30 */ void *head5;
    /* 0x34 */ void *tail5;
    /* 0x38 */ void *head6;
    /* 0x3C */ void *tail6;
    /* 0x40 */ u8 pad40[0x60 - 0x40];
    /* 0x60 */ s32 unk60;
    /* 0x64 */ u8 pad64[0x70 - 0x64];
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ f32 unk78;
    /* 0x7C */ u8 pad7c[0x80 - 0x7c];
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ f32 unk88;
} S_0025198;

typedef struct Node {
    /* 0x0 */ s32 type;
} Node;

typedef s32 (*NodeFunc)(Node *, S_0025198 *);

extern NodeFunc D_0044D640[];
extern u8 D_004BDDB0[0x400];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void EvSubMachineUpdate_251980(S_0025198 *arg0) {
    Node *node;
    s32 i;
    void **head;
    void **tail;

    if (arg0->unk60 > -1) {
        if (!(EventCastGetPos_258740(&(*(void * *)D_004BDDB0), arg0->unk60, &arg0->unk70) == 1)) {
            EvtSubMachineReset_251f60((s32)(arg0));
        } else {
            EventCastGetRotation_258610(&(*(void * *)D_004BDDB0), arg0->unk60, &arg0->unk80);
            for (i = 0; i < 7; i++) {
                switch (i) {
                case 0:
                    head = &arg0->head0;
                    tail = &arg0->tail0;
                    break;
                case 1:
                    head = &arg0->head1;
                    tail = &arg0->tail1;
                    break;
                case 2:
                    head = &arg0->head2;
                    tail = &arg0->tail2;
                    break;
                case 3:
                    head = &arg0->head3;
                    tail = &arg0->tail3;
                    break;
                case 4:
                    head = &arg0->head4;
                    tail = &arg0->tail4;
                    break;
                case 5:
                    head = &arg0->head5;
                    tail = &arg0->tail5;
                    break;
                case 6:
                    head = &arg0->head6;
                    tail = &arg0->tail6;
                    break;
                }
                node = *(Node **) head;
                while (node != NULL) {
                    if (node->type > 0 && node->type <= 0x27) {
                        if (D_0044D640[node->type](node, arg0) != 0) {
                            break;
                        }
                    } else {
                        node = NULL;
                        break;
                    }
                    node = ((Node *)EventSubNodeRelease_251ed0(arg0, node));
                }
                *head = node;
                if (node == NULL) {
                    *tail = NULL;
                }
            }
            arg0->unk84 = WrapAngle_13c050(arg0->unk84);
            EventCastSetPosition_258a50(&(*(void * *)D_004BDDB0), arg0->unk60, arg0->unk70, arg0->unk74, arg0->unk78);
            EventCastSetRotation_258850(&(*(void * *)D_004BDDB0), arg0->unk60, arg0->unk80, arg0->unk84, arg0->unk88);
        }
    }
}
