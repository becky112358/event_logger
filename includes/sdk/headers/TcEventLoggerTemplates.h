#pragma once

#include "TcInterfaces.h"
#include "TcEventLoggerInterfaces.h"


class TcArgs : public _tc_com_ptr_t< _tc_com_IIID<ITcArguments, &__uuidof(ITcArguments)>>
{
public:
	TcArgs(ITcEventLogger* pEventLogger)
	{
		if (pEventLogger)
			pEventLogger->CreateArguments(&m_pInterface);
	}

	TcArgs(ITcEventLoggerPtr& spEventLogger)
	{
		if (spEventLogger)
			spEventLogger->CreateArguments(&m_pInterface);
	}

	TcArgs(ITcMessage* ipMessage)
	{
		if (ipMessage)
			ipMessage->GetArguments(&m_pInterface);
	}

	TcArgs(ITcAlarm* ipAlarm)
	{
		if (ipAlarm)
			ipAlarm->GetArguments(&m_pInterface);
	}

	TcArgs(ITcArguments* ipArgs)
	{
		m_pInterface = ipArgs;
		m_pInterface->TcAddRef();
	}

	void AddArgument() { }
	void AddArgument(bool value) { AddArgumentPriv(TcEventArgumentType::Boolean, &value, sizeof(bool)); }
// void AddArgument(__int8 value) { AddArgumentPriv(TcEventArgumentType::Boolean, &value, sizeof(__int8)); }
// void AddArgument(__int16 value) { AddArgumentPriv( TcEventArgumentType::Int16, &value, sizeof(__int16)); }
	void AddArgument(__int32 value) { AddArgumentPriv(TcEventArgumentType::Int32, &value, sizeof(__int32)); }
	void AddArgument(__int64 value) { AddArgumentPriv(TcEventArgumentType::Int64, &value, sizeof(__int64)); }
	void AddArgument(unsigned __int8 value) { AddArgumentPriv(TcEventArgumentType::UInt8, &value, sizeof(unsigned __int8)); }
// void AddArgument(unsigned __int16 value) { AddArgumentPriv(TcEventArgumentType::UInt16, &value, sizeof(unsigned __int16)); }
	void AddArgument(unsigned __int32 value) { AddArgumentPriv(TcEventArgumentType::UInt32, &value, sizeof(unsigned __int32)); }
	void AddArgument(unsigned long value) { AddArgumentPriv(TcEventArgumentType::UInt32, &value, sizeof(unsigned long)); }
	void AddArgument(unsigned __int64 value) { AddArgumentPriv(TcEventArgumentType::UInt64, &value, sizeof(unsigned __int64)); }
	void AddArgument(float value) { AddArgumentPriv(TcEventArgumentType::Float, &value, sizeof(float)); }
	void AddArgument(double value) { AddArgumentPriv(TcEventArgumentType::Double, &value, sizeof(double)); }

	void AddArgument(char value, TcEventArgumentType eType = TcEventArgumentType::Char) { AddArgumentPriv(eType, &value, sizeof(char)); }

#if _MSC_VER >= 1800
	void AddArgument(wchar_t value) { AddArgumentPriv(TcEventArgumentType::WChar, &value, sizeof(wchar_t)); }
#endif
	void AddArgument(char* value) { AddArgumentPriv(TcEventArgumentType::StringType, value, strlen(value) + 1); }
	void AddArgument(const char* value) { AddArgumentPriv(TcEventArgumentType::StringType, (void*)value, strlen(value) + 1); }

	void AddArgument(wchar_t* value) { AddArgumentPriv(TcEventArgumentType::WStringType, value, (wcslen(value) + 1) * sizeof(wchar_t)); }
	void AddArgument(const wchar_t* value) { AddArgumentPriv(TcEventArgumentType::WStringType, (void*)value, (wcslen(value) + 1) * sizeof(wchar_t)); }

	void AddArgument(const TcEventReference& value) { AddArgumentPriv(TcEventArgumentType::EventReference, (void*)&value, sizeof(TcEventReference)); }
	
	void AddArgument(CAdsLogMessage& value) { AddArgumentPriv(TcEventArgumentType::AdsNotificationStream, (AdsNotificationStream*)value, value.GetDataSize()); }
	
	void AddArgument(const TcBlobArgument& value)
	{
		size_t nBuffer = value.cbData + sizeof(value.cbData);
		BYTE* pBuffer = new unsigned char[nBuffer];

		if (pBuffer != NULL)
		{
			memcpy(pBuffer, &value.cbData, sizeof(value.cbData));
			memcpy(pBuffer + sizeof(value.cbData), value.pData, value.cbData);
			AddArgumentPriv(TcEventArgumentType::Blob, pBuffer, nBuffer);
			delete[] pBuffer;
		}
	}

