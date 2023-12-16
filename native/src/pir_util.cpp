#include "pir_util.hpp"

using namespace std;
using namespace seal;
using namespace seal::util;

void gen_encryption_params(std::uint32_t N, std::uint32_t logt, seal::EncryptionParameters &enc_params) {
    enc_params.set_poly_modulus_degree(N);
    enc_params.set_coeff_modulus(CoeffModulus::BFVDefault(N));
    enc_params.set_plain_modulus(PlainModulus::Batching(N, logt + 1));

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
  if (!context.first_context_data()->qualifiers().using_batching) {
    throw invalid_argument("SEAL parameters do not support batching.");
  }

  BatchEncoder batch_encoder(context);
  size_t slot_count = batch_encoder.slot_count();
  if (slot_count != enc_params.poly_modulus_degree()) {
    throw invalid_argument("Slot count not equal to poly modulus degree - this "
                           "will cause issues downstream.");
  }

  return;
}

void gen_pir_params(uint64_t usr_data_num, uint64_t data_size, const seal::EncryptionParameters &enc_params, PirParams &pir_params) {

}
