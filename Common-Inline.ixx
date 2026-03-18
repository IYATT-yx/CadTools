module;
#include "StdAfx.h"
#include <cmath>

export module Common:Inline;

export namespace Common
{
	template <typename T>
	T* getObject(const AcDbObjectId objId, AcDb::OpenMode mode)
	{
		AcTransaction* pTrans = actrTransactionManager->topTransaction();
		if (pTrans == nullptr)
		{
			return nullptr;
		}

		AcDbObject* pObj = nullptr;
		if (pTrans->getObject(pObj, objId, mode) == Acad::eOk)
		{
			return T::cast(pObj);
		}
		return nullptr;
	}

	constexpr double deg2rad(double degrees)
	{
		return degrees * M_PI / 180.0;
	}

	constexpr double rad2deg(double radians)
	{
		return radians * 180.0 / M_PI;
	}
}

