#pragma once
#include "Component.h"
#include "Transform.h"
#include "string"
#include "memory"
#include "vector"
#include "glut.h"
#include <algorithm>

class GameObject 
{
private:
	std::string _name;
	bool _active = true;
    bool _ignoreParentTransformations = false;

    std::vector<std::unique_ptr<Component>> _components = std::vector<std::unique_ptr<Component>>();

    GameObject* _parent = nullptr;
    std::vector<GameObject*> _children;
public:

    GameObject(const std::string& name = "GameObject", std::vector<GameObject*> children = {});
    GameObject(const GameObject& other);

    void update();
    void render();

    /**
    * Adds a new component of type T to the GameObject.
    *
    * This method constructs the component with the given arguments,
    * sets its owner to this GameObject, stores it internally,
    * and returns a raw pointer to the component.
    *
    * @tparam T The type of the component to add (must derive from Component).
    * @tparam Args Variadic template for constructor arguments of T.
    * @param args Arguments forwarded to the component constructor.
    * @return A raw pointer to the newly created component.
    */
    template<typename T, typename... Args>
    T* addComponent(Args && ...args) {
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        component->setOwner(this);

        T* addedComponentPointer = component.get();
        _components.push_back(std::move(component));

        return addedComponentPointer;
    }

    void addComponent(Component component);

    /**
     * Retrieves the first component of type T attached to this GameObject.
     *
     * This method searches through all components and returns the first one
     * that can be dynamically cast to type T. If no such component exists,
     * returns nullptr.
     *
     * @tparam T The type of component to retrieve.
     * @return Pointer to the component if found, nullptr otherwise.
     */
    template<typename T>
    T* getComponent() {
        for (auto& component : _components) {
            if (auto type = dynamic_cast<T*>(component.get())) {
                return type;
            }
        }
        return nullptr;
    }

    void setActive(bool value);
    bool isActive();

    GameObject* getChild(int index);
    void addChild(GameObject* child);
    void removeChild(int index);
    void removeChild(GameObject* child);

    void setParent(GameObject* parent);
    GameObject* getParent();

    std::string getName();
};
