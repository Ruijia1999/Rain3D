#include "SceneLoader.h"
#include <map>
#include <string>
#include "EngineLog/EngineLog.h"
#include "MeshRender/MeshRender.h"
#include "Math/Math.h"
#include "ECS/Entity.h"
#include "Reflect/Reflect.h"
#include "GameObject/GameObjectSystem.h"
#include "Animation\GeneralAnimationClip.h"
#include "Animation\SklAnimClip.h"
#include "Animation/GeneralAnimationComponent.h"
#include "Animation\SklAnimationComponent.h"
#include "Transform/TransformSystem.h"
#include "Collision/ColliderSystem.h"
#include "Collision/ColliderBase.h"
#include "Application/Rain3DGame.h"
#include "Animation\AnimationSystem.h"
#include "Camera\Camera.h"
namespace {
	std::map<std::string, std::function<void(int, std::shared_ptr <Rain::ECS::Entity> i_entity, lua_State*)>> m_componentCreators;
}

void Rain::Asset::SceneLoader::LoadScene(const char* i_filePath) {
	lua_State* L = luaL_newstate();
	auto i = luaL_dofile(L, "test.lua");
#pragma region Settings
	lua_getglobal(L, "settings");
	LoadSettings(L);
	
#pragma endregion
#pragma region Entities
	lua_getglobal(L, "entities");
	int n = luaL_len(L, -1);
	for (int i = 1; i <= n; ++i) {
		lua_rawgeti(L, -1, i);
		LoadEntity(L);
		lua_pop(L, 1);
	}
#pragma endregion

	EngineLog::Log("Game scene is loaded successfully.");
}
void Rain::Asset::SceneLoader::LoadSettings(lua_State* i_luaState) {
	Math::Vector3 cameraPos;
	Math::Quaternion cameraRot;
	Math::Vector3 lightDirection;
	Math::Vector4 lightColor;

	lua_pushstring(i_luaState, "light");
	lua_gettable(i_luaState, -2);
	lua_pushstring(i_luaState, "direction");
	lua_gettable(i_luaState, -2);
	for (int i = 1; i <= 3; ++i) {
		lua_rawgeti(i_luaState, -1, i);
		lightDirection[i - 1] = lua_tonumber(i_luaState, -1);
		lua_pop(i_luaState, 1);
	}
	lua_pop(i_luaState, 1);

	lua_pushstring(i_luaState, "color");
	lua_gettable(i_luaState, -2);
	for (int i = 1; i <= 4; ++i) {
		lua_rawgeti(i_luaState, -1, i);
		lightColor[i - 1] = lua_tonumber(i_luaState, -1);
		lua_pop(i_luaState, 1);
	}
	lua_pop(i_luaState, 1);
	lua_pop(i_luaState, 1);

	Math::Vector4 backgroundColor;
	lua_pushstring(i_luaState, "background");
	lua_gettable(i_luaState, -2);
	for (int i = 1; i <= 4; ++i) {
		lua_rawgeti(i_luaState, -1, i);
		backgroundColor[i - 1] = lua_tonumber(i_luaState, -1);
		lua_pop(i_luaState, 1);
	}
	lua_pop(i_luaState, 1);

	Rain::Rain3DGame::InitializeSettings(lightColor,lightDirection, backgroundColor);
}

