module;
#include "stdafx.h"

module Dimension;

import Common;

namespace Dimension
{
	void dimensionFix(AcDbObjectId objId)
	{
		AcDbDimension* pDim = Common::getObject<AcDbDimension>(objId, AcDb::kForWrite);
		if (pDim == nullptr)
		{
			return;
		}

		// 获取当前的标注文本
		AcString dimensionOriginText;
		pDim->dimensionText(dimensionOriginText);

		// 获取标注的实体实际尺寸值
		double measurementValue = .0;
		if (pDim->measurement(measurementValue) != Acad::eOk)
		{
			return;
		 }

		AcString measurementValueText;

		if (pDim->isKindOf(AcDb2LineAngularDimension::desc())) // 角度
		{
			int precision = pDim->dimadec();
			measurementValue = Common::rad2deg(measurementValue);
			Common::double2AcString(measurementValue, measurementValueText, precision);
			measurementValueText += Common::DimSymbol::Degree;
		}
		else
		{
			int precision = pDim->dimdec();
			Common::double2AcString(measurementValue, measurementValueText, precision);

			if (pDim->isKindOf(AcDbDiametricDimension::desc())) // 直径
			{
				measurementValueText = Common::DimSymbol::Diameter + measurementValueText;
			}
			else if (pDim->isKindOf(AcDbRadialDimension::desc())) // 半径
			{
				measurementValueText = Common::DimSymbol::Radius + measurementValueText;
			}
		}

		if (dimensionOriginText.isEmpty()) // 没有手改过标注内容的情况
		{
			pDim->setDimensionText(measurementValueText);
		}
		else
		{
			if (dimensionOriginText.find(Common::ACDB_DIM_TEXT_DEFAULT) == -1)
			{
				// 已经是固定文本，跳过处理
				return;
			}
			else
			{
				dimensionOriginText.replace(Common::ACDB_DIM_TEXT_DEFAULT, measurementValueText.kACharPtr());
				pDim->setDimensionText(dimensionOriginText.kACharPtr());
			}
		}
	}

	void dimensionResume(AcDbObjectId objId)
	{
		AcDbDimension* pDim = Common::getObject<AcDbDimension>(objId, AcDb::kForWrite);
		if (pDim == nullptr)
		{
			return;
		}
		pDim->setDimensionText(L"");
	}

	void addSurroundingCharsForDimension(AcDbObjectId objId, const ACHAR* left, const ACHAR* right, bool isLGdt, bool isRGdt)
	{
        AcDbDimension* pDim = Common::getObject<AcDbDimension>(objId, AcDb::kForWrite);
		if (pDim == nullptr)
		{
            return;
		}
		AcString dimensionText;
        pDim->dimensionText(dimensionText);

		// 处理 GDT 字体包裹
		AcString leftWrapedString = isLGdt ? Common::wrapWithGdtFont(left) : AcString(left);
		const ACHAR* leftNew = leftWrapedString.kACharPtr();
		AcString rightWrapedString = isRGdt ? Common::wrapWithGdtFont(right) : AcString(right);
        const ACHAR* rightNew = rightWrapedString.kACharPtr();

		AcString dimensionNewText;
		if (dimensionText.empty())
		{
			dimensionNewText.format(L"%s%s%s", leftNew, Common::ACDB_DIM_TEXT_DEFAULT, rightNew);
		}
		else
		{
			dimensionNewText.format(L"%s%s%s", leftNew, dimensionText.kACharPtr(), rightNew);
		}
        pDim->setDimensionText(dimensionNewText.kACharPtr());
	}

	void removeSurroundingCharsForDimension(AcDbObjectId objId, const ACHAR* left, const ACHAR* right, bool isLGdt, bool isRGdt)
	{
		AcDbDimension* pDim = Common::getObject<AcDbDimension>(objId, AcDb::kForWrite);
		if (pDim == nullptr)
		{
			return;
		}

		AcString text;
		pDim->dimensionText(text);

		if (text.isEmpty())
		{
			return;
		}

		// 处理 GDT 字体包裹
		AcString leftWrapedString = isLGdt ? Common::wrapWithGdtFont(left) : AcString(left);
		const ACHAR* leftNew = leftWrapedString.kACharPtr();
		AcString rightWrapedString = isRGdt ? Common::wrapWithGdtFont(right) : AcString(right);
		const ACHAR* rightNew = rightWrapedString.kACharPtr();

		// 使用 static_cast 明确转换类型，消除编译器关于类型缩减的警告
		int nTextLen = static_cast<int>(text.length());
		int nLeftLen = (leftNew != nullptr) ? static_cast<int>(wcslen(leftNew)) : 0;
		int nRightLen = (rightNew != nullptr) ? static_cast<int>(wcslen(rightNew)) : 0;

		// 检查是否匹配左侧
		bool bLeftMatch = (nLeftLen == 0);
		if (nLeftLen > 0 && nTextLen >= nLeftLen)
		{
			if (text.find(leftNew) == 0)
			{
				bLeftMatch = true;
			}
		}

		// 检查是否匹配右侧
		bool bRightMatch = (nRightLen == 0);
		if (nRightLen > 0 && nTextLen >= nRightLen)
		{
			// 计算索引时也确保类型一致
			if (text.findLast(rightNew) == (nTextLen - nRightLen))
			{
				bRightMatch = true;
			}
		}

		// 只有在参数要求的部分都匹配时才执行截取
		if (bLeftMatch && bRightMatch)
		{
			int nMidLen = nTextLen - nLeftLen - nRightLen;

			if (nMidLen >= 0)
			{
				AcString newText = text.mid(nLeftLen, nMidLen);

				// 如果结果为默认占位符或为空，则清空覆盖文字以恢复测量值显示
				if (newText == Common::ACDB_DIM_TEXT_DEFAULT || newText.isEmpty())
				{
					pDim->setDimensionText(L"");
				}
				else
				{
					pDim->setDimensionText(newText.kACharPtr());
				}
			}
		}
	}

	void setAndUnsetBasicBox(AcDbObjectId objId, bool isSet)
	{
		AcDbDimension* pDim = Common::getObject<AcDbDimension>(objId, AcDb::kForWrite);
		if (pDim == nullptr)
		{
			return;
		}

		double absDimgap = abs(pDim->dimgap());
		if (isSet)
		{
			pDim->setDimgap(-absDimgap);
		}
		else
		{
			pDim->setDimgap(absDimgap);
		}
	}

	void setAndUnsetRefDim(AcDbObjectId objId, bool isSet)
	{
		const ACHAR* left = L"(";
        const ACHAR* right = L")";
		if (isSet)
		{
			Dimension::addSurroundingCharsForDimension(objId, left, right);
		}
		else
		{
            Dimension::removeSurroundingCharsForDimension(objId, left, right);
		}
	}
}