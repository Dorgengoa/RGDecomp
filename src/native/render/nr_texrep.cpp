/* SPDX-License-Identifier: CC0-1.0 */
/* HD texture replacement and texture dumping (nr_texrep.h, docs/TEXTURES.md).  Native-only device
 * (RG_NATIVE_ONLY), compiled to nothing otherwise.
 *
 * Clean-room: the file naming follows the PCSX2 texture-replacement convention as observed from
 * the names PCSX2 itself writes (tools/hdtex/pcsx2_dump.py, research record in docs/TEXTURES.md
 * "Names"); no PCSX2 source was read or used.  XXH3 (xxHash, BSD-2-Clause, third_party/xxhash) and
 * stb_image / stb_image_write (public domain, third_party/stb) are vendored. */
#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY
#include "nr_texrep.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#ifdef _WIN32
#include <direct.h>
#include <windows.h>
#else
#include <dirent.h>
#include <unistd.h>
#endif

#include "nr_gs.h"      /* nr_gs_movie, nr_gs_fields */
#include "nr_gsmem.h"

#ifdef __clang__   /* (vendored headers' -Wextra noise; clang reports some at the end of the file) */
#pragma clang diagnostic ignored "-Wmissing-field-initializers"
#pragma clang diagnostic ignored "-Wunused-function"
#endif
#define XXH_INLINE_ALL
#include "../../../third_party/xxhash/xxhash.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#define STBI_NO_LINEAR
#define STBI_NO_HDR
#define STBI_WINDOWS_UTF8
#include "../../../third_party/stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBIW_WINDOWS_UTF8
#include "../../../third_party/stb/stb_image_write.h"

#define TBITS(v, lo, n) ((uint32_t)(((uint64_t)(v) >> (lo)) & ((1ull << (n)) - 1ull)))

namespace {

const char *kSerial = "SCUS-97490";

/* ------------------------------------------------------------------ files */
static bool is_dir(const std::string &p)
{
    struct stat st;
    return stat(p.c_str(), &st) == 0 && (st.st_mode & S_IFDIR);
}
static void mkdir_p(const std::string &p)
{
    std::string cur;
    for (size_t i = 0; i <= p.size(); i++) {
        if (i == p.size() || p[i] == '/' || p[i] == '\\') {
            if (!cur.empty() && !is_dir(cur)) {
#ifdef _WIN32
                _mkdir(cur.c_str());
#else
                mkdir(cur.c_str(), 0755);
#endif
            }
        }
        if (i < p.size()) cur += p[i];
    }
}
/* the texture root: $RG_TEXTURES, else <exe dir>/textures */
static std::string tex_root()
{
    const char *e = getenv("RG_TEXTURES");
    if (e && *e) return e;
    char buf[1024];
#ifdef _WIN32
    DWORD n = GetModuleFileNameA(NULL, buf, (DWORD)sizeof buf);
    if (!n || n >= sizeof buf) return "textures";
#else
    ssize_t n = readlink("/proc/self/exe", buf, sizeof buf - 1);
    if (n <= 0) return "textures";
    buf[n] = 0;
#endif
    std::string s(buf);
    size_t k = s.find_last_of("/\\");
    return (k == std::string::npos ? std::string() : s.substr(0, k + 1)) + "textures";
}
/* every file under dir (relative names with '/') */
static void list_files(const std::string &dir, const std::string &rel, std::vector<std::string> &out, int depth = 0)
{
    if (depth > 8) return;
#ifdef _WIN32
    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA((dir + "\\*").c_str(), &fd);
    if (h == INVALID_HANDLE_VALUE) return;
    do {
        std::string n = fd.cFileName;
        if (n == "." || n == "..") continue;
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) list_files(dir + "\\" + n, rel + n + "/", out, depth + 1);
        else out.push_back(rel + n);
    } while (FindNextFileA(h, &fd));
    FindClose(h);
#else
    DIR *d = opendir(dir.c_str());
    if (!d) return;
    while (struct dirent *e = readdir(d)) {
        std::string n = e->d_name;
        if (n == "." || n == "..") continue;
        std::string p = dir + "/" + n;
        if (is_dir(p)) list_files(p, rel + n + "/", out, depth + 1);
        else out.push_back(rel + n);
    }
    closedir(d);
#endif
}
static std::string lower(std::string s)
{
    for (char &c : s) c = (char)((c >= 'A' && c <= 'Z') ? c + 32 : c);
    return s;
}

/* ------------------------------------------------------------------ names */
/* A texture's name parts (docs/TEXTURES.md "Names"): the data hash, the CLUT hash (paletted
 * formats only, else 0 and left out of the name) and the TEX0 bits PSM | TW << 6 | TH << 10. */
struct Name {
    uint64_t th, ch;
    uint32_t bits;
    bool has_clut;
    bool operator==(const Name &o) const { return th == o.th && ch == o.ch && bits == o.bits && has_clut == o.has_clut; }
};
struct NameHash {
    size_t operator()(const Name &n) const { return (size_t)(n.th ^ (n.ch * 0x9E3779B97F4A7C15ull) ^ n.bits); }
};
static std::string name_str(const Name &n)
{
    char b[64];
    /* (PCSX2 writes the two hashes without leading zeros, the bits as 8 digits) */
    if (n.has_clut) snprintf(b, sizeof b, "%llx-%llx-%08x", (unsigned long long)n.th, (unsigned long long)n.ch, n.bits);
    else snprintf(b, sizeof b, "%llx-%08x", (unsigned long long)n.th, n.bits);
    return b;
}
static int hexv(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}
/* n digits exactly, or (n = 16) 1 .. 16 digits: hashes are written without leading zeros */
static bool parse_hex(const std::string &s, size_t n, uint64_t *v)
{
    if (n == 16 ? (s.empty() || s.size() > 16) : s.size() != n) return false;
    uint64_t x = 0;
    for (char c : s) {
        int d = hexv(c);
        if (d < 0) return false;
        x = (x << 4) | (uint64_t)d;
    }
    *v = x;
    return true;
}
/* "<hash>[-<CLUT hash>]-<8 hex bits>" (a pack file's base name, extension and suffixes removed;
 * hashes 1 .. 16 hex digits, any case) */
static bool parse_name(const std::string &base, Name *n)
{
    std::vector<std::string> parts;
    size_t s = 0;
    for (size_t i = 0; i <= base.size(); i++)
        if (i == base.size() || base[i] == '-') { parts.push_back(base.substr(s, i - s)); s = i + 1; }
    uint64_t a, b, c;
    if (parts.size() == 2 && parse_hex(parts[0], 16, &a) && parse_hex(parts[1], 8, &c)) {
        n->th = a; n->ch = 0; n->bits = (uint32_t)c; n->has_clut = false;
        return true;
    }
    if (parts.size() == 3 && parse_hex(parts[0], 16, &a) && parse_hex(parts[1], 16, &b) && parse_hex(parts[2], 8, &c)) {
        n->th = a; n->ch = b; n->bits = (uint32_t)c; n->has_clut = true;
        return true;
    }
    return false;
}

/* ------------------------------------------------------------------ GS formats */
enum { CT32 = 0x00, CT24 = 0x01, CT16 = 0x02, CT16S = 0x0A, T8 = 0x13, T4 = 0x14, T8H = 0x1B, T4HL = 0x24, T4HH = 0x2C };
static int indexed(int psm) { return psm == T8 || psm == T4 || psm == T8H || psm == T4HL || psm == T4HH; }
static int known_psm(int psm)
{
    return psm == CT32 || psm == CT24 || psm == CT16 || psm == CT16S || indexed(psm);
}
/* per-format: block size in pixels and the in-block (word, shift) of each pixel (block 0) */
struct BlkTab { uint32_t bwk, bhk, mask; uint8_t word[512], shift[512]; };
static const BlkTab *blk_tab(int psm)
{
    static BlkTab tab[64];
    static std::atomic<int> have[64];
    psm &= 63;
    if (!have[psm].load(std::memory_order_acquire)) {
        BlkTab &t = tab[psm];
        int bpp = nr_psm_bpp(psm);
        uint32_t bwk = 8, bhk = 8;
        if (psm == CT16 || psm == CT16S) { bwk = 16; bhk = 8; }
        else if (psm == T8) { bwk = 16; bhk = 16; }
        else if (psm == T4) { bwk = 32; bhk = 16; }
        (void)bpp;
        t.bwk = bwk; t.bhk = bhk;
        for (uint32_t y = 0; y < bhk; y++)
            for (uint32_t x = 0; x < bwk; x++) {
                uint32_t w, m, sh;
                nr_px_word(psm, 0, 4, x, y, &w, &m, &sh);
                t.word[y * bwk + x] = (uint8_t)(w & 63u);
                t.shift[y * bwk + x] = (uint8_t)sh;
                t.mask = m >> sh;
            }
        have[psm].store(1, std::memory_order_release);
    }
    return &tab[psm];
}

/* ------------------------------------------------------------------ images */
struct Img {
    std::vector<uint32_t> px;
    NrRepImg rep;
    Img *emis = NULL;
};
static void build_mips(Img &im, int w, int h, std::vector<uint32_t> &&l0)
{
    /* level sizes and offsets */
    int levels = 0;
    size_t total = 0;
    int lw = w, lh = h;
    NrRepImg &r = im.rep;
    memset(&r, 0, sizeof r);
    while (levels < NR_REP_MAX_LEVELS) {
        r.off[levels] = (uint32_t)total;
        r.lw[levels] = (uint16_t)lw;
        r.lh[levels] = (uint16_t)lh;
        total += (size_t)lw * lh;
        levels++;
        if (lw == 1 && lh == 1) break;
        lw = lw > 1 ? lw / 2 : 1;
        lh = lh > 1 ? lh / 2 : 1;
    }
    im.px = std::move(l0);
    im.px.resize(total);
    for (int l = 1; l < levels; l++) {
        const uint32_t *s = im.px.data() + r.off[l - 1];
        uint32_t *d = im.px.data() + r.off[l];
        int sw = r.lw[l - 1], sh = r.lh[l - 1], dw = r.lw[l], dh = r.lh[l];
        for (int y = 0; y < dh; y++)
            for (int x = 0; x < dw; x++) {
                int x0 = x * 2 < sw ? x * 2 : sw - 1, x1 = x * 2 + 1 < sw ? x * 2 + 1 : sw - 1;
                int y0 = y * 2 < sh ? y * 2 : sh - 1, y1 = y * 2 + 1 < sh ? y * 2 + 1 : sh - 1;
                uint32_t p[4] = { s[y0 * sw + x0], s[y0 * sw + x1], s[y1 * sw + x0], s[y1 * sw + x1] };
                uint32_t o = 0;
                for (int c = 0; c < 4; c++) {
                    uint32_t acc = 0;
                    for (int k = 0; k < 4; k++) acc += (p[k] >> (8 * c)) & 255u;
                    o |= ((acc + 2u) >> 2) << (8 * c);
                }
                d[y * dw + x] = o;
            }
    }
    r.w = w;
    r.h = h;
    r.levels = levels;
    r.px = im.px.data();
    r.bytes = total * 4;
}

