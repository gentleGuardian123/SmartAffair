#pragma once

#include "seal/seal.h"
#include <vector>

typedef std::vector<seal::Plaintext> Database;
typedef std::vector<seal::Ciphertext> PirQuery;
typedef seal::Ciphertext PirReply;

struct PirParams {
    std::uint64_t tot_data_num;  // |N|, the total number of data in database.
    std::uint32_t tot_data_dim;  // |B| = log|N|.
    std::uint32_t usr_data_num;  // |M|, the maximum number of data for one user.
    std::uint32_t usr_data_dim;
    std::uint32_t data_size; 
};

void gen_encryption_params(std::uint32_t poly_mod_deg, std::uint32_t plain_mod_deg, seal::EncryptionParameters &enc_params);

void verify_encryption_params(const seal::EncryptionParameters &enc_params);

void gen_pir_params(uint32_t tot_data_dim, uint32_t usr_data_dim, uint8_t data_size, PirParams &pir_params);

void gen_params(std::uint32_t ploy_mod_deg, std::uint32_t plain_mod_deg, uint32_t tot_data_dim, uint32_t usr_data_num, uint8_t data_size, PirParams &pir_params, seal::EncryptionParameters &params);

void print_pir_params(const PirParams &pir_params);

void print_seal_params(const seal::EncryptionParameters &enc_params);

bool inline bytes_to_hex(char *dest, uint64_t dest_size, const uint8_t *bytes, uint64_t data_size) {
    static const char hex_table[] = "0123456789ABCDEF";
    if (dest_size < (data_size*2 + 1)) {
        return false;
    } else {
        for (int i = 0; i < data_size; i ++) {
            *dest++ = hex_table[bytes[i] >> 4];
            *dest++ = hex_table[bytes[i] & 0xF];
        }
        *dest = 0;

        return true;
    }
}

void inline print_line() {
    std::cout << std::endl;
}
