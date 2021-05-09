/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include "projectile.h"
#include <game/generated/protocol.h>
#include <game/server/gamecontext.h>
#include <game/server/player.h>
#include <game/version.h>

#include <engine/shared/config.h>
#include <game/server/teams.h>

#include "character.h"

CProjectile::CProjectile(
	CGameWorld *pGameWorld,
	int Type,
	int Owner,
	vec2 Pos,
	vec2 Dir,
	float Radius,
	int Span,
	FProjectileImpactCallback Callback,
	int Layer,
	int Number) :
	CEntity(pGameWorld, CGameWorld::ENTTYPE_PROJECTILE)
{
	m_Type = Type;
	m_Pos = Pos;
	m_Direction = Dir;
	m_LifeSpan = Span;
	m_Owner = Owner;
	m_Callback = Callback;
	m_Radius = Radius;
	m_StartTick = Server()->Tick();

	m_Hit = 0;
	if(m_Owner >= 0)
	{
		CCharacter *pOwnerChar = GameServer()->GetPlayerChar(m_Owner);
		if(pOwnerChar)
		{
			m_Hit = pOwnerChar->m_Hit;
			m_IsSolo = Teams()->m_Core.GetSolo(m_Owner);
		}
	}

	m_Layer = Layer;
	m_Number = Number;

	m_TuneZone = GameServer()->Collision()->IsTune(GameServer()->Collision()->GetMapIndex(m_Pos));
	m_HitMask = 0;
	GameWorld()->InsertEntity(this);
}

void CProjectile::Reset()
{
	if(m_LifeSpan > -2)
		GameWorld()->DestroyEntity(this);
}

void CProjectile::GetProjectileProperties(float *pCurvature, float *pSpeed)
{
	switch(m_Type)
	{
	case WEAPON_GRENADE:
		if(!m_TuneZone)
		{
			*pCurvature = GameServer()->Tuning()->m_GrenadeCurvature;
			*pSpeed = GameServer()->Tuning()->m_GrenadeSpeed;
		}
		else
		{
			*pCurvature = GameServer()->TuningList()[m_TuneZone].m_GrenadeCurvature;
			*pSpeed = GameServer()->TuningList()[m_TuneZone].m_GrenadeSpeed;
		}

		break;

	case WEAPON_SHOTGUN:
		if(!m_TuneZone)
		{
			*pCurvature = GameServer()->Tuning()->m_ShotgunCurvature;
			*pSpeed = GameServer()->Tuning()->m_ShotgunSpeed;
		}
		else
		{
			*pCurvature = GameServer()->TuningList()[m_TuneZone].m_ShotgunCurvature;
			*pSpeed = GameServer()->TuningList()[m_TuneZone].m_ShotgunSpeed;
		}

		break;

	case WEAPON_GUN:
		if(!m_TuneZone)
		{
			*pCurvature = GameServer()->Tuning()->m_GunCurvature;
			*pSpeed = GameServer()->Tuning()->m_GunSpeed;
		}
		else
		{
			*pCurvature = GameServer()->TuningList()[m_TuneZone].m_GunCurvature;
			*pSpeed = GameServer()->TuningList()[m_TuneZone].m_GunSpeed;
		}
		break;
	}
}

vec2 CProjectile::GetPos(float Time)
{
	float Curvature = 0;
	float Speed = 0;
	GetProjectileProperties(&Curvature, &Speed);
	return CalcPos(m_Pos, m_Direction, Curvature, Speed, Time);
}

