/***************************************************************
 * MCException.h
 * ������  : ��������������
 * ��������: ����������(B)_������
 * ��������      ����           ����
 * ----------    -----------    --------------------------------
 * 2007/12/10    ����			��������
 ***************************************************************
 */
#ifndef MCEXCEPTION_H_
#define MCEXCEPTION_H_

#include "exceptions/BalException.h"

/**
 * MC����
 * @author  ����
 * @version V2.0.00
 * @since V2.0.00
 */
class MCException : public BalException {
public:
	/**
	 * ��������
	 * @param	msg			��������������
	 * @param	canContinue	��������������������������������
	 */
	MCException(const string& msg,bool canContinue = false);

	/**
	* ��������
	* @param	msg			��������������
	* @param	errorCode	��������
	* @param	canContinue	��������������������������������
	*/
	MCException(const string& msg,const string& errorCode, bool canContinue = false);
	
	/**
	 * ��������
	 */
	virtual ~MCException() throw();

	/**
	 * ��������������������������������
	 */
	const bool canContinue() const {return _canContinue;}

	/**
	 * ����������������
	 */
	virtual string toString() const;

private:
	/**
	 * ������������������������������������������������������
	 */
	bool _canContinue;
	
};

#endif /*MCEXCEPTION_H_*/
