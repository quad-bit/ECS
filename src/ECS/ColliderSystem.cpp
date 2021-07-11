#include "ColliderSystem.h"
#include "World.h"
#include "Transform.h"
#include "MeshFilter.h"
#include "ComponentManager.h"
#include "EntityManager.h"
#include <vector>
#include <algorithm>

callBackPtr ColliderSystem::callBack = nullptr;

// THIS IS A BASIC ONE-ONE CHECK ALGORITHM, NEED TO IMPROVE IT MAYBE WITH OCT/K-D TREE

std::vector<Collision> ColliderSystem::CheckForCollision(const std::vector<std::tuple<uint32_t, Rect2D>> & boxList)
{
	uint32_t count =(uint32_t)boxList.size();
	std::vector<Collision> collisions;

	for(uint32_t i = 0; i < count; i++)
	{
		Rect2D box0 = std::get<1>(boxList[i]);
		for (uint32_t j = 0; j < count; j++)
		{
			uint32_t id0 = std::get<0>(boxList[i]), id1 = std::get<0>(boxList[j]);

			if (j == i)
				continue;

			Rect2D box1 = std::get<1>(boxList[j]);

			if ((box0.maxX >= box1.minX && box0.minX <= box1.minX) || (box0.maxX >= box1.maxX && box0.minX <= box1.maxX))
			{
				if ((box0.maxY >= box1.minY && box0.minY <= box1.minY) || (box0.maxY >= box1.maxY && box0.minY <= box1.maxY))
				{
					Collision col;
					col.box0 = box0;
					col.entityId_0 = id0;

					col.box1 = box1;
					col.entityId_1 = id1;
					
					std::vector<Collision>::iterator it = std::find_if(collisions.begin(), collisions.end(), [=](Collision collision) {
						if ((collision.entityId_0 == id0 && collision.entityId_1 == id1) || (collision.entityId_0 == id1 && collision.entityId_1 == id0))
							return true;
						else
							return false;
					});

					if(it == collisions.end())
						collisions.push_back(col);
				}
			}
		}
	}

	return collisions;
}

void ColliderSystem::Init()
{
	dependencyList.push_back(ComponentType::TRANSFORM);
	dependencyList.push_back(ComponentType::MESHFILTER);

	componentManager = World::GetInstance()->GetComponentManager(ComponentType::COLLIDER);
	transformCompManager = World::GetInstance()->GetComponentManager(ComponentType::TRANSFORM);
	meshfilterCompManager = World::GetInstance()->GetComponentManager(ComponentType::MESHFILTER);
}

void ColliderSystem::Update()
{
	// iterate through all the collider components 
	
	const std::map<Component*, uint32_t> & map = componentManager->GetComponentMap();

	std::tuple<uint32_t, Rect2D> entityBox;
	std::vector<std::tuple<uint32_t, Rect2D>> entityBoxRects;

	for (auto item : map)
	{
		// check with EntityManager for the dependant components of the entity
		std::vector<Component*> transformList = EntityManager::GetInstance()->GetComponent(item.second, ComponentType::TRANSFORM);
		std::vector<Component*> meshList = EntityManager::GetInstance()->GetComponent(item.second, ComponentType::MESHFILTER);

		glm::mat4 mat = static_cast<Transform2D*>(transformList[0])->GetTransformationMat();
		const std::vector<glm::vec2>& verts = static_cast<MeshFilter*>(meshList[0])->GetVertices();

		Collider2D * collider = static_cast<Collider2D*>(item.first);

		Rect2D rect = collider->GetBoxRect(verts.data(), (uint32_t)verts.size(), mat);

		entityBox = std::make_tuple(item.second, rect);
		entityBoxRects.push_back(entityBox);
	}

	// use while triggering the callback
	std::vector<Collision> collisionList = CheckForCollision(entityBoxRects);

	callBack(collisionList);
}

void ColliderSystem::DeInit()
{
}
