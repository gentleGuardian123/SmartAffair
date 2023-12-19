#include "pir_util.hpp"

using namespace std;
using namespace seal;
using namespace seal::util;

void gen_encryption_params(std::uint32_t poly_mod_deg, std::uint32_t plain_mod_deg, seal::EncryptionParameters &enc_params) {
    enc_params.set_poly_modulus_degree(poly_mod_deg);
    enc_params.set_coeff_modulus(CoeffModulus::BFVDefault(poly_mod_deg));
    enc_params.set_plain_modulus(plain_mod_deg);
    // enc_params.set_plain_modulus(PlainModulus::Batching(poly_mod_deg, logt + 1));

    return;
}

void verify_encryption_params(const seal::EncryptionParameters &enc_params) {
    SEALContext context(enc_params, true);
    if (!context.parameters_set()) {
      throw invalid_argument("SEAL parameters not valid.");
    }
    if (!context.using_keyswitching()) {
      throw invalid_argument("SEAL parameters do not support key switching.");
    }
    // if (!context.first_context_data()->qualifiers().using_batching) {
    //   throw invalid_argument("SEAL parameters do not support batching.");
    // }

    // BatchEncoder batch_encoder(context);
    // size_t slot_count = batch_encoder.slot_count();
    // if (slot_count != enc_params.poly_modulus_degree()) {
    //   throw invalid_argument("Slot count not equal to poly modulus degree - this "
    //                          "will cause issues downstream.");
    // }

    return;
}

void gen_pir_params(uint32_t tot_data_dim, uint32_t usr_data_dim, uint8_t data_size,  PirParams &pir_params) {
    pir_params.data_size = data_size;
    pir_params.usr_data_dim = usr_data_dim;
    pir_params.usr_data_num = 1 << usr_data_dim;
    pir_params.tot_data_dim = tot_data_dim;
    pir_params.tot_data_num = 1 << tot_data_dim;

    return;
}

void gen_params(uint32_t ploy_mod_deg, uint32_t plain_mod_deg, uint32_t tot_data_dim, uint32_t usr_data_num, uint8_t data_size, PirParams &pir_params, seal::EncryptionParameters &params) {
    gen_encryption_params(ploy_mod_deg, plain_mod_deg, params);
    gen_pir_params(tot_data_dim, usr_data_num, data_size, pir_params);

    return;
}

void print_pir_params(const PirParams &pir_params) {

    cout << "PIR Parameters:" << endl;
    cout << "Dimension for number of total data: " << pir_params.tot_data_dim << endl;
    cout << "Number of data for one single user: " << pir_params.usr_data_num << endl;
    cout << "Size per data in the database: " << pir_params.data_size << endl;

}

void print_seal_params(const EncryptionParameters &enc_params) {
    std::uint32_t N = enc_params.poly_modulus_degree();
    Modulus t = enc_params.plain_modulus();
    std::uint32_t logt = floor(log2(t.value()));

    cout << "SEAL encryption parameters:" << endl;
    cout << "Degree of polynomial modulus (N): " << N << endl;
    cout << "Size of plaintext modulus (log t): " << logt << endl;
    cout << "There are " << enc_params.coeff_modulus().size()
         << " coefficient modulus:" << endl;

    for (uint32_t i = 0; i < enc_params.coeff_modulus().size(); ++i) {
      double logqi = log2(enc_params.coeff_modulus()[i].value());
      cout << "Size of coefficient modulus " << i << " (log q_" << i
           << "): " << logqi << endl;
    }

}

