#include "Scene.h"
#include "GameObject.h"
#include "CollisionComp.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object));
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update(float deltaTime)
{
	std::shared_ptr<GameObject> removeObj = nullptr;
	for (auto& object : m_objects)
	{
		object->Update(deltaTime);
		if (object->GetDestroyGameobject())
		{
			removeObj = object;
		}
	}

	if (removeObj != nullptr)
	{
		Remove(removeObj);
	}
}

void dae::Scene::FixedUpdate(float fixedTime)
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate(fixedTime);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

