module;
#include "stdafx.h"
#include "GenericPairEditDlg.hpp"
#include "MainBar.hpp"
#include "resource.h"

module Interface;

import EntityStyle;
import BuildingTime;
import UniversalPicker;
import Dimension;
import Common;
import BalloonNumber;
import CsvModule;
import GeometricTolerance;
import TextUtil;
import ImeAutoSwitcher;
import Commands;
import FileDialog;
import Annotative;

void Interface::init()
{
    CAcModuleResourceOverride resOverride;
    // 命令列表
    Commands::commandInfoList =
    {
        {L"yx", Common::loadString(IDS_CMD_yx), Commands::CommandFlags::Base, Interface::cmdYx},
        {L"yxTest", Common::loadString(IDS_CMD_yxTest), Commands::CommandFlags::Base, Interface::test},
        {L"yxUnload", Common::loadString(IDS_CMD_yxUnload), Commands::CommandFlags::Base, Interface::cmdUnloadApp},
        {L"yxSetByLayer", Common::loadString(IDS_CMD_yxSetByLayer), Commands::CommandFlags::PickRedraw, Interface::cmdSetByLayer},
        {L"yxDimensionFix", Common::loadString(IDS_CMD_yxDimensionFix), Commands::CommandFlags::PickRedraw, Interface::cmdDimensionFix},
        {L"yxDimensionResume", Common::loadString(IDS_CMD_yxDimensionResume), Commands::CommandFlags::PickRedraw, Interface::cmdDimensionResume},
        {L"yxAddSurroundingCharsForDimension", Common::loadString(IDS_CMD_yxAddSurroundingCharsForDimension), Commands::CommandFlags::PickRedraw, Interface::cmdAddSurroundingCharsForDimension},
        {L"yxRemoveSurroundingCharsForDimension", Common::loadString(IDS_CMD_yxRemoveSurroundingCharsForDimension), Commands::CommandFlags::PickRedraw, Interface::cmdRemoveSurroundingCharsForDimension},
        {L"yxSetBasicBox", Common::loadString(IDS_CMD_yxSetBasicBox), Commands::CommandFlags::PickRedraw, Interface::cmdSetBasicBox},
        {L"yxUnsetBasicBox", Common::loadString(IDS_CMD_yxUnsetBasicBox), Commands::CommandFlags::PickRedraw, Interface::cmdUnsetBasicBox},
        {L"yxSetRefDim", Common::loadString(IDS_CMD_yxSetRefDim), Commands::CommandFlags::PickRedraw, Interface::cmdSetRefDim},
        {L"yxUnsetRefDim", Common::loadString(IDS_CMD_yxUnsetRefDim), Commands::CommandFlags::PickRedraw, Interface::cmdUnsetRefDim},
        {L"yxInsertBalloonNumberBlockWithStartNumber", Common::loadString(IDS_CMD_yxInsertBalloonNumberBlockWithStartNumber), Commands::CommandFlags::Base, Interface::cmdInsertBalloonNumberBlockWithStartNumber},
        {L"yxPrintClassHierarchy", Common::loadString(IDS_CMD_yxPrintClassHierarchy), Commands::CommandFlags::Base, Interface::cmdPrintClassHierarchy},
        {L"yxExtractAnnotations", Common::loadString(IDS_CMD_yxExtractAnnotations), Commands::CommandFlags::Base, Interface::cmdExtractAnnotations},
        {L"yxUpdateBalloonNumberBlock", Common::loadString(IDS_CMD_yxUpdateBalloonNumberBlock), Commands::CommandFlags::PickRedraw, Interface::cmdUpdateBalloonNumberBlock},
        {L"yxImeAutoSwitch", Common::loadString(IDS_CMD_yxImeAutoSwitch), Commands::CommandFlags::Base, Interface::cmdImeAutoSwitch},
        {L"yxCloneText", Common::loadString(IDS_CMD_yxCloneText), Commands::CommandFlags::Base, Interface::cmdCloneText},
        {L"yxIntersect", Common::loadString(IDS_CMD_yxIntersect), Commands::CommandFlags::Base, Interface::cmdIntersect},
        {L"yxBalloonNumberOffset", Common::loadString(IDS_CMD_yxBalloonNumberOffset), Commands::CommandFlags::PickRedraw, Interface::cmdBalloonNumberOffset},
        {L"yxBalloonNumberFilter", Common::loadString(IDS_CMD_yxBalloonNumberFilter), Commands::CommandFlags::PickRedraw, Interface::cmdBalloonNumberFilter},
        {L"yxImportCsvToMTextMatrix", Common::loadString(IDS_CMD_yxImportCsvToMTextMatrix), Commands::CommandFlags::PickRedraw, Interface::cmdImportCsvToMTextMatrix},
        {L"yxSpatialTableExplorer", Common::loadString(IDS_CMD_yxSpatialTableExplorer), Commands::CommandFlags::PickRedraw, Interface::cmdSpatialTableExplorer}
    };

    Interface::info();

    // 注册命令
    Commands::registerYxCmds(Commands::commandInfoList);

    // 输入法自动切换自启动 
    bool bAutoStart = false;
    int nAutoMonitorInterval = 200;
    ImeAutoSwitcher::loadSettings(bAutoStart, nAutoMonitorInterval);
    if (bAutoStart)
    {
        ImeAutoSwitcher::start(nAutoMonitorInterval);
    }
    // 显示命令报表悬浮窗
    MainBar::showBar(Commands::commandInfoList);
}

