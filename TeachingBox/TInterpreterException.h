﻿#ifndef _TEACHING_BOX_T_INTERPRETER_EXCEPTION_H_
#define _TEACHING_BOX_T_INTERPRETER_EXCEPTION_H_

#include "QMap"
#include "Exception.h"

class TInterpreterException:public Exception
{
public:
	enum InterpreterExceptionCode
	{
		FOR_SENTENCE_SHOULD_END_WITH_NEXT,
		FOR_SENTENCE_SHOULD_USE_INTERGER_OR_DOUBLE,
		IF_SENTENCE_SHOULD_END_WITH_ENDIF,
		IF_SENTENCE_SHOULD_WITH_BOOL,
		LOSE_COMMA,
		MOVL_SHOULD_WITH_POSITOIN_DYNAMIC_OVERLAP,
		NOT_FIND_RIGHT_BRACKET,
		NOT_MOVL_SENTENCE,
		NEGATION_SHOULD_WITH_BOOL,
		NEGATIVE_SHOULD_WITH_INT_OR_DOUBLE,
		NOT_FIND_VARIATE,
		ONLY_NUMBER_COULD_TAKE_ARITHMETICAL_OPERATION,
		ONLY_NUMBER_COULD_TAKE_RELATIONAL_OPERATION,
		ONLY_BOOL_COULD_TAKE_LOGICAL_OPERATION,
		ONLY_INTERGER_COULD_TAKE_MOD_OPERATION,
		SENTENCE_NOT_END_WITH_ABNORMAL_END,
		SENTENCE_SHOULD_END_WITH_LINE_BREAK,
		TYPE_NOT_MATCH,
		UNKNOWN_TOKEN,
		UNKNOWN_VARIATE,
		WRONG_GRAMMAR,
		NOT_PROGRAM_NAME,
		UNKNOWN_SENTENCE,
	};

private:
	static const QMap<int, QString> Exception_TEXT;

public:
	TInterpreterException(const InterpreterExceptionCode id,const int lineNumber,const QString& text="");

	virtual QString Info() override;

	int LineNumber() const;

private:
	QString Format(const QString& text, int size);

private:
	InterpreterExceptionCode m_id;
	int m_lineNumber;
	QString m_text;
};

#endif