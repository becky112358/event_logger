///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcBase.h"
#include "SyncObjects.h"

///////////////////////////////////////////////////////////////////////////////
template <class ValueType, LONG SIZE>
class CFiFoListStorageStatic
{
public: 
	typedef ValueType VALUE; 

	CFiFoListStorageStatic()
		: m_nSize(SIZE)
	{
	}
	void Clear()
	{
		memset( m_pFiFoEntrys, 0, m_nSize * sizeof(VALUE) );
	}
	VALUE	m_pFiFoEntrys[SIZE];
	LONG	m_nSize;
	LONG	m_nReserved1;		// to be compatible to 64bit memory layout
}; 

template <class ValueType>
class CFiFoListStorageDynamic
{
public: 
	typedef ValueType VALUE; 

	CFiFoListStorageDynamic() 
		: m_pFiFoEntrys(NULL)
		, m_nSize(0)
	{
	}
	
	void Clear()
	{
		if (m_pFiFoEntrys)
		{
			memset( m_pFiFoEntrys, 0, m_nSize * sizeof(VALUE) );
		}
	}

	void Allocate(LONG nSize)
	{
		ASSERT(m_pFiFoEntrys == NULL); 
		m_pFiFoEntrys = new VALUE[nSize]; 
		ASSERT(m_pFiFoEntrys != NULL); 
		m_nSize = nSize; 
	}

	void Deallocate()
	{
		ASSERT(m_pFiFoEntrys); 
		delete[] m_pFiFoEntrys; 
		m_pFiFoEntrys = NULL; 
		m_nSize = 0; 
	}

	VALUE* m_pFiFoEntrys;
	LONG	m_nSize;
}; 

///////////////////////////////////////////////////////////////////////////////
// CFiFoListBase

template <class StorageType, class SyncType>
class CFiFoListBase
{
public:
	CFiFoListBase()
		: m_SyncObj()
		, m_StorageObj()
		, m_nFirst(0)
		, m_nLast(0)
		, m_nCount(0)
	{
	}

	void Lock()
	{
		m_SyncObj.Lock(); 
	}

	void Unlock()
	{
		m_SyncObj.Unlock(); 
	}

	void Clear()
	{
		m_SyncObj.Lock(); 

		Clear_Unprotected(); 

		m_SyncObj.Unlock(); 
	}

	void Clear_Unprotected()
	{
		m_StorageObj.Clear();
		m_nFirst	= 0;
		m_nLast	= 0;
		m_nCount	= 0;
	}

	bool Add( typename StorageType::VALUE newValue )
	{
		m_SyncObj.Lock(); 

		if ( m_nCount >= m_StorageObj.m_nSize )
		{
			m_SyncObj.Unlock(); 
			return false;
		}

		m_StorageObj.m_pFiFoEntrys[m_nLast] = newValue;

		m_nLast++;
		if ( m_nLast == m_StorageObj.m_nSize )
			m_nLast = 0;

		m_nCount++;

		m_SyncObj.Unlock(); 

		return true;
	}

	bool	Add_Unprotected( typename StorageType::VALUE newValue )
	{
		if ( m_nCount >= m_StorageObj.m_nSize )
			return false;

		m_StorageObj.m_pFiFoEntrys[m_nLast] = newValue;

		m_nLast++;
		if ( m_nLast == m_StorageObj.m_nSize )
			m_nLast = 0;

		m_nCount++;

		return true;
	}

	ULONG AddBlock( const typename StorageType::VALUE* pValueBlock, ULONG nValues)
	{
		m_SyncObj.Lock(); 
		ULONG nFreeCount = static_cast<ULONG>(FreeCount()); 
		ASSERT( nFreeCount >= nValues );
		if (nValues>nFreeCount)
		{
			nValues = nFreeCount; 
		}
		
		if (m_nLast+nValues>static_cast<ULONG>(m_StorageObj.m_nSize))
		{
			// copy in two steps
			ULONG nFirstStep = m_StorageObj.m_nSize-m_nLast; 
			ULONG nSecondStep = nValues-nFirstStep; 
			memcpy(m_StorageObj.m_pFiFoEntrys+m_nLast, pValueBlock, sizeof(typename StorageType::VALUE) * nFirstStep); 
			memcpy(m_StorageObj.m_pFiFoEntrys, pValueBlock+nFirstStep, sizeof(typename StorageType::VALUE) * nSecondStep); 
			// adjust last index 
			m_nLast = nSecondStep; 
		}
		else
		{
			// copy in one step
			memcpy(m_StorageObj.m_pFiFoEntrys+m_nLast, pValueBlock, sizeof(typename StorageType::VALUE) * nValues); 

			// adjust last index 
			m_nLast+=nValues;
			if (m_nLast == m_StorageObj.m_nSize)
			{
				m_nLast = 0; 
			}
		}
		m_nCount+=nValues; 
		m_SyncObj.Unlock(); 
		return nValues; 
	}


