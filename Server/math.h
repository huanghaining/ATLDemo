#include "Imath.h"

extern long g_IObjs;
extern long g_ILocks;

class Math:public IMath,public IAdvancedMath
{
public:
	Math();
	~Math();

	STDMETHOD(QueryInterface(REFIID,void**));
	STDMETHOD_(ULONG,AddRef());
	STDMETHOD_(ULONG,Release());

	//IMath
	STDMETHOD(Add)(long,long,long*)			;
	STDMETHOD(Subtract)(long,long,long*)	;
	STDMETHOD(Multiply)(long,long,long*)	;
	STDMETHOD(Devide)(long,long,long*)		;

	//IAdvancedMath
	STDMETHOD(Factorial)(short,long*)		;
	STDMETHOD(Fibonacci)(short,long*)		;
protected:
	long	m_IRef;
private:
};

class MathClassFactory:public IClassFactory
{
public:
	MathClassFactory();
	~MathClassFactory();

	//IUnknow
	STDMETHOD(QueryInterface(REFIID,void**));
	STDMETHOD_(ULONG,AddRef());
	STDMETHOD_(ULONG,Release());

	//IClassFactory
	STDMETHOD(CreateInstance)(LPUNKNOWN,REFIID,void**);
	STDMETHOD(LockServer)(BOOL);
protected:
	long	m_IRef;
private:
};