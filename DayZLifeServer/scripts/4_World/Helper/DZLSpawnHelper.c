class DZLSpawnHelper
{

    static bool SpawnContainer(vector position, vector orientation, string gameObjectName) {
        Container_Base obj = Container_Base.Cast(GetGame().CreateObject(gameObjectName, position));
        if (!obj) {
            return false;
        }

        obj.SetFlags(EntityFlags.STATIC, false);
        DZLSpawnHelper.SetPositionAndOrientation(obj, position, orientation);

		return true;
    }

    static PlayerBase SpawnActionPoint(vector pos, vector orientation, string gameObjectName, bool isBanking, bool isLicence) {
        pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
        Object game_obj = GetGame().CreateObject(gameObjectName, pos, false, false, true );
        if (!game_obj) {
           return null;
        }

        PlayerBase char = PlayerBase.Cast(game_obj);

        char.SetAllowDamage(false);
        DZLSpawnHelper.SetPositionAndOrientation(char, pos, orientation);
        char.IsDZLBank = isBanking;
        char.IsLicencePoint = isLicence;

        return char;
    }

    static void SetPositionAndOrientation(Entity game_obj, vector position, vector orientation) {
        game_obj.SetPosition(position);
        game_obj.SetOrientation(orientation);
        game_obj.SetOrientation(game_obj.GetOrientation()); //Collision fix
        game_obj.Update();
        game_obj.SetAffectPathgraph(true, false);
        if( game_obj.CanAffectPathgraph() ) {
            GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( GetGame().UpdatePathgraphRegionByObject, 100, false, game_obj );
        }
    }
}