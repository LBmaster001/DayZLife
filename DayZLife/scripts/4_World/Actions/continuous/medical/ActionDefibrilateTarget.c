modded class ActionDefibrilateTarget
{

	override void OnFinishProgressServer(ActionData action_data){
		super.OnFinishProgressServer(action_data);
		DZLEmergencies emergencies = DZLDatabaseLayer.Get().GetEmergencies();
		
		PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());
		PlayerIdentity targetIdent = target.GetIdentity();

		if (!targetIdent) return;

		DZLPlayer dzlPlayer = target.GetDZLPlayer();
		string targetId = targetIdent.GetId();

		if(target && emergencies.HasEmergency(targetId)) {
		    emergencies.Remove(targetId);
		    dzlPlayer.AddMoneyToPlayerBank(DZLConfig.Get().medicConfig.priceMedicHeal * -1);
		    dzlPlayer.SetWillHealByMedic();
		    dzlPlayer.SaveItems(target);
		    action_data.m_Player.GetDZLPlayer().AddMoneyToPlayerBank(DZLConfig.Get().medicConfig.priceMedicHeal);
            target.SetCanBeDestroyed(true);
            target.SetHealth(0);
            GetGame().RPCSingleParam(target, DAY_Z_LIFE_ALL_WAS_HEALED_RESPONSE, null, true, targetIdent);
            DZLSendMessage(action_data.m_Player.GetIdentity(), "#player_travels_between_worlds");
		}
	}

}
