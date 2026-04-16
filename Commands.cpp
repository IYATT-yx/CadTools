module;
#include "stdafx.h"
#include "resource.h"

module Commands;
import Common;

namespace Commands
{
	void registerYxCmds(Commands::CommandInfoList& cil)
	{
		CAcModuleResourceOverride resOverride;
		CString cmdGroup;
		cmdGroup.LoadStringW(IDS_CommandGroup);
		for (Commands::CommandInfo commandInfo : cil)
		{
			// ×¢²áÃüÁîÈ«Ãû
			acedRegCmds->addCommand(cmdGroup, commandInfo.commandName.constPtr(), commandInfo.commandName.constPtr(), commandInfo.flags, commandInfo.proc);
			// ×¢²áÃüÁî¼ò³Æ
			AcString shortCommandName = commandInfo.getShortCommandName();
			acedRegCmds->addCommand(cmdGroup, shortCommandName.constPtr(), shortCommandName.constPtr(), commandInfo.flags, commandInfo.proc);
		}
	}

	void executeCommand(const Commands::CommandList& cmdList, AcApDocument* pDoc)
	{
        if (cmdList.empty())
        {
            return;
        }

        if (pDoc == nullptr)
        {
            pDoc = acDocManager->curDocument();
        }

        if (pDoc == nullptr)
        {
            return;
        }

        AcString finalCmd;
        finalCmd.format(L"._%s\n", cmdList[0]);
        for (size_t i = 1; i < cmdList.size(); ++i)
        {
            finalCmd.append(cmdList[i]);
            finalCmd.append(L"\n");

        }
        acDocManager->sendStringToExecute(pDoc, finalCmd.constPtr(), false, true, true);
	}
}