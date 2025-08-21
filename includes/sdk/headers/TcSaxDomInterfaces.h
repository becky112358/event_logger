///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "TcSaxDomServices.h"

typedef struct _TcJsonLevelInfo
{
	PCCH	key;
	ULONG lenIdx;
} TcJsonLevelInfo, *PTcJsonLevelInfo;

struct	__declspec(novtable)	ITcJsonSaxValues : public ITcUnknown
{
	virtual	HRESULT TCOMAPI	OnStringValue(ULONG level, PTcJsonLevelInfo infos, PCCH value, ULONG len) = 0;
	virtual	HRESULT TCOMAPI	OnDintValue(ULONG level, PTcJsonLevelInfo infos, LONG value) = 0;
	virtual	HRESULT TCOMAPI	OnUdintValue(ULONG level, PTcJsonLevelInfo infos, ULONG value) = 0;
	virtual	HRESULT TCOMAPI	OnLintValue(ULONG level, PTcJsonLevelInfo infos, LONGLONG value) = 0;
	virtual	HRESULT TCOMAPI	OnUlintValue(ULONG level, PTcJsonLevelInfo infos, ULONGLONG value) = 0;
	virtual	HRESULT TCOMAPI	OnLrealValue(ULONG level, PTcJsonLevelInfo infos, double value) = 0;
	virtual	HRESULT TCOMAPI	OnBoolValue(ULONG level, PTcJsonLevelInfo infos, bool value) = 0;
	virtual	HRESULT TCOMAPI	OnNullValue(ULONG level, PTcJsonLevelInfo infos) = 0;
	virtual	HRESULT TCOMAPI	OnRawNumberValue(ULONG level, PTcJsonLevelInfo infos, PCCH value, ULONG len) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcJsonSaxValues, IID_ITcJsonSaxValues);

struct	__declspec(novtable)	ITcJsonSaxHandler : public ITcUnknown
{
	virtual	HRESULT TCOMAPI	OnStartObject() = 0;
	virtual	HRESULT TCOMAPI	OnEndObject(ULONG memberCount) = 0;
	virtual	HRESULT TCOMAPI	OnStartArray() = 0;
	virtual	HRESULT TCOMAPI	OnEndArray(ULONG elementCount) = 0;
	virtual	HRESULT TCOMAPI	OnKey(PCCH key, ULONG len) = 0;
	virtual	HRESULT TCOMAPI	OnString(PCCH value, ULONG len) = 0;
	virtual	HRESULT TCOMAPI	OnDint(LONG value) = 0;
	virtual	HRESULT TCOMAPI	OnUdint(ULONG value) = 0;
	virtual	HRESULT TCOMAPI	OnLint(LONGLONG value) = 0;
	virtual	HRESULT TCOMAPI	OnUlint(ULONGLONG value) = 0;
	virtual	HRESULT TCOMAPI	OnLreal(double value) = 0;
	virtual	HRESULT TCOMAPI	OnBool(bool value) = 0;
	virtual	HRESULT TCOMAPI	OnNull() = 0;
	virtual	HRESULT TCOMAPI	OnRawNumber(PCCH value, ULONG len) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcJsonSaxHandler, IID_ITcJsonSaxHandler);

struct	__declspec(novtable)	ITcJsonSaxReader : public ITcUnknown
{
	virtual	HRESULT TCOMAPI	Parse(PCCH sJson, ITcJsonSaxHandler* ipHdl) = 0;
	virtual	HRESULT TCOMAPI	ParseValues(PCCH sJson, ITcJsonSaxValues* ipHdl) = 0;
	virtual	HRESULT TCOMAPI	GetLastParseResult(PLONGLONG pOffset, PLONG pError) = 0;
	virtual	HRESULT TCOMAPI	IsBase64(PCCH sBase64) = 0;
	virtual	HRESULT TCOMAPI	DecodeBase64(PCCH sBase64, PBYTE pBytes, LONG& nBytes) = 0;
	virtual	HRESULT TCOMAPI	IsHexBinary(PCCH sHex) = 0;
	virtual	HRESULT TCOMAPI	DecodeHexBinary(PCCH sHex, PBYTE pBytes, LONG& nBytes) = 0;
	virtual	HRESULT TCOMAPI	IsISO8601TimeFormat(PCCH sDT) = 0;
	virtual	HRESULT TCOMAPI	DecodeDateTime(PCCH sDT, PULONG pDT) = 0;
	virtual	HRESULT TCOMAPI	DecodeDcTime(PCCH sDc, PLONGLONG pDc) = 0;
	virtual	HRESULT TCOMAPI	DecodeFileTime(PCCH sDc, PLONGLONG pFT) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcJsonSaxReader, IID_ITcJsonSaxReader);

