﻿#include "stdafx.h"
#include "TVariateManager.h"
#include "TVariate.h"
#include "TScope.h"
#include "QByteArray"
#include "VariateDatabase.h"
#include "TVariateFactory.h"
#include "Exception.h"
#include "ProjectContext.h"
#include "ProjectManager.h"
#include "TVariateContext.h"
#include "TimeCalculator.h"
#include "TeachingBoxBroadcast.h"

using namespace Database;

TVariateManager* TVariateManager::GetInstance()
{
	return SingleTon<TVariateManager>::GetInstance();
}

TVariateManager::TVariateManager()
	:m_scopeRoot(new TScope())
{
	LoadInitDataFromDatabase();
}

TVariateManager::~TVariateManager()
{
}

void TVariateManager::AddVariate(std::shared_ptr<TVariate> variate)
{
	AddInDatabase(variate);
	TVariateContext::GetInstance()->AddVariate(std::shared_ptr<TVariate>(variate));

	emit(TeachingBoxBroadcast::GetInstance()->AddVariate(variate));
}

void TVariateManager::DeleteVariate(const QString& scope, const QString& name)
{
	auto variate = GetVariate(scope, name);

	TVariateContext::GetInstance()->DeleteVariate(scope, name);
	VariateDatabase::DeleteScope(scope, name);

	emit(TeachingBoxBroadcast::GetInstance()->DeleteVariate(variate));
}

void TVariateManager::DeleteProjectVariates(const QStringList& names)
{
	for (auto name:names)
	{
		VariateDatabase::DeleteScope(name);
	}
	
	TVariateContext::GetInstance()->Clear();
	LoadInitDataFromDatabase();
}

void TVariateManager::DeleteProgramVariates(const QString& program)
{
	VariateDatabase::DeleteScope(program);

	TVariateContext::GetInstance()->Clear();
	LoadInitDataFromDatabase();
}

QVector<std::shared_ptr<TVariate>> TVariateManager::GetVariatesFromScope(const QString& scope)
{
	return TVariateContext::GetInstance()->GetVariates(scope);
}

QVector<std::shared_ptr<TVariate>> TVariateManager::GetAvailableVariatesScollUp(const QString& scope)
{
	return TVariateContext::GetInstance()->GetAvailableVariatesScollUp(scope);
}

QMap<QString, QVector<std::shared_ptr<TVariate>>> TVariateManager::GetAllVariatesMapScollUp(const QString& scope)
{
	return TVariateContext::GetInstance()->GetAllVariatesMapScollUp(scope);
}


QVector<std::shared_ptr<TVariate>> TVariateManager::GetAllVariates(const QString& typeName)
{
	return TVariateContext::GetInstance()->GetAllVariates(typeName);
}

std::shared_ptr<TVariate> TVariateManager::GetVariate(const QString& scope, const QString& name)
{
	return TVariateContext::GetInstance()->GetVariate(scope, name);
}

std::shared_ptr<TVariate> TVariateManager::GetVariateSrollUp(const QString& scope, const QString& name)
{
	return TVariateContext::GetInstance()->GetVariateScollUp(scope, name);
}

void TVariateManager::LoadInitDataFromDatabase()
{
	auto variates = VariateDatabase::SelectAllVariates();
	for (auto var : variates)
	{
		TVariateContext::GetInstance()->AddVariate(std::shared_ptr<TVariate>(TVariateFactory::GetVariate(var)));
	}
}


void TVariateManager::UpdateVariate(std::shared_ptr<TVariate> newVariate)
{
	UpdateInMapScollUp(newVariate);
	UpdateInDatabase(newVariate->GetScope(), newVariate->GetName(), newVariate);
}

void TVariateManager::AddInDatabase(std::shared_ptr<TVariate> variate)
{
	QByteArray data;
	QDataStream dataStream(&data, QIODevice::ReadWrite);
	variate->WriteDataToStream(dataStream);
	dataStream.device()->seek(0);
	VariateDatabase::InsertVariate(dataStream);
}

void TVariateManager::UpdateInMapScollUp(std::shared_ptr<TVariate> newVariate)
{
	TVariateContext::GetInstance()->UpdateVariate(newVariate);
}

void TVariateManager::UpdateInDatabase(const QString& scope, const QString& name, std::shared_ptr<TVariate> variate)
{
	QByteArray data;
	QDataStream dataStream(&data, QIODevice::ReadWrite);
	variate->WriteDataToStream(dataStream);

	VariateDatabase::UpdateVariate(scope, name, dataStream);
}

