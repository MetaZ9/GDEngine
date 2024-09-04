module components;

namespace GDE::Components {
	const Component::Signature Transform::getSignature() const {
		return this->compSign_;
	}

	const Component::Signature Transform::getSSignature() {
		return Transform::compSign_;
	}

	Transform::~Transform() {

	}

}