﻿#include "stdafx.h"
#include "MacroWidgetFactory.h"
#include "Macro.h"
#include "QWidget"
#include "QString"
#include "MacroWidgetMovl.h"
#include "MacroWidgetMovc.h"
#include "MacroWidgetGosub.h"

QWidget* MacroWidgetFactory::CreateMacroWidget(const QString& macro, QWidget* parent /*= nullptr*/)
{
	auto stringList = macro.split(" ");

	if (stringList.size()==0)
	{
		return nullptr;
	}

	auto macroName = stringList.at(0);

	if (macroName==Macro::MACRO_MOVL)
	{
		return new MacroWidgetMovl(macro,parent);
	}
	else if (macroName==Macro::MACRO_MOVC)
	{
		return new MacroWidgetMovc(macro,parent);
	}
	else if (macroName==Macro::MACRO_GOSUB)
	{
		return new MacroWidgetGosub(macro, parent);
	}

	return nullptr;
}