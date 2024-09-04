export module core;

import <wtypes.h>;
import <string>;
import <vector>;
import <bitset>;

namespace GDE {
	namespace Core {
		class Object {

		};

	}

	namespace Components {
		export class Component : public Core::Object {
		protected:
			using Signature = std::bitset<10>;
			static constexpr Signature compSign_ = 0b0;

		public:
			virtual const Signature getSignature() const = 0;
			static const Signature getSSignature();

			virtual ~Component() =0;
		};

		template <typename T> concept ComponentType = std::is_base_of_v<Component, T>;
	}

	namespace Entities {
		export class Entity : public Core::Object {
		private:
			std::string name_;

			std::vector<Components::Component*> components_;

		public:
			Entity(const std::string);

			const std::string getName() const;
			std::string getName();

			template <Components::ComponentType T> inline void addComponent();

			template <Components::ComponentType T> inline const T* getComponent() const;
			template <Components::ComponentType T> inline T* getComponent();

			template <Components::ComponentType T> inline std::vector<T*> getComponents();

			virtual ~Entity() =0;
		};

	}

	namespace Systems {
		export class System : public Core::Object {
		private:
			std::string name_;

		public:
			using Signature = std::bitset<10>;
			static constexpr Signature readComponents_ = 0b0;

			System(const std::string);

			virtual void update() const = 0;
			virtual void render() const = 0;

			virtual ~System() =0;
		};

	}

}

namespace GDE::Entities {
	template <Components::ComponentType T>
	inline void Entity::addComponent() {
		components_.push_back(new T());
	}

	template <Components::ComponentType T>
	inline const T* Entity::getComponent() const {
		for (Components::Component* comp : components_)
			if (comp->getSignature() == T::getSSignature())
				return static_cast<T*>(comp);

		return nullptr;
	}

	template <Components::ComponentType T>
	inline T* Entity::getComponent() {
		for (Components::Component* comp : components_)
			if (comp->getSignature() == T::getSSignature())
				return static_cast<T*>(comp);

		return nullptr;
	}

	template <Components::ComponentType T>
	inline std::vector<T*> Entity::getComponents() {
	}

}