// 测试使用
void Interface::test()
{
}

void Interface::unload()
{
    // 关闭输入法自动切换
    ImeAutoSwitcher::stop();
    // 关闭命令菜单
    MainBar::terminateBar();
    // 卸载命令
    CAcModuleResourceOverride resOverride;
    CString cmdGroup;
    cmdGroup.LoadStringW(IDS_CommandGroup);
	acedRegCmds->removeGroup(cmdGroup);
    acutPrintf(Common::loadString(IDS_Msg_Unload_FMT), Common::loadString(IDS_VAL_LocaleProjectName));
}

void Interface::cmdUnloadApp()
{
    const wchar_t* appName = acedGetAppName();
    Commands::CommandList pszCmdList =
    {
        L"ARX",
        L"U",
        appName
    };
    Commands::executeCommand(pszCmdList);
}

void Interface::info()
{
    CAcModuleResourceOverride resOverride;
    acutPrintf(L"\n%s %s_%s | %s | %s | %s\n",
        Common::loadString(IDS_VAL_LocaleProjectName),
        BuildingTime::WDATE, BuildingTime::WTIME,
        Common::loadString(IDS_VAL_Author),
        Common::loadString(IDS_VAL_LICENSE),
        Common::loadString(IDS_VAL_ProjectUrl)
        );
}

void Interface::cmdYx()
{
    Interface::info();
    MainBar::showBar(Commands::commandInfoList);
}

void Interface::cmdSetByLayer()
{
    CAcModuleResourceOverride resOverride;
    UniversalPicker::run(nullptr, EntityStyle::setByLayer, Common::loadString(IDS_CMD_yxSetByLayer));
}

void Interface::cmdDimensionFix()
{
    CAcModuleResourceOverride resOverride;
    UniversalPicker::run(&Common::DimensionSubClasses, Dimension::dimensionFix, Common::loadString(IDS_CMD_yxDimensionFix));
}

void Interface::cmdDimensionResume()
{
    CAcModuleResourceOverride resOverride;
    UniversalPicker::run(&Common::DimensionSubClasses, Dimension::dimensionResume, Common::loadString(IDS_CMD_yxDimensionResume));
}

void Interface::cmdAddSurroundingCharsForDimension()
{
    CAcModuleResourceOverride resOverride;
    CString title = Common::loadString(IDS_CMD_yxAddSurroundingCharsForDimension);
    GenericPairEditDlg dlg(title, Common::loadString(IDS_LBL_PrefixSymbol), Common::loadString(IDS_LBL_SuffixSymbol));

    CString left, right;
    dlg.setValidatorAndParser([&](const CString& value1, const CString& value2) -> CString
        {
            left = value1;
            right= value2;
            return GenericPairEditDlg::ValidatorOk;
        });
    if (dlg.DoModal() != IDOK)
    {
        acutPrintf(L"\n%s", Common::loadString(IDS_MSG_CancelOperation));
        return;
    }

    bool isLGdt = dlg.getGdtCheckStatus(0);
    bool isRGdt = dlg.getGdtCheckStatus(1);
    UniversalPicker::run(
        &Common::DimensionSubClasses,
        [&](AcDbObjectId objId)
        {
            Dimension::addSurroundingCharsForDimension(objId, left, right, isLGdt, isRGdt);
        },
        title,
        UniversalPicker::SelectMode::Immediate
    );
}

