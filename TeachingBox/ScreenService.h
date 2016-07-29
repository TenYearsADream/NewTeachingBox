﻿#ifndef _TEACHING_BOX_SCREEN_SERVICE_H_
#define _TEACHING_BOX_SCREEN_SERVICE_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ScreenService.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/07/29
//  Description:	用于显示用户、系统、网络等设置的界面
//  Others:
//  History:
//    <author>      刘巍 
//    <time>        2016/07/29
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "ScreenMainParent.h"

class QStackedWidget;
class Button;
class ScreenSetting;
class ScreenUser;
class ScreenUserManager;
class ScreenNetwork;

class ScreenService:public ScreenMainParent
{
	friend class ScreenFactory;

	Q_OBJECT

private:
	ScreenService(QWidget* parent);
	ScreenService(const ScreenService&);
	ScreenService& operator=(const ScreenService&);
	~ScreenService();
	
	void Init();
	void InitStackedWidget();
	void InitSignalSlot();

	virtual void UpdateText() override;

	virtual QList<QPushButton*> GetButtonList() override;

	virtual QLayout* GetMainLayout() override;

private slots:
	void SlotOnChangeToScreenSetting();
	void SlotOnChangeToScreenUser();
	void SlotOnChangeToScreenUserManager();
	void SlotOnChangeToScreenNetwork();

private:
	QStackedWidget* m_stackedWidget;
	ScreenSetting* m_screenSetting;
	ScreenUser* m_screenUser;
	ScreenUserManager* m_screenUserManager;
	ScreenNetwork* m_screenNetwork;

	Button* m_btnSetting;
	Button* m_btnUser;
	Button* m_btnUserManager;
	Button* m_btnVersion;
	Button* m_btnInformation;
	Button* m_btnNetwork;
};

#endif