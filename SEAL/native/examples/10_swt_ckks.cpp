
#include "examples.h"

using namespace std;
using namespace seal;

void swt_ckks()
{

    /** Set up the parameters.*/
    EncryptionParameters parms(scheme_type::ckks);

    size_t poly_modulus_degree = 8192;
    parms.set_poly_modulus_degree(poly_modulus_degree);
    parms.set_coeff_modulus(CoeffModulus::Create(poly_modulus_degree, { 60, 40, 40, 60 }));

    double scale = pow(2.0, 40);

    SEALContext context(parms);
    print_parameters(context);
    cout << endl;

    KeyGenerator keygen(context);
    auto secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);
    RelinKeys relin_keys;
    keygen.create_relin_keys(relin_keys);
    GaloisKeys gal_keys;
    keygen.create_galois_keys(gal_keys);
    Encryptor encryptor(context, public_key);
    Evaluator evaluator(context);
    Decryptor decryptor(context, secret_key);

    CKKSEncoder encoder(context);
    size_t slot_count = encoder.slot_count();
    cout << "Number of slots: " << slot_count << endl;

    vector<double> input;
    input.reserve(slot_count);
    double curr_point = 0;
    double step_size = 1.0 / (static_cast<double>(slot_count) - 1);
    for (size_t i = 0; i < slot_count; i++)
    {
        input.push_back(curr_point);
        curr_point += step_size;
    }
    cout << "Input vector: " << endl;
    print_vector(input, 3, 7);


    /** Begin encoding, encrypting, and computing each entries of the polynomial on ciphertext.*/
    cout << "Evaluating polynomial x^4 - 10x^3 + 35x^2 - 50x + 24" << endl;
    
    Plaintext plain_coeff4, plain_coeff3, plain_coeff2, plain_coeff1, plain_coeff0;
    encoder.encode(1.0, scale, plain_coeff4);
    encoder.encode(-10.0, scale, plain_coeff3);
    encoder.encode(35.0, scale, plain_coeff2);
    encoder.encode(-50.0, scale, plain_coeff1);
    encoder.encode(24.0, scale, plain_coeff0);

    Plaintext x_plain;
    encoder.encode(input, scale, x_plain);
    Ciphertext x1_encrypted;
    encryptor.encrypt(x_plain, x1_encrypted);

    Ciphertext x_sq_encrypted;
    evaluator.square(x1_encrypted, x_sq_encrypted);
    evaluator.relinearize_inplace(x_sq_encrypted, relin_keys);
    evaluator.rescale_to_next_inplace(x_sq_encrypted);

    Ciphertext x1_encrypted_coeff1;
    Ciphertext x1_encrypted_coeff3;
    Ciphertext x1_encrypted_coeff2;
    Ciphertext x2_encrypted_coeff2;
    evaluator.multiply_plain(x1_encrypted, plain_coeff1, x1_encrypted_coeff1);
    evaluator.rescale_to_next_inplace(x1_encrypted_coeff1);
    evaluator.multiply_plain(x1_encrypted, plain_coeff2, x1_encrypted_coeff2);
    evaluator.rescale_to_next_inplace(x1_encrypted_coeff2);
    evaluator.multiply_plain(x1_encrypted, plain_coeff4, x2_encrypted_coeff2);
    evaluator.rescale_to_next_inplace(x2_encrypted_coeff2);
    evaluator.multiply_plain(x1_encrypted, plain_coeff3, x1_encrypted_coeff3);
    evaluator.rescale_to_next_inplace(x1_encrypted_coeff3);

    Ciphertext x3_encrypted_coeff3 = x_sq_encrypted;
    evaluator.multiply_inplace(x2_encrypted_coeff2, x1_encrypted_coeff2);
    evaluator.relinearize_inplace(x2_encrypted_coeff2, relin_keys);
    evaluator.rescale_to_next_inplace(x2_encrypted_coeff2);
    evaluator.multiply_inplace(x3_encrypted_coeff3, x1_encrypted_coeff3);
    evaluator.relinearize_inplace(x3_encrypted_coeff3, relin_keys);
    evaluator.rescale_to_next_inplace(x3_encrypted_coeff3);

    Ciphertext x4_encrypted_coeff4;
    evaluator.square(x1_encrypted, x4_encrypted_coeff4);
    evaluator.relinearize_inplace(x4_encrypted_coeff4, relin_keys);
    evaluator.rescale_to_next_inplace(x4_encrypted_coeff4);
    evaluator.multiply_inplace(x4_encrypted_coeff4, x_sq_encrypted);
    evaluator.relinearize_inplace(x4_encrypted_coeff4, relin_keys);
    evaluator.rescale_to_next_inplace(x4_encrypted_coeff4);

    cout << "Finished encoding, encrypting, computing." << endl;

    /** Compatalize each entry and sum them together. */
    x1_encrypted_coeff1.scale() = pow(2.0, 40);
    x2_encrypted_coeff2.scale() = pow(2.0, 40);
    x3_encrypted_coeff3.scale() = pow(2.0, 40);
    x4_encrypted_coeff4.scale() = pow(2.0, 40);

    parms_id_type last_parms_id = x4_encrypted_coeff4.parms_id();
    evaluator.mod_switch_to_inplace(x1_encrypted_coeff1, last_parms_id);
    evaluator.mod_switch_to_inplace(x2_encrypted_coeff2, last_parms_id);
    evaluator.mod_switch_to_inplace(x3_encrypted_coeff3, last_parms_id);
    evaluator.mod_switch_to_inplace(plain_coeff0, last_parms_id);

    Ciphertext encrypted_result;
    evaluator.add(x2_encrypted_coeff2, x1_encrypted_coeff1, encrypted_result);
    evaluator.add(x3_encrypted_coeff3, encrypted_result, encrypted_result);
    evaluator.add(x4_encrypted_coeff4, encrypted_result, encrypted_result);
    evaluator.add_plain_inplace(encrypted_result, plain_coeff0);


    /** First print the true result. */
    Plaintext plain_result;
    print_line(__LINE__);
    cout << "Decrypt and decode x^4 - 10x^3 + 35x^2 - 50x + 24." << endl;
    cout << "    + Expected result:" << endl;
    vector<double> true_result;
    for (size_t i = 0; i < input.size(); i++)
    {
        double x = input[i];
        true_result.push_back(x*x*x*x - 10.0*x*x*x + 35.0*x*x -50.0*x + 24.0);
    }
    print_vector(true_result, 3, 7);

    /** Decrypt, decode, and print the result. */
    decryptor.decrypt(encrypted_result, plain_result);
    vector<double> result;
    encoder.decode(plain_result, result);
    cout << "    + Computed result ...... Correct." << endl;
    print_vector(result, 3, 7);


}