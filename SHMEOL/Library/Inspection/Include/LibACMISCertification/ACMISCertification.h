#pragma once

#include "export.h"
#include <LibACMISCommon\ACMISCommon.h>
#include <LibACMISCertification\ACMISCertificationDef.h>

namespace ACMISCertification
{
	ACMISCERTIFICATION_API bool IsCertified();
	ACMISCERTIFICATION_API bool IsCertified(std::string strType);
	ACMISCERTIFICATION_API int GetLastError();
	ACMISCERTIFICATION_API std::string GetLastErrorString();

	ACMISCERTIFICATION_API bool SetCertificateKeyInfo(std::string strType, CertificationParam tParams);
	ACMISCERTIFICATION_API bool GetCertificateKeyInfo(std::string strType, CertificationParam& tParams);

	ACMISCERTIFICATION_API bool CertificateKeyOpen(std::string strType, std::string strKey, std::string strPassword);
	ACMISCERTIFICATION_API bool CertificateKeyClose(std::string strType);
	ACMISCERTIFICATION_API bool CertificateKeyWrite(std::string strType, int nStartPos, std::string strQuery, std::string strData);
	ACMISCERTIFICATION_API bool CertificateKeyRead(std::string strType, int nStartPos, int nDataSize, std::string strQuery, std::string& strData);

	ACMISCERTIFICATION_API bool EncDecMSg(std::string strMsg, std::string strPassword, std::string strSalt, bool bIsEncrypt, std::string& strOutput);
	ACMISCERTIFICATION_API bool EncryptMsg(std::string strKey, std::string strPassword, std::string strPlainMsg, bool bIsPublic, bool bIsKeyFile, std::string& strEncMsg);
	ACMISCERTIFICATION_API bool DecryptMsg(std::string strKey, std::string strPassword, std::string strEncMsg, bool bIsPublic, bool bIsKeyFile, std::string& strPlainMsg);

	ACMISCERTIFICATION_API bool MakeCertificationFile(std::string strKey, std::string strPassword, std::string strSalt);
	ACMISCERTIFICATION_API bool MakeRandomCertificationFile(std::string strType);
};



