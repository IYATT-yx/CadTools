module;
#include "stdafx.h"

module EntityStyle;

import Common;

namespace EntityStyle
{
	void setByLayer(const AcDbObjectId& objId)
	{
		AcDbEntity* pEntity = Common::getObject<AcDbEntity>(objId, AcDb::kForWrite);
		if (pEntity == nullptr)
		{
			return;
		}

		// 颜色
		AcCmColor color;
		color.setByLayer();
		pEntity->setColor(color);


		// 线型
		pEntity->setLinetype(L"ByLayer");
		// 线宽
		pEntity->setLineWeight(AcDb::kLnWtByLayer);
	}
}