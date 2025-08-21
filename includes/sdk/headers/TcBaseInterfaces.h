#pragma once

#include "TcDef.h"
#include "TcBase.h"
#include "AdsErrorCodes.h"
#include "TcBaseServices.h"

#if defined(_AFXDLL)
#undef IMPLEMENT_IUNKNOWN 
#undef DECLARE_IUNKNOWN 
#undef DECLARE_IUNKNOWN_DERIVED 
#undef DECLARE_IUNKNOWN_NODELETE 
#undef DECLARE_IUNKNOWN_DERIVED_NODELETE 
#undef DECLARE_IUNKNOWN_AGGR_CHILD 
#undef BEGIN_INTERFACE_MAP 
#undef BEGIN_INTERFACE_MAP2
#undef BEGIN_INTERFACE_MAP_NODELETE 
#undef INTERFACE_ENTRY 
#undef INTERFACE_ENTRY1 
#undef INTERFACE_ENTRY2 
#undef INTERFACE_ENTRY_AGGR 
#undef INTERFACE_ENTRY_AGGR2
#undef INTERFACE_ENTRY_AGGR3
#undef END_INTERFACE_MAP
#undef END_INTERFACE_MAP2
#undef END_INTERFACE_MAP_AGGR
#endif


#define TCOMAPI __cdecl
#define TCOMMETHOD(method) virtual HRESULT TCOMAPI method = 0
#define TCOMMETHODITF(method) virtual HRESULT TCOMAPI method override

// Provide Interface to ITCID association
//
template<typename _Interface, const ITCID* _IID /*= &__uuidof(_Interface)*/>
class _tc_com_IIID
{
public:
	typedef _Interface Interface;

	static _Interface* GetInterfacePtr()
	{
		return NULL;
	}

	static _Interface& GetInterface()
	{
		return *GetInterfacePtr();
	}

	static const ITCID& GetIID()
	{
		return *_IID;
	}
};

