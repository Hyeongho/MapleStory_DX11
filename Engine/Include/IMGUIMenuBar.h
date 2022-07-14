#pragma once

#include "IMGUIWidget.h"

struct MenuItem
{
	std::string Label;
	std::string Shortcut;
};

struct MenuItemUTF8
{
	char Label[1024] = {};
	char Shortcut[1024] = {};
};

class CIMGUIMenuBar :
    public CIMGUIWidget
{
    friend class CIMGUIWindow;
	friend class CIMGUIModal;

protected:
    CIMGUIMenuBar();
    virtual ~CIMGUIMenuBar();

protected:
    std::vector<MenuItem> m_vecItem;
    std::vector<MenuItemUTF8> m_vecItemUTF8;
    bool m_Select;
    int m_SelectIndex;
    int m_PageItemCount;
    bool m_Sort;
    std::function<void(int, std::string)> m_SelectCallback;

public:
	MenuItem GetItem(int Index)
	{
		return m_vecItem[Index];
	}

	MenuItem GetSelectItem() const
	{
		return m_vecItem[m_SelectIndex];
	}

	int GetSelectIndex() const
	{
		return m_SelectIndex;
	}

	int GetItemCount() const
	{
		return (int)m_vecItem.size();
	}

	bool CheckItem(const char* Item)
	{
		size_t Size = m_vecItem.size();

		for (size_t i = 0; i < Size; ++i)
		{
			if (m_vecItem[i].Label == Item)
			{
				return true;
			}
		}

		return false;
	}

public:
	void AddItem(const std::string& Label, const std::string& Shortcut = "")
	{
		MenuItem Item;

		Item.Label = Label;
		Item.Shortcut = Shortcut;

		m_vecItem.push_back(Item);

		MenuItemUTF8 ItemUTF8;

		wchar_t	wILabel[1024] = {};

		int	Length = MultiByteToWideChar(CP_ACP, 0, Label.c_str(), -1, 0, 0);
		MultiByteToWideChar(CP_ACP, 0, Label.c_str(), -1, wILabel, Length);

		// UTF8로 변환한다.
		Length = WideCharToMultiByte(CP_UTF8, 0, wILabel, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_UTF8, 0, wILabel, -1, ItemUTF8.Label, Length, 0, 0);

		wchar_t wlShortcut[1024] = {};

		Length = MultiByteToWideChar(CP_ACP, 0, Shortcut.c_str(), -1, 0, 0);
		MultiByteToWideChar(CP_ACP, 0, Shortcut.c_str(), -1, wlShortcut, Length);

		// UTF8로 변환한다.
		Length = WideCharToMultiByte(CP_UTF8, 0, wlShortcut, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_UTF8, 0, wlShortcut, -1, ItemUTF8.Shortcut, Length, 0, 0);

		m_vecItemUTF8.push_back(ItemUTF8);

		/*if (m_Sort)
		{
			std::sort(m_vecItem.begin(), m_vecItem.end());
			std::sort(m_vecItemUTF8.begin(), m_vecItemUTF8.end());
		}*/
	}

	void SetPageItemCount(int Count)
	{
		m_PageItemCount = Count;
	}

	void DeleteItem(int Index)
	{
		auto iter = m_vecItem.begin() + Index;

		m_vecItem.erase(iter);

		auto iter1 = m_vecItemUTF8.begin() + Index;

		m_vecItemUTF8.erase(iter1);
	}

	void Clear()
	{
		m_vecItem.clear();
		m_vecItemUTF8.clear();
	}

	void Sort(bool bSort)
	{
		m_Sort = bSort;

		/*if (m_Sort)
		{
			std::sort(m_vecItem.begin(), m_vecItem.end());
			std::sort(m_vecItemUTF8.begin(), m_vecItemUTF8.end());
		}*/
	}

public:
    virtual bool Init();
    virtual void Render();

public:
	template <typename T>
	void SetSelectCallback(T* Obj, void(T::* Func)(int, std::string))
	{
		m_SelectCallback = std::bind(Func, Obj, std::placeholders::_1, std::placeholders::_2);
	}
};

