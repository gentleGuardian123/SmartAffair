#include "pir_client.hpp"

using namespace std;
using namespace seal;
using namespace seal::util;

PIRClient::PIRClient(const EncryptionParameters &enc_params, const PirParams &pir_params)
    : enc_params_(enc_params), pir_params_(pir_params) {

  context_ = make_shared<SEALContext>(enc_params, true);

  keygen_ = make_unique<KeyGenerator>(*context_);

  PublicKey public_key;
  keygen_->create_public_key(public_key);
  SecretKey secret_key = keygen_->secret_key();

  decryptor_ = make_unique<Decryptor>(*context_, secret_key);
  evaluator_ = make_unique<Evaluator>(*context_);
  encoder_ = make_unique<BatchEncoder>(*context_);
}