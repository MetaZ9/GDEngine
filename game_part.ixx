export module game_part;
import <iostream>;
import <functional>;
import <map>;
import <concepts>;

namespace GDE {
	namespace GamePart {
		export class Object {};

		export class Player: public Object{};

		export class Terrain: public Object {};

		export enum GPMessageType {
			fail,
			win,
			draw,
			nextTurn,
			nothing
		};

		export class CRTPBase {
		public:
			virtual	void interface() = 0;
		};

		export template <typename Derived>
		class BaseRule: public CRTPBase {
		public:
			//template <typename... Args> void execute(Args&&... args) { std::cout << "Base" << std::endl; };
			virtual	const std::type_info& getTypeInfo() const = 0;
			void interface() override { /*std::cout << */ static_cast<Derived*>(this)->safeExecute();/* << std::endl;*/ };
			//template <typename... Args> void execute(Args&&... args) { ; };
			//inline void execute(this auto&& self) { self.execute(); };
		};

		/*template <typename Derived>
		class BR {
			virtual void execute() { (static_cast<Derived*>(this))->execute(); };
		};

		class R : public BR<R> {
			void execute() override { std::cout << "Child" << std::endl; };
		};*/

		export template <typename F>
		class GameRule : public BaseRule<GameRule<F>> {
		private:
			std::map<GPMessageType, CRTPBase*> successors;

		public:
			F action;
			GameRule(F);

			template <typename U>
			inline void						addSuccessor	(const GPMessageType, GameRule<U>&);
			inline void						removeSuccessor	(const GPMessageType);

			inline const std::type_info&	getTypeInfo()	const	override;

			template <typename... Args> requires std::invocable<F, Args...> void execute(Args&&...);
			inline void safeExecute() { ; };

			~GameRule();
		};

		template <typename F> GameRule<F>::GameRule(F _act)
			: action(_act) {
		}

		template <typename F> inline const std::type_info& GameRule<F>::getTypeInfo() const {
			return typeid(F);
		}

		template <typename F> template <typename U> inline void GameRule<F>::addSuccessor(const GPMessageType _mess, GameRule<U>& _rule) {
			std::cout << "Adding successor" << std::endl;
			std::cout << &_rule << std::endl;
			std::cout << typeid(_rule).name() << std::endl;
			//successors.emplace(_mess, std::make_unique<GameRule<U>>(_rule));

			//std::cout << _rule.getTypeInfo().name() << std::endl;
			successors[_mess] = &_rule;
			std::cout << "Successor added" << std::endl;
			std::cout << successors[_mess] << std::endl;
			std::cout << typeid(successors[_mess]).name() << std::endl;
		}

		template <typename F> inline void GameRule<F>::removeSuccessor(const GPMessageType _mess) {
			successors.erase(_mess);
		}

		template <typename F> template <typename... Args> requires std::invocable<F, Args...>
		void GameRule<F>::execute(Args&&... args) {
			GPMessageType result = std::invoke(action, std::forward<Args>(args)...);

			if (result != nothing) {
				auto it = successors.find(result);

				if (it != successors.end()) {
					std::cout << result << std::endl;
					auto next = it->second;
					next->interface();

				}

			}

		}

		template <typename F> GameRule<F>::~GameRule() {
			for (auto& [k, v] : successors)
				delete v;
		}

	}

}