struct	__declspec(novtable)	ITcJsonSaxWriter : public ITcUnknown
{
	virtual	HRESULT TCOMAPI	StartObject() = 0;
	virtual	HRESULT TCOMAPI	EndObject() = 0;
	virtual	HRESULT TCOMAPI	StartArray() = 0;
	virtual	HRESULT TCOMAPI	EndArray() = 0;
	virtual	HRESULT TCOMAPI	AddKey(PCCH key) = 0;
	virtual	HRESULT TCOMAPI	AddString(PCCH value) = 0;
	virtual	HRESULT TCOMAPI	AddDint(LONG value) = 0;
	virtual	HRESULT TCOMAPI	AddUdint(ULONG value) = 0;
	virtual	HRESULT TCOMAPI	AddLint(LONGLONG value) = 0;
	virtual	HRESULT TCOMAPI	AddUlint(ULONGLONG value) = 0;
	virtual	HRESULT TCOMAPI	AddReal(float value) = 0;
	virtual	HRESULT TCOMAPI	AddLreal(double value) = 0;
	virtual	HRESULT TCOMAPI	AddBool(bool value) = 0;
	virtual	HRESULT TCOMAPI	AddNull() = 0;
	virtual	HRESULT TCOMAPI	AddBase64(PBYTE pBytes, LONG nBytes) = 0;
	virtual	HRESULT TCOMAPI	AddHexBinary(PBYTE pBytes, LONG nBytes, BOOL bUpperCase=FALSE) = 0;
	virtual	HRESULT TCOMAPI	AddDateTime(ULONG value) = 0;
	virtual	HRESULT TCOMAPI	AddDcTime(LONGLONG value) = 0;
	virtual	HRESULT TCOMAPI	AddFileTime(LONGLONG value) = 0;
	virtual	HRESULT TCOMAPI	AddRawObject(PCCH rawJson) = 0;
	virtual	HRESULT TCOMAPI	AddRawArray(PCCH rawJson) = 0;
	virtual	HRESULT TCOMAPI	AddKeyString(PCCH key, PCCH value) = 0;
	virtual	HRESULT TCOMAPI	AddKeyNumber(PCCH key, LONG value) = 0;
	virtual	HRESULT TCOMAPI	AddKeyLreal(PCCH key, double value) = 0;
	virtual	HRESULT TCOMAPI	AddKeyBool(PCCH key, bool value) = 0;
	virtual	HRESULT TCOMAPI	AddKeyNull(PCCH key) = 0;
	virtual	HRESULT TCOMAPI	AddKeyDateTime(PCCH key, ULONG value) = 0;
	virtual	HRESULT TCOMAPI	AddKeyDcTime(PCCH key, LONGLONG value) = 0;
	virtual	HRESULT TCOMAPI	AddKeyFileTime(PCCH key, LONGLONG value) = 0;
	virtual	HRESULT TCOMAPI	GetDocument(PCHAR* ppDoc, PULONG pnDoc=NULL) = 0;
	virtual	HRESULT TCOMAPI	CopyDocument(PCHAR pDoc, ULONG& nDoc) = 0;
	virtual	HRESULT TCOMAPI	ResetDocument() = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcJsonSaxWriter, IID_ITcJsonSaxWriter);

struct	__declspec(novtable)	ITcJsonSaxWriter2 : public ITcJsonSaxWriter
{
	virtual	HRESULT TCOMAPI	IsComplete() = 0;
	virtual	HRESULT TCOMAPI	GetMaxDecimalPlaces(LONG* pDP) = 0;
	virtual	HRESULT TCOMAPI	SetMaxDecimalPlaces(LONG dp) = 0;
};

enum EJsonPrettyFormatOptions {
	eFormatDefault = 0,         //!< Default pretty formatting.
	eFormatSingleLineArray = 1  //!< Format arrays on a single line.
};
struct	__declspec(novtable)	ITcJsonSaxPrettyWriter : public ITcUnknown
{
	virtual	HRESULT TCOMAPI	SetIndent(char indentChar, ULONG indentCharCount) = 0;
	virtual	HRESULT TCOMAPI	SetFormatOptions(EJsonPrettyFormatOptions options) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcJsonSaxPrettyWriter, IID_ITcJsonSaxPrettyWriter);

