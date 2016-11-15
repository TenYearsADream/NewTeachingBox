﻿#include "stdafx.h"
#include "DialogNewVariate.h"
#include "TeachingBoxContext.h"
#include "QRect"
#include "QBoxLayout"
#include "Button.h"
#include "TVariateType.h"
#include "QTreeWidget"
#include "LineEditWithRegExpAndKeyboard.h"
#include "RegExp.h"
#include "WarningManager.h"
#include "VariateTableManager.h"
#include "IEditVariate.h"
#include "VariateDatabase.h"
#include "TVariateManager.h"

namespace VariateWidget{

	DialogNewVariate::DialogNewVariate(const QString& scope, IEditVariate* iEditVariate, QWidget* parent)
		:DialogParent(parent)
		, m_scope(scope)
		, m_iEditVariate(iEditVariate)
		, m_variateTableManager(new VariateTableManager(this))
	{
		Init();
	}

	DialogNewVariate::~DialogNewVariate()
	{

	}

	void DialogNewVariate::SlotOnConfrimButtonClicked()
	{
		if (!m_variateTableManager->IsValidVariate())
		{
			WarningManager::Warning(this, tr("Wrong Variate"));
			return;
		}

		auto variate = m_variateTableManager->GetVariate();
		if (variate==nullptr)
		{
			return;
		}
		m_iEditVariate->OnNewVariate(*variate);
		TVariateManager::GetInstance()->AddVariate(*variate);

		Destroy();
	}

	void DialogNewVariate::SlotOnCancleButtonClicked()
	{
		Destroy();
	}

	void DialogNewVariate::SlotOnTypeChanged(QTreeWidgetItem* item)
	{

		/*若当前节点无效或为顶部节点*/
		if (item == nullptr || item->parent() == nullptr)
		{
			return;
		}

		UpdateVariateWidget(item->text(0));
	}

	void DialogNewVariate::UpdateVariateWidget(const QString& currentType)
	{
		m_variateTableManager->ChangeToType(currentType);
	}

	void DialogNewVariate::UpdateText()
	{
		m_treeWidget->setHeaderLabel(tr("Type"));
		m_variateTableManager->UpdateText();

		m_btnConfrim->setText(tr("Confirm"));
		m_btnCancle->setText(tr("Cancle"));
	}

	void DialogNewVariate::Destroy()
	{
		delete this;
	}

	QLayout* DialogNewVariate::GetButtonLayout()
	{
		m_btnConfrim = new Button(this);
		m_btnCancle = new Button(this);

		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->addStretch(0);
		layout->addWidget(m_btnConfrim);
		layout->addStretch(0);
		layout->addWidget(m_btnCancle);
		layout->addStretch(0);

		return layout;
	}

	QLayout* DialogNewVariate::GetVariateLayout()
	{
		QHBoxLayout* layout = new QHBoxLayout(this);

		layout->addWidget(GetVariateTypeWidget());
		layout->addWidget(GetVariateSettingWidget());

		layout->setStretch(0, 1);
		layout->setStretch(1, 2);

		return layout;
	}

	QWidget* DialogNewVariate::GetVariateTypeWidget()
	{
		/*添加基本类型*/
		QTreeWidgetItem* itemBase = new QTreeWidgetItem(QStringList{ TVariateType::STR_CATEGORY_BASE });
		QStringList strListBase;

		itemBase->addChild(new QTreeWidgetItem(QStringList{ TVariateType::STR_TYPE_INT }));
		itemBase->addChild(new QTreeWidgetItem(QStringList{ TVariateType::STR_TYPE_DOUBLE }));
		itemBase->addChild(new QTreeWidgetItem(QStringList{ TVariateType::STR_TYPE_BOOL }));
		itemBase->addChild(new QTreeWidgetItem(QStringList{ TVariateType::STR_TYPE_STRING }));

		/*添加位置类型*/
		QTreeWidgetItem* itemPosition = new QTreeWidgetItem(QStringList{ TVariateType::STR_TYPE_POSITION });
		itemPosition->addChild(new QTreeWidgetItem(QStringList{ TVariateType::STR_TYPE_POSITION }));

		/*添加动态类型*/
		QTreeWidgetItem* itemDynamic = new QTreeWidgetItem(QStringList{ TVariateType::STR_TYPE_DYNAMIC });
		itemDynamic->addChild(new QTreeWidgetItem(QStringList{ TVariateType::STR_TYPE_DYNAMIC }));

		/*添加过渡类型*/
		QTreeWidgetItem* itemOverlap = new QTreeWidgetItem(QStringList{ TVariateType::STR_TYPE_OVERLAP });
		itemOverlap->addChild(new QTreeWidgetItem(QStringList{ TVariateType::STR_TYPE_OVERLAP }));

		/*添加坐标系类型*/
		QTreeWidgetItem* itemRefSys = new QTreeWidgetItem(QStringList{ TVariateType::STR_TYPE_REF_SYS });
		itemRefSys->addChild(new QTreeWidgetItem(QStringList{ TVariateType::STR_TYPE_REF_SYS }));

		m_treeWidget = new QTreeWidget(this);

		m_treeWidget->addTopLevelItem(itemBase);
		m_treeWidget->addTopLevelItem(itemPosition);
		m_treeWidget->addTopLevelItem(itemDynamic);
		m_treeWidget->addTopLevelItem(itemOverlap);
		m_treeWidget->addTopLevelItem(itemRefSys);

		return m_treeWidget;
	}

	QWidget* DialogNewVariate::GetVariateSettingWidget()
	{
		return m_variateTableManager->GetTableWidget(m_scope);
	}

	void DialogNewVariate::Init()
	{
		setWindowTitle(tr("New Variate"));

		InitLayout();
		InitSignalSlot();

		UpdateText();
	}

	void DialogNewVariate::InitLayout()
	{
		QVBoxLayout* layout = new QVBoxLayout(this);
		layout->setMargin(0);

		//layout->addWidget(GetTitleWidget());
		layout->addLayout(GetVariateLayout());
		layout->addLayout(GetButtonLayout());

		layout->setStretch(0, 1);
	}

	QWidget* DialogNewVariate::GetTitleWidget()
	{
		QLabel* titleWidget = new QLabel(tr("New Variate"), this);
		titleWidget->setStyleSheet("background:white;");
		QFont font;
		font.setPointSize(16);
		titleWidget->setFont(font);
		titleWidget->setMargin(0);

		return titleWidget;
	}

	void DialogNewVariate::InitSignalSlot()
	{
		connect(m_btnConfrim, SIGNAL(clicked()), this, SLOT(SlotOnConfrimButtonClicked()));
		connect(m_btnCancle, SIGNAL(clicked()), this, SLOT(SlotOnCancleButtonClicked()));

		connect(m_treeWidget, SIGNAL(itemPressed(QTreeWidgetItem*, int)), this, SLOT(SlotOnTypeChanged(QTreeWidgetItem*)));
	}


}