void Rain::Asset::SceneLoader::LoadEntity(lua_State* i_luaState) {
	int id;
	std::string script;
	std::string tag;
	std::string name;

	lua_pushstring(i_luaState, "id");
	lua_gettable(i_luaState, -2);
	id = lua_tointeger(i_luaState, -1);
	lua_pop(i_luaState, 1);


	lua_pushstring(i_luaState, "script");
	lua_gettable(i_luaState, -2);
	script = lua_tostring(i_luaState, -1);
	lua_pop(i_luaState, 1);

	lua_pushstring(i_luaState, "tag");
	lua_gettable(i_luaState, -2);
	tag = lua_tostring(i_luaState, -1);
	lua_pop(i_luaState, 1);

	lua_pushstring(i_luaState, "name");
	lua_gettable(i_luaState, -2);
	name = lua_tostring(i_luaState, -1);
	lua_pop(i_luaState, 1);

	lua_pushstring(i_luaState, "components");
	lua_gettable(i_luaState, -2);
	int n = luaL_len(i_luaState, -1);
	
	ECS::Entity* entity = Rain::Reflect::GetClass(script, id, tag, name);

	if (entity != nullptr) {
		std::shared_ptr<ECS::Entity> entityPtr(entity);
		Rain::Rain3DGame::AddEntity(entityPtr);

		for (int i = 1; i <= n; ++i) {
			lua_rawgeti(i_luaState, -1, i);
			LoadComponent(id, i_luaState,entityPtr );
			lua_pop(i_luaState, 1);
		}
		lua_pop(i_luaState, 1);
	}
	else {
		for (int i = 1; i <= n; ++i) {
			lua_rawgeti(i_luaState, -1, i);
			LoadComponent(id, i_luaState, nullptr);
			lua_pop(i_luaState, 1);
		}
		lua_pop(i_luaState, 1);
	}







}

