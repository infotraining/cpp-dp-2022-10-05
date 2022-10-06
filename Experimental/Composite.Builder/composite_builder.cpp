#include <iostream>
#include <optional>
#include <string>

#include "person.hpp"
#include "person_builder.hpp"

int main()
{
    // clang-format off
    Person p = 
        Person::create("Jan", "Kowalski")
            .lives()
                .at("Westerplatte 2/8")
                .in("Cracow")
                .with_postal_code("31-000")
            .works()
                .in_company("Infotraining")
                .with_tax_id("PL00011100");
    // clang-format on

    std::cout << p.description() << "\n";

    Person other = Person::create("Ewa", "Kowalska")
        .lives()
            .in("Gliwice")
            .with_postal_code("44-100")
        .works()
            .in_company("FP")
            .with_tax_id("246278364");
}