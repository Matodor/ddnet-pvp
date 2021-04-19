/* (c) Shereef Marzouk. See "licence DDRace.txt" and the readme.txt in the root of the distribution for more information. */
#include "gamecontext.h"
#include <engine/engine.h>
#include <engine/shared/config.h>
#include <engine/shared/protocol.h>
#include <game/server/gamemodes/DDRace.h>
#include <game/server/teams.h>
#include <game/version.h>

#include "entities/character.h"
#include "player.h"

bool CheckClientID(int ClientID);

// void CGameContext::ConCredits(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;

// 	pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "credits",
// 		"DDNet is run by the DDNet staff (DDNet.tw/staff)");
// 	pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "credits",
// 		"Great maps and many ideas from the great community");
// 	pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "credits",
// 		"Help and code by eeeee, HMH, east, CookieMichal, Learath2,");
// 	pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "credits",
// 		"Savander, laxa, Tobii, BeaR, Wohoo, nuborn, timakro, Shiki,");
// 	pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "credits",
// 		"trml, Soreu, hi_leute_gll, Lady Saavik, Chairn, heinrich5991,");
// 	pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "credits",
// 		"swick, oy, necropotame, Ryozuki, Redix, d3fault, marcelherd,");
// 	pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "credits",
// 		"BannZay, ACTom, SiuFuWong, PathosEthosLogos, TsFreddie,");
// 	pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "credits",
// 		"Jupeyy, noby, ChillerDragon, ZombieToad, weez15, z6zzz,");
// 	pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "credits",
// 		"Piepow, QingGo, RafaelFF, sctt, jao, daverck, fokkonaut,");
// 	pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "credits",
// 		"Bojidar, FallenKN, ardadem, archimede67, sirius1242, Aerll,");
// 	pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "credits",
// 		"trafilaw, Zwelf, Patiga, Konsti, ElXreno, MikiGamer,");
// 	pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "credits",
// 		"Fireball, Banana090, axblk, yangfl & others.");
// 	pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "credits",
// 		"Based on DDRace by the DDRace developers,");
// 	pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "credits",
// 		"which is a mod of Teeworlds by the Teeworlds developers.");
// }

// void CGameContext::ConInfo(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;
// 	pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "info",
// 		"DDraceNetwork Mod. Version: " GAME_VERSION);
// 	if(GIT_SHORTREV_HASH)
// 	{
// 		char aBuf[64];
// 		str_format(aBuf, sizeof(aBuf), "Git revision hash: %s", GIT_SHORTREV_HASH);
// 		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "info", aBuf);
// 	}
// 	pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "info",
// 		"Official site: DDNet.tw");
// 	pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "info",
// 		"For more info: /cmdlist");
// 	pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "info",
// 		"Or visit DDNet.tw");
// }

void CGameContext::ConList(IConsole::IResult *pResult, void *pUserData)
{
	CGameContext *pSelf = (CGameContext *)pUserData;
	int ClientID = pResult->m_ClientID;
	if(!CheckClientID(ClientID))
		return;

	char zerochar = 0;
	if(pResult->NumArguments() > 0)
		pSelf->List(ClientID, pResult->GetString(0));
	else
		pSelf->List(ClientID, &zerochar);
}

// void CGameContext::ConHelp(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;

// 	if(pResult->NumArguments() == 0)
// 	{
// 		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "help",
// 			"/cmdlist will show a list of all chat commands");
// 		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "help",
// 			"/help + any command will show you the help for this command");
// 		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "help",
// 			"Example /help settings will display the help about /settings");
// 	}
// 	else
// 	{
// 		const char *pArg = pResult->GetString(0);
// 		const IConsole::CCommandInfo *pCmdInfo =
// 			pSelf->Console()->GetCommandInfo(pArg, CFGFLAG_SERVER, false);
// 		if(pCmdInfo)
// 		{
// 			if(pCmdInfo->m_pParams)
// 			{
// 				char aBuf[256];
// 				str_format(aBuf, sizeof(aBuf), "Usage: %s %s", pCmdInfo->m_pName, pCmdInfo->m_pParams);
// 				pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "help", aBuf);
// 			}

// 			if(pCmdInfo->m_pHelp)
// 				pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "help", pCmdInfo->m_pHelp);
// 		}
// 		else
// 			pSelf->Console()->Print(
// 				IConsole::OUTPUT_LEVEL_STANDARD,
// 				"help",
// 				"Command is either unknown or you have given a blank command without any parameters.");
// 	}
// }

// void CGameContext::ConSettings(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;

// 	if(pResult->NumArguments() == 0)
// 	{
// 		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "settings",
// 			"to check a server setting say /settings and setting's name, setting names are:");
// 		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "settings",
// 			"teams, cheats, collision, hooking, endlesshooking, me, ");
// 		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "settings",
// 			"hitting, oldlaser, timeout, votes, pause and scores");
// 	}
// 	else
// 	{
// 		const char *pArg = pResult->GetString(0);
// 		char aBuf[256];
// 		float ColTemp;
// 		float HookTemp;
// 		pSelf->m_Tuning.Get("player_collision", &ColTemp);
// 		pSelf->m_Tuning.Get("player_hooking", &HookTemp);
// 		if(str_comp(pArg, "teams") == 0)
// 		{
// 			str_format(aBuf, sizeof(aBuf), "%s %s",
// 				g_Config.m_SvTeam == 1 ?
// 					"Teams are available on this server" :
// 					(g_Config.m_SvTeam == 0 || g_Config.m_SvTeam == 3) ?
// 					"Teams are not available on this server" :
// 					"You have to be in a team to play on this server", /*g_Config.m_SvTeamStrict ? "and if you die in a team all of you die" : */
// 				"and all of your team will die if the team is locked");
// 			pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "settings", aBuf);
// 		}
// 		else if(str_comp(pArg, "cheats") == 0)
// 		{
// 			pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "settings",
// 				g_Config.m_SvTestingCommands ?
// 					"Cheats are enabled on this server" :
// 					"Cheats are disabled on this server");
// 		}
// 		else if(str_comp(pArg, "collision") == 0)
// 		{
// 			pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "settings",
// 				ColTemp ?
// 					"Players can collide on this server" :
// 					"Players can't collide on this server");
// 		}
// 		else if(str_comp(pArg, "hooking") == 0)
// 		{
// 			pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "settings",
// 				HookTemp ?
// 					"Players can hook each other on this server" :
// 					"Players can't hook each other on this server");
// 		}
// 		else if(str_comp(pArg, "endlesshooking") == 0)
// 		{
// 			pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "settings",
// 				g_Config.m_SvEndlessDrag ?
// 					"Players hook time is unlimited" :
// 					"Players hook time is limited");
// 		}
// 		else if(str_comp(pArg, "hitting") == 0)
// 		{
// 			pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "settings",
// 				g_Config.m_SvHit ?
// 					"Players weapons affect others" :
// 					"Players weapons has no affect on others");
// 		}
// 		else if(str_comp(pArg, "oldlaser") == 0)
// 		{
// 			pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "settings",
// 				g_Config.m_SvOldLaser ?
// 					"Lasers can hit you if you shot them and they pull you towards the bounce origin (Like DDRace Beta)" :
// 					"Lasers can't hit you if you shot them, and they pull others towards the shooter");
// 		}
// 		else if(str_comp(pArg, "me") == 0)
// 		{
// 			pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "settings",
// 				g_Config.m_SvSlashMe ?
// 					"Players can use /me commands the famous IRC Command" :
// 					"Players can't use the /me command");
// 		}
// 		else if(str_comp(pArg, "timeout") == 0)
// 		{
// 			str_format(aBuf, sizeof(aBuf), "The Server Timeout is currently set to %d seconds", g_Config.m_ConnTimeout);
// 			pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "settings", aBuf);
// 		}
// 		else if(str_comp(pArg, "votes") == 0)
// 		{
// 			pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "settings",
// 				g_Config.m_SvVoteKick ?
// 					"Players can use Callvote menu tab to kick offenders" :
// 					"Players can't use the Callvote menu tab to kick offenders");
// 			if(g_Config.m_SvVoteKick)
// 			{
// 				str_format(aBuf, sizeof(aBuf),
// 					"Players are banned for %d minute(s) if they get voted off", g_Config.m_SvVoteKickBantime);