template<typename _IIID> class DLL_EXPORT _tc_com_ptr_t {
public:
	// Declare interface type so that the type may be available outside
	// the scope of this template.
	//
	typedef _IIID ThisIIID;
	typedef typename _IIID::Interface Interface;

	// When the compiler supports references in template parameters,
	// _CLSID will be changed to a reference.  To avoid conversion
	// difficulties this function should be used to obtain the
	// CLSID.
	//
	static const ITCID& GetIID()
	{
		return ThisIIID::GetIID();
	}

	// Constructs a smart-pointer from any other smart pointer.
	//
	template<typename _OtherIID> _tc_com_ptr_t(const _tc_com_ptr_t<_OtherIID>& p)
		: m_pInterface(NULL), m_oid(0)
	{
		_QueryInterface(p);
	}

	// Constructs a smart-pointer from any IUnknown-based interface pointer.
	//
	template<typename _InterfaceType> _tc_com_ptr_t(_InterfaceType* p)
		: m_pInterface(NULL), m_oid(0)
	{
		_QueryInterface(p);
	}

	// Disable conversion using _tc_com_ptr_t* specialization of
	// template<typename _InterfaceType> _tc_com_ptr_t(_InterfaceType* p)
	//
	explicit _tc_com_ptr_t(_tc_com_ptr_t* p)
		: m_pInterface(NULL), m_oid(0)
	{
		if (p != NULL)
		{
			m_pInterface = p->m_pInterface;
			AddRef();
		}
	}

	// Default constructor.
	//
	_tc_com_ptr_t()
		: m_pInterface(NULL), m_oid(0)
	{
	}

	// This constructor is provided to allow NULL assignment. It will issue
	// an error if any value other than null is assigned to the object.
	//
	_tc_com_ptr_t(int oid)
		: m_pInterface(NULL), m_oid(oid)
	{
	}

	// Copy the pointer and AddRef().
	//
	_tc_com_ptr_t(const _tc_com_ptr_t& cp)
		: m_pInterface(cp.m_pInterface), m_oid(cp.m_oid)
	{
		_AddRef();
	}

	// Saves the interface.
	//
	_tc_com_ptr_t(Interface* pInterface)
		: m_pInterface(pInterface), m_oid(0)
	{
		_AddRef();
	}

	// Copies the pointer. If fAddRef is TRUE, the interface will
	// be AddRef()ed.
	//
	_tc_com_ptr_t(Interface* pInterface, bool fAddRef)
		: m_pInterface(pInterface), m_oid(0)
	{
		if (fAddRef)
		{
			_AddRef();
		}
	}

	// Queries for interface.
	//
	template<typename _OtherIID> _tc_com_ptr_t& operator=(const _tc_com_ptr_t<_OtherIID>& p)
	{
		_QueryInterface(p);

		return *this;
	}

	// Queries for interface.
	//
	template<typename _InterfaceType> _tc_com_ptr_t& operator=(_InterfaceType* p)
	{
		_QueryInterface(p);

		return *this;
	}

	// Saves the interface.
	//
	_tc_com_ptr_t& operator=(Interface* pInterface)
	{
		if (m_pInterface != pInterface)
		{
			Interface* pOldInterface = m_pInterface;

			m_pInterface = pInterface;

			_AddRef();

			if (pOldInterface != NULL)
			{
				pOldInterface->TcRelease();
			}
		}
		return *this;
	}

	// Copies and AddRef()'s the interface.
	//
	_tc_com_ptr_t& operator=(const _tc_com_ptr_t& cp)
	{
		_tc_com_ptr_t& sp = operator=(cp.m_pInterface);
		sp.m_oid = cp.m_oid;
		return sp;
	}

	// This operator is provided to permit the assignment of NULL to the class.
	//
	_tc_com_ptr_t& operator=(int)
	{
		return operator=(static_cast<Interface*>(NULL));
	}

	_tc_com_ptr_t& operator=(long)
	{
		return operator=(static_cast<Interface*>(NULL));
	}

	// If we still have an interface then Release() it. The interface
	// may be NULL if Detach() has previously been called, or if it was
	// never set.
	//
	~_tc_com_ptr_t()
	{
		_Release();
	}

	// Saves/sets the interface without AddRef()ing. This call
	// will release any previously acquired interface.
	//
	void Attach(Interface* pInterface)
	{
		_Release();
		m_pInterface = pInterface;
	}

	// Saves/sets the interface only AddRef()ing if fAddRef is TRUE.
	// This call will release any previously acquired interface.
	//
	void Attach(Interface* pInterface, bool fAddRef)
	{
		_Release();
		m_pInterface = pInterface;

		if (fAddRef)
		{
			if (pInterface != NULL)
			{
				pInterface->TcAddRef();
			}
		}
	}

	// Simply NULL the interface pointer so that it isn't Released()'ed.
	//
	Interface* Detach()
	{
		Interface* const old = m_pInterface;
		m_pInterface = NULL;
		return old;
	}

	// Allow access to this pointer, as operator& cannot be used
	// Intended for use by STL allocator
	const _tc_com_ptr_t* GetThis() const
	{
		return this;
	}

	// Allow access to this pointer, as operator& cannot be used
	// Intended for use by STL allocator
	_tc_com_ptr_t* GetThis()
	{
		return this;
	}

	// Return the interface. This value may be NULL.
	//
	operator Interface* () const
	{
		return m_pInterface;
	}

	// Queries for the unknown and return it
	// Provides minimal level error checking before use.
	//
	operator Interface& () const
	{
		return *m_pInterface;
	}

	// Allows an instance of this class to act as though it were the
	// actual interface. Also provides minimal error checking.
	//
	Interface& operator*() const
	{
		return *m_pInterface;
	}

	// Returns the address of the interface pointer contained in this
	// class. This is useful when using the COM/OLE interfaces to create
	// this interface.
	//
	Interface** operator&()
	{
		_Release();
		m_pInterface = NULL;
		return &m_pInterface;
	}

	// Declare const operator& private to prevent its accidental usage.
	// Without this declaration the standard operator& would be used,
	// which returns the this pointer. 
	//
private:
	const Interface** operator&() const;

public:
	// Allows this class to be used as the interface itself.
	// Also provides simple error checking.
	//
	Interface* operator->() const
	{
		return m_pInterface;
	}

	// This operator is provided so that simple boolean expressions will
	// work.  For example: "if (p) ...".
	// Returns TRUE if the pointer is not NULL.
	//
	operator bool() const
	{
		return m_pInterface != NULL;
	}

	// This operator is provided so that simple boolean expressions will
	// work.  For example: "if (p) ...".
	// The constness of the smart pointer determines which conversion operator
	// is called. It could be a non const conversion to pointer type of a 
	// derived smart pointer class, if this overload was not here.
	// Returns TRUE if the pointer is not NULL.
	//
	operator bool()
	{
		//return static_cast<const _tc_com_ptr_t>(*this).operator bool();
		return m_pInterface != NULL;
	}

	// Compare two smart pointers
	//
	template<typename _OtherIID> bool operator==(const _tc_com_ptr_t<_OtherIID>& p) const
	{
		return _CompareUnknown(p) == 0;
	}

	// Compare two smart pointers
	//
	template<typename _OtherIID> bool operator==(_tc_com_ptr_t<_OtherIID>& p) const
	{
		return _CompareUnknown(p) == 0;
	}

	// Compare two pointers
	//
	template<typename _InterfaceType> bool operator==(_InterfaceType* p) const
	{
		return _CompareUnknown(p) == 0;
	}

	// Compare with other interface
	//
	bool operator==(Interface* p) const
	{
		return (m_pInterface == p) ? true : _CompareUnknown(p) == 0;
	}

	// Compare two smart pointers
	//
	bool operator==(const _tc_com_ptr_t& p) const
	{
		return operator==(p.m_pInterface);
	}

	// Compare two smart pointers
	//
	bool operator==(_tc_com_ptr_t& p) const
	{
		return operator==(p.m_pInterface);
	}

	// For comparison to NULL
	//
	bool operator==(int) const
	{
		return m_pInterface == NULL;
	}

	bool operator==(long) const
	{
		return m_pInterface == NULL;
	}

	// Compare two smart pointers
	//
	template<typename _OtherIID> bool operator!=(const _tc_com_ptr_t<_OtherIID>& p) const
	{
		return !(operator==(p));
	}

	// Compare two smart pointers
	//
	template<typename _OtherIID> bool operator!=(_tc_com_ptr_t<_OtherIID>& p) const
	{
		return !(operator==(p));
	}

	// Compare two pointers
	//
	template<typename _InterfaceType> bool operator!=(_InterfaceType* p) const
	{
		return !(operator==(p));
	}

	// For comparison to NULL
	//
	bool operator!=(int null) const
	{
		return !(operator==(null));
	}

	bool operator!=(long null) const
	{
		return !(operator==(null));
	}

	// Compare two smart pointers
	//
	template<typename _OtherIID> bool operator<(const _tc_com_ptr_t<_OtherIID>& p) const
	{
		return _CompareUnknown(p) < 0;
	}

	// Compare two smart pointers
	//
	template<typename _OtherIID> bool operator<(_tc_com_ptr_t<_OtherIID>& p) const
	{
		return _CompareUnknown(p) < 0;
	}

	// Compare two pointers
	//
	template<typename _InterfaceType> bool operator<(_InterfaceType* p) const
	{
		return _CompareUnknown(p) < 0;
	}

	// Compare two smart pointers
	//
	template<typename _OtherIID> bool operator>(const _tc_com_ptr_t<_OtherIID>& p) const
	{
		return _CompareUnknown(p) > 0;
	}

	// Compare two smart pointers
	//
	template<typename _OtherIID> bool operator>(_tc_com_ptr_t<_OtherIID>& p) const
	{
		return _CompareUnknown(p) > 0;
	}

	// Compare two pointers
	//
	template<typename _InterfaceType> bool operator>(_InterfaceType* p) const
	{
		return _CompareUnknown(p) > 0;
	}

	// Compare two smart pointers
	//
	template<typename _OtherIID> bool operator<=(const _tc_com_ptr_t<_OtherIID>& p) const
	{
		return _CompareUnknown(p) <= 0;
	}

	// Compare two smart pointers
	//
	template<typename _OtherIID> bool operator<=(_tc_com_ptr_t<_OtherIID>& p) const
	{
		return _CompareUnknown(p) <= 0;
	}

	// Compare two pointers
	//
	template<typename _InterfaceType> bool operator<=(_InterfaceType* p) const
	{
		return _CompareUnknown(p) <= 0;
	}

	// Compare two smart pointers
	//
	template<typename _OtherIID> bool operator>=(const _tc_com_ptr_t<_OtherIID>& p) const
	{
		return _CompareUnknown(p) >= 0;
	}

	// Compare two smart pointers
	//
	template<typename _OtherIID> bool operator>=(_tc_com_ptr_t<_OtherIID>& p) const
	{
		return _CompareUnknown(p) >= 0;
	}

	// Compare two pointers
	//
	template<typename _InterfaceType> bool operator>=(_InterfaceType* p) const
	{
		return _CompareUnknown(p) >= 0;
	}

	// Provides error-checking Release()ing of this interface.
	//
	void Release()
	{
		if (m_pInterface != NULL)
		{
			m_pInterface->TcRelease();
			m_pInterface = NULL;
		}
	}

	// Provides error-checking AddRef()ing of this interface.
	//
	void AddRef()
	{
		if (m_pInterface != NULL)
		{
			m_pInterface->TcAddRef();
		}
	}

	// Another way to get the interface pointer without casting.
	//
	Interface* GetInterfacePtr() const
	{
		return m_pInterface;
	}

	// Another way to get the interface pointer without casting.
	// Use for [in, out] parameter passing
	Interface*& GetInterfacePtr()
	{
		return m_pInterface;
	}

	// Performs the QI for the specified ITCID and returns it in p.
	// As with all QIs, the interface will be AddRef'd.
	//
	template<typename _InterfaceType> HRESULT TcQueryInterface(const ITCID& iid, _InterfaceType*& p) throw ()
	{
		if (m_pInterface != NULL)
		{
			return m_pInterface->TcQueryInterface(iid, reinterpret_cast<void**>(&p));
		}

		return E_POINTER;
	}

	// Performs the QI for the specified ITCID and returns it in p.
	// As with all QIs, the interface will be AddRef'd.
	//
	template<typename _InterfaceType> HRESULT TcQueryInterface(const ITCID& iid, _InterfaceType** p)
	{
		return TcQueryInterface(iid, *p);
	}

	void	SetOID(OTCID oid)
	{
		m_oid = oid;
	}

	OTCID GetOID() const
	{
		return m_oid;
	}

	bool HasOID() const
	{
		return m_oid != 0;
	}

protected:
	// The Interface.
	//
	Interface* m_pInterface;
	OTCID			m_oid;

	// Releases only if the interface is not null.
	// The interface is not set to NULL.
	//
	void _Release()
	{
		if (m_pInterface != NULL)
		{
			m_pInterface->TcRelease();
		}
	}

	// AddRefs only if the interface is not NULL
	//
	void _AddRef()
	{
		if (m_pInterface != NULL)
		{
			m_pInterface->TcAddRef();
		}
	}

	// Compares the provided pointer with this by obtaining IUnknown interfaces
	// for each pointer and then returning the difference.
	//
	template<typename _InterfacePtr>
	LONG_PTR _CompareUnknown(_InterfacePtr p) const;

	// Performs a QI on pUnknown for the interface type returned
	// for this class.  The interface is stored.  If pUnknown is
	// NULL, or the QI fails, E_NOINTERFACE is returned and
	// _pInterface is set to NULL.
	//
	template<typename _InterfacePtr> HRESULT _QueryInterface(_InterfacePtr p)
	{
		HRESULT hr;

		// Can't QI NULL
		//
		if (p != NULL)
		{
			// Query for this interface
			//
			Interface* pInterface;
			hr = p->TcQueryInterface(GetIID(), reinterpret_cast<void**>(&pInterface));

			// Save the interface without AddRef()ing.
			//
			Attach(SUCCEEDED(hr) ? pInterface : NULL);
		}
		else
		{
			operator=(static_cast<Interface*>(NULL));
			hr = E_NOINTERFACE;
		}

		return hr;
	}
};

