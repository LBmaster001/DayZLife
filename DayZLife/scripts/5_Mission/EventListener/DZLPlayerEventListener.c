class DZLPlayerEventListener
{
    private PlayerBase player;
	private ScriptCallQueue queue;

    void DZLPlayerEventListener() {
        GetDayZGame().Event_OnRPC.Insert(HandleEventsDZL);
    }

    void ~DZLPlayerEventListener() {
        GetDayZGame().Event_OnRPC.Remove(HandleEventsDZL);
    }

    void HandleEventsDZL(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx) {
        player = PlayerBaseHelper.GetPlayer();
        if (player) {
            if (rpc_type == DAY_Z_LIFE_RECEIVE_MESSAGE) {
                Param1 <string> dzlMessage;
                if (ctx.Read(dzlMessage) && dzlMessage.param1){
                    player.DisplayMessage(dzlMessage.param1);
                }
            } else if (rpc_type == DAY_Z_LIFE_RECEIVE_MEDIC_MESSAGE) {
                Param1 <string> dzlMessageMedic;
                if (ctx.Read(dzlMessageMedic) && dzlMessageMedic.param1){
                    player.DisplayMessage(dzlMessageMedic.param1);
                }
            } else if(rpc_type == DAY_Z_LIFE_HOUSE_RAID_ALARM) {
                Param3<ref DZLHouseExtension, string, PlayerBase> dzlAlarm;
                if (ctx.Read(dzlAlarm) && dzlAlarm.param1 && dzlAlarm.param2 && dzlAlarm.param3){
                     player.DisplayMessage(dzlAlarm.param1.GetMessage(dzlAlarm.param3, dzlAlarm.param2));
                }
            } else if(rpc_type == DAY_Z_LIFE_ALL_WAS_HEALED_RESPONSE) {
                player.willDie = true;
                player.CheckDeath();
                PlayerRespawn();
            } else if(rpc_type == DAY_Z_LIFE_SEND_MESSAGE_SERVER) {
                Param1<ref DZLMessage> messagesParam;
                if (ctx.Read(messagesParam) && messagesParam.param1){
                     DZLMessage receivedMessage = messagesParam.param1;
                     SEffectManager.CreateSound("DZL_Message_SoundSet", player.GetPosition()).SoundPlay();
                     player.DisplayMessage("#you_got_a_message: " + receivedMessage.GetShortText());
                     DZLMessageDB.Get().AddMessage(receivedMessage);
                     player.RefreshMessageSystem();
                }
            }
        }

        if (rpc_type == DAY_Z_LIFE_NEW_SPAWN_CLIENT) {
            queue = GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM);
            queue.CallLater(CreateSpawnMenu, 1750, true);
        }
    }

    void CreateSpawnMenu() {
        player = PlayerBaseHelper.GetPlayer();
        if (!player || !player.GetConfig() || !player.GetDZLPlayer()) {
            return;
        }

        queue = GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM);
        queue.Remove(CreateSpawnMenu);

        GetGame().GetUIManager().CloseAll();
        GetGame().GetUIManager().ShowScriptedMenu(player.GetSpawnPositionMenu(), null);
    }

    void PlayerRespawn() {
   		GetGame().GetMenuDefaultCharacterData(false).SetRandomCharacterForced(true);
   		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(GetGame().RespawnPlayer);

   		MissionGameplay missionGP = MissionGameplay.Cast(GetGame().GetMission());
   		missionGP.DestroyAllMenus();
   		missionGP.SetPlayerRespawning(true);
   		
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(GetGame().GetMission().Continue);
   	}

}
