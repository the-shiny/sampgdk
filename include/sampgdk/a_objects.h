/* Copyright (C) 2011-2012 Zeex
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SAMPGDK_A_OBJECTS_H
#define SAMPGDK_A_OBJECTS_H

#include <sampgdk/a_samp.h>
#include <sampgdk/bool.h>
#include <sampgdk/export.h>

#include <sampgdk/a_objects-decl.h>

#ifdef __cplusplus

#include <cassert>
#include <cmath>
#include <string>

class Object {
public:
	// Construct from an object ID
	Object(int objectid) : id_(objectid) { assert(id_ != INVALID_OBJECT_ID); }

	// Implicit convertion to 'int'
	operator int() const { return id_; }

	// Explicit ID request
	int GetId() const { return id_; }

	// Sort of factory method
	static Object Create(int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance = 0.0f) {
		return ::CreateObject(modelid, x, y, z, rX, rY, rZ, DrawDistance);
	}
	
	bool AttachToVehicle(int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ) const {
		return ::AttachObjectToVehicle(id_, vehicleid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ);
	}
	bool AttachToObject(int objectid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, bool SyncRotation = true) const {
		return ::AttachObjectToObject(id_, objectid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, SyncRotation);
	}
	bool AttachToPlayer(int playerid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ) const {
		return ::AttachObjectToPlayer(id_, playerid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ);
	}
	bool SetPos(float x, float y, float z) const
		{ return ::SetObjectPos(id_, x, y, z); } 
	bool GetPos(float *x, float *y, float *z) const
		{ return ::GetObjectPos(id_, x, y, z); } 
	bool GetPos(float &x, float &y, float &z) const
		{ return ::GetObjectPos(id_, &x, &y, &z); } 
	bool SetRot(float rotX, float rotY, float rotZ) const
		{ return ::SetObjectRot(id_, rotX, rotY, rotZ); }
	bool GetRot(float *rotX, float *rotY, float *rotZ) const
		{ return ::GetObjectRot(id_, rotX, rotY, rotZ); }
	bool GetRot(float &rotX, float &rotY, float &rotZ) const
		{ return ::GetObjectRot(id_, &rotX, &rotY, &rotZ); }
	bool IsValid() const 
		{ return ::IsValidObject(id_); }
	bool Destroy() const
		{ return ::DestroyObject(id_); }
	int Move(float X, float Y, float Z, float Speed, float RotX = -1000.0f, float RotY = -1000.0f, float RotZ = -1000.0f) const
		{ return ::MoveObject(id_, X, Y, Z, Speed, RotX, RotY, RotZ); }
	bool Stop() const
		{ return ::StopObject(id_); }
	bool IsMoving() const 
		{ return ::IsObjectMoving(id_); }
	bool SetMaterial(int materialindex, int modelid, const char *txdname, const char *texturename, int materialcolor = 0) 
		{ return ::SetObjectMaterial(id_, materialindex, modelid, txdname, texturename, materialcolor); }
	bool SetMaterialText(const char *text, int materialindex = 0, int materialsize = OBJECT_MATERIAL_SIZE_256x128, const char *fontface = "Arial", int fontsize = 24, bool bold = true, int fontcolor = 0xFFFFFFFF, int backcolor = 0, int textalignment = OBJECT_MATERIAL_TEXT_ALIGN_LEFT)
		{ return ::SetObjectMaterialText(id_, text, materialindex, materialsize, fontface, fontsize, bold, fontcolor, backcolor, textalignment); }

private:
	const int id_;
};

class PlayerObject {
public:
	// Construct from a player ID and an object ID
	PlayerObject(int playerid, int objectid) 
		: playerid_(playerid)
		, objectid_(objectid) 
	{
		assert(objectid_ != INVALID_OBJECT_ID);
		assert(playerid_ != INVALID_PLAYER_ID);
	}

	// Explicit ID request
	int GetPlayerId() const { return playerid_; }
	int GetObjectId() const { return objectid_; }

	// Sort of factory method
	static PlayerObject Create(int playerid, int modelid, float x, float y, float z, float rX, float rY, float rZ, float DrawDistance = 0.0f) {
		return PlayerObject(playerid, ::CreatePlayerObject(playerid, modelid, x, y, z, rX, rY, rZ, DrawDistance));
	}
	
	bool AttachToPlayer(int playerid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ) const {
		return ::AttachPlayerObjectToPlayer(playerid_, objectid_, playerid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ);
	}
	bool AttachToVehicle(int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ) const {
		return ::AttachPlayerObjectToVehicle(playerid_, objectid_, vehicleid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ);
	}
	bool SetPos(float x, float y, float z) const
		{ return ::SetPlayerObjectPos(playerid_, objectid_, x, y, z); } 
	bool GetPos(float *x, float *y, float *z) const
		{ return ::GetPlayerObjectPos(playerid_, objectid_, x, y, z); } 
	bool GetPos(float &x, float &y, float &z) const
		{ return ::GetPlayerObjectPos(playerid_, objectid_, &x, &y, &z); } 
	bool SetRot(float rotX, float rotY, float rotZ) const
		{ return ::SetPlayerObjectRot(playerid_, objectid_, rotX, rotY, rotZ); }
	bool GetRot(float *rotX, float *rotY, float *rotZ) const
		{ return ::GetPlayerObjectRot(playerid_, objectid_, rotX, rotY, rotZ); }
	bool GetRot(float &rotX, float &rotY, float &rotZ) const
		{ return ::GetPlayerObjectRot(playerid_, objectid_, &rotX, &rotY, &rotZ); }
	bool IsValid() const 
		{ return ::IsValidPlayerObject(playerid_, objectid_); }
	bool Destroy() const
		{ return ::DestroyPlayerObject(playerid_, objectid_); }
	int Move(float X, float Y, float Z, float Speed, float RotX = -1000.0f, float RotY = -1000.0f, float RotZ = -1000.0f) const
		{ return ::MovePlayerObject(playerid_, objectid_, X, Y, Z, Speed, RotX, RotY, RotZ); }
	bool Stop() const
		{ return ::StopPlayerObject(playerid_, objectid_); }
	bool IsMoving() const 
		{ return ::IsPlayerObjectMoving(playerid_, objectid_); }
	bool SetMaterial(int materialindex, int modelid, const char *txdname, const char *texturename, int materialcolor = 0) 
		{ return ::SetPlayerObjectMaterial(playerid_, objectid_, materialindex, modelid, txdname, texturename, materialcolor); }
	bool SetMaterialText(const char *text, int materialindex = 0, int materialsize = OBJECT_MATERIAL_SIZE_256x128, const char *fontface = "Arial", int fontsize = 24, bool bold = true, int fontcolor = 0xFFFFFFFF, int backcolor = 0, int textalignment = OBJECT_MATERIAL_TEXT_ALIGN_LEFT)
		{ return ::SetPlayerObjectMaterialText(playerid_, objectid_, text, materialindex, materialsize, fontface, fontsize, bold, fontcolor, backcolor, textalignment); }

private:
	const int playerid_;
	const int objectid_;
};

#endif /* __cplusplus */

#endif /* !SAMPGDK_A_OBJECTS_H */