// Reverse comparison operators for _tc_com_ptr_t
//
template<typename _InterfaceType> bool operator==(int null, _tc_com_ptr_t<_InterfaceType>& p)
{
	return p == NULL;
}

template<typename _Interface, typename _InterfacePtr> bool operator==(_Interface* i, _tc_com_ptr_t<_InterfacePtr>& p)
{
	return p == i;
}

template<typename _Interface> bool operator!=(int null, _tc_com_ptr_t<_Interface>& p)
{
	return p != NULL;
}

template<typename _Interface, typename _InterfacePtr> bool operator!=(_Interface* i, _tc_com_ptr_t<_InterfacePtr>& p)
{
	return p != i;
}

template<typename _Interface> bool operator<(int null, _tc_com_ptr_t<_Interface>& p)
{
	return p > NULL;
}

template<typename _Interface, typename _InterfacePtr> bool operator<(_Interface* i, _tc_com_ptr_t<_InterfacePtr>& p)
{
	return p > i;
}

template<typename _Interface> bool operator>(int null, _tc_com_ptr_t<_Interface>& p)
{
	return p < NULL;
}

template<typename _Interface, typename _InterfacePtr> bool operator>(_Interface* i, _tc_com_ptr_t<_InterfacePtr>& p)
{
	return p < i;
}

