
#include <Windows.h>
#include "math.h"



Math::Math()
{
	m_IRef = 0;
	InterlockedIncrement(&g_IObjs);
}

Math::~Math()
{
	InterlockedDecrement(&g_IObjs);
}


STDMETHODIMP Math::QueryInterface(REFIID riid,void** ppv)
{
	*ppv = 0;
	if (riid == IID_IUnknown)
	{
		*ppv = (IMath*)this;
	} 
	else if (riid == IID_IMath)
	{
		*ppv = (IMath*)this;
	} 
	else if (riid == IID_IAdvancedMath)
	{
		*ppv = (IAdvancedMath*)this;
	} 

	if (*ppv)
	{
		AddRef();
		return (S_OK);
	}
	return (E_NOINTERFACE);
}

STDMETHODIMP_(ULONG)Math::AddRef()
{
	return InterlockedIncrement(&m_IRef);
}

STDMETHODIMP_(ULONG)Math::Release()
{
	if (InterlockedDecrement(&m_IRef) == 0)
	{
		delete this;
		return 0;
	}
	return m_IRef;
}

STDMETHODIMP Math::Add(long lOp1,long lOp2,long * pResult)
{
	*pResult = lOp1 + lOp2;
	return S_OK;
}


STDMETHODIMP Math::Subtract(long lOp1,long lOp2,long * pResult)
{
	*pResult = lOp1 - lOp2;
	return S_OK;
}

STDMETHODIMP Math::Multiply(long lOp1,long lOp2,long * pResult)
{
	*pResult = lOp1 * lOp2;
	return S_OK;
}

STDMETHODIMP Math::Devide(long lOp1,long lOp2,long * pResult)
{
	*pResult = lOp1 / lOp2;
	return S_OK;
}


static long calcFactorial(short n)
{
	if (n <= 1)
	{
		return 1;
	}
	return n * calcFactorial(n - 1);
}

STDMETHODIMP Math::Factorial(short sOp,long *pResult)
{
	*pResult = calcFactorial(sOp);
	return S_OK;
}

STDMETHODIMP Math::Fibonacci(short sOp,long *pResult)
{
	*pResult = calcFactorial(sOp);
	return S_OK;
}

MathClassFactory::MathClassFactory()
{
	m_IRef = 0;
}

MathClassFactory::~MathClassFactory()
{

}

STDMETHODIMP MathClassFactory::QueryInterface(REFIID riid,void ** ppv)
{
	*ppv = 0;
	if (riid == IID_IUnknown || riid == IID_IClassFactory)
	{
		*ppv = this;
	}
	if (*ppv)
	{
		AddRef();
		return S_OK;
	}
	return (E_NOINTERFACE);
}

STDMETHODIMP_(ULONG)MathClassFactory::AddRef()
{
	return InterlockedIncrement(&m_IRef);
}

STDMETHODIMP_(ULONG)MathClassFactory::Release()
{
	if (InterlockedDecrement(&m_IRef) == 0)
	{
		delete this;
		return 0;
	}
	return m_IRef;
}

STDMETHODIMP MathClassFactory::CreateInstance(LPUNKNOWN pUnknow, REFIID riid,void **ppvObj)
{
	Math *pMath;
	HRESULT hr;
	*ppvObj = 0;
	pMath = new Math;
	if (pMath == 0)
	{
		return (E_NOINTERFACE);
	}

	hr = pMath->QueryInterface(riid,ppvObj);
	if (FAILED(hr))
	{
		delete pMath;
	}
	
	return hr;
}


STDMETHODIMP MathClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
	{
		InterlockedIncrement(&g_ILocks);
	} 
	else
	{
		InterlockedDecrement(&g_ILocks);
	}
	return S_OK;
}



