/***************************************************************
 * BalException.h
 * ������  : ��������������
 * ��������: ����������(B)_������
 * ��������      ����           ����
 * ----------    -----------    --------------------------------
 * 2007/12/10    ����			��������
 ***************************************************************
 */
#ifndef BALEXCEPTION_H_
#define BALEXCEPTION_H_

#include <string>
#include "Poco/Exception.h"

using std::string;
using Poco::Exception;

/**
 * ����������������������������������������������������������
 * @author  ����
 * @version V2.0.00
 * @since V2.0.00
 */
class BalException : public Exception {
public:

	/**
	 * ��������
	 * @param	��������������
	 */
	BalException(const string& msg);
	
	/**
	 * ��������
	 * @param	��������������
	 * @param	��������
	 */
	BalException(const string& msg, const string& errorCode );

	/**
	 * ��������
	 */
	virtual ~BalException() throw();
	
	/**
	 * ������������
	 * @return	
	 */
	string getErrorCode() {return _errorCode;}

	/**
	 * ������������
	 * @param ��������
	 */
	void setErrorCode(const string& errorCode) {_errorCode=errorCode;};

	/**
	 * ����������������
	 */
	virtual string toString() const;
	
protected:

	/**
	 * ��������
	 */
	string _errorCode;
};

#endif /*BALEXCEPTION_H_*/
