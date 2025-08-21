///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcInterfaces.h"
#include "TcFileAccessServices.h"

#define ITCFILEACCESS5_SUPPORT

struct __declspec(novtable) ITcFileAccess : public ITcUnknown
{
	TCOMMETHOD(FileOpen (PCCH szFileName, TcFileAccessMode AccessMode, PTcFileHandle phFile));
	TCOMMETHOD(FileClose(TcFileHandle hFile));
	TCOMMETHOD(FileRead (TcFileHandle hFile, PVOID pData, UINT cbData, PUINT pcbRead));
	TCOMMETHOD(FileWrite(TcFileHandle hFile, PCVOID pData, UINT cbData, PUINT pcbWrite));
	TCOMMETHOD(FileSeek (TcFileHandle hFile, UINT uiPos));
	TCOMMETHOD(FileTell (TcFileHandle hFile, PUINT puiPos));

	TCOMMETHOD(FileRename   (PCCH szOldName, PCCH szNewName));
	TCOMMETHOD(FileDelete   (PCCH szFileName));
	TCOMMETHOD(FileGetStatus(PCCH szFileName, PTcFileStatus pFileStatus));

	TCOMMETHOD(FileFindFirst(PCCH szFileName, PTcFileFindData pFileFindData , PTcFileFindHandle phFileFind));
	TCOMMETHOD(FileFindNext (TcFileFindHandle hFileFind, PTcFileFindData pFileFindData));
	TCOMMETHOD(FileFindClose(TcFileFindHandle hFileFind));

	TCOMMETHOD(MkDir(PCCH szDir));
	TCOMMETHOD(RmDir(PCCH szDir));
};
_TCOM_SMARTPTR_TYPEDEF(ITcFileAccess, IID_ITcFileAccess);

struct __declspec(novtable) ITcFileAccess2 : public ITcFileAccess
{
	TCOMMETHOD(FileCopy(PCCH szSrcName, PCCH szDestName));
};
_TCOM_SMARTPTR_TYPEDEF(ITcFileAccess2, IID_ITcFileAccess2);

struct __declspec(novtable) ITcFileAccess3 : public ITcFileAccess2
{
	TCOMMETHOD(FileFlush(TcFileHandle hFile));
	TCOMMETHOD(FileTruncate(TcFileHandle hFile, UINT uiPos));
};
_TCOM_SMARTPTR_TYPEDEF(ITcFileAccess3, IID_ITcFileAccess3);

struct __declspec(novtable) ITcFileAccess4 : public ITcFileAccess3
{
	TCOMMETHOD(FileGenerateCRC(PCHAR szFileName, PUINT pulCRC));
};
_TCOM_SMARTPTR_TYPEDEF(ITcFileAccess4, IID_ITcFileAccess4);

struct __declspec(novtable) ITcFileAccess5 : public ITcFileAccess4
{
	TCOMMETHOD(FileRename(PCCH szOldName, PCCH szNewName, USHORT openPath));
	TCOMMETHOD(FileDelete(PCCH szFileName, USHORT openPath));
	TCOMMETHOD(FileGetStatus(PCCH szFileName, USHORT openPath, PTcFileStatus pFileStatus));
	TCOMMETHOD(FileFindFirst(PCCH szFileName, USHORT openPath, PTcFileFindData pFileFindData, PTcFileFindHandle phFileFind));
	TCOMMETHOD(MkDir(PCCH szDir, USHORT openPath));
	TCOMMETHOD(RmDir(PCCH szDir, USHORT openPath));
	TCOMMETHOD(FileCopy(PCCH szSrcName, PCCH szDestName, USHORT openPath, bool bOverride));
	TCOMMETHOD(FileGenerateCRC(PCHAR szFileName, USHORT openPath, PUINT pulCRC));
};
_TCOM_SMARTPTR_TYPEDEF(ITcFileAccess5, IID_ITcFileAccess5);

struct __declspec(novtable) ITcFileAccessAsync : public ITcFileAccess
{
	TCOMMETHOD(Check());
}; 
_TCOM_SMARTPTR_TYPEDEF(ITcFileAccessAsync, IID_ITcFileAccessAsync);

