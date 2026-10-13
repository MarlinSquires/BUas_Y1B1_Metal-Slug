#pragma once


// Global functions for use
namespace utils
{


	// Sign - taken from StackOverflow
	template <typename T> inline int sign(T value)
	{
		return (T(0) < value) - (value < T(0)); // Uses bools being 1 or 0 to return the sign of the value
	};

	// Returns distance between 2 positions
	float distance(float2 p1, float2 p2);


	// Randomization
	float random_range(float range); // Returns a value between -range and range
	bool flip();  // Randomly return true or false
	int rand_sign(); // Randomly returns +1 or -1




	inline int PosToIndex(int x, int y, int width) { return x + y * width; }

	inline int2 IndexToPos(int index, int width) // for 2d representation of linear array
	{
		int x = index % width;
		int y = index / width;

		return int2(x, y);
	}




	template <typename Tag>
	class bool_value
	{
	public:

		enum yes_no : bool
		{
			no = 0,
			yes = 1
		};

		

		// Bool comparison operator
		operator bool() const { return m_value == yes_no::yes;};

		// Constructor using enum
		bool_value(yes_no value) : m_value(value) {}

		// Constructor using bool - comverts the bool to enum and then calls the base constructor
		bool_value(const bool& value) : bool_value(value ? yes_no::yes : yes_no::no){}

		// Delete 
		bool_value(bool&& value) = delete;


	private:
		yes_no m_value;
	};



};