void CProjectile::Tick()
{
	float Pt = (Server()->Tick() - m_StartTick - 1) / (float)Server()->TickSpeed();
	float Ct = (Server()->Tick() - m_StartTick) / (float)Server()->TickSpeed();
	vec2 PrevPos = GetPos(Pt);
	vec2 CurPos = GetPos(Ct);
	vec2 ColPos;
	vec2 NewPos;
	int Collide = GameServer()->Collision()->IntersectLine(PrevPos, CurPos, &ColPos, &NewPos);
	CCharacter *pOwnerChar = nullptr;
	CPlayer *pOwnerPlayer = nullptr;

	if(m_Owner >= 0)
	{
		pOwnerChar = GameServer()->GetPlayerChar(m_Owner);
		pOwnerPlayer = GameServer()->m_apPlayers[m_Owner];
	}

	std::list<CCharacter *> pTargetChars;

	// solo bullet can't interact with
	if(!m_IsSolo && ((m_Type == WEAPON_GRENADE && !(m_Hit & CCharacter::DISABLE_HIT_GRENADE)) ||
				(m_Type == WEAPON_SHOTGUN && !(m_Hit & CCharacter::DISABLE_HIT_SHOTGUN)) ||
				(m_Type == WEAPON_GUN && !(m_Hit & CCharacter::DISABLE_HIT_GUN))))
		pTargetChars = GameWorld()->IntersectedCharacters(PrevPos, ColPos, m_Radius /*m_Freeze ? 1.0f : 6.0f*/, pOwnerChar, m_Owner >= 0);

	if(m_LifeSpan > -1)
		m_LifeSpan--;

	// Owner is dead, consider destroying the projectile
	if((!pOwnerChar || !pOwnerChar->IsAlive()) && m_Owner >= 0 && (m_IsSolo || g_Config.m_SvDestroyBulletsOnDeath))
	{
		GameWorld()->DestroyEntity(this);
		return;
	}

	// Owner has gone to another reality, destroy the projectile
	if(!pOwnerPlayer || GameServer()->GetDDRaceTeam(m_Owner) != GameWorld()->Team())
	{
		GameWorld()->DestroyEntity(this);
		return;
	}

	// if(((pTargetChr && (!(m_Hit & CCharacter::DISABLE_HIT_GRENADE) || m_Owner < 0 || pTargetChr == pOwnerChar)) || Collide || GameLayerClipped(CurPos)) && !IsInvalidWeaponCollide)
	// {
	// 	if(m_Explosive /*??*/ && (!pTargetChr || (pTargetChr && !m_Freeze)))
	// 	{
	// 		GameWorld()->CreateExplosion(ColPos, m_Owner, m_Type, m_Damage, m_Owner < 0);
	// 		GameWorld()->CreateSound(ColPos, m_SoundImpact);
	// 	}
	// 	else if(m_Freeze)
	// 	{
	// 		CCharacter *apEnts[MAX_CLIENTS];
	// 		int Num = GameWorld()->FindEntities(CurPos, 1.0f, (CEntity **)apEnts, MAX_CLIENTS, CGameWorld::ENTTYPE_CHARACTER);
	// 		for(int i = 0; i < Num; ++i)
	// 			if(apEnts[i] && (m_Layer != LAYER_SWITCH || (m_Layer == LAYER_SWITCH && m_Number > 0 && GameServer()->Collision()->m_pSwitchers[m_Number].m_Status[apEnts[i]->Team()])))
	// 				apEnts[i]->Freeze();
	// 	}

	// 	if(pOwnerChar && !GameLayerClipped(ColPos) &&
	// 		((m_Type == WEAPON_GRENADE && pOwnerChar->HasTelegunGrenade()) || (m_Type == WEAPON_GUN && pOwnerChar->HasTelegunGun())))
	// 	{
	// 		int MapIndex = GameServer()->Collision()->GetPureMapIndex(pTargetChr ? pTargetChr->m_Pos : ColPos);
	// 		int TileFIndex = GameServer()->Collision()->GetFTileIndex(MapIndex);
	// 		bool IsSwitchTeleGun = GameServer()->Collision()->IsSwitch(MapIndex) == TILE_ALLOW_TELE_GUN;
	// 		bool IsBlueSwitchTeleGun = GameServer()->Collision()->IsSwitch(MapIndex) == TILE_ALLOW_BLUE_TELE_GUN;

	// 		if(IsSwitchTeleGun || IsBlueSwitchTeleGun)
	// 		{
	// 			// Delay specifies which weapon the tile should work for.
	// 			// Delay = 0 means all.
	// 			int delay = GameServer()->Collision()->GetSwitchDelay(MapIndex);

	// 			if(delay == 1 && m_Type != WEAPON_GUN)
	// 				IsSwitchTeleGun = IsBlueSwitchTeleGun = false;
	// 			if(delay == 2 && m_Type != WEAPON_GRENADE)
	// 				IsSwitchTeleGun = IsBlueSwitchTeleGun = false;
	// 			if(delay == 3 && m_Type != WEAPON_LASER)
	// 				IsSwitchTeleGun = IsBlueSwitchTeleGun = false;
	// 		}

	// 		if(TileFIndex == TILE_ALLOW_TELE_GUN || TileFIndex == TILE_ALLOW_BLUE_TELE_GUN || IsSwitchTeleGun || IsBlueSwitchTeleGun || pTargetChr)
	// 		{
	// 			bool Found;
	// 			vec2 PossiblePos;

	// 			if(!Collide)
	// 				Found = GetNearestAirPosPlayer(pTargetChr ? pTargetChr->m_Pos : ColPos, &PossiblePos);
	// 			else
	// 				Found = GetNearestAirPos(NewPos, CurPos, &PossiblePos);

	// 			if(Found)
	// 			{
	// 				pOwnerChar->m_TeleGunPos = PossiblePos;
	// 				pOwnerChar->m_TeleGunTeleport = true;
	// 				pOwnerChar->m_IsBlueTeleGunTeleport = TileFIndex == TILE_ALLOW_BLUE_TELE_GUN || IsBlueSwitchTeleGun;
	// 			}
	// 		}
	// 	}
	// 	else if(m_Type == WEAPON_GUN)
	// 	{
	// 		if(pTargetChr)
	// 			pTargetChr->TakeDamage(m_Direction * maximum(0.001f, m_Force), m_Damage, m_Owner, m_Type);
	// 		GameWorld()->DestroyEntity(this);
	// 		return;
	// 	}
	// 	else if(m_Type == WEAPON_SHOTGUN)
	// 	{
	// 		if(!m_Freeze)
	// 		{
	// 			if(pTargetChr)
	// 				pTargetChr->TakeDamage(m_Direction * maximum(0.001f, m_Force), m_Damage, m_Owner, m_Type);
	// 			GameWorld()->DestroyEntity(this);
	// 			return;
	// 		}
	// 	}
	// 	else
	// 	{
	// 		GameWorld()->DestroyEntity(this);
	// 		return;
	// 	}
	// }

	if(m_Callback)
	{
		for(auto pChar : pTargetChars)
		{
			if(!pChar->IsAlive() || (m_HitMask & pChar->GetPlayer()->GetCID()))
				continue;

			m_HitMask |= pChar->GetPlayer()->GetCID();
			if(m_Callback(this, ColPos, pChar, false))
			{
				GameWorld()->DestroyEntity(this);
				return;
			}
		}

		if(Collide || GameLayerClipped(CurPos))
		{
			if(m_Callback(this, ColPos, nullptr, false))
			{
				GameWorld()->DestroyEntity(this);
				return;
			}
		}
	}

	if(Collide && m_Bouncing != 0)
	{
		m_StartTick = Server()->Tick();
		m_Pos = NewPos + (-(m_Direction * 4));
		if(m_Bouncing == 1)
			m_Direction.x = -m_Direction.x;
		else if(m_Bouncing == 2)
			m_Direction.y = -m_Direction.y;
		if(fabs(m_Direction.x) < 1e-6)
			m_Direction.x = 0;
		if(fabs(m_Direction.y) < 1e-6)
			m_Direction.y = 0;
		m_Pos += m_Direction;
		if(m_Callback)
			m_Callback(this, ColPos, nullptr, false);
	}

	if(m_LifeSpan == -1)
	{
		// if(m_Explosive)
		// {
		// 	if(m_Owner >= 0)
		// 		pOwnerChar = GameServer()->GetPlayerChar(m_Owner);

		// 	GameWorld()->CreateExplosion(ColPos, m_Owner, m_Type, m_Damage, m_Owner < 0);
		// 	GameWorld()->CreateSound(ColPos, m_SoundImpact);
		// }
		if(m_Callback)
			m_Callback(this, ColPos, nullptr, true);
		GameWorld()->DestroyEntity(this);
		return;
	}

	// Projectile Tele
	int x = GameServer()->Collision()->GetIndex(PrevPos, CurPos);
	int z;
	if(g_Config.m_SvOldTeleportWeapons)
		z = GameServer()->Collision()->IsTeleport(x);
	else
		z = GameServer()->Collision()->IsTeleportWeapon(x);

	if(z && GameServer()->Collision()->NumTeles(z - 1))
	{
		m_Pos = GameServer()->Collision()->TelePos(z - 1);
		m_StartTick = Server()->Tick();
	}
}

