#include "HWECS.h"
#include <cassert>
#include <cstddef>
#include <memory>

//Entity Manager//
EntityManager::EntityManager(){
	for (Entity entity = 0; entity < MAX_ENTITIES; ++entity){
	mAvailableEntities.push(entity);
	}
}

Entity EntityManager::CreateEntity(){
	assert(mLivingEntityCount < MAX_ENTITIES && "Demasiadas entidades en existencia.");
	Entity id = mAvailableEntities.front();
	mAvailableEntities.pop();
	++mLivingEntityCount;
	
	return id;
}

void EntityManager::DestroyEntity(Entity entity){
	assert(entity < MAX_ENTITIES && "Entidad fuera de rango.");
	mSignatures[entity].reset();
	mAvailableEntities.push(entity);
	--mLivingEntityCount;
}

void EntityManager::SetSignature(Entity entity, Signature signature){
	assert(entity < MAX_ENTITIES && "Entidad fuera de rango.");
	mSignatures[entity] = signature;
}

Signature EntityManager::GetSignature(Entity entity){
	assert(entity < MAX_ENTITIES && "Entidad fuera de rango.");
	return mSignatures[entity];
}

//Component array//
template<typename T>
void ComponentArray<T>::InsertData(Entity entity, T component){
	assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Componente sobreescrito en la entidad.");
	size_t newIndex = mSize;
	mEntityToIndexMap[entity] = newIndex;
	mIndexToEntityMap[newIndex] = entity;
	mComponentArray[newIndex] = component;
	++mSize;
}

template<typename T>
void ComponentArray<T>::RemoveData(Entity entity){
	assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Removiendo componente inexistente");
	size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
	size_t indexOfLastElement = mSize - 1;
	mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];
	
	Entity EntityOfLastElement = mIndexToEntityMap[indexOfLastElement];
	mEntityToIndexMap[EntityOfLastElement] = indexOfRemovedEntity;
	mIndexToEntityMap[indexOfRemovedEntity] = EntityOfLastElement;
	
	mEntityToIndexMap.erase(entity);
	mIndexToEntityMap.erase(indexOfLastElement);
	
	--mSize;
}

template<typename T>
T& ComponentArray<T>::GetData(Entity entity){
	assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Recuperando componente inexistente.");
	return mComponentArray[mEntityToIndexMap[entity]];
}

template<typename T>
void ComponentArray<T>::EntityDestroyed(Entity entity){
	if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end()){
		RemoveData(entity);
	}
}

//Component Manager//
template<typename T>
std::shared_ptr<ComponentArray<T>> ComponentManager::GetComponentArray(){
	const char* typeName = typeid(T).name();
	assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Componente no registrado antes de usarse.");
	
	return std::static_pointer_cast<ComponentArray<T>>(mComponentArray[typeName]);
}
template<typename T>
void ComponentManager::RegisterComponent(){
	const char* typeName = typeid(T).name();
	assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Registrando un tipo de componente mas de una vez");
	mComponentTypes.insert({typeName, mNextComponentType});
	mComponentArray.insert({typeName, std::make_shared<ComponentArray<T>>()});
	++mNextComponentType;
}
template<typename T>
ComponentType ComponentManager::GetComponentType(){
	const char* typeName = typeid(T).name();
	assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Componente no registrado antes de su uso.");
	return mComponentTypes[typeName];
}
template<typename T>
void ComponentManager::AddComponent(Entity entity, T component){
	GetComponentArray<T>()->InsertData(entity, component);
}
template<typename T>
void ComponentManager::RemoveComponent(Entity entity){
	GetComponentArray<T>()->RemoveData(entity);
}
template<typename T>
T& ComponentManager::getComponent(Entity entity){
	return GetComponentArray<T>()->GetData(entity);
}
void ComponentManager::EntityDestroyed(Entity entity){
	for (auto const& pair : mComponentArray){
		auto const& component = pair.second;
		component->EntityDestroyed(entity);
	}
}