	ULONG RemoveBlock( typename StorageType::VALUE* pValueBlock, ULONG nValues)
	{
		m_SyncObj.Lock(); 
		if (nValues>static_cast<ULONG>(m_nCount))
		{
			nValues = m_nCount; 
		}
		if (m_nFirst+nValues>static_cast<ULONG>(m_StorageObj.m_nSize))
		{
			// copy in two steps
			ULONG nFirstStep = m_StorageObj.m_nSize-m_nFirst; 
			ULONG nSecondStep = nValues - nFirstStep; 
			memcpy(pValueBlock, m_StorageObj.m_pFiFoEntrys+m_nFirst, sizeof(typename StorageType::VALUE)*nFirstStep); 
			memcpy(pValueBlock+nFirstStep, m_StorageObj.m_pFiFoEntrys, sizeof(typename StorageType::VALUE)*nSecondStep); 

			// adjust first index 
			m_nFirst = nSecondStep;
		}
		else
		{
			// copy in one step
			memcpy(pValueBlock, m_StorageObj.m_pFiFoEntrys+m_nFirst, sizeof(typename StorageType::VALUE)*nValues); 

			// adjust first index 
			m_nFirst+=nValues; 
			if (m_nFirst == m_StorageObj.m_nSize)
			{
				m_nFirst = 0; 
			}
		}
		m_nCount -= nValues; 

		m_SyncObj.Unlock(); 
		return nValues; 
	}

	bool	Remove( typename StorageType::VALUE& rValue )
	{
		m_SyncObj.Lock(); 

		if ( m_nCount == 0 )
		{
			m_SyncObj.Unlock(); 
			return false;
		}

		rValue = m_StorageObj.m_pFiFoEntrys[m_nFirst];
		memset( &m_StorageObj.m_pFiFoEntrys[m_nFirst], 0, sizeof(typename StorageType::VALUE) );

		m_nFirst++;
		if ( m_nFirst == m_StorageObj.m_nSize )
			m_nFirst = 0;

		m_nCount--;

		m_SyncObj.Unlock(); 

		return true;
	}

	bool	Remove_Unprotected( typename StorageType::VALUE& rValue )
	{
		if ( m_nCount == 0 )
			return false;

		ASSERT( m_nFirst >= 0 && m_nFirst < m_StorageObj.m_nSize );

		rValue = m_StorageObj.m_pFiFoEntrys[m_nFirst];
		memset( &m_StorageObj.m_pFiFoEntrys[m_nFirst], 0, sizeof(typename StorageType::VALUE) );

		m_nFirst++;
		if ( m_nFirst == m_StorageObj.m_nSize )
			m_nFirst = 0;

		m_nCount--;

		return true;
	}

	bool	GetEntryXBeforeHead( LONG X, typename StorageType::VALUE& rValue )
	{
		m_SyncObj.Lock(); 

		if ( m_nCount < X )
		{
			m_SyncObj.Unlock(); 
			return false;
		}

		X += m_nFirst;
		if ( X >= m_StorageObj.m_nSize )
			X -= m_StorageObj.m_nSize;

		rValue = m_StorageObj.m_pFiFoEntrys[X];

		m_SyncObj.Unlock(); 

		return true;
	}

	LONG	Count()
	{
		return m_nCount;
	}

	LONG	Size()
	{
		return m_StorageObj.m_nSize;
	}

