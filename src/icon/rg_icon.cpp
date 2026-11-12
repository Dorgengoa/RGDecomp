// SPDX-License-Identifier: CC0-1.0
// The exe / window icon from the player's own data/ (rg_icon.h, docs/ICON.md).
#include "rg_icon.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

extern "C" const int rg_icon_sizes[RG_ICON_IMAGES] = {256, 64, 48, 32, 24, 16};

namespace {

void say(char *err, size_t cap, const char *msg, const char *arg = "") {
    if (err && cap) snprintf(err, cap, "%s%s", msg, arg);
}

uint32_t rd32(const uint8_t *p) { return p[0] | p[1] << 8 | p[2] << 16 | (uint32_t)p[3] << 24; }
uint16_t rd16(const uint8_t *p) { return (uint16_t)(p[0] | p[1] << 8); }
void wr16(std::vector<uint8_t> &v, unsigned x) { v.push_back((uint8_t)x); v.push_back((uint8_t)(x >> 8)); }
void wr32(std::vector<uint8_t> &v, uint32_t x) { wr16(v, x & 0xFFFF); wr16(v, x >> 16); }

FILE *open_utf8(const std::string &path) {
#ifdef _WIN32
    int n = MultiByteToWideChar(CP_UTF8, 0, path.c_str(), -1, nullptr, 0);
    if (n <= 0) return nullptr;
    std::wstring w((size_t)n, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, path.c_str(), -1, &w[0], n);
    return _wfopen(w.c_str(), L"rb");
#else
    return fopen(path.c_str(), "rb");
#endif
}

bool read_all(const std::string &path, std::vector<uint8_t> &out) {
    FILE *f = open_utf8(path);
    if (!f) return false;
    std::vector<uint8_t> v;
    uint8_t buf[65536];
    size_t n;
    while ((n = fread(buf, 1, sizeof buf, f)) > 0) v.insert(v.end(), buf, buf + n);
    fclose(f);
    out.swap(v);
    return true;
}

bool read_at(const std::string &path, uint64_t off, uint32_t size, std::vector<uint8_t> &out) {
    FILE *f = open_utf8(path);
    if (!f) return false;
#ifdef _WIN32
    int sk = _fseeki64(f, (long long)off, SEEK_SET);
#else
    int sk = fseeko(f, (off_t)off, SEEK_SET);
#endif
    out.resize(size);
    bool ok = sk == 0 && fread(out.data(), 1, size, f) == size;
    fclose(f);
    return ok;
}

// DATA*.HD6: tokens (NUL-separated), a varint token-index name stream, u64 records
// (name offset bits 0-17 | DAT offset / 2048 bits 18-37 | size / 4 bits 38-63);
// tools/census/hd6_list.py.
bool hd6_find(const std::vector<uint8_t> &d, const char *want, uint64_t *off, uint32_t *size) {
    if (d.size() < 0x30 || memcmp(d.data(), "HD6", 3)) return false;
    uint32_t tok_off = rd32(&d[4]), tok_size = rd32(&d[8]);
    uint32_t name_off = rd32(&d[0x14]), name_size = rd32(&d[0x18]);
    uint32_t count = rd32(&d[0x24]), dir_off = rd32(&d[0x28]);
    if ((uint64_t)tok_off + tok_size > d.size() || (uint64_t)name_off + name_size > d.size() ||
        (uint64_t)dir_off + (uint64_t)count * 8 > d.size())
        return false;
    std::vector<std::string> toks;
    {
        size_t s = tok_off;
        for (size_t i = tok_off; i <= tok_off + tok_size; i++)
            if (i == tok_off + tok_size || d[i] == 0) {
                toks.emplace_back((const char *)&d[s], i - s);
                s = i + 1;
            }
    }
    const size_t wl = strlen(want);
    for (uint32_t k = 0; k < count; k++) {
        uint64_t v = 0;
        for (int b = 0; b < 8; b++) v |= (uint64_t)d[dir_off + k * 8 + b] << (8 * b);
        uint32_t sz = (uint32_t)((v >> 38) << 2);
        if (!sz) continue;
        size_t i = name_off + (size_t)(v & 0x3FFFF), end = (size_t)name_off + name_size;
        std::string name;
        while (i < end && name.size() <= wl) {
            uint32_t t = 0;
            int shift = 0;
            while (i < end) {
                uint8_t c = d[i++];
                t |= (uint32_t)(c & 0x7F) << shift;
                shift += 7;
                if (!(c & 0x80) || shift > 28) break;
            }
            if (t == 0) break;
            if (t >= toks.size()) { name.clear(); break; }
            name += toks[t];
        }
        if (name == want) {
            *off = ((v >> 18) & 0xFFFFF) * 2048u;
            *size = sz;
            return true;
        }
    }
    return false;
}

struct Pic {
    int w = 0, h = 0;
    std::vector<uint8_t> rgba;   // straight alpha 0..255
};

int csm1(int i) { return (i & 0xE7) | ((i & 0x08) << 1) | ((i & 0x10) >> 1); }

// byte offset of linear PSMT8 pixel (x, y) in a TIM2 stored as GS memory after a PSMCT32
// upload (tools/assets/gaiji.py _swizzle8_table)
uint32_t swz8(int w, int x, int y) {
    uint32_t row = (uint32_t)(y & ~0xF) * (uint32_t)w;
    int swap = (((y + 2) >> 2) & 1) * 4;
    uint32_t col = (uint32_t)(((((y & ~3) >> 1) + (y & 1)) & 7) * w * 2);
    int byte = (y >> 1) & 1;
    return row + (uint32_t)(x & ~0xF) * 2 + col + (uint32_t)(((x + swap) & 7) * 4) + (uint32_t)byte +
           (uint32_t)((x >> 2) & 2);
}

// the TIM2 picture named `name` in the IM3 archive(s) of a file (tools/p6/ps2tex.py)
bool im3_picture(const std::vector<uint8_t> &b, const char *name, Pic &out) {
    for (size_t base = 0; base + 0x10 <= b.size(); base += 16) {
        if (memcmp(&b[base], "IM3\0", 4) || rd32(&b[base + 4]) != 0x10) continue;
        uint32_t n = rd32(&b[base + 8]);
        if (n == 0 || n >= 512) continue;
        for (uint32_t i = 0; i < n; i++) {
            size_t e = base + 0x10 + (size_t)i * 0x40;
            if (e + 0x40 > b.size()) break;
            if (strncmp((const char *)&b[e], name, 0x20)) continue;
            size_t t = base + rd32(&b[e + 0x24]);
            if (t + 0x40 > b.size() || memcmp(&b[t], "TIM2", 4)) return false;
            const uint8_t *p = &b[t + 0x10];
            uint32_t clut_size = rd32(p + 4), img_size = rd32(p + 8);
            uint16_t hdr = rd16(p + 12), clut_colors = rd16(p + 14);
            uint8_t img_type = p[19];
            int w = rd16(p + 20), h = rd16(p + 22);
            size_t px = t + 0x10 + hdr, cl = px + img_size;
            if (!w || !h || cl + clut_size > b.size()) return false;
            out.w = w;
            out.h = h;
            out.rgba.assign((size_t)w * h * 4, 0);
            if (img_type == 5 && clut_colors == 256 && w % 16 == 0 && h % 4 == 0 &&
                img_size >= (uint32_t)(w * h) && clut_size >= 1024) {   // PSMT8, swizzled, CSM1
                for (int y = 0; y < h; y++)
                    for (int x = 0; x < w; x++) {
                        int ix = csm1(b[px + swz8(w, x, y)]);
                        const uint8_t *c = &b[cl + (size_t)ix * 4];
                        uint8_t *o = &out.rgba[((size_t)y * w + x) * 4];
                        o[0] = c[0]; o[1] = c[1]; o[2] = c[2];
                        o[3] = (uint8_t)(c[3] >= 0x80 ? 255 : c[3] * 2);
                    }
                return true;
            }
            if (img_type == 4 && clut_colors == 16 && img_size >= (uint32_t)(w * h / 2) && clut_size >= 64) {
                for (int y = 0; y < h; y++)   // PSMT4: linear, low nibble first (tools/p6/ps2tex.py)
                    for (int x = 0; x < w; x++) {
                        size_t k = (size_t)y * w + x;
                        int ix = (b[px + k / 2] >> ((k & 1) * 4)) & 15;
                        const uint8_t *c = &b[cl + (size_t)ix * 4];
                        uint8_t *o = &out.rgba[k * 4];
                        o[0] = c[0]; o[1] = c[1]; o[2] = c[2];
                        o[3] = (uint8_t)(c[3] >= 0x80 ? 255 : c[3] * 2);
                    }
                return true;
            }
            if (img_type == 2 && img_size >= (uint32_t)(w * h * 3)) {   // CT24
                for (size_t k = 0; k < (size_t)w * h; k++) {
                    memcpy(&out.rgba[k * 4], &b[px + k * 3], 3);
                    out.rgba[k * 4 + 3] = 255;
                }
                return true;
            }
            return false;
        }
    }
    return false;
}

// ---- integer resampler, premultiplied alpha, values in Q8 (0..255*256)
// 1-D: box (area average) from the source; growing = the source repeated k = ceil(ld / ls)
// times per pixel first ("sharp bilinear": crisp pixels, soft only at the seams).  Every
// output is a convex combination of inputs: no ringing, colour never leaves the source's.
void resample_1d(const int64_t *src, int ls, int64_t *dst, int ld, int stride_s, int stride_d) {
    const int k = ld > ls ? (ld + ls - 1) / ls : 1;
    const int64_t L = (int64_t)ls * k;   // virtual source length
    for (int j = 0; j < ld; j++) {
        // target j covers [j*L, (j+1)*L) in units where a virtual pixel is ld wide
        int64_t lo = (int64_t)j * L, hi = (int64_t)(j + 1) * L, acc = 0;
        for (int64_t i = lo / ld; i < L && i * ld < hi; i++) {
            int64_t a = i * ld, z = a + ld;
            int64_t ov = (z < hi ? z : hi) - (a > lo ? a : lo);
            if (ov > 0) acc += src[(size_t)(i / k) * stride_s] * ov;
        }
        dst[(size_t)j * stride_d] = (acc + L / 2) / L;
    }
}

// a w x h straight-RGBA picture -> t x t
void resample(const uint8_t *rgba, int w, int h, int t, uint8_t *out) {
    std::vector<int64_t> pm((size_t)w * h * 4), mid((size_t)t * h * 4), fin((size_t)t * t * 4);
    for (size_t k = 0; k < (size_t)w * h; k++) {
        int a = rgba[k * 4 + 3];
        for (int c = 0; c < 3; c++) pm[k * 4 + c] = ((int64_t)rgba[k * 4 + c] * a * 256 + 127) / 255;
        pm[k * 4 + 3] = (int64_t)a * 256;
    }
    for (int y = 0; y < h; y++)
        for (int c = 0; c < 4; c++)
            resample_1d(&pm[(size_t)y * w * 4 + c], w, &mid[(size_t)y * t * 4 + c], t, 4, 4);
    for (int x = 0; x < t; x++)
        for (int c = 0; c < 4; c++)
            resample_1d(&mid[(size_t)x * 4 + c], h, &fin[(size_t)x * 4 + c], t, t * 4, t * 4);
    for (size_t k = 0; k < (size_t)t * t; k++) {
        int64_t a = fin[k * 4 + 3];
        if (a < 0) a = 0;
        if (a > 255 * 256) a = 255 * 256;
        uint8_t *o = &out[k * 4];
        o[3] = (uint8_t)((a + 128) / 256);
        for (int c = 0; c < 3; c++) {
            int64_t v = fin[k * 4 + c];
            if (v < 0) v = 0;
            if (v > a) v = a;
            o[c] = (uint8_t)(o[3] ? (v * 255 + a / 2) / (a ? a : 1) : 0);
        }
    }
}

int build_from(const uint8_t *rgba, int w, int h, rg_icon_set *out) {
    memset(out, 0, sizeof *out);
    for (int i = 0; i < RG_ICON_IMAGES; i++) {
        int t = rg_icon_sizes[i];
        out->size[i] = t;
        out->rgba[i] = (uint8_t *)malloc((size_t)t * t * 4);
        if (!out->rgba[i]) { rg_icon_free(out); return -1; }
        resample(rgba, w, h, t, out->rgba[i]);
        out->n = i + 1;
    }
    return 0;
}

// a sub-rectangle of a picture, centred on a transparent canvas of cw x ch
std::vector<uint8_t> cut(const Pic &p, int x0, int y0, int x1, int y1, int cw, int ch) {
    std::vector<uint8_t> v((size_t)cw * ch * 4, 0);
    int ox = (cw - (x1 - x0)) / 2, oy = (ch - (y1 - y0)) / 2;
    for (int y = y0; y < y1; y++)
        for (int x = x0; x < x1; x++)
            if (x >= 0 && y >= 0 && x < p.w && y < p.h)
                memcpy(&v[((size_t)(y - y0 + oy) * cw + (x - x0 + ox)) * 4], &p.rgba[((size_t)y * p.w + x) * 4], 4);
    return v;
}

// The icon sources (rg_icon.h), all from DATA0_0: archive member, IM3 picture name (NULL =
// the PS2 memory-card icon's texture), expected size, the cut (x0, y0, x1, y1) centred on a
// cw x ch canvas, glow (alpha from brightness: a texture drawn additively on black).
struct Source {
    const char *name, *member, *pic;
    int w, h, x0, y0, x1, y1, cw, ch, glow, white;   // white: flat 208-grey -> white, canvas white
};
const Source k_sources[RG_ICON_SOURCES] = {
    // Jaster's battle-menu portrait cell
    {"jaster", "menu\\rc\\menu_static_img2_en.pac", "b_m_face", 256, 128, 6, 0, 50, 48, 48, 48, 0, 0},
    // the ship of an early title card, a square on the 4:3 display (512 px shown as 597)
    {"ship", "chara\\dc3title.img", "DC3title", 512, 448, 130, 20, 380, 312, 250, 292, 0, 0},
    // the memory-card icon: the blue galaxy logo on white (128 x 128 RGB555; its flat grey
    // ground made white, cut to the logo)
    {"galaxy", "menu\\rg.ico", nullptr, 128, 128, 2, 8, 126, 100, 124, 124, 0, 1},
    // the logo with the galaxy, own alpha (128 x 64), centred on a square
    {"logo", "menu\\l_mark02_en.img", "L_mark02", 128, 64, 0, 0, 128, 64, 128, 128, 0, 0},
    // the birthmark crest of the save points / transporters (rc\\gate.chr, PSMT4, own alpha)
    {"birthmark", "rc\\gate.chr", "new_gate01", 128, 128, 69, 62, 116, 127, 66, 66, 0, 0},
    // the red seal disc of the space gate (additive glow, 256 x 256)
    {"seal", "map\\m09\\space_gate.ipk", "gate01_01", 256, 256, 0, 0, 256, 256, 256, 256, 1, 0},
    // a blue globe with a ring (event texture, own alpha)
    {"globe", "event\\ev05\\ev05_0010_0\\ev05_001_np_c13.chr", "ev05_001_np_c13_08", 256, 256, 0, 0, 256, 256, 256, 256, 0, 0},
    // a carved crest in stone (map texture, opaque)
    {"crest", "map\\m05_area01\\m05api01b.ipk", "m05api01_50b", 256, 256, 0, 0, 256, 256, 256, 256, 0, 0},
};

// The texture of a PS2 memory-card icon (menu\rg.ico): 128 x 128 RGB555 at the end of the
// file; compressed (texture type bit 3) = u32 size + RLE of u16 words (code >= 0xFF00:
// 0x10000 - code literal words; else the next word code times).  tools/icon/mcicon.py.
bool mc_icon_picture(const std::vector<uint8_t> &d, Pic &out) {
    const size_t n = d.size(), N = 128 * 128;
    if (n < 0x20 + 64 || rd32(&d[0]) != 0x10000) return false;
    std::vector<uint16_t> px;
    if (!(rd32(&d[8]) & 8)) {
        if (n < N * 2) return false;
        for (size_t k = 0; k < N; k++) px.push_back(rd16(&d[n - N * 2 + k * 2]));
    } else {
        size_t off = 20;
        for (; off + 4 <= n; off++) {
            uint32_t sz = rd32(&d[off]);
            if (sz > 64 && off + 4 + sz <= n && n - (off + 4 + sz) < 16) break;
        }
        if (off + 4 > n) return false;
        size_t p = off + 4, end = off + 4 + rd32(&d[off]);
        while (p + 2 <= end && px.size() < N) {
            uint16_t c = rd16(&d[p]);
            p += 2;
            if ((c & 0xFF00) == 0xFF00) {
                for (unsigned k = 0; k < 0x10000u - c && p + 2 <= end; k++, p += 2) px.push_back(rd16(&d[p]));
            } else if (p + 2 <= end) {
                px.insert(px.end(), c, rd16(&d[p]));
                p += 2;
            }
        }
    }
    px.resize(N, 0);
    out.w = out.h = 128;
    out.rgba.assign(N * 4, 255);
    for (size_t k = 0; k < N; k++) {
        out.rgba[k * 4 + 0] = (uint8_t)((px[k] & 31) << 3);
        out.rgba[k * 4 + 1] = (uint8_t)(((px[k] >> 5) & 31) << 3);
        out.rgba[k * 4 + 2] = (uint8_t)(((px[k] >> 10) & 31) << 3);
    }
    return true;
}

}  // namespace

