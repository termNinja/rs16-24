#include <iostream>
#include "class.hpp"
#include "membervisibility.hpp"
#include "relationmanager.hpp"

namespace codegen {

Class::Class(std::string className)
	: m_name(className)
{}

Class::Class(std::string className, std::vector<MemberFunction> memberFunctions)
	: m_name(className)
{
	filterMemberFunctions(memberFunctions);
}

Class::Class(std::string className, std::vector<MemberVariable> memberVariables)
	: m_name(className)
{
	filterMemberVariables(memberVariables);
}

Class::Class(std::string className, std::vector<MemberFunction> memberFunctions, std::vector<MemberVariable> memberVariables)
	: m_name(className)
{
	filterMemberFunctions(memberFunctions);
	filterMemberVariables(memberVariables);
}

Class::Class(std::string className,
			 std::vector<MemberConstructor> memberConstructors,
			 std::vector<MemberFunction> memberFunctions,
			 std::vector<MemberVariable> memberVariables)
	: m_name(className)
{
	filterMemberConstructors(memberConstructors);
	filterMemberFunctions(memberFunctions);
	filterMemberVariables(memberVariables);
}

Class::Class(std::string className, std::vector<Member *> &members)
	: m_name(className)
{
	std::vector<MemberConstructor> conz;
	std::vector<MemberFunction> funz;
	std::vector<MemberVariable> varz;

	std::cerr << "Started classifing" << std::endl;
	for (auto member : members) {
		switch (member->getMemberType()) {
		case MEMBER_CONSTRUCTOR:
			conz.push_back(*(static_cast<MemberConstructor*>(member))); break;
		case MEMBER_FUNCTION:
			funz.push_back(*(static_cast<MemberFunction*>(member))); break;
		case MEMBER_VARIABLE:
			varz.push_back(*(static_cast<MemberVariable*>(member))); break;
		}
	}
	std::cerr << "Finished classifing. Begin filtering." << std::endl;

	filterMemberConstructors(conz);
	std::cerr << "Filtered construcors." << std::endl;
	filterMemberFunctions(funz);
	std::cerr << "Filtered functions." << std::endl;
	filterMemberVariables(varz);
	std::cerr << "Filtered variables. Class constructed." << std::endl;
}

Class::Class(std::string name, std::vector<MemberFunction> pubMemFun,
			 std::vector<MemberFunction> privMemFun,
			 std::vector<MemberFunction> protMemFun,
			 std::vector<MemberVariable> pubMemVar,
			 std::vector<MemberVariable> privMemVar,
			 std::vector<MemberVariable> protMemVar)
	: m_name(name), m_pubMemFun(pubMemFun), m_privMemFun(privMemFun), m_protMemFun(protMemFun),
	  m_pubMemVar(pubMemVar), m_privMemVar(privMemVar), m_protMemVar(protMemVar)
{
}

Class::~Class()
{
	RelationManager *rm = RelationManager::instance();
	rm->deleteNonExistingRelations();
}

std::vector<MemberFunction> &Class::getPublicMemberFunctions()
{
	return m_pubMemFun;
}

std::vector<MemberFunction> &Class::getPrivateMemberFunctions()
{
	return m_privMemFun;
}

std::vector<MemberFunction> &Class::getProtectedMemberFunctions()
{
	return m_protMemFun;
}

std::vector<MemberVariable> &Class::getPublicMemberVariables()
{
	return m_pubMemVar;
}

std::vector<MemberVariable> &Class::getPrivateMemberVariables()
{
	return m_privMemVar;
}

std::vector<MemberVariable> &Class::getProtectedMemberVariables()
{
	return m_protMemVar;
}

std::vector<MemberConstructor>& Class::getPublicConstructors()
{
	return m_pubConst;
}

std::vector<MemberConstructor> &Class::getPrivateConstructors()
{
	return m_privConst;
}

std::vector<MemberConstructor> &Class::getProtectedConstructors()
{
	return m_protConst;
}

void Class::addConstructor(MemberConstructor &c)
{
	if (c.getVisibility() == MemberVisibility::PRIVATE)
		m_privConst.push_back(c);
	else if (c.getVisibility() == MemberVisibility::PROTECTED)
		m_protConst.push_back(c);
	else if (c.getVisibility() == MemberVisibility::PUBLIC)
		m_pubConst.push_back(c);
}

std::string Class::getName() const
{
	return m_name;
}

void Class::setName(std::string name)
{
	m_name = name;
}

const std::vector<const Class *> Class::getClassesThatInherit() const
{
	RelationManager *rm = RelationManager::instance();
	return rm->getClassesThatInheritArgument(this);
}

const std::vector<const Class *> Class::getClassesThatClassInherits() const
{
	RelationManager *rm = RelationManager::instance();
	return rm->getClassesThatArgumentInherits(this);
}

void Class::filterMemberFunctions(std::vector<MemberFunction> memberFunctions)
{
	for (auto memFun : memberFunctions) {
		if (memFun.getVisibility() == MemberVisibility::PUBLIC)
			m_pubMemFun.push_back(memFun);
		else if (memFun.getVisibility() == MemberVisibility::PRIVATE)
			m_privMemFun.push_back(memFun);
		else if (memFun.getVisibility() == MemberVisibility::PROTECTED)
			m_protMemFun.push_back(memFun);
	}
}

void Class::filterMemberVariables(std::vector<MemberVariable> memberVariables)
{
	for (auto memVar : memberVariables) {
		if (memVar.getVisibility() == MemberVisibility::PUBLIC)
			m_pubMemVar.push_back((memVar));
		else if (memVar.getVisibility() == MemberVisibility::PRIVATE)
			m_privMemVar.push_back(memVar);
		else if (memVar.getVisibility() == MemberVisibility::PROTECTED)
			m_protMemVar.push_back(memVar);
	}
}

void Class::filterMemberConstructors(std::vector<MemberConstructor> memberConstuctors)
{
	for (auto memCon : memberConstuctors) {
		if (memCon.getVisibility() == MemberVisibility::PRIVATE)
			m_privConst.push_back(memCon);
		else if (memCon.getVisibility() == MemberVisibility::PROTECTED)
			m_protConst.push_back(memCon);
		else if (memCon.getVisibility() == MemberVisibility::PUBLIC)
			m_pubConst.push_back(memCon);
	}
}

std::ostream &operator<<(std::ostream &out, const Class &c)
{
	std::string sep = "    ";
	out << "class " << c.m_name << " {\n";

	if (!c.m_pubMemFun.empty() || !c.m_pubMemVar.empty()) {
		// write public content
		out << "public:\n";
		for (auto a : c.m_pubMemFun) out << sep << a << "\n";
		for (auto a : c.m_pubMemVar) out << sep << a << "\n";
	}

	if (!c.m_protMemFun.empty() || !c.m_protMemVar.empty()) {
		// write protected content
		out << "protected:\n";
		for (auto a : c.m_protMemFun) out << sep << a << "\n";
		for (auto a : c.m_protMemVar) out << sep << a << "\n";
	}

	if (!c.m_privMemFun.empty() || !c.m_privMemVar.empty()) {
		// write private content
		out << "private:\n";
		for (auto a : c.m_privMemFun) out << sep << a << "\n";
		for (auto a : c.m_privMemVar) out << sep << a << "\n";
	}

	// close down class
	out << "};";
	return out;
}

} // namespace end: codegen
