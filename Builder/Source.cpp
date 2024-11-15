#include <iostream>
#include <vector>
#include <string>
using namespace std;

class IBuilder //Example: Boeing 747
{
public:
	virtual void BuildPartA() = 0;
	virtual void BuildPartB() = 0;
	virtual void BuildPartC() = 0;
};

class Product
{
private:
	vector<string> parts;

public:
	void Add(string part)
	{
		this->parts.push_back(part);
	}

	string ListParts()
	{
		string result;
		for (int i = 0; i < this->parts.size(); i++)
		{
			if(i > 0)
				result += ", ";
			result += this->parts[i];
		}

		return "Product parts: " + result + "\n";
	}
};

class Director
{
private:
	IBuilder * builder;

public:
	Director(IBuilder * builder)
	{
		this->builder = builder;
	}

	void BuildMinimalProduct()
	{
		this->builder->BuildPartA();
	}

	void BuildFullProduct()
	{
		this->builder->BuildPartA();
		this->builder->BuildPartB();
		this->builder->BuildPartC();
	}
};

class ConcreteBuilder : public IBuilder
{
private:
	Product * product;

public:
	ConcreteBuilder()
	{
		product = NULL;
		Reset();
	}

	~ConcreteBuilder()
	{
		if (product)
		{
			delete product;
			product = NULL;
		}
	}

	void Reset()
	{
		if (product)
		{
			delete product;
		}

		product = new Product();

	}

	void BuildPartA()
	{
		this->product->Add("PartA1");
	}

	void BuildPartB()
	{
		this->product->Add("PartB1");
	}

	void BuildPartC()
	{
		this->product->Add("PartC1");
	}

	Product GetProduct()
	{
		Product productCopy = (*product); //Copy product
		Reset();

		return productCopy;
	}
};

int main()
{
	ConcreteBuilder * builder = new ConcreteBuilder();
	Director director(builder);

	cout << "Standard basic product:\n";
	director.BuildMinimalProduct();
	cout << builder->GetProduct().ListParts();

	cout << "Standard full product:\n";
	director.BuildFullProduct();
	cout << builder->GetProduct().ListParts();

	//Using the pattern without a director
	cout << "Building a custom product:\n";
	builder->BuildPartA();
	builder->BuildPartC();
	cout << builder->GetProduct().ListParts();

	delete builder;
	cin.get();
}