/* --- DDS (uncompressed RGBA / BGRA, BC1 / BC2 / BC3 / BC7 decoded on the CPU) --- */
static void bc_color(const uint8_t *b, uint32_t out[16], bool bc1)
{
    uint32_t c0 = b[0] | (b[1] << 8), c1 = b[2] | (b[3] << 8);
    uint32_t pal[4];
    auto rgb = [](uint32_t c, int *r, int *g, int *bb) {
        *r = (int)((c >> 11) & 31) * 255 / 31; *g = (int)((c >> 5) & 63) * 255 / 63; *bb = (int)(c & 31) * 255 / 31;
    };
    int r0, g0, b0, r1, g1, b1;
    rgb(c0, &r0, &g0, &b0);
    rgb(c1, &r1, &g1, &b1);
    auto pk = [](int r, int g, int bb, int a) { return (uint32_t)r | ((uint32_t)g << 8) | ((uint32_t)bb << 16) | ((uint32_t)a << 24); };
    pal[0] = pk(r0, g0, b0, 255);
    pal[1] = pk(r1, g1, b1, 255);
    if (c0 > c1 || !bc1) {
        pal[2] = pk((2 * r0 + r1) / 3, (2 * g0 + g1) / 3, (2 * b0 + b1) / 3, 255);
        pal[3] = pk((r0 + 2 * r1) / 3, (g0 + 2 * g1) / 3, (b0 + 2 * b1) / 3, 255);
    } else {
        pal[2] = pk((r0 + r1) / 2, (g0 + g1) / 2, (b0 + b1) / 2, 255);
        pal[3] = 0;
    }
    uint32_t idx = b[4] | (b[5] << 8) | (b[6] << 16) | ((uint32_t)b[7] << 24);
    for (int i = 0; i < 16; i++) out[i] = pal[(idx >> (2 * i)) & 3];
}
static void bc3_alpha(const uint8_t *b, uint8_t a[16])
{
    int a0 = b[0], a1 = b[1];
    int pal[8] = { a0, a1 };
    if (a0 > a1) for (int i = 1; i < 7; i++) pal[i + 1] = ((7 - i) * a0 + i * a1) / 7;
    else { for (int i = 1; i < 5; i++) pal[i + 1] = ((5 - i) * a0 + i * a1) / 5; pal[6] = 0; pal[7] = 255; }
    uint64_t bits = 0;
    for (int i = 0; i < 6; i++) bits |= (uint64_t)b[2 + i] << (8 * i);
    for (int i = 0; i < 16; i++) a[i] = (uint8_t)pal[(bits >> (3 * i)) & 7];
}
/* BC7 (Microsoft's documented block format: 8 modes, partitions, anchor indices) */
static const uint8_t bc7_p2[64][16] = {
    {0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1},{0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1},{0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1},{0,0,0,1,0,0,1,1,0,0,1,1,0,1,1,1},
    {0,0,0,0,0,0,0,1,0,0,0,1,0,0,1,1},{0,0,1,1,0,1,1,1,0,1,1,1,1,1,1,1},{0,0,0,1,0,0,1,1,0,1,1,1,1,1,1,1},{0,0,0,0,0,0,0,1,0,0,1,1,0,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1},{0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1},{0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1},{0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1},
    {0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,1},{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1},{0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1},{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
    {0,0,0,0,1,0,0,0,1,1,1,0,1,1,1,1},{0,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,0},{0,1,1,1,0,0,1,1,0,0,0,1,0,0,0,0},
    {0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,1,1,0,0,1,1,1,0},{0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0},{0,1,1,1,0,0,1,1,0,0,1,1,0,0,0,1},
    {0,0,1,1,0,0,0,1,0,0,0,1,0,0,0,0},{0,0,0,0,1,0,0,0,1,0,0,0,1,1,0,0},{0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0},{0,0,1,1,0,1,1,0,0,1,1,0,1,1,0,0},
    {0,0,0,1,0,1,1,1,1,1,1,0,1,0,0,0},{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},{0,1,1,1,0,0,0,1,1,0,0,0,1,1,1,0},{0,0,1,1,1,0,0,1,1,0,0,1,1,1,0,0},
    {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},{0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1},{0,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0},{0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0},
    {0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0},{0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0},{0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,1},{0,1,0,1,1,0,1,0,1,0,1,0,0,1,0,1},
    {0,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0},{0,0,0,1,0,0,1,1,1,1,0,0,1,0,0,0},{0,0,1,1,0,0,1,0,0,1,0,0,1,1,0,0},{0,0,1,1,1,0,1,1,1,1,0,1,1,1,0,0},
    {0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0},{0,0,1,1,0,1,1,0,0,1,1,0,1,1,0,0},{0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0},{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},
    {0,1,0,0,1,1,1,0,0,1,0,0,0,0,0,0},{0,0,1,0,0,1,1,1,0,0,1,0,0,0,0,0},{0,0,0,0,0,0,1,0,0,1,1,1,0,0,1,0},{0,0,0,0,0,1,0,0,1,1,1,0,0,1,0,0},
    {0,1,1,0,1,1,0,0,1,0,0,1,0,0,1,1},{0,0,1,1,0,1,1,0,1,1,0,0,1,0,0,1},{0,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0},{0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,0},
    {0,1,1,0,1,1,0,0,1,1,0,0,1,0,0,1},{0,1,1,0,0,0,1,1,0,0,1,1,1,0,0,1},{0,1,1,1,1,1,1,0,1,0,0,0,0,0,0,1},{0,0,0,1,1,0,0,0,1,1,1,0,0,1,1,1},
    {0,0,0,0,1,1,1,1,0,0,1,1,0,0,1,1},{0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0},{0,0,1,0,0,0,1,0,1,1,1,0,1,1,1,0},{0,1,0,0,0,1,0,0,0,1,1,1,0,1,1,1}};
static const uint8_t bc7_p3[64][16] = {
    {0,0,1,1,0,0,1,1,0,2,2,1,2,2,2,2},{0,0,0,1,0,0,1,1,2,2,1,1,2,2,2,1},{0,0,0,0,2,0,0,1,2,2,1,1,2,2,1,1},{0,2,2,2,0,0,2,2,0,0,1,1,0,1,1,1},
    {0,0,0,0,0,0,0,0,1,1,2,2,1,1,2,2},{0,0,1,1,0,0,1,1,0,0,2,2,0,0,2,2},{0,0,2,2,0,0,2,2,1,1,1,1,1,1,1,1},{0,0,1,1,0,0,1,1,2,2,1,1,2,2,1,1},
    {0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2},{0,0,0,0,1,1,1,1,1,1,1,1,2,2,2,2},{0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2},{0,0,1,2,0,0,1,2,0,0,1,2,0,0,1,2},
    {0,1,1,2,0,1,1,2,0,1,1,2,0,1,1,2},{0,1,2,2,0,1,2,2,0,1,2,2,0,1,2,2},{0,0,1,1,0,1,1,2,1,1,2,2,1,2,2,2},{0,0,1,1,2,0,0,1,2,2,0,0,2,2,2,0},
    {0,0,0,1,0,0,1,1,0,1,1,2,1,1,2,2},{0,1,1,1,0,0,1,1,2,0,0,1,2,2,0,0},{0,0,0,0,1,1,2,2,1,1,2,2,1,1,2,2},{0,0,2,2,0,0,2,2,0,0,2,2,1,1,1,1},
    {0,1,1,1,0,1,1,1,0,2,2,2,0,2,2,2},{0,0,0,1,0,0,0,1,2,2,2,1,2,2,2,1},{0,0,0,0,0,0,1,1,0,1,2,2,0,1,2,2},{0,0,0,0,1,1,0,0,2,2,1,0,2,2,1,0},
    {0,1,2,2,0,1,2,2,0,0,1,1,0,0,0,0},{0,0,1,2,0,0,1,2,1,1,2,2,2,2,2,2},{0,1,1,0,1,2,2,1,1,2,2,1,0,1,1,0},{0,0,0,0,0,1,1,0,1,2,2,1,1,2,2,1},
    {0,0,2,2,1,1,0,2,1,1,0,2,0,0,2,2},{0,1,1,0,0,1,1,0,2,0,0,2,2,2,2,2},{0,0,1,1,0,1,2,2,0,1,2,2,0,0,1,1},{0,0,0,0,2,0,0,0,2,2,1,1,2,2,2,1},
    {0,0,0,0,0,0,0,2,1,1,2,2,1,2,2,2},{0,2,2,2,0,0,2,2,0,0,1,2,0,0,1,1},{0,0,1,1,0,0,1,2,0,0,2,2,0,2,2,2},{0,1,2,0,0,1,2,0,0,1,2,0,0,1,2,0},
    {0,0,0,0,1,1,1,1,2,2,2,2,0,0,0,0},{0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0},{0,1,2,0,2,0,1,2,1,2,0,1,0,1,2,0},{0,0,1,1,2,2,0,0,1,1,2,2,0,0,1,1},
    {0,0,1,1,1,1,2,2,2,2,0,0,0,0,1,1},{0,1,0,1,0,1,0,1,2,2,2,2,2,2,2,2},{0,0,0,0,0,0,0,0,2,1,2,1,2,1,2,1},{0,0,2,2,1,1,2,2,0,0,2,2,1,1,2,2},
    {0,0,2,2,0,0,1,1,0,0,2,2,0,0,1,1},{0,2,2,0,1,2,2,1,0,2,2,0,1,2,2,1},{0,1,0,1,2,2,2,2,2,2,2,2,0,1,0,1},{0,0,0,0,2,1,2,1,2,1,2,1,2,1,2,1},
    {0,1,0,1,0,1,0,1,0,1,0,1,2,2,2,2},{0,2,2,2,0,1,1,1,0,2,2,2,0,1,1,1},{0,0,0,2,1,1,1,2,0,0,0,2,1,1,1,2},{0,0,0,0,2,1,1,2,2,1,1,2,2,1,1,2},
    {0,2,2,2,0,1,1,1,0,1,1,1,0,2,2,2},{0,0,0,2,1,1,1,2,1,1,1,2,0,0,0,2},{0,1,1,0,0,1,1,0,0,1,1,0,2,2,2,2},{0,0,0,0,0,0,0,0,2,1,1,2,2,1,1,2},
    {0,1,1,0,0,1,1,0,2,2,2,2,2,2,2,2},{0,0,2,2,0,0,1,1,0,0,1,1,0,0,2,2},{0,0,2,2,1,1,2,2,1,1,2,2,0,0,2,2},{0,0,0,0,0,0,0,0,0,0,0,0,2,1,1,2},
    {0,0,0,2,0,0,0,1,0,0,0,2,0,0,0,1},{0,2,2,2,1,2,2,2,0,2,2,2,1,2,2,2},{0,1,0,1,2,2,2,2,2,2,2,2,2,2,2,2},{0,1,1,1,2,0,1,1,2,2,0,1,2,2,2,0}};
static const uint8_t bc7_a2[64] = {15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,2,8,2,2,8,8,15,2,8,2,2,8,8,2,2,
                                   15,15,6,8,2,8,15,15,2,8,2,2,2,15,15,6,6,2,6,8,15,15,2,2,15,15,15,15,15,2,2,15};
static const uint8_t bc7_a3a[64] = {3,3,15,15,8,3,15,15,8,8,6,6,6,5,3,3,3,3,8,15,3,3,6,10,5,8,8,6,8,5,15,15,
                                    8,15,3,5,6,10,8,15,15,3,15,5,15,15,15,15,3,15,5,5,5,8,5,10,5,10,8,13,15,12,3,3};
static const uint8_t bc7_a3b[64] = {15,8,8,3,15,15,3,8,15,15,15,15,15,15,15,8,15,8,15,3,15,8,15,8,3,15,6,10,15,15,10,8,
                                    15,3,15,10,10,8,9,10,6,15,8,15,3,6,6,8,15,3,15,15,15,15,15,15,15,15,15,15,3,15,15,8};
static const uint8_t bc7_w2[4] = {0,21,43,64}, bc7_w3[8] = {0,9,18,27,37,46,55,64},
                     bc7_w4[16] = {0,4,9,13,17,21,26,30,34,38,43,47,51,55,60,64};
struct BitR {
    const uint8_t *b; int pos;
    uint32_t get(int n) { uint32_t v = 0; for (int i = 0; i < n; i++, pos++) v |= (uint32_t)((b[pos >> 3] >> (pos & 7)) & 1) << i; return v; }
};
static int bc7_interp(int a, int b, int idx, int bits)
{
    int w = bits == 2 ? bc7_w2[idx] : bits == 3 ? bc7_w3[idx] : bc7_w4[idx];
    return ((64 - w) * a + w * b + 32) >> 6;
}
static void bc7_block(const uint8_t *blk, uint32_t out[16])
{
    static const struct { int ns, pb, rb, isb, cb, ab, epb, spb, ib, ib2; } M[8] = {
        {3,4,0,0,4,0,1,0,3,0},{2,6,0,0,6,0,0,1,3,0},{3,6,0,0,5,0,0,0,2,0},{2,6,0,0,7,0,1,0,2,0},
        {1,0,2,1,5,6,0,0,2,3},{1,0,2,0,7,8,0,0,2,2},{1,0,0,0,7,7,1,0,4,0},{2,6,0,0,5,5,1,0,2,0}};
    int mode = 0;
    while (mode < 8 && !(blk[0] & (1 << mode))) mode++;
    if (mode == 8) { for (int i = 0; i < 16; i++) out[i] = 0; return; }
    BitR br = { blk, mode + 1 };
    const auto &m = M[mode];
    int part = (int)br.get(m.pb), rot = (int)br.get(m.rb), isel = (int)br.get(m.isb);
    int ep[6][4] = {};
    for (int c = 0; c < 3; c++)
        for (int i = 0; i < m.ns * 2; i++) ep[i][c] = (int)br.get(m.cb);
    for (int i = 0; i < m.ns * 2; i++) ep[i][3] = m.ab ? (int)br.get(m.ab) : 255;
    int cbits = m.cb, abits = m.ab;
    if (m.epb) {
        for (int i = 0; i < m.ns * 2; i++) {
            int p = (int)br.get(1);
            for (int c = 0; c < 3; c++) ep[i][c] = (ep[i][c] << 1) | p;
            if (m.ab) ep[i][3] = (ep[i][3] << 1) | p;
        }
        cbits++;
        if (m.ab) abits++;
    } else if (m.spb) {
        for (int s = 0; s < m.ns; s++) {
            int p = (int)br.get(1);
            for (int k = 0; k < 2; k++) {
                for (int c = 0; c < 3; c++) ep[s * 2 + k][c] = (ep[s * 2 + k][c] << 1) | p;
                if (m.ab) ep[s * 2 + k][3] = (ep[s * 2 + k][3] << 1) | p;
            }
        }
        cbits++;
        if (m.ab) abits++;
    }
    for (int i = 0; i < m.ns * 2; i++) {
        for (int c = 0; c < 3; c++) { int v = ep[i][c] << (8 - cbits); ep[i][c] = v | (v >> cbits); }
        if (m.ab) { int v = ep[i][3] << (8 - abits); ep[i][3] = v | (v >> abits); }
    }
    auto subset = [&](int i) -> int { return m.ns == 1 ? 0 : m.ns == 2 ? bc7_p2[part][i] : bc7_p3[part][i]; };
    auto anchor = [&](int i) -> bool {
        if (i == 0) return true;
        if (m.ns == 2) return i == bc7_a2[part];
        if (m.ns == 3) return i == bc7_a3a[part] || i == bc7_a3b[part];
        return false;
    };
    int idx1[16], idx2[16];
    for (int i = 0; i < 16; i++) {
        int s = subset(i);
        bool an = m.ns == 1 ? i == 0 : (i == 0 || (m.ns == 2 ? i == bc7_a2[part] : (s == 1 ? i == bc7_a3a[part] : s == 2 ? i == bc7_a3b[part] : i == 0)));
        (void)anchor;
        idx1[i] = (int)br.get(an ? m.ib - 1 : m.ib);
    }
    if (m.ib2)
        for (int i = 0; i < 16; i++) idx2[i] = (int)br.get(i == 0 ? m.ib2 - 1 : m.ib2);
    for (int i = 0; i < 16; i++) {
        int s = subset(i);
        int *e0 = ep[s * 2], *e1 = ep[s * 2 + 1];
        int c[4];
        if (m.ib2) {
            int ci = isel ? idx2[i] : idx1[i], ai = isel ? idx1[i] : idx2[i];
            int cb = isel ? m.ib2 : m.ib, ab = isel ? m.ib : m.ib2;
            for (int k = 0; k < 3; k++) c[k] = bc7_interp(e0[k], e1[k], ci, cb);
            c[3] = bc7_interp(e0[3], e1[3], ai, ab);
        } else {
            for (int k = 0; k < 4; k++) c[k] = bc7_interp(e0[k], e1[k], idx1[i], m.ib);
        }
        if (rot == 1) { int t = c[0]; c[0] = c[3]; c[3] = t; }
        else if (rot == 2) { int t = c[1]; c[1] = c[3]; c[3] = t; }
        else if (rot == 3) { int t = c[2]; c[2] = c[3]; c[3] = t; }
        out[i] = (uint32_t)c[0] | ((uint32_t)c[1] << 8) | ((uint32_t)c[2] << 16) | ((uint32_t)c[3] << 24);
    }
}
/* level 0 of a DDS file as RGBA8; false when the format is not supported */
static bool load_dds(const std::string &path, std::vector<uint32_t> &out, int *w, int *h, std::string *why)
{
    FILE *f = fopen(path.c_str(), "rb");
    if (!f) { *why = "cannot open"; return false; }
    std::vector<uint8_t> d;
    uint8_t buf[65536];
    size_t n;
    while ((n = fread(buf, 1, sizeof buf, f)) > 0) d.insert(d.end(), buf, buf + n);
    fclose(f);
    if (d.size() < 128 || memcmp(d.data(), "DDS ", 4)) { *why = "not a DDS file"; return false; }
    auto u32 = [&](size_t o) { return (uint32_t)d[o] | ((uint32_t)d[o + 1] << 8) | ((uint32_t)d[o + 2] << 16) | ((uint32_t)d[o + 3] << 24); };
    int H = (int)u32(12), W = (int)u32(16);
    uint32_t pf_flags = u32(80), fourcc = u32(84), rgbbits = u32(88), rmask = u32(92), gmask = u32(96), bmask = u32(100), amask = u32(104);
    size_t off = 128;
    int fmt = -1;   /* 0 rgba, 1 bgra, 2 bc1, 3 bc2, 4 bc3, 5 bc7 */
    auto cc = [](const char *s) { return (uint32_t)s[0] | ((uint32_t)s[1] << 8) | ((uint32_t)s[2] << 16) | ((uint32_t)s[3] << 24); };
    if (pf_flags & 4) {
        if (fourcc == cc("DXT1")) fmt = 2;
        else if (fourcc == cc("DXT2") || fourcc == cc("DXT3")) fmt = 3;
        else if (fourcc == cc("DXT4") || fourcc == cc("DXT5")) fmt = 4;
        else if (fourcc == cc("DX10") && d.size() >= 148) {
            uint32_t dxgi = u32(128);
            off = 148;
            if (dxgi == 28 || dxgi == 29) fmt = 0;            /* R8G8B8A8_UNORM(_SRGB) */
            else if (dxgi == 87 || dxgi == 91) fmt = 1;       /* B8G8R8A8_UNORM(_SRGB) */
            else if (dxgi == 71 || dxgi == 72) fmt = 2;       /* BC1 */
            else if (dxgi == 74 || dxgi == 75) fmt = 3;       /* BC2 */
            else if (dxgi == 77 || dxgi == 78) fmt = 4;       /* BC3 */
            else if (dxgi == 98 || dxgi == 99) fmt = 5;       /* BC7 */
        }
    } else if ((pf_flags & 0x40) && rgbbits == 32) {
        if (rmask == 0xFFu && gmask == 0xFF00u && bmask == 0xFF0000u) fmt = 0;
        else if (rmask == 0xFF0000u && gmask == 0xFF00u && bmask == 0xFFu) fmt = 1;
        if (!(pf_flags & 1)) amask = 0;
        (void)amask;
    }
    if (fmt < 0 || W <= 0 || H <= 0 || W > 16384 || H > 16384) { *why = "unsupported DDS format"; return false; }
    out.assign((size_t)W * H, 0);
    if (fmt <= 1) {
        if (d.size() < off + (size_t)W * H * 4) { *why = "truncated"; return false; }
        for (size_t i = 0; i < (size_t)W * H; i++) {
            uint32_t v = u32(off + 4 * i);
            if (fmt == 1) v = (v & 0xFF00FF00u) | ((v >> 16) & 0xFFu) | ((v & 0xFFu) << 16);
            out[i] = v;
        }
    } else {
        int bw = (W + 3) / 4, bh = (H + 3) / 4, bs = fmt == 2 ? 8 : 16;
        if (d.size() < off + (size_t)bw * bh * bs) { *why = "truncated"; return false; }
        for (int by = 0; by < bh; by++)
            for (int bx = 0; bx < bw; bx++) {
                const uint8_t *b = d.data() + off + ((size_t)by * bw + bx) * bs;
                uint32_t px[16];
                if (fmt == 2) bc_color(b, px, true);
                else if (fmt == 3) {
                    bc_color(b + 8, px, false);
                    for (int i = 0; i < 16; i++) px[i] = (px[i] & 0xFFFFFFu) | ((uint32_t)(((b[i / 2] >> (4 * (i & 1))) & 15) * 17) << 24);
                } else if (fmt == 4) {
                    uint8_t a[16];
                    bc_color(b + 8, px, false);
                    bc3_alpha(b, a);
                    for (int i = 0; i < 16; i++) px[i] = (px[i] & 0xFFFFFFu) | ((uint32_t)a[i] << 24);
                } else bc7_block(b, px);
                for (int y = 0; y < 4; y++)
                    for (int x = 0; x < 4; x++)
                        if (bx * 4 + x < W && by * 4 + y < H) out[(size_t)(by * 4 + y) * W + bx * 4 + x] = px[y * 4 + x];
            }
    }
    *w = W;
    *h = H;
    return true;
}
static bool load_image(const std::string &path, std::vector<uint32_t> &px, int *w, int *h, std::string *why)
{
    std::string l = lower(path);
    if (l.size() > 4 && l.compare(l.size() - 4, 4, ".dds") == 0) return load_dds(path, px, w, h, why);
    int n = 0;
    unsigned char *p = stbi_load(path.c_str(), w, h, &n, 4);
    if (!p) { *why = stbi_failure_reason() ? stbi_failure_reason() : "decode failed"; return false; }
    px.assign((const uint32_t *)p, (const uint32_t *)p + (size_t)*w * *h);
    stbi_image_free(p);
    return true;
}

/* ------------------------------------------------------------------ state */
struct Pack {
    std::string path, epath;   /* replacement file, its emissive map (or empty) */
    std::string name;          /* (rt9) the texture name (NrRepImg.name) */
};
/* per texture name: the replacement (one load however many content keys share the name) */
struct Entry {
    int state = -1;            /* replacement: -1 not looked up, 0 none in the pack, 1 to load, 2 loading, 3 loaded, 4 failed */
    Img *img = NULL;
    const Pack *pack = NULL;
    double used = 0;
};
/* per decoded texture (dec_key: the registers, the content keys and the CLUT) */
struct KEnt {
    int named = 0;             /* 1 named, -1 cannot be named (unknown blocks / format) */
    bool dump_wait = false;    /* named while a movie played (dump mode 1): dumped at a later draw outside one */
    Name name;
    Entry *rep = NULL;
};
/* a file to load: gen = the replacement generation it was queued in (a result of an older one,
 * after the setting went off, is dropped) */
struct LoadJob {
    Entry *e;
    Pack pack;
    uint32_t gen;
};
struct Done {
    Entry *e;
    Img *img;
    uint32_t gen;
};
struct K7 {
    uint32_t v[7];
    bool operator==(const K7 &o) const { return !memcmp(v, o.v, sizeof v); }
};
struct KeyH {
    size_t operator()(const K7 &k) const
    {
        uint64_t h = 1469598103934665603ull;
        for (uint32_t x : k.v) h = (h ^ x) * 1099511628211ull;
        return (size_t)h;
    }
};

/* a texture to dump: its blocks as hashed (raster order), registers and palette; decoded and
 * written on the dump thread */
struct DumpJob {
    std::string path;
    uint64_t tex0 = 0, texa = 0;
    uint16_t clut[512];
    std::vector<uint8_t> blocks;
};
static void decode_blocks(const DumpJob &j, std::vector<uint32_t> &out, int *W, int *H);
struct State {
    int dump = 0, replace = 0;
    std::vector<uint8_t> mem;      /* the shadow: GS local memory as the transfers wrote it */
    std::vector<uint8_t> known;    /* per 256-byte block: 1 = the shadow holds it */
    std::string root;              /* textures/<serial> */
    std::unordered_map<Name, Pack, NameHash> pack;
    std::unordered_map<std::string, std::string> alias;   /* rg-aliases.txt: name -> file */
    std::unordered_map<K7, KEnt, KeyH> ents;
    std::unordered_map<Name, Entry, NameHash> reps;
    std::unordered_set<std::string> dumped;
    /* threads */
    std::mutex mu;
    std::condition_variable cv;
    std::deque<LoadJob> loadq;
    std::deque<struct DumpJob> dumpq;   /* textures to decode and write (dump thread) */
    std::vector<Done> done;             /* loaded (img NULL: failed) */
    uint32_t gen = 1;                   /* replacement generation (+1 each time the setting goes off) */
    std::unordered_set<const NrRepImg *> live;   /* images the backends may read (nr_texrep_valid) */
    std::unordered_set<std::string> ct16;        /* names with a CT16 palette (research count) */
    size_t up_budget = 0;               /* backends' upload bytes per frame (0: whole images at once) */
    int readback = 1;                   /* $RG_TEXREP_READBACK: 0 none, 1 blocks a local copy wrote, 2 all */
    uint8_t why[16384] = {};            /* an unknown block: 1 a target write-back, 2 a local copy */
    std::vector<uint8_t> rb;            /* (the mirror read's buffer) */
    uint64_t n_readback = 0, n_readback_blocks = 0;
    double t_readback = 0;
    std::atomic<int> ndone{ 0 };
    bool quit = false, started = false;
    int busy = 0;   /* dumps being written */
    int alive = 0;  /* worker threads running */
    uint64_t next_id = 1;
    size_t img_bytes = 0, cap = 0;
    double hold_s = 5.0;
    /* stats */
    uint64_t n_named = 0, n_unnamed = 0, n_dumped = 0, n_hits = 0, n_loaded = 0, n_failed = 0, n_evicted = 0,
             n_xfer = 0, n_l2l = 0, n_draw_rep = 0, n_movie_skip = 0, n_released = 0, n_toggles = 0;
    /* backend uploads per frame (nr_texrep_upload): frames with uploads, MB, the worst frame */
    uint64_t up_frames = 0;
    double up_ms = 0, up_max_ms = 0, up_mb = 0, up_max_mb = 0;
    std::vector<float> up_hist;   /* ms per frame with uploads (percentiles at the exit) */
    double t_xfer = 0, t_name = 0;   /* seconds on the GS worker: shadow writes, naming + dump decode */
    int hash_variant = 0;
    int raw = 0;
    int log = 0;   /* $RG_TEXREP_LOG=1: one line per loaded replacement */
};
static State *S;

static double now_s()
{
    using namespace std::chrono;
    return duration<double>(steady_clock::now().time_since_epoch()).count();
}

static void worker()
{
    for (;;) {
        LoadJob job;
        DumpJob dj;
        bool have_l = false, have_d = false;
        {
            std::unique_lock<std::mutex> lk(S->mu);
            S->cv.wait(lk, [] { return S->quit || !S->loadq.empty() || !S->dumpq.empty(); });
            if (S->quit && S->dumpq.empty()) { S->alive--; return; }   /* (pending loads dropped at the exit) */
            if (!S->dumpq.empty()) { dj = std::move(S->dumpq.front()); S->dumpq.pop_front(); have_d = true; S->busy++; }
            else if (!S->loadq.empty()) { job = S->loadq.front(); S->loadq.pop_front(); have_l = true; }
        }
        if (have_d) {
            std::vector<uint32_t> px;
            int w = 0, h = 0;
            decode_blocks(dj, px, &w, &h);
            std::string tmp = dj.path + ".tmp";
            if (stbi_write_png(tmp.c_str(), w, h, 4, px.data(), w * 4)) {
                remove(dj.path.c_str());
                rename(tmp.c_str(), dj.path.c_str());
            }
            std::lock_guard<std::mutex> lk(S->mu);
            S->busy--;
            continue;
        }
        if (have_l) {
            Img *im = NULL;
            std::vector<uint32_t> px;
            int w = 0, h = 0;
            std::string why;
            if (load_image(job.pack.path, px, &w, &h, &why)) {
                im = new Img;
                build_mips(*im, w, h, std::move(px));
                snprintf(im->rep.name, sizeof im->rep.name, "%s", job.pack.name.c_str());   /* (rt9) */
                if (!job.pack.epath.empty()) {
                    std::vector<uint32_t> ep;
                    int ew = 0, eh = 0;
                    std::string ewhy;
                    if (load_image(job.pack.epath, ep, &ew, &eh, &ewhy)) {
                        im->emis = new Img;
                        build_mips(*im->emis, ew, eh, std::move(ep));
                        snprintf(im->emis->rep.name, sizeof im->emis->rep.name, "%s", job.pack.name.c_str());
                        im->rep.emissive = &im->emis->rep;
                    }
                }
            } else {
                fprintf(stderr, "texture replacement: %s: %s\n", job.pack.path.c_str(), why.c_str());
            }
            std::lock_guard<std::mutex> lk(S->mu);
            S->done.push_back({ job.e, im, job.gen });
            S->ndone.fetch_add(1, std::memory_order_release);
        }
    }
}
static void start_thread()
{
    if (S->started) return;
    S->started = true;
    /* 1 .. 4 threads (half the cores): PNG decode and mip chains of a pack's files in parallel;
     * they live for the process (the exit waits only for queued dumps, nr_texrep_stats) */
    unsigned n = std::thread::hardware_concurrency() / 2;
    if (n < 1) n = 1;
    if (n > 4) n = 4;
    for (unsigned i = 0; i < n; i++) {
        { std::lock_guard<std::mutex> lk(S->mu); S->alive++; }
        std::thread(worker).detach();
    }
}

static void free_img(Img *im)
{
    if (!im) return;
    if (im->emis) delete im->emis;
    delete im;
}

/* the pack's index: every file under replacements/ whose base name is a texture name */
static void index_pack()
{
    S->pack.clear();
    S->alias.clear();
    std::string dir = S->root + "/replacements";
    std::vector<std::string> files;
    list_files(dir, "", files);
    std::unordered_map<Name, std::string, NameHash> emis;   /* name -> file of <name>_e.* (emissive hook) */
    size_t n = 0;
    for (const std::string &rel : files) {
        std::string base = rel.substr(rel.find_last_of('/') == std::string::npos ? 0 : rel.find_last_of('/') + 1);
        std::string l = lower(base);
        if (l == "rg-aliases.txt") continue;
        size_t dot = l.find_last_of('.');
        if (dot == std::string::npos) continue;
        std::string ext = l.substr(dot), stem = base.substr(0, dot);
        if (ext != ".png" && ext != ".dds") continue;
        if (lower(stem).find("-mip") != std::string::npos) continue;   /* (own mip chain; supplied levels ignored) */
        bool is_e = stem.size() > 2 && lower(stem.substr(stem.size() - 2)) == "_e";
        Name nm;
        if (is_e) {
            if (parse_name(stem.substr(0, stem.size() - 2), &nm)) emis[nm] = dir + "/" + rel;
            continue;
        }
        if (!parse_name(stem, &nm)) continue;
        Pack p;
        p.path = dir + "/" + rel;
        p.name = name_str(nm);
        auto it = S->pack.find(nm);
        if (it == S->pack.end() || ext == ".dds") S->pack[nm] = p;   /* (.dds first when both) */
        n++;
    }
    /* rg-aliases.txt: "<name> <file relative to replacements/>" (a mapping for names this build
     * computes differently from a pack's, docs/TEXTURES.md "Aliases") */
    FILE *f = fopen((dir + "/rg-aliases.txt").c_str(), "rb");
    if (f) {
        char line[1024];
        while (fgets(line, sizeof line, f)) {
            char a[256], b[768];
            if (line[0] == '#' || sscanf(line, "%255s %767[^\r\n]", a, b) != 2) continue;
            Name nm;
            if (!parse_name(a, &nm)) continue;
            Pack p;
            p.path = dir + "/" + b;
            p.name = name_str(nm);
            S->pack[nm] = p;
            S->alias[a] = b;
        }
        fclose(f);
    }
    /* each name's emissive map (rt9: after the aliases, so an aliased name finds its <name>_e too) */
    for (auto &kv : S->pack) {
        auto e = emis.find(kv.first);
        if (e != emis.end()) kv.second.epath = e->second;
    }
    fprintf(stderr, "texture replacement: %zu replacement file(s), %zu alias(es) in %s\n", n, S->alias.size(), dir.c_str());
}

/* ------------------------------------------------------------------ shadow writes */
/* the pixels of a transfer (rc, its first npx pixels) inside the transfer-local rectangle
 * [cx0, cx1) x [cy0, cy1) into the shadow */
template <int BPP>
static void shadow_write(const gs_mem_rect &rc, int psm, const uint8_t *data, uint32_t npx, uint32_t cx0, uint32_t cy0,
                         uint32_t cx1, uint32_t cy1)
{
    const BlkTab *bt = blk_tab(psm);
    const uint32_t bwk = bt->bwk, bhk = bt->bhk, msk = bt->mask;
    uint32_t *mw = (uint32_t *)S->mem.data();
    if (cx1 > rc.w) cx1 = rc.w;
    for (uint32_t py = cy0; py < cy1; py++) {
        uint32_t i = py * rc.w + cx0;
        if (i >= npx) break;
        uint32_t y = (rc.y + py) & 2047u, cy = y & (bhk - 1), base = 0, bx_last = ~0u;
        const uint8_t *wrow = &bt->word[cy * bwk], *srow = &bt->shift[cy * bwk];
        for (uint32_t px = cx0; px < cx1 && i < npx; px++, i++) {
            uint32_t x = (rc.x + px) & 2047u, bxk = x / bwk;
            if (bxk != bx_last) {
                base = (nr_px_addr(psm, rc.bp, rc.bw ? rc.bw : 1, x & ~(bwk - 1), y & ~(bhk - 1), NULL) >> 2) & 0xFFFC0u;
                bx_last = bxk;
            }
            uint32_t e = x & (bwk - 1), w = base + wrow[e], v;
            if (BPP == 32) memcpy(&v, data + 4u * i, 4);
            else if (BPP == 24) v = (uint32_t)data[3u * i] | ((uint32_t)data[3u * i + 1] << 8) | ((uint32_t)data[3u * i + 2] << 16);
            else if (BPP == 16) v = (uint32_t)data[2u * i] | ((uint32_t)data[2u * i + 1] << 8);
            else if (BPP == 8) v = data[i];
            else v = (data[i >> 1] >> ((i & 1) * 4)) & 15u;
            uint32_t sh = srow[e], m = msk << sh;
            mw[w] = (mw[w] & ~m) | ((v << sh) & m);
        }
    }
}
static void shadow_write_any(const gs_mem_rect &rc, const uint8_t *data, uint32_t npx, uint32_t cx0, uint32_t cy0,
                             uint32_t cx1, uint32_t cy1)
{
    switch (nr_psm_bpp(rc.psm)) {
    case 32: shadow_write<32>(rc, rc.psm, data, npx, cx0, cy0, cx1, cy1); break;
    case 24: shadow_write<24>(rc, rc.psm, data, npx, cx0, cy0, cx1, cy1); break;
    case 16: shadow_write<16>(rc, rc.psm, data, npx, cx0, cy0, cx1, cy1); break;
    case 8: shadow_write<8>(rc, rc.psm, data, npx, cx0, cy0, cx1, cy1); break;
    default: shadow_write<4>(rc, rc.psm, data, npx, cx0, cy0, cx1, cy1); break;
    }
}

/* Lazy shadow writes: a transfer is kept (its bytes) and each block it wholly covers points at it;
 * the block's bytes are made (materialized) only when a texture over it is named.  Texture-pool
 * slots are rewritten many times per frame and named once per content key, so most transfers
 * are never swizzled on the CPU.  Blocks a transfer covers only partly are written at once. */
struct Xf {
    gs_mem_rect rc;
    uint32_t npx = 0, refs = 0;
    std::vector<uint8_t> data;
};
static std::vector<Xf *> g_xf;          /* id - 1 -> transfer (NULL: free slot) */
static std::vector<uint32_t> g_xf_free;
static uint32_t g_blk_ref[16384];      /* transfer id (0: the shadow holds the block) */
static uint16_t g_blk_x[16384], g_blk_y[16384];   /* the block's origin in its transfer (transfer-local pixels) */
static size_t g_xf_bytes;
static void xf_deref(uint32_t id)
{
    Xf *x = g_xf[id - 1];
    if (--x->refs == 0) {
        g_xf_bytes -= x->data.size();
        delete x;
        g_xf[id - 1] = NULL;
        g_xf_free.push_back(id);
    }
}
static void blk_materialize(uint32_t b)
{
    uint32_t id = g_blk_ref[b];
    if (!id) return;
    Xf *x = g_xf[id - 1];
    const BlkTab *bt = blk_tab(x->rc.psm);
    shadow_write_any(x->rc, x->data.data(), x->npx, g_blk_x[b], g_blk_y[b], g_blk_x[b] + bt->bwk, g_blk_y[b] + bt->bhk);
    g_blk_ref[b] = 0;
    xf_deref(id);
}
static void blk_drop(uint32_t b)
{
    uint32_t id = g_blk_ref[b];
    if (!id) return;
    g_blk_ref[b] = 0;
    xf_deref(id);
}
static void materialize_all()
{
    for (uint32_t b = 0; b < 16384; b++) blk_materialize(b);
}

/* ------------------------------------------------------------------ texel reads */
static inline uint32_t rd(int psm, uint32_t bp, uint32_t bw, uint32_t x, uint32_t y)
{
    uint32_t w, m, sh;
    nr_px_word(psm, bp, bw, x, y, &w, &m, &sh);
    return (((const uint32_t *)S->mem.data())[w] & m) >> sh;
}
/* every block the w x h texture at (bp, bw, psm) touches is in the shadow */
/* the device's mirror read (nr_texrep_set_reader): blocks the GPU wrote, read back once when a
 * texture over them is named (PCSX2 names such textures from its memory too) */
static int (*g_reader)(void *user, const uint32_t *runs, int nruns, uint8_t *vram);
static void *g_reader_user;
static bool tex_known(int psm, uint32_t bp, uint32_t bw, int w, int h)
{
    const BlkTab *bt = blk_tab(psm);
    std::vector<uint32_t> miss;
    for (int y = 0; y < h; y += (int)bt->bhk)
        for (int x = 0; x < w; x += (int)bt->bwk) {
            uint32_t a = nr_px_addr(psm, bp, bw, (uint32_t)x, (uint32_t)y, NULL), b = (a >> 8) & 16383u;
            if (!S->known[b]) {
                if (S->readback < 2 && S->why[b] != 2) return false;   /* (a render result: no stable name) */
                miss.push_back(b);
                continue;
            }
            blk_materialize(b);
        }
    if (miss.empty()) return true;
    if (!g_reader || !S->readback) return false;
    double t0 = now_s();
    std::sort(miss.begin(), miss.end());
    miss.erase(std::unique(miss.begin(), miss.end()), miss.end());
    std::vector<uint32_t> runs;   /* (byte offset, length) pairs of consecutive blocks */
    for (uint32_t b : miss) {
        if (!runs.empty() && runs[runs.size() - 2] + runs.back() == b * 256u) runs.back() += 256u;
        else { runs.push_back(b * 256u); runs.push_back(256u); }
    }
    if (S->rb.empty()) S->rb.assign(4u << 20, 0);
    bool ok = g_reader(g_reader_user, runs.data(), (int)(runs.size() / 2), S->rb.data()) != 0;
    if (ok)
        for (uint32_t b : miss) {
            blk_drop(b);
            memcpy(S->mem.data() + (size_t)b * 256u, S->rb.data() + (size_t)b * 256u, 256);
            S->known[b] = 1;
        }
    S->n_readback++;
    S->n_readback_blocks += miss.size();
    S->t_readback += now_s() - t0;
    return ok;
}
/* GS colour -> RGBA8 (GS alpha), TEXA for 24 / 16 bits */
static inline uint32_t c16(uint32_t v, uint64_t texa)
{
    uint32_t r = (v & 31u) << 3, g = ((v >> 5) & 31u) << 3, b = ((v >> 10) & 31u) << 3;
    uint32_t a = (v & 0x8000u) ? TBITS(texa, 32, 8) : ((TBITS(texa, 15, 1) && !(v & 0x7FFFu)) ? 0u : TBITS(texa, 0, 8));
    return r | (g << 8) | (b << 16) | (a << 24);
}
static inline uint32_t c24(uint32_t v, uint64_t texa)
{
    uint32_t a = (TBITS(texa, 15, 1) && !(v & 0xFFFFFFu)) ? 0u : TBITS(texa, 0, 8);
    return (v & 0xFFFFFFu) | (a << 24);
}
/* the palette entries (256 for 8-bit, 16 for 4-bit) as raw values: CT32 words or CT16 halves */
static void clut_raw(uint64_t tex0, const uint16_t *cells, uint32_t *ent, int n)
{
    int cpsm = (int)TBITS(tex0, 51, 4);
    uint32_t csa = TBITS(tex0, 56, 5);
    for (int i = 0; i < n; i++) {
        if (cpsm == CT32 || cpsm == CT24) {
            uint32_t e = ((csa & 15u) * 16u + (uint32_t)i) & 255u;
            ent[i] = (uint32_t)cells[e] | ((uint32_t)cells[e + 256] << 16);
        } else {
            ent[i] = cells[(csa * 16u + (uint32_t)i) & 511u];
        }
    }
}

/* ------------------------------------------------------------------ naming */
/* The data hash (docs/TEXTURES.md "Names"): XXH3-64 of the texture's 256-byte blocks of local
 * memory, block rows top to bottom, each row left to right (a texture narrower / shorter than one
 * block: that one block), the bytes as they lie in memory (swizzled).  Found by
 * tools/hdtex/namecheck.py against PCSX2's own dump names (2026-11-02): independent of TBP / TBW.
 * $RG_TEXREP_HASH=1: the older guess (texels row by row), research only. */
static uint64_t data_hash(int psm, uint32_t bp, uint32_t bw, int w, int h, int variant)
{
    if (variant == 0) {
        const BlkTab *bt = blk_tab(psm);
        int nbx = w / (int)bt->bwk, nby = h / (int)bt->bhk;
        if (nbx < 1) nbx = 1;
        if (nby < 1) nby = 1;
        XXH3_state_t st;
        XXH3_64bits_reset(&st);
        for (int by = 0; by < nby; by++)
            for (int bx = 0; bx < nbx; bx++) {
                uint32_t a = nr_px_addr(psm, bp, bw, (uint32_t)bx * bt->bwk, (uint32_t)by * bt->bhk, NULL) & ~255u & 0x3FFFFFu;
                XXH3_64bits_update(&st, S->mem.data() + a, 256);
            }
        return XXH3_64bits_digest(&st);
    }
    std::vector<uint8_t> buf;
    int bpp = nr_psm_bpp(psm);
    {
        /* the texels row by row at their storage size (4-bit: two per byte, low nibble first) */
        size_t rowb = ((size_t)w * (bpp == 24 ? 32 : bpp) + 7) / 8;
        buf.assign(rowb * h, 0);
        for (int y = 0; y < h; y++) {
            uint8_t *row = &buf[(size_t)y * rowb];
            for (int x = 0; x < w; x++) {
                uint32_t v = rd(psm, bp, bw, (uint32_t)x, (uint32_t)y);
                switch (bpp) {
                case 32: case 24: memcpy(row + 4 * x, &v, 4); break;
                case 16: row[2 * x] = (uint8_t)v; row[2 * x + 1] = (uint8_t)(v >> 8); break;
                case 8: row[x] = (uint8_t)v; break;
                default: row[x >> 1] |= (uint8_t)((v & 15u) << ((x & 1) * 4)); break;
                }
            }
        }
    }
    return XXH3_64bits(buf.data(), buf.size());
}
/* The CLUT hash: XXH3-64 of the palette entries the texture indexes (256 for 8-bit, 16 for 4-bit,
 * from CSA), each as a 32-bit word (CT32 CLUT: the colour; CT16: the 16-bit value zero-extended,
 * unconfirmed: no CT16 palette on the checked screens) */
static uint64_t clut_hash(uint64_t tex0, const uint16_t *cells, int variant)
{
    int psm = (int)TBITS(tex0, 20, 6), cpsm = (int)TBITS(tex0, 51, 4);
    int n = (psm == T8 || psm == T8H) ? 256 : 16;
    uint32_t ent[256];
    clut_raw(tex0, cells, ent, n);
    (void)variant;
    (void)cpsm;
    return XXH3_64bits(ent, (size_t)n * 4);
}
static bool make_name(uint64_t tex0, uint64_t texa, const uint16_t *clut, Name *nm)
{
    (void)texa;
    int psm = (int)TBITS(tex0, 20, 6);
    uint32_t bp = TBITS(tex0, 0, 14), bw = TBITS(tex0, 14, 6);
    int tw = (int)TBITS(tex0, 26, 4), th = (int)TBITS(tex0, 30, 4);
    if (!known_psm(psm) || tw > 10 || th > 10) return false;
    if (bw == 0) bw = 1;
    int w = 1 << tw, h = 1 << th;
    if (!tex_known(psm, bp, bw, w, h)) return false;
    if (indexed(psm) && !clut) return false;
    nm->th = data_hash(psm, bp, bw, w, h, S->hash_variant);
    nm->has_clut = indexed(psm) != 0;
    nm->ch = nm->has_clut ? clut_hash(tex0, clut, S->hash_variant) : 0;
    nm->bits = (uint32_t)psm | ((uint32_t)tw << 6) | ((uint32_t)th << 10);
    int cpsm = (int)TBITS(tex0, 51, 4);
    if (nm->has_clut && cpsm != CT32 && cpsm != CT24) {
        /* a CT16 palette (research: tools/hdtex/ct16scan.py finds the screens that use one) */
        std::string s = name_str(*nm);
        if (S->ct16.insert(s).second && S->log)
            fprintf(stderr, "texture replacement: CT16 palette %s (cpsm %d csa %u)\n", s.c_str(), cpsm, TBITS(tex0, 56, 5));
    }
    return true;
}

/* a (named, so materialized) texture's blocks in raster order */
static void tex_blocks(uint64_t tex0, std::vector<uint8_t> &out)
{
    int psm = (int)TBITS(tex0, 20, 6);
    uint32_t bp = TBITS(tex0, 0, 14), bw = TBITS(tex0, 14, 6);
    if (!bw) bw = 1;
    int w = 1 << TBITS(tex0, 26, 4), h = 1 << TBITS(tex0, 30, 4);
    const BlkTab *bt = blk_tab(psm);
    int nbx = w / (int)bt->bwk, nby = h / (int)bt->bhk;
    if (nbx < 1) nbx = 1;
    if (nby < 1) nby = 1;
    out.resize((size_t)nbx * nby * 256);
    for (int by = 0; by < nby; by++)
        for (int bx = 0; bx < nbx; bx++) {
            uint32_t a = nr_px_addr(psm, bp, bw, (uint32_t)bx * bt->bwk, (uint32_t)by * bt->bhk, NULL) & ~255u & 0x3FFFFFu;
            memcpy(out.data() + ((size_t)by * nbx + bx) * 256, S->mem.data() + a, 256);
        }
}
/* the texture as RGBA8 (GS alpha) for a dump, from its blocks in raster order (the bytes the
 * data hash reads: each block's in-block layout is the same everywhere) */
static void decode_blocks(const DumpJob &j, std::vector<uint32_t> &out, int *W, int *H)
{
    uint64_t tex0 = j.tex0, texa = j.texa;
    int psm = (int)TBITS(tex0, 20, 6), cpsm = (int)TBITS(tex0, 51, 4);
    int w = 1 << TBITS(tex0, 26, 4), h = 1 << TBITS(tex0, 30, 4);
    const BlkTab *bt = blk_tab(psm);
    int nbx = w / (int)bt->bwk;
    if (nbx < 1) nbx = 1;
    uint32_t pal[256];
    if (indexed(psm)) {
        uint32_t ent[256];
        int n = (psm == T8 || psm == T8H) ? 256 : 16;
        clut_raw(tex0, j.clut, ent, n);
        for (int i = 0; i < n; i++) pal[i] = (cpsm == CT32 || cpsm == CT24) ? ent[i] : c16(ent[i], texa);
    }
    out.resize((size_t)w * h);
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) {
            size_t bi = (size_t)(y / (int)bt->bhk) * nbx + (size_t)(x / (int)bt->bwk);
            if ((bi + 1) * 256 > j.blocks.size()) { out[(size_t)y * w + x] = 0; continue; }
            uint32_t e = (uint32_t)(y % (int)bt->bhk) * bt->bwk + (uint32_t)(x % (int)bt->bwk), wd;
            memcpy(&wd, j.blocks.data() + bi * 256 + bt->word[e] * 4u, 4);
            uint32_t v = (wd >> bt->shift[e]) & bt->mask, c;
            switch (psm) {
            case CT32: c = v; break;
            case CT24: c = c24(v, texa); break;
            case CT16: case CT16S: c = c16(v, texa); break;
            default: c = pal[v & 255u]; break;
            }
            out[(size_t)y * w + x] = c;
        }
    *W = w;
    *H = h;
}

