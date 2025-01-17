class DZLPayCheck
{
    static void Check(PlayerBase player, DZLPaycheckConfig config) {
        int amount = 0;
        int onlineTime = 100000000;
        DZLPlayer dzlPlayer = player.GetDZLPlayer();
        DZLPaycheck payCheck = DZLRankHelper.getCurrentPayCheck(dzlPlayer, DZLConfig.Get().jobConfig.paycheck);
        amount = payCheck.amount;
        onlineTime = payCheck.onlineMinutesForPay;

        if (amount > 0) {
            dzlPlayer.UpdateOnlineTime();
            if(dzlPlayer.GetActiveOnlineTime() >= onlineTime) {
                dzlPlayer.ResetOnlineTime();
                DZLDatabaseLayer.Get().GetBank().AddMoney(amount);
                dzlPlayer.AddMoneyToPlayerBank(amount);
                GetGame().RPCSingleParam(null, DAY_Z_LIFE_EVENT_CLIENT_SHOULD_REQUEST_PLAYER_BASE, null, true, player.GetIdentity());
                DZLSendMessage(player.GetIdentity(), "#you_recive_a_paycheck: " + amount);
            }
        }
    }
}