	LONG	FreeCount()
	{
		return m_StorageObj.m_nSize - m_nCount;
	}

#pragma warning(disable : 4312 4311 4302) // PVOID is handled as LONG -> disable related warning that are reported for 64 bit builds
	bool GetNextEntry( typename StorageType::VALUE& rValue, PVOID& pVoid )
	{
		bool bRet = false;
		LONG pos = (LONG)(LONG_PTR)pVoid;;
		m_SyncObj.Lock(); 

		if ( m_nCount == 0 )
		{
			m_SyncObj.Unlock(); 
			return false;
		}

		if ( pos == 0 )
		{
			rValue = m_StorageObj.m_pFiFoEntrys[m_nFirst];
			pos = m_nFirst+1;
			bRet = true;
		}
		else
		{
			if (pos == m_StorageObj.m_nSize)
				pos = 0;
				
			if (m_nLast > m_nFirst)
				bRet = pos >= m_nFirst && pos < m_nLast;
			else if (pos != m_nFirst)
				bRet = pos > m_nFirst || pos < m_nLast;
			else
				bRet = m_nFirst != m_nLast; //check if end of list is reached
	
			if (bRet)
			{
				rValue = m_StorageObj.m_pFiFoEntrys[pos];
				pos++;
			}
		}
		pVoid = (PVOID)(LONG_PTR)pos;
		m_SyncObj.Unlock(); 
		return bRet;
	}
#pragma warning(default : 4312 4311 4302)


	typename StorageType::VALUE* GetNextEntry( PVOID& pVoid )
	{
		typename StorageType::VALUE* pValue = NULL;		
		LONG pos = (LONG)(LONG_PTR)pVoid;

		m_SyncObj.Lock(); 
		if ( m_nCount == 0 )
		{
			m_SyncObj.Unlock(); 
			return NULL;
		}

		if ( pos == 0 )
		{
			pValue = &m_StorageObj.m_pFiFoEntrys[m_nFirst];
			pos = m_nFirst+1;
		}
		else
		{
			if (pos == m_StorageObj.m_nSize)
				pos = 0;

			bool bRet = false;
			if (m_nLast > m_nFirst)
				bRet = pos >= m_nFirst && pos < m_nLast;
			else if (pos != m_nFirst)
				bRet = pos > m_nFirst || pos < m_nLast;
			else
				bRet = m_nFirst != m_nLast; //check if end of list is reached

			if (bRet)
			{
				pValue = &m_StorageObj.m_pFiFoEntrys[pos];
				pos++;
			}
		}
		pVoid = (PVOID)(LONG_PTR)pos;
		m_SyncObj.Unlock(); 
		return pValue;
	}

protected:
	// protected non virtual destructor
	// - avoid virtual function table (needed for e.g. by class CFiFoW32List)
	// - no one can use a pointer to this base class to delete an object. 
	~CFiFoListBase()
	{
	}

	SyncType    m_SyncObj;
	StorageType m_StorageObj; 

	LONG		   m_nFirst;
	LONG		   m_nLast;
	LONG		   m_nCount;
	LONG			m_nReserved;	// to be compatible to 64bit memory layout

private:
};

///////////////////////////////////////////////////////////////////////////////
// CFiFoList

template <class VALUE, LONG SIZE, class SyncType = CSyncDefault>
class CFiFoList : public CFiFoListBase<CFiFoListStorageStatic<VALUE,SIZE>, SyncType>
{
public:
	// make size available at compile time
	enum
	{
		eSize = SIZE
	}; 

	CFiFoList()
	: CFiFoListBase<CFiFoListStorageStatic<VALUE,SIZE>, SyncType>()
	{
	}

protected:
};

///////////////////////////////////////////////////////////////////////////////
// CFiFoListDyn

template <class VALUE, class SyncType = CSyncDefault>
class CFiFoListDyn : public CFiFoListBase<CFiFoListStorageDynamic<VALUE>, SyncType>
{
public:
	CFiFoListDyn( LONG nSize )
		: CFiFoListBase<CFiFoListStorageDynamic<VALUE>, SyncType>()
	{
		this->m_StorageObj.Allocate(nSize);
	}

	~CFiFoListDyn()
	{
		this->m_StorageObj.Deallocate();
	}

};

