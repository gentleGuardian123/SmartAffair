#include "pir_server.hpp"
#include "pir_client.hpp"
#include<math.h>

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

void PIRServer::set_database(const std::unique_ptr<const std::uint8_t[]> &bytes) {
    auto result = make_unique<vector<Plaintext>>();
    uint64_t data_num = pir_params_.tot_data_num;
    int offset = 0;

    while (data_num --) {
        char hex[pir_params_.data_size*2 + 1];
        bytes_to_hex(hex, pir_params_.data_size*2 + 1, bytes.get() + offset, pir_params_.data_size);
        Plaintext pt(hex);
        result->push_back(move(pt));
        offset += pir_params_.data_size;
    }

    set_database(move(result));
}

void PIRServer::show_database() {
    uint64_t data_num = pir_params_.tot_data_num;
    uint64_t data_per_line = pir_params_.tot_data_dim > 16 ? (1 << 8) : (1 << (pir_params_.tot_data_dim/2));

    for (int row = 0; row < data_num / data_per_line; row ++) {
        for (int column = 0; column < data_per_line; column ++) {
            uint64_t index = row * data_per_line + column;
            cout << index << ":" << db_->operator[](index).to_string() << '\t';
        }
        cout << endl;
    }

}

PirReply PIRServer::generate_reply(PirQuery &query) {
    PirReply reply;
    KeyGenerator keygen(*context_);
    RelinKeys relin_keys;
    keygen.create_relin_keys(relin_keys);

    for (uint32_t i = 0; i < pir_params_.usr_data_num; i ++) {
        Ciphertext xnor_product;
        uint32_t _i = i;
        for (uint32_t t = 0; t < pir_params_.tot_data_dim; t ++) {
            Ciphertext xnor = query[t];
            if (! (_i & 1) ) {
                Plaintext one("1");
                evaluator_->negate_inplace(xnor);
                evaluator_->relinearize_inplace(xnor, relin_keys);
                evaluator_->add_plain_inplace(xnor, one);
            }
            if (!t) {
                xnor_product = xnor;
            } else {
                evaluator_->multiply_inplace(xnor_product, xnor);
                evaluator_->relinearize_inplace(xnor_product, relin_keys);
            }
            _i = _i >> 1;
        }
        evaluator_->multiply_plain_inplace(xnor_product, db_->operator[](i));
        if (!i) {
            reply = xnor_product;
        } else {
            evaluator_->add_inplace(reply, xnor_product);
        }
    }

    return reply;
}

PirReply PIRServer::generate_reply_debug(PirQuery &query, PIRClient &client) {
    PirReply reply;
    RelinKeys relin_keys;
    client.keygen_->create_relin_keys(relin_keys);

    for (uint32_t i = 0; i < pir_params_.usr_data_num; i ++) {
        Ciphertext xnor_product;
        uint32_t _i = i;
        for (uint32_t t = 0; t < pir_params_.tot_data_dim; t ++) {
            Ciphertext xnor = query[t];
            if (! (_i & 1) ) {
                Plaintext one("1");
                evaluator_->negate_inplace(xnor);
                evaluator_->relinearize_inplace(xnor, relin_keys);
                evaluator_->add_plain_inplace(xnor, one);
            }
            if (!t) {
                xnor_product = xnor;
            } else {
                evaluator_->multiply_inplace(xnor_product, xnor);
                evaluator_->relinearize_inplace(xnor_product, relin_keys);
            }
            _i = _i >> 1;
        }
        evaluator_->multiply_plain_inplace(xnor_product, db_->operator[](i));
        if (!i) {
            reply = xnor_product;
        } else {
            evaluator_->add_inplace(reply, xnor_product);
        }
    }

    return reply;
}