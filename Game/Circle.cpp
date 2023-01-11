#include "Circle.h"
#include "Transform/TransformComponent.h"
#include "Transform/TransformSystem.h"
#include "Input/Input.h"
#include "Collision/ColliderSystem.h"
#include "Collision/ColliderComponent.h"
#include "MeshRender/MeshRender.h"
#include "AI/NavMesh.h"
#include "AI/Map.h"
#include "AI/AStar.h"
namespace {
    std::vector < Rain::Math::Vector2 > path;
    int curPathNode = 0;
    Rain::AI::AStar* aStar;
    Rain::Math::Vector3 direction;
}
void Rain::Circle::Initialize(int i_id) {
    id = i_id;
    
    //Click and the object will move forward.
    Rain::Input::Mouse::BindEvent(MOUSE_LEFT_DOWN, [this](Rain::Input::MouseInfo info) {
        this->StartPathFinding();
        /*Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
        transform->position = transform->position + Math::Vector3(0.0f, 0, 0.49f);
        int o = 1;*/
        });

    ColliderComponent* collider = ColliderSystem::GetInstance()->GetComponent<ColliderComponent>(id);
    collider->OnColliderEnter = [this](const ColliderComponent* other) {
        MeshRender::MeshRenderSystem::GetInstance()->GetComponent< MeshRender::MeshRenderComponent>(id)->color = Math::Vector4(220 / 255.0f, 20 / 255.0f, 60/ 255.0f, 255 / 255.0f);
    };
    collider->OnColliderExit = [this](const ColliderComponent* other) {
        MeshRender::MeshRenderSystem::GetInstance()->GetComponent< MeshRender::MeshRenderComponent>(id)->color = Math::Vector4(144/255.0f, 238 / 255.0f, 144 / 255.0f, 255 / 255.0f);
    };
    //Press A and the object will move to the left.
    Rain::Input::KeyBoard::BindEvent(0x41, KEYSTAY, [this](Rain::Input::KeyBoard::KeyInfo info) {
        Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
        transform->position = transform->position - Math::Vector3(0.001f, 0, 0);
        });
    //w
    Rain::Input::KeyBoard::BindEvent(0x57, KEYSTAY, [this](Rain::Input::KeyBoard::KeyInfo info) {
        Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
        transform->position = transform->position + Math::Vector3(0, 0, 0.001f);
        });
    //S
    Rain::Input::KeyBoard::BindEvent(0x53, KEYSTAY, [this](Rain::Input::KeyBoard::KeyInfo info) {
        Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
        transform->position = transform->position - Math::Vector3(0, 0, 0.001f);
        });
    //D
    Rain::Input::KeyBoard::BindEvent(0x44, KEYSTAY, [this](Rain::Input::KeyBoard::KeyInfo info) {
        Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
        transform->position = transform->position + Math::Vector3(0.001f, 0, 0);
        });



    std::vector<Math::Vector2> vertices;
    vertices.push_back(Math::Vector2(-30, -30));
    vertices.push_back(Math::Vector2(-20, 0));
    vertices.push_back(Math::Vector2(0, 10));
    vertices.push_back(Math::Vector2(-20, 30));
    vertices.push_back(Math::Vector2(10, 40));
    vertices.push_back(Math::Vector2(40, 40));
    vertices.push_back(Math::Vector2(20, 30));
    vertices.push_back(Math::Vector2(30, 10));
    vertices.push_back(Math::Vector2(40, 0));
    vertices.push_back(Math::Vector2(30, -10));
    vertices.push_back(Math::Vector2(10, -20));
    vertices.push_back(Math::Vector2(0,-10));
    vertices.push_back(Math::Vector2(-10, -20));

    AI::Polygon polygon(vertices);

    AI::NavMesh* mesh = new AI::NavMesh();
    mesh->polygonData = polygon;
    mesh->GenerateNavMesh();

    Rain::AI::Map* map = new  Rain::AI::Map();
    map->navMesh = mesh;
    map->GenerateMap();

    aStar = new AI::AStar(map);
    curPathNode = -1;

}
void Rain::Circle::Update(double i_timeSinceLastFrame) {
    Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
    //if (curPathNode == 0) {
    //   curPathNode++;
    //   direction = Math::Vector3(path[curPathNode].x, 0, path[curPathNode].y) - transform->position;
    //   direction.Normalize();
    //}
    if (curPathNode >= 0) {
        Math::Vector3 tempDirection = Math::Vector3(path[curPathNode].x, 0,path[curPathNode].y) - transform->position;
        if ((tempDirection.x*direction.x<=0)&& (tempDirection.y * direction.y <= 0)) {
            curPathNode++;
            if (curPathNode >= path.size()) {
                curPathNode = -1;
            }
            else {
                direction = Math::Vector3(path[curPathNode].x,0, path[curPathNode].y) - transform->position;
            }
        }
        transform->position = transform->position + direction*i_timeSinceLastFrame * 8;
        direction.Normalize();
    }
   
}
void Rain::Circle::Destory() {

}
Rain::Circle::Circle() {
}

void Rain::Circle::StartPathFinding() {
    Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
    Math::Vector3 end = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(5)->position;
    path.clear();
    aStar->GetPath(Math::Vector2(transform->position.x, transform->position.z),Math::Vector2(end.x,end.z), path);
    curPathNode = 0;
}