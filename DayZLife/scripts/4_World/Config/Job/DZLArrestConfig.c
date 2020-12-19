class DZLArrestConfig
{
	string version = "1";

	bool shouldDeleteAllItemsOnPrissoner = true;
	bool shouldDeleteAllItemsOnExPrissoner = true;
	ref array<string> prisonerItems;
	ref array<string> exPrisonerItems;
	ref array<vector> arrestAreas;
	ref array<vector> exPrisonerAreas;
	int arrestAreaRadius = 10;

    void DZLArrestConfig() {
        if (!Load()) {
            prisonerItems = new array<string>;
            prisonerItems.Insert("Pickaxe");

            exPrisonerItems = new array<string>;
            exPrisonerItems.Insert("Crowbar");

            arrestAreas = new array<vector>;
			arrestAreas.Insert("4665.000000 339.282990 10305.000000");

            exPrisonerAreas = new array<vector>;
			exPrisonerAreas.Insert("4645.000000 339.282990 10305.000000");

            Save();
        }
    }

    private bool Load(){
        if (GetGame().IsServer() && FileExist(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "arrest.json")) {
            JsonFileLoader<DZLArrestConfig>.JsonLoadFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "arrest.json", this);
            return true;
        }
        return false;
    }

    private void Save(){
        if (GetGame().IsServer()) {
            CheckDZLConfigPath();
            JsonFileLoader<DZLArrestConfig>.JsonSaveFile(DAY_Z_LIFE_SERVER_FOLDER_CONFIG + "arrest.json", this);
        }
    }
}