void CProjectile::TickPaused()
{
	++m_StartTick;
}

void CProjectile::FillInfo(CNetObj_Projectile *pProj)
{
	pProj->m_X = (int)m_Pos.x;
	pProj->m_Y = (int)m_Pos.y;
	pProj->m_VelX = (int)(m_Direction.x * 100.0f);
	pProj->m_VelY = (int)(m_Direction.y * 100.0f);
	pProj->m_StartTick = m_StartTick;
	pProj->m_Type = m_Type;
}

void CProjectile::Snap(int SnappingClient, int OtherMode)
{
	float Ct = (Server()->Tick() - m_StartTick) / (float)Server()->TickSpeed();

	if(NetworkClipped(SnappingClient, GetPos(Ct)))
		return;

	// don't snap projectiles that is disowned for other mode
	if(m_Owner == -2 && OtherMode)
		return;

	int Tick = (Server()->Tick() % Server()->TickSpeed()) % 10;
	if(m_Layer == LAYER_SWITCH && m_Number > 0 && !GameServer()->Collision()->m_pSwitchers[m_Number].m_Status[GameWorld()->Team()] && (!Tick))
		return;

	int SnappingClientVersion = SnappingClient >= 0 ? GameServer()->GetClientVersion(SnappingClient) : CLIENT_VERSIONNR;

	CNetObj_DDNetProjectile DDNetProjectile;
	if(SnappingClientVersion >= VERSION_DDNET_ANTIPING_PROJECTILE && (GameWorld()->Team() != Teams()->m_Core.Team(SnappingClient) || m_Bouncing) && FillExtraInfo(&DDNetProjectile))
	{
		int Type = SnappingClientVersion < VERSION_DDNET_MSG_LEGACY ? (int)NETOBJTYPE_PROJECTILE : NETOBJTYPE_DDNETPROJECTILE;
		void *pProj = Server()->SnapNewItem(Type, GetID(), sizeof(DDNetProjectile));
		if(!pProj)
		{
			return;
		}
		mem_copy(pProj, &DDNetProjectile, sizeof(DDNetProjectile));
	}
	else
	{
		CNetObj_Projectile *pProj = static_cast<CNetObj_Projectile *>(Server()->SnapNewItem(NETOBJTYPE_PROJECTILE, GetID(), sizeof(CNetObj_Projectile)));
		if(!pProj)
		{
			return;
		}
		FillInfo(pProj);
	}
}

