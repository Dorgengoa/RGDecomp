// SPDX-License-Identifier: CC0-1.0
#include "hash.h"

#include <cstring>

namespace rgx {

namespace {

inline uint32_t rol(uint32_t x, int n) { return (x << n) | (x >> (32 - n)); }
inline uint32_t ror(uint32_t x, int n) { return (x >> n) | (x << (32 - n)); }
inline uint32_t load_be32(const uint8_t* p) {
    return (uint32_t(p[0]) << 24) | (uint32_t(p[1]) << 16) | (uint32_t(p[2]) << 8) | uint32_t(p[3]);
}
inline void store_be32(uint8_t* p, uint32_t v) {
    p[0] = uint8_t(v >> 24);
    p[1] = uint8_t(v >> 16);
    p[2] = uint8_t(v >> 8);
    p[3] = uint8_t(v);
}

// Shared Merkle-Damgard buffering for both hashes (64-byte blocks, big-endian length).
template <class H>
void md_update(H& h, uint8_t* buf, size_t& buf_len, uint64_t& total, const void* data, size_t len) {
    const uint8_t* p = static_cast<const uint8_t*>(data);
    total += len;
    if (buf_len) {
        size_t take = 64 - buf_len;
        if (take > len) take = len;
        std::memcpy(buf + buf_len, p, take);
        buf_len += take;
        p += take;
        len -= take;
        if (buf_len == 64) {
            h.block(buf);
            buf_len = 0;
        }
    }
    while (len >= 64) {
        h.block(p);
        p += 64;
        len -= 64;
    }
    if (len) {
        std::memcpy(buf, p, len);
        buf_len = len;
    }
}

template <class H>
void md_pad(H& h, uint8_t* buf, size_t buf_len, uint64_t total) {
    uint64_t bits = total * 8;
    buf[buf_len++] = 0x80;
    if (buf_len > 56) {
        std::memset(buf + buf_len, 0, 64 - buf_len);
        h.block(buf);
        buf_len = 0;
    }
    std::memset(buf + buf_len, 0, 56 - buf_len);
    for (int i = 0; i < 8; ++i) buf[56 + i] = uint8_t(bits >> (56 - 8 * i));
    h.block(buf);
}

const uint32_t K256[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
};

}  // namespace

std::string to_hex(const uint8_t* p, size_t n) {
    static const char d[] = "0123456789abcdef";
    std::string s(n * 2, '0');
    for (size_t i = 0; i < n; ++i) {
        s[2 * i] = d[p[i] >> 4];
        s[2 * i + 1] = d[p[i] & 15];
    }
    return s;
}

// ---- SHA-1 ----

void Sha1::reset() {
    h_[0] = 0x67452301;
    h_[1] = 0xEFCDAB89;
    h_[2] = 0x98BADCFE;
    h_[3] = 0x10325476;
    h_[4] = 0xC3D2E1F0;
    buf_len_ = 0;
    total_ = 0;
}

void Sha1::block(const uint8_t* p) {
    uint32_t w[80];
    for (int i = 0; i < 16; ++i) w[i] = load_be32(p + 4 * i);
    for (int i = 16; i < 80; ++i) w[i] = rol(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
    uint32_t a = h_[0], b = h_[1], c = h_[2], d = h_[3], e = h_[4];
    for (int i = 0; i < 80; ++i) {
        uint32_t f, k;
        if (i < 20) {
            f = (b & c) | (~b & d);
            k = 0x5A827999;
        } else if (i < 40) {
            f = b ^ c ^ d;
            k = 0x6ED9EBA1;
        } else if (i < 60) {
            f = (b & c) | (b & d) | (c & d);
            k = 0x8F1BBCDC;
        } else {
            f = b ^ c ^ d;
            k = 0xCA62C1D6;
        }
        uint32_t t = rol(a, 5) + f + e + k + w[i];
        e = d;
        d = c;
        c = rol(b, 30);
        b = a;
        a = t;
    }
    h_[0] += a;
    h_[1] += b;
    h_[2] += c;
    h_[3] += d;
    h_[4] += e;
}

void Sha1::update(const void* data, size_t len) { md_update(*this, buf_, buf_len_, total_, data, len); }

std::array<uint8_t, 20> Sha1::finish() {
    md_pad(*this, buf_, buf_len_, total_);
    std::array<uint8_t, 20> out;
    for (int i = 0; i < 5; ++i) store_be32(out.data() + 4 * i, h_[i]);
    reset();
    return out;
}

std::string Sha1::finish_hex() {
    auto d = finish();
    return to_hex(d.data(), d.size());
}

// ---- SHA-256 ----

void Sha256::reset() {
    h_[0] = 0x6a09e667;
    h_[1] = 0xbb67ae85;
    h_[2] = 0x3c6ef372;
    h_[3] = 0xa54ff53a;
    h_[4] = 0x510e527f;
    h_[5] = 0x9b05688c;
    h_[6] = 0x1f83d9ab;
    h_[7] = 0x5be0cd19;
    buf_len_ = 0;
    total_ = 0;
}

void Sha256::block(const uint8_t* p) {
    uint32_t w[64];
    for (int i = 0; i < 16; ++i) w[i] = load_be32(p + 4 * i);
    for (int i = 16; i < 64; ++i) {
        uint32_t s0 = ror(w[i - 15], 7) ^ ror(w[i - 15], 18) ^ (w[i - 15] >> 3);
        uint32_t s1 = ror(w[i - 2], 17) ^ ror(w[i - 2], 19) ^ (w[i - 2] >> 10);
        w[i] = w[i - 16] + s0 + w[i - 7] + s1;
    }
    uint32_t a = h_[0], b = h_[1], c = h_[2], d = h_[3], e = h_[4], f = h_[5], g = h_[6], h = h_[7];
    for (int i = 0; i < 64; ++i) {
        uint32_t S1 = ror(e, 6) ^ ror(e, 11) ^ ror(e, 25);
        uint32_t ch = (e & f) ^ (~e & g);
        uint32_t t1 = h + S1 + ch + K256[i] + w[i];
        uint32_t S0 = ror(a, 2) ^ ror(a, 13) ^ ror(a, 22);
        uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
        uint32_t t2 = S0 + maj;
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }
    h_[0] += a;
    h_[1] += b;
    h_[2] += c;
    h_[3] += d;
    h_[4] += e;
    h_[5] += f;
    h_[6] += g;
    h_[7] += h;
}

void Sha256::update(const void* data, size_t len) { md_update(*this, buf_, buf_len_, total_, data, len); }

std::array<uint8_t, 32> Sha256::finish() {
    md_pad(*this, buf_, buf_len_, total_);
    std::array<uint8_t, 32> out;
    for (int i = 0; i < 8; ++i) store_be32(out.data() + 4 * i, h_[i]);
    reset();
    return out;
}

std::string Sha256::finish_hex() {
    auto d = finish();
    return to_hex(d.data(), d.size());
}

}  // namespace rgx
