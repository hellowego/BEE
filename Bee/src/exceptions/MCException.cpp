/***************************************************************
 * MCException.cpp
 * ������  : ��������������
 * ��������: ����������(B)_������
 * ��������      ����           ����
 * ----------    -----------    --------------------------------
 * 2007/12/20    ����			��������
 ***************************************************************
 */
#include "Poco/Format.h"
#include "exceptions/MCException.h"


MCException::MCException(const string& msg, bool canContinue)
:BalException(msg), _canContinue(canContinue) {

}

MCException::MCException( const string& msg,const string& errorCode, bool canContinue )
:BalException(msg,errorCode), _canContinue(canContinue)
{

}

MCException::~MCException() throw(){

}

string MCException::toString() const
{
	string strContinue = _canContinue ? "true" : "false";
	return Poco::format("%s CONTINUE<%s>", BalException::toString(), strContinue);
}