///////////////////////////////////////////////////////////////////////////////
// CHandover3Buffer
// class to exchange data (from type TYPE) from one task (calls Write) to another task (calls Read) using 3 buffers
// 
template <class TYPE> class CHandover3Buffer
{
public:
	CHandover3Buffer() : m_nAccessR(0), m_nAccessW(0)
	{
#ifdef _DEBUG
		memset(m_data, 0xcd, sizeof(m_data));
#endif
	}
	bool Write(const TYPE* pData)
	{
		const LONG x[] = {0, 1, 0, 2, 0, 1, 0, -1};
		LONG c = x[m_nAccessR | m_nAccessW];

		if ( c < 0 )
			return false;

		memcpy_word_opt(&m_data[c], pData, sizeof(TYPE));

		InterlockedExchangeR0(&m_nAccessW, 1 << c);
		return true;
	}
	bool Read(TYPE* pData)
	{
		const LONG x[] = {-1, 0, 1, -2, 2, -2, -2, -2};

		InterlockedExchangeR0(&m_nAccessR, m_nAccessW);

		LONG c = x[m_nAccessR];
		ASSERT(c!=-2);

		if ( c >= 0 )
			memcpy_word_opt(pData, &m_data[c], sizeof(TYPE));
		else
			return false;

		return true;
	}
protected:
	TYPE	m_data[3];
	ULONG	m_nAccessR;
	ULONG	m_nAccessW;
};

///////////////////////////////////////////////////////////////////////////////
// CHandover3BufferDyn
// class to exchange data (size bytes) from one task (calls Write) to another task (calls Read) using 3 buffers
// 
class CHandover3BufferDyn
{
public:
	CHandover3BufferDyn(size_t size) : m_size(size), m_nAccessR(0), m_nAccessW(0)
	{
		m_asize = (m_size + 7) / 8;
		if ((m_buffer = new ULONGLONG[3 * m_asize]))
		{
			m_data[0] = &m_buffer[0];
			m_data[1] = &m_buffer[m_asize];
			m_data[2] = &m_buffer[m_asize << 1];
		}
#ifdef _DEBUG
		//memset(&m_buffer, 0xcd, 3 * m_asize * sizeof(ULONGLONG));
#endif
	}
	~CHandover3BufferDyn()
	{
		safe_delete(m_buffer);
	}
	bool Write(PVOID pData)
	{
		const LONG x[] = { 0, 1, 0, 2, 0, 1, 0, -1 };
		LONG c = x[m_nAccessR | m_nAccessW];

		if (c < 0)
			return false;

		memcpy_word_opt(m_data[c], pData, m_size);

		InterlockedExchangeR0(&m_nAccessW, 1 << c);
		return true;
	}
	bool Read(PVOID pData)
	{
		const LONG x[] = { -1, 0, 1, -2, 2, -2, -2, -2 };

		InterlockedExchangeR0(&m_nAccessR, m_nAccessW);

		LONG c = x[m_nAccessR];
		ASSERT(c != -2);

		if (c >= 0)
			memcpy_word_opt(pData, m_data[c], m_size);
		else
			return false;

		return true;
	}
	bool Clear()
	{
		const LONG x[] = { 0, 1, 0, 2, 0, 1, 0, -1 };
		LONG c = x[m_nAccessR | m_nAccessW];

		if (c < 0)
			return false;

		memset(m_data[c], 0, m_size);

		InterlockedExchangeR0(&m_nAccessW, 1 << c);
		return true;
	}
	size_t Size() { return m_size; }
protected:
	size_t m_size;
	PVOID	m_data[3];
	ULONG	m_nAccessR;
	ULONG	m_nAccessW;
private:
	size_t m_asize;
	PULONGLONG m_buffer;
};