template<typename _Interface> bool operator<=(int null, _tc_com_ptr_t<_Interface>& p)
{
	return p >= NULL;
}

template<typename _Interface, typename _InterfacePtr> bool operator<=(_Interface* i, _tc_com_ptr_t<_InterfacePtr>& p)
{
	return p >= i;
}

template<typename _Interface> bool operator>=(int null, _tc_com_ptr_t<_Interface>& p)
{
	return p <= NULL;
}

template<typename _Interface, typename _InterfacePtr> bool operator>=(_Interface* i, _tc_com_ptr_t<_InterfacePtr>& p)
{
	return p <= i;
}

#define _TCOM_SMARTPTR        _tc_com_ptr_t
#define _TCOM_SMARTPTR_TYPEDEF(Interface, IID) \
	typedef _TCOM_SMARTPTR<_tc_com_IIID<Interface, &__uuidof(Interface)> > \
			Interface ## Ptr
#define _TCOM_TYPEDEF_SMARTPTR(Interface) \
	typedef _TCOM_SMARTPTR<_tc_com_IIID<Interface, &__uuidof(Interface)> > \
			Interface ## Ptr

template<typename _IIID, class INFO> class DLL_EXPORT _tc_com_ptr_t_listinfo : public _tc_com_ptr_t<_IIID>
{
public:

	using _tc_com_ptr_t<_IIID>::m_pInterface;
	using _tc_com_ptr_t<_IIID>::AddRef;
	using _tc_com_ptr_t<_IIID>::_AddRef;
	using _tc_com_ptr_t<_IIID>::_QueryInterface;

	typedef typename _tc_com_ptr_t<_IIID>::Interface Interface;

	// Constructs a smart-pointer from any other smart pointer.
	//
	template<typename _OtherIID> _tc_com_ptr_t_listinfo(const _tc_com_ptr_t<_OtherIID>& p) : _tc_com_ptr_t<_IIID>(p)
	{
		_QueryInterface(p);
	}

	// Constructs a smart-pointer from any IUnknown-based interface pointer.
	//
	template<typename _InterfaceType> _tc_com_ptr_t_listinfo(_InterfaceType* p) : _tc_com_ptr_t<_IIID>(p)
	{
		_QueryInterface(p);
	}

	// Disable conversion using _tc_com_ptr_t* specialization of
	// template<typename _InterfaceType> _tc_com_ptr_t(_InterfaceType* p)
	//
	explicit _tc_com_ptr_t_listinfo(_tc_com_ptr_t<_IIID>* p)
	{
		if (p != NULL)
		{
			m_pInterface = p->m_pInterface;
			AddRef();
		}
	}
	// Default constructor.
	//
	_tc_com_ptr_t_listinfo()
	{
	}


	// Saves the interface.
	//
	// Queries for interface.
	//
	template<typename _OtherIID> _tc_com_ptr_t_listinfo& operator=(const _tc_com_ptr_t<_OtherIID>& p)
	{
		_QueryInterface(p);

		return *this;
	}

	// Queries for interface.
	//
	template<typename _InterfaceType> _tc_com_ptr_t_listinfo& operator=(_InterfaceType* p)
	{
		_QueryInterface(p);

		return *this;
	}

	// Saves the interface.
	//
	_tc_com_ptr_t_listinfo& operator=(Interface* pInterface)
	{
		if (m_pInterface != pInterface)
		{
			Interface* pOldInterface = m_pInterface;

			m_pInterface = pInterface;

			_AddRef();

			if (pOldInterface != NULL)
			{
				pOldInterface->TcRelease();
			}
		}
		return *this;
	}

	_tc_com_ptr_t_listinfo& operator=(const _tc_com_ptr_t<_IIID>& cp)
	{
		_tc_com_ptr_t_listinfo& sp = operator=(cp.m_pInterface);
		sp.m_oid = cp.m_oid;
		return sp;
	}

	_tc_com_ptr_t_listinfo& operator=(int null)
	{
		return operator=(reinterpret_cast<Interface*>(NULL));
	}

	_tc_com_ptr_t_listinfo& operator=(long null)
	{
		return operator=(reinterpret_cast<Interface*>(NULL));
	}

	INFO* GetInfo()
	{
		return &m_info;
	}

	operator INFO* ()
	{
		return &m_info;
	}

protected:
	INFO m_info;
};

