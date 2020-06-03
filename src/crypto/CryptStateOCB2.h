// Copyright 2005-2020 The Mumble Developers. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file at the root of the
// Mumble source tree or at <https://www.mumble.info/LICENSE>.

#ifndef MUMBLE_CRYPTSTATEOCB2_H
#define MUMBLE_CRYPTSTATEOCB2_H

#include "CryptState.h"

#include <openssl/aes.h>

#define AES_KEY_SIZE_BITS   128
#define AES_KEY_SIZE_BYTES  (AES_KEY_SIZE_BITS/8)


class CryptStateOCB2 : public CryptState {
public:
	CryptStateOCB2();
	~CryptStateOCB2() {};

	virtual bool isValid() const Q_DECL_OVERRIDE;
	virtual void genKey() Q_DECL_OVERRIDE;
	virtual void setKey(const std::string& rkey, const std::string& eiv, const std::string& div) Q_DECL_OVERRIDE;
	virtual void setRawKey(const std::string& rkey) Q_DECL_OVERRIDE;
	virtual void setEncryptIV(const std::string& iv) Q_DECL_OVERRIDE;
	virtual void setDecryptIV(const std::string& iv) Q_DECL_OVERRIDE;
	virtual std::string getRawKey() Q_DECL_OVERRIDE;
	virtual std::string getEncryptIV() Q_DECL_OVERRIDE;
	virtual std::string getDecryptIV() Q_DECL_OVERRIDE;

	virtual bool decrypt(const unsigned char *source, unsigned char *dst, unsigned int crypted_length) Q_DECL_OVERRIDE;
	virtual bool encrypt(const unsigned char *source, unsigned char *dst, unsigned int plain_length) Q_DECL_OVERRIDE;

	bool ocb_encrypt(const unsigned char *plain, unsigned char *encrypted, unsigned int len, const unsigned char *nonce, unsigned char *tag);
	bool ocb_decrypt(const unsigned char *encrypted, unsigned char *plain, unsigned int len, const unsigned char *nonce, unsigned char *tag);

private:
	unsigned char raw_key[AES_KEY_SIZE_BYTES];
	unsigned char encrypt_iv[AES_BLOCK_SIZE];
	unsigned char decrypt_iv[AES_BLOCK_SIZE];
	unsigned char decrypt_history[0x100];

	AES_KEY	encrypt_key;
	AES_KEY decrypt_key;
};


#endif //MUMBLE_CRYPTSTATEOCB2_H
