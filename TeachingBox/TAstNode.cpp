﻿#include "stdafx.h"

#include "TLexer.h"
#include "TAstNode.h"
#include "TAstNodeFactory.h"
#include "TInterpreterException.h"
#include "TToken.h"
#include "TTokenWithValue.h"


TAstNode::TAstNode(const std::shared_ptr<TToken> token /*= nullptr*/)
	:m_token(token)
{

}

TAstNode::~TAstNode()
{

}

void TAstNode::AddChild(std::shared_ptr<TAstNode> child)
{
	child->m_parentNode = this;
	child->m_siblingNode = nullptr;

	if (!m_firstChild)
	{
		m_firstChild = child;
		m_endChild = child;
	}
	else
	{
		m_endChild->m_siblingNode = child;
		m_endChild = child;
	}
}


std::shared_ptr<TToken> TAstNode::GetToken() const
{
	return m_token;
}

std::shared_ptr<TAstNode> TAstNode::GetFirstChild() const
{
	return m_firstChild;
}

std::shared_ptr<TAstNode> TAstNode::GetEndChild() const
{
	return m_endChild;
}

std::shared_ptr<TAstNode> TAstNode::GetSibling() const
{
	return m_siblingNode;
}

TAstNode* TAstNode::GetParentNode() const
{
	return m_parentNode;
}

const TAstNode* TAstNode::GetProgramNode() const
{
	if (m_parentNode==nullptr)
	{
		return nullptr;
	}

	auto result = this;
	while (result->m_parentNode->m_parentNode!=nullptr)
	{
		result = result->m_parentNode;
	}

	return result;
}

TAstNode::ValueReturned TAstNode::Execute() const
{
	return ValueReturned{};
}

void TAstNode::AddSentenceNodes(TLexer* const lexer, std::shared_ptr<TAstNode> parentNode)
{
	std::shared_ptr<TAstNode> childNode{};
	while (childNode = TAstNodeFactory::GetNode(lexer))
	{
		parentNode->AddChild(childNode);
	}
}

void TAstNode::CheckLineBreak(TLexer* const lexer)
{
	if (lexer->GetToken()->Type() != TOKEN_TYPE::SEPARATOR_EOL)
	{
		throw TInterpreterException(TInterpreterException::SENTENCE_SHOULD_END_WITH_LINE_BREAK, lexer->GetToken()->LineNumber());
	}
}

void TAstNode::CheckEofEol(TLexer* const lexer)
{
	if (!IsEofOrEol(lexer->GetToken()->Type()))
	{
		throw TInterpreterException(TInterpreterException::SENTENCE_NOT_END_WITH_ABNORMAL_END, lexer->GetToken()->LineNumber());
	}

}

void TAstNode::CheckLeftBrace(TLexer* const lexer)
{
	if (lexer->GetToken()->Type() != TOKEN_TYPE::OPERATOR_LEFT_BRACE)
	{
		throw TInterpreterException(TInterpreterException::MISS_LEFT_BRACE, lexer->GetToken()->LineNumber());
	}
}

void TAstNode::CheckRightBrace(TLexer* const lexer)
{
	if (lexer->GetToken()->Type() != TOKEN_TYPE::OPERATOR_RIGHT_BRACE)
	{
		throw TInterpreterException(TInterpreterException::MISS_RIGHT_BRACE, lexer->GetToken()->LineNumber());
	}
}

QString TAstNode::GetScope() const
{
	if (m_parentNode == nullptr || m_parentNode->GetParentNode() == nullptr)
	{
		return QString{};
	}

	auto programNode = m_parentNode;
	while (programNode->GetParentNode()->GetParentNode() != nullptr)
	{
		programNode = programNode->GetParentNode();
	}

	return programNode->GetToken()->Name();
		//static_cast<TTokenWithValue<QString>*>(programNode->GetToken().get())->GetValue();
}

bool TAstNode::IsEofOrEol(const int type)
{
	if (type == TOKEN_TYPE::SEPARATOR_EOF || type == TOKEN_TYPE::SEPARATOR_EOL)
	{
		return true;
	}

	return false;
}

void TAstNode::SkipEol(TLexer* const lexer)
{
	while (lexer->PeekToken()->Type() == TOKEN_TYPE::SEPARATOR_EOL)
	{
		lexer->GetToken();
	}
}

TAstNode* TAstNode::FindNextValidNode() const
{
	if (m_siblingNode != nullptr)
	{
		/*若兄弟节点与当前节点在同一行，则继续寻找下一节点*/
		if (m_siblingNode->GetToken()->LineNumber() == m_token->LineNumber())
		{
			return m_siblingNode->FindNextValidNode();
		}

		return m_siblingNode.get();
	}

	if (m_parentNode != nullptr)
	{
		return m_parentNode->FindNextValidNode();
	}

	return nullptr;
}