enum EJsonType {
	eNullType = 0,      // null
	eFalseType = 1,     // false
	eTrueType = 2,      // true
	eObjectType = 3,    // object
	eArrayType = 4,     // array 
	eStringType = 5,    // string
	eNumberType = 6     // number
};
struct	__declspec(novtable)	TJsonValue {};
struct	__declspec(novtable)	TJsonIterator {};
typedef TJsonValue*		SJsonValue;
typedef TJsonIterator*	SJsonIterator;
typedef SJsonValue*		SJsonAIterator;
struct	__declspec(novtable)	ITcJsonDomParser : public ITcUnknown
{
	virtual	SJsonValue		TCOMAPI	NewDocument()=0;
	virtual	SJsonValue		TCOMAPI	ParseDocument(PCCH sJson)=0;
	virtual	SJsonValue		TCOMAPI	GetDocumentRoot()=0;
	virtual	PCCH				TCOMAPI	GetDocument()=0;
	virtual	PCCH				TCOMAPI	GetJson(SJsonValue v)=0;
	virtual	ULONG				TCOMAPI	CopyDocument(PCHAR pDoc, ULONG nDoc)=0;
	virtual	ULONG				TCOMAPI	CopyJson(SJsonValue v, PCHAR pDoc, ULONG nDoc)=0;
	virtual	EJsonType		TCOMAPI	GetType(SJsonValue v)=0;
	virtual	bool				TCOMAPI	IsNull(SJsonValue v)=0;
	virtual	bool				TCOMAPI	IsTrue(SJsonValue v)=0;
	virtual	bool				TCOMAPI	IsFalse(SJsonValue v)=0;
	virtual	bool				TCOMAPI	IsBool(SJsonValue v)=0;
	virtual	bool				TCOMAPI	IsObject(SJsonValue v)=0;
	virtual	bool				TCOMAPI	IsArray(SJsonValue v)=0;
	virtual	bool				TCOMAPI	IsNumber(SJsonValue v)=0;
	virtual	bool				TCOMAPI	IsInt(SJsonValue v)=0;
	virtual	bool				TCOMAPI	IsUint(SJsonValue v)=0;
	virtual	bool				TCOMAPI	IsInt64(SJsonValue v)=0;
	virtual	bool				TCOMAPI	IsUint64(SJsonValue v)=0;
	virtual	bool				TCOMAPI	IsDouble(SJsonValue v)=0;
	virtual	bool				TCOMAPI	IsString(SJsonValue v)=0;
	virtual	bool				TCOMAPI	IsISO8601TimeFormat(SJsonValue v)=0;
	virtual	bool				TCOMAPI	IsHexBinary(SJsonValue v)=0;
	virtual	bool				TCOMAPI	IsBase64(SJsonValue v)=0;

	virtual	bool				TCOMAPI	GetBool(SJsonValue v)=0;
	virtual	LONG				TCOMAPI	GetInt(SJsonValue v)=0;
	virtual	ULONG				TCOMAPI	GetUint(SJsonValue v)=0;
	virtual	LONGLONG			TCOMAPI	GetInt64(SJsonValue v)=0;
	virtual	ULONGLONG		TCOMAPI	GetUint64(SJsonValue v)=0;
	virtual	double			TCOMAPI	GetDouble(SJsonValue v)=0;
	virtual	PCCH				TCOMAPI	GetString(SJsonValue v)=0;
	virtual	ULONG				TCOMAPI	GetArraySize(SJsonValue v)=0;
	virtual	ULONG				TCOMAPI	GetDateTime(SJsonValue v)=0;
	virtual	LONGLONG			TCOMAPI	GetDcTime(SJsonValue v)=0;
	virtual	LONGLONG			TCOMAPI	GetFileTime(SJsonValue v)=0;
	virtual	LONG				TCOMAPI	GetHexBinary(SJsonValue v, PVOID pBuffer, LONG nBuffer)=0;	// -1 indicates a parse error
	virtual	LONG				TCOMAPI	GetBase64(SJsonValue v, PVOID pBuffer, LONG nBuffer)=0;	// -1 indicates a parse error

	virtual	SJsonIterator	TCOMAPI	MemberBegin(SJsonValue v)=0;
	virtual	SJsonIterator	TCOMAPI	MemberEnd(SJsonValue v)=0;
	virtual	SJsonValue		TCOMAPI	FindMember(SJsonValue v, PCCH member)=0;	// find first direct member
	virtual	SJsonValue		TCOMAPI	FindMemberPath(SJsonValue v, PCCH member)=0;	// member seperatet by '/' without leading '/' ('/' in a member name will be encoded "~1" and '~' as "~0")
	virtual	bool				TCOMAPI	HasMember(SJsonValue v, PCCH member)=0;
	virtual	bool				TCOMAPI	RemoveMember(SJsonValue v, SJsonIterator i, bool keepOrder = false)=0;
	virtual	bool				TCOMAPI	RemoveMemberByName(SJsonValue v, PCCH member, bool keepOrder = false)=0;
	virtual	bool				TCOMAPI	RemoveAllMembers(SJsonValue v)=0;
	virtual	SJsonIterator	TCOMAPI	NextMember(SJsonIterator i)=0;
	virtual	PCCH				TCOMAPI	GetMemberName(SJsonIterator i)=0;
	virtual	SJsonValue		TCOMAPI	GetMemberValue(SJsonIterator i)=0;

