#pragma once

#include "seal/seal.h"
#include <algorithm>
#include <chrono>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <mutex>
#include <numeric>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

void same_or(seal::CKKSEncoder encoder, seal::Ciphertext src_bit_1, seal::Ciphertext src_bit_2, seal::Ciphertext dest_bit);
