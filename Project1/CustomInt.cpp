#include "CustomInt.h"

CustomInt::CustomInt() {
}

CustomInt::CustomInt(const std::string& str) {
	try{

		if (str[0] == '-')
			m_isNegative = true;

		for (int i = 0; i < str.size() - m_isNegative; i++)
			m_value.push_back((str[i + m_isNegative] - 48));

		cleanFrontZeroes(m_value);
	}

	catch (const std::exception& exception) {
		std::cout << "Error : " << exception.what() << std::endl;
	}
	catch (...) {
		std::cout << "Error : " << "undefined error";
	}
}

CustomInt::CustomInt(std::list<uint16_t>::iterator begin, std::list<uint16_t>::iterator end) {
	try {
		while (begin != end) {
			m_value.push_back(*begin);
			begin++;
		}
		m_value.push_back(*end);
	}
	catch (const std::exception& exception) {
		std::cout << "Error : " << exception.what() << std::endl;
	}
	catch (...) {
		std::cout << "Error : " << "undefined error";
	}
}

CustomInt::CustomInt(long value) {
	try {

		m_isNegative = value < 0;

		while (value != 0) {
			m_value.push_front(value % 10);
			value /= 10;
		}

		cleanFrontZeroes(m_value);
	}

	catch (const std::exception& exception) {
		std::cout << "Error : " << exception.what() << std::endl;
	}
	catch (...) {
		std::cout << "Error : " << "undefined error";
	}
}

CustomInt::~CustomInt() {

}

bool CustomInt::isNegative() const{
	return m_isNegative;
}

void CustomInt::changeSign() {
	m_isNegative = !m_isNegative;
}

std::ostream& operator<<(std::ostream& os, const CustomInt& val)
{
	if (val.m_value.size() == 0) {
		os << "0" << std::endl;
		return os;
	}

	os << (val.isNegative() ? "-" : "+");
	for (auto i : val.m_value)
		os << i;
	os << std::endl;

	return os;
}

CustomInt operator+(CustomInt left, const CustomInt& right) {
	left += right;
	return left;
}

CustomInt operator-(CustomInt left, const CustomInt& right) {
	left -= right;
	return left;
}

CustomInt operator*(CustomInt left, const CustomInt& right) {
	left *= right;
	return left;
}

CustomInt operator/(CustomInt left, const CustomInt& right) {
	left /= right;
	return left;
}

CustomInt& CustomInt::operator+=(const CustomInt& right) {
	if (isNegative() == right.isNegative())
		piecewiseAddition(right);
	else
		piecewiseSubstraction(right);

	return *this;
}

CustomInt& CustomInt::operator-=(const CustomInt& right) {
	CustomInt copy_right(right);
	copy_right.changeSign();	//equals to { copy_right * -1 } but faster

	if (isNegative() == right.isNegative())
		piecewiseSubstraction(copy_right);
	else
		piecewiseAddition(copy_right);

	return *this;
}

CustomInt& CustomInt::operator*=(const CustomInt& right) {
	std::vector<CustomInt*> result_for_sum;
	uint16_t remindor = 0;
	uint16_t current_value = 0;
	CustomInt* currentValue;

	//column multiplication algorithm
	for (auto i = right.m_value.rbegin(); i != right.m_value.rend(); i++) {
		remindor = 0;
		current_value = 0;
		currentValue = new CustomInt();
	
		for (int k = 0; k < result_for_sum.size(); k++)
			currentValue->m_value.push_back(0);

		for (auto j = m_value.rbegin(); j != m_value.rend(); j++) {
			current_value = (*i) * (*j) + remindor;
			remindor = current_value / 10;
			currentValue->m_value.push_front(current_value % 10);
		}
		result_for_sum.push_back(currentValue);
	}
	if (remindor != 0)
		result_for_sum.back()->m_value.push_front(remindor);

	CustomInt result;
	for (int i = 0; i < result_for_sum.size(); i++)
		result += *result_for_sum[i];

	for (int i = 0; i < result_for_sum.size(); i++)
		delete result_for_sum[i];

	cleanFrontZeroes(result.m_value);
	m_value = result.m_value;
	m_isNegative = m_isNegative == right.isNegative() ? 0 : 1;

	return *this;
}

