#ifndef TOTAL_HPP
#define TOTAL_HPP

struct Total
{
	int m_calTotal;
	int m_carbTotal;
	int m_proteinTotal;
	int m_fiberTotal;

	void ResetTotal()
	{
		m_calTotal = 0;
		m_carbTotal = 0;
		m_proteinTotal = 0;
		m_fiberTotal = 0;
	}

	Total& operator++()
	{
		++m_calTotal;
		++m_carbTotal;
		++m_proteinTotal;
		++m_fiberTotal;

		return *this;
	}

	Total& operator--()
	{
		--m_calTotal;
		--m_carbTotal;
		--m_proteinTotal;
		--m_fiberTotal;

		return *this;
	}
};

class NutrientContent
{
private:
	int m_calories, m_protein, m_carbohydrates, m_fiber;

public:
	NutrientContent(int calories, int protein, int carbohydrates, int fiber)
		: m_calories{ calories }, m_protein{ protein }, m_carbohydrates{ carbohydrates }, m_fiber{ fiber }
	{ }

	const int GetCalories() const { return m_calories; }
	const int GetProtein() const { return m_protein; }
	const int GetCarbohydrates() const { return m_carbohydrates; }
	const int GetFiber() const { return m_fiber; }
};

#endif