#define _TCOM_SMARTPTR_INFO        _tc_com_ptr_t_listinfo
#define _TCOM_SMARTPTR_TYPEDEF_INFO(Interface, IID, INFO) \
	typedef _TCOM_SMARTPTR_INFO<_tc_com_IIID<Interface, &__uuidof(Interface)>, INFO> \
			Interface ## InfoPtr
#define _TCOM_TYPEDEF_SMARTPTR_INFO(Interface, INFO) \
	typedef _TCOM_SMARTPTR_INFO<_tc_com_IIID<Interface, &__uuidof(Interface)>, INFO> \
			Interface ## InfoPtr


///////////////////////////////////////////////////////////////////////////////
// ITcUnknown
struct __declspec(novtable) ITcUnknown
{
	virtual ULONG TCOMAPI	TcAddRef(void) = 0;
	TCOMMETHOD(TcQueryInterface(RITCID iid, PPVOID pipItf));
	virtual ULONG TCOMAPI	TcRelease(void) = 0;
};
_TCOM_SMARTPTR_TYPEDEF(ITcUnknown, IID_ITcUnknown);

template<typename _IIID>
template<typename _InterfacePtr>
LONG_PTR _tc_com_ptr_t<_IIID>::_CompareUnknown(_InterfacePtr p) const
{
	ITcUnknown* pu1, * pu2;

	if (m_pInterface != NULL)
	{
		if (SUCCEEDED(m_pInterface->TcQueryInterface(IID_ITcUnknown, reinterpret_cast<void**>(&pu1))))
			pu1->TcRelease();
	}
	else
		pu1 = NULL;

	if (p != NULL)
	{
		if (SUCCEEDED(p->TcQueryInterface(IID_ITcUnknown, reinterpret_cast<void**>(&pu2))))
			pu2->TcRelease();
	}
	else
		pu2 = NULL;

	return pu1 - pu2;
}

