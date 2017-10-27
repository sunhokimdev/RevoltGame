#pragma once

#include <sstream>
#include <iostream>

// USES_CONVERSION 매크로
#include "atlconv.h"
#include "atlBase.h"
#pragma comment(lib, "atls.lib")
/*
ATL 3.0
USES_CONVERSION을 사용한 함수가 종료되면 메모리가 해제되므로 유의할것.

매크로	인자		결과
A2CW	(LPCSTR)	(LPCWSTR)
A2W		(LPCSTR)	(LPWSTR)	(string->wstring)
W2CA	(LPCWSTR)	(LPCSTR)
W2A		(LPCWSTR)	(LPSTR)		(wstring->string)

T2COLE	(LPCTSTR)	(LPCOLESTR)
T2OLE	(LPCTSTR)	(LPOLESTR)
OLE2CT	(LPCOLESTR)	(LPCTSTR)
OLE2T	(LPCOLESTR)	(LPCSTR)

예)
void Func()
{
USES_CONVERSION;

TCHAR widechar[]=L"sample";
char ansichar[10];
ansichar = W2A(widechar);
}

ATL 7.0 문자열 변환
CA2AEX		이 클래스를 사용 하 여 문자열 변환 매크로에서 CA2TEX 및 CT2AEX, 및 typedef CA2A.
CA2CAEX		이 클래스를 사용 하 여 문자열 변환 매크로에서 CA2CTEX 및 CT2CAEX, 및 typedef CA2CA.
CA2WEX		이 클래스를 사용 하 여 문자열 변환 매크로에서 CA2TEX, CA2CTEX, CT2WEX, 및 CT2CWEX, 및 typedef CA2W.
CW2AEX		이 클래스를 사용 하 여 문자열 변환 매크로에서 CT2AEX, CW2TEX, CW2CTEX, 및 CT2CAEX, 및 typedef CW2A.
CW2CWEX		이 클래스를 사용 하 여 문자열 변환 매크로에서 CW2CTEX 및 CT2CWEX, 및 typedef CW2CW.
CW2WEX		이 클래스를 사용 하 여 문자열 변환 매크로에서 CW2TEX 및 CT2WEX, 및 typedef CW2W.
(맨 뒤의 EX를 제외해서 사용 가능)

CComBSTR		에 대 한 래퍼 클래스인 BSTRs.
_U_STRINGorID	이 인수 어댑터 클래스 두 리소스 이름이 있습니다
				(LPCTSTRs) 또는 리소스 Id (UINTs) 호출자 ID를 사용 하여
				문자열에 변환할 필요 없이 함수에 전달 하는 MAKEINTRESOURCE 매크로.
*/

class cStringUtil
{
public:
	cStringUtil();
	~cStringUtil();

public:
	//문자->숫자
	static int ToInt(std::string text) { return atoi(text.c_str()); }
	static float ToFloat(std::string text) { return atof(text.c_str()); }
	static int ToInt(std::wstring text) { return _wtoi(text.c_str()); }
	static float ToFloat(std::wstring text) { return _wtof(text.c_str()); }

	//stringstream을 이용. 숫자->문자
	static std::string ToString(int value) { std::stringstream ss; ss << value; return ss.str(); }
	static std::string ToString(float value) { std::stringstream ss; ss << value; return ss.str(); }
	static std::string ToString(CHAR text) { std::stringstream ss; ss << text; return ss.str(); }

	static std::wstring ToWString(int value) { std::wstringstream ss; ss << value; return ss.str(); }
	static std::wstring ToWString(float value) { std::wstringstream ss; ss << value; return ss.str(); }
	static std::wstring ToWString(WCHAR text) { std::wstringstream ss; ss << text; return ss.str(); }

	//ATL 3.0 변환 매크로  USES_CONVERSION 사용 (간편 변환) (loop 금지)
	static std::string ToString_c(std::wstring text)
	{
		USES_CONVERSION; return W2A(text.c_str());
	}
	//ATL 3.0 변환 매크로  USES_CONVERSION 사용 (간편 변환) (loop 금지)
	static std::wstring ToWString_c(std::string text)
	{
		USES_CONVERSION; return A2W(text.c_str());
	}

	//ATL 7.0 변환 클래스
	static std::string ToString(std::wstring text)
	{
		return ATL::CW2A(text.c_str());
	}
	//ATL 7.0 변환 클래스
	static std::wstring ToWString(std::string text)
	{
		return ATL::CA2W(text.c_str());
	}
	//자세한 내용(ATL) : "https://technet.microsoft.com/ko-kr/library/87zae4a3(v=vs.110)"


	//std::vector<CHAR> 값에 포함된 문자들을 이용하여 string을 자릅니다.
	static void Split(std::vector<std::string>* datas, std::vector<CHAR>* cutChars, std::string* text)
	{
		datas->clear();
		int startIndex = 0;
		for (int i = 0; i < text->length(); i++)
		{
			for (int j = 0; j < cutChars->size(); j++)
			{
				if ((*text)[i] == (*cutChars)[j])
				{
					std::string pushData = text->substr(startIndex, i - startIndex);
					if (pushData.length ()> 0) datas->push_back(pushData);
					break;
				}
			}
		}
		datas->push_back(text->substr(startIndex, text->length() - startIndex));
	}
	static void Split(std::vector<std::string>* datas, CHAR* cutChar, std::string* text)
	{
		datas->clear();
		int startIndex = 0;
		for (int i = 0; i < text->length(); i++)
		{
			if ((*text)[i] == *cutChar)
			{
				std::string pushData = text->substr(startIndex, i - startIndex);
				if (pushData.length() > 0) datas->push_back(pushData);
				startIndex = i + 1;
			}
		}
		datas->push_back(text->substr(startIndex, text->length() - startIndex));
	}

private:
	void TestFunc()
	{

	}
};

