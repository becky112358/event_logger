///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT Software Development Kit.
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "TcServices.h"
#include "SyncObjects.h"

///////////////////////////////////////////////////////////////////////////////
//	CHashTable

#define	HASHTABLESIZESMALL		17			// should be a prime
#define	HASHTABLESIZE				97			// should be a prime
#define	HASHTABLESIZEBIG			997		// should be a prime
#define	HASHTABLESIZEVERYBIG		9973		// should be a prime
#define	HASHTABLESIZEEXTREMEBIG	99991		// should be a prime

template <class KEY, class VALUE, int SIZE, class SyncType = CSyncDefault>
class DLL_EXPORT CHashTable
{

typedef void (*PForeEachFunc)( PVOID pThis, VALUE* pValue );

protected:
	typedef struct DLL_EXPORT HashEntry
	{
		HashEntry*	pNext;
		HashEntry*	pNextFree;
		HashEntry*	pNextGlob;
		KEY			key;
		VALUE			value;
	} *PHashEntry;

	HashEntry	m_aHashEntrys[SIZE];
	PHashEntry	m_pFreeEntrys;
	PHashEntry	m_pFirstEntry;
	PHashEntry	m_pEntrys[HASHTABLESIZE];
	DWORD			m_nKeyCount;

	mutable SyncType	m_SyncObject;

public:
	CHashTable()
	{
		int i;

		memset( m_pEntrys, 0, HASHTABLESIZE*sizeof(PHashEntry) );

		memset( m_aHashEntrys, 0, SIZE*sizeof(HashEntry) );
		
		for ( i = 1; i < SIZE; i++ )
			m_aHashEntrys[i-1].pNextFree = &m_aHashEntrys[i];

		m_aHashEntrys[SIZE-1].pNextFree = NULL;

		m_pFreeEntrys	= &m_aHashEntrys[0];
		m_pFirstEntry	= NULL;

		m_nKeyCount		= 0;
	}

	CHashTable(const CHashTable& src)
	{
		INT_PTR nOffs = (INT_PTR)m_aHashEntrys - (INT_PTR)src.m_aHashEntrys;

		memcpy(m_aHashEntrys, src.m_aHashEntrys, SIZE*sizeof(HashEntry));
		for ( int i=0; i<HASHTABLESIZE; i++ )
			m_pEntrys[i] = src.m_pEntrys[i] != NULL ?
									(PHashEntry)((BYTE*)src.m_pEntrys[i] + nOffs): NULL;

		m_pFreeEntrys	= (PHashEntry)((BYTE*)src.m_pFreeEntrys+nOffs);
		m_pFirstEntry	= (PHashEntry)((BYTE*)src.m_pFirstEntry+nOffs);
		m_nKeyCount		= src.m_nKeyCount;

	}

	virtual ~CHashTable()
	{
	}

#ifndef IS_R0 // don't use in kernel mode
	CHashTable& operator=(const CHashTable& src)
	{
		m_SyncObject.Lock();

		INT_PTR nOffs = (INT_PTR)m_aHashEntrys - (INT_PTR)src.m_aHashEntrys;

		memcpy(m_aHashEntrys, src.m_aHashEntrys, SIZE*sizeof(HashEntry));
		for ( int i=0; i<HASHTABLESIZE; i++ )
			m_pEntrys[i] = src.m_pEntrys[i] != NULL ?
									(PHashEntry)((BYTE*)src.m_pEntrys[i] + nOffs): NULL;

		m_pFreeEntrys	= (PHashEntry)((BYTE*)src.m_pFreeEntrys+nOffs);
		m_pFirstEntry	= (PHashEntry)((BYTE*)src.m_pFirstEntry+nOffs);
		m_nKeyCount		= src.m_nKeyCount;

		m_SyncObject.Unlock();

		return *this;
	}
#endif

	BOOL	Add( KEY key, VALUE newValue )
	{
		BOOL	ret	= FALSE;
		int	nHash = GetHashValue( key );
		PHashEntry p, n;

		m_SyncObject.Lock();

		if ( p = KeyInUse( key, nHash ) )
		{
			p->value = newValue;
			ret		= TRUE;
		}
		else
		{
			if ( m_pFreeEntrys )
			{
				n						= m_pFreeEntrys;
				m_pFreeEntrys		= m_pFreeEntrys->pNextFree;


				n->value				= newValue;
				n->key				= key;


				n->pNext				= m_pEntrys[nHash];
				m_pEntrys[nHash]	= n;

				n->pNextGlob		= m_pFirstEntry;
				m_pFirstEntry		= n;
				
				ret = TRUE;
				m_nKeyCount++;
			}
		}

		m_SyncObject.Unlock();

		return ret;
	}

	BOOL	AddCritical( KEY key, VALUE newValue )
	{
		BOOL	ret	= FALSE;
		int	nHash = GetHashValue( key );
		PHashEntry p, n;

		if ( p = KeyInUse( key, nHash ) )
		{
			p->value = newValue;
			ret		= TRUE;
		}
		else
		{
			if ( m_pFreeEntrys )
			{
				n						= m_pFreeEntrys;
				m_pFreeEntrys		= m_pFreeEntrys->pNextFree;


		
				n->value				= newValue;
				n->key				= key;

		
				n->pNext				= m_pEntrys[nHash];
				m_pEntrys[nHash]	= n;

				n->pNextGlob		= m_pFirstEntry;
				m_pFirstEntry		= n;
				
				ret = TRUE;
				m_nKeyCount++;
			}
		}

		return ret;
	}

	BOOL	Lookup( KEY key, VALUE& rValue )	const
	{
		BOOL	ret		= FALSE;
		int	nHash		= GetHashValue( key );
	
		m_SyncObject.Lock();

		PHashEntry p	= m_pEntrys[nHash];

		while ( p != NULL )
		{
			if ( p->key == key )
				break;
			p = p->pNext;
		}
		if ( p )
		{
			rValue	= p->value;
			ret		= TRUE;
		}

		m_SyncObject.Unlock();

		return ret;
	}

	BOOL	LookupCritical( KEY key, VALUE& rValue )	const
	{
		BOOL	ret		= FALSE;
		int	nHash		= GetHashValue( key );
	
		PHashEntry p	= m_pEntrys[nHash];

		while ( p != NULL )
		{
			if ( p->key == key )
				break;
			p = p->pNext;
		}
		if ( p )
		{
			rValue	= p->value;
			ret		= TRUE;
		}

		return ret;
	}

	VALUE* Lookup( KEY key )	const
	{
		int	nHash		= GetHashValue( key );

		m_SyncObject.Lock();

		PHashEntry p	= m_pEntrys[nHash];

		while ( p != NULL )
		{
			if ( p->key == key )
				break;
			p = p->pNext;
		}

		m_SyncObject.Unlock();

		if ( p )
			return &p->value;
		else
			return NULL;
	}

	BOOL	Remove( KEY key )
	{
		BOOL	ret		= FALSE;
		int	nHash		= GetHashValue( key );
		PHashEntry l	= NULL;

		m_SyncObject.Lock();

		PHashEntry p	= m_pEntrys[nHash];

		while ( p )										// searching right entry
		{
			if ( p->key == key )
				break;									// entry found

			l = p;										// l is previous entry
			p = p->pNext;
		}
		
		if ( p )
		{
			//	removing from hash-list
			if ( l )										// if not first entry
				l->pNext				= p->pNext;		//	entry removed
			else											//	if first entry
				m_pEntrys[nHash]	= p->pNext;		//	entry removed

			// removing from global-list
			if ( p == m_pFirstEntry )
				m_pFirstEntry = p->pNextGlob;
			else
			{
				l = m_pFirstEntry;
				while ( l->pNextGlob != p )
					l = l->pNextGlob;

				l->pNextGlob = p->pNextGlob;
			}
			
			m_nKeyCount--;

			p->pNextFree	= m_pFreeEntrys;
			m_pFreeEntrys	= p;

			ret				= TRUE;
		}
		else
		{
			TRACE(_T("HashTable Remove: unknown key\n"));
		}

		m_SyncObject.Unlock();

		return ret;
	}

	BOOL	RemoveCritical( KEY key )
	{
		BOOL	ret		= FALSE;
		int	nHash		= GetHashValue( key );
		PHashEntry l	= NULL;


		PHashEntry p	= m_pEntrys[nHash];

		while ( p )										// searching right entry
		{
			if ( p->key == key )
				break;									// entry found

			l = p;										// l is previous entry
			p = p->pNext;
		}
		
		if ( p )
		{
			//	removing from hash-list
			if ( l )										// if not first entry
				l->pNext				= p->pNext;		//	entry removed
			else											//	if first entry
				m_pEntrys[nHash]	= p->pNext;		//	entry removed

			// removing from global-list
			if ( p == m_pFirstEntry )
				m_pFirstEntry = p->pNextGlob;
			else
			{
				l = m_pFirstEntry;
				while ( l->pNextGlob != p )
					l = l->pNextGlob;

				l->pNextGlob = p->pNextGlob;
			}
			
			m_nKeyCount--;

			p->pNextFree	= m_pFreeEntrys;
			m_pFreeEntrys	= p;

			ret				= TRUE;
		}
		else
		{
			TRACE(_T("HashTable Remove: unknown key\n"));
		}


		return ret;
	}

	BOOL	RemoveFirstEntry( VALUE& rValue )
	{
		if ( m_pFirstEntry )
		{
			rValue = m_pFirstEntry->value;
			
			return Remove(m_pFirstEntry->key);
		}
		else
			return FALSE;
	}

	void	RemoveAll()
	{
		int i;

		memset( m_pEntrys, 0, HASHTABLESIZE*sizeof(PHashEntry) );

		memset( m_aHashEntrys, 0, SIZE*sizeof(HashEntry) );
		
		for ( i = 1; i < SIZE; i++ )
			m_aHashEntrys[i-1].pNextFree = &m_aHashEntrys[i];

		m_aHashEntrys[SIZE-1].pNextFree = NULL;

		m_pFreeEntrys	= &m_aHashEntrys[0];
		m_pFirstEntry	= NULL;

		m_nKeyCount		= 0;
	}

	BOOL GetFirstEntry( VALUE& rValue, PVOID& pVoid )
	{
		pVoid = m_pFirstEntry;

		if ( pVoid )
		{
			rValue = ((PHashEntry)pVoid)->value;
			return TRUE;
		}
		else
			return FALSE;
	}

	BOOL GetNextEntry( VALUE& rValue, PVOID& pVoid )
	{
		if ( !pVoid )
			pVoid = m_pFirstEntry;
		else
			pVoid = ((PHashEntry)pVoid)->pNextGlob;

		if ( pVoid )
		{
			rValue = ((PHashEntry)pVoid)->value;
			return TRUE;
		}
		else
			return FALSE;
	}

	BOOL GetNextEntry( KEY& rKey, VALUE*& pValue, PVOID& pVoid )
	{
		if ( !pVoid )
			pVoid = m_pFirstEntry;
		else
			pVoid = ((PHashEntry)pVoid)->pNextGlob;

		if ( pVoid )
		{
			pValue	= &(((PHashEntry)pVoid)->value);
			rKey		= ((PHashEntry)pVoid)->key;
			return TRUE;
		}
		else
			return FALSE;
	}

