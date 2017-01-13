﻿#ifndef _TEACHING_BOX_SCREEN_HEAD_H_
#define _TEACHING_BOX_SCREEN_HEAD_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ScreenState.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/07/27
//  Description:	屏幕中状态栏部分，实时显示机器人当前状态
//  Others:
//  History:
//    <author>      刘巍 
//    <time>        2016/07/27
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "InternationalWidget.h"
#include "QLabel"
#include "LabelWithBorder.h"

class QLayout;

class ScreenState:public InternationalWidget
{
	class ComboBoxWithUniqueIcon;
	class WidgetWithIcon;

private:
	const QString PROJECT_ICON_PATH = ":/new/image/Resources/Image/project_icon.png";
	const QString PROGRAM_ICON_PATH = ":/new/image/Resources/Image/program_icon.png";

public:
	ScreenState(QWidget* parent=0);
	~ScreenState();

private:
	virtual void UpdateText() override;
	virtual void showEvent(QShowEvent *) override;

	void Init();
	void InitLayout();
	void InitSignalSlot();
	void InitState();

	void ChangeRunningMode(int id);
	void ChangeRunningState(int id);
	void ChangeServoState(bool isOn);

	QLayout* GetFirstLayout();
	QLayout* GetSecondLayout();

	void LoadProject(const QString& project, const QStringList& programs);
	void OpenProgram(const QString& project, const QString& program);

	void UpdatePixmap(LabelWithBorder* widget, const QString& pixmapPath, Qt::AspectRatioMode aspectRatioMode = Qt::IgnoreAspectRatio, Qt::TransformationMode transformMode = Qt::SmoothTransformation);

private:
	bool m_isFirstCreate = true;

	LabelWithBorder* m_lbLogo;			/*商标*/

	LabelWithBorder* m_lbServoState;			/*程序状态*/
	LabelWithBorder* m_lbExecuteMode;		/*同上*/
	LabelWithBorder* m_lbExecuteState;				/*用户自定义*/
	LabelWithBorder* m_lb4;				/*同上*/
	LabelWithBorder* m_lb5;				/*同上*/
	LabelWithBorder* m_lbSpace;			/*空间监控*/
	LabelWithBorder* m_lbSecurityState;	/*安全状态*/
	LabelWithBorder* m_lbUserAuthority;	/*用户权限*/
	LabelWithBorder* m_lbCurrentTime;	/*当前时间*/

	ComboBoxWithUniqueIcon* m_comboBoxCoordiante;	/*参考坐标系*/
	ComboBoxWithUniqueIcon* m_comboBoxTool;			/*工具手*/
	ComboBoxWithUniqueIcon* m_comboBoxSpeed;			/*工具手*/
	ComboBoxWithUniqueIcon* m_comboBoxProject;		/*当前打开的项目*/
	ComboBoxWithUniqueIcon* m_comboBoxProgram;		/*当前打开的程序*/

private:
	class ComboBoxWithUniqueIcon :public QComboBox
	{
	public:
		ComboBoxWithUniqueIcon(const QString& iconPath,QWidget* parent = 0);

		void AddIconItem(const QString& text);
		void AddIconItems(const QStringList& texts);

	private:
		QString m_iconPath;
	};

	class ComboBoxWithBorder :public LabelWithBorder
	{
	public:
		ComboBoxWithBorder(QComboBox* widget, QWidget* parent = 0);

		virtual void showEvent(QShowEvent *) override;

	protected:
		QHBoxLayout* m_layout;
		QComboBox* m_widget;
	};

	class WidgetWithIcon :public LabelWithBorder
	{
	public:
		WidgetWithIcon(QWidget* widget, const QString& iconPath, QWidget* parent = 0);

		virtual void showEvent(QShowEvent *) override;

	private:
		QString m_iconPath;
		QLabel* m_icon;
		QWidget* m_widget;
	};

};

#endif