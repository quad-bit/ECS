#include "World.h"

#include "ComponentManager.h"
#include "ColliderSystem.h"
#include "Transform.h"
#include "MeshFilter.h"
#include "Collider.h"
#include "Health.h"
#include "Attack.h"

#include <assert.h>

World * World::instance = nullptr;

void World::Init()
{
	std::shared_ptr<BaseComponentManager> transformManager(new ComponentManager<Transform2D>(ComponentType::TRANSFORM));
	RegisterComponentManager(ComponentType::TRANSFORM, transformManager);

	std::shared_ptr<BaseComponentManager> colliderManager(new ComponentManager<Collider2D>(ComponentType::COLLIDER));
	RegisterComponentManager(ComponentType::COLLIDER, colliderManager);

	std::shared_ptr<BaseComponentManager> meshFilterManager(new ComponentManager<MeshFilter>(ComponentType::MESHFILTER));
	RegisterComponentManager(ComponentType::MESHFILTER, meshFilterManager);

	std::shared_ptr<SystemBase> colliderSystem(new ColliderSystem());
	RegisterComponentSystem(ComponentType::COLLIDER, colliderSystem);
	colliderSystem->Init();

	std::shared_ptr<BaseComponentManager> healthManager(new ComponentManager<Health>(ComponentType::HEALTH));
	RegisterComponentManager(ComponentType::HEALTH, healthManager);

	std::shared_ptr<BaseComponentManager> attackManager(new ComponentManager<Health>(ComponentType::ATTACK));
	RegisterComponentManager(ComponentType::ATTACK, attackManager);

	EntityManager::GetInstance()->Init();
}

void World::DeInit()
{
	componentManagerMap.clear();

	EntityManager::GetInstance()->DeInit();
	delete EntityManager::GetInstance();
}

void World::Update()
{
	for (auto item : componentSystemMap)
	{
		item.second->Update();
	}
}

World * World::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new World();
	}
	return instance;
}

World::~World()
{
	
}

void World::RegisterComponentManager(const ComponentType & type, std::shared_ptr<BaseComponentManager> manager)
{
	componentManagerMap.insert(std::pair<ComponentType, std::shared_ptr<BaseComponentManager>>(manager->GetManagerType(), manager));
}

void World::RegisterComponentSystem(const ComponentType & type, std::shared_ptr<SystemBase> system)
{
	componentSystemMap.insert(std::pair<ComponentType, std::shared_ptr<SystemBase>>(type, system));
}

std::shared_ptr<BaseComponentManager> World::GetComponentManager(ComponentType type)
{
	return componentManagerMap[type];
}

std::shared_ptr<SystemBase> World::GetComponentSystem(ComponentType type)
{
	return componentSystemMap[type];
}

void World::GenerateComponents(Entity * entityObj, const std::map<ComponentType, std::vector<Component*>>& componentList)
{
	// for each component create a new one by copying
	uint32_t numComponentTypes = (uint32_t)componentList.size();

	// Need to learn about type deduction to avoid the following garbage
	for (auto const & item : componentList)
	{
		ComponentType type = item.first;

		switch (type)
		{
		case ComponentType::TRANSFORM:

			CreateComponenHelper<Transform2D>(entityObj, item.second);
			break;
		
		case ComponentType::COLLIDER:
			CreateComponenHelper<Collider2D>(entityObj, item.second);
			break;

		case ComponentType::MESHFILTER:
			CreateComponenHelper<MeshFilter>(entityObj, item.second);
			break;

		case ComponentType::HEALTH:
			CreateComponenHelper<Health>(entityObj, item.second);
			break;
		
		case ComponentType::ATTACK:
			CreateComponenHelper<Attack>(entityObj, item.second);
			break;
		
		default:
			assert(0 && "type not found");
			break;
		}
	}
}
