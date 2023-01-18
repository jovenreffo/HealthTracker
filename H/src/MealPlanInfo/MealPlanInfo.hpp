#ifndef MEALPLAINFO_HPP
#define MEALPLANINFO_HPP

#include <wx/wx.h>
#include <vector>

/* MealInfo
* The MealInfo struct will be used for storing a string-string pair.
* The first string will be used for holding the meal name, and the second for holding the description.
*/

struct MealInfo
{
	wxString m_mealName;
	wxString m_mealDesc;
	wxString m_dayString;
	int m_dayIndex;
};

/* MealPlanInfo
* The MealPlanInfo class will be used for storing vectors of MealInfo/string-string pairs that correspond to their respective days.
* Several vectors will be instantiated, one for each day of the week. Because vectors allow for dynamic resizing, they are an obious choice.
*/

/* Notes
* We have nested vectors, as MealPlanInfo has been instantiated as std::vector<MealPlanInfo> in MealPlanWindow.
* It is stored as a vec in MPW because the items will then be saved to a list, and each meal plan needs to be accessed. 
*/

class MealPlanInfo
{
private:
	std::vector<MealInfo> m_sunday;
	std::vector<MealInfo> m_monday;
	std::vector<MealInfo> m_tuesday;
	std::vector<MealInfo> m_wednesday;
	std::vector<MealInfo> m_thursday;
	std::vector<MealInfo> m_friday;
	std::vector<MealInfo> m_saturday;

public:
	MealPlanInfo() = default;

	// Getters
	const std::vector<MealInfo>& GetSunday() const { return m_sunday; }
	const std::vector<MealInfo>& GetMonday() const { return m_monday; }
	const std::vector<MealInfo>& GetTuesday() const { return m_tuesday; }
	const std::vector<MealInfo>& GetWednesday() const { return m_wednesday; }
	const std::vector<MealInfo>& GetThursday() const { return m_thursday; }
	const std::vector<MealInfo>& GetFriday() const { return m_friday; }
	const std::vector<MealInfo>& GetSaturday() const { return m_saturday; }
};

#endif