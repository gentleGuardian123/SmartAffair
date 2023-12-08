// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#include "examples.h"

using namespace std;
using namespace seal;

void swt_bfv_test()
{
    print_example_banner("SWT‘s BFV test");

    EncryptionParameters parms(scheme_type::bfv);

    size_t poly_modulus_degree = 4096;
    parms.set_poly_modulus_degree(poly_modulus_degree);

    parms.set_coeff_modulus(CoeffModulus::BFVDefault(poly_modulus_degree));

    parms.set_plain_modulus(1024);

    SEALContext context(parms);

    print_line(__LINE__);
    cout << "Set encryption parameters and print" << endl;
    print_parameters(context);

    cout << "Parameter validation (success): " << context.parameter_error_message() << endl;

    cout << endl;
    cout << "~~~~~~ A naive way to calculate x^4-10x^3+5x^2-50x+24~~~~~~" << endl;

    KeyGenerator keygen(context);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

    Encryptor encryptor(context, public_key);

    Evaluator evaluator(context);

    Decryptor decryptor(context, secret_key);

    print_line(__LINE__);
    uint64_t x = 3;
    Plaintext x_plain(uint64_to_hex_string(x));
    cout << "Express x = " + to_string(x) + " as a plaintext polynomial 0x" + x_plain.to_string() + "." << endl;

    print_line(__LINE__);
    Ciphertext x_encrypted;
    cout << "Encrypt x_plain to x_encrypted." << endl;
    encryptor.encrypt(x_plain, x_encrypted);

    cout << "    + size of freshly encrypted x: " << x_encrypted.size() << endl;

    cout << "    + noise budget in freshly encrypted x: " << decryptor.invariant_noise_budget(x_encrypted) << " bits"
         << endl;

    Plaintext x_decrypted;
    cout << "    + decryption of x_encrypted: ";
    decryptor.decrypt(x_encrypted, x_decrypted);
    cout << "0x" << x_decrypted.to_string() << " ...... Correct." << endl;

    print_line(__LINE__);
    cout << "Generate relinearization keys." << endl;
    RelinKeys relin_keys;
    keygen.create_relin_keys(relin_keys);

    print_line(__LINE__);
    cout << "Compute x_powed_by_2 x^2." << endl;
    Ciphertext x_powed_by_2;
    Ciphertext x_sq_plus_35;
    Ciphertext x_sq_plus_5;
    Plaintext plain_35("23");
    Plaintext plain_5("5");
    Plaintext Plain_24("18");

    evaluator.square(x_encrypted, x_powed_by_2); 
    evaluator.relinearize_inplace(x_powed_by_2, relin_keys);
    evaluator.square(x_encrypted, x_sq_plus_35);
    evaluator.relinearize_inplace(x_sq_plus_35, relin_keys);
    evaluator.square(x_encrypted, x_sq_plus_5);
    evaluator.relinearize_inplace(x_sq_plus_5, relin_keys);

    evaluator.add_plain_inplace(x_sq_plus_35, plain_35);
    evaluator.add_plain_inplace(x_sq_plus_5, plain_5);

    cout << "    + size of x_sq_plus_35: " << x_sq_plus_35.size() << endl;
    cout << "    + noise budget in x_sq_plus_35: " << decryptor.invariant_noise_budget(x_sq_plus_35) << " bits"
         << endl;

    Plaintext decrypted_result;
    cout << "    + decryption of x_sq_plus_35: ";
    decryptor.decrypt(x_sq_plus_35, decrypted_result);
    cout << "0x" << decrypted_result.to_string() << " ...... Correct." << endl;

    print_line(__LINE__);
    cout << "Compute x_sq_multi_x_sq_plus_35 x^2(x^2+35)." << endl;
    Ciphertext x_sq_multi_x_sq_plus_35;
    evaluator.multiply(x_powed_by_2, x_sq_plus_35, x_sq_multi_x_sq_plus_35);
    evaluator.relinearize_inplace(x_sq_multi_x_sq_plus_35, relin_keys);

    print_line(__LINE__);
    cout << "Compute ten_x_multi_x_sq_plus_5 10x(x^2+5)." << endl;
    Ciphertext ten_x_multi_x_sq_plus_5;
    Plaintext plain_10("a");
    evaluator.multiply_plain_inplace(x_sq_plus_5, plain_10);
    evaluator.multiply(x_encrypted, x_sq_plus_5, ten_x_multi_x_sq_plus_5);
    evaluator.relinearize_inplace(ten_x_multi_x_sq_plus_5, relin_keys);

    cout << "    + decryption of ten_x_multi_x_sq_plus_5: ";
    decryptor.decrypt(ten_x_multi_x_sq_plus_5, decrypted_result);
    cout << "0x" << decrypted_result.to_string() << " ...... Correct." << endl;

    print_line(__LINE__);
    evaluator.negate_inplace(ten_x_multi_x_sq_plus_5);
    evaluator.add_inplace(x_sq_multi_x_sq_plus_35, ten_x_multi_x_sq_plus_5);
    evaluator.add_plain_inplace(x_sq_multi_x_sq_plus_35, Plain_24);

    cout << "NOTE: Decryption can be incorrect if noise budget is zero." << endl;

    print_line(__LINE__);
    cout << "Decrypt encrypted_result." << endl;
    decryptor.decrypt(x_sq_multi_x_sq_plus_35, decrypted_result);
    cout << "    + decryption = 0x" << decrypted_result.to_string() << " ...... Correct." << endl;
    cout << endl;

    print_line(__LINE__);
    cout << "An example of invalid parameters" << endl;
    parms.set_poly_modulus_degree(4096);
    context = SEALContext(parms);
    print_parameters(context);
    cout << "Parameter validation (failed): " << context.parameter_error_message() << endl << endl;

}