void Rain::Asset::SceneLoader::LoadComponent(int i_id, lua_State* i_luaState, std::shared_ptr <ECS::Entity> i_entity) {
	
	
	lua_pushstring(i_luaState, "component");
	lua_gettable(i_luaState, -2);
	std::string component = lua_tostring(i_luaState, -1);
	lua_pop(i_luaState, 1);

	if (m_componentCreators.find(component) == m_componentCreators.end()) {
		std::string msg;
		msg.append("Invalid component:");
		msg.append(component);
		EngineLog::LogWarning(msg.c_str());
		return;
	}
	m_componentCreators.find(component)->second(i_id, i_entity, i_luaState);
}
void Rain::Asset::SceneLoader::RegisterComponentCreators() {
#pragma region Animation
	RegisterComponentCreator("Animation", [](int i_id, std::shared_ptr <ECS::Entity> i_entity, lua_State* i_luaState) {

		Animation::AnimationSystem* system = Animation::AnimationSystem::GetInstance();

		lua_pushstring(i_luaState, "type");
		lua_gettable(i_luaState, -2);
		std::string type = lua_tostring(i_luaState, -1);
		lua_pop(i_luaState, 1);

		lua_pushstring(i_luaState, "currentClip");
		lua_gettable(i_luaState, -2);
		std::string currentClip = lua_tostring(i_luaState, -1);
		lua_pop(i_luaState, 1);
		
		
		lua_pushstring(i_luaState, "autoPlay");
		lua_gettable(i_luaState, -2);
		bool autoPlay = lua_toboolean (i_luaState, -1);
		lua_pop(i_luaState, 1);
		
		lua_pushstring(i_luaState, "loop");
		lua_gettable(i_luaState, -2);
		bool loop = lua_toboolean(i_luaState, -1);
		lua_pop(i_luaState, 1);

		if (type == "Skeletal") {
			std::shared_ptr< Animation::SklAnimClip> clip = system->GetSkeletalClip(currentClip);
			system->AddComponent(new Animation::SklAnimationComponent(i_id, i_entity, clip, autoPlay, loop));
		}
		else if (type == "General") {
			lua_pushstring(i_luaState, "relative");
			lua_gettable(i_luaState, -2);
			bool relative = lua_toboolean(i_luaState, -1);
			lua_pop(i_luaState, 1);

			std::shared_ptr< Animation::GeneralAnimationClip> clip = system->GetGeneralClip(currentClip);
			system->AddComponent(new Animation::GeneralAnimationComponent(i_id, i_entity, clip, autoPlay, loop, relative));

		}

		}
	);
#pragma endregion
#pragma region GameObjectComponent
	RegisterComponentCreator("GameObject", [](int i_id, std::shared_ptr <ECS::Entity> i_entity, lua_State* i_luaState) {

		lua_pushstring(i_luaState, "isActive");
		lua_gettable(i_luaState, -2);
		bool isActive = lua_toboolean(i_luaState, -1);
		lua_pop(i_luaState, 1);

		lua_pushstring(i_luaState, "isVisible");
		lua_gettable(i_luaState, -2);
		bool isVisible = lua_toboolean(i_luaState, -1);
		lua_pop(i_luaState, 1);

		GameObject::GameObjectSystem::GetInstance()->AddComponent(new GameObject::GameObjectComponent(i_id, i_entity, isActive,isVisible,"name","tag"));

		}
	);
#pragma endregion

#pragma region TransformComponent
	RegisterComponentCreator("Transform", [](int i_id, std::shared_ptr <ECS::Entity> i_entity, lua_State* i_luaState) {
		Math::Vector3 position;
		lua_pushstring(i_luaState, "position");
		lua_gettable(i_luaState, -2);
		for (int i = 1; i <= 3; ++i) {
			lua_rawgeti(i_luaState, -1, i);
			position[i-1] = lua_tonumber(i_luaState,-1); 
			lua_pop(i_luaState, 1);
		}
		lua_pop(i_luaState, 1);

		Math::Quaternion rotation;
		lua_pushstring(i_luaState, "rotation");
		lua_gettable(i_luaState, -2);
		for (int i = 1; i <= 4; ++i) {
			lua_rawgeti(i_luaState, -1, i);
			rotation[i - 1] = lua_tonumber(i_luaState, -1);
			lua_pop(i_luaState, 1);
		}
		lua_pop(i_luaState, 1);

		Math::Vector3 scale;
		lua_pushstring(i_luaState, "scale");
		lua_gettable(i_luaState, -2);
		for (int i = 1; i <= 3; ++i) {
			lua_rawgeti(i_luaState, -1, i);
			scale[i - 1] = lua_tonumber(i_luaState, -1);
			lua_pop(i_luaState, 1);
		}
		lua_pop(i_luaState, 1);

		Transform::TransformSystem::GetInstance()->AddComponent(new Transform::TransformComponent(i_id, i_entity, position,scale,rotation));
		}
	);
#pragma endregion

#pragma region MeshRender
	RegisterComponentCreator("MeshRender", [](int i_id, std::shared_ptr <ECS::Entity> i_entity, lua_State* i_luaState) {
		std::shared_ptr< Render::Mesh> mesh;
		lua_pushstring(i_luaState, "mesh");
		lua_gettable(i_luaState, -2);
		std::string mesh_name = lua_tostring(i_luaState,-1);
		lua_pop(i_luaState, 1);
		MeshRender::MeshRenderSystem* n = MeshRender::MeshRenderSystem::GetInstance();
		if (MeshRender::MeshRenderSystem::GetInstance()->meshes.find(mesh_name) == MeshRender::MeshRenderSystem::GetInstance()->meshes.end()) {
			mesh = MeshRender::MeshRenderSystem::GetInstance()->InitializeMesh(mesh_name.c_str());
		}
		else {
			mesh = MeshRender::MeshRenderSystem::GetInstance()->meshes.find(mesh_name)->second;
		}
		

		std::shared_ptr < Render::Effect> effect;
		lua_pushstring(i_luaState, "effect");
		lua_gettable(i_luaState, -2);
		std::string effect_name = lua_tostring(i_luaState,-1);
		lua_pop(i_luaState, 1);
		effect = MeshRender::MeshRenderSystem::GetInstance()->effects.find(effect_name)->second;
		
		std::shared_ptr< Render::Texture> texture;
		lua_pushstring(i_luaState, "texture");
		lua_gettable(i_luaState, -2);
		std::string texture_name = lua_tostring(i_luaState, -1);
		lua_pop(i_luaState, 1);
		if (MeshRender::MeshRenderSystem::GetInstance()->textures.find(texture_name) == MeshRender::MeshRenderSystem::GetInstance()->textures.end()) {
			texture = MeshRender::MeshRenderSystem::GetInstance()->InitializeTexture(texture_name.c_str());
		}
		else {
			texture = MeshRender::MeshRenderSystem::GetInstance()->textures.find(texture_name)->second;
		}

		std::shared_ptr< Render::Texture> normalMap;
		lua_pushstring(i_luaState, "normalMap");
		lua_gettable(i_luaState, -2);
		std::string normal_name = lua_tostring(i_luaState, -1);
		lua_pop(i_luaState, 1);
		if (MeshRender::MeshRenderSystem::GetInstance()->textures.find(normal_name) == MeshRender::MeshRenderSystem::GetInstance()->textures.end()) {
			normalMap = MeshRender::MeshRenderSystem::GetInstance()->InitializeTexture(normal_name.c_str());
		}
		else {
			normalMap = MeshRender::MeshRenderSystem::GetInstance()->textures.find(normal_name)->second;
		}

		Math::Vector4 color;
		lua_pushstring(i_luaState, "color");
		lua_gettable(i_luaState, -2);
		for (int i = 1; i <= 4; ++i) {
			lua_rawgeti(i_luaState, -1, i);
			color[i - 1] = lua_tonumber(i_luaState, -1)/255.0f;
			lua_pop(i_luaState, 1);
		}
		lua_pop(i_luaState, 1);

		MeshRender::MeshRenderSystem::GetInstance()->AddComponent(new MeshRender::MeshRenderComponent(i_id, i_entity, mesh, effect,texture,normalMap,color));
		}
	);
#pragma endregion
#pragma region SkeletalMesh
	RegisterComponentCreator("SkeletalMesh", [](int i_id, std::shared_ptr <ECS::Entity> i_entity, lua_State* i_luaState) {
		std::shared_ptr< Render::SkeletalMesh> mesh;
		lua_pushstring(i_luaState, "mesh");
		lua_gettable(i_luaState, -2);
		std::string mesh_name = lua_tostring(i_luaState, -1);
		lua_pop(i_luaState, 1);
		MeshRender::MeshRenderSystem* n = MeshRender::MeshRenderSystem::GetInstance();
		if (MeshRender::MeshRenderSystem::GetInstance()->skeletalMeshes.find(mesh_name) == MeshRender::MeshRenderSystem::GetInstance()->skeletalMeshes.end()) {
			mesh = MeshRender::MeshRenderSystem::GetInstance()->InitializeSkeletalMesh(mesh_name.c_str());
		}
		else {
			mesh = MeshRender::MeshRenderSystem::GetInstance()->skeletalMeshes.find(mesh_name)->second;
		}


		std::shared_ptr < Render::Effect> effect;
		lua_pushstring(i_luaState, "effect");
		lua_gettable(i_luaState, -2);
		std::string effect_name = lua_tostring(i_luaState, -1);
		lua_pop(i_luaState, 1);
		effect = MeshRender::MeshRenderSystem::GetInstance()->effects.find(effect_name)->second;

		std::shared_ptr< Render::Texture> texture;
		lua_pushstring(i_luaState, "texture");
		lua_gettable(i_luaState, -2);
		std::string texture_name = lua_tostring(i_luaState, -1);
		lua_pop(i_luaState, 1);
		if (MeshRender::MeshRenderSystem::GetInstance()->textures.find(texture_name) == MeshRender::MeshRenderSystem::GetInstance()->textures.end()) {
			texture = MeshRender::MeshRenderSystem::GetInstance()->InitializeTexture(texture_name.c_str());
		}
		else {
			texture = MeshRender::MeshRenderSystem::GetInstance()->textures.find(texture_name)->second;
		}

		std::shared_ptr< Render::Texture> normalMap;
		lua_pushstring(i_luaState, "normalMap");
		lua_gettable(i_luaState, -2);
		std::string normal_name = lua_tostring(i_luaState, -1);
		lua_pop(i_luaState, 1);
		if (MeshRender::MeshRenderSystem::GetInstance()->textures.find(normal_name) == MeshRender::MeshRenderSystem::GetInstance()->textures.end()) {
			normalMap = MeshRender::MeshRenderSystem::GetInstance()->InitializeTexture(normal_name.c_str());
		}
		else {
			normalMap = MeshRender::MeshRenderSystem::GetInstance()->textures.find(normal_name)->second;
		}

		Math::Vector4 color;
		lua_pushstring(i_luaState, "color");
		lua_gettable(i_luaState, -2);
		for (int i = 1; i <= 4; ++i) {
			lua_rawgeti(i_luaState, -1, i);
			color[i - 1] = lua_tonumber(i_luaState, -1) / 255.0f;
			lua_pop(i_luaState, 1);
		}
		lua_pop(i_luaState, 1);

		MeshRender::MeshRenderSystem::GetInstance()->AddComponent(new MeshRender::MeshRenderComponent(i_id, i_entity, mesh, effect, texture, normalMap, color));
		}
	);
#pragma endregion
#pragma region Collider
	RegisterComponentCreator("Collider", [](int i_id, std::shared_ptr <ECS::Entity> i_entity, lua_State* i_luaState) {
		
		lua_pushstring(i_luaState, "type");
		lua_gettable(i_luaState, -2);
		std::string type = lua_tostring(i_luaState, -1);
		lua_pop(i_luaState, 1);

		Math::Vector3 size(0,0,0);
		lua_pushstring(i_luaState, "size");
		lua_gettable(i_luaState, -2);
		for (int i = 1; i <= 3; ++i) {
			lua_rawgeti(i_luaState, -1, i);
			size[i - 1] = lua_tonumber(i_luaState, -1);
			lua_pop(i_luaState, 1);
		}
		lua_pop(i_luaState, 1);
		if (size.x==0||size.y==0||size.z==0) {
			ColliderSystem::GetInstance()->AddComponent(new ColliderComponent(i_id, i_entity, type.c_str()));
		}
		else {
			ColliderSystem::GetInstance()->AddComponent(new ColliderComponent(i_id, i_entity, type.c_str(), size));
		}

		
		}
	);
#pragma endregion
#pragma region Camera
	RegisterComponentCreator("Camera", [](int i_id, std::shared_ptr <ECS::Entity> i_entity, lua_State* i_luaState) {

		Camera::CameraSystem* system = Camera::CameraSystem::GetInstance();

		lua_pushstring(i_luaState, "isMain");
		lua_gettable(i_luaState, -2);
		bool isMain = lua_toboolean(i_luaState, -1);
		lua_pop(i_luaState, 1);

		lua_pushstring(i_luaState, "far");
		lua_gettable(i_luaState, -2);
		float cfar = lua_tonumber(i_luaState, -1);
		lua_pop(i_luaState, 1);
	

		lua_pushstring(i_luaState, "near");
		lua_gettable(i_luaState, -2);
		float cnear = lua_tonumber(i_luaState, -1);
		lua_pop(i_luaState, 1);


		lua_pushstring(i_luaState, "horizental");
		lua_gettable(i_luaState, -2);
		float chorizental = lua_tonumber(i_luaState, -1);
		lua_pop(i_luaState, 1);


		lua_pushstring(i_luaState, "vertical");
		lua_gettable(i_luaState, -2);
		float cvertical = lua_tonumber(i_luaState, -1);
		lua_pop(i_luaState, 1);

		system->AddComponent(new Camera::CameraComponent(i_id, i_entity,isMain, cnear, cfar, chorizental, cvertical));
			
		}
	);
#pragma endregion
}

void Rain::Asset::SceneLoader::RegisterComponentCreator(const std::string& i_ComponentName, std::function<void(int, std::shared_ptr <ECS::Entity> i_entity, lua_State*)> i_ComponentCreator) {
	m_componentCreators.insert(std::pair<std::string, std::function<void(int, std::shared_ptr <Rain::ECS::Entity> i_entity, lua_State*)>>(i_ComponentName, i_ComponentCreator));
}