void Interface::cmdRemoveSurroundingCharsForDimension()
{
    CAcModuleResourceOverride resOverride;
    CString title = Common::loadString(IDS_CMD_yxRemoveSurroundingCharsForDimension);
    GenericPairEditDlg dlg(title, Common::loadString(IDS_LBL_PrefixSymbol), Common::loadString(IDS_LBL_SuffixSymbol));

    CString left, right;
    dlg.setValidatorAndParser([&](const CString& value1, const CString& value2) -> CString
        {
            left = value1;
            right = value2;
            return GenericPairEditDlg::ValidatorOk;
        });
    if (dlg.DoModal() != IDOK)
    {
        acutPrintf(L"\n%s", Common::loadString(IDS_MSG_CancelOperation));
        return;
    }

    bool isLGdt = dlg.getGdtCheckStatus(0);
    bool isRGdt = dlg.getGdtCheckStatus(1);
    UniversalPicker::run(
        &Common::DimensionSubClasses,
        [&](AcDbObjectId objId)
        {
            Dimension::removeSurroundingCharsForDimension(objId, left, right, isLGdt, isRGdt);
        },
        title,
        UniversalPicker::SelectMode::Immediate
    );
}

void Interface::cmdSetBasicBox()
{
    CAcModuleResourceOverride resOverride;
    UniversalPicker::run(
        &Common::DimensionSubClasses,
        [](AcDbObjectId objId)
        {
            Dimension::setAndUnsetBasicBox(objId, true);
        },
        Common::loadString(IDS_CMD_yxSetBasicBox),
        UniversalPicker::SelectMode::Immediate
    );
}

void Interface::cmdUnsetBasicBox()
{
    CAcModuleResourceOverride resOverride;
    UniversalPicker::run(
        &Common::DimensionSubClasses,
        [](AcDbObjectId objId)
        {
            Dimension::setAndUnsetBasicBox(objId, false);
        },
        Common::loadString(IDS_CMD_yxUnsetBasicBox),
        UniversalPicker::SelectMode::Immediate
    );
}

void Interface::cmdSetRefDim()
{
    CAcModuleResourceOverride resOverride;
    UniversalPicker::run(
        &Common::DimensionSubClasses,
        [](AcDbObjectId objId)
        {
            Dimension::setAndUnsetRefDim(objId, true);
        },
        Common::loadString(IDS_CMD_yxSetRefDim),
        UniversalPicker::SelectMode::Immediate
    );
}

void Interface::cmdUnsetRefDim()
{
    CAcModuleResourceOverride resOverride;
    UniversalPicker::run(
        &Common::DimensionSubClasses,
        [](AcDbObjectId objId)
        {
            Dimension::setAndUnsetRefDim(objId, false);
        },
        Common::loadString(IDS_CMD_yxUnsetRefDim),
        UniversalPicker::SelectMode::Immediate
    );
}

void Interface::cmdInsertBalloonNumberBlockWithStartNumber()
{
    CAcModuleResourceOverride resOverride;
    CString title = Common::loadString(IDS_CMD_yxInsertBalloonNumberBlockWithStartNumber);
    acutPrintf(L"\n%s\n", title);

    GenericPairEditDlg dlg(title, Common::loadString(IDS_LBL_StartNumber), Common::loadString(IDS_LBL_Tip), false, true, true);
    // 设置默认字高
    CString csTips;
    csTips.Format(Common::loadString(IDS_TIP_yxInsertBalloonNumberBlockWithStartNumber_FMT), Common::BalloonNumberBlock::defaultTextHeight, Annotative::getCurrentScaleValue());
    dlg.modifyEditControl(L"", csTips);

    int startNumber;
    dlg.setValidatorAndParser([&](const CString& strVal, const CString& _) -> CString
        {
            try
            {
                size_t pos;
                startNumber = std::stoi(strVal.GetString(), &pos);
                if (pos != strVal.GetLength())
                {
                    throw std::exception();
                }
                if (startNumber < 0)
                {
                    throw std::exception();
                }
            }
            catch (...)
            {
                return Common::loadString(IDS_Err_InvalidStartNumber);
            }
            return GenericPairEditDlg::ValidatorOk;
        });

    if (dlg.DoModal() != IDOK)
    {
        acutPrintf(L"\n%s", Common::loadString(IDS_MSG_CancelOperation));
        return;
    }

    BalloonNumber::createBalloonNumberBlock();
    BalloonNumber::insertBalloonNumberBlockWithStartNumber(startNumber);
}