// 				pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "settings",
// 					g_Config.m_SvVoteKickBantime ?
// 						aBuf :
// 						"Players are just kicked and not banned if they get voted off");
// 			}
// 		}
// 		else if(str_comp(pArg, "pause") == 0)
// 		{
// 			pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "settings",
// 				g_Config.m_SvPauseable ?
// 					"/spec will pause you and your tee will vanish" :
// 					"/spec will pause you but your tee will not vanish");
// 		}
// 		else if(str_comp(pArg, "scores") == 0)
// 		{
// 			pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "settings",
// 				g_Config.m_SvHideScore ?
// 					"Scores are private on this server" :
// 					"Scores are public on this server");
// 		}
// 		else
// 		{
// 			pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "settings",
// 				"no matching settings found, type /settings to view them");
// 		}
// 	}
// }

void CGameContext::ConRules(IConsole::IResult *pResult, void *pUserData)
{
	CGameContext *pSelf = (CGameContext *)pUserData;
	bool Printed = false;
	if(g_Config.m_SvDDRaceRules)
	{
		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "rules",
			"Be nice.");
		Printed = true;
	}
#define _RL(n) g_Config.m_SvRulesLine##n
	char *pRuleLines[] = {
		_RL(1),
		_RL(2),
		_RL(3),
		_RL(4),
		_RL(5),
		_RL(6),
		_RL(7),
		_RL(8),
		_RL(9),
		_RL(10),
	};
	for(auto &pRuleLine : pRuleLines)
	{
		if(pRuleLine[0])
		{
			pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD,
				"rules", pRuleLine);
			Printed = true;
		}
	}
	if(!Printed)
	{
		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "rules",
			"No Rules Defined, Kill em all!!");
	}
}

void ToggleSpecPause(IConsole::IResult *pResult, void *pUserData, int PauseType)
{
	if(!CheckClientID(pResult->m_ClientID))
		return;

	CGameContext *pSelf = (CGameContext *)pUserData;
	IServer *pServ = pSelf->Server();
	CPlayer *pPlayer = pSelf->m_apPlayers[pResult->m_ClientID];
	if(!pPlayer)
		return;

	int PauseState = pPlayer->IsPaused();
	if(PauseState > 0)
	{
		char aBuf[128];
		str_format(aBuf, sizeof(aBuf), "You are force-paused for %d seconds.", (PauseState - pServ->Tick()) / pServ->TickSpeed());
		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "spec", aBuf);
	}
	else if(pResult->NumArguments() > 0)
	{
		if(-PauseState == PauseType && pPlayer->m_SpectatorID != pResult->m_ClientID && pServ->ClientIngame(pPlayer->m_SpectatorID) && !str_comp(pServ->ClientName(pPlayer->m_SpectatorID), pResult->GetString(0)))
		{
			pPlayer->Pause(CPlayer::PAUSE_NONE, false);
		}
		else
		{
			pPlayer->Pause(PauseType, false);
			pPlayer->SpectatePlayerName(pResult->GetString(0));
		}
	}
	else if(-PauseState != CPlayer::PAUSE_NONE && PauseType != CPlayer::PAUSE_NONE)
	{
		pPlayer->Pause(CPlayer::PAUSE_NONE, false);
	}
	else if(-PauseState != PauseType)
	{
		pPlayer->Pause(PauseType, false);
	}
}

void ToggleSpecPauseVoted(IConsole::IResult *pResult, void *pUserData, int PauseType)
{
	if(!CheckClientID(pResult->m_ClientID))
		return;

	CGameContext *pSelf = (CGameContext *)pUserData;
	CPlayer *pPlayer = pSelf->m_apPlayers[pResult->m_ClientID];
	if(!pPlayer)
		return;

	int PauseState = pPlayer->IsPaused();
	if(PauseState > 0)
	{
		IServer *pServ = pSelf->Server();
		char aBuf[128];
		str_format(aBuf, sizeof(aBuf), "You are force-paused for %d seconds.", (PauseState - pServ->Tick()) / pServ->TickSpeed());
		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "spec", aBuf);
		return;
	}

	bool IsPlayerBeingVoted = pSelf->m_VoteCloseTime &&
				  (pSelf->IsKickVote() || pSelf->IsSpecVote()) &&
				  pResult->m_ClientID != pSelf->m_VoteVictim;
	if((!IsPlayerBeingVoted && -PauseState == PauseType) ||
		(IsPlayerBeingVoted && PauseState && pPlayer->m_SpectatorID == pSelf->m_VoteVictim))
	{
		pPlayer->Pause(CPlayer::PAUSE_NONE, false);
	}
	else
	{
		pPlayer->Pause(PauseType, false);
		if(IsPlayerBeingVoted)
			pPlayer->m_SpectatorID = pSelf->m_VoteVictim;
	}
}

// void CGameContext::ConToggleSpec(IConsole::IResult *pResult, void *pUserData)
// {
// 	ToggleSpecPause(pResult, pUserData, g_Config.m_SvPauseable ? CPlayer::PAUSE_SPEC : CPlayer::PAUSE_PAUSED);
// }

// void CGameContext::ConToggleSpecVoted(IConsole::IResult *pResult, void *pUserData)
// {
// 	ToggleSpecPauseVoted(pResult, pUserData, g_Config.m_SvPauseable ? CPlayer::PAUSE_SPEC : CPlayer::PAUSE_PAUSED);
// }

