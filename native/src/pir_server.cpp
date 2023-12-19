#include "pir_server.hpp"
#include "pir_client.hpp"

using namespace std;
using namespace seal;
using namespace seal::util;

PIRServer::PIRServer(const EncryptionParameters &enc_params, const PirParams &pir_params)
    : enc_params_(enc_params), pir_params_(pir_params) {
    context_ = make_shared<SEALContext>(enc_params, true);
    evaluator_ = make_unique<Evaluator>(*context_);
}

void PIRServer::set_database(unique_ptr<vector<Plaintext>> &&db) {
    if (!db)
      throw invalid_argument("db cannot be null");

    db_ = move(db);
}

void PIRServer::set_database(const std::unique_ptr<const std::uint8_t[]> &bytes, std::uint64_t tot_data_num, std::uint64_t data_size) {
    auto result = make_unique<vector<Plaintext>>();

    while (tot_data_num --) {
        char hex[data_size*2 + 1];
        bytes_to_hex(hex, data_size*2 + 1, bytes.get(), data_size);
        Plaintext pt(hex);
        result->push_back(move(pt));
    }

    set_database(move(result));
}

PirReply PIRServer::generate_reply(PirQuery &query) {
    PirReply reply;
    KeyGenerator keygen(*context_);
    RelinKeys relin_keys;
    keygen.create_relin_keys(relin_keys);

    for (uint32_t i = 0; i < pir_params_.usr_data_num; i ++) {
        Ciphertext sor_product;
        uint32_t _i = i;
        for (uint32_t t = 0; t < pir_params_.tot_data_dim; t ++) {
            Ciphertext sor = query[t];
            if (! (_i & 1) ) {
                Plaintext one("1");
                evaluator_->negate_inplace(sor);
                evaluator_->relinearize_inplace(sor, relin_keys);
                evaluator_->add_plain_inplace(sor, one);
            }
            if (!t) {
                sor_product = sor;
            } else {
                evaluator_->multiply_inplace(sor_product, sor);
                evaluator_->relinearize_inplace(sor_product, relin_keys);
            }
            _i = _i >> 1;
        }
        evaluator_->multiply_plain_inplace(sor_product, db_->operator[](i));
        if (!i) {
            reply = sor_product;
        } else {
            evaluator_->add_inplace(reply, sor_product);
        }
    }

    return reply;
}
