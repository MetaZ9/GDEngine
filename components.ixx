export module components;

import core;
import types;

namespace GDE {
	namespace Components {
		class LoggerComponent : public Component {
		
		};

		class SquareCelledBoard : public Component {
			
		};

		export class Transform : public Component {
		private:
			Position pos_;

		public:
			const Position getPosition() const;
			Position getPosition();
			void setPosition(const Position);
		};

		export template <typename State>
		class StateComp : public Component {
		private:
			State state_;

		public:
			const State getState() const;
			State getState();
			void setState(const State);
		};

	}

}

namespace GDE::Components {
	template <typename State>
	const State StateComp<State>::getState() const {
		return state_;
	}

	template <typename State>
	State StateComp<State>::getState() {
		return state_;
	}

	template <typename State>
	void StateComp<State>::setState(const State _state) {
		state_ = _state;
	}

}

//namespace GDE {
//	namespace Components {
//		export class LoggerComponent : public GDE::GamePart::Component {
//		private:
//			std::ostream& dest_;
//			std::string format_;
//			GDE::Game::State time_;
//
//
//			//log format
//			//log time
//		public:
//			static constexpr Signature compSign_ = 0b1;
//
//			LoggerComponent(std::ostream& _dest = std::cout): dest_(_dest) {};
//
//			virtual Signature getSignature() override {
//				return LoggerComponent::compSign_;
//			}
//
//			static Signature getSSignature() {
//				return LoggerComponent::compSign_;
//			}
//
//			void setDestination(std::ostream&) {};
//			std::ostream& getDestination() { return dest_; };
//
//			void setFormat(const std::string _format) { format_.assign(_format); };
//			std::string getFormat() const { return format_; };
//
//			void setTime(const GDE::Game::State _time) { time_ = _time; };
//			GDE::Game::State getTime() const { return time_; };
//
//			~LoggerComponent() {};
//		};
//
//		export template <typename CellType, unsigned int S>
//		class SquareCelledBoardComponent : public GDE::GamePart::Component {
//
//		};
//	}
//
//}