	BOOL KeyInUse( KEY key ) const
	{
		int			nHash	= GetHashValue( key );

		m_SyncObject.Lock();

		PHashEntry	p		= m_pEntrys[nHash];
		while ( p )
		{
			if ( p->key == key )
			{
				m_SyncObject.Unlock();
				return TRUE;
			}
			p = p->pNext;
		}

		m_SyncObject.Unlock();

		return FALSE;
	}

	BOOL KeyInUseCritical( KEY key ) const
	{
		int			nHash	= GetHashValue( key );

		PHashEntry	p		= m_pEntrys[nHash];
		while ( p )
		{
			if ( p->key == key )
			{
				return TRUE;
			}
			p = p->pNext;
		}

		return FALSE;
	}

	void ForEach( PForeEachFunc pFunc, PVOID pUser ) const
	{
		int i;
		PHashEntry	p;
		for ( i = 0; i < HASHTABLESIZE; i++ )
		{
			p = m_pEntrys[i];
			while ( p )
			{
				pFunc( pUser, &p->value );
				p = p->pNext;
			}
		}
	}

	DWORD KeyCount() const
	{
		return m_nKeyCount;
	}

protected:
	PHashEntry KeyInUse( KEY key, int nHash ) const
	{
		PHashEntry p = m_pEntrys[nHash];
		while ( p )
		{
			if ( p->key == key )
				return p;
			p = p->pNext;
		}
		return NULL;
	}

	int GetHashValue( KEY key ) const
	{ 
		return GetHashValueImpl(key); 
	}

private:

	template<typename T>
	int GetHashValueImpl(T key) const
	{
		int hash = key % HASHTABLESIZE;
		return (hash < 0) ? -hash : hash;
	}

	int GetHashValueImpl(GUID key) const
	{
		return (((PULONG)&key)[0] ^ ((PULONG)&key)[1] ^ ((PULONG)&key)[2] ^ ((PULONG)&key)[3]) % HASHTABLESIZE;
	}

	int GetHashValueImpl(unsigned char key) const { return GetHashValueImplUnsigned(key); }
	int GetHashValueImpl(unsigned short key) const { return GetHashValueImplUnsigned(key); }
	int GetHashValueImpl(unsigned int key) const { return GetHashValueImplUnsigned(key); }
	int GetHashValueImpl(unsigned long key) const { return GetHashValueImplUnsigned(key); }
	int GetHashValueImpl(unsigned long long key) const { return GetHashValueImplUnsigned(key); }

	template<typename T>
	int GetHashValueImplUnsigned(T key) const 
	{
		return key % HASHTABLESIZE;
	}
};

///////////////////////////////////////////////////////////////////////////////
//	CHashTableDyn
// Note for template parameter class VALUE:
// Constructor or destructor of type VALUE are not called on creation or 
// deletion of internal storage array. Type VALUE must not have virtual 
// functions, because its vtable will not be initialized. 
#define	HASHTABLEDYN_MAXBLOCKS	4
template <class KEY, class VALUE, class SyncType = CSyncDefault>
class DLL_EXPORT CHashTableDyn
{

typedef void (*PForeEachFunc)( PVOID pThis, VALUE* pValue );

protected:
	typedef struct HashEntry
	{
		HashEntry*	pNext;
		KEY			key;
		VALUE			value;
	} *PHashEntry;

	typedef struct BlockInfo
	{
		BlockInfo*	pNext;
		ULONG			size;
		HashEntry	hashEntrys[1];
	} *PBlockInfo;

#define	SIZEOF_BlockInfo(n)	(sizeof(BlockInfo) + (((int)(n))-1)*sizeof(HashEntry))

	PBlockInfo	m_pFirstBlock;
	PHashEntry	m_pFreeEntrys;
	PHashEntry*	m_ppEntrys;
	ULONG			m_nKeyCount;
	ULONG			m_hashSize;

	PHashEntry	m_pExtern;
	PHashEntry	m_pIterator;

	mutable SyncType	m_SyncObject;

public:
	CHashTableDyn( ULONG size, ULONG hashSize=HASHTABLESIZE )
	{
		m_hashSize		= hashSize;

		PBYTE p = new BYTE[SIZEOF_BlockInfo(size) + m_hashSize*sizeof(PHashEntry)];
		if (p)
		{
			memset(p, 0, SIZEOF_BlockInfo(size) + m_hashSize * sizeof(PHashEntry));

			m_pFirstBlock = (PBlockInfo)&p[0];
			m_pFirstBlock->size = size;

			m_ppEntrys = (PHashEntry*)&p[SIZEOF_BlockInfo(size)];

			for (ULONG i = 1; i < size; i++)
				m_pFirstBlock->hashEntrys[i - 1].pNext = &m_pFirstBlock->hashEntrys[i];

			m_pFirstBlock->hashEntrys[size - 1].pNext = NULL;

			m_pFreeEntrys = &m_pFirstBlock->hashEntrys[0];
		}
		else
		{
			TRACE(_T("CHashTableDyn::CHashTableDyn(): Error, allocation failed\n"));
			ASSERT(FALSE);
			m_pFirstBlock = NULL;
			m_pFreeEntrys = NULL;
		}
		m_nKeyCount		= 0;
		m_pExtern		= NULL;
		m_pIterator		= NULL;
	}

	~CHashTableDyn()
	{
		PBlockInfo p = m_pFirstBlock;
		while ( p )
		{
			PBlockInfo pNext = p->pNext;
			delete[] (BYTE*)p;
			p = pNext;
		}
	}
	VOID Lock()
	{
		m_SyncObject.Lock(); 
	}
	VOID Unlock()
	{
		m_SyncObject.Unlock(); 
	}
	BOOL	GrowTableSize(ULONG growBy=0)
	{
		if ( growBy == 0 )
			growBy = Size() * 5;

		PBlockInfo p = (PBlockInfo)new BYTE[SIZEOF_BlockInfo(growBy)];

		if ( p == NULL )
			return FALSE;

		memset( p, 0, SIZEOF_BlockInfo(growBy) );
		p->size	= growBy;
		
		for ( ULONG i = 1; i < growBy; i++ )
			p->hashEntrys[i-1].pNext = &p->hashEntrys[i];

		m_SyncObject.Lock();

		p->hashEntrys[growBy-1].pNext = m_pFreeEntrys;
		m_pFreeEntrys	= &p->hashEntrys[0];

		p->pNext			= m_pFirstBlock;
		m_pFirstBlock	= p;

		m_SyncObject.Unlock();

		return TRUE;
	}

	BOOL	AddGrow( KEY key, VALUE newValue, ULONG growBy=0 )
	{
		BOOL ret = Add(key, newValue);
		if ( !ret && GrowTableSize(growBy) )
			ret = Add(key, newValue);
		return ret;
	}

	BOOL	Add( KEY key, VALUE newValue )
	{
		BOOL	ret	= FALSE;
		int	nHash = GetHashValue( key );
		PHashEntry p, n;

		m_SyncObject.Lock();

		if ( p = KeyInUse( key, nHash ) )
		{
			p->value = newValue;
			ret		= TRUE;
		}
		else
		{
			if ( m_pFreeEntrys )
			{
				n						= m_pFreeEntrys;
				m_pFreeEntrys		= m_pFreeEntrys->pNext;

				n->value				= newValue;
				n->key				= key;

				n->pNext				= m_ppEntrys[nHash];
				m_ppEntrys[nHash]	= n;

				ret = TRUE;
				m_nKeyCount++;
			}
		}

		m_SyncObject.Unlock();

		return ret;
	}
	
	BOOL	AddCritical( KEY key, VALUE newValue )
	{
		BOOL	ret	= FALSE;
		int	nHash = GetHashValue( key );
		PHashEntry p, n;		

		if ( p = KeyInUse( key, nHash ) )
		{
			p->value = newValue;
			ret		= TRUE;
		}
		else
		{
			if ( m_pFreeEntrys )
			{
				n						= m_pFreeEntrys;
				m_pFreeEntrys		= m_pFreeEntrys->pNext;
				
				n->value				= newValue;
				n->key				= key;

				n->pNext				= m_ppEntrys[nHash];
				m_ppEntrys[nHash]	= n;

				ret = TRUE;
				m_nKeyCount++;
			}
		}

		return ret;
	}


	BOOL	Lookup( KEY key, VALUE& rValue )	const
	{
		BOOL	ret		= FALSE;
		int	nHash		= GetHashValue( key );

		m_SyncObject.Lock();

		PHashEntry p	= m_ppEntrys[nHash];

		while ( p != NULL )
		{
			if ( p->key == key )
				break;
			p = p->pNext;
		}
		if ( p )
		{
			rValue	= p->value;
			ret		= TRUE;
		}

		m_SyncObject.Unlock();

		return ret;
	}

	BOOL	LookupCritical( KEY key, VALUE& rValue )	const
	{
		BOOL	ret		= FALSE;
		int	nHash		= GetHashValue( key );

		PHashEntry p	= m_ppEntrys[nHash];

		while ( p != NULL )
		{
			if ( p->key == key )
				break;
			p = p->pNext;
		}
		if ( p )
		{
			rValue	= p->value;
			ret		= TRUE;
		}

		return ret;
	}

	VALUE* Lookup( KEY key )	const
	{
		int	nHash		= GetHashValue( key );
		
		m_SyncObject.Lock();
		
		PHashEntry p	= m_ppEntrys[nHash];

		while ( p != NULL )
		{
			if ( p->key == key )
				break;
			p = p->pNext;
		}

		m_SyncObject.Unlock();

		if ( p )
			return &p->value;
		else
			return NULL;
	}

	VALUE* LookupCritical( KEY key )	const
	{
		int	nHash		= GetHashValue( key );
		
		PHashEntry p	= m_ppEntrys[nHash];

		while ( p != NULL )
		{
			if ( p->key == key )
				break;
			p = p->pNext;
		}

		if ( p )
			return &p->value;
		else
			return NULL;
	}

	BOOL	Remove( KEY key )
	{
		BOOL	ret		= FALSE;
		int	nHash		= GetHashValue( key );
		PHashEntry l	= NULL;

		m_SyncObject.Lock();

		PHashEntry p	= m_ppEntrys[nHash];

		while ( p )										// searching right entry
		{
			if ( p->key == key )
				break;									// entry found

			l = p;										// l is previous entry
			p = p->pNext;
		}
		
		if ( p )
		{
			if ( p == m_pIterator )
			{
				if ( l )
					m_pIterator = l;
				else
				{
					m_pIterator = NULL;
					int n = nHash;
					while ( n > 0 )
					{
						n--;
						if ( m_ppEntrys[n] )
						{
							m_pIterator	= m_ppEntrys[n];
							while ( m_pIterator->pNext )
								m_pIterator = m_pIterator->pNext;
							break;
						}
					}
				}
			}

			//	removing from hash-list
			if ( l )										// if not first entry
				l->pNext				= p->pNext;		//	entry removed
			else											//	if first entry
				m_ppEntrys[nHash]	= p->pNext;		//	entry removed

			m_nKeyCount--;

			p->pNext			= m_pFreeEntrys;
			m_pFreeEntrys	= p;

			ret				= TRUE;
		}
		else
		{
			TRACE(_T("HashTable Remove: unknown key\n"));
		}

		m_SyncObject.Unlock();

		return ret;
	}