	virtual	SJsonValue		TCOMAPI	AddIntMember(SJsonValue v, PCCH member, LONG value)=0;
	virtual	SJsonValue		TCOMAPI	AddUintMember(SJsonValue v, PCCH member, ULONG value)=0;
	virtual	SJsonValue		TCOMAPI	AddInt64Member(SJsonValue v, PCCH member, LONGLONG value)=0;
	virtual	SJsonValue		TCOMAPI	AddUint64Member(SJsonValue v, PCCH member, ULONGLONG value)=0;
	virtual	SJsonValue		TCOMAPI	AddDoubleMember(SJsonValue v, PCCH member, double value)=0;
	virtual	SJsonValue		TCOMAPI	AddBoolMember(SJsonValue v, PCCH member, bool value)=0;
	virtual	SJsonValue		TCOMAPI	AddNullMember(SJsonValue v, PCCH member)=0;
	virtual	SJsonValue		TCOMAPI	AddStringMember(SJsonValue v, PCCH member, PCCH value)=0;
	virtual	SJsonValue		TCOMAPI	AddDateTimeMember(SJsonValue v, PCCH member, ULONG value)=0;
	virtual	SJsonValue		TCOMAPI	AddDcTimeMember(SJsonValue v, PCCH member, LONGLONG value)=0;
	virtual	SJsonValue		TCOMAPI	AddFileTimeMember(SJsonValue v, PCCH member, LONGLONG value)=0;
	virtual	SJsonValue		TCOMAPI	AddHexBinaryMember(SJsonValue v, PCCH member, PVOID pData, LONG nData, BOOL bUpperCase=FALSE)=0;
	virtual	SJsonValue		TCOMAPI	AddBase64Member(SJsonValue v, PCCH member, PVOID pData, LONG nData)=0;
	virtual	SJsonValue		TCOMAPI	AddArrayMember(SJsonValue v, PCCH member, ULONG reserve=0)=0;
	virtual	SJsonValue		TCOMAPI	AddObjectMember(SJsonValue v, PCCH member)=0;

	virtual	SJsonAIterator	TCOMAPI	ArrayBegin(SJsonValue v)=0;
	virtual	SJsonAIterator	TCOMAPI	ArrayEnd(SJsonValue v)=0;
	virtual	SJsonAIterator	TCOMAPI	NextArray(SJsonAIterator i)=0;
	virtual	SJsonValue		TCOMAPI	GetArrayValue(SJsonAIterator i)=0;
	virtual	SJsonValue		TCOMAPI	GetArrayValueByIdx(SJsonValue v, ULONG idx)=0;
	virtual	SJsonValue		TCOMAPI	PushbackIntValue(SJsonValue v, LONG value)=0;
	virtual	SJsonValue		TCOMAPI	PushbackUintValue(SJsonValue v, ULONG value)=0;
	virtual	SJsonValue		TCOMAPI	PushbackInt64Value(SJsonValue v, LONGLONG value)=0;
	virtual	SJsonValue		TCOMAPI	PushbackUint64Value(SJsonValue v, ULONGLONG value)=0;
	virtual	SJsonValue		TCOMAPI	PushbackDoubleValue(SJsonValue v, double value)=0;
	virtual	SJsonValue		TCOMAPI	PushbackBoolValue(SJsonValue v, bool value)=0;
	virtual	SJsonValue		TCOMAPI	PushbackNullValue(SJsonValue v)=0;
	virtual	SJsonValue		TCOMAPI	PushbackStringValue(SJsonValue v, PCCH value)=0;
	virtual	SJsonValue		TCOMAPI	PushbackDateTimeValue(SJsonValue v, ULONG value)=0;
	virtual	SJsonValue		TCOMAPI	PushbackDcTimeValue(SJsonValue v, LONGLONG value)=0;
	virtual	SJsonValue		TCOMAPI	PushbackFileTimeValue(SJsonValue v, LONGLONG value)=0;
	virtual	SJsonValue		TCOMAPI	PushbackHexBinaryValue(SJsonValue v, PVOID pData, LONG nData, BOOL bUpperCase=FALSE)=0;
	virtual	SJsonValue		TCOMAPI	PushbackBase64Value(SJsonValue v, PVOID pData, LONG nData)=0;
	virtual	bool				TCOMAPI	PopbackValue(SJsonValue v)=0;
	virtual	bool				TCOMAPI	RemoveArray(SJsonValue v, SJsonAIterator i)=0;
	virtual	bool				TCOMAPI	ClearArray(SJsonValue v)=0;

