class DZLMedicHelpMenu : DZLBaseMenu
{
	private ButtonWidget killButton;
	private ButtonWidget healButton;
	private ButtonWidget hospitalButton;

    void DZLMedicHelpMenu() {
        Construct();
    }
    void ~DZLMedicHelpMenu() {
        Destruct();
    }

    override Widget Init() {
        layoutPath = "DayZLife/layout/MedicHelp/MedicHelp.layout";
        super.Init();

        killButton = creator.GetButtonWidget("KillButton");
        healButton = creator.GetButtonWidget("HealButton");
        hospitalButton = creator.GetButtonWidget("HealButton");

        return layoutRoot;
    }

    override bool OnClick(Widget w, int x, int y, int button) {
        if (super.OnClick(w, x, y, button)) return true;

        if (w == killButton) {
            GetGame().RPCSingleParam(player, DAY_Z_LIFE_EVENT_MEDIC_KILL_PLAYER, new Param1<PlayerBase>(player), true);
            player.willDie = true;
            OnHide();
        } else if (w == healButton) {
			GetGame().RPCSingleParam(player, DAY_Z_LIFE_EVENT_MEDIC_HEAL_PLAYER, new Param1<PlayerBase>(player), true);
			player.willHealByMedic = true;
			OnHide();
		} else if (w == hospitalButton) {
			GetGame().RPCSingleParam(player, DAY_Z_LIFE_EVENT_HOSPITAL_HEAL_PLAYER, new Param1<PlayerBase>(player), true);
			player.willHealByHospital = true;
			OnHide();
		}

        return false;
    }

}