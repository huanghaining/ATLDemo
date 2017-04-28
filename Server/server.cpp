
#include <Windows.h>
#include <ComCat.h>
#include <InitGuid.h>
#include "math.h"
//#include "Imath.h"

HINSTANCE g_hinstDLL = 0;

 long g_IObjs = 0;
 long g_ILocks = 0;

 STDAPI DllGetClassObject(__in REFCLSID rclsid, __in REFIID riid, LPVOID FAR* ppv)
 {
	 HRESULT			hr;
	 MathClassFactory	*pCF;

	 if (rclsid != CLSID_Math)
	 {
		 return (E_FAIL);
	 }

	 pCF = new MathClassFactory;
	 if (pCF == 0)
	 {
		 return (E_OUTOFMEMORY);
	 }

	 hr = pCF->QueryInterface(riid,ppv);
	 if (FAILED(hr))
	 {
		 delete pCF;
	 }

	 return hr;
 }

 STDAPI DllCanUnloadNow(void)
 {
	 if (g_IObjs || g_ILocks)
	 {
		 return (S_FALSE);
	 }
	 else
	 {
		 return (S_OK);
	 }	
 }


BOOL WINAPI DllMain(_In_ HANDLE _HDllHandle, _In_ DWORD _Reason, _In_opt_ LPVOID _Reserved)
{
	if (_Reason == DLL_PROCESS_ATTACH)
	{
		g_hinstDLL = _HDllHandle;
	}
	return TRUE;
}

static BOOL SetRegKeyValue(LPTSTR pszKey,LPTSTR pszSubKey,LPTSTR pszValue)
{
	BOOL bOk = FALSE;
	LONG ec;
	HKEY hKey;
	TCHAR szKey[120];

	lstrcpy(szKey,pszKey);
	if (NULL != pszSubKey)
	{
		lstrcat(szKey,"\\");
		lstrcat(szKey,pszSubKey);
	}

	ec = RegCreateKeyEx(HKEY_CLASSES_ROOT,szKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,NULL);
	if (ERROR_SUCCESS == ec)
	{
		if (NULL != pszValue)
		{
			ec = RegSetValueEx(hKey,NULL,0,REG_SZ,(BYTE*)pszValue,(lstrlen(pszValue)+1) * sizeof(TCHAR));
		}

		if (ERROR_SUCCESS == ec)
		{
			bOk = TRUE;
		}
		RegCloseKey(hKey);
	}
	return bOk;
}


STDAPI DllRegisterServer(void)
{
	HRESULT hr = NOERROR;
	CHAR	szModulePath[MAX_PATH];
	CHAR	szID[128];
	CHAR	szCLSID[128];

	WCHAR	wszID[128];
	WCHAR	wszCLSID[128];

	GetModuleFileName(g_hinstDLL,szModulePath,sizeof(szModulePath)/sizeof(CHAR));
	StringFromCLSID(CLSID_Math,wszID,sizeof(wszID));
	wcscpy(wszCLSID,L"CLSID\\");
	wcscat(wszCLSID,wszID);
	wcstombs(szID,wszID,sizeof(szID));
	wcstombs(szCLSID,wszCLSID,sizeof(szID));

	SetRegKeyValue("Chapter2.Math.1",NULL,"Chapter Math,Component");
	SetRegKeyValue("Chapter2.Math.1","CLSID",szID);
	SetRegKeyValue("Chapter2.Math",NULL,"Chapter2 Math,Component");
	SetRegKeyValue("Chapter2.Math","CurVer","Chapter2.Math.1");
	SetRegKeyValue("Chapter2.Math","CLSID",szID);
}
