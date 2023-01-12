#include "Circle.h"
#include "Transform/TransformComponent.h"
#include "Transform/TransformSystem.h"
#include "Input/Input.h"
#include "Collision/ColliderSystem.h"
#include "Collision/ColliderComponent.h"
#include "Collision/Collision.h"
#include "MeshRender/MeshRender.h"
#include "AI/NavMesh.h"
#include "AI/Map.h"
#include "AI/AStar.h"
#include <vector>
#include <list>
#include "Application\Rain3DGame.h"
namespace {
    std::list < Rain::Math::Vector2 > path;
    std::vector < Rain::Math::Vector2 > path;
    int curPathNode = 0;
    Rain::AI::AStar* aStar;
    Rain::Math::Vector3 direction;
}
void Rain::Circle::Initialize(int i_id, std::string i_tag, std::string i_name) {
    id = i_id;
    name = i_name;
    tag = i_tag;
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
    vertices.push_back(Math::Vector2(40, 25));
    vertices.push_back(Math::Vector2(20, 30));
    vertices.push_back(Math::Vector2(30, 10));
    vertices.push_back(Math::Vector2(40, 0));
    vertices.push_back(Math::Vector2(30, -10));
    vertices.push_back(Math::Vector2(10, -20));
    vertices.push_back(Math::Vector2(0,-10));
    vertices.push_back(Math::Vector2(-10, -20));
    vertices.push_back(Math::Vector2(0, -30));

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
    CheckCollision();
    //if (curPathNode == 0) {
    //   curPathNode++;
    //   direction = Math::Vector3(path[curPathNode].x, 0, path[curPathNode].y) - transform->position;
    //   direction.Normalize();
    //}
    if (curPathNode >= 0) {
        Math::Vector3 tempDirection = Math::Vector3(path[curPathNode].x, 0,path[curPathNode].y) - transform->position;
        if (Math::Distance(Math::Vector3(path[curPathNode].x, 0, path[curPathNode].y),transform->position) < 0.1) {
            curPathNode++;
            if (curPathNode >= path.size()) {
                curPathNode = -1;
            }
            else {
                direction = Math::Vector3(path[curPathNode].x,0, path[curPathNode].y) - transform->position;
                direction.Normalize();
            }
        }
        
        transform->position = transform->position + direction*i_timeSinceLastFrame * 13;

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

std::vector<int> Rain::Circle::CheckCollision() {
    std::vector<int> outcome;
    Rain::Math::Vector3 point = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(id)->position;
    Collision::SphereCollider* collider1;
    Collision::SphereCollider* collider2 = ((Collision::SphereCollider*)((ColliderSystem::GetInstance()->GetComponent<ColliderComponent>(id)))->collider);

    Math::Vector3 pos0;
    Math::Vector3 pos1 = collider2->pos;
    Math::Vector3 posTemp = pos1 + direction * 4;
    for (auto collider : ColliderSystem::GetInstance()->GetAllComponents<ColliderComponent>()) {
        const ECS::Entity* e = Rain3DGame::GetEntity(collider->id);
        std::string tag = Rain3DGame::GetEntity(collider->id)->tag;
        if (tag.compare("obstacle") == 0) {
            collider1 = (Collision::SphereCollider*)(collider->collider);
            
            float radius0 = collider1->radius;
            float radius1 = collider2->radius;

            pos0 = collider1->pos;
            float distance = (pos0 - posTemp).GetLength();

            if (radius0 + radius1 > distance) {
                outcome.push_back(collider->id);
            }
        }
    }
    if (outcome.size() > 0) {
        ModifyVelocity(Math::Vector2(pos1.x,pos1.z), path[curPathNode], outcome);
    }
    return outcome;
}

void Rain::Circle::ModifyVelocity(Math::Vector2 i_curPos, Math::Vector2 i_aimPos, const std::vector<int>& i_obstacles) {
    Math::Vector2 tangent0;


    Collision::SphereCollider* collider = ((Collision::SphereCollider*)(ColliderSystem::GetInstance()->GetComponent<ColliderComponent>(i_obstacles[0]))->collider);
    float radius = collider->radius;
    Math::Vector2 obstaclePos= Math::Vector2(collider->pos.x, collider->pos.z);

    Math::Vector2 cur_obs = obstaclePos - i_curPos;
    float i = (cur_obs.x * cur_obs.x + cur_obs.y * cur_obs.y);
    float angle1 = asinf(radius/sqrtf(cur_obs.x*cur_obs.x+cur_obs.y*cur_obs.y));
    Math::Vector2 tangent1 = Math::Vector2(cur_obs.x * (sin(angle1) + cos(angle1)),cur_obs.y * (-sin(angle1) + cos(angle1)));
    float slope1 = tangent1.y / tangent1.x;
    float intersect1 = -i_curPos.y / slope1 + i_curPos.x;

    Math::Vector2 cur_aim = obstaclePos - i_aimPos;
    float angle2 = asinf(radius / sqrtf(cur_aim.x * cur_aim.x + cur_aim.y * cur_aim.y));
    Math::Vector2 tangent2 = Math::Vector2(cur_aim.x * (sin(angle2) + cos(angle2)), cur_aim.y * (-sin(angle2) + cos(angle2)));
    float slope2 = tangent2.y / tangent2.x;
    float intersect2 = -i_aimPos.y / slope2 + i_aimPos.x;

    float x = (intersect2 - intersect1) / (slope1 - slope2);
    float y = slope1*x+intersect1;

    path.insert(path.begin()+1,)
}