///////////////////////////////////////////////////////////////////////////////
// CHandoverFifo
// class to exchange data in a fifo from one task (calls Insert) to another tasks (calls Remove)
// default fifo depth is 8 (2^3), only 2^n is possible
template <class TYPE, ULONG DEPTH_EXP=3> class CHandoverFifo
{
public:
	CHandoverFifo() : m_nAccessR(0), m_nAccessW(0)
	{
#ifdef _DEBUG
		memset(m_data, 0xcd, sizeof(m_data));
#endif
	}
	bool Insert(TYPE* pData)
	{
		if ( m_nAccessW-m_nAccessR == (1 << DEPTH_EXP) )
			return false;
		ULONG c = m_nAccessW & ((1 << DEPTH_EXP)-1);
		memcpy_word_opt(&m_data[c], pData, sizeof(TYPE));
		InterlockedIncrementR0(&m_nAccessW);
		return true;
	}
	bool Remove(TYPE* pData)
	{
		if ( m_nAccessR == m_nAccessW )
			return false;
		ULONG c = m_nAccessR & ((1 << DEPTH_EXP)-1);
		memcpy_word_opt(pData, &m_data[c], sizeof(TYPE));
		InterlockedIncrementR0(&m_nAccessR);
		return true;
	}
	bool Add(TYPE& data)
	{
		if ( m_nAccessW-m_nAccessR == (1 << DEPTH_EXP) )
			return false;
		ULONG c = m_nAccessW & ((1 << DEPTH_EXP)-1);
		memcpy_word_opt(&m_data[c], &data, sizeof(TYPE));
		InterlockedIncrementR0(&m_nAccessW);
		return true;
	}
	bool Remove(TYPE& data)
	{
		if ( m_nAccessR == m_nAccessW )
			return false;
		ULONG c = m_nAccessR & ((1 << DEPTH_EXP)-1);
		memcpy_word_opt(&data, &m_data[c], sizeof(TYPE));
		InterlockedIncrementR0(&m_nAccessR);
		return true;
	}
	ULONG GetCount()
	{
		return m_nAccessW - m_nAccessR;
	}
protected:
	TYPE	m_data[1 << DEPTH_EXP];
	ULONG	m_nAccessR;
	ULONG	m_nAccessW;
};

///////////////////////////////////////////////////////////////////////////////
// CHandoverFifo
// class to exchange data in a fifo from one task (calls Insert) to another tasks (calls Remove)
// default fifo depth is 8 (2^3), only 2^n is possible
template <class TYPE> class CHandoverFifoDyn
{
public:
	CHandoverFifoDyn(ULONG depth = 3) : m_nAccessR(0), m_nAccessW(0)
	{
		m_nData = 1 << depth;
		if ((m_data = new TYPE[m_nData])!=NULL)
		{
#ifdef _DEBUG
			memset(m_data, 0xcd, m_nData * sizeof(TYPE));
#endif
		}
		else
			m_nData = 0;
	}
	virtual ~CHandoverFifoDyn()
	{
		safe_delete(m_data);
	}
	bool Insert(TYPE* pData)
	{
		if (m_nAccessW - m_nAccessR == (m_nData))
			return false;
		ULONG c = m_nAccessW & ((m_nData) - 1);
		memcpy_word_opt(&m_data[c], pData, sizeof(TYPE));
		InterlockedIncrementR0(&m_nAccessW);
		return true;
	}
	bool Remove(TYPE* pData)
	{
		if (m_nAccessR == m_nAccessW)
			return false;
		ULONG c = m_nAccessR & ((m_nData) - 1);
		memcpy_word_opt(pData, &m_data[c], sizeof(TYPE));
		InterlockedIncrementR0(&m_nAccessR);
		return true;
	}
	bool Add(TYPE& data)
	{
		if (m_nAccessW - m_nAccessR == (m_nData))
			return false;
		ULONG c = m_nAccessW & ((m_nData) - 1);
		memcpy_word_opt(&m_data[c], &data, sizeof(TYPE));
		InterlockedIncrementR0(&m_nAccessW);
		return true;
	}
	bool Remove(TYPE& data)
	{
		if (m_nAccessR == m_nAccessW)
			return false;
		ULONG c = m_nAccessR & ((m_nData) - 1);
		memcpy_word_opt(&data, &m_data[c], sizeof(TYPE));
		InterlockedIncrementR0(&m_nAccessR);
		return true;
	}
	ULONG GetCount()
	{
		return m_nAccessW - m_nAccessR;
	}
protected:
	TYPE*	m_data;
	ULONG m_nData;
	ULONG	m_nAccessR;
	ULONG	m_nAccessW;
};

