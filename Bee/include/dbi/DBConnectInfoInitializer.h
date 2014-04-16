/***************************************************************
 * DBConnectInfoInitializer.h
 * ϵͳ��  : ����һ��ͨϵͳ
 * ��ϵͳ��: ������ϵͳ(B)_ͨ�ÿ�
 * ��������      ����           ժҪ
 * ----------    -----------    --------------------------------
 * 2007/12/10    л��			���ο���
 ***************************************************************
 */
#ifndef DBCONNECTINFO_INITIALIZER_H_
#define DBCONNECTINFO_INITIALIZER_H_

#include "exceptions/BalException.h"
#include "dbi/DBConnectInfo.h"

/**
 * ��ȡ���ݿ�������Ϣ������
 * @author  л��
 * @version V2.0.00
 * @since V2.0.00
 */
class DBConnectInfoInitializer {
public:

	/**
	 * ��ʼ�����ݿ�������Ϣ
	 * @param	info ������������ݿ�������Ϣ
	 * @throws	BalException   �����쳣
	 */
	void initDBConnectInfo(DBConnectInfo& info) throw (BalException);

};

#endif /*DBCONNECTINFO_INITIALIZER_H_*/
