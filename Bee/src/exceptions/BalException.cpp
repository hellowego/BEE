/***************************************************************
 * BalException.cpp
 * ������  : ��������������
 * ��������: ����������(B)_������
 * ��������      ����           ����
 * ----------    -----------    --------------------------------
 * 2007/12/20    ����			��������
 ***************************************************************
 */
#include "Poco/Format.h"
#include "exceptions/BalException.h"


BalException::BalException(const string& msg) :
Exception(msg), _errorCode("0000000000")
{

}

BalException::BalException(const string& msg, const string& errorCode) :
Exception(msg), _errorCode(errorCode) 
{

}

BalException::~BalException() throw()
{

}

string BalException::toString() const
{
	return Poco::format("CODE<%s> MSG<%s>", _errorCode, message());
}
