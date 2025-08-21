///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <TcDef.h>

/////////////////////////////////////////////////////////////////////////////////////

#if defined(TC_ENVIRONMENT_RT) || defined(TC_ENVIRONMENT_CE_RT) || defined(TC_ENVIRONMENT_OS) || ( defined(TC_ENVIRONMENT_CE) && !defined(_ARM_) && UNDER_CE >= 0x700 )

#define TC_SPINLOCK_DEFINED
class
#if defined(TC_ENVIRONMENT_CE_RT) || ( defined(TC_ENVIRONMENT_CE) && !defined(_ARM_) )
DLL_EXPORT 
#endif
CSpinlock
{
private:
	ULONG m_cData[8];

public:
	CSpinlock();
	~CSpinlock();

	void Lock();
	void Unlock();

	inline void lock() { Lock(); }
	inline void unlock() { Unlock(); }
};

#elif defined(TC_ENVIRONMENT_CE) && !defined(_ARM_)
//CE6(x86)

#define TC_SPINLOCK_DEFINED
class DLL_EXPORT CSpinlock
{
private:
	volatile DWORD_PTR m_irqFlags;

public: 
	CSpinlock();
	~CSpinlock ();

	void Lock();
	void Unlock();

	inline void lock() { Lock(); }
	inline void unlock() { Unlock(); }
}; 

#endif

/////////////////////////////////////////////////////////////////////////////////////

#if defined(TC_ENVIRONMENT_UM) || (defined(_ARM_) && !defined(TCRTOS) && !defined(TC_ENVIRONMENT_OS))
#define TC_SPINLOCK_DEFINED
class DLL_EXPORT CSpinlock
{
private:
	CRITICAL_SECTION m_CritSect;

public:
	CSpinlock();
	~CSpinlock ();

	void Lock();
	void Unlock();

	inline void lock() { Lock(); }
	inline void unlock() { Unlock(); }
};
#endif


/////////////////////////////////////////////////////////////////////////////////////


#ifdef TC_SPINLOCK_DEFINED
#undef TC_SPINLOCK_DEFINED

/// <summary>
/// Scope guard class for spinlocks. Automatically unlocks the spinlock acquired
/// at construction when it goes out of scope, even in case of early returns.
/// </summary>
class CSpinlockScopeGuard
{
private:
	CSpinlock* m_lock;
	// Forbid copy constructor/assignment
	CSpinlockScopeGuard(const CSpinlockScopeGuard&);
	CSpinlockScopeGuard& operator=(const CSpinlockScopeGuard&);
public:
	CSpinlockScopeGuard(CSpinlock& lock) : m_lock(&lock)
	{
		m_lock->Lock();
	}
	~CSpinlockScopeGuard()
	{
		Unlock();
	}
	void Unlock()
	{
		if (m_lock)
		{
			m_lock->Unlock();
			m_lock = NULL;
		}
	}
};
#endif // TC_SPINLOCK_DEFINED



