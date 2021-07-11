#include <memory>
#include "Entity.h"
#include "Transform.h"
#include "Collider.h"
#include "MeshFilter.h"
#include "ComponentManager.h"
#include "World.h"
#include "ColliderSystem.h"

#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <chrono>

std::shared_ptr<Entity> tri0, tri1;

std::shared_ptr<Transform2D> triTransform_0, triTransform_1;
std::shared_ptr<MeshFilter> triMesh_0, triMesh_1;
std::shared_ptr<Collider2D> triColl_0, triColl_1;

std::array<glm::vec2, 3> verts{ glm::vec2(0, 2), glm::vec2(-1, -1), glm::vec2(1, -1) };

void CreateTriangles()
{
	{
		tri0 = std::make_shared<Entity>();
		{
			triTransform_0 = std::make_shared<Transform2D>(glm::vec2(4, 1));
			tri0.get()->AddComponent<Transform2D>(triTransform_0.get());
		}
		{
			triMesh_0 = std::make_shared<MeshFilter>(verts.data(), (uint32_t)verts.size());
			tri0->AddComponent<MeshFilter>(triMesh_0.get());
		}
		{
			triColl_0 = std::make_shared<Collider2D>();
			tri0->AddComponent<Collider2D>(triColl_0.get());
		}
	}

	{
		tri1 = std::make_shared<Entity>();
		
		{
			triTransform_1 = std::make_shared<Transform2D>(glm::vec2(4, 1));
			tri1.get()->AddComponent<Transform2D>(triTransform_1.get());
		}
		{
			triMesh_1 = std::make_shared<MeshFilter>(verts.data(), (uint32_t)verts.size());
			tri1->AddComponent<MeshFilter>(triMesh_1.get());
		}
		{
			triColl_1 = std::make_shared<Collider2D>();
			tri1->AddComponent<Collider2D>(triColl_1.get());
		}
	}
}

void MoveTriangle(float offset)
{
	glm::vec2 pos = triTransform_0->GetPosition() + glm::vec2(offset, 0);
	triTransform_0->SetPosition(pos);
}

void CollisionCallback(std::vector<Collision> collisions)
{
	if (collisions.size() > 0)
	{
		for (auto coll : collisions)
		{
			std::cout << "colliding entities " << coll.entityId_0 << " & " << coll.entityId_1 ;
			std::cout << " xmin0 position : " << coll.box0.minX << " xmax0 position : " << coll.box0.maxX << " xmin1 position : " << coll.box1.minX << " xmax1 position : " << coll.box1.maxX << "\n"; ;
		}
	}
	else
	{
		std::cout << "no Collision\n";
	}
}

void CopyEntity()
{
	Entity tri2 = *tri1;
	Transform2D transform1 = *tri1->GetComponent<Transform2D>();
	Collider2D coll1 = *tri1->GetComponent<Collider2D>();
	MeshFilter mesh1 = *tri1->GetComponent<MeshFilter>();

	Transform2D transform2 = *tri2.GetComponent<Transform2D>();
	Collider2D coll2 = *tri2.GetComponent<Collider2D>();
	MeshFilter mesh2 = *tri2.GetComponent<MeshFilter>();

	std::cout << "\nAfter entity copy\n";
	World::GetInstance()->Update();
}

int main(int argc, const char* argv[])
{
	World::GetInstance()->Init();

	CreateTriangles();

	//Just for testing
	ColliderSystem::callBack = &CollisionCallback;

	uint32_t counter = 0;
	while (counter < 30)
	{
		MoveTriangle(-0.1f);

		World::GetInstance()->Update();
		counter++;
	}

#define ENTITY_COPY
	
	CopyEntity();

#undef ENTITY_COPY

	World::GetInstance()->DeInit();
	delete World::GetInstance();

	getchar();

	return 0;
}