extern "C" {

int rg_icon_source_by_name(const char *name) {
    if (!name) return -1;
    for (int i = 0; i < RG_ICON_SOURCES; i++)
        if (!strcmp(name, rg_icon_source_name(i))) return i;
    return -1;
}

const char *rg_icon_source_name(int source) {
    return source >= 0 && source < RG_ICON_SOURCES ? k_sources[source].name : "?";
}

int rg_icon_build_rgba(const uint8_t *rgba, int w, int h, rg_icon_set *out) {
    if (!rgba || w <= 0 || h <= 0 || !out) return -1;
    return build_from(rgba, w, h, out);
}

int rg_icon_build(const char *data_dir, int source, rg_icon_set *out, char *err, size_t errcap) {
    if (out) memset(out, 0, sizeof *out);
    if (!data_dir || !out || source < 0 || source >= RG_ICON_SOURCES) {
        say(err, errcap, "bad arguments");
        return -1;
    }
    const Source &S = k_sources[source];
    std::string dir = data_dir;
    if (!dir.empty() && dir.back() != '/' && dir.back() != '\\') dir += '/';
    std::vector<uint8_t> hd6, file;
    if (!read_all(dir + "DATA0_0.HD6", hd6)) {
        say(err, errcap, "cannot read ", (dir + "DATA0_0.HD6").c_str());
        return -1;
    }
    uint64_t off;
    uint32_t size;
    if (!hd6_find(hd6, S.member, &off, &size)) {
        say(err, errcap, "not in DATA0_0.HD6: ", S.member);
        return -1;
    }
    if (!read_at(dir + "DATA0_0.DAT", off, size, file)) {
        say(err, errcap, "cannot read DATA0_0.DAT");
        return -1;
    }
    Pic p;
    if (S.pic ? !im3_picture(file, S.pic, p) : !mc_icon_picture(file, p)) {
        say(err, errcap, "unexpected texture layout: ", S.member);
        return -1;
    }
    if (p.w != S.w || p.h != S.h) {
        say(err, errcap, "unexpected picture size: ", S.member);
        return -1;
    }
    if (S.glow)   // an additive glow on black: alpha = brightness, colour un-premultiplied
        for (size_t k = 0; k < (size_t)p.w * p.h; k++) {
            uint8_t *c = &p.rgba[k * 4];
            int m = c[0] > c[1] ? c[0] : c[1];
            if (c[2] > m) m = c[2];
            for (int i = 0; i < 3; i++) c[i] = (uint8_t)(m ? (c[i] * 255 + m / 2) / m : 0);
            c[3] = (uint8_t)m;
        }
    if (S.white)
        for (size_t k = 0; k < (size_t)p.w * p.h; k++) {
            uint8_t *c = &p.rgba[k * 4];
            if (c[0] == 208 && c[1] == 208 && c[2] == 208) c[0] = c[1] = c[2] = 255;
        }
    std::vector<uint8_t> canvas = cut(p, S.x0, S.y0, S.x1, S.y1, S.cw, S.ch);
    if (S.white)
        for (size_t k = 0; k < (size_t)S.cw * S.ch; k++)
            if (!canvas[k * 4 + 3]) canvas[k * 4] = canvas[k * 4 + 1] = canvas[k * 4 + 2] = canvas[k * 4 + 3] = 255;
    if (build_from(canvas.data(), S.cw, S.ch, out)) {
        say(err, errcap, "out of memory");
        return -1;
    }
    return 0;
}

void rg_icon_free(rg_icon_set *s) {
    if (!s) return;
    for (int i = 0; i < RG_ICON_IMAGES; i++) free(s->rgba[i]);
    memset(s, 0, sizeof *s);
}

uint8_t *rg_icon_image_bytes(const rg_icon_set *s, int i, size_t *len) {
    if (!s || i < 0 || i >= s->n || !s->rgba[i]) return nullptr;
    const int t = s->size[i];
    const size_t mask_row = (size_t)((t + 31) / 32) * 4;
    std::vector<uint8_t> v;
    wr32(v, 40);
    wr32(v, (uint32_t)t);
    wr32(v, (uint32_t)t * 2);
    wr16(v, 1);
    wr16(v, 32);
    wr32(v, 0);                       // BI_RGB
    wr32(v, (uint32_t)(t * t * 4 + mask_row * t));
    for (int k = 0; k < 4; k++) wr32(v, 0);
    for (int y = t - 1; y >= 0; y--)
        for (int x = 0; x < t; x++) {
            const uint8_t *p = &s->rgba[i][((size_t)y * t + x) * 4];
            v.push_back(p[2]); v.push_back(p[1]); v.push_back(p[0]); v.push_back(p[3]);
        }
    for (int y = t - 1; y >= 0; y--) {
        std::vector<uint8_t> row(mask_row, 0);
        for (int x = 0; x < t; x++)
            if (s->rgba[i][((size_t)y * t + x) * 4 + 3] == 0) row[(size_t)x / 8] |= (uint8_t)(0x80 >> (x & 7));
        v.insert(v.end(), row.begin(), row.end());
    }
    uint8_t *out = (uint8_t *)malloc(v.size());
    if (!out) return nullptr;
    memcpy(out, v.data(), v.size());
    *len = v.size();
    return out;
}

static void dir_entry(std::vector<uint8_t> &v, int t, size_t bytes) {
    v.push_back((uint8_t)(t >= 256 ? 0 : t));
    v.push_back((uint8_t)(t >= 256 ? 0 : t));
    v.push_back(0);                   // colours
    v.push_back(0);
    wr16(v, 1);                       // planes
    wr16(v, 32);                      // bpp
    wr32(v, (uint32_t)bytes);
}

uint8_t *rg_icon_ico_bytes(const rg_icon_set *s, size_t *len) {
    if (!s || s->n <= 0) return nullptr;
    std::vector<std::vector<uint8_t>> img((size_t)s->n);
    for (int i = 0; i < s->n; i++) {
        size_t n = 0;
        uint8_t *b = rg_icon_image_bytes(s, i, &n);
        if (!b) return nullptr;
        img[(size_t)i].assign(b, b + n);
        free(b);
    }
    std::vector<uint8_t> v;
    wr16(v, 0);
    wr16(v, 1);
    wr16(v, (unsigned)s->n);
    uint32_t off = 6 + 16 * (uint32_t)s->n;
    for (int i = 0; i < s->n; i++) {
        dir_entry(v, s->size[i], img[(size_t)i].size());
        wr32(v, off);
        off += (uint32_t)img[(size_t)i].size();
    }
    for (auto &b : img) v.insert(v.end(), b.begin(), b.end());
    uint8_t *out = (uint8_t *)malloc(v.size());
    if (!out) return nullptr;
    memcpy(out, v.data(), v.size());
    *len = v.size();
    return out;
}

uint8_t *rg_icon_group_bytes(const rg_icon_set *s, int first_id, size_t *len) {
    if (!s || s->n <= 0) return nullptr;
    std::vector<uint8_t> v;
    wr16(v, 0);
    wr16(v, 1);
    wr16(v, (unsigned)s->n);
    for (int i = 0; i < s->n; i++) {
        size_t n = 0;
        uint8_t *b = rg_icon_image_bytes(s, i, &n);
        if (!b) return nullptr;
        free(b);
        dir_entry(v, s->size[i], n);
        wr16(v, (unsigned)(first_id + i));
    }
    uint8_t *out = (uint8_t *)malloc(v.size());
    if (!out) return nullptr;
    memcpy(out, v.data(), v.size());
    *len = v.size();
    return out;
}

#ifdef _WIN32
static std::wstring wide(const char *s) {
    int n = MultiByteToWideChar(CP_UTF8, 0, s, -1, nullptr, 0);
    std::wstring w(n > 0 ? (size_t)n : 1, L'\0');
    if (n > 0) MultiByteToWideChar(CP_UTF8, 0, s, -1, &w[0], n);
    w.resize(wcslen(w.c_str()));
    return w;
}

int rg_icon_embed_exe(const char *exe, const rg_icon_set *s, char *err, size_t errcap) {
    if (!exe || !s || s->n <= 0) { say(err, errcap, "bad arguments"); return -1; }
    const WORD lang = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);
    HANDLE h = BeginUpdateResourceW(wide(exe).c_str(), FALSE);
    if (!h) { say(err, errcap, "BeginUpdateResource failed (exe missing, read-only or running?)"); return -1; }
    bool ok = true;
    for (int i = 0; i < s->n && ok; i++) {
        size_t n = 0;
        uint8_t *b = rg_icon_image_bytes(s, i, &n);
        ok = b && UpdateResourceW(h, MAKEINTRESOURCEW(3) /* RT_ICON */, MAKEINTRESOURCEW(1 + i), lang, b, (DWORD)n);
        free(b);
    }
    size_t gn = 0;
    uint8_t *g = ok ? rg_icon_group_bytes(s, 1, &gn) : nullptr;
    ok = ok && g && UpdateResourceW(h, MAKEINTRESOURCEW(14) /* RT_GROUP_ICON */, MAKEINTRESOURCEW(1), lang, g, (DWORD)gn);
    free(g);
    if (!EndUpdateResourceW(h, ok ? FALSE : TRUE) || !ok) {
        say(err, errcap, "UpdateResource failed");
        return -1;
    }
    return 0;
}