	virtual	SJsonValue		TCOMAPI	SetObject(SJsonValue v)=0;
	virtual	SJsonValue		TCOMAPI	SetArray(SJsonValue v, ULONG reserve=0)=0;
	virtual	SJsonValue		TCOMAPI	SetNull(SJsonValue v)=0;
	virtual	SJsonValue		TCOMAPI	SetInt(SJsonValue v, LONG value)=0;
	virtual	SJsonValue		TCOMAPI	SetUint(SJsonValue v, ULONG value)=0;
	virtual	SJsonValue		TCOMAPI	SetInt64(SJsonValue v, LONGLONG value)=0;
	virtual	SJsonValue		TCOMAPI	SetUint64(SJsonValue v, ULONGLONG value)=0;
	virtual	SJsonValue		TCOMAPI	SetDouble(SJsonValue v, double value)=0;
	virtual	SJsonValue		TCOMAPI	SetBool(SJsonValue v, bool value)=0;
	virtual	SJsonValue		TCOMAPI	SetString(SJsonValue v, PCCH value)=0;
	virtual	SJsonValue		TCOMAPI	SetDateTime(SJsonValue v, ULONG value)=0;
	virtual	SJsonValue		TCOMAPI	SetDcTime(SJsonValue v, LONGLONG value)=0;
	virtual	SJsonValue		TCOMAPI	SetFileTime(SJsonValue v, LONGLONG value)=0;
	virtual	SJsonValue		TCOMAPI	SetHexBinary(SJsonValue v, PVOID pData, LONG nData, BOOL bUpperCase=FALSE)=0;
	virtual	SJsonValue		TCOMAPI	SetBase64(SJsonValue v, PVOID pData, LONG nData)=0;

	virtual	bool				TCOMAPI	ExceptionRaised()=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcJsonDomParser, IID_ITcJsonDomParser);

struct	__declspec(novtable)	ITcJsonDomParser2 : public ITcJsonDomParser
{
	virtual	SJsonValue		TCOMAPI	AddJsonMember(SJsonValue v, PCCH member, PCCH rawJson)=0;
	virtual	SJsonValue		TCOMAPI	PushbackJsonValue(SJsonValue v, PCCH rawJson)=0;
	virtual	SJsonValue		TCOMAPI	SetJson(SJsonValue v, PCCH rawJson)=0;
	virtual	bool				TCOMAPI	Swap(SJsonValue v, SJsonValue w)=0;
	virtual	SJsonValue		TCOMAPI	CopyFrom(SJsonValue v, SJsonValue s)=0;
	virtual	void				TCOMAPI	SetMaxDecimalPlaces(LONG dp)=0;
	virtual	LONG				TCOMAPI	GetMaxDecimalPlaces()=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcJsonDomParser2, IID_ITcJsonDomParser2);

struct	__declspec(novtable)	ITcJsonDomParser3 : public ITcJsonDomParser2
{
	virtual	SJsonValue		TCOMAPI	PushbackCopyValue(SJsonValue v, SJsonValue s) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcJsonDomParser3, IID_ITcJsonDomParser3);

enum EJsonParseError {
	eNone = 0,      // null
	eDocumentEmpty = 1,     // document is empty
	eDocumentRootNotSingular = 2,      // document root must not follow by other values
	eValueInvalid = 3,    // invalid value
	eObjectMissName = 4,     // missing a name for object member 
	eObjectMissColon = 5,    // missing a colon after a name of object member
	eObjectMissCommaOrCurlyBracket = 6,     // missing a comma or '}' after an object member
	eArrayMissCommaOrSquareBracket = 7,      // missing a comma or ']' after an array element
	eStringUnicodeEscapeInvalidHex = 8,      // incorrect hex digit after \\u escape in string
	eStringUnicodeSurrogateInvalid = 9,      // surrogate pair in string is invalid
	eStringEscapeInvalid = 10,      // invalid escape character in string
	eStringMissQuotationMark = 11,      // missing a closing quotation mark in string
	eStringInvalidEncoding = 12,      // invalid encoding in string
	eNumberTooBig = 13,      // number too big to be stored in double
	eNumberMissFraction = 14,      // miss fraction part in number
	eNumberMissExponent = 15,      // miss exponent in number
	eTermination = 16,      // parsing was terminated
	eUnspecificSyntaxError = 17,      // unspecific syntax error
};
struct	__declspec(novtable)	ITcJsonDomParserError : public ITcUnknown
{
	virtual	EJsonParseError TCOMAPI	GetLastParseResult(PLONGLONG pOffset) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcJsonDomParserError, IID_ITcJsonDomParserError);

