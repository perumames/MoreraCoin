// Copyright (c) 2019, The Vulkan Developers.
//
// This file is part of Vulkan.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// You should have received a copy of the MIT License
// along with Vulkan. If not, see <https://opensource.org/licenses/MIT>.

#pragma once

#include <stdlib.h>
#include <stdint.h>

#include <sodium.h>

#ifdef USE_LEVELDB
#include <leveldb/c.h>
#else
#include <rocksdb/c.h>
#endif

#include "common/util.h"

#include "core/parameters.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct Wallet
{
  uint8_t secret_key[crypto_sign_SECRETKEYBYTES];
  uint8_t public_key[crypto_sign_PUBLICKEYBYTES];
  uint8_t address[ADDRESS_SIZE];
  uint64_t balance;
} wallet_t;

wallet_t* make_wallet(void);
void free_wallet(wallet_t* wallet);

int serialize_wallet(buffer_t *buffer, wallet_t* wallet);
int deserialize_wallet(buffer_iterator_t *buffer_iterator, wallet_t **wallet_out);

#ifdef USE_LEVELDB
leveldb_t* open_wallet(const char *wallet_dir, char *err);
#else
rocksdb_t* open_wallet(const char *wallet_dir, char *err);
#endif

int new_wallet(const char *wallet_dir, wallet_t **wallet_out);
int get_wallet(const char *wallet_dir, wallet_t **wallet_out);
int init_wallet(const char *wallet_dir, wallet_t **wallet_out);
int remove_wallet(const char *wallet_dir);

void print_wallet(wallet_t* wallet);
void print_public_key(wallet_t *wallet);
void print_secret_key(wallet_t *wallet);

int compare_addresses(uint8_t *address, uint8_t *other_address);

int public_key_to_address(unsigned char *address, unsigned char *pk);
uint8_t get_address_id(uint8_t *address);
int valid_address(uint8_t *address);

#ifdef __cplusplus
}
#endif
