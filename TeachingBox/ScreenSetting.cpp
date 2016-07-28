﻿#include "stdafx.h"
#include "ScreenSetting.h"
#include "QGridLayout"
#include "Button.h"



ScreenSetting::ScreenSetting(QWidget* parent)
	:ScreenMainParent(parent)
{
	Init();
}

ScreenSetting::~ScreenSetting()
{

}

void ScreenSetting::UpdateText()
{
	/*登录窗口*/
	m_groupboxLogin->setTitle(tr("Login"));
	m_lbUser->setText(QCoreApplication::translate("CScreenSetting", "User"));
	m_lbAuthority->setText(QCoreApplication::translate("CScreenSetting", "Level"));
	m_btnLogout->setText(QCoreApplication::translate("CScreenSetting", "Logout"));

	/*系统设置窗口*/
	m_groupboxSystemSettings->setTitle(QCoreApplication::translate("CScreenSetting", "System settings"));
	m_lbLanguage->setText(QCoreApplication::translate("CScreenSetting", "Language"));
	m_lbDate->setText(QCoreApplication::translate("CScreenSetting", "Date"));
	m_lbTime->setText(QCoreApplication::translate("CScreenSetting", "time"));
	m_cmbLanguage->setItemText(0, QCoreApplication::translate("CScreenSetting", "English"));
	m_cmbLanguage->setItemText(1, QCoreApplication::translate("CScreenSetting", "Chinese"));

	/*机器人控制权限窗口*/
	m_groupboxRobotControlAuthority->setTitle(QCoreApplication::translate("CScreenSetting", "Robot control authority"));
	m_lbControlAuthority->setText(QCoreApplication::translate("CScreenSetting", "Control authority"));
	m_lbDevice->setText(QCoreApplication::translate("CScreenSetting", "Device"));
	m_lbDeviceIp->setText(QCoreApplication::translate("CScreenSetting", "Device IP"));

	/*显示设置窗口*/
	m_groupboxDispaySettings->setTitle(QCoreApplication::translate("CScreenSetting", "Display setting"));
	m_lbLockScreen->setText(QCoreApplication::translate("CScreenSetting", "Displaylock"));
	m_btnLockScreen->setText(QCoreApplication::translate("CScreenSetting", "Lock"));


	/*更新日期时间*/
	QDateTime dateTime = QDateTime::currentDateTime();
	QString date = dateTime.toString("yyyy-MM-dd");
	QString time = dateTime.toString("hh:mm:ss");
	m_lbDateValue->setText(date);
	m_lbTimeValue->setText(time);
}

void ScreenSetting::Init()
{
	QGridLayout* layout = new QGridLayout(this);
	m_layoutMain->addLayout(layout);

	layout->addWidget(CreateBoxLogin(), 0, 0);
	layout->addWidget(CreateBoxSystemSettings(), 0, 1);
	layout->addWidget(CreateBoxRobotControlAuthority(), 1, 0);
	layout->addWidget(CreateBoxLockScreenSetting(), 1, 1);

	layout->setRowStretch(0, 1);
	layout->setRowStretch(1, 1);
	layout->setColumnStretch(0, 1);
	layout->setColumnStretch(1, 1);
	layout->setSpacing(5);
	layout->setMargin(5);

	QList<QPushButton*> btnList;
	btnList.append(new Button("test"));
	UpdateButtonList(btnList);

	UpdateText();

}

QGroupBox* ScreenSetting::CreateBoxLogin()
{
	m_groupboxLogin = new QGroupBox(this);

	/*布局*/
	QVBoxLayout* layoutLogin = new QVBoxLayout(m_groupboxLogin);
	QHBoxLayout* layoutUser = new QHBoxLayout;
	QHBoxLayout* layoutLevel = new QHBoxLayout;
	QHBoxLayout* layoutLogout = new QHBoxLayout;

	layoutLogin->addStretch(0);
	layoutLogin->addLayout(layoutUser);
	layoutLogin->addStretch(0);
	layoutLogin->addLayout(layoutLevel);
	layoutLogin->addStretch(0);
	layoutLogin->addLayout(layoutLogout);
	layoutLogin->addStretch(0);

	/*创建窗口控件*/
	m_lbUser = new QLabel(this);
	m_lbAuthority = new QLabel(this);
	m_lbAuthorityValue = new QLabel("1",this);
	m_cmbUser = new QComboBox(this);
	m_btnLogout = new Button(this);

	/*添加控件并布局*/
	layoutUser->addWidget(m_lbUser);
	layoutUser->addWidget(m_cmbUser);
	layoutUser->setStretch(0, 1);
	layoutUser->setStretch(1, 1);

	layoutLevel->addWidget(m_lbAuthority);
	layoutLevel->addWidget(m_lbAuthorityValue);
	layoutLevel->setStretch(0, 1);
	layoutLevel->setStretch(1, 1);

	layoutLogout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));
	layoutLogout->addWidget(m_btnLogout);
	layoutLogout->setStretch(0, 1);
	layoutLogout->setStretch(1, 1);

	/*设置控件样式*/
	m_lbAuthorityValue->setAlignment(Qt::AlignRight | Qt::AlignCenter);
	m_lbAuthorityValue->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);

	return m_groupboxLogin;
}