struct __declspec(novtable) ITcFileAccessAsync2 : public ITcFileAccess2
{
	TCOMMETHOD(Check());
};
_TCOM_SMARTPTR_TYPEDEF(ITcFileAccessAsync2, IID_ITcFileAccessAsync2);

struct __declspec(novtable) ITcFileAccessAsync3 : public ITcFileAccess3
{
	TCOMMETHOD(Check());
};
_TCOM_SMARTPTR_TYPEDEF(ITcFileAccessAsync3, IID_ITcFileAccessAsync3);

struct __declspec(novtable) ITcFileAccessAsync4 : public ITcFileAccess4
{
	TCOMMETHOD(Check());
};
_TCOM_SMARTPTR_TYPEDEF(ITcFileAccessAsync4, IID_ITcFileAccessAsync4);

struct __declspec(novtable) ITcFileAccessAsync5 : public ITcFileAccess5
{
	TCOMMETHOD(Check());
};
_TCOM_SMARTPTR_TYPEDEF(ITcFileAccessAsync5, IID_ITcFileAccessAsync5);


#ifndef EOF
#define EOF     (-1)
#endif

#ifndef SEEK_SET
#define SEEK_SET        0               /* seek to an absolute position */
#define SEEK_CUR        1               /* seek relative to current position */
#define SEEK_END        2               /* seek relative to end of file */
#endif  /* ifndef SEEK_SET */

struct __declspec(novtable) ITcFileAccessCrt : public ITcUnknown
{
	TCOMMETHOD(FAC_fopen(PCCH szFileName, PCCH szMode, PTcFileHandle phFile));
	TCOMMETHOD(FAC_fopen(PCCH szFileName, PCCH szMode, USHORT openPath, PTcFileHandle phFile));
	TCOMMETHOD(FAC_fclose(TcFileHandle hFile));
	TCOMMETHOD(FAC_fread(TcFileHandle hFile, PVOID pData, ULONG_PTR cbData, PULONG_PTR pcbRead));
	TCOMMETHOD(FAC_fwrite(TcFileHandle hFile, PCVOID pData, ULONG_PTR cbData, PULONG_PTR pcbWritten));
	TCOMMETHOD(FAC_fseek(TcFileHandle hFile, LONG uiPos, INT origin=SEEK_SET));
	TCOMMETHOD(FAC_ftell(TcFileHandle hFile, PLONG puiPos));
	TCOMMETHOD(FAC_fgets(TcFileHandle hFile, PCHAR pData, LONG cbData));
	TCOMMETHOD(FAC_fputs(TcFileHandle hFile, PCCH pData));
	TCOMMETHOD(FAC_feof(TcFileHandle hFile, PLONG pEof));
	TCOMMETHOD(FAC_flasterror(PLONG pErr));
};
_TCOM_SMARTPTR_TYPEDEF(ITcFileAccessCrt, IID_ITcFileAccessCrt);

struct __declspec(novtable) ITcFileEncryption : public ITcUnknown
{
	TCOMMETHOD(FileOpen (PCCH szFileName, TcFileAccessMode AccessMode, PBYTE pKey, ULONG nKey, PTcFileHandle phFile));
	TCOMMETHOD(FileOpen (PCCH szFileName, TcFileAccessMode AccessMode, PCHAR szPassword, PTcFileHandle phFile));
}; 
_TCOM_SMARTPTR_TYPEDEF(ITcFileEncryption, IID_ITcFileEncryption);

struct __declspec(novtable) ITcDecrypterInplace : public ITcUnknown
{
	TCOMMETHOD(InitKeyAndData(PBYTE pKey, ULONG nKey, PBYTE pData, ULONG nData));
	TCOMMETHOD(GetBlockSize(ULONG& nBlockSize));
	TCOMMETHOD(DecryptAll());
	TCOMMETHOD(DecryptBlocks(ULONG nBlocks, ULONG& nRemainingBlocks));
	TCOMMETHOD(GetDecryptedData(PBYTE& pDecryptedData, ULONG& nDecryptedData));
};
_TCOM_SMARTPTR_TYPEDEF(ITcDecrypterInplace, IID_ITcDecrypterInplace);
