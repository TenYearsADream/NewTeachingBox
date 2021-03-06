﻿#include "stdafx.h"
#include "ButtonGroup.h"
#include "Button.h"
#include "TeachingBoxContext.h"


ButtonGroup::ButtonGroup(QList<QPushButton*>& btnlist, QPushButton* parentButton)
	:QWidget(parentButton)
	, m_btnList(btnlist)
	, m_parentButton(parentButton)
{
	Init();
}

ButtonGroup::~ButtonGroup()
{

}

void ButtonGroup::showEvent(QShowEvent *)
{
	if (m_btnList.size() > 0)
	{
		resize(m_parentButton->width(), m_parentButton->height()*m_btnList.size());
	}

	int positionLeft = m_parentButton->geometry().left() + TeachingBoxContext::GetInstance()->GetScreenRect().left();
	int positionBottom = TeachingBoxContext::GetInstance()->GetScreenRect().bottom();

	this->move(positionLeft, positionBottom - this->height()-m_parentButton->height());
}

void ButtonGroup::Init()
{
	this->setWindowFlags(Qt::Popup);
	m_layout = new QVBoxLayout(this);

	for (auto button : m_btnList)
	{
		m_layout->addWidget(button);
		connect(button, &QPushButton::clicked, [this]{
			this->hide();
		});
	}

	m_layout->setMargin(0);
	m_layout->setSpacing(0);
}

