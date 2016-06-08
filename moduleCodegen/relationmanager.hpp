#ifndef RELATIONMANAGER_HPP
#define RELATIONMANAGER_HPP

#include <map>
#include <vector>
#include <set>
#include <string>
#include "class.hpp"

using std::map;
using std::vector;
using std::set;

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Different relations - (very) short manual
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//	* Association 	(knows a)
//	* Dependency 	(uses a)
//	* Composition 	(has a)
//	* Aggregation 	(has a)
//  * Inheritance 	(is a)
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

namespace codegen {

class RelationManager {
public:
	static RelationManager* instance();

	unsigned deleteNonExistingRelations();

	void addAssociationRelation(const Class* A, const Class* B);
	void addDependencyRelation(const Class* A, const Class* B);
	void addCompositionRelation(const Class* A, const Class* B);
	void addAggregationRelation(const Class* A, const Class* B);
	void addInheritanceRelation(const Class* A, const Class* B);

	/**
	 * @brief Gives classes that inherit class given as argument.
	 * @param cls Class for which we search classes that inherit it.
	 * @return Vector of classes that inherit class given as argument.
	 */
	std::vector<const Class*> getClassesThatInheritArgument(const Class* cls) const;


	/**
	 * @brief Gives classes that class given as argument inherits.
	 * @param cls Class for which we wish to find class that in inherits.
	 * @return Vector of classes that contains classes that are inherited by class given as argument.
	 */
	std::vector<const Class*> getClassesThatArgumentInherits(const Class* cls) const;

	std::vector<const Class*> getAssociationClasses(const Class* cls) const;
	std::vector<const Class*> getDependencyClasses(const Class* cls) const;
	std::vector<const Class*> getAggregationClasses(const Class* cls) const;
	std::set<const Class*> getAllClassesThatUseGivenClass(const Class* cls) const;

	friend std::ostream& operator <<(std::ostream &out, const RelationManager &rm);

private:
	RelationManager();
	RelationManager& operator=(const RelationManager &rm) = delete;
	RelationManager& operator=(const RelationManager &&rm) = delete;
	RelationManager(const RelationManager &rm) = delete;
	RelationManager(const RelationManager &&rm) = delete;

	std::string showMap(const map<const Class*, set<const Class*> > &map, std::string msg = "") const;

	unsigned cleanMap(map<const Class*, set<const Class*> > &map);
	unsigned cleanSet(set<const Class*> &s);

	// Class A is using B, C, D IN SOME WAY mapped by other members
	map<const Class*, set<const Class*> > m_using;

protected:
	// m_inher = {"Shape" -> ["Rectangle", "Circle"]}
	// Shape is inherited by Rectangle and Circle (pretending we're working with strings instead of Class*
	map<const Class*, set<const Class*> > m_keyIsInheritedBy;
	map<const Class*, set<const Class*> > m_whoDoesKeyInherit;

	// A -> {B, C, D}
	// Class A knows classes B, C, D
	map<const Class *, set<const Class *> > m_association;

	// Class A uses B, C, D
	map<const Class *, set<const Class*> > m_dependency;

	// Class A has B, C, D
	map<const Class *, set<const Class*> > m_composition;

	// Class A has B, C, D
	map<const Class *, set<const Class*> > m_aggregation;


};

} // namespace end: codegen

#endif // RELATIONMANAGER_HPP
