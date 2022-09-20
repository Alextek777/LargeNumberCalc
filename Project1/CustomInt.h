#pragma once
#include <iostream>
#include <ostream>
#include <istream>

#include <list>
#include <vector>	
//#include <exception>
//
//
//class CustomIntException : public std::exception {
//
//};


class CustomInt{
	std::list<uint16_t> m_value;
	bool m_isNegative = false;
	
	void piecewiseAddition(const CustomInt& right);
	void piecewiseSubstraction(const CustomInt& right);

	void cleanFrontZeroes(std::list<uint16_t>& value);
	bool onlyZeroesLeft(std::list<uint16_t>::iterator left, std::list<uint16_t>::iterator right);
public:
	CustomInt();
	CustomInt(const std::string& str);
	CustomInt(std::list<uint16_t>::iterator begin, std::list<uint16_t>::iterator end);
	CustomInt(long value);
	~CustomInt();

	bool isNegative()const;
	void changeSign();
	const std::list<uint16_t>* getValue();

	static CustomInt* AbsGreater(CustomInt& first, CustomInt& second);
	CustomInt abs()const;

	friend std::ostream& operator<<(std::ostream& os, const CustomInt& val);

	friend CustomInt operator+(CustomInt left, const CustomInt& right);
	friend CustomInt operator-(CustomInt left, const CustomInt& right);
	friend CustomInt operator*(CustomInt left, const CustomInt& right);
	friend CustomInt operator/(CustomInt left, const CustomInt& right);

	CustomInt& operator+=(const CustomInt& rhs);
	CustomInt& operator-=(const CustomInt& rhs);
	CustomInt& operator*=(const CustomInt& rhs);
	CustomInt& operator/=(const CustomInt& rhs);

	friend bool operator< (const CustomInt& left, const CustomInt& right);
	friend bool operator> (const CustomInt& left, const CustomInt& right);
	friend bool operator<= (const CustomInt& left, const CustomInt& right);
	friend bool operator>= (const CustomInt& left, const CustomInt& right);
	friend bool operator== (const CustomInt& left, const CustomInt& right);
	friend bool operator== (const CustomInt& left, int right);
	friend bool operator!= (const CustomInt& left, const CustomInt& right);
	friend bool operator!= (const CustomInt& left, int right);
};

// ------------------------ inline functions begin -----------------------
inline bool operator< (const CustomInt& left, const CustomInt& right) {
	int left_val = left.m_value.size() * (left.isNegative() ? -1 : 1);
	int right_val = right.m_value.size() * (right.isNegative() ? -1 : 1);
	//check by digits
	if (left.m_value.size() != right.m_value.size())
		return left_val < right_val;

	//check by sign
	if (left.isNegative() && !right.isNegative())
		return true;
	if (!left.isNegative() && right.isNegative())
		return false;

	//same length and signs
	auto left_iterator = left.m_value.begin();
	auto right_iterator = right.m_value.begin();

	for (int i = 0; i < left.m_value.size(); i++) {
		if (*left_iterator != *right_iterator)
			return (*left_iterator < *right_iterator) /** left.isNegative()*/ ? 1 : 0;
		left_iterator++;
		right_iterator++;
	}

	//if they are equal
	return false;
}

inline bool operator> (const CustomInt& left, const CustomInt& right) {
	return right < left;
}

inline bool operator<= (const CustomInt& left, const CustomInt& right) {
	int left_val = left.m_value.size() * (left.isNegative() ? -1 : 1);
	int right_val = right.m_value.size() * (right.isNegative() ? -1 : 1);
	//check by digits
	if (left.m_value.size() != right.m_value.size())
		return left_val < right_val;

	//check by sign
	if (left.isNegative() && !right.isNegative())
		return true;
	if (!left.isNegative() && right.isNegative())
		return false;

	//same length and signs
	auto left_iterator = left.m_value.begin();
	auto right_iterator = right.m_value.begin();

	for (int i = 0; i < left.m_value.size(); i++) {
		if (*left_iterator != *right_iterator)
			return (*left_iterator < *right_iterator) * left.isNegative() ? 1 : 0;
	}

	//if they are equal
	return true;
}

inline bool operator>= (const CustomInt& left, const CustomInt& right) {
	return right <= left;
}

inline bool operator== (const CustomInt& left, const CustomInt& right) {
	return left.m_value == right.m_value && left.isNegative() == right.isNegative();
}

inline bool operator== (const CustomInt& left, int right) {
	return left == CustomInt(right);
}

inline bool operator!= (const CustomInt& left, const CustomInt& right) {
	return !(left == right);
}

inline bool operator!= (const CustomInt& left, int right) {
	return left != CustomInt(right);
}
// ------------------------ inline functions end -------------------------