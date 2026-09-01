#pragma once

#include "precomp.h"


// Global functions for use
namespace utils
{

	// Math functions //

	// Sign - taken from StackOverflow
	template <typename T> inline int sign(T value)
	{
		return (T(0) < value) - (value < T(0)); // Uses bools being 1 or 0 to return the sign of the value
	};

	// Returns distance between 2 positions
	// Accepts both float and int
	inline float distance(Tmpl8::float2 p1, Tmpl8::float2 p2)
	{
		float xDistance = abs(p1.x - p2.x);
		float yDistance = abs(p1.y - p2.y);

		return (float)abs(sqrt((xDistance * xDistance) + (yDistance * yDistance))); // Finding hypotenuse
	}


	// Returns a value between -range and range
	inline float random_range(float range)
	{
		// Bit of a hacky way to get a random range but i think it works?
		float r = Rand(2 * range);

		if (r > range)
		{
			r -= range;
			r *= -1;
		}
		return r;
	}

	inline bool flip() // Randomly return true or false
	{
		return (int)round(Rand(1)); // rounds to either 1 or 0
	}

	inline int rand_sign() // Randomly returns +1 or -1
	{
		return sign(
			Rand(1) - 0.5f); // Returns a number between -0.5 and 0.5
	}





	// I dont think this is gonna work
	template <typename T> class generic_array
	{
	public:


		generic_array(int size) : size(size)
		{
			items = new T[size];
		}

		T* get(int i)
		{
			if (i >= size) return nullptr;
			return items[i];
		}

		void set(int i, T item)
		{
			if (i >= size) return;
			items[i] = item;
		}

		int get_size()
		{
			return size;
		}


	private:
		T* items;
		int size;

	};


};

