

/*
	Binary Search Tree

	Date:
		2001/01/09

	Note: 
		���� Ž�� Ʈ��

	Usage:
		����ϱ� �� �ݵ�� SetCompareFunction�� ���־�� �Ѵ�.
		��Ʈ������ Ű ���� ���� ��� SetCompareStringFunction�� ȣ���Ѵ�.
		�� ���� �� �ڿ� �޸𸮸� �����ϱ� ���ؼ� �ݵ�� ClearAll�� ȣ���ؾ� �Ѵ�. 
*/
#ifndef __ORZ_DATASTRUCTURE_BINARY_SEARCH_TREE__
#define __ORZ_DATASTRUCTURE_BINARY_SEARCH_TREE__


/*
	Tree ��� ����

	Note: class T�� �����͸� ����Ѵ�.
*/
template< class T >
class CBsTreeNode
{
public:
	T *m_pData;
	CBsTreeNode< T > *m_pParent, *m_pLeft, *m_pRight;
		
	CBsTreeNode();
	virtual ~CBsTreeNode();

	void ClearAll( bool bDeleteData, bool bDeleteArray );

	CBsTreeNode< T > * GetMaxKeyNode();
	CBsTreeNode< T > * GetMinKeyNode();

	void Preorder( void (*pfnCallback)( void *pArg, T *pData ), void *pArg );
	void Inorder( void (*pfnCallback)( void *pArg, T *pData ), void *pArg );
	void Postorder( void (*pfnCallback)( void *pArg, T *pData ), void *pArg );
};



/*
	Tree ��� ����
*/
template< class T >
CBsTreeNode< T >::CBsTreeNode()
: m_pData( NULL ), m_pParent( NULL ), m_pLeft( NULL ), m_pRight( NULL )
{
}


template< class T >
CBsTreeNode< T >::~CBsTreeNode()
{
}


template< class T >
void CBsTreeNode< T >::ClearAll( bool bDeleteData, bool bDeleteArray )
{
	if ( m_pLeft )
		m_pLeft->ClearAll( bDeleteData, bDeleteArray );

	if ( m_pRight )
		m_pRight->ClearAll( bDeleteData, bDeleteArray );

	if ( bDeleteData )
	{
		if ( bDeleteArray )
			delete[] m_pData;
		else 
			delete m_pData;
	}

	delete this;
}


template< class T >
CBsTreeNode< T > * CBsTreeNode< T >::GetMaxKeyNode()
{
	CBsTreeNode< T > *pTemp = this;

	while ( pTemp->m_pRight )
		pTemp = pTemp->m_pRight;
		
	return pTemp;
}


template< class T >
CBsTreeNode< T > * CBsTreeNode< T >::GetMinKeyNode()
{
	CBsTreeNode< T > *pTemp = this;

	while ( pTemp->m_pLeft )
		pTemp = pTemp->m_pLeft;
		
	return pTemp;
}


template< class T >
void CBsTreeNode< T >::Preorder( void (*pfnCallback)( void *pArg, T *pData ), void *pArg ) 
{
	pfnCallback( pArg, m_pData );

	if ( m_pLeft )
		m_pLeft->Preorder( pfnCallback, pArg );

	if ( m_pRight )
		m_pRight->Preorder( pfnCallback, pArg );
}


template< class T >
void CBsTreeNode< T >::Inorder( void (*pfnCallback)( void *pArg, T *pData ), void *pArg ) 
{
	if ( m_pLeft )
		m_pLeft->Inorder( pfnCallback, pArg );

	pfnCallback( pArg, m_pData );

	if ( m_pRight )
		m_pRight->Inorder( pfnCallback, pArg );
}


template< class T >
void CBsTreeNode< T >::Postorder( void (*pfnCallback)( void *pArg, T *pData ), void *pArg ) 
{
	if ( m_pRight )
		m_pRight->Postorder( pfnCallback, pArg );

	if ( m_pLeft )
		m_pLeft->Postorder( pfnCallback, pArg );

	pfnCallback( pArg, m_pData );
}



/*
	Binary Search Tree ����
*/
template< class T >
class CBsTree
{
protected:
	CBsTreeNode< T > *m_pRoot;

	// Key�� ���� �� ȣ��Ǵ� �Լ�
	int  (*m_pfnCmp)( void *pArg, T *pFirst, T *pSecond );
	void *m_pArgCmpFunc;