// void CGameContext::ConTogglePause(IConsole::IResult *pResult, void *pUserData)
// {
// 	ToggleSpecPause(pResult, pUserData, CPlayer::PAUSE_PAUSED);
// }

// void CGameContext::ConTogglePauseVoted(IConsole::IResult *pResult, void *pUserData)
// {
// 	ToggleSpecPauseVoted(pResult, pUserData, CPlayer::PAUSE_PAUSED);
// }

// void CGameContext::ConTeamTop5(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;
// 	if(!CheckClientID(pResult->m_ClientID))
// 		return;

// 	if(g_Config.m_SvHideScore)
// 	{
// 		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "teamtop5",
// 			"Showing the team top 5 is not allowed on this server.");
// 		return;
// 	}

// 	if(pResult->NumArguments() == 0)
// 	{
// 		pSelf->Score()->ShowTeamTop5(pResult->m_ClientID, 1);
// 	}
// 	else if(pResult->NumArguments() == 1)
// 	{
// 		if(pResult->GetInteger(0) != 0)
// 		{
// 			pSelf->Score()->ShowTeamTop5(pResult->m_ClientID, pResult->GetInteger(0));
// 		}
// 		else
// 		{
// 			const char *pRequestedName = (str_comp(pResult->GetString(0), "me") == 0) ?
// 							     pSelf->Server()->ClientName(pResult->m_ClientID) :
// 							     pResult->GetString(0);
// 			pSelf->Score()->ShowTeamTop5(pResult->m_ClientID, pRequestedName, 0);
// 		}
// 	}
// 	else if(pResult->NumArguments() == 2 && pResult->GetInteger(1) != 0)
// 	{
// 		const char *pRequestedName = (str_comp(pResult->GetString(0), "me") == 0) ?
// 						     pSelf->Server()->ClientName(pResult->m_ClientID) :
// 						     pResult->GetString(0);
// 		pSelf->Score()->ShowTeamTop5(pResult->m_ClientID, pRequestedName, pResult->GetInteger(1));
// 	}
// 	else
// 	{
// 		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "teamtop5", "/top5team needs 0, 1 or 2 parameter. 1. = name, 2. = start number");
// 		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "teamtop5", "Example: /top5team, /top5team me, /top5team Hans, /top5team \"Papa Smurf\" 5");
// 		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "teamtop5", "Bad: /top5team Papa Smurf 5 # Good: /top5team \"Papa Smurf\" 5 ");
// 	}
// }

// void CGameContext::ConTop5(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;
// 	if(!CheckClientID(pResult->m_ClientID))
// 		return;

// 	if(g_Config.m_SvHideScore)
// 	{
// 		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "top5",
// 			"Showing the top 5 is not allowed on this server.");
// 		return;
// 	}

// 	if(pResult->NumArguments() > 0)
// 		pSelf->Score()->ShowTop5(pResult->m_ClientID, pResult->GetInteger(0));
// 	else
// 		pSelf->Score()->ShowTop5(pResult->m_ClientID);
// }

// void CGameContext::ConTimes(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;
// 	if(!CheckClientID(pResult->m_ClientID))
// 		return;

// 	if(pResult->NumArguments() == 0)
// 	{
// 		pSelf->Score()->ShowTimes(pResult->m_ClientID, 1);
// 	}
// 	else if(pResult->NumArguments() == 1)
// 	{
// 		if(pResult->GetInteger(0) != 0)
// 		{
// 			pSelf->Score()->ShowTimes(pResult->m_ClientID, pResult->GetInteger(0));
// 		}
// 		else
// 		{
// 			const char *pRequestedName = (str_comp(pResult->GetString(0), "me") == 0) ?
// 							     pSelf->Server()->ClientName(pResult->m_ClientID) :
// 							     pResult->GetString(0);
// 			pSelf->Score()->ShowTimes(pResult->m_ClientID, pRequestedName, pResult->GetInteger(1));
// 		}
// 	}
// 	else if(pResult->NumArguments() == 2 && pResult->GetInteger(1) != 0)
// 	{
// 		const char *pRequestedName = (str_comp(pResult->GetString(0), "me") == 0) ?
// 						     pSelf->Server()->ClientName(pResult->m_ClientID) :
// 						     pResult->GetString(0);
// 		pSelf->Score()->ShowTimes(pResult->m_ClientID, pRequestedName, pResult->GetInteger(1));
// 	}
// 	else
// 	{
// 		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "times", "/times needs 0, 1 or 2 parameter. 1. = name, 2. = start number");
// 		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "times", "Example: /times, /times me, /times Hans, /times \"Papa Smurf\" 5");
// 		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "times", "Bad: /times Papa Smurf 5 # Good: /times \"Papa Smurf\" 5 ");
// 	}
// }

// void CGameContext::ConDND(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;
// 	if(!CheckClientID(pResult->m_ClientID))
// 		return;

// 	CPlayer *pPlayer = pSelf->m_apPlayers[pResult->m_ClientID];
// 	if(!pPlayer)
// 		return;

// 	if(pPlayer->m_DND)
// 	{
// 		pPlayer->m_DND = false;
// 		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "dnd", "You will receive global chat and server messages");
// 	}
// 	else
// 	{
// 		pPlayer->m_DND = true;
// 		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "dnd", "You will not receive any further global chat and server messages");
// 	}
// }

// void CGameContext::ConMap(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;
// 	if(!CheckClientID(pResult->m_ClientID))
// 		return;

// 	if(g_Config.m_SvMapVote == 0)
// 	{
// 		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "map",
// 			"/map is disabled");
// 		return;
// 	}

// 	if(pResult->NumArguments() <= 0)
// 	{
// 		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "map", "Example: /map adr3 to call vote for Adrenaline 3. This means that the map name must start with 'a' and contain the characters 'd', 'r' and '3' in that order");
// 		return;
// 	}

// 	CPlayer *pPlayer = pSelf->m_apPlayers[pResult->m_ClientID];
// 	if(!pPlayer)
// 		return;

// 	if(pSelf->RateLimitPlayerVote(pResult->m_ClientID) || pSelf->RateLimitPlayerMapVote(pResult->m_ClientID))
// 		return;

// 	pSelf->Score()->MapVote(pResult->m_ClientID, pResult->GetString(0));
// }

// void CGameContext::ConMapInfo(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;
// 	if(!CheckClientID(pResult->m_ClientID))
// 		return;

// 	CPlayer *pPlayer = pSelf->m_apPlayers[pResult->m_ClientID];
// 	if(!pPlayer)
// 		return;

// 	if(pResult->NumArguments() > 0)
// 		pSelf->Score()->MapInfo(pResult->m_ClientID, pResult->GetString(0));
// 	else
// 		pSelf->Score()->MapInfo(pResult->m_ClientID, g_Config.m_SvMap);
// }

// void CGameContext::ConTimeout(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;
// 	if(!CheckClientID(pResult->m_ClientID))
// 		return;