// DDRace

void CProjectile::SetBouncing(int Value)
{
	m_Bouncing = Value;
}

bool CProjectile::FillExtraInfo(CNetObj_DDNetProjectile *pProj)
{
	const int MaxPos = 0x7fffffff / 100;
	if(abs((int)m_Pos.y) + 1 >= MaxPos || abs((int)m_Pos.x) + 1 >= MaxPos)
	{
		//If the modified data would be too large to fit in an integer, send normal data instead
		return false;
	}
	//Send additional/modified info, by modifiying the fields of the netobj
	float Angle = -atan2f(m_Direction.x, m_Direction.y);

	int Data = 0;
	Data |= (abs(m_Owner) & 255) << 0;
	if(m_Owner < 0)
		Data |= PROJECTILEFLAG_NO_OWNER;
	//This bit tells the client to use the extra info
	Data |= PROJECTILEFLAG_IS_DDNET;
	// PROJECTILEFLAG_BOUNCE_HORIZONTAL, PROJECTILEFLAG_BOUNCE_VERTICAL
	Data |= (m_Bouncing & 3) << 10;
	// if(m_Explosive)
	// 	Data |= PROJECTILEFLAG_EXPLOSIVE;
	// if(m_Freeze)
	// 	Data |= PROJECTILEFLAG_FREEZE;

	pProj->m_X = (int)(m_Pos.x * 100.0f);
	pProj->m_Y = (int)(m_Pos.y * 100.0f);
	pProj->m_Angle = (int)(Angle * 1000000.0f);
	pProj->m_Data = Data;
	pProj->m_StartTick = m_StartTick;
	pProj->m_Type = m_Type;
	return true;
}