/* research dump ($RG_TEXREP_RAW=1): registers, CLUT cells and every 8 KB page the texture's
 * blocks lie in, for tools/hdtex/namecheck.py */
static void raw_dump(const std::string &path, uint64_t tex0, uint64_t texa, const uint16_t *clut)
{
    FILE *f = fopen(path.c_str(), "wb");
    if (!f) return;
    int psm = (int)TBITS(tex0, 20, 6);
    uint32_t bp = TBITS(tex0, 0, 14), bw = TBITS(tex0, 14, 6);
    if (!bw) bw = 1;
    int w = 1 << TBITS(tex0, 26, 4), h = 1 << TBITS(tex0, 30, 4);
    std::vector<uint8_t> pg(512, 0);
    const BlkTab *bt = blk_tab(psm);
    for (int y = 0; y < h; y += (int)bt->bhk)
        for (int x = 0; x < w; x += (int)bt->bwk) pg[(nr_px_addr(psm, bp, bw, (uint32_t)x, (uint32_t)y, NULL) >> 13) & 511u] = 1;
    uint32_t np = 0;
    for (uint8_t v : pg) np += v;
    fwrite("RGTX", 1, 4, f);
    fwrite(&tex0, 8, 1, f);
    fwrite(&texa, 8, 1, f);
    uint16_t c0[512] = {};
    fwrite(clut ? clut : c0, 2, 512, f);
    fwrite(&np, 4, 1, f);
    for (uint32_t p = 0; p < 512; p++)
        if (pg[p]) {
            for (uint32_t b = p * 32u; b < p * 32u + 32u; b++) blk_materialize(b);
            fwrite(&p, 4, 1, f);
            fwrite(S->mem.data() + (size_t)p * 8192u, 1, 8192, f);
        }
    fclose(f);
}