// 	CPlayer *pPlayer = pSelf->m_apPlayers[pResult->m_ClientID];
// 	if(!pPlayer)
// 		return;

// 	const char *pTimeout = pResult->NumArguments() > 0 ? pResult->GetString(0) : pPlayer->m_TimeoutCode;

// 	if(!pSelf->Server()->IsSixup(pResult->m_ClientID))
// 	{
// 		for(int i = 0; i < pSelf->Server()->MaxClients(); i++)
// 		{
// 			if(i == pResult->m_ClientID)
// 				continue;
// 			if(!pSelf->m_apPlayers[i])
// 				continue;
// 			if(str_comp(pSelf->m_apPlayers[i]->m_TimeoutCode, pTimeout))
// 				continue;
// 			if(pSelf->Server()->SetTimedOut(i, pResult->m_ClientID))
// 			{
// 				if(pSelf->m_apPlayers[i]->GetCharacter())
// 					pSelf->SendTuningParams(i, pSelf->m_apPlayers[i]->GetCharacter()->m_TuneZone);
// 				/*if(pSelf->Server()->IsSixup(i))
// 					pSelf->SendClientInfo(i, i);*/
// 				return;
// 			}
// 		}
// 	}
// 	else
// 	{
// 		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "print",
// 			"Your timeout code has been set. 0.7 clients can not reclaim their tees on timeout; however, a 0.6 client can claim your tee ");
// 	}

// 	pSelf->Server()->SetTimeoutProtected(pResult->m_ClientID);
// 	str_copy(pPlayer->m_TimeoutCode, pResult->GetString(0), sizeof(pPlayer->m_TimeoutCode));
// }

// void CGameContext::ConPractice(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;
// 	if(!CheckClientID(pResult->m_ClientID))
// 		return;

// 	CPlayer *pPlayer = pSelf->m_apPlayers[pResult->m_ClientID];
// 	if(!pPlayer)
// 		return;

// 	if(pSelf->ProcessSpamProtection(pResult->m_ClientID))
// 		return;

// 	if(!g_Config.m_SvPractice)
// 	{
// 		pSelf->Console()->Print(
// 			IConsole::OUTPUT_LEVEL_STANDARD,
// 			"print",
// 			"Practice mode is disabled");
// 		return;
// 	}

// 	CGameTeams &Teams = ((CGameControllerDDRace *)pSelf->m_pController)->m_Teams;

// 	int Team = Teams.m_Core.Team(pResult->m_ClientID);

// 	if(Team < TEAM_FLOCK || (Team == TEAM_FLOCK && g_Config.m_SvTeam != 3) || Team >= TEAM_SUPER)
// 	{
// 		pSelf->Console()->Print(
// 			IConsole::OUTPUT_LEVEL_STANDARD,
// 			"print",
// 			"Join a team to enable practice mode, which means you can use /r, but can't earn a rank.");
// 		return;
// 	}

// 	if(Teams.IsPractice(Team))
// 	{
// 		pSelf->Console()->Print(
// 			IConsole::OUTPUT_LEVEL_STANDARD,
// 			"print",
// 			"Team is already in practice mode");
// 		return;
// 	}

// 	bool VotedForPractice = pResult->NumArguments() == 0 || pResult->GetInteger(0);

// 	if(VotedForPractice == pPlayer->m_VotedForPractice)
// 		return;

// 	pPlayer->m_VotedForPractice = VotedForPractice;

// 	int NumCurrentVotes = 0;
// 	int TeamSize = 0;

// 	for(int i = 0; i < MAX_CLIENTS; i++)
// 	{
// 		if(Teams.m_Core.Team(i) == Team)
// 		{
// 			CPlayer *pPlayer2 = pSelf->m_apPlayers[i];
// 			if(pPlayer2 && pPlayer2->m_VotedForPractice)
// 				NumCurrentVotes++;
// 			TeamSize++;
// 		}
// 	}

// 	int NumRequiredVotes = TeamSize / 2 + 1;

// 	char aBuf[512];
// 	str_format(aBuf, sizeof(aBuf), "'%s' voted to %s /practice mode for your team, which means you can use /r, but you can't earn a rank. Type /practice to vote (%d/%d required votes)", pSelf->Server()->ClientName(pResult->m_ClientID), VotedForPractice ? "enable" : "disable", NumCurrentVotes, NumRequiredVotes);

// 	for(int i = 0; i < MAX_CLIENTS; i++)
// 		if(Teams.m_Core.Team(i) == Team)
// 			pSelf->SendChatTarget(i, aBuf);

// 	if(NumCurrentVotes >= NumRequiredVotes)
// 	{
// 		Teams.EnablePractice(Team);

// 		for(int i = 0; i < MAX_CLIENTS; i++)
// 			if(Teams.m_Core.Team(i) == Team)
// 				pSelf->SendChatTarget(i, "Practice mode enabled for your team, happy practicing!");
// 	}
// }

// void CGameContext::ConSave(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;
// 	if(!CheckClientID(pResult->m_ClientID))
// 		return;

// 	if(!g_Config.m_SvSaveGames)
// 	{
// 		pSelf->SendChatTarget(pResult->m_ClientID, "Save-function is disabled on this server");
// 		return;
// 	}

// 	const char *pCode = "";
// 	if(pResult->NumArguments() > 0)
// 		pCode = pResult->GetString(0);

// 	pSelf->Score()->SaveTeam(pResult->m_ClientID, pCode, g_Config.m_SvSqlServerName);
// }

// void CGameContext::ConLoad(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;
// 	if(!CheckClientID(pResult->m_ClientID))
// 		return;

// 	if(!g_Config.m_SvSaveGames)
// 	{
// 		pSelf->SendChatTarget(pResult->m_ClientID, "Save-function is disabled on this server");
// 		return;
// 	}

// 	if(pResult->NumArguments() > 0)
// 		pSelf->Score()->LoadTeam(pResult->GetString(0), pResult->m_ClientID);
// 	else
// 		pSelf->Score()->GetSaves(pResult->m_ClientID);
// }

// void CGameContext::ConTeamRank(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;
// 	if(!CheckClientID(pResult->m_ClientID))
// 		return;

// 	if(pResult->NumArguments() > 0)
// 	{
// 		if(!g_Config.m_SvHideScore)
// 			pSelf->Score()->ShowTeamRank(pResult->m_ClientID, pResult->GetString(0));
// 		else
// 			pSelf->Console()->Print(
// 				IConsole::OUTPUT_LEVEL_STANDARD,
// 				"teamrank",
// 				"Showing the team rank of other players is not allowed on this server.");
// 	}
// 	else
// 		pSelf->Score()->ShowTeamRank(pResult->m_ClientID,
// 			pSelf->Server()->ClientName(pResult->m_ClientID));
// }

// void CGameContext::ConRank(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;
// 	if(!CheckClientID(pResult->m_ClientID))
// 		return;