	// String�� Data�� ���� �� ȣ��Ǵ� �Լ�
	int  (*m_pfnCmpStr)( void *pArg, T *pData, char *pString );
	void *m_pArgCmpStrFunc;

	int  m_nCount;

public:
	CBsTree();
	virtual ~CBsTree();

	void ClearAll( bool bDeleteData = true, bool bDeleteArray = false );

	void SetCompareFunction( int (*pfnCmp)( void *pArg, T *pFirst, T *pSecond ), void *pArg );
	void SetCompareStringFunction( int (*pfnCmp)( void *pArg, T *pData, char *pString ), void *pArg );

	bool Insert( T *pData );
	T *  Remove( T *pKey );
	T *  Search( T *pKey );
	T *  SearchKeyString( char *pKey );
	CBsTreeNode< T > * SearchNode( T *pKey );

	void Preorder( void (*pfnCallback)( void *pArg, T *pData ), void *pArg );
	void Inorder( void (*pfnCallback)( void *pArg, T *pData ), void *pArg );
	void Postorder( void (*pfnCallback)( void *pArg, T *pData ), void *pArg );

	int  GetCount();
	bool IsEmpty();
};




/*
	Binary Search Tree ����
*/
template< class T >
CBsTree< T >::CBsTree()
{
	m_pRoot				= NULL;
	m_pfnCmp			= NULL;
	m_pArgCmpFunc		= NULL;
	m_pfnCmpStr			= NULL;
	m_pArgCmpStrFunc	= NULL;
	m_nCount			= 0;
}


template< class T >
CBsTree< T >::~CBsTree()
{
}


template< class T >
void CBsTree< T >::ClearAll( bool bDeleteData, bool bDeleteArray )
{
	if ( m_pRoot )
	{
		m_pRoot->ClearAll( bDeleteData, bDeleteArray );
		m_pRoot = NULL;
	}
}


template< class T >
void CBsTree< T >::SetCompareFunction( int (*pfnCmp)( void *pArg, T *pFirst, T *pSecond ), void *pArg )
{
	m_pfnCmp		= pfnCmp;
	m_pArgCmpFunc	= pArg;
}


template< class T >
void CBsTree< T >::SetCompareStringFunction( int (*pfnCmp)( void *pArg, T *pData, char *pString ), void *pArg )
{
	m_pfnCmpStr			= pfnCmp;
	m_pArgCmpStrFunc	= pArg;
}


template< class T >
bool CBsTree< T >::Insert( T *pData )
{
	int nCmpResult;
	CBsTreeNode< T > *pTemp = m_pRoot, *pTempParent = NULL;

	while ( pTemp )
	{
		pTempParent	= pTemp;
		nCmpResult	= m_pfnCmp( m_pArgCmpFunc, pTemp->m_pData, pData );

		// ���� Key��� 
		if ( nCmpResult == 0 )
			return false;

		if ( nCmpResult > 0 )
			pTemp = pTemp->m_pLeft;
		else
			pTemp = pTemp->m_pRight;
	}

	pTemp = new CBsTreeNode< T >;
	if ( pTemp == NULL )
		return false;

	pTemp->m_pData		= pData;
	pTemp->m_pParent	= pTempParent;

	if ( m_pRoot == NULL )
		m_pRoot = pTemp;
	else if ( m_pfnCmp( m_pArgCmpFunc, pTemp->m_pData, pTempParent->m_pData ) < 0 )
		pTempParent->m_pLeft = pTemp;
	else
		pTempParent->m_pRight = pTemp;
	
	++m_nCount;

	return true;
}


