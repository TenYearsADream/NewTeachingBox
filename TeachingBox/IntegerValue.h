﻿#ifndef _TEACHING_BOX_INTEGER_VALUE_H_
#define _TEACHING_BOX_INTEGER_VALUE_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    IntegerValue.h
//  Author:			刘巍
//  Version: 		1.0
//  Date: 			2016/12/13
//  Description:    保存整数值，并继承自VariateValue
//  Others:
//  Function List:
//  History:
//    <author>      刘巍
//    <time>        2016/12/13
//    <version>     1.0
//    <desc>        build this moudle
*************************************************/

#include "VariateValue.h"

class IntegerValue :public VariateValue
{
public:
	typedef int ValueType;

public:
	explicit IntegerValue(int value);
	operator int() const;

	virtual void WriteToDataStream(QDataStream& dataStream) const override;

	//virtual void WriteToTreeWidget(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, int row, int column) const override;

	virtual void ReadFromDataStream(QDataStream& dataStream) override;

	//virtual void ReadFromTreeWidget(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, int row, int column) override;

	//virtual void UpdateTreeWidget(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, int row, int column) const override;

private:
	int m_value = 0;
};


#endif // !_TEACHING_BOX_N_VARIATE_VALUE_INTEGER_VALUE_H_