// 	if(pResult->NumArguments() > 0)
// 	{
// 		if(!g_Config.m_SvHideScore)
// 			pSelf->Score()->ShowRank(pResult->m_ClientID, pResult->GetString(0));
// 		else
// 			pSelf->Console()->Print(
// 				IConsole::OUTPUT_LEVEL_STANDARD,
// 				"rank",
// 				"Showing the rank of other players is not allowed on this server.");
// 	}
// 	else
// 		pSelf->Score()->ShowRank(pResult->m_ClientID,
// 			pSelf->Server()->ClientName(pResult->m_ClientID));
// }

void CGameContext::ConLockTeam(IConsole::IResult *pResult, void *pUserData)
{
	CGameContext *pSelf = (CGameContext *)pUserData;
	if(!CheckClientID(pResult->m_ClientID))
		return;

	if(g_Config.m_SvTeam == 0 || g_Config.m_SvTeam == 3)
	{
		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "lock",
			"Teams are disabled");
		return;
	}

	int Team = ((CGameControllerDDRace *)pSelf->m_pController)->m_Teams.m_Core.Team(pResult->m_ClientID);

	bool Lock = ((CGameControllerDDRace *)pSelf->m_pController)->m_Teams.TeamLocked(Team);

	if(pResult->NumArguments() > 0)
		Lock = !pResult->GetInteger(0);

	if(Team <= TEAM_FLOCK || Team >= TEAM_SUPER)
	{
		pSelf->Console()->Print(
			IConsole::OUTPUT_LEVEL_STANDARD,
			"print",
			"This team can't be locked");
		return;
	}

	if(pSelf->ProcessSpamProtection(pResult->m_ClientID))
		return;

	char aBuf[512];
	if(Lock)
	{
		pSelf->UnlockTeam(pResult->m_ClientID, Team);
	}
	else
	{
		((CGameControllerDDRace *)pSelf->m_pController)->m_Teams.SetTeamLock(Team, true);

		str_format(aBuf, sizeof(aBuf), "'%s' locked your team. After the race starts, killing will kill everyone in your team.", pSelf->Server()->ClientName(pResult->m_ClientID));

		for(int i = 0; i < MAX_CLIENTS; i++)
			if(((CGameControllerDDRace *)pSelf->m_pController)->m_Teams.m_Core.Team(i) == Team)
				pSelf->SendChatTarget(i, aBuf);
	}
}

void CGameContext::ConUnlockTeam(IConsole::IResult *pResult, void *pUserData)
{
	CGameContext *pSelf = (CGameContext *)pUserData;
	if(!CheckClientID(pResult->m_ClientID))
		return;

	if(g_Config.m_SvTeam == 0 || g_Config.m_SvTeam == 3)
	{
		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "unlock",
			"Teams are disabled");
		return;
	}

	int Team = ((CGameControllerDDRace *)pSelf->m_pController)->m_Teams.m_Core.Team(pResult->m_ClientID);

	if(Team <= TEAM_FLOCK || Team >= TEAM_SUPER)
		return;

	if(pSelf->ProcessSpamProtection(pResult->m_ClientID))
		return;

	pSelf->UnlockTeam(pResult->m_ClientID, Team);
}

void CGameContext::UnlockTeam(int ClientID, int Team)
{
	((CGameControllerDDRace *)m_pController)->m_Teams.SetTeamLock(Team, false);

	char aBuf[512];
	str_format(aBuf, sizeof(aBuf), "'%s' unlocked your team.", Server()->ClientName(ClientID));

	for(int i = 0; i < MAX_CLIENTS; i++)
		if(((CGameControllerDDRace *)m_pController)->m_Teams.m_Core.Team(i) == Team)
			SendChatTarget(i, aBuf);
}

void CGameContext::ConInviteTeam(IConsole::IResult *pResult, void *pUserData)
{
	CGameContext *pSelf = (CGameContext *)pUserData;
	CGameControllerDDRace *pController = (CGameControllerDDRace *)pSelf->m_pController;
	const char *pName = pResult->GetString(0);

	if(g_Config.m_SvTeam == 0 || g_Config.m_SvTeam == 3)
	{
		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "join",
			"Teams are disabled");
		return;
	}

	if(!g_Config.m_SvInvite)
	{
		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "invite", "Invites are disabled");
		return;
	}

	int Team = pController->m_Teams.m_Core.Team(pResult->m_ClientID);
	if(Team > TEAM_FLOCK && Team < TEAM_SUPER)
	{
		int Target = -1;
		for(int i = 0; i < MAX_CLIENTS; i++)
		{
			if(!str_comp(pName, pSelf->Server()->ClientName(i)))
			{
				Target = i;
				break;
			}
		}

		if(Target < 0)
		{
			pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "invite", "Player not found");
			return;
		}

		if(pController->m_Teams.IsInvited(Team, Target))
		{
			pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "invite", "Player already invited");
			return;
		}

		if(pSelf->m_apPlayers[pResult->m_ClientID] && pSelf->m_apPlayers[pResult->m_ClientID]->m_LastInvited + g_Config.m_SvInviteFrequency * pSelf->Server()->TickSpeed() > pSelf->Server()->Tick())
		{
			pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "invite", "Can't invite this quickly");
			return;
		}

		pController->m_Teams.SetClientInvited(Team, Target, true);
		pSelf->m_apPlayers[pResult->m_ClientID]->m_LastInvited = pSelf->Server()->Tick();

		char aBuf[512];
		str_format(aBuf, sizeof aBuf, "'%s' invited you to team %d.", pSelf->Server()->ClientName(pResult->m_ClientID), Team);
		pSelf->SendChatTarget(Target, aBuf);

		str_format(aBuf, sizeof aBuf, "'%s' invited '%s' to your team.", pSelf->Server()->ClientName(pResult->m_ClientID), pSelf->Server()->ClientName(Target));
		;
		for(int i = 0; i < MAX_CLIENTS; i++)
			if(((CGameControllerDDRace *)pSelf->m_pController)->m_Teams.m_Core.Team(i) == Team)
				pSelf->SendChatTarget(i, aBuf);
	}
	else
		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "invite", "Can't invite players to this team");
}

