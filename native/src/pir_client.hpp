#pragma once

#include "pir_util.hpp"
#include <memory>
#include <vector>

class PIRClient {
public:
    PIRClient(const seal::EncryptionParameters &enc_params, const PirParams &pir_params);

    seal::RelinKeys gen_relin_keys();

    PirQuery generate_query(std::uint32_t desired_index);

    // int generate_serialized_query(std::uint32_t desired_index, std::stringstream &stream);

    seal::Plaintext decrypt(PirReply reply);

private:
    seal::EncryptionParameters enc_params_;
    PirParams pir_params_;

    std::unique_ptr<seal::Encryptor> encryptor_;
    std::unique_ptr<seal::Decryptor> decryptor_;
    std::unique_ptr<seal::Evaluator> evaluator_;
    std::unique_ptr<seal::KeyGenerator> keygen_;
    // std::unique_ptr<seal::BatchEncoder> encoder_;
    std::shared_ptr<seal::SEALContext> context_;

    friend class PIRServer;
};

