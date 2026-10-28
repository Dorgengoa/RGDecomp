/* SPDX-License-Identifier: CC0-1.0 */
/* VU instruction decoder + disassembler (docs/VU.md). */
#include "vu_decode.h"

#include <stdio.h>
#include <string.h>

static int32_t sext(uint32_t v, int bits)
{
    uint32_t m = 1u << (bits - 1);
    v &= (1u << bits) - 1;
    return (int32_t)((v ^ m) - m);
}

/* ------------------------------------------------------------- upper */

void vu_decode_upper(uint32_t w, vu_upper *u)
{
    unsigned op6 = w & 0x3F;
    memset(u, 0, sizeof *u);
    u->dest = (w >> 21) & 0xF;
    u->ft = (w >> 16) & 0x1F;
    u->fs = (w >> 11) & 0x1F;
    u->fd = (w >> 6) & 0x1F;
    u->bc = w & 3;
    u->bits = (uint8_t)((w >> 27) & 0x1F); /* I E M D T = bits 31..27 */
    u->kind = VU_U_INVALID;

    if (op6 < 0x3C) {
        static const uint8_t bck[7] = {VU_U_ADD, VU_U_SUB, VU_U_MADD, VU_U_MSUB,
                                       VU_U_MAX, VU_U_MINI, VU_U_MUL};
        if (op6 < 0x1C) {
            u->kind = bck[op6 >> 2];
            u->src = VU_SRC_BC;
            return;
        }
        switch (op6) {
        case 0x1C: u->kind = VU_U_MUL;  u->src = VU_SRC_Q; break;
        case 0x1D: u->kind = VU_U_MAX;  u->src = VU_SRC_I; break;
        case 0x1E: u->kind = VU_U_MUL;  u->src = VU_SRC_I; break;
        case 0x1F: u->kind = VU_U_MINI; u->src = VU_SRC_I; break;
        case 0x20: u->kind = VU_U_ADD;  u->src = VU_SRC_Q; break;
        case 0x21: u->kind = VU_U_MADD; u->src = VU_SRC_Q; break;
        case 0x22: u->kind = VU_U_ADD;  u->src = VU_SRC_I; break;
        case 0x23: u->kind = VU_U_MADD; u->src = VU_SRC_I; break;
        case 0x24: u->kind = VU_U_SUB;  u->src = VU_SRC_Q; break;
        case 0x25: u->kind = VU_U_MSUB; u->src = VU_SRC_Q; break;
        case 0x26: u->kind = VU_U_SUB;  u->src = VU_SRC_I; break;
        case 0x27: u->kind = VU_U_MSUB; u->src = VU_SRC_I; break;
        case 0x28: u->kind = VU_U_ADD;  break;
        case 0x29: u->kind = VU_U_MADD; break;
        case 0x2A: u->kind = VU_U_MUL;  break;
        case 0x2B: u->kind = VU_U_MAX;  break;
        case 0x2C: u->kind = VU_U_SUB;  break;
        case 0x2D: u->kind = VU_U_MSUB; break;
        case 0x2E: u->kind = VU_U_OPMSUB; break;
        case 0x2F: u->kind = VU_U_MINI; break;
        default: break;
        }
        return;
    }

    {
        unsigned op = (((w >> 6) & 0x1F) << 2) | (w & 3);
        static const uint8_t bck[4] = {VU_U_ADD, VU_U_SUB, VU_U_MADD, VU_U_MSUB};
        static const uint8_t fr[4] = {0, 4, 12, 15};
        u->to_acc = 1;
        if (op < 0x10) {
            u->kind = bck[op >> 2];
            u->src = VU_SRC_BC;
            return;
        }
        u->to_acc = 0;
        if (op < 0x14) { u->kind = VU_U_ITOF; u->frac = fr[op & 3]; return; }
        if (op < 0x18) { u->kind = VU_U_FTOI; u->frac = fr[op & 3]; return; }
        u->to_acc = 1;
        if (op < 0x1C) { u->kind = VU_U_MUL; u->src = VU_SRC_BC; return; }
        switch (op) {
        case 0x1C: u->kind = VU_U_MUL;  u->src = VU_SRC_Q; break;
        case 0x1D: u->kind = VU_U_ABS;  u->to_acc = 0; break;
        case 0x1E: u->kind = VU_U_MUL;  u->src = VU_SRC_I; break;
        case 0x1F: u->kind = VU_U_CLIP; u->to_acc = 0; break;
        case 0x20: u->kind = VU_U_ADD;  u->src = VU_SRC_Q; break;
        case 0x21: u->kind = VU_U_MADD; u->src = VU_SRC_Q; break;
        case 0x22: u->kind = VU_U_ADD;  u->src = VU_SRC_I; break;
        case 0x23: u->kind = VU_U_MADD; u->src = VU_SRC_I; break;
        case 0x24: u->kind = VU_U_SUB;  u->src = VU_SRC_Q; break;
        case 0x25: u->kind = VU_U_MSUB; u->src = VU_SRC_Q; break;
        case 0x26: u->kind = VU_U_SUB;  u->src = VU_SRC_I; break;
        case 0x27: u->kind = VU_U_MSUB; u->src = VU_SRC_I; break;
        case 0x28: u->kind = VU_U_ADD;  break;
        case 0x29: u->kind = VU_U_MADD; break;
        case 0x2A: u->kind = VU_U_MUL;  break;
        case 0x2C: u->kind = VU_U_SUB;  break;
        case 0x2D: u->kind = VU_U_MSUB; break;
        case 0x2E: u->kind = VU_U_OPMULA; break;
        case 0x2F: u->kind = VU_U_NOP; u->to_acc = 0; break;
        default: u->kind = VU_U_INVALID; u->to_acc = 0; break;
        }
    }
}

