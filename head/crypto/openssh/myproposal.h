/* $OpenBSD: myproposal.h,v 1.32 2013/01/08 18:49:04 markus Exp $ */
/* $FreeBSD: soc2013/dpl/head/crypto/openssh/myproposal.h 249820 2013-03-22 17:55:38Z des $ */

/*
 * Copyright (c) 2000 Markus Friedl.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <openssl/opensslv.h>

#ifdef OPENSSL_HAS_ECC
# define KEX_ECDH_METHODS \
	"ecdh-sha2-nistp256," \
	"ecdh-sha2-nistp384," \
	"ecdh-sha2-nistp521,"
# define HOSTKEY_ECDSA_CERT_METHODS \
	"ecdsa-sha2-nistp256-cert-v01@openssh.com," \
	"ecdsa-sha2-nistp384-cert-v01@openssh.com," \
	"ecdsa-sha2-nistp521-cert-v01@openssh.com,"
# define HOSTKEY_ECDSA_METHODS \
	"ecdsa-sha2-nistp256," \
	"ecdsa-sha2-nistp384," \
	"ecdsa-sha2-nistp521,"
#else
# define KEX_ECDH_METHODS
# define HOSTKEY_ECDSA_CERT_METHODS
# define HOSTKEY_ECDSA_METHODS
#endif

/* Old OpenSSL doesn't support what we need for DHGEX-sha256 */
#if OPENSSL_VERSION_NUMBER >= 0x00907000L
# define KEX_SHA256_METHODS \
	"diffie-hellman-group-exchange-sha256,"
#else
# define KEX_SHA256_METHODS
#endif

# define KEX_DEFAULT_KEX \
	KEX_ECDH_METHODS \
	KEX_SHA256_METHODS \
	"diffie-hellman-group-exchange-sha1," \
	"diffie-hellman-group14-sha1," \
	"diffie-hellman-group1-sha1"

#define	KEX_DEFAULT_PK_ALG	\
	HOSTKEY_ECDSA_CERT_METHODS \
	"ssh-rsa-cert-v01@openssh.com," \
	"ssh-dss-cert-v01@openssh.com," \
	"ssh-rsa-cert-v00@openssh.com," \
	"ssh-dss-cert-v00@openssh.com," \
	HOSTKEY_ECDSA_METHODS \
	"ssh-rsa," \
	"ssh-dss"

#define	KEX_DEFAULT_ENCRYPT \
	"aes128-ctr,aes192-ctr,aes256-ctr," \
	"arcfour256,arcfour128," \
	"aes128-gcm@openssh.com,aes256-gcm@openssh.com," \
	"aes128-cbc,3des-cbc,blowfish-cbc,cast128-cbc," \
	"aes192-cbc,aes256-cbc,arcfour,rijndael-cbc@lysator.liu.se"
#ifdef	NONE_CIPHER_ENABLED
#define KEX_ENCRYPT_INCLUDE_NONE KEX_DEFAULT_ENCRYPT \
	",none"
#endif
#ifdef HAVE_EVP_SHA256
#define	SHA2_HMAC_MODES \
	"hmac-sha2-256," \
	"hmac-sha2-512,"
#else
# define SHA2_HMAC_MODES
#endif
#define	KEX_DEFAULT_MAC \
	"hmac-md5-etm@openssh.com," \
	"hmac-sha1-etm@openssh.com," \
	"umac-64-etm@openssh.com," \
	"umac-128-etm@openssh.com," \
	"hmac-sha2-256-etm@openssh.com," \
	"hmac-sha2-512-etm@openssh.com," \
	"hmac-ripemd160-etm@openssh.com," \
	"hmac-sha1-96-etm@openssh.com," \
	"hmac-md5-96-etm@openssh.com," \
	"hmac-md5," \
	"hmac-sha1," \
	"umac-64@openssh.com," \
	"umac-128@openssh.com," \
	SHA2_HMAC_MODES \
	"hmac-ripemd160," \
	"hmac-ripemd160@openssh.com," \
	"hmac-sha1-96," \
	"hmac-md5-96"

#define	KEX_DEFAULT_COMP	"none,zlib@openssh.com,zlib"
#define	KEX_DEFAULT_LANG	""


static char *myproposal[PROPOSAL_MAX] = {
	KEX_DEFAULT_KEX,
	KEX_DEFAULT_PK_ALG,
	KEX_DEFAULT_ENCRYPT,
	KEX_DEFAULT_ENCRYPT,
	KEX_DEFAULT_MAC,
	KEX_DEFAULT_MAC,
	KEX_DEFAULT_COMP,
	KEX_DEFAULT_COMP,
	KEX_DEFAULT_LANG,
	KEX_DEFAULT_LANG
};
