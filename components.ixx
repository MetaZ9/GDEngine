export module components;

import core;
import types;

namespace GDE {
	namespace Components {
		export class Transform : public Component {
		private:
			static constexpr Signature compSign_ = 0b01;

		public:
			Position pos_ = { 0, 0 };

		public:
			const Signature getSignature() const override;
			static const Signature getSSignature();

			~Transform() override;
		};

		export template <typename State>
		class StateComp : public Component {
		private:
			static constexpr Signature compSign_ = 0b10;

		public:
			State state_;

		public:
			const Signature getSignature() const override;
			static const Signature getSSignature();

			~StateComp() override;
		};

		export class SpriteComp : public Component {
		private:
			static constexpr Signature compSign_ = 0b10;

		public:
			const Signature getSignature() const override;
			static const Signature getSSignature();

			~SpriteComp() override;
		};

	}

}

namespace GDE::Components {
	template <typename State>
	const Component::Signature StateComp<State>::getSignature() const {
		return this->compSign_;
	}

	template <typename State>
	const Component::Signature StateComp<State>::getSSignature() {
		return StateComp<State>::compSign_;
	}

	template <typename State>
	StateComp<State>::~StateComp<State>() {

	}

}