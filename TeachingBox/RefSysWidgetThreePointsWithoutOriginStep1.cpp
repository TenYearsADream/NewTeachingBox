﻿#include "stdafx.h"
#include "RefSysWidgetThreePointsWithoutOriginStep1.h"
#include "Button.h"
#include "CoordinateSystemTeachInfo.h"


RefSysWidgetThreePointsWithoutOriginStep1::RefSysWidgetThreePointsWithoutOriginStep1(QStackedWidget* parent)
	:SystemDialogWidgetParent(parent)
{

}

QWidget* RefSysWidgetThreePointsWithoutOriginStep1::MainWidget()
{
	QGroupBox* groupBox = new QGroupBox(tr("First point on axis"), this);

	QVBoxLayout* layout = new QVBoxLayout(groupBox);

	auto btnX = new QRadioButton("X", this);
	auto btnY = new QRadioButton("Y", this);
	auto btnZ = new QRadioButton("Z", this);
	m_btnGroup = new QButtonGroup(this);
	m_btnGroup->addButton(btnX, CoordinateSystemTeachInfo::X);
	m_btnGroup->addButton(btnY, CoordinateSystemTeachInfo::Y);
	m_btnGroup->addButton(btnZ, CoordinateSystemTeachInfo::Z);

	connect(m_btnGroup, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), [this](int id){
		if (IsTeached())
		{
			m_coorInfo->UpdateOrientation(static_cast<CoordinateSystemTeachInfo::Orientation>(id));
		}
	});

	btnX->setChecked(true);
	QHBoxLayout* radioLayout = new QHBoxLayout(this);
	radioLayout->addWidget(btnX);
	radioLayout->addWidget(btnY);
	radioLayout->addWidget(btnZ);

	layout->addLayout(radioLayout);
	layout->addWidget(PointWidgetXYZ());

	auto teachButton = new Button(tr("Teach"), this);
	connect(teachButton, &Button::clicked, [this]{
		GetRemotePose();
	});

	layout->addWidget(teachButton);

	layout->setStretch(1, 1);

	return groupBox;
}

QString RefSysWidgetThreePointsWithoutOriginStep1::IllustrationPixmapPath()
{
	return ":/new/image/Resources/Image/ref_sys_3_points_without_origin_step1.png";
}

void RefSysWidgetThreePointsWithoutOriginStep1::OnReseivePose(const tPoseEuler& pose/* = */)
{
	SystemDialogWidgetParent::OnReseivePose(pose);

	if (IsTeached())
	{
		m_coorInfo->UpdatePoseEuler(pose);
	}
	else
	{
		m_coorInfo->AddCoorSysInfo({ static_cast<CoordinateSystemTeachInfo::Orientation>(m_btnGroup->checkedId()), std::make_shared<tPoseEuler>(pose) });
	}

	UpdateButtonState();
}