	BOOL	RemoveCritical( KEY key )
	{
		BOOL	ret		= FALSE;
		int	nHash		= GetHashValue( key );
		PHashEntry l	= NULL;
		PHashEntry p	= m_ppEntrys[nHash];

		while ( p )										// searching right entry
		{
			if ( p->key == key )
				break;									// entry found

			l = p;										// l is previous entry
			p = p->pNext;
		}
		
		if ( p )
		{
			if ( p == m_pIterator )
			{
				if ( l )
					m_pIterator = l;
				else
				{
					m_pIterator = NULL;
					int n = nHash;
					while ( n > 0 )
					{
						n--;
						if ( m_ppEntrys[n] )
						{
							m_pIterator	= m_ppEntrys[n];
							while ( m_pIterator->pNext )
								m_pIterator = m_pIterator->pNext;
							break;
						}
					}
				}
			}

			//	removing from hash-list
			if ( l )										// if not first entry
				l->pNext				= p->pNext;		//	entry removed
			else											//	if first entry
				m_ppEntrys[nHash]	= p->pNext;		//	entry removed

			m_nKeyCount--;

			p->pNext			= m_pFreeEntrys;
			m_pFreeEntrys	= p;

			ret				= TRUE;
		}
		else
		{
			TRACE(_T("HashTable Remove: unknown key\n"));
		}

		return ret;
	}

	BOOL GetFirstEntry( VALUE& rValue, PVOID& pVoid )
	{
		pVoid=NULL;
		if ( GetNextEntry(rValue, pVoid) )
			return TRUE;
		else
			return FALSE;
	}

	BOOL	RemoveFirstEntry( VALUE& rValue )
	{
		PVOID pVoid=NULL;
		if ( GetNextEntry(rValue, pVoid) )
			return Remove(((PHashEntry)pVoid)->key);
		else
			return FALSE;
	}

	BOOL	RemoveFirstEntry( KEY& rKey, VALUE& rValue )
	{
		ULONG n=0;
		while ( n < m_hashSize )
		{
			if ( m_ppEntrys[n] )
			{
				rKey		= m_ppEntrys[n]->key;
				rValue	= m_ppEntrys[n]->value;
				return Remove(m_ppEntrys[n]->key);
			}
			n++;
		}
		return FALSE;
	}

	void	RemoveAll()
	{
		memset( m_ppEntrys, 0, m_hashSize*sizeof(PHashEntry) );

		PBlockInfo p = m_pFirstBlock;
		while ( p )
		{
			memset( &p->hashEntrys[0], 0, p->size*sizeof(HashEntry) );
			
			for ( ULONG i = 1; i < p->size; i++ )
				p->hashEntrys[i-1].pNext = &p->hashEntrys[i];

			if ( p->pNext )
				p->hashEntrys[p->size-1].pNext = &p->pNext->hashEntrys[0];
			else
				p->hashEntrys[p->size-1].pNext = NULL;

			p = p->pNext;
		}

		m_pFreeEntrys	= &m_pFirstBlock->hashEntrys[0];

		m_pExtern	= NULL;
		m_pIterator	= NULL;

		m_nKeyCount		= 0;
	}

	BOOL GetNextEntry( VALUE& rValue, PVOID& pVoid )
	{
		ULONG n=m_hashSize;

		if ( pVoid == NULL )
		{
			m_pExtern	= NULL;
			m_pIterator	= NULL;
			n				= 0;
		}
		else if ( m_pExtern == pVoid )
		{
			if ( m_pIterator != NULL )
			{
				if ( m_pIterator->pNext )
				{
					pVoid = m_pExtern = m_pIterator	= m_pIterator->pNext;
					rValue	= m_pIterator->value;
					return TRUE;
				}
				else
					n = GetHashValue(m_pIterator->key) + 1;
			}
			else
				n = 0;
		}

		while ( n < m_hashSize )
		{
			if ( m_ppEntrys[n] )
			{
				pVoid		= m_pExtern = m_pIterator	= m_ppEntrys[n];
				rValue	= m_pIterator->value;
				return TRUE;
			}
			n++;
		}
		pVoid = m_pExtern = m_pIterator	= NULL;
		return FALSE;
	}

	BOOL GetNextEntry( KEY& rKey, VALUE*& pValue, PVOID& pVoid )
	{
		ULONG n=m_hashSize;

		if ( pVoid == NULL )
		{
			m_pExtern	= NULL;
			m_pIterator	= NULL;
			n				= 0;
		}
		else if ( m_pExtern == pVoid )
		{
			if ( m_pIterator != NULL )
			{
				if ( m_pIterator->pNext )
				{
					pVoid		= m_pExtern = m_pIterator = m_pIterator->pNext;
					pValue	= &(m_pIterator->value);
					rKey		= m_pIterator->key;
					return TRUE;
				}
				else
					n = GetHashValue(m_pIterator->key) + 1;
			}
			else
				n = 0;
		}

		while ( n < m_hashSize )
		{
			if ( m_ppEntrys[n] )
			{
				pVoid		= m_pExtern = m_pIterator = m_ppEntrys[n];
				pValue	= &(m_pIterator->value);
				rKey		= m_pIterator->key;
				return TRUE;
			}
			n++;
		}
	
		pVoid = m_pExtern = m_pIterator = NULL;
		return FALSE;
	}

	BOOL KeyInUse( KEY key ) const
	{
		int			nHash	= GetHashValue( key );
		m_SyncObject.Lock();
		PHashEntry	p		= m_ppEntrys[nHash];
		while ( p )
		{
			if ( p->key == key )
			{
				m_SyncObject.Unlock();
				return TRUE;
			}
			p = p->pNext;
		}
		m_SyncObject.Unlock();
		return FALSE;
	}

	void ForEach( PForeEachFunc pFunc, PVOID pUser ) const
	{
		ULONG i;
		PHashEntry	p;
		for ( i = 0; i < m_hashSize; i++ )
		{
			p = m_ppEntrys[i];
			while ( p )
			{
				pFunc( pUser, &p->value );
				p = p->pNext;
			}
		}
	}

	DWORD KeyCount() const
	{
		return m_nKeyCount;
	}

	ULONG Size() const
	{
		ULONG size=0;

		PBlockInfo p = m_pFirstBlock;
		while ( p )
		{
			size += p->size;
			p = p->pNext;
		}
		return size;
	}

protected:
	PHashEntry KeyInUse( KEY key, int nHash ) const
	{
		PHashEntry p = m_ppEntrys[nHash];
		while ( p )
		{
			if ( p->key == key )
				return p;
			p = p->pNext;
		}
		return NULL;
	}

	int GetHashValue( KEY key ) const
	{ 
		return GetHashValueImpl(key); 
	}

private:

	template<typename T> 
	int GetHashValueImpl(T key) const
	{
		int hash = key % m_hashSize;
		return (hash < 0) ? -hash : hash;
	}

	int GetHashValueImpl(unsigned char key) const { return GetHashValueImplUnsigned(key); }
	int GetHashValueImpl(unsigned short key) const { return GetHashValueImplUnsigned(key); }
	int GetHashValueImpl(unsigned int key) const { return GetHashValueImplUnsigned(key); }
	int GetHashValueImpl(unsigned long key) const { return GetHashValueImplUnsigned(key); }
	int GetHashValueImpl(unsigned long long key) const { return GetHashValueImplUnsigned(key); }

	int GetHashValueImpl(GUID key) const
	{
		return (((PULONG)&key)[0] ^ ((PULONG)&key)[1] ^ ((PULONG)&key)[2] ^ ((PULONG)&key)[3]) % m_hashSize;
	}

	int GetHashValueImpl(AmsAddr key) const
	{
		return (((int*)&key)[0] ^ ((int*)&key)[1]) % m_hashSize;
	}

	template<typename T>
	int GetHashValueImplUnsigned(T key) const 
	{
		return key % m_hashSize;
	}
};

///////////////////////////////////////////////////////////////////////////////
//	CInterfaceMapDyn
template <class KEY, class IFACE, class SyncType = CSyncDefault>
class DLL_EXPORT CInterfaceMapDyn
{

typedef void (*PForeEachFunc)( PVOID pThis, IFACE* pipValue );

protected:
	typedef struct HashEntry
	{
		HashEntry*	pNext;
		KEY			key;
		IFACE			ip;
	} *PHashEntry;

	typedef struct BlockInfo
	{
		BlockInfo*	pNext;
		ULONG			size;
		HashEntry	hashEntrys[1];
	} *PBlockInfo;

#define	SIZEOF_BlockInfo(n)	(sizeof(BlockInfo) + (((int)(n))-1)*sizeof(HashEntry))

	PBlockInfo	m_pFirstBlock;
	PHashEntry	m_pFreeEntrys;
	PHashEntry*	m_ppEntrys;
	ULONG			m_nKeyCount;
	ULONG			m_hashSize;

	PHashEntry	m_pExtern;
	PHashEntry	m_pIterator;

	mutable SyncType	m_SyncObject;

public:
	CInterfaceMapDyn( ULONG size, ULONG hashSize=HASHTABLESIZE )
	{
		m_hashSize		= hashSize;

		PBYTE p = new BYTE[SIZEOF_BlockInfo(size) + m_hashSize*sizeof(PHashEntry)];
		memset(p, 0, SIZEOF_BlockInfo(size) + m_hashSize*sizeof(PHashEntry));

		m_pFirstBlock			= (PBlockInfo)&p[0];
		m_pFirstBlock->size	= size;

		m_ppEntrys				= (PHashEntry*)&p[SIZEOF_BlockInfo(size)];

		for ( ULONG i = 1; i < size; i++ )
			m_pFirstBlock->hashEntrys[i-1].pNext = &m_pFirstBlock->hashEntrys[i];

		m_pFirstBlock->hashEntrys[size-1].pNext = NULL;

		m_pFreeEntrys	= &m_pFirstBlock->hashEntrys[0];

		m_nKeyCount		= 0;

		m_pExtern		= NULL;
		m_pIterator		= NULL;
	}

	~CInterfaceMapDyn()
	{
		IFACE ip;
		while ( SUCCEEDED(DeleteFirstEntry(ip)) )
			ip->TcRelease();

		PBlockInfo p = m_pFirstBlock;
		while ( p )
		{
			PBlockInfo pNext = p->pNext;
			delete[] (BYTE*)p;
			p = pNext;
		}
	}

	HRESULT	GrowTableSize(ULONG growBy=0)
	{
		if ( growBy == 0 )
			growBy = Size() * 5;

		PBlockInfo p = (PBlockInfo)new BYTE[SIZEOF_BlockInfo(growBy)];

		if ( p == NULL )
			return E_POINTER;

		memset( p, 0, SIZEOF_BlockInfo(growBy) );
		p->size	= growBy;
		
		for ( ULONG i = 1; i < growBy; i++ )
			p->hashEntrys[i-1].pNext = &p->hashEntrys[i];

		m_SyncObject.Lock();

		p->hashEntrys[growBy-1].pNext = m_pFreeEntrys;
		m_pFreeEntrys	= &p->hashEntrys[0];

		p->pNext			= m_pFirstBlock;
		m_pFirstBlock	= p;

		m_SyncObject.Unlock();

		return S_OK;
	}