void Interface::cmdPrintClassHierarchy()
{
    CAcModuleResourceOverride resOverride;
    UniversalPicker::run(nullptr, Common::printClassHierarchy, Common::loadString(IDS_CMD_yxPrintClassHierarchy), UniversalPicker::SelectMode::Immediate, true);
}

void Interface::cmdExtractAnnotations()
{
    CAcModuleResourceOverride resOverride;
    FileDialog::FileDialogFilterBuilder fileFilterBuilder;
    CString strFileFilter = fileFilterBuilder.addFilter(Common::loadString(IDS_FILTER_CsvFiles), { L"*.csv" }).build();
    CString filePath = FileDialog::ShowSaveFileDialog(Common::loadString(IDS_TITLE_SaveCsv), Common::loadString(IDS_FILE_DefaultSaveDataCsv), L"csv", strFileFilter);
    if (filePath.IsEmpty())
    {
        acutPrintf(L"\n%s", Common::loadString(IDS_MSG_CancelOperation));
        return;
    }

    CsvWriter csv(filePath);
    if (!csv.isValid())
    {
        AfxMessageBox(Common::loadString(IDS_Err_FileOpenFailed), MB_OK | MB_ICONERROR);
        return;
    }

    UniversalPicker::AcRxClassVector filter = { AcmFCF::desc(), AcDbMText::desc(), AcDbText::desc()};
    filter.insert(filter.end(), Common::DimensionSubClasses.begin(), Common::DimensionSubClasses.end());
    UniversalPicker::run(
        &filter,
        [&csv](AcDbObjectId objId)
        {
            Dimension::DimensionData dimData{};
            Dimension::readDim(objId, dimData);
            GeometricTolerance::GeometricToleranceData gtData{};
            GeometricTolerance::readFcf(objId, gtData);
            AcString asMText, asDText;

            if (dimData.status) // 尺寸
            {
                // 名义值
                AcString asMeasuredValue;
                double dMeasuredValue = dimData.measuredValue;
                if (dimData.isAngle)
                {
                    dMeasuredValue = dimData.degreeValue();
                }
                Common::double2AcString(dMeasuredValue, asMeasuredValue, dimData.measuredValuePrecision);
                
                //acutPrintf(L"\n调试：%s %s %f %f ", dimData.prefix.constPtr(), dimData.suffix.constPtr(), dimData.tolUpper, dimData.tolLower);
                // 公差
                AcString asTol,asTolUpper, asTolLower;
                if (dimData.tolUpper == 0 && dimData.tolLower == 0) // 无公差
                {
                    asTol = L"";
                    asTolUpper = L"0";
                    asTolLower = L"0";
                }
                else
                {
                    if (abs(dimData.tolUpper + dimData.tolLower) < 1e-6) // 等双向公差
                    {
                        double dAbsTol = abs(dimData.tolUpper);
                        asTol.format(L"%s%.*g", Common::SymbolCodes::PlusMinus, dimData.tolPrecision, dAbsTol);
                        asTolUpper.format(L"%.*g", dimData.tolPrecision, dAbsTol);
                        asTolLower.format(L"-%.*g", dimData.tolPrecision, dAbsTol);
                    }
                    else // 双向公差
                    {
                        
                        Common::double2AcString(dimData.tolUpper, asTolUpper, dimData.tolPrecision);
                        Common::double2AcString(dimData.tolLower, asTolLower, dimData.tolPrecision);
                        asTol.format(L"+%s/%s", asTolUpper.constPtr(), asTolLower.constPtr());
                        asTolUpper.format(L"%.*g", dimData.tolPrecision, dimData.tolUpper);
                        asTolLower.format(L"%.*g", dimData.tolPrecision, dimData.tolLower);
                    }
                }

                AcString asDimText = dimData.prefix + asMeasuredValue + asTol + dimData.suffix;
                acutPrintf(Common::loadString(IDS_MSG_Dimension_FMT), asDimText.constPtr());
                std::vector<AcString> row = { asDimText, asMeasuredValue, asTolUpper, asTolLower }; // 完整尺寸文本、名义值、上极限偏差、下极限偏差
                csv.writeRow(row);
            }
            else if (gtData.status) // 几何公差
            {
                for (int i = 0; i < GeometricTolerance::GeometricToleranceDataLen; ++i)
                {
                    GeometricTolerance::GeometricToleranceRow row = gtData.rows[i];
                    if (row.gdtSymbolType != Acm::kNoType)
                    {
                        AcString name = row.name;
                        AcString value = row.value;
                        AcString primary = row.primary;
                        AcString secondary = row.secondary;
                        AcString tertiary = row.tertiary;
                        AcString strRow = row.toString();
                        acutPrintf(Common::loadString(IDS_MSG_GDT), strRow.constPtr());
                        std::vector<AcString> asvRow = { strRow, name, value, primary, secondary, tertiary };
                        csv.writeRow(asvRow);
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else if (TextUtil::readMText(objId, asMText))
            {
                acutPrintf(Common::loadString(IDS_MSG_MText_FMT), asMText.constPtr());
                std::vector<AcString> rows = { asMText };
                csv.writeRow(rows);
            }
            else if (TextUtil::readDText(objId, asDText))
            {
                acutPrintf(Common::loadString(IDS_MSG_DText_FMT), asDText.constPtr());
                std::vector<AcString> rows = { asDText };
                csv.writeRow(rows);
            }
        },
        Common::loadString(IDS_CMD_yxExtractAnnotations),
        UniversalPicker::SelectMode::Immediate,
        false,
        UniversalPicker::SortMode::RD,
        false
    );
}

void Interface::cmdUpdateBalloonNumberBlock()
{
    CAcModuleResourceOverride resOverride;
    CString title = Common::loadString(IDS_CMD_yxUpdateBalloonNumberBlock);
    acutPrintf(L"\n%s\n", title);

    GenericPairEditDlg dlg(title, Common::loadString(IDS_LBL_StartNumber), Common::loadString(IDS_LBL_BalloonNumberHeight), true, true, true);

    int startNumber;
    dlg.setValidatorAndParser([&](const CString& strValue, const CString& _) -> CString
    {
            try
            {
                size_t pos;
                startNumber = std::stoi(strValue.GetString(), &pos);
                if (pos != strValue.GetLength())
                {
                    throw std::exception();
                }
                if (startNumber < 0)
                {
                    throw std::exception();
                }
            }
            catch (...)
            {
                return Common::loadString(IDS_Err_InvalidStartNumber);
            }
            return GenericPairEditDlg::ValidatorOk;
    });

    if (dlg.DoModal() != IDOK)
    {
        acutPrintf(L"\n%s", Common::loadString(IDS_MSG_CancelOperation));
        return;
    }

    UniversalPicker::AcRxClassVector arcv = { AcDbBlockReference::desc() };

    acutPrintf(Common::loadString(IDS_MSG_BalloonNextNumber_FMT), startNumber);
    UniversalPicker::run(
        &arcv,
        [&](const AcDbObjectId& id)
        {
            if (BalloonNumber::updateBalloonNumberBlock(id, startNumber))
            {
                ++startNumber;
                acutPrintf(Common::loadString(IDS_MSG_BalloonNextNumber_FMT), startNumber);
            }
        },
        nullptr,
        UniversalPicker::SelectMode::Immediate,
        false,
        UniversalPicker::SortMode::RD,
        false
    );
}

void Interface::cmdImeAutoSwitch()
{
    CAcModuleResourceOverride resOverride;
    CString title = Common::loadString(IDS_CMD_yxImeAutoSwitch);
    GenericPairEditDlg dlg(title, Common::loadString(IDS_LBL_AutoStart), Common::loadString(IDS_LBL_Interval), false, true, true);

    CString edit1Result, edit2Result;
    bool bAutoStart;
    int nInterval;
    ImeAutoSwitcher::loadSettings(bAutoStart, nInterval);
    edit1Result.Format(L"%d", bAutoStart);
    edit2Result.Format(L"%d", nInterval);
    dlg.modifyEditControl(edit1Result, edit2Result);

    dlg.setValidatorAndParser([&](const CString& value1, const CString& value2) -> CString
        {
            if (value1.IsEmpty() || value2.IsEmpty())
            {
                return Common::loadString(IDS_Err_ImeAutoSwitchEmptySetting);
            }
            if (value1.SpanIncluding(L"01") != value1)
            {
                return Common::loadString(IDS_Err_InvalidAutoStart);
            }
            try
            {
                size_t pos;
                nInterval = std::stoi(value2.GetString(), &pos);
                if (pos != value2.GetLength())
                {
                    throw std::exception();
                }
                if (nInterval < ImeAutoSwitcher::defaultIntervalMs)
                {
                    throw std::exception();
                }
            }
            catch (...)
            {
                CString csInvalidInterval;
                csInvalidInterval.Format(Common::loadString(IDS_Err_InvalidInterval_FMT), ImeAutoSwitcher::defaultIntervalMs);
                return csInvalidInterval;
            }

            edit1Result = value1;
            return GenericPairEditDlg::ValidatorOk;
        });

    if (dlg.DoModal() != IDOK)
    {
        acutPrintf(L"\n%s", Common::loadString(IDS_MSG_CancelOperation));
        return;
    }

    bAutoStart = edit1Result == L"1";
    ImeAutoSwitcher::stop();
    if (bAutoStart)
    {
        ImeAutoSwitcher::start(nInterval);
    }
    ImeAutoSwitcher::saveSettings(bAutoStart, nInterval);
}

void Interface::cmdCloneText()
{
    CAcModuleResourceOverride resOverride;
    AcString asSrcTextContent;
    acutPrintf(L"\n%s", Common::loadString(IDS_PROMPT_CopySrcText));
    if (!TextUtil::getSelectedTextRawContent(asSrcTextContent) || asSrcTextContent.isEmpty())
    {
        acutPrintf(L"\n%s", Common::loadString(IDS_MSG_CancelOperation));
        return;
    }
    acutPrintf(L"\n读取到：%s\n", asSrcTextContent.constPtr());

    acutPrintf(L"\n%s", Common::loadString(IDS_PROMPT_PasteDstText));
    UniversalPicker::run(
        &TextUtil::textClassList,
        [&asSrcTextContent](const AcDbObjectId& id)
        {
            TextUtil::updateTextEntityContent(id, asSrcTextContent);
        },
        Common::loadString(IDS_CMD_yxCloneText),
        UniversalPicker::SelectMode::Immediate,
        false,
        UniversalPicker::SortMode::None,
        true
    );
}

void Interface::cmdIntersect()
{
    Commands::CommandList pszCmdList =
    {
        L"FILLET",
        L"M",
        L"R",
        L"0"
    };
    Commands::executeCommand(pszCmdList);
}

void Interface::cmdBalloonNumberOffset()
{
    CAcModuleResourceOverride resOverride;
    CString title = Common::loadString(IDS_CMD_yxBalloonNumberOffset);
    GenericPairEditDlg dlg(title, Common::loadString(IDS_LBL_BalloonNumberOffset), Common::loadString(IDS_LBL_Tip), false, true, true);
    dlg.modifyEditControl(L"", Common::loadString(IDS_TIP_BalloonNumberOffset));

    int offset;
    dlg.setValidatorAndParser([&](const CString& strValue, const CString& _) -> CString
        {
            if (strValue.IsEmpty())
            {
                return Common::loadString(IDS_Err_EmptyBalloonNumberOffset);
            }
            try
            {
                size_t pos = 0;
                offset = std::stoi(strValue.GetString(), &pos);
                if (pos != strValue.GetLength())
                {
                    throw std::exception();
                }
            }
            catch (...)
            {
                return Common::loadString(IDS_Err_InvalidInteger);
            }
            return GenericPairEditDlg::ValidatorOk;
        });

    if (dlg.DoModal() != IDOK)
    {
        acutPrintf(L"\n%s", Common::loadString(IDS_MSG_CancelOperation));
        return;
    }

    UniversalPicker::AcRxClassVector arcv = { AcDbBlockReference::desc() };
    UniversalPicker::run(
        &arcv,
        [&offset](const AcDbObjectId& id)
        {
            BalloonNumber::balloonNumberOffset(id, offset);
        },
        title,
        UniversalPicker::SelectMode::Batch,
        false,
        UniversalPicker::SortMode::None,
        true
    );
}

void Interface::cmdBalloonNumberFilter()
{
    CAcModuleResourceOverride resOverride;
    CString title = Common::loadString(IDS_CMD_yxBalloonNumberFilter);
    GenericPairEditDlg dlg(title, Common::loadString(IDS_LBL_BalloonNumberFilterCondition), Common::loadString(IDS_LBL_Tip), false, true, false);
    dlg.modifyEditControl(L"", Common::loadString(IDS_TIP_BalloonNumberFilter));

    CString edit1Result;
    dlg.setValidatorAndParser([&](const CString& strValue, const CString& _) -> CString
        {
            if (strValue.GetLength() < 3)
            {
                return Common::loadString(IDS_Err_BalloonNumberFilterEmptyCriteria);
            }

            // 验证输入合法性
            /////////////////////
            // 无限制判定值的符号列表
            std::vector<CString> opNoLimit = { BalloonNumber::OperatorType::equal, BalloonNumber::OperatorType::notEqual1, BalloonNumber::OperatorType::notEqual2 };
            // 限制判定值为数字的列表
            std::vector<CString> opNeedNumeric =
            {
                BalloonNumber::OperatorType::greater1, BalloonNumber::OperatorType::greater2,
                BalloonNumber::OperatorType::less1, BalloonNumber::OperatorType::less2,
                BalloonNumber::OperatorType::greaterEqual1, BalloonNumber::OperatorType::greaterEqual2,
                BalloonNumber::OperatorType::lessEqual1, BalloonNumber::OperatorType::lessEqual2
            };

            CString strInputOpType = strValue.Left(2);
            CString strInputOpValue = strValue.Mid(2);
            auto it = std::find(opNoLimit.begin(), opNoLimit.end(), strInputOpType);
            if (it == opNoLimit.end()) // 不在无限制判定值的符号列表中，则要求判定值必须为正数
            {
                // 进一步判断是否输入了非法符号
                it = std::find(opNeedNumeric.begin(), opNeedNumeric.end(), strInputOpType);
                if (it == opNeedNumeric.end())
                {
                    return Common::loadString(IDS_Err_BalloonNumberFilterInvalidOperatorType);
                }

                try
                {
                    size_t pos = 0;
                    int iInputOpValue = std::stoi(strInputOpValue.GetString(), &pos);
                    if (pos != strInputOpValue.GetLength())
                    {
                        throw std::exception();
                    }
                }
                catch (...)
                {
                    return Common::loadString(IDS_Err_BalloonNumberFilterNeedInterger);
                }
            }
            edit1Result = strValue;
            return GenericPairEditDlg::ValidatorOk;
        });

    if (dlg.DoModal() != IDOK)
    {
        acutPrintf(L"\n%s", Common::loadString(IDS_MSG_CancelOperation));
        return;
    }

    AcDbObjectIdArray matchedIds;
    UniversalPicker::AcRxClassVector arcv = { AcDbBlockReference::desc() };

    UniversalPicker::run(
        &arcv,
        [&](const AcDbObjectId& id)
        {
            AcString attrValue;
            if (BalloonNumber::getBalloonAttributeValue(id, attrValue))
            {
                if (BalloonNumber::meetCriteria(attrValue, edit1Result.GetString()))
                {
                    matchedIds.append(id);
                }
            }
        },
        title,
        UniversalPicker::SelectMode::Batch,
        true,
        UniversalPicker::SortMode::None,
        true
    );

    if (matchedIds.length() > 0)
    {
        UniversalPicker::setSelection(matchedIds);
        acutPrintf(Common::loadString(IDS_Msg_BalloonNumberFilterMatchCount_FMT), matchedIds.length());
    }
    else
    {
        acutPrintf(Common::loadString(IDS_Msg_BalloonNumberFilterNoMatch));
    }
}

void Interface::cmdImportCsvToMTextMatrix()
{
    CAcModuleResourceOverride resOverride;
    FileDialog::FileDialogFilterBuilder fileFilterBuilter;
    CString strFileFilter = fileFilterBuilter.addFilter(Common::loadString(IDS_FILTER_CsvFiles), { L"*.csv" }).build();
    CString strFilePath = FileDialog::ShowOpenFileDialog(Common::loadString(IDS_TITLE_ImportCsv), L"csv", strFileFilter);
    if (strFilePath.IsEmpty())
    {
        acutPrintf(L"\n%s", Common::loadString(IDS_MSG_CancelOperation));
        return;
    }

    CsvModule::AcStringMatrix matrixData;
    CsvModule::readCsvToAcStringMatrix(strFilePath, matrixData);

    GenericPairEditDlg dlg(Common::loadString(IDS_CMD_yxImportCsvToMTextMatrix), Common::loadString(IDS_LBL_Parameter), Common::loadString(IDS_LBL_Tip), false, true, true);
    dlg.modifyEditControl(L"", Common::loadString(IDS_TIP_MTextMatrixParameter));

    std::vector<double> params;
    dlg.setValidatorAndParser([&](const CString& edit1, const CString& _) -> CString
        {
            const int paramsNumber = 3;
            if (!Common::parse(edit1, paramsNumber, [](double v) { return v > 0; }, params))
            {
                return Common::loadString(IDS_TIP_MTextMatrixParameter);
            }
            return GenericPairEditDlg::ValidatorOk;
        });

    if (dlg.DoModal() != IDOK)
    {
        acutPrintf(L"\n%s", Common::loadString(IDS_MSG_CancelOperation));
        return;
    }

    ads_point pt{};
    if (acedGetPoint(nullptr, Common::loadString(IDS_PROMPT_GetPoint), pt) != RTNORM)
    {
        acutPrintf(L"\n%s", Common::loadString(IDS_MSG_CancelOperation));
        return;
    }

    TextUtil::createMTextMatrix(params[0], params[1], params[2], matrixData, asPnt3d(pt));
}

    void Interface::cmdSpatialTableExplorer()
    {
        CAcModuleResourceOverride resOverride;
        CString title = Common::loadString(IDS_CMD_yxSpatialTableExplorer);
        GenericPairEditDlg dlg(title, Common::loadString(IDS_LBL_Parameter), Common::loadString(IDS_LBL_Tip), false, true, true);

        // 默认列容差和行容差
        // 字高默认 3.5，列容差默认按字高的 3 倍，行容差默认按字高的 1 倍（考虑注释比例缩放值）
        CString strInitParameter;
        double scale = Annotative::getCurrentScaleValue();
        strInitParameter.Format(L"%g %g", Common::defaultTextHeight * scale * 3, Common::defaultTextHeight * scale * 1);
        dlg.modifyEditControl(strInitParameter, Common::loadString(IDS_TIP_SpatialTableExplorerParameter));

        std::vector<double> params;
        dlg.setValidatorAndParser([&](const CString& edit1, const CString& _) -> CString
            {
                const int paramsNumber = 2;
                if (!Common::parse(edit1, paramsNumber, [](double v) { return v > 0; }, params))
                {
                    return Common::loadString(IDS_TIP_SpatialTableExplorerParameter);
                }
                return GenericPairEditDlg::ValidatorOk;
            });

    
        if (dlg.DoModal() != IDOK)
        {
            acutPrintf(L"\n%s", Common::loadString(IDS_MSG_CancelOperation));
            return;
        }

        FileDialog::FileDialogFilterBuilder fileFilterBuilter;
        CString strFileFilter = fileFilterBuilter.addFilter(Common::loadString(IDS_FILTER_CsvFiles), { L"*.csv" }).build();
        CString strFilePath = FileDialog::ShowSaveFileDialog(Common::loadString(IDS_TITLE_SaveCsv), Common::loadString(IDS_FILE_DefaultSaveDataCsv), L"csv", strFileFilter);
        if (strFilePath.IsEmpty())
        {
            acutPrintf(L"\n%s", Common::loadString(IDS_MSG_CancelOperation));
            return;
        }
        CsvWriter writer(strFilePath);
        if (!writer.isValid())
        {
            AfxMessageBox(Common::loadString(IDS_Err_FileOpenFailed), MB_OK | MB_ICONERROR);
            return;
        }

        TextUtil::TextEntityDataList elements;
        UniversalPicker::run(
            &TextUtil::textClassList,
            [&](const AcDbObjectId& id)
            {
                TextUtil::TextEntityData data;
                data.id = id;
                if (TextUtil::readMText(id, data.text, false, &data.pos))
                {
                    acutPrintf(Common::loadString(IDS_MSG_MTextPos_FMT), data.pos.x, data.pos.y, data.pos.z, data.text.constPtr());
                }
                else if (TextUtil::readDText(id, data.text, false, &data.pos))
                {
                    acutPrintf(Common::loadString(IDS_MSG_DTextPos_FMT), data.text.constPtr());
                }
                elements.push_back(data);
            },
            title,
            UniversalPicker::SelectMode::Batch,
            false,
            UniversalPicker::SortMode::None,
            true
        );

        CsvModule::AcStringMatrix matrixData;
        TextUtil::structureTextToAcStringMatrix(elements, params[0], params[1], matrixData);
    

        for (const auto& row : matrixData)
        {
            writer.writeRow(row);
            acutPrintf(L"\n");
            for (const auto& field : row)
            {
                acutPrintf(L"%s\t", field.constPtr());
            }
        }

        acutPrintf(Common::loadString(IDS_MSG_FileLocation_FMT), strFilePath);
    }