CustomInt& CustomInt::operator/=(const CustomInt& right) {
	try {
		if (right == 0)
			throw std::exception("Error! Devision on zero!");
		CustomInt right_abs = right.abs();

		if (*this < right_abs) {
			m_value.clear();
			return *this;
		}

		CustomInt result;
		bool flag = true;
		auto cur_left = m_value.begin();
		auto cur_right = m_value.begin();
		for (int i = 0; i < right.m_value.size() -1; i++)
			cur_right++;

		CustomInt cur_part = CustomInt(cur_left, cur_right);
		for (int i = 0; i <= right.m_value.size() - m_value.size(); i++) {
			uint16_t curValue = 9;
			while (cur_part < (right_abs * curValue))
				curValue--;

			if (curValue == 0) {
				if (onlyZeroesLeft(cur_right, m_value.end()) && cur_part == 0) {
					while (cur_right != m_value.end()) {
						result.m_value.push_back(0);
						cur_right++;
					}
					break;
				}

				cur_right++;
				if (cur_right == m_value.end())
					break;
				cur_part = cur_part * 10 + *cur_right;
				continue;
			}

			result.m_value.push_back(curValue);
			if (cur_right == m_value.end() || ++cur_right == m_value.end())
				break;

			cur_part = (cur_part - (right_abs * curValue)) * 10 + *cur_right;
		}
		m_value = result.m_value;
		m_isNegative = m_isNegative == right.isNegative() ? 0 : 1;

		return *this;
	}
	catch (const std::exception exception) {
		std::cout << exception.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknow error" << std::endl;
	}

}

const std::list<uint16_t>* CustomInt::getValue() {
	return &m_value;
}

void CustomInt::piecewiseAddition(const CustomInt& right) {
	std::list<uint16_t>::reverse_iterator left_iter = m_value.rbegin();
	std::list<uint16_t>::const_reverse_iterator right_iter = right.m_value.rbegin();
	uint16_t reminder = 0;
	uint16_t current_value = 0;


	for (int i = 0; i < std::max(m_value.size(), right.m_value.size()); i++) {
		if (left_iter != m_value.rend()) {
			if (right_iter != right.m_value.rend()) {
				current_value = *left_iter + *right_iter + reminder;
				*left_iter = current_value % 10;
				reminder = current_value / 10;

				left_iter++;
				right_iter++;
			}
			else {
				*left_iter = *left_iter + reminder;
				reminder = 0;
				left_iter++;
			}
		}

		else {
			while (right_iter != right.m_value.rend()) {
				m_value.push_front(*right_iter + reminder);
				right_iter++;
				reminder = 0;
			}
			if (reminder != 0) 
				m_value.push_front(reminder);

			return;
		}
	}

	if (reminder != 0)
		m_value.push_front(reminder);
}

void CustomInt::piecewiseSubstraction(const CustomInt& right) {
	CustomInt* greatest = CustomInt::AbsGreater(*this, const_cast<CustomInt&>(right));

	//result is 0 if they are equal
	if (greatest == nullptr) {
		m_isNegative = false;
		m_value.clear();
		return;
	}

	m_isNegative = greatest->isNegative();
	CustomInt* smallest;
	if (greatest == this)
		smallest = const_cast<CustomInt*>(&right);
	else
		smallest = this;

	std::list<uint16_t> result;
	auto great_iter = greatest->m_value.rbegin();
	auto small_iter = smallest->m_value.rbegin();
	uint16_t reminder = 0;
	uint16_t curret_value;

	for (int i = 0; i < greatest->m_value.size(); i++) {
		if (small_iter != smallest->m_value.rend()) {
			if (*great_iter >= *small_iter + reminder) {
				curret_value = *great_iter - *small_iter - reminder;
				reminder = 0;
			}
			else {
				curret_value = 10 + *great_iter - *small_iter - reminder;
				reminder = 1;
			}

			result.push_front(curret_value);
			great_iter++;
			small_iter++;
		}
		else {
			curret_value = *great_iter - reminder;
			reminder = 0;
			result.push_front(curret_value);

			great_iter++;
		}
	}
	cleanFrontZeroes(result);
	m_value = result;
}

void CustomInt::cleanFrontZeroes(std::list<uint16_t>& value) {
	int count = 0;
	for (auto iter = value.begin(); iter != value.end(); iter++) {
		if (*iter != 0)
			break;

		count++;
	}
	for (int i = 0; i < count; i++)
		value.pop_front();
}

bool CustomInt::onlyZeroesLeft(std::list<uint16_t>::iterator left, std::list<uint16_t>::iterator right) {
	while (left != right) {
		if (*left != 0)
			return false;
		left++;
	}
	return true;
}

CustomInt* CustomInt::AbsGreater(CustomInt& first, CustomInt& second) {
	if (first.getValue()->size() != second.getValue()->size())
		return first.getValue()->size() > second.getValue()->size() ? &first : &second;

	auto iter1 = first.getValue()->begin();
	auto iter2 = second.getValue()->begin();
	while (iter1 != first.getValue()->end()) {
		if (*iter1 != *iter2)
			return *iter1 > *iter2 ? &first : &second;
		iter1++;
		iter2++;
	}
	
	//if they are equal;
	return nullptr;
}

CustomInt CustomInt::abs()const {
	CustomInt result = *this;
	result.m_isNegative = false;
	return result;
}