export module types;
import <tuple>;
import <vector>;
import <cstdarg>;

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

export template<int T> class IntSet {
protected:
	//tuple_of<T, int> values;
	int values[];

public:
	IntSet(int, int...);

	int* getValues() const;
	int get(const unsigned int) const;
	//std::vector<int> getValues() const;
	//template<int U> int get() const;
};

template<int T>
IntSet<T>::IntSet(int T, int...)
	//:values(tuple_of<T, int>())
{
	// values = tuple_of<T, int>();

	std::va_list args;
	va_start(args, T);
	//auto val = std::make_tuple(args);
//	std::get<0>(val);
	for (unsigned int i = 0; i < T; ++i)
		values[i] = va_arg(args, int);
		//std::get<i>(values);
		//std::get<i>(values) = va_arg(args, int);

	va_end(args);
}
/*
template<int T>
std::vector<int> IntSet<T>::getValues() const{
	std::vector<int> retValues = std::vector<int>();

	for (unsigned int i = 0; i < std::tuple_size_v<IntSet>; ++i)
		retValues.push_back(values.get<i>());

	return retValues;
}
*/
template<int T>
int* IntSet<T>::getValues() const {
	return values;
}

template<int T>
int IntSet<T>::get(const unsigned int i) const {
	return values[i];
}

/*
template<int T>
template<int U>
int IntSet<T>::get() const{
	return std::get<U>(values);
}*/
/*
template <> class Coordinate<2> {
protected:
	tuple_of<2, int> coordinates;

};

export class Position : public Coordinate<2> {
public:
	Position(const int, const int);

	template<int U> int get() const;
};

Position::Position(const int x, const int y)
{
	std::get<0>(coordinates) = x;
	std::get<1>(coordinates) = y;
}

template<int U>
int Position::get() const {
	return Coordinate<2>::get<U>();
}
*/
export typedef IntSet<2> Position;
export typedef IntSet<2> Size;