#ifndef CLASS_HPP
#define CLASS_HPP

#include <string>
#include <vector>
#include "type.hpp"
#include "membervariable.hpp"
#include "memberfunction.hpp"
#include "memberconstructor.hpp"

namespace codegen {

class Class {
public:
	/**
	 *  \brief Constructor for Class for given name
	 *  \param name Name of the constructed class
	 */
	Class(std::string name);

    // NOTE: Going to get removed in newer versions
	Class(std::string className, std::vector<MemberFunction> memberFunctions);

	// NOTE: Going to get removed in newer versions
	Class(std::string className, std::vector<MemberVariable> memberVariables);

	// NOTE: Going to get removed in newer versions
	Class(std::string className, std::vector<MemberFunction> memberFunctions, std::vector<MemberVariable> memberVariables);

	// MAIN constructor
	/**
	 *  \brief Constructor for Class for given members.
	 *  \param className Name of the constructed class
	 *  \param memberConstructors Vector of constructors that belong to the class
	 *  \param memberFunctions Vector of functions that belong to the class
	 *  \param memberVariables Vector of variables that belong to the class (they can also be static)
	 */
	Class(std::string className,
		  std::vector<MemberConstructor> memberConstructors,
		  std::vector<MemberFunction> memberFunctions,
		  std::vector<MemberVariable> memberVariables);

	/**
	 *  \brief Constructor for Class for given vector of members.
	 *
	 *  \param className Name of the constructed class
	 *  \param members Instantiates class data and filters given members by visibility (public, protected, private)
	 * 		and then separates them into MemberConstructor, MemberFunction and MemberVariable
	 */
	Class(std::string className, std::vector<Member *> &members);

	// NOTE: Going to get removed in newer versions
	Class(
			std::string name,
			std::vector<MemberFunction> pubMemFun,
			std::vector<MemberFunction> privMemFun,
			std::vector<MemberFunction> protMemFun,
			std::vector<MemberVariable> pubMemVar,
			std::vector<MemberVariable> privMemVar,
			std::vector<MemberVariable> protMemVar
	);

	~Class();

	// These getters allow you to add new members into class
	// because they return vectors by reference
	std::vector<MemberFunction>& getPublicMemberFunctions();
	std::vector<MemberFunction>& getPrivateMemberFunctions();
	std::vector<MemberFunction>& getProtectedMemberFunctions();
	std::vector<MemberVariable>& getPublicMemberVariables();
	std::vector<MemberVariable>& getPrivateMemberVariables();
	std::vector<MemberVariable>& getProtectedMemberVariables();
	std::vector<MemberConstructor>& getPublicConstructors();
	std::vector<MemberConstructor>& getPrivateConstructors();
	std::vector<MemberConstructor>& getProtectedConstructors();

	/**
	 *  \brief Adds a new constructor onto class object.
	 *
	 *  \param newConstructor New constructor to be added.
	 */

	void addConstructor(MemberConstructor newConstructor);

	/**
	 *  \brief Returns the class name.
	 *
	 *  \param newConstructor New constructor to be added
	 *  \return String representation of class name
	 */
	std::string getName() const;

	/**
	 *  \brief Sets a class name.
	 *
	 *  \param name New name for class.
	 */
	void setName(std::string name);

	const std::vector<const Class *> getClassesThatInherit() const;
	const std::vector<const Class *> getClassesThatClassInherits() const;


	friend std::ostream& operator<<(std::ostream& out, const Class &c);

private:
	std::string m_name;
	std::vector<MemberFunction> m_pubMemFun;
	std::vector<MemberFunction> m_privMemFun;
	std::vector<MemberFunction> m_protMemFun;
	std::vector<MemberVariable> m_pubMemVar;
	std::vector<MemberVariable> m_privMemVar;
	std::vector<MemberVariable> m_protMemVar;
	std::vector<MemberConstructor> m_pubConst;
	std::vector<MemberConstructor> m_privConst;
	std::vector<MemberConstructor> m_protConst;

	void filterMemberFunctions(std::vector<MemberFunction> memberFunctions);
	void filterMemberVariables(std::vector<MemberVariable> memberVariables);
	void filterMemberConstructors(std::vector<MemberConstructor> memberConstuctors);
};

} // namespace end: codegen

#endif // CLASS_HPP
