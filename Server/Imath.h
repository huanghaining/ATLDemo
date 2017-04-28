

// {74DF63C4-ADA5-46da-9AE8-DD29CA95C235}
DEFINE_GUID(CLSID_Math, 
			0x74df63c4, 0xada5, 0x46da, 0x9a, 0xe8, 0xdd, 0x29, 0xca, 0x95, 0xc2, 0x35);

// {5D5E05E7-4CC0-4539-9B4D-99B0286E5849}
DEFINE_GUID(IID_IMath, 
			0x5d5e05e7, 0x4cc0, 0x4539, 0x9b, 0x4d, 0x99, 0xb0, 0x28, 0x6e, 0x58, 0x49);

// {9A63E367-6800-4689-8067-B595940D2489}
DEFINE_GUID(IID_IAdvancedMath, 
			0x9a63e367, 0x6800, 0x4689, 0x80, 0x67, 0xb5, 0x95, 0x94, 0xd, 0x24, 0x89);


class IMath:public IUnknown
{
public:
	STDMETHOD(Add)(long,long,long*)			PURE;
	STDMETHOD(Subtract)(long,long,long*)	PURE;
	STDMETHOD(Multiply)(long,long,long*)	PURE;
	STDMETHOD(Devide)(long,long,long*)		PURE;
};

class IAdvancedMath:public IUnknown
{
public:
	STDMETHOD(Factorial)(short,long*)		PURE;
	STDMETHOD(Fibonacci)(short,long*)		PURE;
};