const char *vu_upper_name(const vu_upper *u)
{
    static const char *base[VU_U_COUNT] = {
#define X(n) #n,
        VU_UPPER_KINDS(X)
#undef X
    };
    static char buf[8][16];
    static unsigned slot;
    char *b;
    switch (u->kind) {
    case VU_U_OPMULA: case VU_U_OPMSUB: case VU_U_ABS: case VU_U_CLIP:
    case VU_U_NOP: case VU_U_INVALID:
        return base[u->kind];
    case VU_U_ITOF: return u->frac == 0 ? "ITOF0" : u->frac == 4 ? "ITOF4" : u->frac == 12 ? "ITOF12" : "ITOF15";
    case VU_U_FTOI: return u->frac == 0 ? "FTOI0" : u->frac == 4 ? "FTOI4" : u->frac == 12 ? "FTOI12" : "FTOI15";
    default: break;
    }
    b = buf[slot++ & 7];
    snprintf(b, 16, "%s%s%s", base[u->kind], u->to_acc ? "A" : "",
             u->src == VU_SRC_BC ? "bc" : u->src == VU_SRC_Q ? "q" : u->src == VU_SRC_I ? "i" : "");
    return b;
}

/* ------------------------------------------------------------- lower */

void vu_decode_lower(uint32_t w, vu_lower *l)
{
    unsigned op7 = w >> 25;
    memset(l, 0, sizeof *l);
    l->dest = (w >> 21) & 0xF;
    l->ft = (w >> 16) & 0x1F;
    l->fs = (w >> 11) & 0x1F;
    l->fd = (w >> 6) & 0x1F;
    l->fsf = (w >> 21) & 3;
    l->ftf = (w >> 23) & 3;
    l->imm = sext(w, 11);
    l->op = VU_L_INVALID;

    if (op7 == 0x40) {
        unsigned low = w & 0x3F;
        switch (low) {
        case 0x30: l->op = VU_L_IADD; return;
        case 0x31: l->op = VU_L_ISUB; return;
        case 0x32: l->op = VU_L_IADDI; l->imm = sext(w >> 6, 5); return;
        case 0x34: l->op = VU_L_IAND; return;
        case 0x35: l->op = VU_L_IOR; return;
        default: break;
        }
        if (low < 0x3C) return;
        switch ((((w >> 6) & 0x1F) << 2) | (w & 3)) {
        case 0x30: l->op = l->dest ? VU_L_MOVE : VU_L_NOP; break;
        case 0x31: l->op = VU_L_MR32; break;
        case 0x34: l->op = VU_L_LQI; break;
        case 0x35: l->op = VU_L_SQI; break;
        case 0x36: l->op = VU_L_LQD; break;
        case 0x37: l->op = VU_L_SQD; break;
        case 0x38: l->op = VU_L_DIV; break;
        case 0x39: l->op = VU_L_SQRT; break;
        case 0x3A: l->op = VU_L_RSQRT; break;
        case 0x3B: l->op = VU_L_WAITQ; break;
        case 0x3C: l->op = VU_L_MTIR; break;
        case 0x3D: l->op = VU_L_MFIR; break;
        case 0x3E: l->op = VU_L_ILWR; break;
        case 0x3F: l->op = VU_L_ISWR; break;
        case 0x40: l->op = VU_L_RNEXT; break;
        case 0x41: l->op = VU_L_RGET; break;
        case 0x42: l->op = VU_L_RINIT; break;
        case 0x43: l->op = VU_L_RXOR; break;
        case 0x64: l->op = VU_L_MFP; break;
        case 0x68: l->op = VU_L_XTOP; break;
        case 0x69: l->op = VU_L_XITOP; break;
        case 0x6C: l->op = VU_L_XGKICK; break;
        case 0x70: l->op = VU_L_ESADD; break;
        case 0x71: l->op = VU_L_ERSADD; break;
        case 0x72: l->op = VU_L_ELENG; break;
        case 0x73: l->op = VU_L_ERLENG; break;
        case 0x74: l->op = VU_L_EATANxy; break;
        case 0x75: l->op = VU_L_EATANxz; break;
        case 0x76: l->op = VU_L_ESUM; break;
        case 0x78: l->op = VU_L_ESQRT; break;
        case 0x79: l->op = VU_L_ERSQRT; break;
        case 0x7A: l->op = VU_L_ERCPR; break;
        case 0x7B: l->op = VU_L_WAITP; break;
        case 0x7C: l->op = VU_L_ESIN; break;
        case 0x7D: l->op = VU_L_EATAN; break;
        case 0x7E: l->op = VU_L_EEXP; break;
        default: break;
        }
        return;
    }

    switch (op7) {
    case 0x00: l->op = VU_L_LQ; break;
    case 0x01: l->op = VU_L_SQ; break;
    case 0x04: l->op = VU_L_ILW; break;
    case 0x05: l->op = VU_L_ISW; break;
    case 0x08: l->op = VU_L_IADDIU; l->imm = (int32_t)((((w >> 21) & 0xF) << 11) | (w & 0x7FF)); break;
    case 0x09: l->op = VU_L_ISUBIU; l->imm = (int32_t)((((w >> 21) & 0xF) << 11) | (w & 0x7FF)); break;
    case 0x10: l->op = VU_L_FCEQ;  l->imm = (int32_t)(w & 0xFFFFFF); break;
    case 0x11: l->op = VU_L_FCSET; l->imm = (int32_t)(w & 0xFFFFFF); break;
    case 0x12: l->op = VU_L_FCAND; l->imm = (int32_t)(w & 0xFFFFFF); break;
    case 0x13: l->op = VU_L_FCOR;  l->imm = (int32_t)(w & 0xFFFFFF); break;
    case 0x14: l->op = VU_L_FSEQ;  l->imm = (int32_t)((((w >> 21) & 1) << 11) | (w & 0x7FF)); break;
    case 0x15: l->op = VU_L_FSSET; l->imm = (int32_t)((((w >> 21) & 1) << 11) | (w & 0x7FF)); break;
    case 0x16: l->op = VU_L_FSAND; l->imm = (int32_t)((((w >> 21) & 1) << 11) | (w & 0x7FF)); break;
    case 0x17: l->op = VU_L_FSOR;  l->imm = (int32_t)((((w >> 21) & 1) << 11) | (w & 0x7FF)); break;
    case 0x18: l->op = VU_L_FMEQ; break;
    case 0x1A: l->op = VU_L_FMAND; break;
    case 0x1B: l->op = VU_L_FMOR; break;
    case 0x1C: l->op = VU_L_FCGET; break;
    case 0x20: l->op = VU_L_B; break;
    case 0x21: l->op = VU_L_BAL; break;
    case 0x24: l->op = VU_L_JR; break;
    case 0x25: l->op = VU_L_JALR; break;
    case 0x28: l->op = VU_L_IBEQ; break;
    case 0x29: l->op = VU_L_IBNE; break;
    case 0x2C: l->op = VU_L_IBLTZ; break;
    case 0x2D: l->op = VU_L_IBGTZ; break;
    case 0x2E: l->op = VU_L_IBLEZ; break;
    case 0x2F: l->op = VU_L_IBGEZ; break;
    default: break;
    }
}

