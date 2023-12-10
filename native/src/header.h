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

void same_or(CKKSEncoder encoder, Ciphertext src_bit_1, Ciphertext src_bit_2, Ciphertext dest_bit);
