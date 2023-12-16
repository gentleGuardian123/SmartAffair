#pragma once

#include<pir_util.hpp>
#include<memory>
#include<vector>

class PIRClient {
public:
    PIRClient(const seal::EncryptionParameters &enc_params, const PirParams &pir_params);

    PirQuery generate_query(std::uint64_t desiredIndex);

    int generate_serialized_query(std::uint64_t desiredIndex, std::stringstream &stream);

    seal::Plaintext decrypt(seal::Ciphertext ct);

private:
  seal::EncryptionParameters enc_params_;
  PirParams pir_params_;

  std::unique_ptr<seal::Encryptor> encryptor_;
  std::unique_ptr<seal::Decryptor> decryptor_;
  std::unique_ptr<seal::Evaluator> evaluator_;
  std::unique_ptr<seal::KeyGenerator> keygen_;
  std::unique_ptr<seal::BatchEncoder> encoder_;
  std::shared_ptr<seal::SEALContext> context_;
};