static void evict(double t)
{
    if (S->img_bytes <= S->cap) return;
    /* least recently drawn first, never one drawn in the last hold_s seconds (recorded draws of
     * the interpolated presentation still point at it) */
    std::vector<Entry *> v;
    for (auto &kv : S->reps)
        if (kv.second.state == 3 && kv.second.img && t - kv.second.used > S->hold_s) v.push_back(&kv.second);
    std::sort(v.begin(), v.end(), [](const Entry *a, const Entry *b) { return a->used < b->used; });
    for (Entry *e : v) {
        if (S->img_bytes <= S->cap * 3 / 4) break;
        size_t b = e->img->rep.bytes + (e->img->emis ? e->img->emis->rep.bytes : 0);
        S->live.erase(&e->img->rep);
        if (e->img->emis) S->live.erase(&e->img->emis->rep);
        free_img(e->img);
        e->img = NULL;
        e->state = 1;   /* (loaded again on its next draw) */
        S->img_bytes -= b;
        S->n_evicted++;
    }
}

static void collect()
{
    if (!S->ndone.load(std::memory_order_acquire)) return;
    std::vector<Done> d;
    {
        std::lock_guard<std::mutex> lk(S->mu);
        d.swap(S->done);
        S->ndone.store(0, std::memory_order_relaxed);
    }
    for (Done &p : d) {
        if (p.gen != S->gen) { free_img(p.img); continue; }   /* (queued before the setting went off) */
        if (!p.img) { p.e->state = 4; S->n_failed++; continue; }
        p.img->rep.id = S->next_id++;
        if (p.img->emis) p.img->emis->rep.id = S->next_id++;
        p.e->img = p.img;
        p.e->state = 3;
        S->live.insert(&p.img->rep);
        if (p.img->emis) S->live.insert(&p.img->emis->rep);
        S->img_bytes += p.img->rep.bytes + (p.img->emis ? p.img->emis->rep.bytes : 0);
        S->n_loaded++;
        if (S->log)
            fprintf(stderr, "texture replacement: loaded %s (%dx%d, %d levels%s)\n", p.e->pack ? p.e->pack->path.c_str() : "?",
                    p.img->rep.w, p.img->rep.h, p.img->rep.levels, p.img->emis ? ", emissive map" : "");
    }
}