	HRESULT	InsertGrow( KEY key, IFACE ip, ULONG growBy=0 )
	{
		HRESULT hr = Insert(key, ip);
		if ( hr == E_OUTOFMEMORY && SUCCEEDED(GrowTableSize(growBy)) )
			hr = Insert(key, ip);
		return hr;
	}

	HRESULT	Insert( KEY key, IFACE ip )
	{
		HRESULT	ret	= E_OUTOFMEMORY;
		int	nHash = GetHashValue( key );
		PHashEntry p, n;
		IFACE	ipOld=NULL;

		m_SyncObject.Lock();

		if ( p = KeyInUse( key, nHash ) )
		{
			ipOld		= p->ip;
			p->ip = ip;
			p->ip->TcAddRef();
			ret		= S_OK;
		}
		else
		{
			if ( m_pFreeEntrys )
			{
				n						= m_pFreeEntrys;
				m_pFreeEntrys		= m_pFreeEntrys->pNext;

				m_SyncObject.Unlock();
		
				n->ip				= ip;
				n->ip->TcAddRef();
				n->key				= key;

				m_SyncObject.Lock();
		
				n->pNext				= m_ppEntrys[nHash];
				m_ppEntrys[nHash]	= n;

				ret = S_OK;
				m_nKeyCount++;
			}
		}

		m_SyncObject.Unlock();

		if ( ipOld )
			ipOld->TcRelease();

		return ret;
	}

	HRESULT	Find( KEY key, IFACE& rip )	const
	{
		HRESULT	ret	= ADS_E_INVALIDPARM;
		int	nHash		= GetHashValue( key );

		m_SyncObject.Lock();

		PHashEntry p	= m_ppEntrys[nHash];

		while ( p != NULL )
		{
			if ( p->key == key )
				break;
			p = p->pNext;
		}
		if ( p )
		{
			rip		= p->ip;
			rip->TcAddRef();
			ret		= S_OK;
		}

		m_SyncObject.Unlock();

		return ret;
	}

	HRESULT	Find( KEY key, ITCID iid, PPVOID pip )	const
	{
		HRESULT	ret	= ADS_E_INVALIDPARM;
		IFACE	ip;
		int	nHash		= GetHashValue( key );

		m_SyncObject.Lock();

		PHashEntry p	= m_ppEntrys[nHash];

		while ( p != NULL )
		{
			if ( p->key == key )
				break;
			p = p->pNext;
		}
		if ( p )
		{
			ip			= p->ip;
			ip->TcAddRef();
			m_SyncObject.Unlock();
			ret		= ip->TcQueryInterface(iid, pip);
			ip->TcRelease();
		}
		else
		{
			m_SyncObject.Unlock();
		}

		return ret;
	}

	HRESULT	FindCritical( KEY key, IFACE& rip )	const
	{
		HRESULT	ret	= ADS_E_INVALIDPARM;
		int	nHash		= GetHashValue( key );

		PHashEntry p	= m_ppEntrys[nHash];

		while ( p != NULL )
		{
			if ( p->key == key )
				break;
			p = p->pNext;
		}
		if ( p )
		{
			rip		= p->ip;
			rip->TcAddRef();
			ret		= S_OK;
		}

		return ret;
	}

	HRESULT	FindCritical( KEY key, ITCID iid, PPVOID pip )	const
	{
		HRESULT	ret	= ADS_E_INVALIDPARM;
		int	nHash		= GetHashValue( key );

		PHashEntry p	= m_ppEntrys[nHash];

		while ( p != NULL )
		{
			if ( p->key == key )
				break;
			p = p->pNext;
		}
		if ( p )
			ret		= p->ip->TcQueryInterface(iid, pip);

		return ret;
	}

	IFACE* Find( KEY key )	const
	{
		int	nHash		= GetHashValue( key );
		
		m_SyncObject.Lock();
		
		PHashEntry p	= m_ppEntrys[nHash];

		while ( p != NULL )
		{
			if ( p->key == key )
				break;
			p = p->pNext;
		}

		m_SyncObject.Unlock();

		if ( p )
		{
			p->ip->TcAddRef();
			return &p->ip;
		}
		else
			return NULL;
	}

	HRESULT	Delete( KEY key )
	{
		HRESULT	ret	= ADS_E_INVALIDPARM;
		int	nHash		= GetHashValue( key );
		PHashEntry l	= NULL;

		m_SyncObject.Lock();

		PHashEntry p	= m_ppEntrys[nHash];

		while ( p )										// searching right entry
		{
			if ( p->key == key )
				break;									// entry found

			l = p;										// l is previous entry
			p = p->pNext;
		}
		
		if ( p )
		{
			if ( p == m_pIterator )
			{
				if ( l )
					m_pIterator = l;
				else
				{
					m_pIterator = NULL;
					int n = nHash;
					while ( n > 0 )
					{
						n--;
						if ( m_ppEntrys[n] )
						{
							m_pIterator	= m_ppEntrys[n];
							while ( m_pIterator->pNext )
								m_pIterator = m_pIterator->pNext;
							break;
						}
					}
				}
			}

			//	removing from hash-list
			if ( l )										// if not first entry
				l->pNext				= p->pNext;		//	entry removed
			else											//	if first entry
				m_ppEntrys[nHash]	= p->pNext;		//	entry removed

			m_nKeyCount--;

			m_SyncObject.Unlock();
			p->ip->TcRelease();
			m_SyncObject.Lock();
	
			p->pNext			= m_pFreeEntrys;
			m_pFreeEntrys	= p;

			ret				= S_OK;
		}
		else
		{
			TRACE(_T("HashTable Remove: unknown key\n"));
		}

		m_SyncObject.Unlock();

		return ret;
	}

	HRESULT	DeleteFirstEntry( IFACE& rip )
	{
		PVOID pVoid=NULL;
		if ( SUCCEEDED(GetNext(rip, pVoid)) )
			return Delete(((PHashEntry)pVoid)->key);
		else
			return ADS_E_ERROR;
	}

	HRESULT	Clear()
	{
		IFACE ip;
		while ( SUCCEEDED(DeleteFirstEntry(ip)) )
			ip->TcRelease();

		memset( m_ppEntrys, 0, m_hashSize*sizeof(PHashEntry) );

		PBlockInfo p = m_pFirstBlock;
		while ( p )
		{
			memset( &p->hashEntrys[0], 0, p->size*sizeof(HashEntry) );
			
			for ( ULONG i = 1; i < p->size; i++ )
				p->hashEntrys[i-1].pNext = &p->hashEntrys[i];

			if ( p->pNext )
				p->hashEntrys[p->size-1].pNext = &p->pNext->hashEntrys[0];
			else
				p->hashEntrys[p->size-1].pNext = NULL;

			p = p->pNext;
		}

		m_pFreeEntrys	= &m_pFirstBlock->hashEntrys[0];

		m_pExtern	= NULL;
		m_pIterator	= NULL;

		m_nKeyCount		= 0;
		return S_OK;
	}

	HRESULT GetNext( IFACE& rip, PVOID& pVoid )
	{
		ULONG n=m_hashSize;

		if ( pVoid == NULL )
		{
			m_pExtern	= NULL;
			m_pIterator	= NULL;
			n				= 0;
		}
		else if ( m_pExtern == pVoid )
		{
			if ( m_pIterator != NULL )
			{
				if ( m_pIterator->pNext )
				{
					pVoid = m_pExtern = m_pIterator	= m_pIterator->pNext;
					rip	= m_pIterator->ip;
					rip->TcAddRef();
					return S_OK;
				}
				else
					n = GetHashValue(m_pIterator->key) + 1;
			}
			else
				n = 0;
		}

		while ( n < m_hashSize )
		{
			if ( m_ppEntrys[n] )
			{
				pVoid	= m_pExtern = m_pIterator	= m_ppEntrys[n];
				rip	= m_pIterator->ip;
				rip->TcAddRef();
				return S_OK;
			}
			n++;
		}
		pVoid = m_pExtern = m_pIterator	= NULL;
		return ADS_E_ERROR;
	}

	HRESULT GetNext( ITCID iid, PPVOID pip, PVOID& pVoid )
	{
		HRESULT	hr = ADS_E_ERROR;
		IFACE		ip;
		while ( SUCCEEDED(hr=GetNext(ip, pVoid)) )
		{
			if ( SUCCEEDED(hr=ip->TcQueryInterface(iid, pip)) )
			{
				ip->TcRelease();
				return hr;
			}
			ip->TcRelease();
		}
		return hr;
	}

	HRESULT GetNext( KEY& rKey, IFACE& pip, PVOID& pVoid )
	{
		ULONG n=m_hashSize;

		if ( pVoid == NULL )
		{
			m_pExtern	= NULL;
			m_pIterator	= NULL;
			n				= 0;
		}
		else if ( m_pExtern == pVoid )
		{
			if ( m_pIterator != NULL )
			{
				if ( m_pIterator->pNext )
				{
					pVoid	= m_pExtern = m_pIterator = m_pIterator->pNext;
					pip	= m_pIterator->ip;
					rKey	= m_pIterator->key;
					pip->TcAddRef();
					return S_OK;
				}
				else
					n = GetHashValue(m_pIterator->key) + 1;
			}
			else 
				n = 0;
		}

		while ( n < m_hashSize )
		{
			if ( m_ppEntrys[n] )
			{
				pVoid	= m_pExtern = m_pIterator = m_ppEntrys[n];
				pip	= m_pIterator->ip;
				rKey	= m_pIterator->key;
				pip->TcAddRef();
				return S_OK;
			}
			n++;
		}
		pVoid = m_pExtern = m_pIterator = NULL;
		return ADS_E_ERROR;
	}

	HRESULT InUse( KEY key ) const
	{
		int			nHash	= GetHashValue( key );
		m_SyncObject.Lock();
		PHashEntry	p		= m_ppEntrys[nHash];
		while ( p )
		{
			if ( p->key == key )
			{
				m_SyncObject.Unlock();
				return S_OK;
			}
			p = p->pNext;
		}
		m_SyncObject.Unlock();
		return S_FALSE;
	}

	HRESULT CallEach( PForeEachFunc pFunc, PVOID pUser ) const
	{
		ULONG i;
		PHashEntry	p;
		for ( i = 0; i < m_hashSize; i++ )
		{
			p = m_ppEntrys[i];
			while ( p )
			{
				pFunc( pUser, &p->ip );
				p = p->pNext;
			}
		}
		return S_OK;
	}

	DWORD Count() const
	{
		return m_nKeyCount;
	}

