#ifndef _MATERIASOURCE_HPP_
# define _MATERIASOURCE_HPP_

#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource
{
public:
	MateriaSource();
	~MateriaSource();
	MateriaSource(const MateriaSource& tmp);
	MateriaSource& operator=(const MateriaSource& tmp);
	void learnMateria(AMateria* materia);
	AMateria* createMateria(std::string const & type);
private:
	AMateria *mat1;
	AMateria *mat2;
	AMateria *mat3;
	AMateria *mat4;	
};

#endif