	void AddArgument(long value) { AddArgumentPriv(TcEventArgumentType::Int32, &value, sizeof(long)); }

#if (_MSC_VER >= 1800) || defined(POSIX)
	template <typename Thead, typename... Ttail>
	void AddArgument(Thead head, Ttail... tail)
	{
		AddArgument(head);
		AddArgument(tail...);
	}
#endif

	void AddString(const char* s, size_t n)
	{
		if (m_pInterface == NULL) return;

		size_t sLen = strlen(s) + 1;

		if (n > 0 && n < sLen)
		{
			char* text = new char[n + 1];

			if (text != NULL)
			{
				memcpy(text, s, n);
				text[n] = 0;
				AddArgumentPriv(TcEventArgumentType::StringType, (void*)text, n + 1);
				delete[] text;
			}
		}
		else
		{
			AddArgumentPriv(TcEventArgumentType::StringType, (void*)s, sLen);
		}
	}

	void AddUtf8EncodedString(const char* s, size_t n)
	{
		if (m_pInterface == NULL) return;

		size_t sLen = strlen(s) + 1;

		if (n > 0 && n < sLen)
		{
			char* text = new char[n + 1];

			if (text != NULL)
			{
				memcpy(text, s, n);
				text[n] = 0;
				AddArgumentPriv(TcEventArgumentType::UTF8EncodedString, (void*)text, n + 1);
				delete[] text;
			}
		}
		else
		{
			AddArgumentPriv(TcEventArgumentType::UTF8EncodedString, (void*)s, sLen);
		}
	}

	void AddString(const wchar_t* s, size_t n)
	{
		if (m_pInterface == NULL)
			return;

		size_t sLen = wcslen(s) + 1;

		if (n > 0 && n < sLen)
		{
			wchar_t* text = new wchar_t[n + 1];

			if (text != NULL)
			{
				memcpy(text, s, n * sizeof(wchar_t));
				text[n] = 0;
				AddArgumentPriv(TcEventArgumentType::WStringType, (void*)text, (n + 1) * sizeof(wchar_t));

				delete[] text;
			}
		}
		else
		{
			AddArgumentPriv(TcEventArgumentType::WStringType, (void*)s, sLen * sizeof(wchar_t));
		}
	}

	void AddExternalTimeStamp(ULONGLONG timeStamp)
	{
		AddArgumentPriv(TcEventArgumentType::ExternalTimestamp, (void*)&timeStamp, sizeof(ULONGLONG));
	}

	void AddFormatString(const char* format)
	{
		AddArgumentPriv(TcEventArgumentType::FormatString, (void*)format, strlen(format) + 1);
	};

	void AddBlob(const BYTE* pData, const ULONG cbData)
	{
		TcBlobArgument blobArgument(pData, cbData);
		AddArgument(blobArgument);
	};

	inline void AddArguments(PCHAR pszFormat, va_list vl)
	{
		if (pszFormat == NULL)
			return;

		ULONG nArgs = 0;
		char szTmpFmt[TCEVENT_MAXARGS + 1];
		int cbFmtLen;

		if ((cbFmtLen = (int)strlen(pszFormat)) > TCEVENT_MAXBUFFERSIZE)
			return;

		if (TryParseFormatString(pszFormat, cbFmtLen, szTmpFmt, nArgs))
		{
			AddArgsToSerializedArguments(szTmpFmt, vl, nArgs);
		}
	}

	inline void AddArguments(PCHAR pszFormat, ...)
	{
		va_list vl;
		va_start(vl, pszFormat);
		AddArguments(pszFormat, vl);
		va_end(vl);
	};

	inline void AddArgumentBase(TcEventArgumentType eType, void * pData, size_t cbData)
	{
		 AddArgumentPriv(eType, pData, cbData);
	}

private:
	inline void AddArgumentPriv(TcEventArgumentType eType, void* pData, size_t cbData)
	{
		if (m_pInterface == NULL)
			return;

		bool bAddWithOwnership = true;

		if (ITcVersionProviderPtr spVersionProvider = m_pInterface)
		{
			bAddWithOwnership = false;
		}

		void* pBuffer = pData;

		if (bAddWithOwnership)
		{
			pBuffer = new BYTE[cbData];
			if (pBuffer == NULL)
				return;
			memcpy(pBuffer, pData, cbData);
		}
		
		m_pInterface->AddArgument(eType, pBuffer, (ULONG)cbData);
	}

