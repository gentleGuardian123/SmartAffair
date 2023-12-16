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
    cout << "Main: Initializing server..." << endl;
    PIRServer server(enc_params, pir_params);

    cout << "Main: Creating the database with random data (this may take some time) ..."
         << endl;

    auto db(make_unique<uint8_t[]>(pir_params.tot_data_num * pir_params.data_size));
    auto db_copy(make_unique<uint8_t[]>(pir_params.tot_data_num * pir_params.data_size));

    random_device rd;
    for (uint64_t i = 0; i < pir_params.tot_data_dim; i++) {
        for (uint64_t j = 0; j < pir_params.data_size; j++) {
            uint8_t val = rd() % 256;
            db.get()[(i * pir_params.data_size) + j] = val;
            db_copy.get()[(i * pir_params.data_size) + j] = val;
        }
    }

}