	ULONG Size() const
	{
		ULONG size=0;

		PBlockInfo p = m_pFirstBlock;
		while ( p )
		{
			size += p->size;
			p = p->pNext;
		}
		return size;
	}

protected:
	PHashEntry KeyInUse( KEY key, int nHash ) const
	{
		PHashEntry p = m_ppEntrys[nHash];
		while ( p )
		{
			if ( p->key == key )
				return p;
			p = p->pNext;
		}
		return NULL;
	}

	ULONG GetHashValue( KEY key ) const
		{ return ( key % m_hashSize ); }

};

/////////////////////////////////////////////////////////////////////////////
// CListR0<TYPE, ARG_TYPE, SIZE>

#if !defined(_AFXDLL)  && !defined(__AFX_H__) && !defined(__ATLCOLL_H__)
	typedef	PVOID		POSITION;
#endif

template<class TYPE, class ARG_TYPE, UINT SIZE>
class DLL_EXPORT CListR0
{
protected:
	struct DLL_EXPORT CNode
	{
		CNode* pNext;
		CNode* pPrev;
		TYPE data;
	};
public:
// Construction
	CListR0();

// Attributes (head and tail)
	// count of elements
	UINT GetCount() const;
	UINT GetFreeCount() const;
	BOOL IsEmpty() const;

	// peek at head or tail
	TYPE& GetHead();
	TYPE GetHead() const;
	TYPE& GetTail();
	TYPE GetTail() const;

// Operations
	// get head or tail (and remove it) - don't call on empty list !
	TYPE RemoveHead();
	TYPE RemoveHeadCritical();
	TYPE RemoveTail();
	TYPE RemoveTailCritical();
	void RemoveAll();
	void RemoveAllCritical();

	// add before head or after tail
	POSITION AddHead(ARG_TYPE newElement);
	POSITION AddHeadCritical(ARG_TYPE newElement);
	POSITION AddTail(ARG_TYPE newElement);
	POSITION AddTailCritical(ARG_TYPE newElement);

	// iteration
	POSITION GetHeadPosition() const;
	POSITION GetTailPosition() const;
	TYPE& GetNext(POSITION& rPosition); // return *Position++
	TYPE GetNext(POSITION& rPosition) const; // return *Position++
	TYPE& GetPrev(POSITION& rPosition); // return *Position--
	TYPE GetPrev(POSITION& rPosition) const; // return *Position--

	// getting/modifying an element at a given position
	TYPE& GetAt(POSITION position);
	TYPE GetAt(POSITION position) const;
	void SetAt(POSITION pos, ARG_TYPE newElement);
	void RemoveAt(POSITION position);
	void RemoveAtCritical(POSITION position);

	// inserting before or after a given position
	POSITION InsertBefore(POSITION position, ARG_TYPE newElement);
	POSITION InsertBeforeCritical(POSITION position, ARG_TYPE newElement);
	POSITION InsertAfter(POSITION position, ARG_TYPE newElement);
	POSITION InsertAfterCritical(POSITION position, ARG_TYPE newElement);

	// helper functions (note: O(n) speed)
	POSITION Find(ARG_TYPE searchValue, POSITION startAfter = NULL) const;
		// defaults to starting at the HEAD, return NULL if not found
	POSITION FindIndex(int nIndex) const;
		// get the 'nIndex'th element (may return NULL)

// Implementation
protected:
	CNode*	m_pNodeHead;
	CNode*	m_pNodeTail;
	CNode*	m_pNodeFree;
	UINT		m_nCount;
	CNode		m_arrNodeFree[SIZE];

	DECLARE_CRITSEC
public:
	~CListR0();
//	void Serialize(CArchive&);
};


template<class TYPE, class ARG_TYPE, UINT SIZE>
inline UINT CListR0<TYPE, ARG_TYPE, SIZE>::GetCount() const
	{ return m_nCount; }
template<class TYPE, class ARG_TYPE, UINT SIZE>
inline UINT CListR0<TYPE, ARG_TYPE, SIZE>::GetFreeCount() const
	{ return SIZE-m_nCount; }
template<class TYPE, class ARG_TYPE, UINT SIZE>
BOOL CListR0<TYPE, ARG_TYPE, SIZE>::IsEmpty() const
	{ return m_nCount == 0; }
template<class TYPE, class ARG_TYPE, UINT SIZE>
TYPE& CListR0<TYPE, ARG_TYPE, SIZE>::GetHead()
	{ ASSERT(m_pNodeHead != NULL);
		return m_pNodeHead->data; }
template<class TYPE, class ARG_TYPE, UINT SIZE>
TYPE CListR0<TYPE, ARG_TYPE, SIZE>::GetHead() const
	{ ASSERT(m_pNodeHead != NULL);
		return m_pNodeHead->data; }
template<class TYPE, class ARG_TYPE, UINT SIZE>
TYPE& CListR0<TYPE, ARG_TYPE, SIZE>::GetTail()
	{ ASSERT(m_pNodeTail != NULL);
		return m_pNodeTail->data; }
template<class TYPE, class ARG_TYPE, UINT SIZE>
TYPE CListR0<TYPE, ARG_TYPE, SIZE>::GetTail() const
	{ ASSERT(m_pNodeTail != NULL);
		return m_pNodeTail->data; }
template<class TYPE, class ARG_TYPE, UINT SIZE>
POSITION CListR0<TYPE, ARG_TYPE, SIZE>::GetHeadPosition() const
	{ return (POSITION) m_pNodeHead; }
template<class TYPE, class ARG_TYPE, UINT SIZE>
POSITION CListR0<TYPE, ARG_TYPE, SIZE>::GetTailPosition() const
	{ return (POSITION) m_pNodeTail; }
template<class TYPE, class ARG_TYPE, UINT SIZE>
TYPE& CListR0<TYPE, ARG_TYPE, SIZE>::GetNext(POSITION& rPosition) // return *Position++
	{ CNode* pNode = (CNode*) rPosition;
		rPosition = (POSITION) pNode->pNext;
		return pNode->data; }
template<class TYPE, class ARG_TYPE, UINT SIZE>
TYPE CListR0<TYPE, ARG_TYPE, SIZE>::GetNext(POSITION& rPosition) const // return *Position++
	{ CNode* pNode = (CNode*) rPosition;
		rPosition = (POSITION) pNode->pNext;
		return pNode->data; }
template<class TYPE, class ARG_TYPE, UINT SIZE>
TYPE& CListR0<TYPE, ARG_TYPE, SIZE>::GetPrev(POSITION& rPosition) // return *Position--
	{ CNode* pNode = (CNode*) rPosition;
		rPosition = (POSITION) pNode->pPrev;
		return pNode->data; }
template<class TYPE, class ARG_TYPE, UINT SIZE>
TYPE CListR0<TYPE, ARG_TYPE, SIZE>::GetPrev(POSITION& rPosition) const // return *Position--
	{ CNode* pNode = (CNode*) rPosition;
		rPosition = (POSITION) pNode->pPrev;
		return pNode->data; }
template<class TYPE, class ARG_TYPE, UINT SIZE>
TYPE& CListR0<TYPE, ARG_TYPE, SIZE>::GetAt(POSITION position)
	{ CNode* pNode = (CNode*) position;
		return pNode->data; }
template<class TYPE, class ARG_TYPE, UINT SIZE>
TYPE CListR0<TYPE, ARG_TYPE, SIZE>::GetAt(POSITION position) const
	{ CNode* pNode = (CNode*) position;
		return pNode->data; }
template<class TYPE, class ARG_TYPE, UINT SIZE>
void CListR0<TYPE, ARG_TYPE, SIZE>::SetAt(POSITION pos, ARG_TYPE newElement)
	{ CNode* pNode = (CNode*) pos;
		pNode->data = newElement; }

template<class TYPE, class ARG_TYPE, UINT SIZE>
CListR0<TYPE, ARG_TYPE, SIZE>::CListR0()
{
	memset( m_arrNodeFree, 0, sizeof(m_arrNodeFree) );

	for ( UINT i=1; i < SIZE; i++ )
	{
		m_arrNodeFree[i].pPrev = &m_arrNodeFree[i-1];
		m_arrNodeFree[i-1].pNext = &m_arrNodeFree[i];
	}

	m_pNodeFree = m_arrNodeFree;
	m_pNodeHead	= NULL;
	m_pNodeTail	= NULL;

	m_nCount		= 0;

	INIT_CRITSEC
}

template<class TYPE, class ARG_TYPE, UINT SIZE>
CListR0<TYPE, ARG_TYPE, SIZE>::~CListR0()
{
	DELETE_CRITSEC
}

template<class TYPE, class ARG_TYPE, UINT SIZE>
POSITION CListR0<TYPE, ARG_TYPE, SIZE>::AddHead(ARG_TYPE newElement)
{
	if ( !m_pNodeFree )
		return NULL;

	CNode* pNewNode = m_pNodeFree;
	m_pNodeFree = m_pNodeFree->pNext;
	pNewNode->pPrev = NULL;
	pNewNode->pNext = m_pNodeHead;
	m_nCount++;

	pNewNode->data = newElement;

	DISABLE_IRQS();

	if (m_pNodeHead != NULL)
		m_pNodeHead->pPrev = pNewNode;
	else
		m_pNodeTail = pNewNode;
	m_pNodeHead = pNewNode;

	ENABLE_IRQS();

	return (POSITION) pNewNode;
}

template<class TYPE, class ARG_TYPE, UINT SIZE>
POSITION CListR0<TYPE, ARG_TYPE, SIZE>::AddHeadCritical(ARG_TYPE newElement)
{
	if ( !m_pNodeFree )
		return NULL;

	CNode* pNewNode = m_pNodeFree;
	m_pNodeFree = m_pNodeFree->pNext;
	pNewNode->pPrev = NULL;
	pNewNode->pNext = m_pNodeHead;
	m_nCount++;

	pNewNode->data = newElement;

	if (m_pNodeHead != NULL)
		m_pNodeHead->pPrev = pNewNode;
	else
		m_pNodeTail = pNewNode;
	m_pNodeHead = pNewNode;

	return (POSITION) pNewNode;
}

template<class TYPE, class ARG_TYPE, UINT SIZE>
POSITION CListR0<TYPE, ARG_TYPE, SIZE>::AddTail(ARG_TYPE newElement)
{
	if ( !m_pNodeFree )
		return NULL;

	DISABLE_IRQS();

	CNode* pNewNode = m_pNodeFree;
	m_pNodeFree = m_pNodeFree->pNext;
	pNewNode->pPrev = m_pNodeTail;
	pNewNode->pNext = NULL;
	m_nCount++;

	pNewNode->data = newElement;

	if (m_pNodeTail != NULL)
		m_pNodeTail->pNext = pNewNode;
	else
		m_pNodeHead = pNewNode;
	m_pNodeTail = pNewNode;

	ENABLE_IRQS();

	return (POSITION) pNewNode;
}

template<class TYPE, class ARG_TYPE, UINT SIZE>
POSITION CListR0<TYPE, ARG_TYPE, SIZE>::AddTailCritical(ARG_TYPE newElement)
{
	if ( !m_pNodeFree )
		return NULL;

	CNode* pNewNode = m_pNodeFree;
	m_pNodeFree = m_pNodeFree->pNext;
	pNewNode->pPrev = m_pNodeTail;
	pNewNode->pNext = NULL;
	m_nCount++;

	pNewNode->data = newElement;

	if (m_pNodeTail != NULL)
		m_pNodeTail->pNext = pNewNode;
	else
		m_pNodeHead = pNewNode;
	m_pNodeTail = pNewNode;

	return (POSITION) pNewNode;
}

