#include "relationmanager.hpp"
#include <utility>
#include <algorithm>
#include <iostream>

namespace codegen {

RelationManager::RelationManager()
{
}

std::string RelationManager::showMap(const map<const Class *, set<const Class *> > &map, std::string msg) const
{
	std::string s;

	if (map.empty()) return "";

	if (msg != "")
		s.append(msg + "\n");
	for (auto i = map.cbegin(); i != map.cend(); i++) {
		s.append(i->first->getName() + ": ");
		for (auto j = i->second.cbegin(); j != i->second.cend(); j++)
			s.append((*j)->getName() + " ");
		s.append("\n");
	}

	return s.append("\n");
}

unsigned RelationManager::cleanMap(map<const Class *, set<const Class *> > &map)
{
	unsigned deletedRecords = 0;
	std::set<const Class*>::iterator setIter;

	// associative-container erase idiom
	for (auto it = map.begin(); it != map.end();) {
		if (it->first == nullptr) {
			map.erase(it++);
			++deletedRecords;
		} else if ((setIter = std::find(it->second.cbegin(), it->second.cend(), nullptr)) != it->second.cend()) {
			deletedRecords += cleanSet(it->second);
			++it;
			++deletedRecords;
		}
		else {
			++it;
		}
	}

	return deletedRecords;
}

unsigned RelationManager::cleanSet(set<const Class *> &s)
{
	unsigned deletedRecords = 0;
	for (auto it = s.cbegin(); it != s.cend();) {
		if ((*it) == nullptr) {
			s.erase(it++); ++deletedRecords;
		} else ++it;
	}

	return deletedRecords;
}

RelationManager *codegen::RelationManager::instance()
{
	static RelationManager rm;
	return &rm;
}

unsigned RelationManager::deleteNonExistingRelations()
{
	// removes nulls from maps -> important to keep relation manager up to date with destroyed classes
	unsigned deletedRecords = 0;
	deletedRecords += cleanMap(m_aggregation);
	deletedRecords += cleanMap(m_association);
	deletedRecords += cleanMap(m_composition);
	deletedRecords += cleanMap(m_dependency);
	deletedRecords += cleanMap(m_whoDoesKeyInherit);
	deletedRecords += cleanMap(m_keyIsInheritedBy);
	return deletedRecords;
}

void RelationManager::addInheritanceRelation(const Class *imInherited, const Class *imInheriting)
{
	m_keyIsInheritedBy[imInherited].insert(imInheriting);
	m_whoDoesKeyInherit[imInheriting].insert(imInherited);
	m_using[imInheriting].insert(imInherited);
}

void RelationManager::addAssociationRelation(const Class *A, const Class *B)
{
	m_association[A].insert(B);
	m_using[A].insert(B);
}

void RelationManager::addDependencyRelation(const Class *A, const Class *B)
{
	m_dependency[A].insert(B);
	m_using[A].insert(B);
}

void RelationManager::addCompositionRelation(const Class *A, const Class *B)
{
	m_composition[A].insert(B);
	m_using[A].insert(B);
}

void RelationManager::addAggregationRelation(const Class *A, const Class *B)
{
	m_aggregation[A].insert(B);
	m_using[A].insert(B);
}

std::vector<const Class *> RelationManager::getClassesThatInheritArgument(const Class *cls) const
{
	std::vector<const Class *> res;

	const auto finder = m_keyIsInheritedBy.find(cls);
	if (finder == m_keyIsInheritedBy.cend())
		return res;

	for (auto iter = res.cbegin(); iter != res.cend(); iter++)
		res.push_back(*iter);

	return res;
}

std::vector<const Class *> RelationManager::getClassesThatArgumentInherits(const Class *cls) const
{
	std::vector<const Class *> res;

	const auto finder = m_whoDoesKeyInherit.find(cls);
	if (finder == m_whoDoesKeyInherit.cend())
		return res;

	// We iterate over set that contains classes that inherit given class
	auto setOfElements = finder->second;
	for (auto elem : setOfElements) {
		res.push_back(elem);
	}

	std::cout << "Formed inheritance vector: " << std::endl;
	for (auto c : res)
		std::cout << c->getName() << " ";

	return res;
}

std::set<const Class *> RelationManager::getAllClassesThatUseGivenClass(const Class *cls) const
{
	const auto i = m_using.find(cls);
	if (i != m_using.cend())
		return i->second;
	return std::set<const Class*>();
}

std::ostream& operator <<(std::ostream &out, const RelationManager &rm)
{
	out << rm.showMap(rm.m_whoDoesKeyInherit, "Class A inherits: B, C, D...:");
	out << rm.showMap(rm.m_aggregation, "Aggregation relations:");
	out << rm.showMap(rm.m_composition, "Composition relations:");
	out << rm.showMap(rm.m_dependency, "Dependency relations:");
	out << rm.showMap(rm.m_association, "Association relations:");
	return out;
}

} // namespace end: codegen