#define DEFINE_THIS_FILE() \
	static LPCSTR THIS_FILE = __FILE__;

#define IMPLEMENT_IUNKNOWN() 

#define DECLARE_IUNKNOWN() \
virtual	HRESULT _cdecl TcQueryInterface( RITCID iid, PPVOID pipItf );\
AUTO_ULONG	m_refCnt;\
virtual	ULONG _cdecl TcAddRef(void) \
{ \
	{	return InterlockedIncrementR0(&m_refCnt); }\
}\
virtual	ULONG	_cdecl TcRelease(void) \
{\
	{	\
		ULONG refCnt = InterlockedDecrementR0(&m_refCnt); \
		if ( refCnt == 0 ) \
			delete this; \
		return refCnt; \
	}\
}
#define DECLARE_IUNKNOWN_DERIVED() \
virtual	HRESULT _cdecl TcQueryInterface( RITCID iid, PPVOID pipItf );\
virtual	ULONG _cdecl TcAddRef(void) \
{ \
	{	return InterlockedIncrementR0(&m_refCnt); }\
}\
virtual	ULONG	_cdecl TcRelease(void) \
{\
	{	\
		ULONG refCnt = InterlockedDecrementR0(&m_refCnt); \
		if ( refCnt == 0 ) \
			delete this; \
		return refCnt; \
	}\
}

#define DECLARE_IUNKNOWN_NODELETE() \
virtual	HRESULT _cdecl TcQueryInterface( RITCID iid, PPVOID pipItf );\
AUTO_ULONG	m_refCnt;\
virtual	ULONG _cdecl TcAddRef(void) \
{ \
	{	return InterlockedIncrementR0(&m_refCnt); }\
}\
virtual	ULONG _cdecl TcRelease(void) \
{\
	{	\
		return InterlockedDecrementR0(&m_refCnt); \
	}\
}

#define DECLARE_IUNKNOWN_DERIVED_NODELETE() \
virtual	HRESULT	_cdecl TcQueryInterface( RITCID iid, PPVOID pipItf );\
virtual	ULONG	_cdecl TcAddRef(void) \
{ \
	{	return InterlockedIncrementR0(&m_refCnt); }\
}\
virtual	ULONG	_cdecl TcRelease(void) \
{\
	{	\
		return InterlockedDecrementR0(&m_refCnt); \
	}\
}

