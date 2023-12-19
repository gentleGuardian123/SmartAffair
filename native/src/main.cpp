#include "pir_util.hpp"
#include "pir_client.hpp"
#include "pir_server.hpp"
#include <chrono>
#include <seal/seal.h>

using namespace std::chrono;
using namespace std;
using namespace seal;

int main(int argc, char *argv[]) {

    uint32_t poly_mod_deg = 4096;
    uint32_t plain_mod_deg = 1024;
    uint8_t tot_data_dim = 4;
    uint32_t usr_data_dim = 2;
    uint8_t data_size = 8;

    EncryptionParameters enc_params(scheme_type::bfv);
    PirParams pir_params;

    cout << "Main: Generating SEAL parameters..." << endl;
    gen_encryption_params(poly_mod_deg, plain_mod_deg, enc_params);
    cout << "Main: Verifying SEAL parameters..." << endl;
    verify_encryption_params(enc_params);
    cout << "Main: SEAL parameters are good." << endl;
    cout << "Main: Generating PIR parameters..." << endl;
    gen_pir_params(tot_data_dim, usr_data_dim, data_size, pir_params);
    print_line();

    print_seal_params(enc_params);
    print_pir_params(pir_params);

    print_line();
    cout << "Main: Initializing client..." << endl;
    PIRClient client(enc_params, pir_params);
    cout << "Main: Initializing server..." << endl;
    PIRServer server(enc_params, pir_params);

    cout << "Main: Creating the database with random data (this may take some time) ..." << endl;

    auto db(make_unique<uint8_t[]>(pir_params.tot_data_num * pir_params.data_size));
    auto db_copy(make_unique<uint8_t[]>(pir_params.tot_data_num * pir_params.data_size));

    random_device rd;
    for (uint64_t i = 0; i < pir_params.tot_data_num; i++) {
        for (uint64_t j = 0; j < pir_params.data_size; j++) {
            uint8_t val = rd() % 256;
            db.get()[(i * pir_params.data_size) + j] = val;
            db_copy.get()[(i * pir_params.data_size) + j] = val;
        }
    }

    auto time_pre_s = high_resolution_clock::now();
    server.set_database(move(db), pir_params.tot_data_num, pir_params.data_size);
    auto time_pre_e = high_resolution_clock::now();
    auto time_db_us = duration_cast<microseconds>(time_pre_e - time_pre_s).count();
    cout << "Main: Database set up." << endl;
    print_line();

    cout << "Main: Choosing an index of one element valid for the current user (0 < index < " << pir_params.usr_data_num << ")..." << endl;
    uint64_t valid_desired_index = rd() % pir_params.usr_data_num;
    cout << "Main: Valid desired index is " << valid_desired_index << "." << endl;
    cout << "Main: Choosing an index of one element invalid for the current user (index > " << pir_params.usr_data_num << ")..." << endl;
    uint64_t invalid_desired_index = rd() % (pir_params.tot_data_num - pir_params.usr_data_num) + pir_params.usr_data_num;
    cout << "Main: Invalid desired index is " << invalid_desired_index << "." << endl;
    print_line();

    cout << "Main: Generating query..." << endl;
    auto time_query_s = high_resolution_clock::now();
    PirQuery query = client.generate_query(valid_desired_index);
    auto time_query_e = high_resolution_clock::now();
    auto time_query_us = duration_cast<microseconds>(time_query_e - time_query_s).count();
    cout << "Main: Query generated." << endl;
    print_line();

    cout << "Main: Generating reply..." << endl;
    auto time_reply_s = high_resolution_clock::now();
    PirReply reply = server.generate_reply(query);
    auto time_reply_e = high_resolution_clock::now();
    auto time_reply_us = duration_cast<microseconds>(time_reply_e - time_reply_s).count();
    cout << "Main: Reply generated." << endl;
    print_line();

    cout << "Main: Decrypting reply..." << endl;
    auto time_dec_s = high_resolution_clock::now();
    Plaintext result = client.decrypt(reply);
    auto time_dec_e = high_resolution_clock::now();
    auto time_dec_us = duration_cast<microseconds>(time_dec_e - time_dec_s).count();
    cout << "Main: Decryption finished." << endl;
    cout << "Main: Decryption result is " << result.to_string() << "." << endl;
    print_line();

}