template< class T >
T * CBsTree< T >::Remove( T *pKey )
{
	if ( m_pRoot == NULL )
		return NULL;

	CBsTreeNode< T > *pTemp = SearchNode( pKey );
	if ( pTemp == NULL )
		return NULL;

	T *pData = pTemp->m_pData;

	// �ڽ��� ���°��
	if ( pTemp->m_pLeft == NULL && pTemp->m_pRight == NULL )
	{		
		if ( m_pRoot == pTemp )
		{
			m_pRoot = NULL;
		}
		else
		{
			if ( pTemp->m_pParent->m_pLeft == pTemp )
				pTemp->m_pParent->m_pLeft = NULL;
			else
				pTemp->m_pParent->m_pRight = NULL;
		}		
	}
	// �ڽ��� �ϳ� �ִ� ���
	else if ( (pTemp->m_pLeft && pTemp->m_pRight == NULL) ||
		      (pTemp->m_pLeft == NULL && pTemp->m_pRight) )
	{
		CBsTreeNode< T > *pChild = pTemp->m_pLeft ? pTemp->m_pLeft : pTemp->m_pRight;

		if ( m_pRoot == pTemp )
		{
			m_pRoot = pChild;
		}
		else
		{
			pChild->m_pParent = pTemp->m_pParent;
			
			if ( pTemp->m_pParent->m_pLeft == pTemp )
				pTemp->m_pParent->m_pLeft = pChild;
			else
				pTemp->m_pParent->m_pRight = pChild;
		}
	}
	// �ڽ��� ���� ��� ���� ���� Ʈ������ ���� ū ����� ������ ġȯ�Ѵ�.
	else
	{
		CBsTreeNode< T > *pMaxKeyNode = pTemp->m_pLeft->GetMaxKeyNode();
		pTemp->m_pData = pMaxKeyNode->m_pData;

		if ( pMaxKeyNode->m_pLeft )
		{
			pMaxKeyNode->m_pLeft->m_pParent = pMaxKeyNode->m_pParent;
			
			if ( pMaxKeyNode->m_pParent->m_pLeft == pMaxKeyNode )
				pMaxKeyNode->m_pParent->m_pLeft = pMaxKeyNode->m_pLeft;
			else
				pMaxKeyNode->m_pParent->m_pRight = pMaxKeyNode->m_pLeft;
		}
		else
		{
			if ( pMaxKeyNode->m_pParent->m_pLeft == pMaxKeyNode )
				pMaxKeyNode->m_pParent->m_pLeft = NULL;
			else
				pMaxKeyNode->m_pParent->m_pRight = NULL;
		}

		pTemp = pMaxKeyNode;
	}
	
	delete pTemp;

	--m_nCount;

	return pData;
}


template< class T >
T * CBsTree< T >::Search( T *pKey )
{
	int nCmpResult;
	CBsTreeNode< T > *pTemp = m_pRoot;

	while ( pTemp )
	{
		nCmpResult = m_pfnCmp( m_pArgCmpFunc, pTemp->m_pData, pKey );

		if ( nCmpResult == 0 )
			return pTemp->m_pData;

		if ( nCmpResult > 0 )
			pTemp = pTemp->m_pLeft;
		else
			pTemp = pTemp->m_pRight;
	}

	return NULL;
}


template< class T >
T * CBsTree< T >::SearchKeyString( char *pKey )
{
	int nCmpResult;
	CBsTreeNode< T > *pTemp = m_pRoot;

	while ( pTemp )
	{
		nCmpResult = m_pfnCmpStr( m_pArgCmpFunc, pTemp->m_pData, pKey );

		if ( nCmpResult == 0 )
			return pTemp->m_pData;

		if ( nCmpResult > 0 )
			pTemp = pTemp->m_pLeft;
		else
			pTemp = pTemp->m_pRight;
	}

	return NULL;
}


template< class T >
CBsTreeNode< T > * CBsTree< T >::SearchNode( T *pKey )
{
	int nCmpResult;
	CBsTreeNode< T > *pTemp = m_pRoot;

	while ( pTemp )
	{
		nCmpResult = m_pfnCmp( m_pArgCmpFunc, pTemp->m_pData, pKey );

		if ( nCmpResult == 0 )
			return pTemp;

		if ( nCmpResult > 0 )
			pTemp = pTemp->m_pLeft;
		else
			pTemp = pTemp->m_pRight;
	}

	return NULL;
}


template< class T >
void CBsTree< T >::Preorder( void (*pfnCallback)( void *pArg, T *pData ), void *pArg )
{
	if ( m_pRoot == NULL )
		return;

	m_pRoot->Preorder( pfnCallback, pArg );
}


template< class T >
void CBsTree< T >::Inorder( void (*pfnCallback)( void *pArg, T *pData ), void *pArg )
{
	if ( m_pRoot == NULL )
		return;

	m_pRoot->Inorder( pfnCallback, pArg );
}


template< class T >
void CBsTree< T >::Postorder( void (*pfnCallback)( void *pArg, T *pData ), void *pArg )
{
	if ( m_pRoot == NULL )
		return;

	m_pRoot->Postorder( pfnCallback, pArg );
}


template< class T >
int CBsTree< T >::GetCount()
{
	return m_nCount;
}


template< class T >
bool CBsTree< T >::IsEmpty()
{
	return m_nCount == 0;
}



#endif