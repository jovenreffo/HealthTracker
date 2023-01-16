#ifndef MEALPLAINFO_HPP
#define MEALPLANINFO_HPP

#include <wx/wx.h>
#include <vector>

/* MealPair
* The MealPair struct will be used for storing a string-string pair.
* The first string will be used for holding the meal name, and the second for holding the description.
*/

struct MealPair
{
	wxString m_mealName;
	wxString m_mealDesc;
};

/* MealPlanInfo
* The MealPlanInfo class will be used for storing vectors of MealPair/string-string pairs that correspond to their respective days.
* Several vectors will be instantiated, one for each day of the week. Because vectors allow for dynamic resizing, they are an obious choice.
*/

class MealPlanInfo
{
private:
	std::vector<MealPair> m_sunday;
	std::vector<MealPair> m_monday;
	std::vector<MealPair> m_tuesday;
	std::vector<MealPair> m_wednesday;
	std::vector<MealPair> m_thursday;
	std::vector<MealPair> m_friday;
	std::vector<MealPair> m_saturday;

public:
	MealPlanInfo() = default;

	// Getters
	const std::vector<MealPair>& GetSunday() const { return m_sunday; }
	const std::vector<MealPair>& GetMonday() const { return m_monday; }
	const std::vector<MealPair>& GetTuesday() const { return m_tuesday; }
	const std::vector<MealPair>& GetWednesday() const { return m_wednesday; }
	const std::vector<MealPair>& GetThursday() const { return m_thursday; }
	const std::vector<MealPair>& GetFriday() const { return m_friday; }
	const std::vector<MealPair>& GetSaturday() const { return m_saturday; }
};

#endif