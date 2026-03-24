module;
#include "StdAfx.h"

export module MText;

export namespace MText
{
	/**
	 * @brief 从标注文本中解析上下极限偏差
	 * @param dimText 标注文本
	 * @param tolUpper 传出上极限偏差
	 * @param tolLower 传出下极限偏差
	 */
	void parseDimensionTolerance(const AcString& dimText, double& tolUpper, double& tolLower);
}
