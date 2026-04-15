module;
#include "StdAfx.h"

export module TextUtil;
import UniversalPicker;

export namespace TextUtil
{
	// 文本类型列表
	UniversalPicker::AcRxClassVector textClassList =
	{
		AcDbMText::desc(),
		AcDbText::desc()
	};
};

export namespace TextUtil
{
	/**
	 * @brief 从标注文本中解析上下极限偏差
	 * @param dimText 标注文本
	 * @param tolUpper 传出上极限偏差
	 * @param tolLower 传出下极限偏差
	 */
	void parseDimensionTolerance(const AcString& dimText, double& tolUpper, double& tolLower);

	/**
	 * @brief 从标注中读取MText内容
	 * @param id 对象 ID
	 * @param text 内容文本
	 * @param isRawContent true 获取带控制字符的原始内容；false 获取纯文本内容
	 * @return true 成功；false 失败
	 */
	bool readMText(const AcDbObjectId& id, AcString& text, bool isRawContent = false);

	/**
	 * @brief 从标注中读取DText内容
	 * @param id 对象 ID
	 * @param text 内容文本
	 * @param isRawContent true 获取带控制字符的原始内容；false 获取纯文本内容
	 * @return true 成功；false 失败
	 */
	bool readDText(const AcDbObjectId& id, AcString& text, bool isRawContent = false);

	/**
	 * @brief 解析控制字符得到纯文本
	 * @param text 传带控制字符的文本，传出纯文本
	 */
	void resolveControlCodes(AcString& text);

	/**
	 * @brief 获取被选中的多行文本或单行文本的带控制字符文本
	 * @param content 传出带控制字符的文本
	 * @return true 成功；false 失败
	 */
	bool getSelectedTextRawContent(AcString& content);

	/**
	 * @brief 更新文本内容
	 * @param id 文本对象
	 * @param content 文本内容
	 */
	void updateTextEntityContent(const AcDbObjectId& id, const AcString& content);
}