static BOOL CALLBACK any_name(HMODULE, LPCWSTR, LPWSTR, LONG_PTR p) {
    *(int *)p = 1;
    return FALSE;
}

int rg_icon_exe_has_icon(const char *exe) {
    HMODULE m = exe ? LoadLibraryExW(wide(exe).c_str(), nullptr, LOAD_LIBRARY_AS_DATAFILE | LOAD_LIBRARY_AS_IMAGE_RESOURCE)
                    : GetModuleHandleW(nullptr);
    if (!m) return 0;
    int found = 0;
    EnumResourceNamesW(m, MAKEINTRESOURCEW(14), any_name, (LONG_PTR)&found);
    if (exe) FreeLibrary(m);
    return found;
}

static HICON g_big, g_small;

static HICON make_icon(const rg_icon_set *s, int want) {
    int best = 0;   // the smallest image >= want, else the largest
    for (int i = 0; i < s->n; i++)
        if (s->size[i] >= want && (s->size[best] < want || s->size[i] < s->size[best])) best = i;
    size_t n = 0;
    uint8_t *b = rg_icon_image_bytes(s, best, &n);
    if (!b) return nullptr;
    HICON ic = CreateIconFromResourceEx(b, (DWORD)n, TRUE, 0x00030000, want, want, LR_DEFAULTCOLOR);
    free(b);
    return ic;
}