struct	__declspec(novtable)	TXmlNode {};
struct	__declspec(novtable)	TXmlAttribute {};
typedef TXmlNode*			SXmlNode;
typedef TXmlAttribute*	SXmlAttribute;
struct __declspec(novtable) SXmlIterator
{
	SXmlIterator() {node = NULL; itN = NULL; itA = NULL;};
	SXmlIterator(SXmlNode n) {node = n; itN = NULL; itA = NULL;}
	SXmlIterator(SXmlNode n, SXmlNode i) {node = n; itN=i; itA = NULL;}
	SXmlIterator(SXmlNode n, SXmlAttribute i) {node = n; itA=i; itN = NULL;}
	SXmlIterator(PVOID a, PVOID b, PVOID c) {node = (SXmlNode)a; itN = (SXmlNode)b; itA = (SXmlAttribute)c;}
	bool	IsNode() {return itN!=NULL;}
	bool	IsAttribute() {return itA!=NULL;}
	bool	IsEnd() {return itN==NULL && itA==NULL;}
	PVOID	A() {return node;}
	PVOID	B() {return itN;}
	PVOID	C() {return itA;}
protected:
	friend class CTcXmlDomParser;
	SXmlNode node;
	SXmlNode itN;
	SXmlAttribute itA;
};
struct	__declspec(novtable)	ITcXmlDomParserBase : public ITcUnknown
{
	// ITcXmlDomParser
	virtual	SXmlNode			TCOMAPI	ParseDocument(PCCH sXml)=0;
	virtual	SXmlNode			TCOMAPI	GetDocumentNode()=0;
	virtual	SXmlNode			TCOMAPI	GetRootNode()=0;
	virtual	ULONG				TCOMAPI	CopyDocument(PCHAR sXml, ULONG nXml)=0;
	virtual	ULONG				TCOMAPI	CopyNodeXml(SXmlNode xNode, PCHAR sXml, ULONG nXml)=0;

	virtual	SXmlNode			TCOMAPI	Child(SXmlNode xNode, PCCH sName=NULL)=0;
	virtual	SXmlNode			TCOMAPI	NextSibling(SXmlNode xNode, PCCH sName=NULL)=0;
	virtual	SXmlNode			TCOMAPI	ChildByAttribute(SXmlNode xNode, PCCH sAttr, PCCH sValue, PCCH sChild=NULL)=0;
	virtual	SXmlNode			TCOMAPI	FirstNodeByPath(SXmlNode xNode, PCCH sPath)=0;
	virtual	SXmlAttribute	TCOMAPI	Attribute(SXmlNode xNode, PCCH sName=NULL)=0;
	virtual	SXmlAttribute	TCOMAPI	NextAttribute(SXmlAttribute xAttr)=0;
	virtual	PCCH				TCOMAPI	NodeName(SXmlNode xNode)=0;
	virtual	PCCH				TCOMAPI	NodeText(SXmlNode xNode)=0;
	virtual	bool				TCOMAPI	NodeAsBool(SXmlNode xNode)=0;
	virtual	double			TCOMAPI	NodeAsDouble(SXmlNode xNode)=0;
	virtual	float				TCOMAPI	NodeAsFloat(SXmlNode xNode)=0;
	virtual	long				TCOMAPI	NodeAsInt(SXmlNode xNode)=0;
	virtual	ULONG 			TCOMAPI	NodeAsUint(SXmlNode xNode)=0;
	virtual	LONGLONG			TCOMAPI	NodeAsLint(SXmlNode xNode)=0;
	virtual	ULONGLONG		TCOMAPI	NodeAsUlint(SXmlNode xNode)=0;
	virtual	PCCH				TCOMAPI	AttributeName(SXmlAttribute xAttr)=0;
	virtual	PCCH				TCOMAPI	AttributeText(SXmlAttribute xAttr)=0;
	virtual	bool				TCOMAPI	AttributeAsBool(SXmlAttribute xAttr)=0;
	virtual	double			TCOMAPI	AttributeAsDouble(SXmlAttribute xAttr)=0;
	virtual	float				TCOMAPI	AttributeAsFloat(SXmlAttribute xAttr)=0;
	virtual	long				TCOMAPI	AttributeAsInt(SXmlAttribute xAttr)=0;
	virtual	ULONG 			TCOMAPI	AttributeAsUint(SXmlAttribute xAttr)=0;
	virtual	LONGLONG			TCOMAPI	AttributeAsLint(SXmlAttribute xAttr)=0;
	virtual	ULONGLONG		TCOMAPI	AttributeAsUlint(SXmlAttribute xAttr)=0;

