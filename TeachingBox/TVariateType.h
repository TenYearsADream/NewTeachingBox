﻿#ifndef _TEACHING_BOX_T_VARIATE_TYPE_MANAGER_H_
#define _TEACHING_BOX_T_VARIATE_TYPE_MANAGER_H_

class TVariateType
{
public:
	TVariateType();
	~TVariateType();

	/*基本类型*/
	static const QString STR_CATEGORY_BASE;	/*基本类型*/

	static const QString STR_TYPE_INT;
	static const QString STR_TYPE_DOUBLE;
	static const QString STR_TYPE_STRING;
	static const QString STR_TYPE_BOOL;
	static const QString STR_TYPE_LABEL;

	/*位置类型*/
	static const QString STR_TYPE_POSITION;

	/*动态类型*/
	static const QString STR_TYPE_DYNAMIC;

	/*过渡类型*/
	static const QString STR_TYPE_OVERLAP;

	/*参考坐标系*/
	static const QString STR_TYPE_REF_SYS;

	/*布尔值*/
	static const QString STR_BOOL_TRUE;
	static const QString STR_BOOL_FALSE;

	/*过渡模式*/
	static const QString STR_TRANSITION_MODE_ABSOLUTE;
	static const QString STR_TRANSITION_MODE_RELATIVE;



	static const QStringList TYPE_COLLECTION;

private:

};

#endif