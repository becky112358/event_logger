///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcServices.h"

const CTCID CID_TcFileAccess       = {0xb8f15811,0x5278,0x4ad8,{0xa1,0x5d,0x26,0x2f,0x5a,0xd7,0x68,0xca}};
const CTCID CID_TcFileAccessAsync  = {0xb7c8953b,0xfda9,0x45ff,{0x81,0x19,0x2d,0x9d,0x71,0x80,0xa7,0xb9}};
const CTCID CID_TcDecrypterInplace = {0x973636ce,0x8a02,0x44c2,{0x89,0x37,0x00,0x52,0x59,0x6f,0xaf,0x6e}};

TCOM_DECL_INTERFACE("742A7429-DA6D-4C1D-80D8-398D8C1F1747", ITcFileAccess)
TCOM_DECL_INTERFACE("3FF69D65-9950-443D-98F1-6FBB4B8ACF8D", ITcFileAccess2)
TCOM_DECL_INTERFACE("5FA8045E-CB2C-4981-875F-C117FB2F7A31", ITcFileAccess3)
TCOM_DECL_INTERFACE("1432EE66-6045-4885-B17E-761BBE62A772", ITcFileAccess4)
TCOM_DECL_INTERFACE("8FD5AB27-8602-4E8D-A034-9FF5E7DAF589", ITcFileAccess5)
TCOM_DECL_INTERFACE("C04AC244-C126-466E-982E-93EC571F2277", ITcFileAccessAsync)
TCOM_DECL_INTERFACE("A00E3363-D7A2-42CC-AC2A-42F508DD8665", ITcFileAccessAsync2)
TCOM_DECL_INTERFACE("8A0DED25-DC06-44DC-A68F-4DBD48AD9D32", ITcFileAccessAsync3)
TCOM_DECL_INTERFACE("471F4DA8-83BB-4795-8CE3-B970C2278353", ITcFileAccessAsync4)
TCOM_DECL_INTERFACE("9D402627-1CEE-4A90-877A-AEDD0EA0C179", ITcFileAccessAsync5)
TCOM_DECL_INTERFACE("1750EFB8-09AC-458E-9650-F3668E1D38D5", ITcFileAccessCrt)
TCOM_DECL_INTERFACE("93E1CAC9-62B2-413C-9B9B-3A9A16D342EE", ITcFileEncryption)
TCOM_DECL_INTERFACE("00D0317E-0DA1-4DDE-A6A5-963B28A498BC", ITcDecrypterInplace)

const PTCID PID_TcFileAccessAsyncAdsProvider = 0x00000001; 
const PTCID PID_TcFileAccessAsyncNetId       = 0x00000002; // AmsNetId of the system service use for file access
const PTCID PID_TcFileAccessAsyncNetIdStr    = 0x00000003; // String with AmsNetId of the system service use for file access
const PTCID PID_TcFileAccessAsyncTimeoutMs   = 0x00000004; // Timeout used for a file access
const PTCID PID_TcFileAccessAsyncSegmentSize = 0x00000005; // Read and write file access is fragmented using thissegment size

typedef DWORD TcFileHandle, *PTcFileHandle;
typedef DWORD TcFileFindHandle, *PTcFileFindHandle;

typedef enum TcFileAccessMode
{
	amRead            = 0x00000001,
	amWrite           = 0x00000002,
	amAppend          = 0x00000004,
	amPlus            = 0x00000008,
	amBinary          = 0x00000010,
	amReadBinary      = 0x00000011,
	amWriteBinary     = 0x00000012,
	amText            = 0x00000020,
	amReadText        = 0x00000021,
	amWriteText       = 0x00000022,
	amEnsureDirectory = 0x00000040,
	amReadBinaryED    = 0x00000051,
	amWriteBinaryED   = 0x00000052,
	amReadTextED      = 0x00000061,
	amWriteTextED     = 0x00000062,
	amEncryption      = 0x00000080,
	amReadBinEnc      = 0x00000091,
	amWriteBinEnc     = 0x00000092,
	amReadBinEncED    = 0x000000d1,
	amWriteBinEncED   = 0x000000d2,
} TcFileAccessMode, *PTcFileAccessMode;

typedef enum TcFileOpenPath
{
	opDefault         = 0x00000000,
	opGeneric         = 0x00010000,
	opBootPrj         = 0x00020000,
	opBootData        = 0x00030000,
	opBootPath        = 0x00040000,
	opTargetPath      = 0x00050000,
	opConfigPath      = 0x00060000,
	opTc3Path         = 0x00070000,
	opTc3Repository   = 0x00080000,
	opTc3UserPath1    = 0x000B0000,
	opTc3UserPath2    = 0x000C0000,
	opTc3UserPath3    = 0x000D0000,
	opTc3UserPath4    = 0x000E0000,
	opTc3UserPath5    = 0x000F0000,
	opTc3UserPath6    = 0x00100000,
	opTc3UserPath7    = 0x00110000,
	opTc3UserPath8    = 0x00120000,
	opTc3UserPath9    = 0x00130000,
} TcFileOpenPath, *PTcFileOpenPath;

#pragma warning(push)
#pragma warning(disable: 4201)
typedef struct TcFileStatus
{
	union
	{
		ULONGLONG ulFileSize;
		struct
		{
			ULONG ulFileSizeLow;
			ULONG ulFileSizeHigh;
		};
	};
	ULONGLONG  ulCreateTime;
	ULONGLONG  ulModifiedTime;
	ULONGLONG  ulReadTime;
	DWORD      dwAttribute;
	DWORD      wReserved0;
} TcFileStatus, *PTcFileStatus;
#pragma warning(pop)


typedef struct TcFileFindData
{
	TcFileHandle hFile;
	DWORD       dwFileAttributes;
	ULONGLONG   ui64CreationTime;
	ULONGLONG   ui64LastAccessTime;
	ULONGLONG   ui64LastWriteTime;
	DWORD       dwFileSizeHigh;
	DWORD       dwFileSizeLow;
	DWORD       dwReserved1;
	DWORD       dwReserved2;
	CHAR        cFileName[260];
	CHAR        cAlternateFileName[14];
	WORD        wReserved0;
} TcFileFindData, *PTcFileFindData;