/* replacement off: every loaded image freed (the backends drop their copies: GpuBackend::
 * nr_rep_clear; a recorded draw that still points at one finds it invalid: nr_texrep_valid),
 * queued loads dropped, loads in flight discarded when they finish (gen) */
static void release_reps()
{
    collect();
    {
        std::lock_guard<std::mutex> lk(S->mu);
        S->loadq.clear();
    }
    S->gen++;
    for (auto &kv : S->reps)
        if (kv.second.img) {
            Img *im = kv.second.img;
            S->img_bytes -= im->rep.bytes + (im->emis ? im->emis->rep.bytes : 0);
            free_img(im);
            S->n_released++;
        }
    S->live.clear();
    S->reps.clear();
    for (auto &kv : S->ents) kv.second.rep = NULL;
}

/* both modes off: the CPU copy of local memory is freed (a later enable starts a new one from
 * the mirror: a copy kept while nothing updated it would name textures from stale bytes) */
static void free_shadow()
{
    for (uint32_t b = 0; b < 16384; b++) blk_drop(b);
    std::vector<uint8_t>().swap(S->mem);
    std::vector<uint8_t>().swap(S->known);
    std::vector<uint8_t>().swap(S->rb);
}

/* one texture's dump (dump mode): queued for the dump threads unless written before */
static void dump_one(const Name &nm, uint64_t tex0, uint64_t texa, const uint16_t *clut)
{
    std::string nstr = name_str(nm);
    if (!S->dumped.insert(nstr).second) return;
    std::string path = S->root + "/dumps/" + nstr + ".png";
    struct stat st;
    if (stat(path.c_str(), &st) == 0) return;
    DumpJob j;
    j.path = path;
    j.tex0 = tex0;
    j.texa = texa;
    if (clut) memcpy(j.clut, clut, sizeof j.clut);
    else memset(j.clut, 0, sizeof j.clut);
    tex_blocks(tex0, j.blocks);
    if (S->raw) raw_dump(S->root + "/dumps/" + nstr + ".rgtx", tex0, texa, clut);
    {
        std::lock_guard<std::mutex> lk(S->mu);
        S->dumpq.push_back(std::move(j));
    }
    S->cv.notify_one();
    S->n_dumped++;
}

} /* namespace */