template<class TYPE, class ARG_TYPE, UINT SIZE>
TYPE CListR0<TYPE, ARG_TYPE, SIZE>::RemoveHead()
{
	ASSERT(m_pNodeHead != NULL);  // don't call on empty list !!!

	DISABLE_IRQS();

	CNode* pOldNode = m_pNodeHead;
	TYPE returnValue = pOldNode->data;

	m_pNodeHead = pOldNode->pNext;
	if (m_pNodeHead != NULL)
		m_pNodeHead->pPrev = NULL;
	else
		m_pNodeTail = NULL;

	pOldNode->pNext = m_pNodeFree;
	m_pNodeFree = pOldNode;
	m_nCount--;

	ENABLE_IRQS();

	ASSERT(m_nCount >= 0);  // make sure we don't underflow

	return returnValue;
}

template<class TYPE, class ARG_TYPE, UINT SIZE>
TYPE CListR0<TYPE, ARG_TYPE, SIZE>::RemoveHeadCritical()
{
	ASSERT(m_pNodeHead != NULL);  // don't call on empty list !!!

	CNode* pOldNode = m_pNodeHead;
	TYPE returnValue = pOldNode->data;

	m_pNodeHead = pOldNode->pNext;
	if (m_pNodeHead != NULL)
		m_pNodeHead->pPrev = NULL;
	else
		m_pNodeTail = NULL;

	pOldNode->pNext = m_pNodeFree;
	m_pNodeFree = pOldNode;
	m_nCount--;

	ASSERT(m_nCount >= 0);  // make sure we don't underflow

	return returnValue;
}

template<class TYPE, class ARG_TYPE, UINT SIZE>
TYPE CListR0<TYPE, ARG_TYPE, SIZE>::RemoveTail()
{
	ASSERT(m_pNodeHead != NULL);  // don't call on empty list !!!

	DISABLE_IRQS();

	CNode* pOldNode = m_pNodeTail;
	TYPE returnValue = pOldNode->data;

	m_pNodeTail = pOldNode->pPrev;
	if (m_pNodeTail != NULL)
		m_pNodeTail->pNext = NULL;
	else
		m_pNodeHead = NULL;

	pOldNode->pNext = m_pNodeFree;
	m_pNodeFree = pOldNode;
	m_nCount--;

	ENABLE_IRQS();

	ASSERT(m_nCount >= 0);  // make sure we don't underflow

	return returnValue;
}

template<class TYPE, class ARG_TYPE, UINT SIZE>
TYPE CListR0<TYPE, ARG_TYPE, SIZE>::RemoveTailCritical()
{
	ASSERT(m_pNodeHead != NULL);  // don't call on empty list !!!

	CNode* pOldNode = m_pNodeTail;
	TYPE returnValue = pOldNode->data;

	m_pNodeTail = pOldNode->pPrev;
	if (m_pNodeTail != NULL)
		m_pNodeTail->pNext = NULL;
	else
		m_pNodeHead = NULL;

	pOldNode->pNext = m_pNodeFree;
	m_pNodeFree = pOldNode;
	m_nCount--;

	ASSERT(m_nCount >= 0);  // make sure we don't underflow

	return returnValue;
}

template<class TYPE, class ARG_TYPE, UINT SIZE>
void CListR0<TYPE, ARG_TYPE, SIZE>::RemoveAll()
{
	DISABLE_IRQS();
	while (m_pNodeHead)
	{
		CNode* pOldNode = m_pNodeHead;
		m_pNodeHead = pOldNode->pNext;
		if (m_pNodeHead != NULL)
			m_pNodeHead->pPrev = NULL;
		else
			m_pNodeTail = NULL;

		pOldNode->pNext = m_pNodeFree;
		m_pNodeFree = pOldNode;
		m_nCount--;
	}
	ENABLE_IRQS();
	ASSERT(m_nCount == 0);  
}

template<class TYPE, class ARG_TYPE, UINT SIZE>
void CListR0<TYPE, ARG_TYPE, SIZE>::RemoveAllCritical()
{
	while (m_pNodeHead)
	{
		CNode* pOldNode = m_pNodeHead;
		m_pNodeHead = pOldNode->pNext;
		if (m_pNodeHead != NULL)
			m_pNodeHead->pPrev = NULL;
		else
			m_pNodeTail = NULL;

		pOldNode->pNext = m_pNodeFree;
		m_pNodeFree = pOldNode;
		m_nCount--;
	}
	ASSERT(m_nCount == 0);  
}

template<class TYPE, class ARG_TYPE, UINT SIZE>
POSITION CListR0<TYPE, ARG_TYPE, SIZE>::InsertBefore(POSITION position, ARG_TYPE newElement)
{
	if (position == NULL)
		return AddHead(newElement); // insert before nothing -> head of the list

	if ( !m_pNodeFree )
		return NULL;

	DISABLE_IRQS();

	// Insert it before position
	CNode* pOldNode = (CNode*) position;
	CNode* pNewNode = m_pNodeFree;
	m_pNodeFree = m_pNodeFree->pNext;
	pNewNode->pPrev = pOldNode->pPrev;
	pNewNode->pNext = pOldNode;
	m_nCount++;

	pNewNode->data = newElement;
	
	if (pOldNode->pPrev != NULL)
	{
		pOldNode->pPrev->pNext = pNewNode;
	}
	else
	{
		ASSERT(pOldNode == m_pNodeHead);
		m_pNodeHead = pNewNode;
	}
	pOldNode->pPrev = pNewNode;
	
	ENABLE_IRQS();

	return (POSITION) pNewNode;
}

template<class TYPE, class ARG_TYPE, UINT SIZE>
POSITION CListR0<TYPE, ARG_TYPE, SIZE>::InsertBeforeCritical(POSITION position, ARG_TYPE newElement)
{
	if (position == NULL)
		return AddHead(newElement); // insert before nothing -> head of the list

	if ( !m_pNodeFree )
		return NULL;

	// Insert it before position
	CNode* pOldNode = (CNode*) position;
	CNode* pNewNode = m_pNodeFree;
	m_pNodeFree = m_pNodeFree->pNext;
	pNewNode->pPrev = pOldNode->pPrev;
	pNewNode->pNext = pOldNode;
	m_nCount++;

	pNewNode->data = newElement;
	
	if (pOldNode->pPrev != NULL)
	{
		pOldNode->pPrev->pNext = pNewNode;
	}
	else
	{
		ASSERT(pOldNode == m_pNodeHead);
		m_pNodeHead = pNewNode;
	}
	pOldNode->pPrev = pNewNode;
	
	return (POSITION) pNewNode;
}

template<class TYPE, class ARG_TYPE, UINT SIZE>
POSITION CListR0<TYPE, ARG_TYPE, SIZE>::InsertAfter(POSITION position, ARG_TYPE newElement)
{
	if (position == NULL)
		return AddTail(newElement); // insert after nothing -> tail of the list

	if ( !m_pNodeFree )
		return NULL;

	DISABLE_IRQS();

	// Insert it before position
	CNode* pOldNode = (CNode*) position;
	CNode* pNewNode = m_pNodeFree;
	m_pNodeFree = m_pNodeFree->pNext;
	pNewNode->pPrev = pOldNode;
	pNewNode->pNext = pOldNode->pNext;
	m_nCount++;

	pNewNode->data = newElement;
	
	if (pOldNode->pNext != NULL)
	{
		pOldNode->pNext->pPrev = pNewNode;
	}
	else
	{
		ASSERT(pOldNode == m_pNodeTail);
		m_pNodeTail = pNewNode;
	}
	pOldNode->pNext = pNewNode;
	
	ENABLE_IRQS();

	return (POSITION) pNewNode;
}

template<class TYPE, class ARG_TYPE, UINT SIZE>
POSITION CListR0<TYPE, ARG_TYPE, SIZE>::InsertAfterCritical(POSITION position, ARG_TYPE newElement)
{
	if (position == NULL)
		return AddTail(newElement); // insert after nothing -> tail of the list

	if ( !m_pNodeFree )
		return NULL;

	// Insert it before position
	CNode* pOldNode = (CNode*) position;
	CNode* pNewNode = m_pNodeFree;
	m_pNodeFree = m_pNodeFree->pNext;
	pNewNode->pPrev = pOldNode;
	pNewNode->pNext = pOldNode->pNext;
	m_nCount++;

	pNewNode->data = newElement;
	
	if (pOldNode->pNext != NULL)
	{
		pOldNode->pNext->pPrev = pNewNode;
	}
	else
	{
		ASSERT(pOldNode == m_pNodeTail);
		m_pNodeTail = pNewNode;
	}
	pOldNode->pNext = pNewNode;
	
	return (POSITION) pNewNode;
}

template<class TYPE, class ARG_TYPE, UINT SIZE>
void CListR0<TYPE, ARG_TYPE, SIZE>::RemoveAt(POSITION position)
{
	DISABLE_IRQS();

	CNode* pOldNode = (CNode*) position;

	// remove pOldNode from list
	if (pOldNode == m_pNodeHead)
	{
		m_pNodeHead = pOldNode->pNext;
	}
	else
	{
		pOldNode->pPrev->pNext = pOldNode->pNext;
	}
	if (pOldNode == m_pNodeTail)
	{
		m_pNodeTail = pOldNode->pPrev;
	}
	else
	{
		pOldNode->pNext->pPrev = pOldNode->pPrev;
	}
	
	pOldNode->pNext = m_pNodeFree;
	m_pNodeFree = pOldNode;
	m_nCount--;

	ENABLE_IRQS();

	ASSERT(m_nCount >= 0);  // make sure we don't underflow
}

template<class TYPE, class ARG_TYPE, UINT SIZE>
void CListR0<TYPE, ARG_TYPE, SIZE>::RemoveAtCritical(POSITION position)
{
	CNode* pOldNode = (CNode*) position;

	// remove pOldNode from list
	if (pOldNode == m_pNodeHead)
	{
		m_pNodeHead = pOldNode->pNext;
	}
	else
	{
		pOldNode->pPrev->pNext = pOldNode->pNext;
	}
	if (pOldNode == m_pNodeTail)
	{
		m_pNodeTail = pOldNode->pPrev;
	}
	else
	{
		pOldNode->pNext->pPrev = pOldNode->pPrev;
	}
	
	pOldNode->pNext = m_pNodeFree;
	m_pNodeFree = pOldNode;
	m_nCount--;

	ASSERT(m_nCount >= 0);  // make sure we don't underflow
}

template<class TYPE, class ARG_TYPE, UINT SIZE>
POSITION CListR0<TYPE, ARG_TYPE, SIZE>::FindIndex(int nIndex) const
{
	if (nIndex < 0 || static_cast<UINT>(nIndex) >= m_nCount )
		return NULL;  // went too far

	CNode* pNode = m_pNodeHead;
	while (nIndex--)
	{
		pNode = pNode->pNext;
	}
	return (POSITION) pNode;
}