void vu_decode_pair(uint32_t lower_word, uint32_t upper_word, vu_pair *p)
{
    p->uw = upper_word;
    p->lw = lower_word;
    vu_decode_upper(upper_word, &p->up);
    if (p->up.bits & VU_B_I) {
        memset(&p->lo, 0, sizeof p->lo);
        p->lo.op = VU_L_LOI;
        p->lo.imm = (int32_t)lower_word;
    } else {
        vu_decode_lower(lower_word, &p->lo);
    }
}

const char *vu_lower_name(int op)
{
    static const char *n[VU_L_COUNT] = {
#define X(x) #x,
        VU_LOWER_OPS(X)
#undef X
    };
    return (op >= 0 && op < VU_L_COUNT) ? n[op] : "?";
}

/* ------------------------------------------------------------- use sets */

void vu_use_add_read(vu_use *o, unsigned reg, unsigned mask);
#define add_r vu_use_add_read
void vu_use_add_read(vu_use *o, unsigned reg, unsigned mask)
{
    if (reg == 0 || mask == 0 || o->n_vf_r >= 4) return;
    o->vf_r[o->n_vf_r] = (uint8_t)reg;
    o->vf_r_mask[o->n_vf_r] = (uint8_t)mask;
    o->n_vf_r++;
}

