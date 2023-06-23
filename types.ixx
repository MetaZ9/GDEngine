export module types;
import <tuple>;
import <vector>;

export typedef struct Vector2 {
	int x;
	int y;
} Vector2;

template <size_t I, typename T> class Tuple_N {
	template <typename ...Args> using type = typename Tuple_N<I - 1, T>::template type<T, Args...>;
};

template <typename T> class Tuple_N<0, T> {
	template <typename ...Args> using type = std::tuple<Args...>;
};

template <size_t I, typename T> using tuple_of = typename Tuple_N<I, T>::template type<>;

export template<int T> class Coordinate {
private:
	tuple_of<T, int> coordinates;

public:
	std::vector<int> getCoordinates() const;
	template<int U> int get() const;
};

template<int T>
std::vector<int> Coordinate<T>::getCoordinates() const{
	std::vector<int> values = std::vector<int>();

	for (unsigned int i = 0; i < std::tuple_size_v<Coordinate>; ++i)
		values.push_back(coordinates.get<i>());

	return values;
}

template<int T>
template<int U>
int Coordinate<T>::get() const{
	return std::get<U>(coordinates);
}

export typedef Coordinate<2> Position;
export typedef Coordinate<2> Size;			//-- Temporaire, Taille =/= Coordonnées