template<class TYPE, class ARG_TYPE, UINT SIZE>
POSITION CListR0<TYPE, ARG_TYPE, SIZE>::Find(ARG_TYPE searchValue, POSITION startAfter) const
{
	CNode* pNode = NULL;
	if ( startAfter )
		pNode = (CNode*)startAfter;
	else
		pNode = m_pNodeHead;

	while ( pNode && pNode->data != searchValue )
		pNode = pNode->pNext;

	return (POSITION)pNode;
}

/////////////////////////////////////////////////////////////////////////////
// CListR0Dyn<TYPE, ARG_TYPE>

template<class TYPE, class ARG_TYPE>
class DLL_EXPORT CListR0Dyn
{
protected:
	struct CNode
	{
		CNode* pNext;
		CNode* pPrev;
		TYPE data;
	};
public:
// Construction
	CListR0Dyn(UINT size);

// Attributes (head and tail)
	// count of elements
	UINT GetCount() const;
	UINT GetFreeCount() const;
	BOOL IsEmpty() const;

	// peek at head or tail
	TYPE& GetHead();
	TYPE GetHead() const;
	TYPE& GetTail();
	TYPE GetTail() const;

// Operations
	// get head or tail (and remove it) - don't call on empty list !
	TYPE RemoveHead();
	TYPE RemoveHeadCritical();
	TYPE RemoveTail();
	TYPE RemoveTailCritical();
	void RemoveAll();
	void RemoveAllCritical();

	// add before head or after tail
	POSITION AddHead(ARG_TYPE newElement);
	POSITION AddHeadCritical(ARG_TYPE newElement);
	POSITION AddTail(ARG_TYPE newElement);
	POSITION AddTailCritical(ARG_TYPE newElement);

	// iteration
	POSITION GetHeadPosition() const;
	POSITION GetTailPosition() const;
	TYPE& GetNext(POSITION& rPosition); // return *Position++
	TYPE GetNext(POSITION& rPosition) const; // return *Position++
	TYPE& GetPrev(POSITION& rPosition); // return *Position--
	TYPE GetPrev(POSITION& rPosition) const; // return *Position--

	// getting/modifying an element at a given position
	TYPE& GetAt(POSITION position);
	TYPE GetAt(POSITION position) const;
	void SetAt(POSITION pos, ARG_TYPE newElement);
	void RemoveAt(POSITION position);
	void RemoveAtCritical(POSITION position);

	// inserting before or after a given position
	POSITION InsertBefore(POSITION position, ARG_TYPE newElement);
	POSITION InsertBeforeCritical(POSITION position, ARG_TYPE newElement);
	POSITION InsertAfter(POSITION position, ARG_TYPE newElement);
	POSITION InsertAfterCritical(POSITION position, ARG_TYPE newElement);

	// helper functions (note: O(n) speed)
	POSITION Find(ARG_TYPE searchValue, POSITION startAfter = NULL) const;
		// defaults to starting at the HEAD, return NULL if not found
	POSITION FindIndex(int nIndex) const;
		// get the 'nIndex'th element (may return NULL)

// Implementation
protected:
	CNode*	m_pNodeHead;
	CNode*	m_pNodeTail;
	CNode*	m_pNodeFree;
	UINT		m_nCount;
	UINT		m_nSize;
	CNode*	m_arrNodeFree;

	DECLARE_CRITSEC
public:
	~CListR0Dyn();
//	void Serialize(CArchive&);
};


template<class TYPE, class ARG_TYPE>
inline UINT CListR0Dyn<TYPE, ARG_TYPE>::GetCount() const
	{ return m_nCount; }
template<class TYPE, class ARG_TYPE>
inline UINT CListR0Dyn<TYPE, ARG_TYPE>::GetFreeCount() const
	{ return m_nSize-m_nCount; }
template<class TYPE, class ARG_TYPE>
BOOL CListR0Dyn<TYPE, ARG_TYPE>::IsEmpty() const
	{ return m_nCount == 0; }
template<class TYPE, class ARG_TYPE>
TYPE& CListR0Dyn<TYPE, ARG_TYPE>::GetHead()
	{ ASSERT(m_pNodeHead != NULL);
		return m_pNodeHead->data; }
template<class TYPE, class ARG_TYPE>
TYPE CListR0Dyn<TYPE, ARG_TYPE>::GetHead() const
	{ ASSERT(m_pNodeHead != NULL);
		return m_pNodeHead->data; }
template<class TYPE, class ARG_TYPE>
TYPE& CListR0Dyn<TYPE, ARG_TYPE>::GetTail()
	{ ASSERT(m_pNodeTail != NULL);
		return m_pNodeTail->data; }
template<class TYPE, class ARG_TYPE>
TYPE CListR0Dyn<TYPE, ARG_TYPE>::GetTail() const
	{ ASSERT(m_pNodeTail != NULL);
		return m_pNodeTail->data; }
template<class TYPE, class ARG_TYPE>
POSITION CListR0Dyn<TYPE, ARG_TYPE>::GetHeadPosition() const
	{ return (POSITION) m_pNodeHead; }
template<class TYPE, class ARG_TYPE>
POSITION CListR0Dyn<TYPE, ARG_TYPE>::GetTailPosition() const
	{ return (POSITION) m_pNodeTail; }
template<class TYPE, class ARG_TYPE>
TYPE& CListR0Dyn<TYPE, ARG_TYPE>::GetNext(POSITION& rPosition) // return *Position++
	{ CNode* pNode = (CNode*) rPosition;
		rPosition = (POSITION) pNode->pNext;
		return pNode->data; }
template<class TYPE, class ARG_TYPE>
TYPE CListR0Dyn<TYPE, ARG_TYPE>::GetNext(POSITION& rPosition) const // return *Position++
	{ CNode* pNode = (CNode*) rPosition;
		rPosition = (POSITION) pNode->pNext;
		return pNode->data; }
template<class TYPE, class ARG_TYPE>
TYPE& CListR0Dyn<TYPE, ARG_TYPE>::GetPrev(POSITION& rPosition) // return *Position--
	{ CNode* pNode = (CNode*) rPosition;
		rPosition = (POSITION) pNode->pPrev;
		return pNode->data; }
template<class TYPE, class ARG_TYPE>
TYPE CListR0Dyn<TYPE, ARG_TYPE>::GetPrev(POSITION& rPosition) const // return *Position--
	{ CNode* pNode = (CNode*) rPosition;
		rPosition = (POSITION) pNode->pPrev;
		return pNode->data; }
template<class TYPE, class ARG_TYPE>
TYPE& CListR0Dyn<TYPE, ARG_TYPE>::GetAt(POSITION position)
	{ CNode* pNode = (CNode*) position;
		return pNode->data; }
template<class TYPE, class ARG_TYPE>
TYPE CListR0Dyn<TYPE, ARG_TYPE>::GetAt(POSITION position) const
	{ CNode* pNode = (CNode*) position;
		return pNode->data; }
template<class TYPE, class ARG_TYPE>
void CListR0Dyn<TYPE, ARG_TYPE>::SetAt(POSITION pos, ARG_TYPE newElement)
	{ CNode* pNode = (CNode*) pos;
		pNode->data = newElement; }

template<class TYPE, class ARG_TYPE>
CListR0Dyn<TYPE, ARG_TYPE>::CListR0Dyn(UINT size)
{
	m_nSize = size;
	m_arrNodeFree = new CNode[m_nSize];
	ASSERT(m_arrNodeFree);
	memset( m_arrNodeFree, 0, sizeof(CNode) * m_nSize );

	for ( UINT i=1; i < m_nSize; i++ )
	{
		m_arrNodeFree[i].pPrev = &m_arrNodeFree[i-1];
		m_arrNodeFree[i-1].pNext = &m_arrNodeFree[i];
	}

	m_pNodeFree = m_arrNodeFree;
	m_pNodeHead	= NULL;
	m_pNodeTail	= NULL;

	m_nCount		= 0;

	INIT_CRITSEC
}

template<class TYPE, class ARG_TYPE>
CListR0Dyn<TYPE, ARG_TYPE>::~CListR0Dyn()
{
	DELETE_CRITSEC
	delete [] m_arrNodeFree;
}

template<class TYPE, class ARG_TYPE>
POSITION CListR0Dyn<TYPE, ARG_TYPE>::AddHead(ARG_TYPE newElement)
{
	if ( !m_pNodeFree )
		return NULL;

	CNode* pNewNode = m_pNodeFree;
	m_pNodeFree = m_pNodeFree->pNext;
	pNewNode->pPrev = NULL;
	pNewNode->pNext = m_pNodeHead;
	m_nCount++;

	pNewNode->data = newElement;

	DISABLE_IRQS();

	if (m_pNodeHead != NULL)
		m_pNodeHead->pPrev = pNewNode;
	else
		m_pNodeTail = pNewNode;
	m_pNodeHead = pNewNode;

	ENABLE_IRQS();

	return (POSITION) pNewNode;
}

template<class TYPE, class ARG_TYPE>
POSITION CListR0Dyn<TYPE, ARG_TYPE>::AddHeadCritical(ARG_TYPE newElement)
{
	if ( !m_pNodeFree )
		return NULL;

	CNode* pNewNode = m_pNodeFree;
	m_pNodeFree = m_pNodeFree->pNext;
	pNewNode->pPrev = NULL;
	pNewNode->pNext = m_pNodeHead;
	m_nCount++;

	pNewNode->data = newElement;

	if (m_pNodeHead != NULL)
		m_pNodeHead->pPrev = pNewNode;
	else
		m_pNodeTail = pNewNode;
	m_pNodeHead = pNewNode;

	return (POSITION) pNewNode;
}

template<class TYPE, class ARG_TYPE>
POSITION CListR0Dyn<TYPE, ARG_TYPE>::AddTail(ARG_TYPE newElement)
{
	if ( !m_pNodeFree )
		return NULL;

	DISABLE_IRQS();

	CNode* pNewNode = m_pNodeFree;
	m_pNodeFree = m_pNodeFree->pNext;
	pNewNode->pPrev = m_pNodeTail;
	pNewNode->pNext = NULL;
	m_nCount++;

	pNewNode->data = newElement;

	if (m_pNodeTail != NULL)
		m_pNodeTail->pNext = pNewNode;
	else
		m_pNodeHead = pNewNode;
	m_pNodeTail = pNewNode;

	ENABLE_IRQS();

	return (POSITION) pNewNode;
}

template<class TYPE, class ARG_TYPE>
POSITION CListR0Dyn<TYPE, ARG_TYPE>::AddTailCritical(ARG_TYPE newElement)
{
	if ( !m_pNodeFree )
		return NULL;

	CNode* pNewNode = m_pNodeFree;
	m_pNodeFree = m_pNodeFree->pNext;
	pNewNode->pPrev = m_pNodeTail;
	pNewNode->pNext = NULL;
	m_nCount++;

	pNewNode->data = newElement;

	if (m_pNodeTail != NULL)
		m_pNodeTail->pNext = pNewNode;
	else
		m_pNodeHead = pNewNode;
	m_pNodeTail = pNewNode;

	return (POSITION) pNewNode;
}