extern "C" {

int nr_texrep_on(void) { return S && (S->dump || S->replace); }

int nr_texrep_config(int dump, int replace)
{
    if (!dump && !replace && !S) return 0;
    int fresh = 0;
    if (!S) {
        S = new State;
        const char *hv = getenv("RG_TEXREP_HASH");
        S->hash_variant = hv ? atoi(hv) : 0;
        const char *rw = getenv("RG_TEXREP_RAW");
        S->raw = rw && rw[0] == '1';
        const char *lg = getenv("RG_TEXREP_LOG");
        S->log = lg ? atoi(lg) : 0;   /* (2: also one line per TEX0 that cannot be named) */
        const char *mb = getenv("RG_TEXREP_MB");
        size_t def = sizeof(void *) >= 8 ? 2048 : 512;
        S->cap = (size_t)(mb ? atol(mb) : (long)def) << 20;
        S->root = tex_root() + "/" + kSerial;
        /* the backends' upload rate (staged uploads, docs/TEXTURES.md "How it works"): MB per
         * frame, 0 = each image whole in its first draw (the hdtex behaviour) */
        const char *rbk = getenv("RG_TEXREP_READBACK");
        S->readback = rbk ? atoi(rbk) : 1;
        const char *um = getenv("RG_TEXREP_UPLOAD_MB");
        S->up_budget = (size_t)(um ? atof(um) * 1048576.0 : 2.0 * 1048576.0);
    }
    int was = S->dump || S->replace;
    if (was) S->n_toggles += (dump != S->dump) + (replace != S->replace);
    if (!replace && S->replace) release_reps();
    if (!dump && !replace) {
        if (was) free_shadow();
        S->dump = S->replace = 0;
        return 0;
    }
    /* dump turned on: textures named before (replacement only / an earlier dump session) are
     * looked at again (a texture is dumped when it is named) */
    if (dump && !S->dump) S->ents.clear();
    if ((dump || replace) && S->mem.empty()) {
        S->mem.assign(4u << 20, 0);
        S->known.assign(16384, 1);   /* (never written = zero, as on the PS2 at power-on; GPU writes unknown) */
        fresh = 1;
    }
    if (replace && !S->replace) {
        index_pack();
        /* a new index: names seen before are looked up again */
        for (auto &kv : S->reps)
            if (kv.second.state != 2 && kv.second.state != 3) { kv.second.state = -1; kv.second.pack = NULL; }
    }
    if (dump && !S->dump) mkdir_p(S->root + "/dumps");
    S->dump = dump;
    S->replace = replace;
    if ((dump || replace) && !was) start_thread();
    return fresh;
}

void nr_texrep_xfer(const gs_mem_rect *rc0, const uint8_t *data, uint32_t npx)
{
    if (!S || S->mem.empty()) return;
    gs_mem_rect rc = *rc0;
    int psm = rc.psm, bpp = nr_psm_bpp(psm);
    if (!bpp || !rc.w || !rc.h || !npx) return;
    if (!rc.bw) rc.bw = 1;
    if ((uint64_t)npx > (uint64_t)rc.w * rc.h) npx = rc.w * rc.h;
    S->n_xfer++;
    double t0 = now_s();
    const BlkTab *bt = blk_tab(psm);
    const uint32_t bwk = bt->bwk, bhk = bt->bhk, full_rows = npx / rc.w, rows = (npx + rc.w - 1) / rc.w;
    const bool fullfmt = !(psm == CT24 || psm == T8H || psm == T4HL || psm == T4HH) && rc.x + rc.w <= 2048 && rc.y + rows <= 2048;
    uint32_t id = 0;
    Xf *x = NULL;
    for (uint32_t yb = rc.y & ~(bhk - 1); yb < rc.y + rows; yb += bhk)
        for (uint32_t xb = rc.x & ~(bwk - 1); xb < rc.x + rc.w; xb += bwk) {
            uint32_t b = (nr_px_addr(psm, rc.bp, rc.bw, xb & 2047u, yb & 2047u, NULL) >> 8) & 16383u;
            S->known[b] = 1;
            bool full = fullfmt && xb >= rc.x && xb + bwk <= rc.x + rc.w && yb >= rc.y && yb + bhk <= rc.y + full_rows;
            if (!full) {
                /* partly covered: the older bytes first, then this transfer's pixels there */
                blk_materialize(b);
                uint32_t lx0 = xb > rc.x ? xb - rc.x : 0, ly0 = yb > rc.y ? yb - rc.y : 0;
                shadow_write_any(rc, data, npx, lx0, ly0, xb + bwk - rc.x, yb + bhk - rc.y);
                continue;
            }
            if (!x) {
                x = new Xf;
                x->rc = rc;
                x->npx = npx;
                x->data.assign(data, data + (((uint64_t)npx * (uint32_t)bpp + 7) / 8));
                g_xf_bytes += x->data.size();
                if (!g_xf_free.empty()) { id = g_xf_free.back(); g_xf_free.pop_back(); g_xf[id - 1] = x; }
                else { g_xf.push_back(x); id = (uint32_t)g_xf.size(); }
            }
            blk_drop(b);
            g_blk_ref[b] = id;
            g_blk_x[b] = (uint16_t)(xb - rc.x);
            g_blk_y[b] = (uint16_t)(yb - rc.y);
            x->refs++;
        }
    if (x && !x->refs) { g_xf_bytes -= x->data.size(); delete x; g_xf[id - 1] = NULL; g_xf_free.push_back(id); }
    /* (kept bytes past 64 MB: everything is made, the kept transfers freed) */
    if (g_xf_bytes > (64u << 20)) materialize_all();
    S->t_xfer += now_s() - t0;
}

void nr_texrep_gpu_write(uint32_t bp, uint32_t bw, int psm, int x0, int y0, int x1, int y1, int copy)
{
    if (!S || S->known.empty()) return;
    const BlkTab *bt = blk_tab(psm);
    int bwk = (int)bt->bwk, bhk = (int)bt->bhk;
    if (x0 < 0) x0 = 0;
    if (y0 < 0) y0 = 0;
    if (x1 > 2048) x1 = 2048;
    if (y1 > 2048) y1 = 2048;
    if (bw == 0) bw = 1;
    for (int by = y0 / bhk; by <= (y1 - 1) / bhk && y1 > y0; by++)
        for (int bx = x0 / bwk; bx <= (x1 - 1) / bwk && x1 > x0; bx++) {
            uint32_t b = (nr_px_addr(psm, bp, bw, (uint32_t)(bx * bwk), (uint32_t)(by * bhk), NULL) >> 8) & 16383u;
            S->known[b] = 0;
            S->why[b] = copy ? 2 : 1;
            blk_drop(b);
        }
}

int nr_texrep_copy(const gs_mem_rect *s, uint32_t dbp, uint32_t dbw, int dpsm, uint32_t dx, uint32_t dy)
{
    if (!S || S->mem.empty() || !s->w || !s->h) return 0;
    int spsm = s->psm;
    if (!known_psm(spsm) || !known_psm(dpsm) || nr_psm_bpp(spsm) != nr_psm_bpp(dpsm)) return 0;
    uint32_t sbw = s->bw ? s->bw : 1;
    if (!dbw) dbw = 1;
    double t0 = now_s();
    uint32_t *mw = (uint32_t *)S->mem.data();
    /* the source as the shadow holds it (every block known), then the destination written pixel
     * by pixel (the GS's own addressing, 2048 wrap); a destination block wholly written is known */
    std::vector<uint32_t> px((size_t)s->w * s->h);
    for (uint32_t y = 0; y < s->h; y++)
        for (uint32_t x = 0; x < s->w; x++) {
            uint32_t w, m, sh;
            nr_px_word(spsm, s->bp, sbw, (s->x + x) & 2047u, (s->y + y) & 2047u, &w, &m, &sh);
            uint32_t b = (w >> 6) & 16383u;
            if (!S->known[b]) { S->t_xfer += now_s() - t0; return 0; }
            blk_materialize(b);
            px[(size_t)y * s->w + x] = (mw[w] & m) >> sh;
        }
    static uint16_t cnt[16384];
    std::vector<uint32_t> touched;
    for (uint32_t y = 0; y < s->h; y++)
        for (uint32_t x = 0; x < s->w; x++) {
            uint32_t w, m, sh;
            nr_px_word(dpsm, dbp, dbw, (dx + x) & 2047u, (dy + y) & 2047u, &w, &m, &sh);
            uint32_t b = (w >> 6) & 16383u;
            if (!cnt[b]) { touched.push_back(b); blk_materialize(b); }
            cnt[b]++;
            mw[w] = (mw[w] & ~m) | ((px[(size_t)y * s->w + x] << sh) & m);
        }
    const BlkTab *bt = blk_tab(dpsm);
    for (uint32_t b : touched) {
        if (cnt[b] >= bt->bwk * bt->bhk) S->known[b] = 1;   /* (partly written: known only if it was) */
        cnt[b] = 0;
    }
    S->n_l2l++;
    S->t_xfer += now_s() - t0;
    return 1;
}

void nr_texrep_load_all(const uint8_t *vram)
{
    if (!S || S->mem.empty()) return;
    for (uint32_t b = 0; b < 16384; b++) blk_drop(b);
    memcpy(S->mem.data(), vram, 4u << 20);
    memset(S->known.data(), 1, S->known.size());
}

int nr_texrep_name(uint64_t tex0, uint64_t texa, const uint16_t *clut, char *out, size_t n)
{
    Name nm;
    if (!S || S->mem.empty() || !make_name(tex0, texa, clut, &nm)) return 0;
    snprintf(out, n, "%s", name_str(nm).c_str());
    return 1;
}

const NrRepImg *nr_texrep_draw(const uint32_t key[8], uint64_t tex0, uint64_t texa, const uint16_t *clut, int clut_known)
{
    if (!S || !(S->dump || S->replace)) return NULL;
    collect();
    K7 k;
    memcpy(k.v, key, sizeof k.v);
    KEnt &ke = S->ents[k];
    double t = now_s();
    if (!ke.named) {
        KEnt &e = ke;
        struct Tm { double t0; ~Tm() { S->t_name += now_s() - t0; } } tm_{ now_s() };
        Name nm;
        if (make_name(tex0, texa, clut_known ? clut : NULL, &nm)) {
            e.named = 1;
            e.name = nm;
            S->n_named++;
        } else {
            e.named = -1;
            if (S->log >= 2) {
                static std::unordered_set<uint64_t> seen;
                if (seen.insert(tex0).second)
                    fprintf(stderr, "texture replacement: cannot name TEX0 %016llx (bits %08x, palette %s)\n", (unsigned long long)tex0,
                            (unsigned)(TBITS(tex0, 20, 6) | (TBITS(tex0, 26, 4) << 6) | (TBITS(tex0, 30, 4) << 10)),
                            clut_known ? "known" : "GPU-loaded");
            }
            S->n_unnamed++;
            /* (a later draw of the same key cannot do better: the key is its content) */
        }
        if (e.named == 1 && S->dump) {
            if (S->dump == 1 && nr_gs_movie) {
                /* a movie plays: its frames are not dumped (PCSX2's default); anything else
                 * drawn now is dumped at its next draw outside a movie */
                e.dump_wait = true;
                S->n_movie_skip++;
            } else {
                dump_one(e.name, tex0, texa, clut);
            }
        }
    } else if (ke.dump_wait && S->dump && !(S->dump == 1 && nr_gs_movie)) {
        Name nm;
        ke.dump_wait = false;
        if (make_name(tex0, texa, clut_known ? clut : NULL, &nm) && nm == ke.name) dump_one(nm, tex0, texa, clut);
    }
    if (!S->replace || ke.named != 1) return NULL;
    if (!ke.rep) ke.rep = &S->reps[ke.name];
    Entry &e = *ke.rep;
    if (e.state < 0) {
        auto it = S->pack.find(ke.name);
        if (it == S->pack.end()) { e.state = 0; return NULL; }
        e.pack = &it->second;
        e.state = 1;
        S->n_hits++;
    }
    if (e.state == 1) {
        e.state = 2;
        {
            std::lock_guard<std::mutex> lk(S->mu);
            S->loadq.push_back({ &e, *e.pack, S->gen });
        }
        S->cv.notify_one();
        e.used = t;
        return NULL;
    }
    if (e.state != 3 || !e.img) return NULL;
    e.used = t;
    S->n_draw_rep++;
    evict(t);
    return e.img ? &e.img->rep : NULL;
}

void nr_texrep_set_reader(int (*fn)(void *user, const uint32_t *runs, int nruns, uint8_t *vram), void *user)
{
    g_reader = fn;
    g_reader_user = user;
}

int nr_texrep_valid(const NrRepImg *im) { return S && im && S->live.count(im) != 0; }

int nr_texrep_key_name(const uint32_t key[8], char *out, size_t n)
{
    if (!S || !(S->dump || S->replace) || !out || !n) return 0;
    K7 k;
    memcpy(k.v, key, sizeof k.v);
    auto it = S->ents.find(k);
    if (it == S->ents.end() || it->second.named != 1) return 0;
    snprintf(out, n, "%s", name_str(it->second.name).c_str());
    return 1;
}

size_t nr_texrep_upload_budget(void) { return S ? S->up_budget : 0; }

uint32_t nr_texrep_frame(void) { return nr_gs_fields; }

void nr_texrep_upload(double ms, size_t bytes)
{
    if (!S || !bytes) return;
    double mb = (double)bytes / 1048576.0;
    S->up_frames++;
    S->up_ms += ms;
    S->up_mb += mb;
    if (ms > S->up_max_ms) S->up_max_ms = ms;
    if (mb > S->up_max_mb) S->up_max_mb = mb;
    if (S->up_hist.size() < 1000000) S->up_hist.push_back((float)ms);
}

void nr_texrep_stats(FILE *f)
{
    if (!S) return;
    /* queued dumps reach the disk before the exit (at most 60 s) */
    for (int i = 0; i < 6000; i++) {
        {
            std::lock_guard<std::mutex> lk(S->mu);
            if (S->dumpq.empty() && S->busy == 0) break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    /* the workers stop (loads not started are dropped) before the process exits: a decode still
     * running while the CRT shuts down crashed the exit */
    {
        std::lock_guard<std::mutex> lk(S->mu);
        S->quit = true;
        S->loadq.clear();
    }
    S->cv.notify_all();
    for (int i = 0; i < 3000; i++) {
        {
            std::lock_guard<std::mutex> lk(S->mu);
            if (S->alive == 0) break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    {
        std::lock_guard<std::mutex> lk(S->mu);
        if (S->alive == 0) { S->quit = false; S->started = false; }   /* (a later renderer starts them again) */
    }
    std::vector<float> hs = S->up_hist;
    std::sort(hs.begin(), hs.end());
    auto pct = [&](double q) { return hs.empty() ? 0.0 : (double)hs[(size_t)(q * (double)(hs.size() - 1) + 0.5)]; };
    int over4 = 0;
    for (float v : hs) over4 += v > 4.0f;
    fprintf(f, "texture replacement: dump %d replace %d, %llu transfers + %llu local copies shadowed, %llu textures named, %llu not nameable, "
               "%llu dumped, %llu movie-time textures not dumped, %zu CT16-palette names, %zu pack files, %llu matched, %llu loaded, %llu failed, "
               "%llu evicted, %llu released, %llu replaced draws, %zu MB loaded, %llu toggles; worker time: shadow %.2f s, naming %.2f s, "
               "%llu mirror reads (%llu blocks) %.2f s; "
               "uploads: %llu frames, %.1f MB, %.2f ms, worst frame %.2f ms / %.1f MB (budget %.1f MB/frame), ms per frame p50 %.2f p95 %.2f p99 %.2f, %d frames over 4 ms\n",
            S->dump, S->replace, (unsigned long long)S->n_xfer, (unsigned long long)S->n_l2l, (unsigned long long)S->n_named, (unsigned long long)S->n_unnamed,
            (unsigned long long)S->n_dumped, (unsigned long long)S->n_movie_skip, S->ct16.size(), S->pack.size(),
            (unsigned long long)S->n_hits, (unsigned long long)S->n_loaded, (unsigned long long)S->n_failed,
            (unsigned long long)S->n_evicted, (unsigned long long)S->n_released, (unsigned long long)S->n_draw_rep, S->img_bytes >> 20,
            (unsigned long long)S->n_toggles, S->t_xfer, S->t_name, (unsigned long long)S->n_readback,
            (unsigned long long)S->n_readback_blocks, S->t_readback, (unsigned long long)S->up_frames, S->up_mb, S->up_ms, S->up_max_ms,
            S->up_max_mb, (double)S->up_budget / 1048576.0, pct(0.50), pct(0.95), pct(0.99), over4);
}

} /* extern "C" */

#endif /* RG_NATIVE_ONLY */
