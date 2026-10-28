// SPDX-License-Identifier: CC0-1.0
// Streaming SHA-1 and SHA-256 (FIPS 180-4), written for rg-extract.
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

namespace rgx {

class Sha1 {
public:
    Sha1() { reset(); }
    void reset();
    void update(const void* data, size_t len);
    std::array<uint8_t, 20> finish();
    std::string finish_hex();
    void block(const uint8_t* p);  // one 64-byte block; used by the shared buffering code

private:
    uint32_t h_[5];
    uint8_t buf_[64];
    size_t buf_len_;
    uint64_t total_;
};

class Sha256 {
public:
    Sha256() { reset(); }
    void reset();
    void update(const void* data, size_t len);
    std::array<uint8_t, 32> finish();
    std::string finish_hex();
    void block(const uint8_t* p);  // one 64-byte block; used by the shared buffering code

private:
    uint32_t h_[8];
    uint8_t buf_[64];
    size_t buf_len_;
    uint64_t total_;
};

std::string to_hex(const uint8_t* p, size_t n);

}  // namespace rgx
