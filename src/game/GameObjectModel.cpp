/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
 
#include "VMapFactory.h"
#include "VMapManager2.h"
#include "VMapDefinitions.h"
#include "WorldModel.h"

#include "GameObjectModel.h"
#include "Log.h"
#include "GameObject.h"
#include "Creature.h"
#include "TemporarySummon.h"
#include "Object.h"
#include "DBCStores.h"
#include "World.h"

using G3D::Vector3;
using G3D::Ray;
using G3D::AABox;

struct GameobjectModelData
{
    GameobjectModelData(const std::string& name_, const AABox& box) :
        name(name_), bound(box) {}

    AABox bound;
    std::string name;
};

typedef UNORDERED_MAP<uint32, GameobjectModelData> ModelList;
ModelList model_list;

void LoadGameObjectModelList()
{
    FILE* model_list_file = fopen((sWorld.GetDataPath() + "vmaps/" + VMAP::GAMEOBJECT_MODELS).c_str(), "rb");
    if (!model_list_file)
        return;

    uint32 name_length, displayId;
    char buff[500];
    while (!feof(model_list_file))
    {
        fread(&displayId,sizeof(uint32),1,model_list_file);
        fread(&name_length,sizeof(uint32),1,model_list_file);

        if (name_length >= sizeof(buff))
        {
            printf("\nFile '%s' seems to be corrupted", VMAP::GAMEOBJECT_MODELS);
            break;
        }

        fread(&buff, sizeof(char), name_length,model_list_file);
        Vector3 v1, v2;
        fread(&v1, sizeof(Vector3), 1, model_list_file);
        fread(&v2, sizeof(Vector3), 1, model_list_file);

        model_list.emplace(displayId, GameobjectModelData(GameobjectModelData(std::string(buff, name_length), AABox(v1, v2))));
    }
    fclose(model_list_file);
}

GameObjectModel::~GameObjectModel()
{
    if (iModel)
        ((VMAP::VMapManager2*)VMAP::VMapFactory::createOrGetVMapManager())->releaseModelInstance(name);
}

bool GameObjectModel::initialize(const GameObject& go, const GameObjectDisplayInfoEntry& info)
{
    ModelList::const_iterator it = model_list.find(info.Displayid);
    if (it == model_list.end())
        return false;

    G3D::AABox mdl_box(it->second.bound);
    // ignore models with no bounds
    if (mdl_box == G3D::AABox::zero())
    {
        std::cout << "Model " << it->second.name << " has zero bounds, loading skipped" << std::endl;
        return false;
    }

    iModel = ((VMAP::VMapManager2*)VMAP::VMapFactory::createOrGetVMapManager())->acquireModelInstance(sWorld.GetDataPath() + "vmaps/", it->second.name);

    if (!iModel)
        return false;

    name = it->second.name;
    //flags = VMAP::MOD_M2;
    //adtId = 0;
    //ID = 0;
    iPos = Vector3(go.GetPositionX(), go.GetPositionY(), go.GetPositionZ());
    iScale = go.GetFloatValue(OBJECT_FIELD_SCALE_X);
    iInvScale = 1.f / iScale;

    G3D::Matrix3 iRotation = G3D::Matrix3::fromEulerAnglesZYX(go.GetOrientation(), 0, 0);
    iInvRot = iRotation.inverse();
    // transform bounding box:
    mdl_box = AABox(mdl_box.low() * iScale, mdl_box.high() * iScale);
    AABox rotated_bounds;
    for (int i = 0; i < 8; ++i)
        rotated_bounds.merge(iRotation * mdl_box.corner(i));

    this->iBound = rotated_bounds + iPos;
#ifdef SPAWN_CORNERS
    // test:
    for (int i = 0; i < 8; ++i)
    {
        Vector3 pos(iBound.corner(i));
        if (Creature* c = const_cast<GameObject&>(go).SummonCreature(24440, pos.x, pos.y, pos.z, 0, TEMPSUMMON_MANUAL_DESPAWN))
        {
            c->setFaction(35);
            c->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.1f);
        }
    }
#endif

    return true;
}

GameObjectModel* GameObjectModel::Create(const GameObject& go)
{
    const GameObjectDisplayInfoEntry* info = sGameObjectDisplayInfoStore.LookupEntry(go.GetGOInfo()->displayId);
    if (!info)
        return NULL;

    GameObjectModel* mdl = new GameObjectModel();
    if (!mdl->initialize(go, *info))
    {
        delete mdl;
        return NULL;
    }

    return mdl;
}

bool GameObjectModel::intersectRay(const G3D::Ray& ray, float& MaxDist, bool StopAtFirstHit, uint32 /*ph_mask*/) const
{
    if (!sWorld.getConfig(CONFIG_GAMEOBJECT_COLLISION))
        return false;
    
    if (!collisionEnabled)
        return false;

    float time = ray.intersectionTime(iBound);
    if (time == G3D::inf())
        return false;

    // child bounds are defined in object space:
    Vector3 p = iInvRot * (ray.origin() - iPos) * iInvScale;
    Ray modRay(p, iInvRot * ray.direction());
    float distance = MaxDist * iInvScale;
    
    if (distance < 0.0f || distance > 50000.0f || distance < 1.0e-4) { // Our epsilon!
        sLog.outError("[CRASH ALERT] Prevented crash in GameObjectModel::intersectRay, distance was %f", distance);
        return false;
    }
    else if (distance == G3D::inf()) {
        sLog.outError("[CRASH ALERT] Prevented crash in GameObjectModel::intersectRay, distance was inf");
        return false;
    }
    
    bool hit = iModel->IntersectRay(modRay, distance, StopAtFirstHit);
    if(hit)
    {
        distance *= iScale;
        MaxDist = distance;
    }
    return hit;
}