#define DECLARE_IUNKNOWN_AGGR_CHILD(parent) \
virtual	HRESULT _cdecl TcQueryInterface( RITCID iid, PPVOID pipItf );\
virtual	ULONG _cdecl TcAddRef(void) \
{ \
	{	return parent->TcAddRef(); }\
}\
virtual	ULONG	_cdecl TcRelease(void) \
{\
	{	\
		return parent->TcRelease(); \
	}\
}

#define BEGIN_INTERFACE_MAP(theClass) \
HRESULT	theClass::TcQueryInterface( RITCID iid, PPVOID pipItf )\
{	*pipItf = NULL;

#define BEGIN_INTERFACE_MAP2(theClass) \
HRESULT	theClass::TcQueryInterface( RITCID iid, PPVOID pipItf )\
{	*pipItf = NULL;

#define BEGIN_INTERFACE_MAP_NODELETE(theClass) \
HRESULT	theClass::TcQueryInterface( RITCID iid, PPVOID pipItf )\
{	*pipItf = NULL;

#define INTERFACE_ENTRY(IntefaceId, InterfacePtr) \
if ( iid == IntefaceId )\
*pipItf = static_cast<InterfacePtr*>(this);\
else 

#define INTERFACE_ENTRY1(InterfacePtr) \
if ( iid == __uuidof(InterfacePtr) )\
*pipItf = static_cast<InterfacePtr*>(this);\
else 

#define INTERFACE_ENTRY2(IntefaceId, InterfacePtr) \
if ( iid == IID_ITcUnknown )\
*pipItf = static_cast<InterfacePtr*>(this);\
else if ( iid == IntefaceId )\
*pipItf = static_cast<InterfacePtr*>(this);\
else 

#define INTERFACE_ENTRY_AGGR(IntefaceId, ipAggregate) \
if ( iid == IntefaceId && ipAggregate != NULL )\
return ipAggregate->TcQueryInterface(iid, pipItf);\
else 

#define INTERFACE_ENTRY_AGGR2(InterfaceId, pAggregate, ipAggregate) \
if ( iid == InterfaceId ) \
{ \
	if ( pAggregate == NULL || pAggregate->ipAggregate == NULL ) \
		return ADS_E_NOINTERFACE; \
	return pAggregate->ipAggregate->TcQueryInterface(InterfaceId, pipItf); \
} \
else

#define INTERFACE_ENTRY_AGGR3(IntefaceId, InterfacePtr, pAggregate) \
if ( iid == IntefaceId )\
*pipItf = static_cast<InterfacePtr*>(pAggregate);\
else 

#define END_INTERFACE_MAP() \
return ADS_E_NOINTERFACE;\
reinterpret_cast<ITcUnknown*>(*pipItf)->TcAddRef();\
return S_OK;\
}

#define END_INTERFACE_MAP2(theBase) \
return theBase::TcQueryInterface( iid, pipItf );\
reinterpret_cast<ITcUnknown*>(*pipItf)->TcAddRef();\
return S_OK;\
}

#define END_INTERFACE_MAP_AGGR(ipAggregate) \
if ( ipAggregate )\
return ipAggregate->TcQueryInterface( iid, pipItf );\
else \
return ADS_E_NOINTERFACE;\
reinterpret_cast<ITcUnknown*>(*pipItf)->TcAddRef();\
return S_OK;\
}

// AUTO_ULONG is just a unsigned long that constructs to zero
struct DLL_EXPORT AUTO_ULONG {
	ULONG value;
	AUTO_ULONG(void) : value(0) {}
	inline ULONG* operator & (void) { return &value; }
	inline ULONG operator ++(void) { return ++value; }
	inline ULONG operator --(void) { return --value; }
	inline bool operator != (const ULONG& rhs) const { return      value != rhs; }
	inline bool operator == (const ULONG& rhs) const { return      value == rhs; }
	inline bool operator != (const int& rhs)   const { return (int)value != rhs; }
	inline bool operator == (const int& rhs)   const { return (int)value == rhs; }
	inline operator ULONG (void) { return value; }
};

#ifndef safe_release
#define safe_release(p)		{if (p) (p)->TcRelease(); p = NULL;}
#endif // !safe_release
