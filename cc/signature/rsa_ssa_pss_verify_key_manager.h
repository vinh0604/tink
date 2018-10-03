// Copyright 2018 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef TINK_SIGNATURE_RSA_SSA_PSS_VERIFY_KEY_MANAGER_H_
#define TINK_SIGNATURE_RSA_SSA_PSS_VERIFY_KEY_MANAGER_H_

#include <algorithm>
#include <vector>

#include "absl/strings/string_view.h"
#include "tink/core/key_manager_base.h"
#include "tink/key_manager.h"
#include "tink/public_key_verify.h"
#include "tink/util/errors.h"
#include "tink/util/protobuf_helper.h"
#include "tink/util/status.h"
#include "tink/util/statusor.h"
#include "proto/rsa_ssa_pss.pb.h"
#include "proto/tink.pb.h"

namespace crypto {
namespace tink {

class RsaSsaPssVerifyKeyManager
    : public KeyManagerBase<PublicKeyVerify,
                            google::crypto::tink::RsaSsaPssPublicKey> {
 public:
  static constexpr uint32_t kVersion = 0;

  RsaSsaPssVerifyKeyManager();

  // Returns the version of this key manager.
  uint32_t get_version() const override;

  // Returns a factory that generates keys of the key type
  // handled by this manager.
  const KeyFactory& get_key_factory() const override;

  virtual ~RsaSsaPssVerifyKeyManager() {}

 protected:
  crypto::tink::util::StatusOr<std::unique_ptr<PublicKeyVerify>>
  GetPrimitiveFromKey(const google::crypto::tink::RsaSsaPssPublicKey&
                          rsa_ssa_pss_public_key) const override;

 private:
  // Friends that re-use proto validation helpers.
  friend class RsaSsaPssPrivateKeyFactory;
  friend class RsaSsaPssSignKeyManager;

  std::string key_type_;
  std::unique_ptr<KeyFactory> key_factory_;

  static crypto::tink::util::Status Validate(
      const google::crypto::tink::RsaSsaPssParams& params);
  static crypto::tink::util::Status Validate(
      const google::crypto::tink::RsaSsaPssPublicKey& key);
};

}  // namespace tink
}  // namespace crypto

#endif  // TINK_SIGNATURE_RSA_SSA_PSS_VERIFY_KEY_MANAGER_H_