	virtual	SXmlNode			TCOMAPI	AppendChild(SXmlNode xNode, PCCH sName, PCCH value=NULL, bool cdata=false)=0;
	virtual	SXmlNode			TCOMAPI	AppendChildAsBool(SXmlNode xNode, PCCH sName, bool value)=0;
	virtual	SXmlNode			TCOMAPI	AppendChildAsDouble(SXmlNode xNode, PCCH sName, double value)=0;
	virtual	SXmlNode			TCOMAPI	AppendChildAsFloat(SXmlNode xNode, PCCH sName, float value)=0;
	virtual	SXmlNode			TCOMAPI	AppendChildAsInt(SXmlNode xNode, PCCH sName, long value)=0;
	virtual	SXmlNode			TCOMAPI	AppendChildAsUint(SXmlNode xNode, PCCH sName, ULONG value)=0;
	virtual	SXmlNode			TCOMAPI	AppendChildAsLint(SXmlNode xNode, PCCH sName, LONGLONG value)=0;
	virtual	SXmlNode			TCOMAPI	AppendChildAsUlint(SXmlNode xNode, PCCH sName, ULONGLONG value)=0;
	virtual	SXmlNode			TCOMAPI	InsertChild(SXmlNode xNode, SXmlNode xBefore, PCCH sName)=0;
	virtual	SXmlNode			TCOMAPI	AppendCopy(SXmlNode xNode, SXmlNode xCopy)=0;
	virtual	SXmlNode			TCOMAPI	InsertCopy(SXmlNode xNode, SXmlNode xBefore, SXmlNode xCopy)=0;
	virtual	SXmlAttribute	TCOMAPI	AppendAttribute(SXmlNode xNode, PCCH sName, PCCH value)=0;
	virtual	SXmlAttribute	TCOMAPI	AppendAttributeAsBool(SXmlNode xNode, PCCH sName, bool value)=0;
	virtual	SXmlAttribute	TCOMAPI	AppendAttributeAsDouble(SXmlNode xNode, PCCH sName, double value)=0;
	virtual	SXmlAttribute	TCOMAPI	AppendAttributeAsFloat(SXmlNode xNode, PCCH sName, float value)=0;
	virtual	SXmlAttribute	TCOMAPI	AppendAttributeAsInt(SXmlNode xNode, PCCH sName, long value)=0;
	virtual	SXmlAttribute	TCOMAPI	AppendAttributeAsUint(SXmlNode xNode, PCCH sName, ULONG value)=0;
	virtual	SXmlAttribute	TCOMAPI	AppendAttributeAsLint(SXmlNode xNode, PCCH sName, LONGLONG value)=0;
	virtual	SXmlAttribute	TCOMAPI	AppendAttributeAsUlint(SXmlNode xNode, PCCH sName, ULONGLONG value)=0;
	virtual	SXmlAttribute	TCOMAPI	InsertAttribute(SXmlNode xNode, SXmlAttribute xBefore, PCCH sName)=0;
	virtual	SXmlAttribute	TCOMAPI	AppendAttributeCopy(SXmlNode xNode, SXmlAttribute xCopy)=0;
	virtual	SXmlAttribute	TCOMAPI	InsertAttributeCopy(SXmlNode xNode, SXmlAttribute xBefore, SXmlAttribute xCopy)=0;
	virtual	bool				TCOMAPI	RemoveChildByName(SXmlNode xNode, PCCH sName)=0;
	virtual	bool				TCOMAPI	RemoveChild(SXmlNode xNode, SXmlNode xChild)=0;
	virtual	bool				TCOMAPI	RemoveAttributeByName(SXmlNode xNode, PCCH sName)=0;
	virtual	bool				TCOMAPI	RemoveAttribute(SXmlNode xNode, SXmlAttribute xAttr)=0;
	virtual	bool				TCOMAPI	SetChildValue(SXmlNode xNode, PCCH value, bool cdata=false)=0;
	virtual	bool				TCOMAPI	SetChildValueAsBool(SXmlNode xNode, bool value)=0;
	virtual	bool				TCOMAPI	SetChildValueAsDouble(SXmlNode xNode, double value)=0;
	virtual	bool				TCOMAPI	SetChildValueAsFloat(SXmlNode xNode, float value)=0;
	virtual	bool				TCOMAPI	SetChildValueAsInt(SXmlNode xNode, long value)=0;
	virtual	bool				TCOMAPI	SetChildValueAsUint(SXmlNode xNode, ULONG value)=0;
	virtual	bool				TCOMAPI	SetChildValueAsLint(SXmlNode xNode, LONGLONG value)=0;
	virtual	bool				TCOMAPI	SetChildValueAsUlint(SXmlNode xNode, ULONGLONG value)=0;
	virtual	bool				TCOMAPI	SetAttributeValue(SXmlAttribute xAttr, PCCH value)=0;
	virtual	bool				TCOMAPI	SetAttributeValueAsBool(SXmlAttribute xAttr, bool value)=0;
	virtual	bool				TCOMAPI	SetAttributeValueAsDouble(SXmlAttribute xAttr, double value)=0;
	virtual	bool				TCOMAPI	SetAttributeValueAsFloat(SXmlAttribute xAttr, float value)=0;
	virtual	bool				TCOMAPI	SetAttributeValueAsInt(SXmlAttribute xAttr, long value)=0;
	virtual	bool				TCOMAPI	SetAttributeValueAsUint(SXmlAttribute xAttr, ULONG value)=0;
	virtual	bool				TCOMAPI	SetAttributeValueAsLint(SXmlAttribute xAttr, LONGLONG value)=0;
	virtual	bool				TCOMAPI	SetAttributeValueAsUlint(SXmlAttribute xAttr, ULONGLONG value)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcXmlDomParserBase, IID_ITcXmlDomParserBase);

