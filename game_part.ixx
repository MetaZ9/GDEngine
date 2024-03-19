export module game_part;
import <iostream>;
import <functional>;
import <map>;
import <concepts>;

namespace GDE {
	namespace GamePart {
		export class Object {};

		export class Component: public Object{
		private:
			static const int signature;
		};

		template <typename T> concept ComponentType = std::is_base_of_v<Component, T>;

		export class Entity : public Object {
		private:
			std::string name;

		public:
			Entity() {};
			template <typename... Comps> Entity(std::string, Comps...);

			const std::string getName() const;
			std::string getName();

			inline void addComponent(const Component*);
			template <ComponentType T> inline void addComponent();

			template <ComponentType T> inline const Component* getComponent() const;
			template <ComponentType T> inline Component* getComponent();

			template <ComponentType T> inline Component** getComponents();

			~Entity() {};
		};

		export class Player: public Entity{
		private:
			const unsigned int number_;

		public:
			Player(const unsigned int _number) :number_(_number) {};

			inline const unsigned int number() const { return number_; };
		};

		export class Terrain: public Entity {};

		export template <typename CState>
		class Cell {
		private:
			CState value_;

		public:
			Cell();
			Cell(CState);

			inline const CState& getValue() const;
			inline CState& getValue();
			inline void setValue(CState);

			~Cell();
		};

		template <typename CState>
		Cell<CState>::Cell() {};

		template <typename CState>
		Cell<CState>::Cell(CState _val)
			:value_(_val)
		{};

		template <typename CState>
		inline const CState& Cell<CState>::getValue() const {
			return value_;
		};

		template <typename CState>
		inline CState& Cell<CState>::getValue() {
			return value_;
		};

		template <typename CState>
		inline void Cell<CState>::setValue(CState _newValue) {
			value_ = _newValue;
		};

		template <typename CState>
		Cell<CState>::~Cell() {
			//if (std::is_pointer_v<CState> == true)
				//delete value_;
		};


		export template <typename CellType, int S>
		class SquareCelledBoard {
		private:
			Cell<CellType> cells_[S];
			const unsigned int boardSize = S;

		public:
			SquareCelledBoard(CellType);

			inline Cell<CellType>* const getCells() const;
			inline Cell<CellType>* getCells();

			inline const Cell<CellType>& getCell(const unsigned int) const;
			inline Cell<CellType>& getCell(const unsigned int);
			inline void setCell(const unsigned int, const Cell<CellType>);

			~SquareCelledBoard();
		};

		template <typename CellType, int S>
		SquareCelledBoard<CellType, S>::SquareCelledBoard(CellType _initialValue) {
			for (unsigned int i = 0; i < boardSize; ++i)
				cells_[i].setValue(_initialValue);
		};

		template <typename CellType, int S>
		inline Cell<CellType>* const SquareCelledBoard<CellType, S>::getCells() const {
			return cells_;
		};

		template <typename CellType, int S>
		inline Cell<CellType>* SquareCelledBoard<CellType, S>::getCells() {
			return cells_;
		};

		template <typename CellType, int S>
		inline const Cell<CellType>& SquareCelledBoard<CellType, S>::getCell(const unsigned int _at) const {
			return cells_[_at];
		};

		template <typename CellType, int S>
		inline Cell<CellType>& SquareCelledBoard<CellType, S>::getCell(const unsigned int _at) {
			return cells_[_at];
		};

		template <typename CellType, int S>
		inline void SquareCelledBoard<CellType, S>::setCell(const unsigned int _at, Cell<CellType> _cell) {
			cells_[_at] = _cell;
		};

		template <typename CellType, int S>
		SquareCelledBoard<CellType, S>::~SquareCelledBoard() {
			//for (unsigned int i = 0; i < S; i++)
				//delete cells_[i];

			//delete[] cells_;
		};

		export enum GPMessageType {
			fail,
			win,
			draw,
			nextTurn,
			nothing
		};

		export class CRTPBase {
		public:
			virtual	void recoverTrueType() = 0;
		};



		template <typename Derived>
		class BaseRule: public CRTPBase {
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

		template <typename D>
		BaseRule<D>::~BaseRule() {
			for (auto& [k, v] : successors)
				delete v;
		}



		export template <typename B, typename... Args> requires std::invocable<B, Args...>
		class InnerRule : public BaseRule<InnerRule<B, Args...>> {
		public:
			B action;
			const unsigned int parameters;

			InnerRule(B, Args&&...);

			void safeExecute();
			void execute(Args&&...);
		};

		template <typename B, typename... Args> requires std::invocable<B, Args...>
		InnerRule<B, Args...>::InnerRule(B _havior, Args&&... _params)
			:action(_havior), parameters(sizeof...(_params)) {}

		template <typename B, typename... Args> requires std::invocable<B, Args...>
		void InnerRule<B, Args...>::safeExecute() {
			if (parameters == 0)
				execute();
			else
				;
		}

		template <typename B, typename... Args> requires std::invocable<B, Args...>
		void InnerRule<B, Args...>::execute(Args&&... args) {
			GPMessageType result = std::invoke(action, std::forward<Args>(args)...);
		}



		export template <typename B>
		class GameRule : public BaseRule<GameRule<B>> {

		public:
			B action;
			GameRule(B);

			template <typename... Args> requires std::invocable<B, Args...> void execute(Args&&...);
			inline void safeExecute() { ; };

			//~GameRule();
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