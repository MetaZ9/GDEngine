module components;

namespace GDE::Components {
	const Position Transform::getPosition() const {
		return pos_;
	}

	Position Transform::getPosition() {
		return pos_;
	}

	void Transform::setPosition(const Position _pos) {
		pos_ = _pos;
	}

}