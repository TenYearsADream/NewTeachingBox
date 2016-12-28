﻿#ifndef _TEACHING_BOX_MACRO_MANAGER_H_
#define _TEACHING_BOX_MACRO_MANAGER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    MacroManager.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/12/28
//  Description:    宏命令管理器，用于提供宏命令信息
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2016/12/28
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include <set>

class MacroInfo;

class MacroManager
{
private:
	typedef std::map<QString, std::shared_ptr<MacroInfo>> MacroMap;
	typedef std::map<QString, std::set<QString>> TypeMap;

public:
	static MacroManager* GetInstance();

	std::shared_ptr<MacroMap> GetMacroMap();
	std::shared_ptr<TypeMap> GetCategoryTypeMap();
	std::shared_ptr<TypeMap> GetTypeMacroMap();

private:
	MacroManager();
	MacroManager(const MacroManager&) = delete;
	MacroManager& operator=(const MacroManager&) = delete;
	~MacroManager()=default;

	void InitMapFromXmlFile();
	
private:
	std::shared_ptr<MacroMap> m_macroMap;
	std::shared_ptr<TypeMap> m_categoryTypeMap;
	std::shared_ptr<TypeMap> m_typeMacroMap;

};

#endif