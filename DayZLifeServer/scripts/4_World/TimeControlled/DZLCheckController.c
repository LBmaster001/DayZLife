class DZLCheckController
{
    DZLConfig config;
    private int countRun;

    void DZLCheckController() {
        config = DZLConfig.Get();
    }
	
	void Check() {
	    ++countRun;
	    if (!DZLLicenceCheck.Get().HasActiveLicence(null)) return;
        array<Man> allPlayers = new array<Man>;
        GetGame().GetPlayers(allPlayers);

        foreach(Man playerMan: allPlayers) {
			PlayerBase player = PlayerBase.Cast(playerMan);
			if (!player) continue;
			PlayerIdentity playerIdent = player.GetIdentity();

			if (countRun == 30) {
                DZLPayCheck.Check(player, config.jobConfig.paycheck);
                countRun = 0;
			}

			DZLMedicHealth.CheckHealth(player, playerIdent);
        }
	}
}