struct	__declspec(novtable)	ITcXmlDomParser : public ITcXmlDomParserBase
{
	virtual	SXmlNode			TCOMAPI	Children(SXmlNode xNode, SXmlIterator& xIter, PCCH sName=NULL)=0;
	virtual	SXmlAttribute	TCOMAPI	Attributes(SXmlNode xNode, SXmlIterator& xIter)=0;
	virtual	SXmlIterator	TCOMAPI	Begin(SXmlNode xNode, PCCH sName=NULL)=0;
	virtual	SXmlIterator	TCOMAPI	AttributeBegin(SXmlNode xNode)=0;
	virtual	SXmlIterator	TCOMAPI	End(SXmlNode xNode)=0;
	virtual	SXmlIterator	TCOMAPI	Next(SXmlIterator xIter, PCCH sName=NULL)=0;
	virtual	SXmlNode			TCOMAPI	Node(SXmlIterator xIter)=0;
	virtual	SXmlAttribute	TCOMAPI	AttributeFromIterator(SXmlIterator xIter)=0;
	virtual	bool				TCOMAPI	IsEnd(SXmlIterator xIter)=0;
	virtual	bool				TCOMAPI	Compare(SXmlIterator xIter1, SXmlIterator xIter2)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcXmlDomParser, IID_ITcXmlDomParser);

struct	__declspec(novtable)	ITcXmlDomParserPlc : public ITcUnknown
{
	virtual	SXmlNode			TCOMAPI	Children(SXmlNode xNode, PVOID& xIterA, PVOID& xIterB, PVOID& xIterC, PCCH sName)=0;
	virtual	SXmlAttribute	TCOMAPI	Attributes(SXmlNode xNode, PVOID& xIterA, PVOID& xIterB, PVOID& xIterC)=0;
	virtual	void				TCOMAPI	Begin(SXmlNode xNode, PCCH sName, PVOID& xIterA, PVOID& xIterB, PVOID& xIterC)=0;
	virtual	void				TCOMAPI	AttributeBegin(SXmlNode xNode, PVOID& xIterA, PVOID& xIterB, PVOID& xIterC)=0;
	virtual	void				TCOMAPI	End(SXmlNode xNode, PVOID& xIterA, PVOID& xIterB, PVOID& xIterC)=0;
	virtual	void				TCOMAPI	Next(PVOID xIterAI, PVOID xIterBI, PVOID xIterCI, PCCH sName, PVOID& xIterAO, PVOID& xIterBO, PVOID& xIterCO)=0;
	virtual	SXmlNode			TCOMAPI	Node(PVOID xIterA, PVOID xIterB, PVOID xIterC)=0;
	virtual	SXmlAttribute	TCOMAPI	AttributeFromIterator(PVOID xIterA, PVOID xIterB, PVOID xIterC)=0;
	virtual	bool				TCOMAPI	IsEnd(PVOID xIterA, PVOID xIterB, PVOID xIterC)=0;
	virtual	bool				TCOMAPI	Compare(PVOID xIterA1, PVOID xIterB1, PVOID xIterC1, PVOID xIterA2, PVOID xIterB2, PVOID xIterC2)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcXmlDomParserPlc, IID_ITcXmlDomParserPlc);

struct	__declspec(novtable)	ITcDomParserFileAccess : public ITcUnknown
{
	virtual	HRESULT			TCOMAPI	LoadFromFile(PCCH sFile, bool bExec)=0;
	virtual	HRESULT			TCOMAPI	SaveToFile(PCCH sFile, bool bExec)=0;
	virtual	HRESULT			TCOMAPI	SetAdsProvider(OTCID oidAdsInvoker)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcDomParserFileAccess, IID_ITcDomParserFileAccess);

struct	__declspec(novtable)	ITcDomParserStreamAccess : public ITcUnknown	// NON_RT only
{
	virtual	HRESULT			TCOMAPI	LoadFromStream(ITComArchiveStream* ip)=0;
	virtual	HRESULT			TCOMAPI	SaveToStream(ITComArchiveStream* ip)=0;
	virtual	HRESULT			TCOMAPI	SetOwner(ITcUnknown* ipUnk)=0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcDomParserStreamAccess, IID_ITcDomParserStreamAccess);