template<class TYPE, class ARG_TYPE>
TYPE CListR0Dyn<TYPE, ARG_TYPE>::RemoveHead()
{
	ASSERT(m_pNodeHead != NULL);  // don't call on empty list !!!

	DISABLE_IRQS();

	CNode* pOldNode = m_pNodeHead;
	TYPE returnValue = pOldNode->data;

	m_pNodeHead = pOldNode->pNext;
	if (m_pNodeHead != NULL)
		m_pNodeHead->pPrev = NULL;
	else
		m_pNodeTail = NULL;

	pOldNode->pNext = m_pNodeFree;
	m_pNodeFree = pOldNode;
	m_nCount--;

	ENABLE_IRQS();

	ASSERT(m_nCount >= 0);  // make sure we don't underflow

	return returnValue;
}

template<class TYPE, class ARG_TYPE>
TYPE CListR0Dyn<TYPE, ARG_TYPE>::RemoveHeadCritical()
{
	ASSERT(m_pNodeHead != NULL);  // don't call on empty list !!!

	CNode* pOldNode = m_pNodeHead;
	TYPE returnValue = pOldNode->data;

	m_pNodeHead = pOldNode->pNext;
	if (m_pNodeHead != NULL)
		m_pNodeHead->pPrev = NULL;
	else
		m_pNodeTail = NULL;

	pOldNode->pNext = m_pNodeFree;
	m_pNodeFree = pOldNode;
	m_nCount--;

	ASSERT(m_nCount >= 0);  // make sure we don't underflow

	return returnValue;
}

template<class TYPE, class ARG_TYPE>
TYPE CListR0Dyn<TYPE, ARG_TYPE>::RemoveTail()
{
	ASSERT(m_pNodeHead != NULL);  // don't call on empty list !!!

	DISABLE_IRQS();

	CNode* pOldNode = m_pNodeTail;
	TYPE returnValue = pOldNode->data;

	m_pNodeTail = pOldNode->pPrev;
	if (m_pNodeTail != NULL)
		m_pNodeTail->pNext = NULL;
	else
		m_pNodeHead = NULL;

	pOldNode->pNext = m_pNodeFree;
	m_pNodeFree = pOldNode;
	m_nCount--;

	ENABLE_IRQS();

	ASSERT(m_nCount >= 0);  // make sure we don't underflow

	return returnValue;
}

template<class TYPE, class ARG_TYPE>
TYPE CListR0Dyn<TYPE, ARG_TYPE>::RemoveTailCritical()
{
	ASSERT(m_pNodeHead != NULL);  // don't call on empty list !!!

	CNode* pOldNode = m_pNodeTail;
	TYPE returnValue = pOldNode->data;

	m_pNodeTail = pOldNode->pPrev;
	if (m_pNodeTail != NULL)
		m_pNodeTail->pNext = NULL;
	else
		m_pNodeHead = NULL;

	pOldNode->pNext = m_pNodeFree;
	m_pNodeFree = pOldNode;
	m_nCount--;

	ASSERT(m_nCount >= 0);  // make sure we don't underflow

	return returnValue;
}

template<class TYPE, class ARG_TYPE>
void CListR0Dyn<TYPE, ARG_TYPE>::RemoveAll()
{
	DISABLE_IRQS();
	while (m_pNodeHead)
	{
		CNode* pOldNode = m_pNodeHead;
		m_pNodeHead = pOldNode->pNext;
		if (m_pNodeHead != NULL)
			m_pNodeHead->pPrev = NULL;
		else
			m_pNodeTail = NULL;

		pOldNode->pNext = m_pNodeFree;
		m_pNodeFree = pOldNode;
		m_nCount--;
	}
	ENABLE_IRQS();
	ASSERT(m_nCount == 0);  
}

template<class TYPE, class ARG_TYPE>
void CListR0Dyn<TYPE, ARG_TYPE>::RemoveAllCritical()
{
	while (m_pNodeHead)
	{
		CNode* pOldNode = m_pNodeHead;
		m_pNodeHead = pOldNode->pNext;
		if (m_pNodeHead != NULL)
			m_pNodeHead->pPrev = NULL;
		else
			m_pNodeTail = NULL;

		pOldNode->pNext = m_pNodeFree;
		m_pNodeFree = pOldNode;
		m_nCount--;
	}
	ASSERT(m_nCount == 0);  
}

template<class TYPE, class ARG_TYPE>
POSITION CListR0Dyn<TYPE, ARG_TYPE>::InsertBefore(POSITION position, ARG_TYPE newElement)
{
	if (position == NULL)
		return AddHead(newElement); // insert before nothing -> head of the list

	if ( !m_pNodeFree )
		return NULL;

	DISABLE_IRQS();

	// Insert it before position
	CNode* pOldNode = (CNode*) position;
	CNode* pNewNode = m_pNodeFree;
	m_pNodeFree = m_pNodeFree->pNext;
	pNewNode->pPrev = pOldNode->pPrev;
	pNewNode->pNext = pOldNode;
	m_nCount++;

	pNewNode->data = newElement;
	
	if (pOldNode->pPrev != NULL)
	{
		pOldNode->pPrev->pNext = pNewNode;
	}
	else
	{
		ASSERT(pOldNode == m_pNodeHead);
		m_pNodeHead = pNewNode;
	}
	pOldNode->pPrev = pNewNode;
	
	ENABLE_IRQS();

	return (POSITION) pNewNode;
}

template<class TYPE, class ARG_TYPE>
POSITION CListR0Dyn<TYPE, ARG_TYPE>::InsertBeforeCritical(POSITION position, ARG_TYPE newElement)
{
	if (position == NULL)
		return AddHead(newElement); // insert before nothing -> head of the list

	if ( !m_pNodeFree )
		return NULL;

	// Insert it before position
	CNode* pOldNode = (CNode*) position;
	CNode* pNewNode = m_pNodeFree;
	m_pNodeFree = m_pNodeFree->pNext;
	pNewNode->pPrev = pOldNode->pPrev;
	pNewNode->pNext = pOldNode;
	m_nCount++;

	pNewNode->data = newElement;
	
	if (pOldNode->pPrev != NULL)
	{
		pOldNode->pPrev->pNext = pNewNode;
	}
	else
	{
		ASSERT(pOldNode == m_pNodeHead);
		m_pNodeHead = pNewNode;
	}
	pOldNode->pPrev = pNewNode;
	
	return (POSITION) pNewNode;
}

template<class TYPE, class ARG_TYPE>
POSITION CListR0Dyn<TYPE, ARG_TYPE>::InsertAfter(POSITION position, ARG_TYPE newElement)
{
	if (position == NULL)
		return AddTail(newElement); // insert after nothing -> tail of the list

	if ( !m_pNodeFree )
		return NULL;

	DISABLE_IRQS();

	// Insert it before position
	CNode* pOldNode = (CNode*) position;
	CNode* pNewNode = m_pNodeFree;
	m_pNodeFree = m_pNodeFree->pNext;
	pNewNode->pPrev = pOldNode;
	pNewNode->pNext = pOldNode->pNext;
	m_nCount++;

	pNewNode->data = newElement;
	
	if (pOldNode->pNext != NULL)
	{
		pOldNode->pNext->pPrev = pNewNode;
	}
	else
	{
		ASSERT(pOldNode == m_pNodeTail);
		m_pNodeTail = pNewNode;
	}
	pOldNode->pNext = pNewNode;
	
	ENABLE_IRQS();

	return (POSITION) pNewNode;
}

template<class TYPE, class ARG_TYPE>
POSITION CListR0Dyn<TYPE, ARG_TYPE>::InsertAfterCritical(POSITION position, ARG_TYPE newElement)
{
	if (position == NULL)
		return AddTail(newElement); // insert after nothing -> tail of the list

	if ( !m_pNodeFree )
		return NULL;

	// Insert it before position
	CNode* pOldNode = (CNode*) position;
	CNode* pNewNode = m_pNodeFree;
	m_pNodeFree = m_pNodeFree->pNext;
	pNewNode->pPrev = pOldNode;
	pNewNode->pNext = pOldNode->pNext;
	m_nCount++;

	pNewNode->data = newElement;
	
	if (pOldNode->pNext != NULL)
	{
		pOldNode->pNext->pPrev = pNewNode;
	}
	else
	{
		ASSERT(pOldNode == m_pNodeTail);
		m_pNodeTail = pNewNode;
	}
	pOldNode->pNext = pNewNode;
	
	return (POSITION) pNewNode;
}

template<class TYPE, class ARG_TYPE>
void CListR0Dyn<TYPE, ARG_TYPE>::RemoveAt(POSITION position)
{
	DISABLE_IRQS();

	CNode* pOldNode = (CNode*) position;

	// remove pOldNode from list
	if (pOldNode == m_pNodeHead)
	{
		m_pNodeHead = pOldNode->pNext;
	}
	else
	{
		pOldNode->pPrev->pNext = pOldNode->pNext;
	}
	if (pOldNode == m_pNodeTail)
	{
		m_pNodeTail = pOldNode->pPrev;
	}
	else
	{
		pOldNode->pNext->pPrev = pOldNode->pPrev;
	}
	
	pOldNode->pNext = m_pNodeFree;
	m_pNodeFree = pOldNode;
	m_nCount--;

	ENABLE_IRQS();

	ASSERT(m_nCount >= 0);  // make sure we don't underflow
}

template<class TYPE, class ARG_TYPE>
void CListR0Dyn<TYPE, ARG_TYPE>::RemoveAtCritical(POSITION position)
{
	CNode* pOldNode = (CNode*) position;

	// remove pOldNode from list
	if (pOldNode == m_pNodeHead)
	{
		m_pNodeHead = pOldNode->pNext;
	}
	else
	{
		pOldNode->pPrev->pNext = pOldNode->pNext;
	}
	if (pOldNode == m_pNodeTail)
	{
		m_pNodeTail = pOldNode->pPrev;
	}
	else
	{
		pOldNode->pNext->pPrev = pOldNode->pPrev;
	}
	
	pOldNode->pNext = m_pNodeFree;
	m_pNodeFree = pOldNode;
	m_nCount--;

	ASSERT(m_nCount >= 0);  // make sure we don't underflow
}

template<class TYPE, class ARG_TYPE>
POSITION CListR0Dyn<TYPE, ARG_TYPE>::FindIndex(int nIndex) const
{
	if (nIndex < 0 || static_cast<UINT>(nIndex) >= m_nCount )
		return NULL;  // went too far

	CNode* pNode = m_pNodeHead;
	while (nIndex--)
	{
		pNode = pNode->pNext;
	}
	return (POSITION) pNode;
}

template<class TYPE, class ARG_TYPE>
POSITION CListR0Dyn<TYPE, ARG_TYPE>::Find(ARG_TYPE searchValue, POSITION startAfter) const
{
	CNode* pNode = NULL;
	if ( startAfter )
		pNode = (CNode*)startAfter;
	else
		pNode = m_pNodeHead;

	while ( pNode && pNode->data != searchValue )
		pNode = pNode->pNext;

	return (POSITION)pNode;
}

