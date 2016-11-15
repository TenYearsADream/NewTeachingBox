﻿#ifndef _TEACHING_BOX_VARIATE_WIDGET_WIDGET_MANAGER_NEW_REF_SYS_H_
#define _TEACHING_BOX_VARIATE_WIDGET_WIDGET_MANAGER_NEW_REF_SYS_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    WidgetManagerNewRefSys.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/15
//  Description:		用于生成新建RefSys变量控件，并从该控件中获取变量值
	本类位于VariateWidget命名控件中，避免与其它Variate相关类命名冲突
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/11/15
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "WidgetManagerNewVariate.h"

namespace VariateWidget
{
	class WidgetManagerNewRefSys:public WidgetManagerNewVariate
	{
	public:
		WidgetManagerNewRefSys(QTableWidget* tableWidget, int startRowCount);
		~WidgetManagerNewRefSys();

		virtual std::unique_ptr<TVariate> GetVariate(const QString& name, const QString& scope) override;

		virtual void InitParameter() override;

		virtual void OnScopeChanged(const QString& scope) override;
	};
}

#endif