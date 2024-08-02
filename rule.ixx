export module game_part.rule;
import <concepts>;
import <map>;
import gameplay;

namespace GDE {
	namespace GamePart {
		export class CRTPBase {
		public:
			virtual	void recoverTrueType() = 0;
		};

		template <typename Derived>
		class BaseRule : public CRTPBase {
		protected:
			std::map<GPMessageType, CRTPBase*> successors;

		public:
			inline void addSuccessor(const GPMessageType, CRTPBase&);
			inline void removeSuccessor(const GPMessageType);

			inline void recoverTrueType() override;

			~BaseRule();
		};

		template <typename Derived>
		void BaseRule<Derived>::addSuccessor(const GPMessageType _srcMsg, CRTPBase& _ruleTarget) {
			successors[_srcMsg] = &_ruleTarget;
		}

		template <typename Derived>
		void BaseRule<Derived>::removeSuccessor(const GPMessageType _srcMsg) {
			successors.erase(_srcMsg);
		}

		template <typename Derived>
		void BaseRule<Derived>::recoverTrueType() {
			static_cast<Derived*>(this)->safeExecute();
		}

		template <typename Derived>
		BaseRule<Derived>::~BaseRule() {
			for (auto& [k, v] : successors)
				delete v;
		}

		export template <typename B, typename... Args> requires std::invocable<B, Args...>
		class OuterRule : public BaseRule<OuterRule<B, Args...>> {
		public:
			B action;
			const unsigned int parameters;

			OuterRule(B, Args&&...);

			void safeExecute();
			void execute(Args&&...);
		};

		template <typename B, typename... Args> requires std::invocable<B, Args...>
		OuterRule<B, Args...>::OuterRule(B _havior, Args&&... _params)
			:action(_havior), parameters(sizeof...(_params)) {}

		template <typename B, typename... Args> requires std::invocable<B, Args...>
		void OuterRule<B, Args...>::safeExecute() {
			if (parameters == 0)
				execute();
			else
				;
		}

		template <typename B, typename... Args> requires std::invocable<B, Args...>
		void OuterRule<B, Args...>::execute(Args&&... args) {
			GPMessageType result = std::invoke(action, std::forward<Args>(args)...);
		}

		export template <typename B>
		class GameRule : public BaseRule<GameRule<B>> {

		public:
			B action;
			GameRule(B);

			template <typename... Args> requires std::invocable<B, Args...> void execute(Args&&...);
			inline void safeExecute() { ; };
		};

		template <typename B> GameRule<B>::GameRule(B _act)
			: action(_act) {
		}

		template <typename B> template <typename... Args> requires std::invocable<B, Args...>
		void GameRule<B>::execute(Args&&... args) {
			GPMessageType result = std::invoke(action, std::forward<Args>(args)...);

			if (result != nothing) {
				auto it = this->successors.find(result);

				if (it != this->successors.end()) {
					auto next = it->second;
					next->recoverTrueType();

				}

			}

		}

	}
}