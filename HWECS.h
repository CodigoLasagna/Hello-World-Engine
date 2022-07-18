#ifndef ECS
#define ECS

#include <array>
#include <iostream>
#include <ncurses.h>
#include <bitset>
#include <queue>
#include <cassert>
#include <unordered_map>
#include <memory>

using Entity = std::uint32_t;
using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

const Entity MAX_ENTITIES = 5000;

struct Transform{
	int x{}, y{};
};
struct Draw{
	chtype sprite{};
	int fg{}, bg{};
	bool altc{};
};

class EntityManager{
	private:
	std::queue<Entity> mAvailableEntities{};
	std::array<Signature, MAX_ENTITIES> mSignatures{};
	uint32_t mLivingEntityCount{};
	
	public:
	EntityManager();
	Entity CreateEntity();
	void DestroyEntity(Entity entity);
	void SetSignature(Entity entity, Signature signature);
	Signature GetSignature(Entity entity);
};

class IComponentArray{
	public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray{
	private:
	std::array<T, MAX_ENTITIES> mComponentArray;
	std::unordered_map<Entity, size_t> mEntityToIndexMap;
	std::unordered_map<size_t, Entity> mIndexToEntityMap;
	size_t mSize;
	
	public:
	void InsertData(Entity entity, T component);
	void RemoveData(Entity entity);
	T& GetData(Entity entity);
	void EntityDestroyed(Entity entity) override;
};

class ComponentManager{
	public:
	template<typename T>
	void RegisterComponent();
	template<typename T>
	ComponentType GetComponentType();
	template<typename T>
	void AddComponent(Entity entity, T component);
	template<typename T>
	void RemoveComponent(Entity entity);
	template<typename T>
	T& getComponent(Entity entity);
	void EntityDestroyed(Entity entity);
	
	private:
	std::unordered_map<const char*, ComponentType> mComponentTypes{};
	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> mComponentArray{};
	ComponentType mNextComponentType{};
	
	template<typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray();
};

#endif
