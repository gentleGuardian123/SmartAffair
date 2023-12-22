#pragma once

#include "pir_util.hpp"
#include "pir_client.hpp"
#include <map>
#include <memory>
#include <vector>

class PIRServer {
public:
    PIRServer(const seal::EncryptionParameters &enc_params, const PirParams &pir_params);

    void set_database(std::unique_ptr<Database> &&db);

    void set_database(const std::unique_ptr<const std::uint8_t[]> &bytes);

    void show_database();

    PirReply generate_reply(PirQuery &query, seal::RelinKeys relin_keys);

    PirReply generate_reply_debug(PirQuery &query, seal::RelinKeys relin_keys);

    int serialize_reply(PirReply &reply, std::stringstream &stream);
    
private:
    seal::EncryptionParameters enc_params_; // SEAL parameters
    PirParams pir_params_;                  // PIR parameters
    std::unique_ptr<Database> db_;
    std::unique_ptr<seal::Evaluator> evaluator_;
    std::shared_ptr<seal::SEALContext> context_;
    // std::unique_ptr<seal::KeyGenerator> keygen_;
    // std::unique_ptr<seal::RelinKeys> relin_keys_;

    friend class PIRClient;
};
