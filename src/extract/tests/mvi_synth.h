// SPDX-License-Identifier: CC0-1.0
// A small synthetic MVI movie (program stream, MPEG-2 headers, SShd/SSbd PCM) and the
// outputs the converter must produce for it. Shared by mvi_tests.cpp and extract_tests.cpp.
#pragma once

#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <vector>

#include "../mvi.h"

namespace mvisynth {

using Bytes = std::vector<uint8_t>;

inline void put(Bytes& v, std::initializer_list<int> b) {
    for (int x : b) v.push_back(uint8_t(x));
}
inline void put(Bytes& v, const Bytes& b) { v.insert(v.end(), b.begin(), b.end()); }
inline void le32(Bytes& v, uint32_t x) { put(v, {int(x & 255), int(x >> 8 & 255), int(x >> 16 & 255), int(x >> 24)}); }

inline Bytes pts_field(uint64_t ts) {
    return {uint8_t(0x21 | ((ts >> 29) & 0x0E)), uint8_t(ts >> 22), uint8_t(((ts >> 14) & 0xFE) | 1),
            uint8_t(ts >> 7), uint8_t(((ts << 1) & 0xFE) | 1)};
}

// MPEG-2 pack header with SCR 0 and no stuffing.
inline Bytes pack() { return {0, 0, 1, 0xBA, 0x44, 0, 4, 0, 4, 1, 0x01, 0x89, 0xC3, 0xF8}; }

inline Bytes pes(uint8_t id, const Bytes& payload, int64_t ts) {
    Bytes h = {0x81, uint8_t(ts >= 0 ? 0x80 : 0), uint8_t(ts >= 0 ? 5 : 0)};
    if (ts >= 0) put(h, pts_field(uint64_t(ts)));
    size_t n = h.size() + payload.size();
    Bytes v = {0, 0, 1, id, uint8_t(n >> 8), uint8_t(n)};
    put(v, h);
    put(v, payload);
    return v;
}

inline Bytes padding(size_t total) {  // a padding packet of `total` bytes (>= 6)
    Bytes v = {0, 0, 1, 0xBE, uint8_t((total - 6) >> 8), uint8_t(total - 6)};
    v.resize(total, 0xFF);
    return v;
}

// Video ES: 512x336 MP@ML sequence header + extension, a GOP and `pics` pictures.
inline Bytes video_es(int pics) {
    Bytes v = {0, 0, 1, 0xB3, 0x20, 0x01, 0x50, 0x24, 0x02, 0xEE, 0x03, 0x80};  // 512x336, 4:3, 29.97
    put(v, {0, 0, 1, 0xB5, 0x14, 0x8A, 0x00, 0x01, 0x00, 0x00});                 // seq ext, MP@ML
    put(v, {0, 0, 1, 0xB8, 0, 8, 0, 0});
    for (int i = 0; i < pics; ++i) put(v, {0, 0, 1, 0x00, 0, 0x0F, 0xFF, 0xF8, 0x12, 0x34, 0, 0, 0});
    return v;
}

struct Synth {
    uint32_t rate = 9000, il = 8;
    int64_t vpts = 9000, apts = 9000;
    int frames = 40;  // per channel (multiple of il/2)
    Bytes plain, expect_mpg, expect_pcm;
};

// Builds plaintext MVI + expected outputs. Audio sample s of channel c = c*1000 + s.
inline void build(Synth& s) {
    Bytes ssbd;
    const uint32_t per = s.il / 2;
    for (int blk = 0; blk < s.frames / int(per); ++blk)
        for (int c = 0; c < 2; ++c)
            for (uint32_t k = 0; k < per; ++k) {
                int v = c * 1000 + blk * int(per) + int(k);
                put(ssbd, {v & 255, v >> 8});
            }
    Bytes audio = {0xFF, 0xA0, 0, 0};
    put(audio, {'S', 'S', 'h', 'd'});
    le32(audio, 24);
    le32(audio, 1);
    le32(audio, s.rate);
    le32(audio, 2);
    le32(audio, s.il);
    le32(audio, 0xFFFFFFFF);
    le32(audio, 0xFFFFFFFF);
    put(audio, {'S', 'S', 'b', 'd'});
    le32(audio, uint32_t(ssbd.size()));
    // Split the audio over two packets: header + the first 10 body bytes, then the rest
    // (so a channel block straddles packets), plus zero fill past the SSbd length.
    Bytes a1 = audio;
    a1.insert(a1.end(), ssbd.begin(), ssbd.begin() + 10);
    Bytes a2 = {0xFF, 0xA0, 0, 0};
    a2.insert(a2.end(), ssbd.begin() + 10, ssbd.end());
    a2.resize(a2.size() + 16, 0);

    Bytes es = video_es(3);
    Bytes v1(es.begin(), es.begin() + 14), v2(es.begin() + 14, es.end());  // split mid-header

    Bytes p, m;
    auto both = [&](const Bytes& b) {
        put(p, b);
        put(m, b);
    };
    both(pack());
    both({0, 0, 1, 0xBB, 0, 6, 0x80, 0x01, 0x01, 0x04, 0xE1, 0xFF});  // system header
    both(pes(0xE0, v1, s.vpts));
    Bytes pa1 = pes(0xBD, a1, s.apts);
    put(p, pa1);
    put(m, padding(pa1.size()));
    both(pes(0xE0, v2, -1));
    Bytes pa2 = pes(0xBD, a2, -1);
    put(p, pa2);
    put(m, padding(pa2.size()));
    size_t fill = 2048 - p.size() % 2048;
    if (fill < 6) fill += 2048;
    both(padding(fill));
    both({0, 0, 1, 0xB9});  // the 4-byte tail past the last sector, like the real files
    s.plain = p;
    s.expect_mpg = m;

    // Expected interleaved PCM after alignment.
    int64_t shift = ((s.apts - s.vpts) * int64_t(s.rate) + (s.apts >= s.vpts ? 45000 : -45000)) / 90000;
    Bytes pcm;
    if (shift > 0) pcm.assign(size_t(shift) * 4, 0);
    for (int f = shift < 0 ? int(-shift) : 0; f < s.frames; ++f)
        for (int c = 0; c < 2; ++c) {
            int v = c * 1000 + f;
            put(pcm, {v & 255, v >> 8});
        }
    s.expect_pcm = pcm;
}

inline Bytes scramble(Bytes b) {
    rgx::mvi::descramble(b.data(), b.size(), 0);
    return b;
}

}  // namespace mvisynth
