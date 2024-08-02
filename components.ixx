export module game_part.components;

import <iostream>;
import core;

namespace GDE {
	namespace Component {
		class LoggerComponent : public Core::Component {
		
		};

		class SquareCelledBoard : public Core::Component {
			
		};

	}

}

namespace GDE {
	namespace Components {
		export class LoggerComponent : public GDE::GamePart::Component {
		private:
			std::ostream& dest_;
			std::string format_;
			GDE::Game::State time_;


			//log format
			//log time
		public:
			static constexpr Signature compSign_ = 0b1;

			LoggerComponent(std::ostream& _dest = std::cout): dest_(_dest) {};

			virtual Signature getSignature() override {
				return LoggerComponent::compSign_;
			}

			static Signature getSSignature() {
				return LoggerComponent::compSign_;
			}

			void setDestination(std::ostream&) {};
			std::ostream& getDestination() { return dest_; };

			void setFormat(const std::string _format) { format_.assign(_format); };
			std::string getFormat() const { return format_; };

			void setTime(const GDE::Game::State _time) { time_ = _time; };
			GDE::Game::State getTime() const { return time_; };

			~LoggerComponent() {};
		};

		export template <typename CellType, unsigned int S>
		class SquareCelledBoardComponent : public GDE::GamePart::Component {

		};
	}

}