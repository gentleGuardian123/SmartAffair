#pragma once

#include "seal/seal.h"
#include <vector>

typedef std::vector<seal::Plaintext> Database;
typedef std::vector<seal::Ciphertext> PirQuery;
typedef seal::Ciphertext PirReply;

struct PirParams {
    std::uint64_t tot_data_num; // |N|, the total number of data in database.
    std::uint8_t tot_data_dim;  // |B| = log|N|.
    std::uint32_t usr_data_num; // |M|, the maximum number of data for one user.
    std::uint8_t data_size; 
};

void gen_encryption_params(std::uint32_t N,    // degree of polynomial
                           std::uint32_t logt, // bits of plaintext coefficient
                           seal::EncryptionParameters &enc_params);

void verify_encryption_params(const seal::EncryptionParameters &enc_params);

void gen_pir_params(uint64_t usr_data_num, uint64_t data_size,
                    const seal::EncryptionParameters &enc_params,
                    PirParams &pir_params);

void gen_params(uint64_t ele_num, uint64_t ele_size, uint32_t N, uint32_t logt,
                uint32_t d, seal::EncryptionParameters &params,
                PirParams &pir_params);

void print_pir_params(const PirParams &pir_params);
void print_seal_params(const seal::EncryptionParameters &enc_params);