void CGameContext::ConJoinTeam(IConsole::IResult *pResult, void *pUserData)
{
	CGameContext *pSelf = (CGameContext *)pUserData;
	CGameControllerDDRace *pController = (CGameControllerDDRace *)pSelf->m_pController;
	if(!CheckClientID(pResult->m_ClientID))
		return;

	CPlayer *pPlayer = pSelf->m_apPlayers[pResult->m_ClientID];
	if(!pPlayer)
		return;

	if(pSelf->m_VoteCloseTime && pSelf->m_VoteCreator == pResult->m_ClientID && (pSelf->IsKickVote() || pSelf->IsSpecVote()))
	{
		pSelf->Console()->Print(
			IConsole::OUTPUT_LEVEL_STANDARD,
			"join",
			"You are running a vote please try again after the vote is done!");
		return;
	}
	else if(g_Config.m_SvTeam == 0 || g_Config.m_SvTeam == 3)
	{
		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "join",
			"Teams are disabled");
		return;
	}
	else if(g_Config.m_SvTeam == 2 && pResult->GetInteger(0) == 0 && pPlayer->GetCharacter() && pPlayer->GetCharacter()->m_LastStartWarning < pSelf->Server()->Tick() - 3 * pSelf->Server()->TickSpeed())
	{
		pSelf->Console()->Print(
			IConsole::OUTPUT_LEVEL_STANDARD,
			"join",
			"You must join a team and play with somebody or else you can\'t play");
		pPlayer->GetCharacter()->m_LastStartWarning = pSelf->Server()->Tick();
	}

	if(pResult->NumArguments() > 0)
	{
		if(pPlayer->GetCharacter() == 0)
		{
			pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "join",
				"You can't change teams while you are dead/a spectator.");
		}
		else
		{
			int Team = pResult->GetInteger(0);

			if(pPlayer->m_Last_Team + (int64_t)pSelf->Server()->TickSpeed() * g_Config.m_SvTeamChangeDelay > pSelf->Server()->Tick())
			{
				pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "join",
					"You can\'t change teams that fast!");
			}
			else if(Team > 0 && Team < MAX_CLIENTS && pController->m_Teams.TeamLocked(Team) && !pController->m_Teams.IsInvited(Team, pResult->m_ClientID))
			{
				pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "join",
					g_Config.m_SvInvite ?
						"This team is locked using /lock. Only members of the team can unlock it using /lock." :
						"This team is locked using /lock. Only members of the team can invite you or unlock it using /lock.");
			}
			else if(Team > 0 && Team < MAX_CLIENTS && pController->m_Teams.Count(Team) >= g_Config.m_SvTeamMaxSize)
			{
				char aBuf[512];
				str_format(aBuf, sizeof(aBuf), "This team already has the maximum allowed size of %d players", g_Config.m_SvTeamMaxSize);
				pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "join", aBuf);
			}
			else if(const char *pError = pController->m_Teams.SetCharacterTeam(pPlayer->GetCID(), Team))
			{
				pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "join", pError);
			}
			else
			{
				char aBuf[512];
				str_format(aBuf, sizeof(aBuf), "%s joined team %d",
					pSelf->Server()->ClientName(pPlayer->GetCID()),
					Team);
				pSelf->SendChat(-1, CGameContext::CHAT_ALL, aBuf);
				pPlayer->m_Last_Team = pSelf->Server()->Tick();

				// if(pController->m_Teams.IsPractice(Team))
				// 	pSelf->SendChatTarget(pPlayer->GetCID(), "Practice mode enabled for your team, happy practicing!");
			}
		}
	}
	else
	{
		char aBuf[512];
		if(!pPlayer->IsPlaying())
		{
			pSelf->Console()->Print(
				IConsole::OUTPUT_LEVEL_STANDARD,
				"join",
				"You can't check your team while you are dead/a spectator.");
		}
		else
		{
			str_format(
				aBuf,
				sizeof(aBuf),
				"You are in team %d",
				((CGameControllerDDRace *)pSelf->m_pController)->m_Teams.m_Core.Team(pResult->m_ClientID));
			pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "join",
				aBuf);
		}
	}
}

void CGameContext::ConMe(IConsole::IResult *pResult, void *pUserData)
{
	CGameContext *pSelf = (CGameContext *)pUserData;
	if(!CheckClientID(pResult->m_ClientID))
		return;

	char aBuf[256 + 24];

	str_format(aBuf, 256 + 24, "'%s' %s",
		pSelf->Server()->ClientName(pResult->m_ClientID),
		pResult->GetString(0));
	if(g_Config.m_SvSlashMe)
		pSelf->SendChat(-2, CGameContext::CHAT_ALL, aBuf, pResult->m_ClientID);
	else
		pSelf->Console()->Print(
			IConsole::OUTPUT_LEVEL_STANDARD,
			"me",
			"/me is disabled on this server");
}

void CGameContext::ConConverse(IConsole::IResult *pResult, void *pUserData)
{
	// This will never be called
}

void CGameContext::ConWhisper(IConsole::IResult *pResult, void *pUserData)
{
	// This will never be called
}

void CGameContext::ConSetEyeEmote(IConsole::IResult *pResult,
	void *pUserData)
{
	CGameContext *pSelf = (CGameContext *)pUserData;
	if(!CheckClientID(pResult->m_ClientID))
		return;

	CPlayer *pPlayer = pSelf->m_apPlayers[pResult->m_ClientID];
	if(!pPlayer)
		return;
	if(pResult->NumArguments() == 0)
	{
		pSelf->Console()->Print(
			IConsole::OUTPUT_LEVEL_STANDARD,
			"emote",
			(pPlayer->m_EyeEmoteEnabled) ?
				"You can now use the preset eye emotes." :
				"You don't have any eye emotes, remember to bind some. (until you die)");
		return;
	}
	else if(str_comp_nocase(pResult->GetString(0), "on") == 0)
		pPlayer->m_EyeEmoteEnabled = true;
	else if(str_comp_nocase(pResult->GetString(0), "off") == 0)
		pPlayer->m_EyeEmoteEnabled = false;
	else if(str_comp_nocase(pResult->GetString(0), "toggle") == 0)
		pPlayer->m_EyeEmoteEnabled = !pPlayer->m_EyeEmoteEnabled;
	pSelf->Console()->Print(
		IConsole::OUTPUT_LEVEL_STANDARD,
		"emote",
		(pPlayer->m_EyeEmoteEnabled) ?
			"You can now use the preset eye emotes." :
			"You don't have any eye emotes, remember to bind some. (until you die)");
}