QGroupBox* ScreenSetting::CreateBoxSystemSettings()
{
	/*新窗口*/
	m_groupboxSystemSettings = new QGroupBox;

	/*布局*/
	QVBoxLayout* layoutSystemSettings = new QVBoxLayout(m_groupboxSystemSettings);
	QHBoxLayout* layoutLanguage = new QHBoxLayout;
	QHBoxLayout* layoutDate = new QHBoxLayout;
	QHBoxLayout* layoutTime = new QHBoxLayout;

	layoutSystemSettings->addStretch(0);
	layoutSystemSettings->addLayout(layoutLanguage);
	layoutSystemSettings->addStretch(0);
	layoutSystemSettings->addLayout(layoutDate);
	layoutSystemSettings->addStretch(0);
	layoutSystemSettings->addLayout(layoutTime);
	layoutSystemSettings->addStretch(0);

	/*创建窗口控件并布局*/
	m_lbLanguage = new QLabel;
	m_lbDate = new QLabel;
	m_lbTime = new QLabel;
	m_cmbLanguage = new QComboBox;
	m_lbDateValue = new QLabel;
	m_lbTimeValue = new QLabel;

	layoutLanguage->addWidget(m_lbLanguage);
	layoutLanguage->addWidget(m_cmbLanguage);
	layoutLanguage->setStretch(0, 1);
	layoutLanguage->setStretch(1, 1);

	layoutDate->addWidget(m_lbDate);
	layoutDate->addWidget(m_lbDateValue);
	layoutDate->setStretch(0, 1);
	layoutDate->setStretch(1, 1);

	layoutTime->addWidget(m_lbTime);
	layoutTime->addWidget(m_lbTimeValue);
	layoutTime->setStretch(0, 1);
	layoutTime->setStretch(1, 1);

	/*为控件添加内容*/
	m_cmbLanguage->addItem(tr("English"));
	m_cmbLanguage->addItem(tr( "Chinese"));

	/*设置控件样式*/
	m_lbDateValue->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);
	m_lbTimeValue->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);

	return m_groupboxSystemSettings;
}

QGroupBox* ScreenSetting::CreateBoxRobotControlAuthority()
{
	/*创建窗口*/
	m_groupboxRobotControlAuthority = new QGroupBox;

	/*布局*/
	QVBoxLayout* layoutRobotControlAuthority = new QVBoxLayout(m_groupboxRobotControlAuthority);
	QHBoxLayout* layoutControlAuthority = new QHBoxLayout;
	QHBoxLayout* layoutDevice = new QHBoxLayout;
	QHBoxLayout* layoutDeviceIp = new QHBoxLayout;

	layoutRobotControlAuthority->addStretch(0);
	layoutRobotControlAuthority->addLayout(layoutControlAuthority);
	layoutRobotControlAuthority->addStretch(0);
	layoutRobotControlAuthority->addLayout(layoutDevice);
	layoutRobotControlAuthority->addStretch(0);
	layoutRobotControlAuthority->addLayout(layoutDeviceIp);
	layoutRobotControlAuthority->addStretch(0);

	/*创建窗口控件并布局*/
	m_lbControlAuthority = new QLabel;
	m_checkboxControlAuthority = new QCheckBox;
	m_checkboxControlAuthority->setChecked(false);
	m_lbDevice = new QLabel;
	m_lbDeviceValue = new QLabel;
	m_lbDeviceIp = new QLabel;
	m_lbDeviceIpValue = new QLabel;

	layoutControlAuthority->addWidget(m_lbControlAuthority);
	layoutControlAuthority->addWidget(m_checkboxControlAuthority);
	layoutControlAuthority->setStretch(0, 1);
	layoutControlAuthority->setStretch(1, 1);
	layoutControlAuthority->setAlignment(m_checkboxControlAuthority, Qt::AlignRight);

	layoutDevice->addWidget(m_lbDevice);
	layoutDevice->addWidget(m_lbDeviceValue);
	layoutDevice->setStretch(0, 1);
	layoutDevice->setStretch(1, 1);

	layoutDeviceIp->addWidget(m_lbDeviceIp);
	layoutDeviceIp->addWidget(m_lbDeviceIpValue);
	layoutDeviceIp->setStretch(0, 1);
	layoutDeviceIp->setStretch(1, 1);

	/*设置控件样式*/
	m_lbDeviceValue->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);
	m_lbDeviceIpValue->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);

	return m_groupboxRobotControlAuthority;
}

QGroupBox* ScreenSetting::CreateBoxLockScreenSetting()
{
	/*创建窗口*/
	m_groupboxDispaySettings = new QGroupBox;

	/*布局*/
	QVBoxLayout* layoutDisplaySetting = new QVBoxLayout(m_groupboxDispaySettings);
	QHBoxLayout* layoutDisplayLock = new QHBoxLayout;

	layoutDisplaySetting->addStretch(1);
	layoutDisplaySetting->addLayout(layoutDisplayLock);
	layoutDisplaySetting->addStretch(1);

	/*创建窗口控件并布局*/
	m_lbLockScreen = new QLabel;
	m_btnLockScreen = new Button;

	layoutDisplayLock->addWidget(m_lbLockScreen);
	layoutDisplayLock->addWidget(m_btnLockScreen);
	layoutDisplayLock->setStretch(0, 1);
	layoutDisplayLock->setStretch(1, 1);

	return m_groupboxDispaySettings;
}