static unsigned fbit(unsigned f) { return 8u >> f; }

void vu_upper_use(const vu_upper *u, vu_use *o)
{
    memset(o, 0, sizeof *o);
    o->vi_w = o->vi_r0 = o->vi_r1 = -1;
    switch (u->kind) {
    case VU_U_ADD: case VU_U_SUB: case VU_U_MADD: case VU_U_MSUB:
    case VU_U_MUL: case VU_U_MAX: case VU_U_MINI:
        add_r(o, u->fs, u->dest);
        if (u->src == VU_SRC_VF) add_r(o, u->ft, u->dest);
        else if (u->src == VU_SRC_BC) add_r(o, u->ft, fbit(u->bc));
        else if (u->src == VU_SRC_Q) o->uses_q = 1;
        else o->reads_i = 1;
        if (!u->to_acc) { o->vf_w = u->fd; o->vf_w_mask = u->dest; }
        break;
    case VU_U_OPMULA: case VU_U_OPMSUB:
        add_r(o, u->fs, 0xE);
        add_r(o, u->ft, 0xE);
        if (u->kind == VU_U_OPMSUB) { o->vf_w = u->fd; o->vf_w_mask = u->dest; }
        break;
    case VU_U_ITOF: case VU_U_FTOI: case VU_U_ABS:
        add_r(o, u->fs, u->dest);
        o->vf_w = u->ft; o->vf_w_mask = u->dest;
        break;
    case VU_U_CLIP:
        add_r(o, u->fs, 0xE);
        add_r(o, u->ft, 1);
        break;
    default: break;
    }
    if (o->vf_w == 0) o->vf_w_mask = 0;
}