void CGameContext::ConEyeEmote(IConsole::IResult *pResult, void *pUserData)
{
	CGameContext *pSelf = (CGameContext *)pUserData;
	if(g_Config.m_SvEmotionalTees == -1)
	{
		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "emote",
			"Emotes are disabled.");
		return;
	}

	if(!CheckClientID(pResult->m_ClientID))
		return;

	CPlayer *pPlayer = pSelf->m_apPlayers[pResult->m_ClientID];
	if(!pPlayer)
		return;

	if(pResult->NumArguments() == 0)
	{
		pSelf->Console()->Print(
			IConsole::OUTPUT_LEVEL_STANDARD,
			"emote",
			"Emote commands are: /emote surprise /emote blink /emote close /emote angry /emote happy /emote pain");
		pSelf->Console()->Print(
			IConsole::OUTPUT_LEVEL_STANDARD,
			"emote",
			"Example: /emote surprise 10 for 10 seconds or /emote surprise (default 1 second)");
	}
	else
	{
		if(!pPlayer->CanOverrideDefaultEmote())
			return;

		int EmoteType = 0;
		if(!str_comp(pResult->GetString(0), "angry"))
			EmoteType = EMOTE_ANGRY;
		else if(!str_comp(pResult->GetString(0), "blink"))
			EmoteType = EMOTE_BLINK;
		else if(!str_comp(pResult->GetString(0), "close"))
			EmoteType = EMOTE_BLINK;
		else if(!str_comp(pResult->GetString(0), "happy"))
			EmoteType = EMOTE_HAPPY;
		else if(!str_comp(pResult->GetString(0), "pain"))
			EmoteType = EMOTE_PAIN;
		else if(!str_comp(pResult->GetString(0), "surprise"))
			EmoteType = EMOTE_SURPRISE;
		else if(!str_comp(pResult->GetString(0), "normal"))
			EmoteType = EMOTE_NORMAL;
		else
		{
			pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD,
				"emote", "Unknown emote... Say /emote");
			return;
		}

		int Duration = 1;
		if(pResult->NumArguments() > 1)
			Duration = clamp(pResult->GetInteger(1), 1, 86400);

		pPlayer->OverrideDefaultEmote(EmoteType, pSelf->Server()->Tick() + Duration * pSelf->Server()->TickSpeed());
	}
}

// void CGameContext::ConNinjaJetpack(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;
// 	if(!CheckClientID(pResult->m_ClientID))
// 		return;

// 	CPlayer *pPlayer = pSelf->m_apPlayers[pResult->m_ClientID];
// 	if(!pPlayer)
// 		return;
// 	if(pResult->NumArguments())
// 		pPlayer->m_NinjaJetpack = pResult->GetInteger(0);
// 	else
// 		pPlayer->m_NinjaJetpack = !pPlayer->m_NinjaJetpack;
// }

// void CGameContext::ConShowOthers(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;
// 	if(!CheckClientID(pResult->m_ClientID))
// 		return;

// 	CPlayer *pPlayer = pSelf->m_apPlayers[pResult->m_ClientID];
// 	if(!pPlayer)
// 		return;
// 	if(g_Config.m_SvShowOthers)
// 	{
// 		if(pResult->NumArguments())
// 			pPlayer->m_ShowOthers = pResult->GetInteger(0);
// 		else
// 			pPlayer->m_ShowOthers = !pPlayer->m_ShowOthers;
// 	}
// 	else
// 		pSelf->Console()->Print(
// 			IConsole::OUTPUT_LEVEL_STANDARD,
// 			"showotherschat",
// 			"Showing players from other teams is disabled");
// }

// void CGameContext::ConShowAll(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;
// 	if(!CheckClientID(pResult->m_ClientID))
// 		return;

// 	CPlayer *pPlayer = pSelf->m_apPlayers[pResult->m_ClientID];
// 	if(!pPlayer)
// 		return;

// 	if(pResult->NumArguments())
// 	{
// 		if(pPlayer->m_ShowAll == (bool)pResult->GetInteger(0))
// 			return;

// 		pPlayer->m_ShowAll = pResult->GetInteger(0);
// 	}
// 	else
// 	{
// 		pPlayer->m_ShowAll = !pPlayer->m_ShowAll;
// 	}

// 	if(pPlayer->m_ShowAll)
// 		pSelf->SendChatTarget(pResult->m_ClientID, "You will now see all tees on this server, no matter the distance");
// 	else
// 		pSelf->SendChatTarget(pResult->m_ClientID, "You will no longer see all tees on this server");
// }

// void CGameContext::ConSpecTeam(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;
// 	if(!CheckClientID(pResult->m_ClientID))
// 		return;

// 	CPlayer *pPlayer = pSelf->m_apPlayers[pResult->m_ClientID];
// 	if(!pPlayer)
// 		return;

// 	if(pResult->NumArguments())
// 		pPlayer->m_SpecTeam = pResult->GetInteger(0);
// 	else
// 		pPlayer->m_SpecTeam = !pPlayer->m_SpecTeam;
// }

bool CheckClientID(int ClientID)
{
	if(ClientID < 0 || ClientID >= MAX_CLIENTS)
		return false;
	return true;
}

// void CGameContext::ConSayTime(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;
// 	if(!CheckClientID(pResult->m_ClientID))
// 		return;

// 	int ClientID;
// 	char aBufName[MAX_NAME_LENGTH];

// 	if(pResult->NumArguments() > 0)
// 	{
// 		for(ClientID = 0; ClientID < MAX_CLIENTS; ClientID++)
// 			if(str_comp(pResult->GetString(0), pSelf->Server()->ClientName(ClientID)) == 0)
// 				break;

// 		if(ClientID == MAX_CLIENTS)
// 			return;

// 		str_format(aBufName, sizeof(aBufName), "%s's", pSelf->Server()->ClientName(ClientID));
// 	}
// 	else
// 	{
// 		str_copy(aBufName, "Your", sizeof(aBufName));
// 		ClientID = pResult->m_ClientID;
// 	}

// 	CPlayer *pPlayer = pSelf->m_apPlayers[ClientID];
// 	if(!pPlayer)
// 		return;
// 	CCharacter *pChr = pPlayer->GetCharacter();
// 	if(!pChr)
// 		return;
// 	if(pChr->m_DDRaceState != DDRACE_STARTED)
// 		return;

// 	char aBufTime[32];
// 	char aBuf[64];
// 	int64 Time = (int64)100 * (float)(pSelf->Server()->Tick() - pChr->m_StartTime) / ((float)pSelf->Server()->TickSpeed());
// 	str_time(Time, TIME_HOURS, aBufTime, sizeof(aBufTime));
// 	str_format(aBuf, sizeof(aBuf), "%s current race time is %s", aBufName, aBufTime);
// 	pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "time", aBuf);
// }

// void CGameContext::ConSayTimeAll(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;
// 	if(!CheckClientID(pResult->m_ClientID))
// 		return;

// 	CPlayer *pPlayer = pSelf->m_apPlayers[pResult->m_ClientID];
// 	if(!pPlayer)
// 		return;
// 	CCharacter *pChr = pPlayer->GetCharacter();
// 	if(!pChr)
// 		return;
// 	if(pChr->m_DDRaceState != DDRACE_STARTED)
// 		return;

// 	char aBufTime[32];
// 	char aBuf[64];
// 	int64 Time = (int64)100 * (float)(pSelf->Server()->Tick() - pChr->m_StartTime) / ((float)pSelf->Server()->TickSpeed());
// 	const char *pName = pSelf->Server()->ClientName(pResult->m_ClientID);
// 	str_time(Time, TIME_HOURS, aBufTime, sizeof(aBufTime));
// 	str_format(aBuf, sizeof(aBuf), "%s\'s current race time is %s", pName, aBufTime);
// 	pSelf->SendChat(-1, CGameContext::CHAT_ALL, aBuf, pResult->m_ClientID);
// }

