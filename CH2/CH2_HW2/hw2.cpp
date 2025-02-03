#include <iostream>
#include <random>
class Animal
{
public:
	virtual void makeSound() const = 0;
	~Animal() {}
};

class Zoo
{
	static const int MAX_SIZE = 10;
	int animalCount = 0;
	Animal* animals[MAX_SIZE];
public:
	void addAnimal(Animal* animal)
	{
		if (animalCount < MAX_SIZE)
		{
			animals[animalCount++] = animal;
		}
		else
		{
			std::cout << "Animal Array is out of range\n";
		}
	}
	void performActions()
	{
		for (int i = 0; i < animalCount; ++i)
		{
			if (animals[i] != nullptr)
			{
				animals[i]->makeSound();
			}
		}
	}
	~Zoo() 
	{
		for (int i = 0; i < animalCount; ++i)
		{
			delete animals[i];
		}
	}
};
class Dog : public Animal
{
public:
	void makeSound() const override
	{
		std::cout << "wal wal\n";
	}
};
class Cat : public Animal
{
public:
	void makeSound() const override
	{
		std::cout << "meow\n";
	}
};
class Cow : public Animal
{
public:
	virtual void makeSound() const override
	{
		std::cout << "um me\n";
	}
};
Animal* createRandomAnimal()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 2);
	switch (dis(gen))
	{
	case 0:
		return new Dog();
		break;
	case 1:
		return new Cat();
		break;
	case 2:
		return new Cow();
		break;
	default:
		// error
		break;
	}
}
int main()
{
	Zoo* zoo = new Zoo();
	Dog* dog1 = new Dog();
	Cat* cat1 = new Cat();
	Cat* cat2 = new Cat();
	Cow* cow1 = new Cow();
	zoo->addAnimal(dog1);
	zoo->addAnimal(cat1);
	zoo->addAnimal(cat2);
	zoo->addAnimal(cow1);
	zoo->addAnimal(createRandomAnimal());
	zoo->performActions();
	delete zoo;
	return 0;
}