module;
#include "StdAfx.h"

module GeometricTolerance;
import Common;

namespace GeometricTolerance
{
	void readFcf(AcDbObjectId id, GeometricToleranceData& data)
	{
		AcmFCF* pFcf = Common::getObject<AcmFCF>(id, AcDb::kForRead);
		if (pFcf == nullptr)
		{
			data.status = false;
			return;
		}

		// 句柄
		AcDbHandle handle = nullptr;
		pFcf->getAcDbHandle(handle);
		data.u64handle = handle;

		// 第 1 个
		data.gdtSymbolType[0] = pFcf->symbol();
		data.name[0] = GeometricTolerance::gdtNameMap[data.gdtSymbolType[0]];
		data.gdtSymbol[0] = GeometricTolerance::gdtSymbolMap[data.gdtSymbolType[0]];
		data.value[0] = pFcf->value(Acm::FCFTolerance);
		data.primary[0] = pFcf->value(Acm::FCFDatumPrimary);
        data.secondary[0] = pFcf->value(Acm::FCFDatumSecondary);
        data.tertiary[0] = pFcf->value(Acm::FCFDatumTertiary);

		// 第 2 个
		data.gdtSymbolType[1] = pFcf->symbol2();
		if (data.gdtSymbolType[1] != Acm::kNoType)
		{
            data.name[1] = GeometricTolerance::gdtNameMap[data.gdtSymbolType[1]];
            data.gdtSymbol[1] = GeometricTolerance::gdtSymbolMap[data.gdtSymbolType[1]];
			data.value[1] = pFcf->value(Acm::FCFTolerance2);
            data.primary[1] = pFcf->value(Acm::FCFDatumPrimary2);
            data.secondary[1] = pFcf->value(Acm::FCFDatumSecondary2);
            data.tertiary[1] = pFcf->value(Acm::FCFDatumTertiary2);

			// 第 3 个
			data.gdtSymbolType[2] = pFcf->symbol3();
			if (data.gdtSymbolType[2] != Acm::kNoType)
			{
                data.name[2] = GeometricTolerance::gdtNameMap[data.gdtSymbolType[2]];
                data.gdtSymbol[2] = GeometricTolerance::gdtSymbolMap[data.gdtSymbolType[2]];
                data.value[2] = pFcf->value(Acm::FCFTolerance3);
                data.primary[2] = pFcf->value(Acm::FCFDatumPrimary3);
                data.secondary[2] = pFcf->value(Acm::FCFDatumSecondary3);
                data.tertiary[2] = pFcf->value(Acm::FCFDatumTertiary3);
			}
		}
        data.status = true;
	}
}