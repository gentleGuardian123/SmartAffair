#include "pir_client.hpp"
#include "pir_server.hpp"

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

    encryptor_ = make_unique<Encryptor>(*context_, public_key);
    decryptor_ = make_unique<Decryptor>(*context_, secret_key);
    evaluator_ = make_unique<Evaluator>(*context_);
    // encoder_ = make_unique<BatchEncoder>(*context_);
}

PirQuery PIRClient::generate_query(uint32_t desired_index) {
    PirQuery query;

    uint32_t desired_index_ = desired_index;
    for (uint32_t i = 0; i < pir_params_.tot_data_dim; i ++) {
        Plaintext pt(desired_index_ & 1 ? "1" : "0");
        Ciphertext ct;
        encryptor_->encrypt(pt, ct);
        query.push_back(ct);
        desired_index_ = desired_index_ >> 1;
    }

    return query;
}

Plaintext PIRClient::decrypt(PirReply reply) {
    Plaintext pt;
    decryptor_->decrypt(reply, pt);

    return pt;
}