// void CGameContext::ConTime(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;
// 	if(!CheckClientID(pResult->m_ClientID))
// 		return;

// 	CPlayer *pPlayer = pSelf->m_apPlayers[pResult->m_ClientID];
// 	if(!pPlayer)
// 		return;
// 	CCharacter *pChr = pPlayer->GetCharacter();
// 	if(!pChr)
// 		return;

// 	char aBufTime[32];
// 	char aBuf[64];
// 	int64 Time = (int64)100 * (float)(pSelf->Server()->Tick() - pChr->m_StartTime) / ((float)pSelf->Server()->TickSpeed());
// 	str_time(Time, TIME_HOURS, aBufTime, sizeof(aBufTime));
// 	str_format(aBuf, sizeof(aBuf), "Your time is %s", aBufTime);
// 	pSelf->SendBroadcast(aBuf, pResult->m_ClientID);
// }

// static const char s_aaMsg[4][128] = {"game/round timer.", "broadcast.", "both game/round timer and broadcast.", "racetime."};

// void CGameContext::ConSetTimerType(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;

// 	if(!CheckClientID(pResult->m_ClientID))
// 		return;

// 	CPlayer *pPlayer = pSelf->m_apPlayers[pResult->m_ClientID];
// 	if(!pPlayer)
// 		return;

// 	char aBuf[128];

// 	if(pResult->NumArguments() > 0)
// 	{
// 		int OldType = pPlayer->m_TimerType;
// 		bool Result = false;

// 		if(str_comp_nocase(pResult->GetString(0), "default") == 0)
// 			Result = pPlayer->SetTimerType(CPlayer::TIMERTYPE_DEFAULT);
// 		else if(str_comp_nocase(pResult->GetString(0), "gametimer") == 0)
// 			Result = pPlayer->SetTimerType(CPlayer::TIMERTYPE_GAMETIMER);
// 		else if(str_comp_nocase(pResult->GetString(0), "broadcast") == 0)
// 			Result = pPlayer->SetTimerType(CPlayer::TIMERTYPE_BROADCAST);
// 		else if(str_comp_nocase(pResult->GetString(0), "both") == 0)
// 			Result = pPlayer->SetTimerType(CPlayer::TIMERTYPE_GAMETIMER_AND_BROADCAST);
// 		else if(str_comp_nocase(pResult->GetString(0), "none") == 0)
// 			Result = pPlayer->SetTimerType(CPlayer::TIMERTYPE_NONE);
// 		else
// 		{
// 			pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "timer", "Unknown parameter. Accepted values: default, gametimer, broadcast, both, none");
// 			return;
// 		}

// 		if(!Result)
// 		{
// 			pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "timer", "Selected timertype is not supported by your client");
// 			return;
// 		}

// 		if((OldType == CPlayer::TIMERTYPE_BROADCAST || OldType == CPlayer::TIMERTYPE_GAMETIMER_AND_BROADCAST) && (pPlayer->m_TimerType == CPlayer::TIMERTYPE_GAMETIMER || pPlayer->m_TimerType == CPlayer::TIMERTYPE_NONE))
// 			pSelf->SendBroadcast("", pResult->m_ClientID);
// 	}

// 	if(pPlayer->m_TimerType <= CPlayer::TIMERTYPE_SIXUP && pPlayer->m_TimerType >= CPlayer::TIMERTYPE_GAMETIMER)
// 		str_format(aBuf, sizeof(aBuf), "Timer is displayed in %s", s_aaMsg[pPlayer->m_TimerType]);
// 	else if(pPlayer->m_TimerType == CPlayer::TIMERTYPE_NONE)
// 		str_format(aBuf, sizeof(aBuf), "Timer isn't displayed.");

// 	pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "timer", aBuf);
// }

// void CGameContext::ConRescue(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;
// 	if(!CheckClientID(pResult->m_ClientID))
// 		return;
// 	CPlayer *pPlayer = pSelf->m_apPlayers[pResult->m_ClientID];
// 	if(!pPlayer)
// 		return;
// 	CCharacter *pChr = pPlayer->GetCharacter();
// 	if(!pChr)
// 		return;

// 	CGameTeams &Teams = ((CGameControllerDDRace *)pSelf->m_pController)->m_Teams;
// 	int Team = Teams.m_Core.Team(pResult->m_ClientID);
// 	if(!g_Config.m_SvRescue && !Teams.IsPractice(Team))
// 	{
// 		pSelf->SendChatTarget(pPlayer->GetCID(), "Rescue is not enabled on this server and you're not in a team with /practice turned on. Note that you can't earn a rank with practice enabled.");
// 		return;
// 	}

// 	pChr->Rescue();
// }

// void CGameContext::ConProtectedKill(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;
// 	if(!CheckClientID(pResult->m_ClientID))
// 		return;
// 	CPlayer *pPlayer = pSelf->m_apPlayers[pResult->m_ClientID];
// 	if(!pPlayer)
// 		return;
// 	CCharacter *pChr = pPlayer->GetCharacter();
// 	if(!pChr)
// 		return;

// 	int CurrTime = (pSelf->Server()->Tick() - pChr->m_StartTime) / pSelf->Server()->TickSpeed();
// 	if(g_Config.m_SvKillProtection != 0 && CurrTime >= (60 * g_Config.m_SvKillProtection) && pChr->m_DDRaceState == DDRACE_STARTED)
// 	{
// 		pPlayer->KillCharacter(WEAPON_SELF);
// 	}
// }

// void CGameContext::ConPoints(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;
// 	if(!CheckClientID(pResult->m_ClientID))
// 		return;

// 	if(pResult->NumArguments() > 0)
// 	{
// 		if(!g_Config.m_SvHideScore)
// 			pSelf->Score()->ShowPoints(pResult->m_ClientID, pResult->GetString(0));
// 		else
// 			pSelf->Console()->Print(
// 				IConsole::OUTPUT_LEVEL_STANDARD,
// 				"points",
// 				"Showing the global points of other players is not allowed on this server.");
// 	}
// 	else
// 		pSelf->Score()->ShowPoints(pResult->m_ClientID,
// 			pSelf->Server()->ClientName(pResult->m_ClientID));
// }

// void CGameContext::ConTopPoints(IConsole::IResult *pResult, void *pUserData)
// {
// 	CGameContext *pSelf = (CGameContext *)pUserData;
// 	if(!CheckClientID(pResult->m_ClientID))
// 		return;

// 	if(g_Config.m_SvHideScore)
// 	{
// 		pSelf->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "toppoints",
// 			"Showing the global top points is not allowed on this server.");
// 		return;
// 	}

// 	if(pResult->NumArguments() > 0)
// 		pSelf->Score()->ShowTopPoints(pResult->m_ClientID, pResult->GetInteger(0));
// 	else
// 		pSelf->Score()->ShowTopPoints(pResult->m_ClientID);
// }
