#pragma once

#include "../GameInfo.h"
#include "../Ref.h"

class CData : 
	public CRef
{
public:
	CData();
	virtual ~CData();

public:
	libxl::Book* m_Excel;
	libxl::Sheet* m_Sheet;

public:
	void SetBook(libxl::Book* book)
	{
		m_Excel = book;
	}

	void SetSheet(libxl::Sheet* sheet)
	{
		m_Sheet = sheet;
	}

public:
	libxl::Book* GetBook() const
	{
		return m_Excel;
	}

	libxl::Sheet* GetSheet() const
	{
		return m_Sheet;
	}

public:
	void ReleaseBook()
	{
		if (m_Excel)
		{
			m_Excel->release();
		}
	}

	void ReadBook()
	{
		libxl::Sheet* sheet = m_Excel->getSheet(0);

		const TCHAR* a;

		if (sheet)
		{
			/*sheet->writeStr(2, 1, L"Hello, World !");
			sheet->writeNum(3, 1, 1000);

			a = sheet->readNum(3, 1);*/

			a = sheet->readStr(1, 0);
		}
	}

public:
	void LoadExcel(const std::string& Name, const TCHAR* FileName, const std::string& PathName = DATA_PATH);
	void SaveExcel(const std::string& Name, const TCHAR* FileName, const std::string& PathName = DATA_PATH);
	libxl::Book* MakeExcel(const std::string& Name);
};

