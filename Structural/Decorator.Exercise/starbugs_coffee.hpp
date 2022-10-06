#ifndef COFFEEHELL_HPP_
#define COFFEEHELL_HPP_

#include <iostream>
#include <string>

class Coffee
{
public:
    virtual ~Coffee() = default;

    virtual float get_total_price() const = 0;
    virtual std::string get_description() const = 0;
    virtual void prepare() = 0;
};

class CoffeeBase : public Coffee
{
    float price_;
    std::string description_;

public:
    CoffeeBase(float price, const std::string& description) : price_{price}, description_{description}
    {
    }

    float get_total_price() const override
    {
        return price_;
    }

    std::string get_description() const override
    {
        return description_;
    }
};

class Espresso : public CoffeeBase
{
public:
    Espresso(float price = 4.0, const std::string& description = "Espresso")
        : CoffeeBase{price, description}
    {
    }

    void prepare() override
    {
        std::cout << "Making a perfect espresso: 7 g, 15 bar and 24 sec.\n";
    }
};

class Cappuccino : public CoffeeBase
{
public:
    Cappuccino(float price = 6.0, const std::string& description = "Cappuccino")
        : CoffeeBase{price, description}
    {
    }

    void prepare() override
    {
        std::cout << "Making a perfect cappuccino.\n";
    }
};

class Latte : public CoffeeBase
{
public:
    Latte(float price = 8.0, const std::string& description = "Latte")
        : CoffeeBase{price, description}
    {
    }

    void prepare() override
    {
        std::cout << "Making a perfect latte.\n";
    }
};

// TODO: Condiments: Whipped: 2.5$, Whisky: 6.0$, ExtraEspresso: 4.0$

// TODO: Add CoffeeDecorator and concrete decorators for condiments 
class CoffeeDecorator : public Coffee
{
    std::unique_ptr<Coffee> coffee_;
public:
    CoffeeDecorator(std::unique_ptr<Coffee> coffee) : coffee_{std::move(coffee)}
    {}

protected:
    Coffee& get_decorated_coffee() const
    {
        return *coffee_;
    }
};

class CoffeeDecoratorBase : public CoffeeDecorator
{
    float price_;
    std::string description_;
public:
    CoffeeDecoratorBase(std::unique_ptr<Coffee> coffee, float price, std::string desc)
        : CoffeeDecorator{std::move(coffee)}, price_{price}, description_{std::move(desc)}
    {}

    float get_total_price() const override
    {
        return get_decorated_coffee().get_total_price() + price_;
    }

    std::string get_description() const override
    {
        return get_decorated_coffee().get_description() + " + " + description_;
    }
};

class Whipped : public CoffeeDecoratorBase
{
public:
    Whipped(std::unique_ptr<Coffee> coffee, float price = 2.5, std::string desc = "Whipped Cream")
        : CoffeeDecoratorBase{std::move(coffee), price, std::move(desc)}        
    {}

    void prepare() override
    {
        get_decorated_coffee().prepare();
        std::cout << "Add whipped cream...\n";
    }
};

class Whisky : public CoffeeDecoratorBase
{
public:
    Whisky(std::unique_ptr<Coffee> coffee, float price = 6.0, std::string desc = "Whisky")
        : CoffeeDecoratorBase{std::move(coffee), price, std::move(desc)}        
    {}

    void prepare() override
    {
        get_decorated_coffee().prepare();
        std::cout << "Pour 5cl of whisky...\n";
    }
};

class ExtraEspresso : public CoffeeDecoratorBase
{
public:
    ExtraEspresso(std::unique_ptr<Coffee> coffee, float price = 4.0, std::string desc = "Extra espresso")
        : CoffeeDecoratorBase{std::move(coffee), price, std::move(desc)}        
    {}

    void prepare() override
    {
        get_decorated_coffee().prepare();
        Espresso{}.prepare();
    }
};


#endif /*COFFEEHELL_HPP_*/