	inline static bool TryParseFormatString(PCHAR pszFormat, size_t cbFmtLen, char* pszArgs, ULONG& rnArgs)
	{
		rnArgs = 0;

		for (ULONG i = 0; i<cbFmtLen; i++)
		{
			if (pszFormat[i] == '%')
			{
				i++;
				for (; i<cbFmtLen; i++)
				{
					char cFormat = pszFormat[i];
					if (isalpha(cFormat) || cFormat == '%' || cFormat == ',')
						break;
					if (cFormat == '*')
						pszArgs[rnArgs++] = cFormat;
				}
				if (i == cbFmtLen)
					return false;

				// check for "ll" prefix (64bit)
				bool bLong = false;
				if ((i + 1 < cbFmtLen) && (pszFormat[i] == 'l'))
				{
					i++;
					// one 'l' means long, skipped
					if ((i + 1 < cbFmtLen) && (pszFormat[i] == 'l'))
					{
						// second one counts for 64 bit data type
						bLong = true;
						i++;
					}
				}

				switch (char cFormat = pszFormat[i])
				{
				case 'i':
				case 'u':
				case 'x':
				case 'X':
					if (bLong)
						pszArgs[rnArgs++] = 'L'; // add temporal format for 64bit int
					else
						pszArgs[rnArgs++] = cFormat;
					break;

				case 'a':
					pszFormat[i] = 's'; // patch for FormatV
				case '*':
				case 'c':
				case 'd':
				case 'o':
				case 'p':
				case 'P':
				case 's':
				case 'e':
				case 'E':
				case 'g':
				case 'G':
				case 'f':
				case 'q':	// special modes for pointer (saved with leading size)
				case 'Q':

					// long mode only valid for iuxX
					if (bLong)
						return false;

					pszArgs[rnArgs++] = cFormat;
					break;
				case '%':
					break;
				case 'n':  // not supported for ADS log messages, because it makes no sense
				default:
					return false;
				}
			}
			if (rnArgs > TCEVENT_MAXARGS)
				return false;
		}

		return true;
	}

	inline long AddArgsToSerializedArguments(const char* pszFmt, va_list vl, ULONG nArgs)
	{
		ULONG i;
		for (i = 0; i<nArgs; i++)
		{
			switch (pszFmt[i])
			{
			case '*':
			case 'c':
			case 'd':
			case 'i':
			case 'o':
			case 'u':
			case 'x':
			case 'X':
#ifdef _X64_
				AddArgument(va_arg(vl, __int64));
#else
				AddArgument(va_arg(vl, int));
#endif
				break;
			case 'L':
				AddArgument(va_arg(vl, __int64));
				break;
			case 'p':
			case 'P':
#ifdef _X64_
				AddArgument(va_arg(vl, __int64));
#else
				AddArgument(va_arg(vl, int));
#endif
				break;

			case 'e':
			case 'E':
			case 'g':
			case 'G':
			case 'f':
				AddArgument(va_arg(vl, double));
				break;
			case 'a':
			{
				int eventId = 0;
				char* sEventReference = va_arg(vl, char*);

				if (sEventReference != NULL && sscanf(sEventReference, "[E%d]", &eventId) == 1)
				{
					AddArgument(TcEventReference(eventId));
				}
				else
				{
					AddArgument(sEventReference);
				}
			}
			break;
			case 's':
				AddArgument(va_arg(vl, char*));
				break;
			case 'q':
			case 'Q':
			{
#ifdef _X64_
				AddArgument(va_arg(vl, __int64));
#else
				AddArgument(va_arg(vl, int));
#endif
			}
			break;
			case 'n':  // not supported for ADS log messages, because it makes no sense
			default:
				return E_INVALIDARG;
				break;
			}
		}
		return 0;
	}
};

////////////////////////////////////////////////////////////////////////////////
#if _MSC_VER >= 1900
template <typename... T>
inline HRESULT Raise(ITcAlarm* ipAlarm, const T&... args)
{
	if (!ipAlarm)
		return E_POINTER;

	TcArgs tcArgs(ipAlarm);
	tcArgs->Clear();
	tcArgs.AddArgument(args...);
	return ipAlarm->Raise(0);
};

template <typename... T>
inline HRESULT Send(ITcMessage* ipMessage, const T&... args)
{
	if (!ipMessage)
		return E_POINTER;

	TcArgs tcArgs(ipMessage);
	tcArgs->Clear();
	tcArgs.AddArgument(args...);
	return ipMessage->Send(0);
};


template <typename... T>
inline HRESULT SendTcMessage(ITcEventLogger* ipLogger, const GUID& eventClass, ULONG eventId, TcEventSeverity severity, ITcSourceInfo* ipSourceInfo, const T&... args)
{
	if (!ipLogger)
		return E_POINTER;

	TcArgs tcArgs(ipLogger);
	tcArgs.AddArgument(args...);

	return ipLogger->SendTcMessage(eventClass, eventId, severity, ipSourceInfo, 0, tcArgs);
};


template <typename... T>
inline HRESULT SendTcMessageEx(ITcEventLogger* ipLogger, const TcEventEntry& eventEntry, ITcSourceInfo* ipSourceInfo, const T&... args)
{
	return SendTcMessage(ipLogger, eventEntry.uuidEventClass, eventEntry.nEventId, eventEntry.eSeverity, ipSourceInfo, args...);
};
#endif
