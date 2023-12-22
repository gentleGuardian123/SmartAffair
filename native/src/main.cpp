#include "pir_util.hpp"
#include "pir_client.hpp"
#include "pir_server.hpp"
#include <chrono>
#include <seal/seal.h>

using namespace std::chrono;
using namespace std;
using namespace seal;

int main(int argc, char *argv[]) {

    uint32_t poly_mod_deg = 16384;
    uint32_t plain_mod_deg = 1024;
    uint8_t tot_data_dim = 4;
    uint32_t usr_data_dim = 3;
    uint8_t data_size = 1;

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

    stringstream client_stream_for_valid;
    stringstream server_stream_for_valid;
    stringstream client_stream_for_invalid;
    stringstream server_stream_for_invalid;

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

    auto time_db_s = high_resolution_clock::now();
    server.set_database(move(db));
    auto time_db_e = high_resolution_clock::now();
    auto time_db_us = duration_cast<microseconds>(time_db_e - time_db_s).count();
    cout << "Main: Database set up." << endl;
    cout << "Main: The database is as followed:" << endl;
    server.show_database();
    print_line();

    cout << "Main: Choosing an index of one element valid for the current user (0 < index < " << pir_params.usr_data_num << ")..." << endl;
    uint64_t valid_desired_index = rd() % pir_params.usr_data_num;
    cout << "Main: Valid desired index is " << valid_desired_index << "." << endl;
    cout << "Main: Choosing an index of one element invalid for the current user (index > " << pir_params.usr_data_num << ")..." << endl;
    uint64_t invalid_desired_index = rd() % (pir_params.tot_data_num - pir_params.usr_data_num) + pir_params.usr_data_num;
    cout << "Main: Invalid desired index is " << invalid_desired_index << "." << endl;
    print_line();

    cout << "Main: Generating query for valid index..." << endl;
    auto time_va_query_s = high_resolution_clock::now();
    PirQuery valid_query = client.generate_query(valid_desired_index);
    auto time_va_query_e = high_resolution_clock::now();
    auto time_va_query_us = duration_cast<microseconds>(time_va_query_e - time_va_query_s).count();
    cout << "Main: Valid query generated." << endl;
    int valid_query_size = client.generate_serialized_query(valid_desired_index, client_stream_for_valid);
    print_line();

    cout << "Main: Generating reply for valid index..." << endl;
    auto time_va_reply_s = high_resolution_clock::now();
    PirReply valid_reply = server.generate_reply(valid_query, client.gen_relin_keys());
    auto time_va_reply_e = high_resolution_clock::now();
    auto time_va_reply_us = duration_cast<microseconds>(time_va_reply_e - time_va_reply_s).count();
    cout << "Main: Reply for valid query generated." << endl;
    int valid_reply_size = server.serialize_reply(valid_reply, server_stream_for_valid);
    print_line();

    cout << "Main: Decrypting reply..." << endl;
    auto time_va_dec_s = high_resolution_clock::now();
    Plaintext valid_result = client.decrypt(valid_reply);
    auto time_va_dec_e = high_resolution_clock::now();
    auto time_va_dec_us = duration_cast<microseconds>(time_va_dec_e - time_va_dec_s).count();
    cout << "Main: Decryption finished." << endl;
    cout << "Main: Decryption result is " << valid_result.to_string() << "... Correct." << endl;
    print_line();

    cout << "Main: Generating query for invalid index..." << endl;
    auto time_iva_query_s = high_resolution_clock::now();
    PirQuery invalid_query = client.generate_query(invalid_desired_index);
    auto time_iva_query_e = high_resolution_clock::now();
    auto time_iva_query_us = duration_cast<microseconds>(time_iva_query_e - time_iva_query_s).count();
    cout << "Main: Valid query generated." << endl;
    int invalid_query_size = client.generate_serialized_query(invalid_desired_index, client_stream_for_invalid);
    print_line();

    cout << "Main: Generating reply for invalid index..." << endl;
    auto time_iva_reply_s = high_resolution_clock::now();
    PirReply invalid_reply = server.generate_reply(invalid_query, client.gen_relin_keys());
    auto time_iva_reply_e = high_resolution_clock::now();
    auto time_iva_reply_us = duration_cast<microseconds>(time_iva_reply_e - time_iva_reply_s).count();
    cout << "Main: Reply for valid query generated." << endl;
    int invalid_reply_size = server.serialize_reply(invalid_reply, server_stream_for_invalid);
    print_line();

    cout << "Main: Decrypting reply..." << endl;
    auto time_iva_dec_s = high_resolution_clock::now();
    Plaintext invalid_result = client.decrypt(invalid_reply);
    auto time_iva_dec_e = high_resolution_clock::now();
    auto time_iva_dec_us = duration_cast<microseconds>(time_iva_dec_e - time_iva_dec_s).count();
    cout << "Main: Decryption finished." << endl;
    cout << "Main: Decryption result is " << invalid_result.to_string() << "... Retrieved nothing." << endl;
    print_line();

    cout << "Main: The benchmark result:" << endl;
    cout << "Main: Time spent on database setup on server-side:\t" << time_db_us << "us" << endl;
    cout << "Main: Time spent on query generation on client-side:\t" << (time_va_query_us + time_iva_query_us) / 2000 << "ms" << endl;
    cout << "Main: Time spent on reply generation on server-side:\t" << (time_va_reply_us + time_iva_reply_us) / 2000 << "ms" << endl;
    cout << "Main: Time spent on decryption on client-side:\t\t" << (time_va_dec_us + time_iva_dec_us) / 2000 << "ms" << endl;
    cout << "Main: Query overhead on client-side:\t" << (valid_query_size + invalid_query_size) / 2048 << " KB" << endl;
    cout << "Main: Reply overhead on server-side:\t" << (valid_reply_size + invalid_reply_size) / 2048 << " KB" << endl;
    cout << "Main: Total communication overhead:\t" << (valid_query_size + invalid_query_size + valid_query_size + invalid_query_size) / 2048 << " KB" << endl;

}
