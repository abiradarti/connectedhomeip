/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
#pragma once

#include "lib/support/logging/CHIPLogging.h"
#include <credentials/DeviceAttestationCredsProvider.h>
#include <jni.h>
#include <lib/support/JniReferences.h>

namespace matter {
namespace casting {
namespace support {

class JNIDACProvider : public chip::Credentials::DeviceAttestationCredentialsProvider
{
public:
    JNIDACProvider(jobject provider);
    CHIP_ERROR GetCertificationDeclaration(chip::MutableByteSpan & out_cd_buffer) override;
    CHIP_ERROR GetFirmwareInformation(chip::MutableByteSpan & out_firmware_info_buffer) override;
    CHIP_ERROR GetDeviceAttestationCert(chip::MutableByteSpan & out_dac_buffer) override;
    CHIP_ERROR GetProductAttestationIntermediateCert(chip::MutableByteSpan & out_pai_buffer) override;
    CHIP_ERROR SignWithDeviceAttestationKey(const chip::ByteSpan & message_to_sign,
                                            chip::MutableByteSpan & out_signature_buffer) override;

private:
    CHIP_ERROR GetJavaByteByMethod(jmethodID method, chip::MutableByteSpan & out_buffer);
    CHIP_ERROR GetJavaByteByMethod(jmethodID method, const chip::ByteSpan & in_buffer, chip::MutableByteSpan & out_buffer);
    chip::JniGlobalReference mJNIDACProviderObject;
    jmethodID mGetCertificationDeclarationMethod           = nullptr;
    jmethodID mGetFirmwareInformationMethod                = nullptr;
    jmethodID mGetDeviceAttestationCertMethod              = nullptr;
    jmethodID mGetProductAttestationIntermediateCertMethod = nullptr;
    jmethodID mSignWithDeviceAttestationKeyMethod          = nullptr;
};

}; // namespace support
}; // namespace casting
}; // namespace matter
