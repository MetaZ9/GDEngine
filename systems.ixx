export module systems;

import core;

namespace GDE {
	namespace Systems {
		class LogSystem : public System {

		};

	}

}

//namespace GDE {
//	namespace GamePart {
//		export class LogSystem : public System {
//		public:
//			static constexpr Signature readComponents_ = 0b1;
//
//			void update() const override {};
//			void render() const override {
//				//get components with matching signature
//				std::vector<Components::LoggerComponent*> comps = Game::gameRef->getAllComponents<GDE::Components::LoggerComponent>();
//
//				for (Components::LoggerComponent* comp : comps)
//					if (GDE::Game::gameRef->getState() == comp->getTime())
//						comp->getDestination() << comp->getFormat();
//					//if (comp)
//			};
//
//		};
//
//	}
//
//}