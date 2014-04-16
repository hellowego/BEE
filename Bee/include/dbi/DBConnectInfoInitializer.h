/***************************************************************
 * DBConnectInfoInitializer.h
 * 系统名  : 城市一卡通系统
 * 子系统名: 结算子系统(B)_通用库
 * 更改日期      姓名           摘要
 * ----------    -----------    --------------------------------
 * 2007/12/10    谢琨			初次开发
 ***************************************************************
 */
#ifndef DBCONNECTINFO_INITIALIZER_H_
#define DBCONNECTINFO_INITIALIZER_H_

#include "exceptions/BalException.h"
#include "dbi/DBConnectInfo.h"

/**
 * 获取数据库连接信息助手类
 * @author  谢琨
 * @version V2.0.00
 * @since V2.0.00
 */
class DBConnectInfoInitializer {
public:

	/**
	 * 初始化数据库连接信息
	 * @param	info 输出参数，数据库连接信息
	 * @throws	BalException   结算异常
	 */
	void initDBConnectInfo(DBConnectInfo& info) throw (BalException);

};

#endif /*DBCONNECTINFO_INITIALIZER_H_*/