int rg_icon_set_window(void *hwnd, const rg_icon_set *s) {
    if (!hwnd || !s || s->n <= 0) return -1;
    HICON big = make_icon(s, GetSystemMetrics(SM_CXICON)), small = make_icon(s, GetSystemMetrics(SM_CXSMICON));
    if (!big || !small) {
        if (big) DestroyIcon(big);
        if (small) DestroyIcon(small);
        return -1;
    }
    SendMessageW((HWND)hwnd, WM_SETICON, ICON_BIG, (LPARAM)big);
    SendMessageW((HWND)hwnd, WM_SETICON, ICON_SMALL, (LPARAM)small);
    rg_icon_window_release();
    g_big = big;
    g_small = small;
    return 0;
}

void rg_icon_window_release(void) {
    if (g_big) DestroyIcon(g_big);
    if (g_small) DestroyIcon(g_small);
    g_big = g_small = nullptr;
}
#else
int rg_icon_embed_exe(const char *, const rg_icon_set *, char *err, size_t errcap) {
    say(err, errcap, "exe icons are Windows only");
    return -1;
}
int rg_icon_exe_has_icon(const char *) { return 0; }
int rg_icon_set_window(void *, const rg_icon_set *) { return -1; }
void rg_icon_window_release(void) {}
#endif

}  // extern "C"
