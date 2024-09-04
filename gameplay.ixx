export module gameplay;

import <concepts>;
import <map>;

namespace GDE {
	namespace Rule {
		export class CRTPRule {
		public:
			virtual	void recoverTrueType() = 0;
		};

		export enum GPMessageType {
			fail,
			win,
			draw,
			nextTurn,
			nothing,
			end
		};

		template <typename Derived>
		class BaseRule : public CRTPRule {
		protected:
			std::map<GPMessageType, CRTPRule*> successors;

		public:
			inline void addSuccessor(const GPMessageType, CRTPRule&);
			inline void removeSuccessor(const GPMessageType);

			inline void recoverTrueType() override;

			~BaseRule();
		};

		template <typename Derived>
		void BaseRule<Derived>::addSuccessor(const GPMessageType _srcMsg, CRTPRule& _ruleTarget) {
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
				v = nullptr;

			successors.clear();
		}

		export template <typename B>
		class InnerRule : public BaseRule<InnerRule<B>> {
		public:
			B action;
		public:
			InnerRule(B);

			template <typename... Args> requires std::invocable<B, Args...> void execute(Args&&...);

			inline const B getAction() const {
				return action;
			};

			inline void safeExecute() { ; };
		};

		template <typename B> InnerRule<B>::InnerRule(B _act)
			: action(_act) {
		}

		template <typename B> template <typename... Args> requires std::invocable<B, Args...>
		void InnerRule<B>::execute(Args&&... args) {
			GPMessageType result = std::invoke(action, std::forward<Args>(args)...);

			if (result != nothing) {
				auto it = this->successors.find(result);

				if (it != this->successors.end()) {
					auto next = it->second;
					next->recoverTrueType();

				}

			}

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

	}

}